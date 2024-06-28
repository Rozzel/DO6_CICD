#!/bin/bash

# shellcheck disable=SC1091
source ./tests_bash/modules/utilities.sh
source ./tests_bash/modules/files.sh
source ./tests_bash/modules/compare.sh
source ./tests_bash/modules/tests.sh

TOTAL_TESTS=0
SUCCESSFUL_TESTS=0
# shellcheck disable=SC2034
PROGRAM="./s21_grep"
# shellcheck disable=SC2034
RESULT_S21="temp_s21.txt"
# shellcheck disable=SC2034
RESULT_ORIG="temp_orig.txt"

create_files

test_start

console_log "ˁ˚ᴥ˚ˀ Checks: $TOTAL_TESTS, Errors: $((TOTAL_TESTS - SUCCESSFUL_TESTS))"

dell_files
