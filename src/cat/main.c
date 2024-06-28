#include "cat.h"

/**
 * @file main.c
 * @brief Главная точка входа программы.
 *
 * Функция `main` инициирует обработку аргументов командной строки для
 * установления флагов работы программы, определяет начало списка файлов для
 * обработки и запускает процесс обработки файлов или стандартного ввода. Эта
 * функция управляет основным потоком выполнения программы, делегируя задачи
 * обработки входных данных специализированным функциям в зависимости от
 * полученных флагов и указанных входных файлов.
 *
 * @param argc Количество аргументов командной строки, переданных программе.
 * @param argv Массив строк, содержащий аргументы командной строки.
 * @return Возвращает 0 после успешного выполнения всех операций.
 *
 * @note Программа поддерживает как стандартный ввод, так и обработку списка
 * файлов, переданных в качестве аргументов. В случае если файлы для обработки
 * не указаны, программа ожидает ввода данных с стандартного ввода.
 *
 */
int main(int argc, char *argv[]) {
  struct options flag = process_options(argc, argv);
  int startFiles = find_first_file(argc, argv);

  process_files(flag, argc, argv, startFiles);

  return 0;
}