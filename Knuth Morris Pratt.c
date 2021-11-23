#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 200000005

void computeLPSArray(char *pat, int m, int *lps);
void kmp(char* pat, char* txt, FILE *out);

int main() {
  FILE *in = (FILE*) malloc(sizeof(FILE)), *out = (FILE*) malloc(sizeof(FILE));
  // array of input files
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
    "test1kmp.out",
    "test2kmp.out",
    "test3kmp.out",
    "test4kmp.out",
    "test5kmp.out",
    "test6kmp.out",
    "test7kmp.out",
    "test8kmp.out"
  };
  char *text = malloc(MAX);
  char *model = malloc(MAX);
  char *s1 = malloc(MAX);
  char *s2 = malloc(MAX);
  // iterate through all the tests
  for (int i = 0; i <= 7; i++) {
    // open the test file and create the output file
    // for the test
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
    kmp(model, text, out);
    // clear the variables
    strcpy(text, "\0");
    strcpy(model, "\0");
    // close files
    fclose(in);
    fclose(out);
  }
  free(text);
  free(model);
  free(s2);
  return 0;
}

void computeLPSArray(char *pat, int m, int *lps)
{
  // length of the previous longest prefix suffix
  int len = 0;

  lps[0] = 0; // lps[0] is always 0

  // the loop calculates lps[i] for i = 1 to m-1
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
          else // if (len == 0)
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

  // create lps[] that will hold the longest prefix suffix
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

      // mismatch after j matches
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
