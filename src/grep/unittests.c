/*
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file "tests_check/_unittests.check" instead.
 */

#include <check.h>
#include <unistd.h>

#include "grep.h"

/** @cond */
int s21_grep(int argc, char** argv) {
  int errorCode = NO_RESULTS;

  if (argc > 2) {
    Flags options = {0};

    char pattern[SIZE] = {0};
    int optionSymbol = 0;
    char* optstring = "violnce:f:sh?";

    while (-1 != (optionSymbol = getopt_long(argc, argv, optstring, 0, NULL))) {
      errorCode = init_struct(&options, optionSymbol, pattern);
    }

    if ((options.e || options.f) && (argc < 4)) {
      errorCode = ERROR;
    }

    if (ERROR != errorCode) {
      executor((const char**)argv, pattern, &options);
    }
  }

  return errorCode;
}
/** @endcond */

/**
 * @brief Клонирует строку.
 *
 * Функция выделяет память под новую строку того же размера, что и s, копирует в
 * неё содержимое s, включая терминальный нулевой символ, и возвращает указатель
 * на новую строку.
 * @param s Указатель на строку, которую необходимо склонировать.
 * @return Указатель на новую строку в случае успеха или NULL, если не удалось
 * выделить память.
 */
char* s21_strdup(const char* s) {
  size_t len = strlen(s) + 1;
  char* new = malloc(len);
  if (new == NULL) return NULL;
  memcpy(new, s, len);
  return new;
}

void test_grep(const char* input) {
  const char* resultS21 = "temp_s21.txt";
  const char* resultOrig = "temp_orig.txt";

  char* argv[64];
  int argc = 1;
  argv[0] = "./s21_grep";

  // Дублируем входную строку, чтобы избежать изменения оригинала
  char* inputCopy = s21_strdup(input);

  // Разделяем входную строку на флаги и пути к файлам
  char* token = strtok(inputCopy, " ");
  int isLimitReached = 0;
  const int maxArgs = 63;
  while (token && !isLimitReached) {
    argv[argc++] = token;
    token = strtok(NULL, " ");
    // Ограничение на количество аргументов
    if (argc >= maxArgs) {
      isLimitReached = 1;
    }
  }

  argv[argc] = NULL;

  (void)freopen(resultS21, "w", stdout);
  s21_grep(argc, argv);
  fclose(stdout);

  // Формируем команду для оригинального grep
  char cmd_orig[1024] = "grep ";
  for (int i = 1; i < argc; i++) {
    // Безопасное добавление аргументов в строку команды
    strncat(cmd_orig, argv[i], sizeof(cmd_orig) - strlen(cmd_orig) - 2);
    // Добавляем пробел между аргументами
    strncat(cmd_orig, " ", sizeof(cmd_orig) - strlen(cmd_orig) - 1);
  }
  // Добавляем перенаправление вывода и имя файла результата
  snprintf(cmd_orig + strlen(cmd_orig), sizeof(cmd_orig) - strlen(cmd_orig),
           "> %s", resultOrig);

  system(cmd_orig);

  // Сравниваем результаты
  char cmd_diff[1024];
  snprintf(cmd_diff, sizeof(cmd_diff), "diff %s %s", resultS21, resultOrig);
  int diff_result = system(cmd_diff);
  ck_assert_msg(diff_result == 0,
                "Outputs of s21_grep and original grep are different");

  unlink(resultS21);
  unlink(resultOrig);

  // Освобождаем память inputCopy после всех операций
  free(inputCopy);
}

START_TEST(part2_1) { test_grep("Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part2_2) {
  test_grep(
      "Hello ./tests_check/files/file1.txt ./tests_check/files/file2.txt");
}
END_TEST

START_TEST(part2_3) { test_grep("-i HELLO ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part2_4) {
  test_grep(
      "-i HELLO ./tests_check/files/file1.txt ./tests_check/files/file2.txt");
}
END_TEST

START_TEST(part2_5) { test_grep("-v Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part2_6) {
  test_grep(
      "-l Hello ./tests_check/files/file1.txt ./tests_check/files/file2.txt");
}
END_TEST

START_TEST(part2_7) { test_grep("-c Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part2_8) { test_grep("-n Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part2_9) {
  test_grep(
      "-n Hello ./tests_check/files/file1.txt ./tests_check/files/file2.txt");
}
END_TEST

START_TEST(part2_10) {
  test_grep("-e Hello -e Again ./tests_check/files/file1.txt");
}
END_TEST

START_TEST(part3_1) {
  test_grep(
      "-h Hello ./tests_check/files/file1.txt ./tests_check/files/file2.txt");
}
END_TEST

START_TEST(part3_2) { test_grep("-s Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part3_3) {
  test_grep("-f ./tests_check/files/file3.txt ./tests_check/files/file1.txt");
}
END_TEST

START_TEST(part3_4) { test_grep("-o Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part4_1) { test_grep("-iv Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part4_2) { test_grep("-in Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part4_3) { test_grep("-ce Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part4_4) { test_grep("-c -e Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part4_5) { test_grep("-nivh Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part4_6) { test_grep("-ie Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part4_7) { test_grep("-ne Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part4_8) { test_grep("-o -e Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part4_9) { test_grep("-cs Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part4_10) { test_grep("-vn Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part4_11) { test_grep("-io Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part4_12) {
  test_grep(
      "-sl Hello ./tests_check/files/file1.txt ./tests_check/files/file2.txt");
}
END_TEST

START_TEST(part4_13) { test_grep("-oh Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part4_14) { test_grep("-ho Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part4_15) {
  test_grep("-hf ./tests_check/files/file3.txt ./tests_check/files/file1.txt");
}
END_TEST

START_TEST(part4_16) { test_grep("-no Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part4_17) {
  test_grep("-nf ./tests_check/files/file3.txt ./tests_check/files/file1.txt");
}
END_TEST

START_TEST(part4_18) { test_grep("-nh Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part4_19) {
  test_grep(
      "-lo Hello ./tests_check/files/file1.txt ./tests_check/files/file2.txt");
}
END_TEST

START_TEST(part4_20) {
  test_grep("-lf ./tests_check/files/file3.txt ./tests_check/files/file1.txt");
}
END_TEST

START_TEST(part4_21) { test_grep("-lh Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part4_22) { test_grep("-ln Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part4_23) { test_grep("-co Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part4_24) {
  test_grep("-vf ./tests_check/files/file3.txt ./tests_check/files/file1.txt");
}
END_TEST

START_TEST(part4_25) {
  test_grep(
      "-ch Hello ./tests_check/files/file1.txt ./tests_check/files/file2.txt");
}
END_TEST

START_TEST(part4_26) { test_grep("-ic Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part4_27) { test_grep("-il Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part4_28) { test_grep("-ih Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part4_29) {
  test_grep("-if ./tests_check/files/file3.txt ./tests_check/files/file1.txt");
}
END_TEST

START_TEST(part4_30) { test_grep("-vc Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part4_31) { test_grep("-vl Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part4_32) { test_grep("-vh Hello ./tests_check/files/file1.txt"); }
END_TEST

START_TEST(part4_33) { test_grep("-cn Hello ./tests_check/files/file1.txt"); }
END_TEST

int main(void) {
  Suite* s1 = suite_create("part2_");
  TCase* tc1_1 = tcase_create("part2_");
  Suite* s2 = suite_create("part3_");
  TCase* tc2_1 = tcase_create("part3_");
  Suite* s3 = suite_create("part4_");
  TCase* tc3_1 = tcase_create("part4_");
  SRunner* sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, part2_1);
  tcase_add_test(tc1_1, part2_2);
  tcase_add_test(tc1_1, part2_3);
  tcase_add_test(tc1_1, part2_4);
  tcase_add_test(tc1_1, part2_5);
  tcase_add_test(tc1_1, part2_6);
  tcase_add_test(tc1_1, part2_7);
  tcase_add_test(tc1_1, part2_8);
  tcase_add_test(tc1_1, part2_9);
  tcase_add_test(tc1_1, part2_10);
  suite_add_tcase(s2, tc2_1);
  tcase_add_test(tc2_1, part3_1);
  tcase_add_test(tc2_1, part3_2);
  tcase_add_test(tc2_1, part3_3);
  tcase_add_test(tc2_1, part3_4);
  suite_add_tcase(s3, tc3_1);
  tcase_add_test(tc3_1, part4_1);
  tcase_add_test(tc3_1, part4_2);
  tcase_add_test(tc3_1, part4_3);
  tcase_add_test(tc3_1, part4_4);
  tcase_add_test(tc3_1, part4_5);
  tcase_add_test(tc3_1, part4_6);
  tcase_add_test(tc3_1, part4_7);
  tcase_add_test(tc3_1, part4_8);
  tcase_add_test(tc3_1, part4_9);
  tcase_add_test(tc3_1, part4_10);
  tcase_add_test(tc3_1, part4_11);
  tcase_add_test(tc3_1, part4_12);
  tcase_add_test(tc3_1, part4_13);
  tcase_add_test(tc3_1, part4_14);
  tcase_add_test(tc3_1, part4_15);
  tcase_add_test(tc3_1, part4_16);
  tcase_add_test(tc3_1, part4_17);
  tcase_add_test(tc3_1, part4_18);
  tcase_add_test(tc3_1, part4_19);
  tcase_add_test(tc3_1, part4_20);
  tcase_add_test(tc3_1, part4_21);
  tcase_add_test(tc3_1, part4_22);
  tcase_add_test(tc3_1, part4_23);
  tcase_add_test(tc3_1, part4_24);
  tcase_add_test(tc3_1, part4_25);
  tcase_add_test(tc3_1, part4_26);
  tcase_add_test(tc3_1, part4_27);
  tcase_add_test(tc3_1, part4_28);
  tcase_add_test(tc3_1, part4_29);
  tcase_add_test(tc3_1, part4_30);
  tcase_add_test(tc3_1, part4_31);
  tcase_add_test(tc3_1, part4_32);
  tcase_add_test(tc3_1, part4_33);

  srunner_add_suite(sr, s2);
  srunner_add_suite(sr, s3);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}