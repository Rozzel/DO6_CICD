#include "grep.h"

static int compile_regex(regex_t *preg, const char *pattern,
                         Flags const *options);
static void update_num_matches(unsigned int *numMatches, const Flags *options);

/**
 * @brief Обработчик файлов
 *
 * @param argv массив аргументов командной строки
 * @param pattern указатель на шаблон для поиска
 * @param numFiles количество файлов
 * @param flagNoPattern флаг отсутствия шаблона
 * @param options указатель на структуру опций
 * @return int возвращает код ошибки
 */
int file_handler(const char **argv, const char *pattern, int numFiles,
                 int flagNoPattern, Flags const *options) {
  int errorCode = NO_RESULTS;

  for (int i = 0; i < numFiles; ++i) {
    FILE *filePtr;

    int fileArgumentIndex = optind + i + flagNoPattern;
    const char *fileName = argv[fileArgumentIndex];

    if (NULL == (filePtr = fopen(fileName, "r"))) {
      if (!options->s) {
        fprintf(stderr, "s21_grep: %s: %s\n", fileName, strerror(2));
      }

      errorCode = ERROR;
    } else {
      char optionsL = CLEAR;
      regex_t preg;

      unsigned int numMatches = 0;

      int regcode = compile_regex(&preg, pattern, options);

      if (OK != regcode) {
        char reg_errbuf[LITTLE_SIZE] = {0};

        regerror(regcode, &preg, reg_errbuf, LITTLE_SIZE);
        fprintf(stderr, "Regexp compilation failed: '%s'\n", reg_errbuf);
        errorCode = ERROR;
      }

      if (ERROR != errorCode) {
        char bufStr[SIZE] = {0};

        int lineNumber = 1;
        while (NULL != fgets(bufStr, SIZE, filePtr)) {
          int isMatch = regexec(&preg, bufStr, 0, NULL, 0) == OK;
          int shouldInvertMatch = options->v;
          int isConditionMet = (!shouldInvertMatch && isMatch) ||
                               (shouldInvertMatch && !isMatch);

          if (isConditionMet) {
            if (options->c) {
              update_num_matches(&numMatches, options);
            }

            if (options->l) {
              optionsL = SET;
            } else {
              errorCode = opt_handler(fileName, numFiles, lineNumber, bufStr,
                                      pattern, options);
            }
          }
          lineNumber++;
        }
      }

      if (options->c) {
        errorCode = c_handler(options, numFiles, fileName, numMatches);
      }

      if (optionsL == SET) {
        printf("%s\n", fileName);
        errorCode = OK;
      }

      regfree(&preg);
      fclose(filePtr);
    }
  }

  return errorCode;
}

/**
 * @brief Обработчик опций
 *
 * @param fileName имя файла
 * @param numFiles количество файлов
 * @param i индекс
 * @param bufStr буферная строка
 * @param pattern шаблон
 * @param options указатель на структуру опций
 * @return int возвращает код ошибки
 */
int opt_handler(const char *fileName, int numFiles, int i, char *bufStr,
                const char *pattern, Flags const *options) {
  int errorCode = NO_RESULTS;

  if (!options->c) {
    if (numFiles > 1 && !options->h) {
      printf("%s:", fileName);
    }

    if (options->n) {
      printf("%d:", i);
    }

    if (options->o && !options->v) {
      errorCode = o_handler(options, bufStr, pattern);
    } else {
      fputs(bufStr, stdout);
      errorCode = OK;
    }

    if (!options->o) {
      int n = strlen(bufStr);

      if (bufStr[n] == '\0' && bufStr[n - 1] != '\n') {
        putchar('\n');
      }
    }
  }
  return errorCode;
}

/**
 * @brief Обработчик для подсчета количества совпадений
 *
 * @param options указатель на структуру опций
 * @param numFiles количество файлов
 * @param fileName имя файла
 * @param numMatches количество совпадений
 * @return int возвращает код ошибки
 */
int c_handler(Flags const *options, int numFiles, const char *fileName,
              unsigned int numMatches) {
  int errorCode = NO_RESULTS;

  if ((numFiles > 1) && !options->h) {
    printf("%s:%u\n", fileName, numMatches);
    errorCode = OK;
  } else {
    printf("%u\n", numMatches);
    errorCode = OK;
  }

  return errorCode;
}

/**
 * @brief Обработчик для определения совпадений в строке
 *
 * @param options указатель на структуру опций
 * @param bufStr буфер строки для поиска
 * @param pattern шаблон для поиска
 * @return int возвращает код ошибки
 */
int o_handler(Flags const *options, char *bufStr, const char *pattern) {
  int errorCode = NO_RESULTS;
  regex_t preg;

  int regcode = options->i ? regcomp(&preg, pattern, REG_ICASE)
                           : regcomp(&preg, pattern, REG_EXTENDED);

  if (OK != regcode) {
    char reg_errbuf[LITTLE_SIZE] = {0};

    regerror(regcode, &preg, reg_errbuf, LITTLE_SIZE);
    fprintf(stderr, "Regexp compilation failed: '%s'\n", reg_errbuf);
    errorCode = ERROR;
  }

  if (OK == regcode && !options->v) {
    regmatch_t pmatch[SIZE];
    char *s = bufStr;

    int continueSearch = 1;
    while (*s != '\0' && continueSearch) {
      if (0 != regexec(&preg, s, 1, pmatch, 0)) {
        continueSearch = 0;
      } else {
        printf("%.*s\n", (int)(pmatch->rm_eo - pmatch->rm_so),
               s + pmatch->rm_so);
        s += pmatch->rm_eo;
        errorCode = OK;
      }
    }
  }

  regfree(&preg);

  return errorCode;
}

/**
 * @brief Обработчик для чтения шаблона из файла и инициализации шаблона
 *
 * @param pattern указатель на шаблон для инициализации
 * @return int возвращает код ошибки
 */
int f_handler(char *pattern) {
  int errorCode = NO_RESULTS;

  FILE *filePatternPointer;
  const char *fileNamePattern = optarg;

  if (NULL == (filePatternPointer = fopen(fileNamePattern, "r"))) {
    fprintf(stderr, "s21_grep: %s: %s\n", fileNamePattern, strerror(2));
    errorCode = ERROR;
  } else {
    char patternBuffer[SIZE] = {0};

    while (NULL != fgets(patternBuffer, SIZE, filePatternPointer)) {
      if ('\n' == *patternBuffer) {
        strcpy(pattern, ".*\0");
      } else {
        patternBuffer[strlen(patternBuffer) - 1] = '\0';
        init_pattern(pattern, patternBuffer);
      }
    }
    fclose(filePatternPointer);
  }

  return errorCode;
}

/**
 * @brief Компилирует регулярное выражение
 *
 * @param preg указатель на структуру regex_t
 * @param pattern указатель на строку с шаблоном
 * @param options указатель на структуру опций Flags
 * @return int возвращает код ошибки
 */
int compile_regex(regex_t *preg, const char *pattern, Flags const *options) {
  int flags = REG_EXTENDED;

  if (options->i) {
    flags |= REG_ICASE;
  }

  int regcode = regcomp(preg, pattern, flags);

  if (regcode != 0) {
    char reg_errbuf[LITTLE_SIZE];
    regerror(regcode, preg, reg_errbuf, sizeof(reg_errbuf));
    fprintf(stderr, "Regexp compilation failed: '%s'\n", reg_errbuf);
    return ERROR;
  }
  return OK;
}

/**
 * @brief Обновляет количество совпадений
 *
 * @param numMatches указатель на количество совпадений
 * @param options указатель на структуру опций Flags
 */
void update_num_matches(unsigned int *numMatches, const Flags *options) {
  if (options->l) {
    *numMatches = 1;
  } else {
    ++(*numMatches);
  }
}
