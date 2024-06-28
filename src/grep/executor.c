#include "grep.h"

static int calculate_file_count(const char **argv, int flagNoPattern);

/**
 * @brief Функция исполнителя, которая обрабатывает входные аргументы и вызывает
 * обработчик файлов
 *
 * @param argv массив аргументов командной строки
 * @param pattern указатель на шаблон для поиска
 * @param options указатель на структуру опций
 * @return int возвращает код ошибки
 */
int executor(const char **argv, const char *pattern, Flags const *options) {
  int errorCode = NO_RESULTS; /**< Код ошибки */
  int numFiles = 0;           /**< Количество файлов */
  int flagNoPattern = CLEAR; /**< Флаг отсутствия шаблона */

  if (options->e || options->f) {
    numFiles = calculate_file_count(
        argv, flagNoPattern); /**< Вычисление количества файлов */
  } else {
    flagNoPattern = SET; /**< Установка флага отсутствия шаблона */
    pattern =
        argv[optind]; /**< Установка шаблона из аргументов командной строки */
    numFiles = calculate_file_count(
        argv, flagNoPattern); /**< Вычисление количества файлов */
  }

  errorCode = file_handler(argv, pattern, numFiles, flagNoPattern,
                           options); /**< Вызов обработчика файлов */

  return errorCode; /**< Возврат кода ошибки */
}

/**
 * @brief Функция для вычисления количества файлов
 *
 * @param argv массив аргументов командной строки
 * @param flagNoPattern флаг отсутствия шаблона
 * @return int возвращает количество файлов
 */
int calculate_file_count(const char **argv, int flagNoPattern) {
  int numFiles = 0;   /**< Количество файлов */
  int index = optind; /**< Индекс */

  if (flagNoPattern) {
    index += 1;
  }

  for (int i = index; NULL != argv[i]; ++i) {
    if (argv[i][0] != '-') {
      numFiles += 1;
    }
  }

  return numFiles;
}
