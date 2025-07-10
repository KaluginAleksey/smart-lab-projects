# Dust Gate Controller

**Dust Gate Controller** — это система управления вытяжкой и тремя шиберами, построенная на Arduino Nano. Система предназначена для работы в мастерской и позволяет автоматически или вручную управлять воздушными потоками с помощью реле, кнопок и инфракрасного датчика.

## 🚀 Возможности

* **Автоматический режим (AUTO)**: управление двумя основными шиберами на основе ИК-датчика.
* **Ручной режим (MANUAL)**: управление всеми тремя шиберами кнопками.
* **Нейтральный режим (NEUTRAL)**: отключение всех устройств.
* **Третий шибер** (для уборки пылесосом): включается только вручную, автоматически закрывается при смене режима.
* **Автоматическое включение/выключение вытяжки** при переключении режимов.
* Светодиодная индикация текущего режима и состояний устройств.

## 🔌 Подключения

| Назначение              | Название пина      | Пин Arduino |
| ----------------------- | ------------------ | ----------- |
| Режим AUTO              | `AUTO_PIN`         | D2          |
| Режим MANUAL            | `MANUAL_PIN`       | D3          |
| Кнопка Основной шибер   | `PRIMARY_BUTTON`   | A2          |
| Кнопка Доп. шибер       | `SECONDARY_BUTTON` | A3          |
| Кнопка Пылесосный шибер | `VACUUM_BUTTON`    | A4          |
| Инфракрасный датчик     | `SENSOR_PIN`       | A5          |
| Светодиод AUTO          | `AUTO_LED`         | D4          |
| Светодиод MANUAL        | `MANUAL_LED`       | D5          |
| Светодиод Вент ON       | `VENT_ON_LED`      | D6          |
| Светодиод Вент OFF      | `VENT_OFF_LED`     | D7          |
| Светодиод PRIMARY       | `PRIMARY_LED`      | D8          |
| Светодиод SECONDARY     | `SECONDARY_LED`    | D9          |
| Светодиод VACUUM        | `VACUUM_LED`       | D10         |
| Реле Вент ON            | `VENT_RELAY_ON`    | D11         |
| Реле Вент OFF           | `VENT_RELAY_OFF`   | D12         |
| Реле PRIMARY Open       | `PRIMARY_OPEN`     | D13         |
| Реле SECONDARY Open     | `SECONDARY_OPEN`   | A0          |
| Реле VACUUM Open        | `VACUUM_OPEN`      | A1          |

## 📂 Структура проекта

dust-gate-controller/

├── src/

│   └── dust\_gate\_controller.ino — основной скетч

├── docs/

│   └── wiring\_diagram.png — схема подключения (при наличии)

├── README.md

├── LICENSE

## ⚙️ Зависимости

* [OneButton](https://github.com/mathertel/OneButton) — библиотека для работы с кнопками

## 📜 Лицензия

Проект распространяется под лицензией MIT. См. файл [LICENSE](LICENSE) для подробностей.

MIT License

Copyright (c) 2025 Алексей

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the “Software”), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
