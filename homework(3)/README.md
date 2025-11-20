# Домашняя работа №3:

Репозиторий содержит реализацию потокобезопасного buffered_channel.h.

Проект реализован для одной платформы: **Linux**. Реализация реализует RingBuffer потому что он быстрый blazing vector based.
1.  `#include <condition_variable>`
2.  `#include <mutex>`

Есть main.cpp - это просто бенчмарк

## Структура проекта

*   `../homework(3)/` — Проект.

## Сборка и запуск

### Linux

Для сборки... Инструкции по сборки запуску находятся в файле [../homework(3)/README.md](./README.md).

```bash
    g++ -O2 -g -o main main.cpp
    ./main
    ```

