#!/bin/bash

# Test Part 2.
# Поддержка следующих флагов: `-e`, `-i`, `-v`, `-c`, `-l`, `-n`

part2_1() {
  compare_results "Hello ./tests_bash/temp/file1.txt"
}

part2_2() {
  compare_results "Hello ./tests_bash/temp/file1.txt ./tests_bash/temp/file2.txt"
}

part2_3() {
  compare_results "-i HELLO ./tests_bash/temp/file1.txt"
}

part2_4() {
  compare_results "-i HELLO ./tests_bash/temp/file1.txt ./tests_bash/temp/file2.txt"
}

part2_5() {
  compare_results "-v Hello ./tests_bash/temp/file1.txt"
}

part2_6() {
  compare_results "-l Hello ./tests_bash/temp/file1.txt ./tests_bash/temp/file2.txt"
}

part2_7() {
  compare_results "-c Hello ./tests_bash/temp/file1.txt"
}

part2_8() {
  compare_results "-n Hello ./tests_bash/temp/file1.txt"
}

part2_9() {
  compare_results "-n Hello ./tests_bash/temp/file1.txt ./tests_bash/temp/file2.txt"
}

part2_10() {
  compare_results "-e Hello -e Again ./tests_bash/temp/file1.txt"
}

# Test Part 3.
# Поддержка всех флагов, включая: `-h`, `-s`, `-f`, `-o`

part3_1() {
  compare_results "-h Hello ./tests_bash/temp/file1.txt ./tests_bash/temp/file2.txt"
}

part3_2() {
  compare_results "-s Hello ./tests_bash/temp/file_no.txt"
}

part3_3() {
  compare_results "-f ./tests_bash/temp/file3.txt ./tests_bash/temp/file1.txt"
}

part3_4() {
  compare_results "-o Hello ./tests_bash/temp/file1.txt"
}

# Test Part 4.
# Поддержка всех флагов, включая их парные комбинации.

part4_1() {
  compare_results "-iv Hello ./tests_bash/temp/file1.txt"
}

part4_2() {
  compare_results "-in Hello ./tests_bash/temp/file1.txt"
}

part4_3() {
  compare_results "-ce Hello ./tests_bash/temp/file1.txt"
}

part4_4() {
  compare_results "-c -e Hello ./tests_bash/temp/file1.txt"
}

part4_5() {
  compare_results "-nivh Hello ./tests_bash/temp/file1.txt"
}

part4_6() {
  compare_results "-ie Hello ./tests_bash/temp/file1.txt"
}

part4_7() {
  compare_results "-ne Hello ./tests_bash/temp/file1.txt"
}

part4_8() {
  compare_results "-o -e Hello ./tests_bash/temp/file1.txt"
}

part4_9() {
  compare_results "-cs Hello ./tests_bash/temp/file1.txt"
}

part4_10() {
  compare_results "-vn Hello ./tests_bash/temp/file1.txt"
}

part4_11() {
  compare_results "-io Hello ./tests_bash/temp/file1.txt"
}

part4_12() {
  compare_results "-sl Hello ./tests_bash/temp/file1.txt ./tests_bash/temp/file2.txt"
}

part4_13() {
  compare_results "-oh Hello ./tests_bash/temp/file1.txt"
}

part4_14() {
  compare_results "-ho Hello ./tests_bash/temp/file1.txt"
}

part4_15() {
  compare_results "-hf ./tests_bash/temp/file3.txt ./tests_bash/temp/file1.txt"
}

part4_16() {
  compare_results "-no Hello ./tests_bash/temp/file1.txt"
}

part4_17() {
  compare_results "-nf Hello ./tests_bash/temp/file1.txt"
}

part4_18() {
  compare_results "-nh Hello ./tests_bash/temp/file1.txt"
}

part4_19() {
  compare_results "-lo Hello ./tests_bash/temp/file1.txt ./tests_bash/temp/file2.txt"
}

part4_20() {
  compare_results "-lf ./tests_bash/temp/file3.txt ./tests_bash/temp/file1.txt"
}

part4_21() {
  compare_results "-lh Hello ./tests_bash/temp/file1.txt"
}

part4_22() {
  compare_results "-ln Hello ./tests_bash/temp/file1.txt"
}

part4_23() {
  compare_results "-co Hello ./tests_bash/temp/file1.txt"
}

part4_24() {
  compare_results "-vf ./tests_bash/temp/file3.txt ./tests_bash/temp/file1.txt"
}

part4_25() {
  compare_results "-ch Hello ./tests_bash/temp/file1.txt ./tests_bash/temp/file2.txt"
}

part4_26() {
  compare_results "-ic Hello ./tests_bash/temp/file1.txt"
}

part4_27() {
  compare_results "-il Hello ./tests_bash/temp/file1.txt"
}

part4_28() {
  compare_results "-ih Hello ./tests_bash/temp/file1.txt"
}

part4_29() {
  compare_results "-if ./tests_bash/temp/file3.txt ./tests_bash/temp/file1.txt"
}

part4_30() {
  compare_results "-vc Hello ./tests_bash/temp/file1.txt"
}

part4_31() {
  compare_results "-vl Hello ./tests_bash/temp/file1.txt"
}

part4_32() {
  compare_results "-vh Hello ./tests_bash/temp/file1.txt"
}

part4_33() {
  compare_results "-cn Hello ./tests_bash/temp/file1.txt"
}

test_start() {
  part2_1
  part2_2
  part2_3
  part2_4
  part2_5
  part2_6
  part2_7
  part2_8
  part2_9
  part2_10

  part3_1
  part3_2
  part3_3
  part3_4

  part4_1
  part4_2
  part4_3
  part4_4
  part4_5
  part4_6
  part4_7
  part4_8
  part4_9
  part4_10
  part4_11
  part4_12
  part4_13
  part4_14
  part4_15
  part4_16
  part4_17
  part4_18
  part4_19
  part4_20
  part4_21
  part4_22
  part4_23
  part4_24
  part4_25
  part4_26
  part4_27
  part4_28
  part4_29
  part4_30
  part4_31
  part4_32
  part4_33
}
