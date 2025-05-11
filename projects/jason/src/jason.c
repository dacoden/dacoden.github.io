/*
File: jason.c
Author: Dimitrios Arvanitakis
ID: sdi2400007
Brief: Handles json files, and does ai chat conversation.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "neurolib.h"

int is_json_valid(const char *data) {
  int braces = 0, brackets = 0, quotes = 0;
  const char *ptr = data;
  // Began in the start of the data in the file, and reach the end of
  // the file where where the character is '/0'. Increase and decrease whenever
  // it reads the standard json characters in order to see if they all close
  // when they open.
  while (*ptr) {
    switch (*ptr) {
      case '{':
        braces++;
        break;
      case '}':
        braces--;
        break;
      case '[':
        brackets++;
        break;
      case ']':
        brackets--;
        break;
      case '"':
        quotes = !quotes;
        break;
      default:
        break;
    }

    // Checked for structural errors.
    if (braces < 0 || brackets < 0) {
      return 0;
    }
    ptr++;
  }

  return (braces == 0 && brackets == 0 && quotes == 0);
}

int main(int argc, char *argv[]) {
  // With argc != 2 and argc != 3, I accepted only the arguments wich have the
  // formation of
  // "./jason --bot / ./jason --extract <filename>".
  if ((argc != 2 || strcmp(argv[1], "--bot")) &&
      (argc != 3 || strcmp(argv[1], "--extract"))) {
    fprintf(stderr, "Usage: ./jason --bot / ./jason --extract <filename>\n");
    return 1;
  }
  char ch;
  int i, j;
  // Started with the first case (Extraction mode), with strcmp if it returns 0,
  // then there argv[1] is --extract.
  if (!strcmp(argv[1], "--extract")) {
    FILE *file = fopen(argv[2], "r");
    if (!file) {
      fprintf(stderr, "File does not exist\n");
      return 1;
    }
    // Checked if the file is empty, by moving pointer of the first byte of the
    // file to the last byte of the file and then with ftell(file) that returns
    // 0 if the file is empty, else the bytes of the file.
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
      fprintf(stderr, "Error: The file is empty.\n");
      fclose(file);
      return 1;
    }
    long length = ftell(file);
    fseek(file, 0,
          SEEK_SET);  // Reset the file pointer to the start of the file.
    char *data = malloc(sizeof(char) * (length + 1));
    if (!data) {
      fprintf(stderr, "Memory allocation failed\n");
      fclose(file);
      return 1;
    }

    fread(data, 1, length, file);
    // Added the NULL to string data.
    data[length] = '\0';

    if (!is_json_valid(data)) {
      fprintf(stderr, "Not an accepted JSON!\n");
      free(data);
      fclose(file);
      return 1;
    }
    free(data);
    fseek(file, 0,
          SEEK_SET);  // Reset the file pointer to the start of the file.
    // Made an infinitive loop that stops only if it finds "content".
    // And every time checked it that the character ch from the file is scanned
    // correctly.
    while (1) {
      // Made a loop that stops when it reads " in the file.
      while (fscanf(file, "%c", &ch) == 1 && ch != '"')
        ;
      // Made a memory allocation for the first character of word.
      char *word = malloc(sizeof(char));
      if (!word) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return 1;
      }
      i = 0;
      // Reallocated the word string until it reads '"' character from ch.
      // Added that character ch to string word.
      while (fscanf(file, "%c", &ch) == 1 && ch != '"') {
        char *temp = realloc(word, sizeof(char) * (i + 2));
        if (!temp) {
          fprintf(stderr, "Memory reallocation failed\n");
          free(word);
          fclose(file);
          return 1;
        }
        word = temp;
        word[i++] = ch;
      }
      // Added the NULL to string word.
      word[i] = '\0';
      // Checked with strcmp if word is content and returns 0.
      if (!strcmp(word, "content")) {
        // Freed word in order to print something else.
        free(word);
        // Made a loop that stops when it reads " in the file, where it is what
        // I look for.
        while (fscanf(file, "%c", &ch) == 1 && ch != '"')
          ;
        // Made a memory allocation for the first character of word.
        word = malloc(sizeof(char));
        if (!word) {
          fprintf(stderr, "Memory allocation failed\n");
          fclose(file);
          return 1;
        }
        i = 0;
        // Reallocated the word string until it reads '"' character from ch.
        // Added that character ch to string word.
        while (fscanf(file, "%c", &ch) == 1 && ch != '"') {
          /*
          Brief: Checked if ch is \, if it is that then I get two cases. First
          case that the next letter is n then prints the word with a change of
          line, and begin on a new word.
          */
          if (ch == '\\') {
            if (fscanf(file, "%c", &ch) == 1) {
              if (ch == 'n') {
                // Added the NULL to string word.
                word[i] = '\0';
                fprintf(stdout, "%s\n", word);
                free(word);
                // Made a memory allocation for the first character of word.
                word = malloc(sizeof(char));
                if (!word) {
                  fprintf(stderr, "Memory allocation failed\n");
                  fclose(file);
                  return 1;
                }
                i = 0;
              }
              // Second case is that the next letter is \ then I just put them
              // in word.
              else {
                char *temp = realloc(word, sizeof(char) * (i + 3));
                if (!temp) {
                  fprintf(stderr, "Memory reallocation failed\n");
                  free(word);
                  fclose(file);
                  return 1;
                }
                word = temp;
                word[i++] = '\\';
                word[i++] = ch;
              }
            }
          } else {
            char *temp = realloc(word, sizeof(char) * (i + 2));
            if (!temp) {
              fprintf(stderr, "Memory reallocation failed\n");
              free(word);
              fclose(file);
              return 1;
            }
            word = temp;
            word[i++] = ch;
          }
        }
        // Added the NULL to string word.
        word[i] = '\0';
        fprintf(stdout, "%s", word);
        free(word);
        break;
      }
      free(word);
    }
    fclose(file);
    return 0;
  }
  // Started with the first case (Conversation mode), with strcmp if it returns
  // 0, then there argv[1] is --bot.
  else if (!strcmp(argv[1], "--bot")) {
    fprintf(stdout, "> What would you like to know? ");
    // Called neurosym_init() function that gets an api key and
    // initiallizes some other functions in order to use real ai with tokens.
    neurosym_init();
    // Made a loop that stops only if the user inputs EOF(End Of File),"ctr +
    // D". And every time checked it that the character ch from the stdin is
    // scanned correctly.
    while (fscanf(stdin, "%c", &ch) != EOF) {
      // Made a memory allocation for the first character of word.
      char *word = malloc(sizeof(char));
      if (!word) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
      }
      j = 0;
      // Reallocated the word string until it reads '\n' character from ch.
      // Added that character ch to string word.
      while (fscanf(stdin, "%c", &ch) == 1 && ch != '\n') {
        char *temp = realloc(word, sizeof(char) * (j + 2));
        if (!temp) {
          fprintf(stderr, "Memory reallocation failed\n");
          free(word);
          return 1;
        }
        word = temp;
        word[j++] = ch;
      }
      // Added the NULL to string word.
      word[j] = '\0';
      // Used the word as input to the response, which gets a string and based
      // on the tokens and randomness it returns a response to the word.
      char *response_result = response(word);
      free(word);
      // Checked if the response is accurate.
      if (!response_result) {
        fprintf(stderr, "Error: Failed to get response from the server\n");
        continue;
      }
      // Copied the response_result to json and used json, like an array of
      // characters. Also I treat json array like a json file because it has the
      // same structure.
      char *json = strdup(response_result);
      free(response_result);
      if (!json) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
      }
      i = -1;
      // Made an infinitive loop that stops only if it finds "content".
      // And every time checked it that the character json[++i] from the json
      // array is scanned correctly.
      while (1) {
        // Made a loop that stops when it reads " in the json array and
        // increases the json pointer by one.
        while (json[++i] && json[i] != '"')
          ;
        word = malloc(sizeof(char));
        if (!word) {
          fprintf(stderr, "Memory allocation failed\n");
          free(json);
          return 1;
        }
        j = 0;
        // Reallocated the word string until it reads '"' character from
        // json[i]. Added that character json[i] to string word, while
        // increasing the json pointer by one.
        while (json[++i] && json[i] != '"') {
          char *temp = realloc(word, sizeof(char) * (j + 2));
          if (!temp) {
            fprintf(stderr, "Memory reallocation failed\n");
            free(json);
            free(word);
            return 1;
          }
          word = temp;
          word[j++] = json[i];
        }
        // Added the NULL to string word.
        word[j] = '\0';
        if (!strcmp(word, "content")) {
          free(word);
          while (json[++i] && json[i] != '"')
            ;
          word = malloc(sizeof(char));
          if (!word) {
            fprintf(stderr, "Memory allocation failed\n");
            free(json);
            return 1;
          }
          j = 0;
          while (json[++i] && json[i] != '"') {
            /*
            Brief: Checked if json[i] is \, if it is that then I get two cases.
            First case that the next letter is n then prints the word with a
            change of line, and begin on a new word.
            */
            if (json[i] == '\\') {
              if (json[++i]) {
                if (json[i] == 'n') {
                  // Added the NULL to string word.
                  word[j] = '\0';
                  fprintf(stdout, "%s\n", word);
                  free(word);
                  // Made a memory allocation for the first character of word.
                  word = malloc(sizeof(char));
                  if (!word) {
                    fprintf(stderr, "Memory allocation failed\n");
                    free(json);
                    return 1;
                  }
                  j = 0;
                }
                // Second case is that the next letter is \ then I just put them
                // in word.
                else {
                  char *temp = realloc(word, sizeof(char) * (j + 3));
                  if (!temp) {
                    fprintf(stderr, "Memory reallocation failed\n");
                    free(json);
                    free(word);
                    return 1;
                  }
                  word = temp;
                  word[j++] = '\\';
                  word[j++] = json[i];
                }
              }
            } else {
              char *temp = realloc(word, sizeof(char) * (j + 2));
              if (!temp) {
                fprintf(stderr, "Memory reallocation failed\n");
                free(json);
                free(word);
                return 1;
              }
              word = temp;
              word[j++] = json[i];
            }
          }
          // Added the NULL to string word.
          word[j] = '\0';
          fprintf(stdout, "%s", word);
          free(json);
          free(word);
          break;
        }
        free(word);
      }
      fprintf(stdout, "\n> What would you like to know? ");
    }
    fprintf(stdout, "Terminating\n");
    return 0;
  }
}