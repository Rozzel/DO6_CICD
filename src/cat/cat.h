#ifndef CAT_H
#define CAT_H

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/** \mainpage Project Documentation
  \section Library
  - <getopt.h> для разбора аргументов командной строки с короткими и длинными
  опциями.
  - <stdbool.h> для использования типа bool для логических переменных.
  - <stdio.h> для стандартного ввода и вывода, работы с файлами (FILE, stderr,
  stdin, fopen, fclose, printf, fprintf).
  - <stdlib.h> для общих утилит, таких как управление памятью и процессами
  (exit).
  - <unistd.h> для работы с POSIX-совместимыми операциями (unlink).
  \section Project
  - <a href="files.html">Файлы</a>
  - <a href="annotated.html">Структуры</a>
  - <a href="pages.html">Документация</a>
 */

/**
 * @struct options
 * @brief Структура для хранения настроек флагов командной строки.
 *
 * Эта структура используется для хранения состояний флагов командной строки,
 * которые определяют поведение программы. Каждое поле соответствует
 * определенному флагу командной строки.
 */
struct options {
  bool v;  ///< Вывод непечатаемых символов. Активируется флагом -v.
  bool b;  ///< Нумерация непустых строк. Активируется флагом -b.
  bool e;  ///< Вывод символа $ в конце каждой строки. Активируется флагом -e.
  bool E;  ///< Аналогично флагу -e, но активируется флагом -E.
  bool n;  ///< Нумерация всех строк. Активируется флагом -n.
  bool s;  ///< Сжатие нескольких пустых строк в одну. Активируется флагом -s.
  bool t;  ///< Вывод табуляций как ^I. Активируется флагом -t.
  bool T;  ///< Аналогично флагу -t, но активируется флагом -T.
};

void operation(struct options flag, char thisSymbol, char previousSymbol,
               int *pCountLines, int consecutiveLineBreaks);

void option_s(const char *pThisSymbol, char previous_simbol,
              int consecutiveLineBreaks, int *pIsItNull);
void option_v(char *pThisSymbol);
void option_e(const char *pThisSymbol);
void option_t(char *pThisSymbol);
void option_b(const char *pThisSymbol, char previousSymbol, int *pCountLines);
void option_n(char previousSymbol, int *pCountLines);

int find_first_file(int argc, char *argv[]);
void process_input(struct options flag, FILE *file);
struct options process_options(int argc, char *argv[]);
void process_files(struct options flag, int argc, char *argv[], int startFiles);

#endif  // CAT_H
