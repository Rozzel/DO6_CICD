#!/bin/bash

compare_results() {
  local data="$1"

  console_log "$(tput setaf 5)---$(tput sgr0)"

  console_log "$(tput setaf 4)$PROGRAM$(tput sgr0) $data"
  # shellcheck disable=SC2086
  $PROGRAM $data > "$RESULT_S21"
  # shellcheck disable=SC2086
  $PROGRAM $data

  console_log "$(tput setaf 4)      grep$(tput sgr0) $data"
  # shellcheck disable=SC2086
  grep $data > "$RESULT_ORIG"
  # shellcheck disable=SC2086
  grep $data

  ((TOTAL_TESTS++))

  if diff "$RESULT_S21" "$RESULT_ORIG" > /dev/null; then
    console_log "$(tput setaf 3)Тест $TOTAL_TESTS:$(tput sgr0) Результаты совпадают - $(tput setaf 2)OK$(tput sgr0)"
    ((SUCCESSFUL_TESTS++))
  else
    console_log "$(tput setaf 3)Тест $TOTAL_TESTS:$(tput sgr0) Результаты не совпадают - $(tput setaf 1)ERROR$(tput sgr0)"
  fi

  console_log "$(tput setaf 5)---$(tput sgr0)\n"

  rm -f "$RESULT_S21" "$RESULT_ORIG"
}
