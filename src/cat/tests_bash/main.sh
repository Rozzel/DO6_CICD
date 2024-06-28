#!/bin/bash

# shellcheck disable=SC1091
source ./tests_bash/modules/utilities.sh
source ./tests_bash/modules/compare.sh

TOTAL_TESTS=0
SUCCESSFUL_TESTS=0

OUTPUT_FILE="output.txt"
PROGRAM="./s21_cat"
FILES="./tests_bash/files/"

# Массив с флагами
declare -a arrFlags

arrFlags=(
  ""
  "-benstv" "-bnvste"
  "-b -e -n -s -t -v"
  "-t" "-n" "-b" "-s" "-v" "-e"
  "-n -b" "-nb"
  "-s -n -e" "-sne"
)

if [[ "$(uname)" == "Linux" ]]; then
  arrFlags+=("-T" "-E" "-vT" "--number" "--squeeze-blank" "--number-nonblank")
fi

for inputFile in "$FILES"*; do
  # Используем basename для получения имени файла без пути
  OUTPUT_FILE="output_$(basename "$inputFile")"

  # Запускаем тестирование для текущего файла
  for cmd in "${arrFlags[@]}"; do
    ((TOTAL_TESTS++))
    compare_results "$cmd" "$inputFile" "$PROGRAM" "$OUTPUT_FILE"
  done
done

log_console "ˁ˚ᴥ˚ˀ Тестов: $SUCCESSFUL_TESTS из $TOTAL_TESTS"
