# Part 6. Дополнительно. Уведомления

## Создание бота в Telegram

### BotFather в Telegram

- `@BotFather` начните чат.
- Отправьте команду `/newbot` и следуйте инструкциям для создания бота.
- После создания бота, BotFather предоставит токен доступа к API.

```txt
/newbot
[lothostr] DO6 CI/CD
lothostr_do6cicd_bot

Use this token to access the HTTP API:
```


## Добавить бота в группу

- Добавить бота в группу
- Сделать бота администратором
- Отправьть сообщение в группу

```txt
/start
```

- Получить обновление через API Telegram

```txt
https://api.telegram.org/bot<ТОКЕН>/getUpdates
curl https://api.telegram.org

"chat":{"id":-000,"title":"DO6_CICD","type":"supergroup"},"date":1709021585,"text":"/start","entities":[{"offset":0,"length":6,"type":"bot_command"}]
```
> `-000` id чата.

- `$TELEGRAM_TOKEN`: переменная для хранения токена Telegram бота. Токен используется для аутентификации запросов к Telegram API для отправки сообщений.

- `$TELEGRAM_CHAT_ID`: Эта переменная содержит идентификатор чата в Telegram, куда будут отправляться сообщения. Идентификатор определяет, куда именно бот должен отправить сообщение.

- [DOCS: Predefined CI/CD variables reference](https://docs.gitlab.com/ee/ci/variables/predefined_variables.html)

## Тест работы бота

```zsh
curl -X POST https://api.telegram.org/---/sendMessage \
-d chat_id=-000 \
-d text="Пайплайн your_pipeline_id в проекте your_project_name на ветке your_commit_ref_name завершился с состоянием: your_pipeline_status."
```
