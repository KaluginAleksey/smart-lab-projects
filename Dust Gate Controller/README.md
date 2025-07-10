# Dust Gate Controller

**Dust Gate Controller** — это система управления вытяжкой и тремя шиберами, построенная на Arduino Nano. Система предназначена для работы в мастерской и позволяет автоматически или вручную управлять воздушными потоками с помощью реле, кнопок и инфракрасного датчика.

## 🚀 Возможности

- **Автоматический режим (AUTO)**: управление двумя основными шиберами на основе ИК-датчика.
- **Ручной режим (MANUAL)**: управление всеми тремя шиберами кнопками.
- **Нейтральный режим (NEUTRAL)**: отключение всех устройств.
- **Третий шибер** (для уборки пылесосом): включается только вручную, автоматически закрывается при смене режима.
- **Автоматическое включение/выключение вытяжки** при переключении режимов.
- Светодиодная индикация текущего режима и состояний устройств.

## 🔌 Подключения

| Назначение                | Пин Arduino     |
| ------------------------- | --------------- |
| AUTO переключатель        | 2               |
| MANUAL переключатель      | 3               |
| Кнопка основного шибера   | 15 (A1)         |
| Кнопка вторичного шибера  | 16 (A2)         |
| Кнопка пылесосного шибера | 14 (A0)         |
| Инфракрасный датчик       | A3              |
| Светодиоды режима         | 4, 5            |
| Светодиоды вытяжки        | 6, 7            |
| Светодиоды шиберов        | 8, 9, 17 (A4)   |
| Реле вытяжки              | 10, 11          |
| Реле шиберов              | 12, 13, 18 (A5) |

## 📂 Структура проекта

dust-gate-controller/

├── src/

│ └── dust_gate_controller.ino # Основной скетч

├── docs/

│ └── wiring_diagram.png # Схема подключения (при наличии)

├── README.md

├── LICENSE

## ⚙️ Зависимости

- [OneButton](https://github.com/mathertel/OneButton) — библиотека для работы с кнопками

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
