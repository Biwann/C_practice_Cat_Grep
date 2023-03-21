#include "cat.h"

#include <ctype.h>

void ProcessFiles(char **arr, int n) {
  FILE *in = NULL;
  opt activeOptions = {0};

  CheckOptions(&activeOptions, arr, n);

  if (activeOptions.b == -1) return;
  for (int i = optind; i < n; i++) {
    in = fopen(arr[i], "r");
    if (in) {
      PrintWithOptions(&activeOptions, in);
    } else {
      printf("no such file");
    }
    fclose(in);
  }
  if (optind >= n) {
    PrintWithOptions(&activeOptions, NULL);
  }
}

void CheckOptions(opt *actOpt, char **arr, int n) {
  const struct option opts[] = {
      {"number-nonblank", 0, 0, 'b'},
      {"number", 0, 0, 'n'},
      {"squeeze-blank", 0, 0, 's'},

      {0, 0, 0, 0},
  };

  char res = 0;
  while ((res = getopt_long(n, arr, "beEnstTv", opts, 0)) != -1) {
    switch (res) {
      case 'b':
        actOpt->b = 1;
        break;
      case 'e':
        actOpt->e = 1;
        actOpt->v = 1;
        break;
      case 'E':
        actOpt->e = 1;
        break;
      case 'n':
        actOpt->n = 1;
        break;
      case 's':
        actOpt->s = 1;
        break;
      case 't':
        actOpt->t = 1;
        actOpt->v = 1;
        break;
      case 'T':
        actOpt->t = 1;
        break;
      case 'v':
        actOpt->v = 1;
        break;
      case '?':
        printf("wrong option\n");
        actOpt->b = -1;
        return;
        break;
    }
  }
}

void PrintWithOptions(opt *actOpt, FILE *in) {
  int state = 0;
  char c = 0;
  int near_empty_line = 0;
  int line = 1;

  while (c != EOF) {
    if (!in) {
      c = getchar();
    } else
      c = fgetc(in);
    if (c == EOF) continue;
    switch (state) {
      case 0:

        if (actOpt->s == 1 && near_empty_line && c == '\n') continue;

        if (actOpt->b == 1) {
          if (c != '\n') {
            printf("%6d\t", line);
            line++;
          }
        } else if (actOpt->n == 1) {
          printf("%6d\t", line);
          line++;
        }

        if (actOpt->t == 1 && c == '\t') {
          printf("^I");
          state = 1;
          continue;
        }

        if (actOpt->v == 1) {
          if (CheckCharacter(c) == 1) {
            state = 1;
            continue;
          }
        }

        if (actOpt->e == 1 && c == '\n') printf("$");

        if (c != '\n') {
          state = 1;
          near_empty_line = 0;
        } else
          near_empty_line = 1;
        break;
      case 1:
        if (actOpt->t == 1 && c == '\t') {
          printf("^I");
          continue;
        }

        if (actOpt->v == 1) {
          if (CheckCharacter(c) == 1) {
            continue;
          }
        }

        if (c == '\n') {
          if (actOpt->e == 1) printf("$");
          near_empty_line = 0;
          state = 0;
        }
        break;
    }
    printf("%c", c);
  }
}

int CheckCharacter(char c) {
  int flag = 0;

  if (!isascii(c) && !isprint(c)) {
    printf("M-");

    flag = 1;
  }
  c = toascii(c);
  if (iscntrl(c) && c != '\n' && c != '\t') {
    if (c == 127)
      printf("^?");
    else
      printf("^%c", c + 64);
    flag = 1;
  }
  return flag;
}