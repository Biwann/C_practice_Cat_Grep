#include "s21_grep.h"

void FreeMemory(opt *actOpt);

int main(int n, char **arr) {
  opt activeOptions = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, 0};
  int error = 0;

  error = CheckOptions(&activeOptions, arr, n);

  if (!error) {
    Process(&activeOptions, arr, n);
  }
  FreeMemory(&activeOptions);
  return 0;
}

void FreeMemory(opt *actOpt) {
  for (int i = 0; i < actOpt->eAmount; i++) {
    if (actOpt->eSample[i]) free(actOpt->eSample[i]);
  }
  free(actOpt->eSample);
}
