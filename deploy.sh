#!/bin/bash

USERNAME=$UI_USERNAME
HOST=$UI_HOST
SSH_PRIVATE_KEY=$UI_SSH_PRIVATE_KEY

mkdir -p ~/.ssh
chmod 700 ~/.ssh
eval "$(ssh-agent -s)"
echo "$SSH_PRIVATE_KEY" > id_rsa.base64
base64 -d < id_rsa.base64 > id_rsa

chmod 600 id_rsa
ssh-add id_rsa
ssh-keyscan "$HOST" >> ~/.ssh/known_hosts

DEST_PATH=/usr/local/bin

if [ ! -f src/cat/artifacts/s21_cat ]; then
  echo "Файл s21_cat не найден"
  exit 1
fi

if [ ! -f src/grep/artifacts/s21_grep ]; then
  echo "Файл s21_grep не найден"
  exit 1
fi

if ! scp src/cat/artifacts/s21_cat "$USERNAME@$HOST":/tmp/s21_cat; then
  echo "Ошибка копирования s21_cat"
  exit 1
fi

if ! scp src/grep/artifacts/s21_grep "$USERNAME@$HOST":/tmp/s21_grep; then
  echo "Ошибка копирования s21_grep"
  exit 1
fi

if ! ssh "$USERNAME@$HOST" 'mv /tmp/s21_cat '"$DEST_PATH"'/s21_cat && chmod +x '"$DEST_PATH"'/s21_cat'; then
  echo "Ошибка установки s21_cat"
  exit 1
fi

if ! ssh "$USERNAME@$HOST" 'mv /tmp/s21_grep '"$DEST_PATH"'/s21_grep && chmod +x '"$DEST_PATH"'/s21_grep'; then
  echo "Ошибка установки s21_grep"
  exit 1
fi
