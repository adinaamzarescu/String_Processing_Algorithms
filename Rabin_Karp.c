#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// d is the min number of characters in the input alphabet 
#define d 1
#define NRFILES 40
#define NAME 25
#define MAX 200000006

void rabin_karp(char * model, char * text, int q, FILE *out);

int main()
{
  FILE *in, *out;
  // Array of input files
  char in_files[NRFILES + 1][NAME] = {
    "./input/test1.in",
    "./input/test2.in",
    "./input/test3.in",
    "./input/test4.in",
    "./input/test5.in",
    "./input/test6.in",
    "./input/test7.in",
    "./input/test8.in",
    "./input/test9.in",
    "./input/test10.in",
    "./input/test11.in",
    "./input/test12.in",
    "./input/test13.in",
    "./input/test14.in",
    "./input/test15.in",
    "./input/test15.in",
    "./input/test17.in",
    "./input/test18.in",
    "./input/test19.in",
    "./input/test20.in",
    "./input/test21.in",
    "./input/test22.in",
    "./input/test23.in",
    "./input/test24.in",
    "./input/test25.in",
    "./input/test26.in",
    "./input/test27.in",
    "./input/test28.in",
    "./input/test29.in",
    "./input/test30.in",
    "./input/test31.in",
    "./input/test32.in",
    "./input/test33.in",
    "./input/test34.in",
    "./input/test35.in",
    "./input/test36.in",
    "./input/test37.in",
    "./input/test38.in",
    "./input/test39.in",
    "./input/test40.in"
  };
  // Array of output files
  char out_files[NRFILES + 1][NAME] = {
    "./out-rk/test1rk.out",
    "./out-rk/test2rk.out",
    "./out-rk/test3rk.out",
    "./out-rk/test4rk.out",
    "./out-rk/test5rk.out",
    "./out-rk/test6rk.out",
    "./out-rk/test7rk.out",
    "./out-rk/test8rk.out",
    "./out-rk/test9rk.out",
    "./out-rk/test10rk.out",
    "./out-rk/test11rk.out",
    "./out-rk/test12rk.out",
    "./out-rk/test13rk.out",
    "./out-rk/test14rk.out",
    "./out-rk/test15rk.out",
    "./out-rk/test15rk.out",
    "./out-rk/test17rk.out",
    "./out-rk/test18rk.out",
    "./out-rk/test19rk.out",
    "./out-rk/test20rk.out",
    "./out-rk/test21rk.out",
    "./out-rk/test22rk.out",
    "./out-rk/test23rk.out",
    "./out-rk/test24rk.out",
    "./out-rk/test25rk.out",
    "./out-rk/test26rk.out",
    "./out-rk/test27rk.out",
    "./out-rk/test28rk.out",
    "./out-rk/test29rk.out",
    "./out-rk/test30rk.out",
    "./out-rk/test31rk.out",
    "./out-rk/test32rk.out",
    "./out-rk/test33rk.out",
    "./out-rk/test34rk.out",
    "./out-rk/test35rk.out",
    "./out-rk/test36rk.out",
    "./out-rk/test37rk.out",
    "./out-rk/test38rk.out",
    "./out-rk/test39rk.out",
    "./out-rk/test40rk.out"
  };

  char *text = malloc(MAX);
  char *model = malloc(MAX);
  strcpy(model, "\0");
  strcpy(text, "\0");
  // The strings that will contain the
  // model to be matched and the text to be searched in
  char *s1 = malloc(MAX);
  char *s2 = malloc(MAX);
  // A prime number for the hashing process
  int q = 89261;

  // Iterate through all the tests
  for (int i = 0; i < NRFILES; ++i) {
    char file_in[NAME];
    char file_out[NAME];
    strcpy(file_in, in_files[i]);
    strcpy(file_out, out_files[i]);
    // Open input file
    in = fopen(file_in, "r");
    if (!in) {
        fprintf(stderr, "ERROR: Can't open file %s", in_files[i]);
        return -1;
    }
    // Open output file
    out = fopen(file_out, "wt");
    if (!out) {
        fprintf(stderr, "ERROR: Can't open file %s", out_files[i]);
        return -1;
    }

    // Reading the pattern
    fscanf(in, "%s", s1);
    if (!strcmp(s1, "Pattern:")) {
      fscanf(in, "%s", s1);
      while (strcmp(s1, "Text:")) {
        strcat(model, s1);
        fscanf(in, "%s", s1);
        if (!strcmp(s1, "Text:"))
          break;
        strcat(model, " ");
      }
    }

    // Reading the text
    while (fscanf(in, "%s", s2) != EOF) {
      strcat(text, s2);
      strcat(text, " ");
    }

    rabin_karp(model, text, q, out);
    // Clear the variables
    strcpy(model, "\0");
    strcpy(text, "\0");
    strcpy(s2, "\0");
    strcpy(s1, "\0");
    // Close files
    fclose(in);
    fclose(out);
  }
  free(text);
  free(model);
  free(s2);
  free(s1);
  return 0;
}

void rabin_karp(char *model, char *text, int q, FILE *out) {
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
  // The hash for the pattern 
  // and the hash of the first part of 
  // the text of same length

  int ok = 0;
  // Move across the entire text in search of word of the same 
  // length of model    
  for (i = 0; i <= n - m; i++) {
   // Comapre hash of position and text
    if (pattern_hash == text_hash) {
      for (j = 0; j < m; j++) {
        if (text[i + j] != model[j])
          break;
      }
      // If word found
      if (j == m) {
        fprintf(out, "Pattern found at index: %d\n", i);
        ok = 1;
      }
    }

    if (i < n - m) {
      text_hash = (d * (text_hash - text[i] * h) + text[i + m]) % q;
      // In case text_hash is negative, reset it to be greater than 0
      if (text_hash < 0) {
        text_hash = (text_hash + q);
      }
    }
  }
  if (ok == 0) {
    fprintf(out, "No pattern found\n");
  }
}
