#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Opt {
  int e, i, v, c, l, n, h, s, f, o;
  char **eSample;
  int eAmount;
} opt;

int CheckOptions(opt *actOpt, char **arr, int n);

void AddInSamples(opt *actOpt, char *optarg);

void CopySamplesFromFile(opt *actOpt, FILE *samples);

void Process(opt *actOpt, char **arr, int n);

void SearchInFile(opt *actOpt, char *fileName, int lotsFiles);

void PrintLine(char *line);

void CopyString(char *into, char *from);

void MakeSearchString(char *searchString, opt *actOpt);
