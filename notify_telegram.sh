#!/bin/bash

TELEGRAM_TOKEN=""
TELEGRAM_CHAT_ID=""

STATUS=$1

if [ "$STATUS" == "success" ]; then
  MESSAGE="Все задачи процесса CI/CD успешно выполнены в проекте $CI_PROJECT_PATH, ветка $CI_COMMIT_BRANCH. Посмотреть: $CI_PROJECT_URL/-/pipelines/$CI_PIPELINE_ID"
elif [ "$STATUS" == "failure" ]; then
  MESSAGE="Внимание: Ошибка в выполнении задач в проекте $CI_PROJECT_PATH, ветка $CI_COMMIT_BRANCH. Посмотреть: $CI_PROJECT_URL/-/pipelines/$CI_PIPELINE_ID"
else
  MESSAGE="Статус не определен."
fi

curl -X POST https://api.telegram.org/bot$TELEGRAM_TOKEN/sendMessage \
-d chat_id=$TELEGRAM_CHAT_ID \
-d text="$MESSAGE"
