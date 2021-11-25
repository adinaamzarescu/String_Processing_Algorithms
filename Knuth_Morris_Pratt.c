#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 200000005
#define NRFILES 40
#define NAME 25

void computeLPSArray(char *pat, int m, int *lps);
void kmp(char* pat, char* txt, FILE *out);

int main() {
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
    "./out-kmp/test1kmp.out",
    "./out-kmp/test2kmp.out",
    "./out-kmp/test3kmp.out",
    "./out-kmp/test4kmp.out",
    "./out-kmp/test5kmp.out",
    "./out-kmp/test6kmp.out",
    "./out-kmp/test7kmp.out",
    "./out-kmp/test8kmp.out",
    "./out-kmp/test9kmp.out",
    "./out-kmp/test10kmp.out",
    "./out-kmp/test11kmp.out",
    "./out-kmp/test12kmp.out",
    "./out-kmp/test13kmp.out",
    "./out-kmp/test14kmp.out",
    "./out-kmp/test15kmp.out",
    "./out-kmp/test15kmp.out",
    "./out-kmp/test17kmp.out",
    "./out-kmp/test18kmp.out",
    "./out-kmp/test19kmp.out",
    "./out-kmp/test20kmp.out",
    "./out-kmp/test21kmp.out",
    "./out-kmp/test22kmp.out",
    "./out-kmp/test23kmp.out",
    "./out-kmp/test24kmp.out",
    "./out-kmp/test25kmp.out",
    "./out-kmp/test26kmp.out",
    "./out-kmp/test27kmp.out",
    "./out-kmp/test28kmp.out",
    "./out-kmp/test29kmp.out",
    "./out-kmp/test30kmp.out",
    "./out-kmp/test31kmp.out",
    "./out-kmp/test32kmp.out",
    "./out-kmp/test33kmp.out",
    "./out-kmp/test34kmp.out",
    "./out-kmp/test35kmp.out",
    "./out-kmp/test36kmp.out",
    "./out-kmp/test37kmp.out",
    "./out-kmp/test38kmp.out",
    "./out-kmp/test39kmp.out",
    "./out-kmp/test40kmp.out"
  };

  char *text = malloc(MAX);
  char *model = malloc(MAX);
  strcpy(model, "\0");
  strcpy(text, "\0");
  // The strings that will contain the
  // model to be matched and the text to be searched in
  char *s1 = malloc(MAX);
  char *s2 = malloc(MAX);

  // Iterate through all the tests
  for (int i = 0; i < NRFILES; ++i) {
    // Open the test file and create the output file
    // for the test
    char file_in[NAME], file_out[NAME];
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

    kmp(model, text, out);
    // Clear the variables
    strcpy(text, "\0");
    strcpy(model, "\0");
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

void computeLPSArray(char *pat, int m, int *lps)
{
  // Length of the previous longest prefix suffix
  int len = 0;

  lps[0] = 0; // lps[0] is always 0

  // The loop calculates lps[i] for i = 1 to m-1
  int i = 1;
  while (i < m) {
      if (pat[i] == pat[len]) {
          len++;
          lps[i] = len;
          i++;
      }
      else // (pat[i] != pat[len])
      {
          // This is tricky. Consider the example.
          // AAACAAAA and i = 7. The idea is similar
          // to search step.
          if (len != 0) {
              len = lps[len - 1];

              // Also, note that we do not increment
              // i here
          }
          else // If (len == 0)
          {
              lps[i] = 0;
              i++;
          }
      }
  }
}

void kmp(char* pat, char* txt, FILE *out)
{
  int m = strlen(pat);
  int n = strlen(txt);
  int ok = 0;

  // Create lps[] that will hold the longest prefix suffix
  // values for pattern
  int lps[m];

  // Preprocess the pattern (calculate lps[] array)
  computeLPSArray(pat, m, lps);

  int i = 0; // index for txt[]
  int j = 0; // index for pat[]
  while (i < n) {
      if (pat[j] == txt[i]) {
          j++;
          i++;
      }

      if (j == m) {
          fprintf(out, "Pattern found at index: %d\n", i - j);
          ok = 1;
          j = lps[j - 1];
      }

      // Mismatch after j matches
      else if (i < n && pat[j] != txt[i]) {
          if (j != 0)
              j = lps[j - 1];
          else
              i = i + 1;
      }
  }
  if (!ok) {
    fprintf(out, "No pattern found\n");
  }
}
