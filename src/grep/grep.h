#ifndef GREP_H
#define GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** \mainpage Project Documentation
  \section Library
  - <getopt.h> для обработки аргументов командной строки.
  - <regex.h> для работы с регулярными выражениями.
  - <stdio.h> для стандартного ввода/вывода.
  - <stdlib.h> для работы с памятью и процессами.
  - <string.h> для работы со строками.
  \section Project
  - <a href="files.html">Файлы</a>
  - <a href="annotated.html">Структуры</a>
  - <a href="pages.html">Документация</a>
 */

#define SIZE 1024
#define LITTLE_SIZE 128

/**
 * @brief Структура флагов для опций
 */
typedef struct {
  char v; /**< Флаг для инвертирования совпадений */
  char i; /**< Флаг для игнорирования регистра */
  char o; /**< Флаг для вывода только совпадений */
  char l; /**< Флаг для вывода только имен файлов */
  char n; /**< Флаг для вывода номеров строк */
  char c; /**< Флаг для вывода количества совпадений */
  char e; /**< Флаг для указания шаблона поиска */
  char f; /**< Флаг для чтения шаблона из файла */
  char s; /**< Флаг для тихого режима */
  char h; /**< Флаг убирает имена файлов при поиске в нескольких файлах */
} Flags;

enum ErrorCodes {
  OK = 0,
  NO_RESULTS = 1,
  ERROR = 2,
};

enum optionCodes {
  CLEAR = 0,
  SET = 1,
  HELP = 2,
};

// init.c
void init_pattern(char *pattern, const char *string);
int init_struct(Flags *options, int symbol, char *pattern);

// executor.c
int executor(const char **argv, const char *pattern, Flags const *options);

// handler.c
int file_handler(const char **argv, const char *pattern, int numFiles,
                 int flagNoPattern, Flags const *options);
int opt_handler(const char *fileName, int numFiles, int i, char *bufStr,
                const char *pattern, Flags const *options);
int o_handler(Flags const *options, char *bufStr, const char *pattern);
int c_handler(Flags const *options, int numFiles, const char *fileName,
              unsigned int numMatches);
int f_handler(char *pattern);

#endif  // GREP_H
