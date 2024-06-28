#include "grep.h"

/**
 * @brief Инициализирует шаблон для поиска
 *
 * @param pattern указатель на шаблон
 * @param string строка для инициализации шаблона
 */
void init_pattern(char *pattern, const char *string) {
  if (0 == *string) {
    strcpy(pattern, ".*\0");
  }

  if (0 == pattern[0]) {
    strcpy(pattern, string);
  } else if (strcmp(pattern, ".*") != 0) {
    strcat(pattern, "|");
    strcat(pattern, string);
  }
}

/**
 * @brief Инициализирует структуру опций в соответствии с переданным символом
 *
 * @param options указатель на структуру опций
 * @param symbol символ опции
 * @param pattern указатель на шаблон
 * @return int возвращает код ошибки
 */
int init_struct(Flags *options, int symbol, char *pattern) {
  int errorCode = OK;

  switch (symbol) {
    case 'v':
      options->v = SET;
      break;
    case 'i':
      options->i = SET;
      break;
    case 'o':
      options->o = SET;
      break;
    case 'l':
      options->l = SET;
      break;
    case 'n':
      options->n = SET;
      break;
    case 'c':
      options->c = SET;
      break;
    case 'e':
      options->e = SET;
      init_pattern(pattern, optarg);
      break;
    case 'f':
      options->f = SET;
      errorCode = f_handler(pattern);
      break;
    case 's':
      options->s = SET;
      break;
    case 'h':
      options->h = SET;
      break;
    case '?':
      errorCode = ERROR;
  }

  return errorCode;
}
