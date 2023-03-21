#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define optionsAmount 6

typedef struct Opt {
  int b, e, n, s, t, v;
} opt;

void ProcessFiles(char **arr, int n);

void CheckOptions(opt *actOpt, char **arr, int n);

void PrintWithOptions(opt *actOpt, FILE *in);

int CheckCharacter(char c);