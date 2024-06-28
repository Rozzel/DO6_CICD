#!/bin/bash

create_files() {
  mkdir ./tests_bash/temp/
  echo -e "Hello\nWorld\nHello Again" > ./tests_bash/temp/file1.txt
  echo -e "Testing\ngrep\nTesting Again" > ./tests_bash/temp/file2.txt
  echo -e "Again" > ./tests_bash/temp/file3.txt
}

dell_files() {
  rm -rf tests_bash/temp/
}
