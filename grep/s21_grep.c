#include "s21_grep.h"

int CheckOptions(opt *actOpt, char **arr, int n) {
  FILE *samples = NULL;
  char res = 0;
  while ((res = getopt_long(n, arr, "e:ivclnhsf:o", NULL, 0)) != -1) {
    switch (res) {
      case 'e':
        actOpt->e = 1;
        AddInSamples(actOpt, optarg);
        break;
      case 'i':
        actOpt->i = 1;
        break;
      case 'v':
        actOpt->v = 1;
        break;
      case 'c':
        actOpt->c = 1;
        break;
      case 'l':
        actOpt->l = 1;
        break;
      case 'n':
        actOpt->n = 1;
        break;
      case 'h':
        actOpt->h = 1;
        break;
      case 's':
        actOpt->s = 1;
        break;
      case 'f':
        samples = fopen(optarg, "r+");
        if (samples) {
          actOpt->f = 1;
          CopySamplesFromFile(
              actOpt, samples);  // заходит в файл и добавляет все в eSample
        } else {
          printf("wrong option\n");
          return 1;
        }
        break;
      case 'o':
        actOpt->o = 1;
        break;
      case '?':
        printf("wrong option\n");
        return 1;
        break;
    }
  }
  if (samples) fclose(samples);
  return 0;
}

void Process(opt *actOpt, char **arr, int n) {
  int firstFile = optind;
  if (!actOpt->e && !actOpt->f && firstFile < n) {
    AddInSamples(actOpt, arr[firstFile]);
    firstFile++;
  }

  int lotsFiles = (n - firstFile) > 1;
  for (int i = firstFile; i < n; i++) {
    SearchInFile(actOpt, arr[i], lotsFiles);
  }
}

void AddInSamples(opt *actOpt, char *opt) {
  if (actOpt->eAmount == 0) {
    actOpt->eSample = (char **)calloc(1, sizeof(char *));
    actOpt->eSample[actOpt->eAmount] = (char *)calloc(strlen(opt) + 1, 1);
  } else {
    char **temp = NULL;
    temp = (char **)realloc(actOpt->eSample,
                            (actOpt->eAmount + 1) * sizeof(char *));
    if (temp) {
      actOpt->eSample = temp;
      actOpt->eSample[actOpt->eAmount] = NULL;
      actOpt->eSample[actOpt->eAmount] = (char *)calloc(strlen(opt) + 1, 1);
    } else {
      free(actOpt->eSample);
      actOpt->eSample = NULL;
    }
  }
  if (actOpt->eSample[actOpt->eAmount]) {
    CopyString(actOpt->eSample[actOpt->eAmount], opt);
    actOpt->eAmount++;
  }
}

void CopySamplesFromFile(opt *actOpt, FILE *samples) {
  char *line = NULL;
  size_t linecap = 0;
  ssize_t linelen = 0;
  while ((linelen = getline(&line, &linecap, samples)) > 0) {
    AddInSamples(actOpt, line);
  }
  free(line);
}

void SearchInFile(opt *actOpt, char *fileName, int lotsFiles) {
  FILE *in = fopen(fileName, "r+");
  if (!in) {
    if (!actOpt->s) printf("no such file %s\n", fileName);
    return;
  }

  regex_t regex;
  char *line = NULL;
  int iFlag = 0, vFlag = 0, lineCount = 0, matchesCount = 0;
  int done = 0;
  size_t num = 0;
  char *searchString = calloc(10000, 1);

  if (actOpt->i == 1) iFlag = REG_ICASE;
  if (actOpt->v == 1) vFlag = REG_NOMATCH;

  MakeSearchString(searchString, actOpt);
  regcomp(&regex, searchString, iFlag + REG_EXTENDED);

  while (getline(&line, &num, in) != EOF) {
    if (line) {
      lineCount++;
      done = regexec(&regex, line, 0, 0, 0);
      if (done == vFlag) {
        matchesCount++;
        if (actOpt->l) {
        } else if (actOpt->c) {
        } else {
          if (lotsFiles && !actOpt->h) printf("%s:", fileName);
          if (actOpt->n) printf("%d:", lineCount);
          PrintLine(line);
        }
      }
    }
    if (actOpt->l && matchesCount > 0) break;
  }

  if (actOpt->c) {
    if (lotsFiles && !actOpt->h) printf("%s:", fileName);
    printf("%d\n", matchesCount);
  }
  if (actOpt->l && matchesCount > 0) printf("%s\n", fileName);
  if (line) free(line);
  free(searchString);
  regfree(&regex);
  fclose(in);
}

void PrintLine(char *line) {
  for (char *p = line; *p; p++) {
    if (*p != '\n') printf("%c", *p);
  }
  printf("\n");
}

void CopyString(char *into, char *from) {
  char *f = into;
  for (char *p = from; *p; p++) {
    if (*p != '\n') {
      *f = *p;
      f++;
    }
  }
}

void MakeSearchString(char *searchString, opt *actOpt) {
  for (int i = 0; i < actOpt->eAmount; i++) {
    if (*searchString != '\0') {
      strcat(searchString, "|");
      strcat(searchString, actOpt->eSample[i]);
    } else {
      strcpy(searchString, actOpt->eSample[i]);
    }
  }
}
