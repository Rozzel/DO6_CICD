#!/bin/bash

compare_results() {
  local cmd="$1"
  local inputFile="$2"
  local program="$3"
  local outputFile="$4"

  log_console "ˁ˚ᴥ˚ˀ Сравниваю результаты с помощью команды cat для <$inputFile> с флагом <$cmd>"

  if [ -z "$cmd" ]; then
    $program "$inputFile" > "$outputFile"
  else
    $program "$cmd" "$inputFile" > "$outputFile"
  fi

  if diff "$outputFile" <([ -z "$cmd" ] && cat "$inputFile" || cat "$cmd" "$inputFile"); then
    log_console "Тест $TOTAL_TESTS: Результаты совпадают - OK"
    ((SUCCESSFUL_TESTS++))
  else
    log_console "Тест $TOTAL_TESTS: Результаты не совпадают - ERROR"
  fi

  rm -f "$outputFile"
}
