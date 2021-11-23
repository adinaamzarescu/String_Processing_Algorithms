#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// d is the min number of characters in the input alphabet 
#define d 1
#define MAX 200000005

void rabin_karp(char * model, char * text, int q, FILE *out);

int main() {
  // array of input files
  FILE *in = (FILE*) malloc(sizeof(FILE)), *out = (FILE*) malloc(sizeof(FILE));
  char in_files[9][9] = {
    "test1.in",
    "test2.in",
    "test3.in",
    "test4.in",
    "test5.in",
    "test6.in",
    "test7.in",
    "test8.in"
  };
  // array of output files
  char out_files[9][13] = {
    "test1rk.out",
    "test2rk.out",
    "test3rk.out",
    "test4rk.out",
    "test5rk.out",
    "test6rk.out",
    "test7rk.out",
    "test8rk.out"
  };

  char *text = malloc(MAX);
  // text = NULL;
  char *model = malloc(MAX);
  model = NULL;
  // a prime number for the hashing process
  int q = 89261;
  // the strings that will contain the
  // model to be matched and the text to be searched in
  char *s1 = malloc(MAX);
  char *s2 = malloc(MAX);
  //iterate through all the tests
  for (int i = 0; i < 8; i++) {
    char file_in[9], file_out[13];
    strcpy(file_in, in_files[i]);
    strcpy(file_out, out_files[i]);
    in = fopen(file_in, "rt");
    if (in == NULL) {
        fprintf(stderr, "ERROR: Can't open file %s", in_files[i]);
        return -1;
    }
    out = fopen(file_out, "wt");
    if (out == NULL) {
        fprintf(stderr, "ERROR: Can't open file %s", out_files[i]);
        return -1;
    }
    fscanf(in, "%s", s1);
    model = s1;
    while(fscanf(in, "%s", s2) != EOF) {
      strcat(text, s2);
      strcat(text, " ");
    }
    // copy the pattern and the text
    rabin_karp(model, text, q, out); 
    strcpy(model, "\0");
    strcpy(text, "\0");
    strcpy(s2, "\0");
    fclose(in);
    fclose(out);
  }
  free(text);
  free(model);
  free(s2);
  return 0;
}

void rabin_karp(char * model, char * text, int q, FILE *out) {
  int m = strlen(model);
  int n = strlen(text);
  int i, j;
  int pattern_hash = 0;
  int text_hash = 0;
  int h = 1;

  for (i = 0; i < m - 1; i++) {
    h = (h * d) % q;
  }

  for (i = 0; i < m; i++) {
    pattern_hash = (d * pattern_hash + model[i]) % q;
    text_hash = (d * text_hash + text[i]) % q;
  }
  // the hash for the pattern 
  // and the hash of the first part of 
  // the text of same length

  int ok = 0;
  // move across the entire text in search of word of the same 
  // length of model    
  for (i = 0; i <= n - m; i++) {
   //comapre hash of position and text
    if (pattern_hash == text_hash) {
      for (j = 0; j < m; j++) {
        if (text[i + j] != model[j])
          break;
      }
      // if word found
      if (j == m) {
        fprintf(out, "Pattern found at index: %d\n", i);
        ok = 1;
      }
    }

    if (i < n - m) {
      text_hash = (d * (text_hash - text[i] * h) + text[i + m]) % q;
      // in case text_hash is negative, reset it to be greater than 0
      if (text_hash < 0) {
        text_hash = (text_hash + q);
      }
    }
  }
  if (ok == 0) {
    fprintf(out, "No pattern found\n");
  }
}
