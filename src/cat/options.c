#include "cat.h"

/**
 * @brief Обрабатывает последовательные переносы строк при активации флага -s.
 *
 * Функция предназначена для сокращения множественных последовательных переносов
 * строк до одного. Это достигается путём установки флага в `pIsItNull`, который
 * указывает на необходимость игнорирования текущего символа переноса строки,
 * если до этого уже были обнаружены два или более переноса подряд.
 *
 * @param pThisSymbol Указатель на текущий анализируемый символ.
 * @param previous_simbol Предыдущий символ в потоке данных. Используется для
 * определения, является ли текущий символ частью последовательных переносов
 * строк.
 * @param consecutiveLineBreaks Счётчик последовательных переносов строк. Если
 * значение больше 1, и текущий и предыдущий символы являются переносами строк,
 * текущий символ будет проигнорирован.
 * @param pIsItNull Указатель на переменную, которая устанавливается в 1, если
 * текущий символ переноса строки должен быть проигнорирован в соответствии с
 * логикой флага -s.
 *
 * @note Эта функция является частью обработки флагов для утилиты, имитирующей
 * поведение стандартной команды `cat` в UNIX-подобных системах.
 */
void option_s(const char *pThisSymbol, char previous_simbol,
              int consecutiveLineBreaks, int *pIsItNull) {
  if (*pThisSymbol == '\n' && previous_simbol == '\n' &&
      consecutiveLineBreaks > 1) {
    *pIsItNull = 1;
  }
}

/**
 * @brief Визуализирует непечатаемые символы.
 *
 * Функция преобразует непечатаемые символы (с кодом меньше 32, исключая 9
 * (табуляция) и 10 (перевод строки), а также символы с кодом больше 126) в
 * визуально отличимые представления. Для символов с кодом меньше 32 и не равным
 * 9 и 10, выводится символ '^', а их код увеличивается на 64, делая их видимыми
 * и интерпретируемыми как контрольные символы ASCII. Для символов с кодом
 * больше 126 производится уменьшение кода символа на 64.
 *
 * @param pThisSymbol Указатель на текущий обрабатываемый символ. Функция
 * модифицирует значение по этому адресу, если символ является непечатаемым.
 *
 * @note Функция используется для улучшения читабельности текста, содержащего
 * непечатаемые символы, путём их замены на визуально отличимые представления.
 * Это особенно полезно при анализе данных, содержащих такие символы.
 */
void option_v(char *pThisSymbol) {
  unsigned char symbol = (unsigned char)*pThisSymbol;

  if ((symbol < 9) || (symbol > 10 && symbol < 32) || (symbol > 126)) {
    printf("^");

    if (symbol < 126) {
      *pThisSymbol = symbol + 64;
    }

    if (symbol > 126) {
      *pThisSymbol = symbol - 64;
    }
  }
}

/**
 * @brief Добавляет символ '$' перед символом новой строки.
 *
 * Эта функция предназначена для визуального отображения конца строк при
 * активации соответствующего флага. Когда текущий символ является символом
 * новой строки ('\n'), перед ним в выводе отображается символ '$'. Это улучшает
 * визуализацию переводов строк, особенно при просмотре содержимого файлов, где
 * эти символы могут быть не очевидны.
 *
 * @param pThisSymbol Указатель на текущий обрабатываемый символ. Функция
 * проверяет, является ли этот символ символом новой строки.
 *
 * @note Этот подход часто используется в текстовых редакторах и при выводе
 * текстовых данных для облегчения восприятия структуры текста, особенно в
 * файлах, где концы строк имеют значение.
 */
void option_e(const char *pThisSymbol) {
  if (*pThisSymbol == '\n') {
    printf("$");
  }
}

/**
 * @brief Заменяет символ табуляции на визуальный маркер.
 *
 * Эта функция предназначена для обработки символов табуляции ('\t') при
 * активации соответствующего флага. Когда текущий символ является символом
 * табуляции, в выводе перед ним отображается символ '^', а сам символ табуляции
 * заменяется на символ 'I'. Это делается для улучшения визуализации и
 * читабельности текста, позволяя пользователю ясно видеть места, где
 * используется табуляция.
 *
 * @param pThisSymbol Указатель на текущий обрабатываемый символ. Если символ
 * является табуляцией, он заменяется на 'I', предварительно выводя маркер '^'.
 *
 * @note Применение этой функции особенно полезно при выводе текстов, где точное
 * представление пробельных символов имеет значение, например, при анализе кода
 * или отформатированных текстов.
 */
void option_t(char *pThisSymbol) {
  if (*pThisSymbol == '\t') {
    printf("^");

    *pThisSymbol = 'I';
  }
}

/**
 * @brief Нумерует непустые строки при активации флага -b.
 *
 * Функция `option_b` отвечает за нумерацию непустых строк, анализируя текущий и
 * предыдущий символы. Если предыдущий символ является символом новой строки
 * ('\n') и текущий символ не является символом новой строки, то это указывает
 * на начало новой непустой строки, и выполняется функция `option_n` для
 * нумерации этой строки.
 *
 * @param pThisSymbol Указатель на текущий символ. Используется для определения,
 * является ли текущая строка непустой.
 * @param previousSymbol Предыдущий символ в тексте. Используется для
 * определения начала новой строки.
 * @param pCountLines Указатель на счетчик строк. Функция `option_n` использует
 * этот счетчик для нумерации строк.
 *
 * @note Функция `option_b` используется в комбинации с `option_n` для условной
 * нумерации строк, пропуская пустые строки. Это особенно полезно при обработке
 * текстов с множеством пустых строк, где необходимо нумеровать только строки с
 * содержимым.
 */
void option_b(const char *pThisSymbol, char previousSymbol, int *pCountLines) {
  if (previousSymbol == '\n' && *pThisSymbol != '\n') {
    option_n(previousSymbol, pCountLines);
  }
}

/**
 * @brief Нумерует все строки при активации флага -n.
 *
 * Функция `option_n` отвечает за нумерацию всех строк в тексте. Нумерация
 * происходит только если предыдущий символ является символом новой строки
 * ('\n'), что указывает на начало новой строки. При этом счетчик строк
 * увеличивается на единицу, и номер строки выводится перед строкой с
 * форматированием, обеспечивающим выравнивание номеров строк.
 *
 * @param previousSymbol Предыдущий символ, используется для определения, когда
 * начинается новая строка.
 * @param pCountLines Указатель на переменную счетчика строк, которая
 * инкрементируется при обнаружении новой строки.
 *
 * @note Эта функция используется для добавления номеров строк к каждой строке
 * входных данных, что может быть полезно для анализа содержимого или отладки.
 * Форматирование номера строки обеспечивает читаемость и удобство восприятия
 * нумерованного текста.
 */
void option_n(char previousSymbol, int *pCountLines) {
  if (previousSymbol == '\n') {
    *pCountLines = *pCountLines + 1;

    printf("%6d\t", *pCountLines);
  }
}
