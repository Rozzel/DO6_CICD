#include "grep.h"

/**
 * @brief Основная функция программы
 *
 * @param argc количество аргументов командной строки
 * @param argv массив аргументов командной строки
 * @return int возвращает код ошибки
 */
int main(int argc, char **argv) {
  int errorCode = NO_RESULTS;

  if (argc > 2) {
    Flags options = {0};

    char pattern[SIZE] = {0};
    int optionSymbol = 0;
    char *optstring = "violnce:f:sh?";

    while (-1 != (optionSymbol = getopt_long(argc, argv, optstring, 0, NULL))) {
      errorCode = init_struct(&options, optionSymbol, pattern);
    }

    if ((options.e || options.f) && (argc < 4)) {
      errorCode = ERROR;
    }

    if (ERROR != errorCode) {
      executor((const char **)argv, pattern, &options);
    }
  }

  return errorCode;
}
