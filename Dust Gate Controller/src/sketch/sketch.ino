/*
  Project:     Dust Gate Controller (управление вытяжкой и шиберами)
  Version:     1.1
  Date:        2025-07-09
  Author:      Калугин Алексей (инженер-технолог)

  Description:
    - Управление тремя шиберами (основной, дополнительный, пылесосный).
    - Работа в трёх режимах: AUTO, MANUAL, NEUTRAL.
    - В режиме AUTO управление шиберами по инфракрасному датчику.
    - В режиме MANUAL — ручное управление кнопками.
    - Вытяжка включается автоматически при входе в режим AUTO или MANUAL.
    - Пылесосный шибер активен только в MANUAL и закрывается при выходе из него.
    - Светодиодная индикация состояний реле, режимов и шиберов.

  Hardware:
    - Arduino Nano
    - Реле x5
    - Светодиоды x6
    - Кнопки x3 (основной, дополнительный, пылесосный)
    - Тумблер на 3 положения (AUTO / NEUTRAL / MANUAL)
    - Инфракрасный NPN-датчик
    - Механизм шиберов с управлением от реле

  Notes:
    - LOW = активное состояние реле
    - Все реле и светодиоды управляются по логике активного уровня LOW

  Wiring:
    - AUTO_PIN        - пин тумблера AUTO
    - MANUAL_PIN      - пин тумблера MANUAL
    - SENSOR_PIN      - инфракрасный датчик
    - PRIMARY_BUTTON  - кнопка основного шибера
    - SECONDARY_BUTTON- кнопка дополнительного шибера
    - VAC_BUTTON      - кнопка пылесосного шибера
    - VENT_RELAY_ON/OFF - реле вытяжки
    - PRIMARY/SECONDARY/VACUUM_OPEN - управление шиберами
    - VENT_ON/OFF, PRIMARY, SECONDARY, VACUUM - светодиодная индикация
*/

#include <OneButton.h>

// Пины тумблера переключения режимов
// Автоматический режим позволяет управлять шиберами при помощи отслеживания головы станка
#define AUTO_PIN 2
#define MANUAL_PIN 3

// Кнопки
#define PRIMARY_BUTTON_PIN A2
#define SECONDARY_BUTTON_PIN A3
#define VACUUM_BUTTON_PIN A4

OneButton primaryButton(PRIMARY_BUTTON_PIN, true);
OneButton secondaryButton(SECONDARY_BUTTON_PIN, true);
OneButton vacuumButton(VACUUM_BUTTON_PIN, true);

//Инфракрасный датчик
#define SENSOR_PIN A5

// Светодиоды
#define AUTO_LED 4
#define MANUAL_LED 5
#define VENT_ON_LED 6
#define VENT_OFF_LED 7
#define PRIMARY_LED 8
#define SECONDARY_LED 9
#define VACUUM_LED 10

// Реле
#define VENT_RELAY_ON 11
#define VENT_RELAY_OFF 12
#define PRIMARY_OPEN 13
#define SECONDARY_OPEN A0
#define VACUUM_OPEN A1

// Состояние шиберов
bool primaryState = false;
bool secondaryState = false;
bool vacuumState = false;

enum Mode {
  NEUTRAL,
  AUTO,
  MANUAL
};

Mode currentMode = NEUTRAL;
Mode previousMode = NEUTRAL;

void setup() {
  Serial.begin(9600);

  // Настройка пинов тумблера
  pinMode(AUTO_PIN, INPUT_PULLUP);
  pinMode(MANUAL_PIN, INPUT_PULLUP);

  //привязка кнопок
  primaryButton.attachClick(toggleRelayPrimary);
  secondaryButton.attachClick(toggleRelaySecondary);
  vacuumButton.attachClick(toggleRelayVacuum);

  // Светодиоды
  pinMode(AUTO_LED, OUTPUT);
  pinMode(MANUAL_LED, OUTPUT);
  pinMode(VENT_ON_LED, OUTPUT);
  pinMode(VENT_OFF_LED, OUTPUT);
  pinMode(PRIMARY_LED, OUTPUT);
  pinMode(SECONDARY_LED, OUTPUT);
  pinMode(VACUUM_LED, OUTPUT);

  // Реле
  pinMode(VENT_RELAY_ON, OUTPUT);
  pinMode(VENT_RELAY_OFF, OUTPUT);
  pinMode(PRIMARY_OPEN, OUTPUT);
  pinMode(SECONDARY_OPEN, OUTPUT);
  pinMode(VACUUM_OPEN, OUTPUT);

    //Сброс в начальное состояние
  digitalWrite(VENT_RELAY_ON, HIGH);
  digitalWrite(VENT_RELAY_OFF, HIGH);
  digitalWrite(PRIMARY_OPEN, HIGH);
  digitalWrite(SECONDARY_OPEN, HIGH);
  digitalWrite(VACUUM_OPEN, HIGH);

  //Светодиоды начальное состояние
  digitalWrite(VENT_ON_LED, LOW);
  digitalWrite(VENT_OFF_LED, LOW);
  digitalWrite(PRIMARY_LED, LOW);
  digitalWrite(SECONDARY_LED, LOW);
  digitalWrite(VACUUM_LED, LOW);

  //NPN инфракрасный датчик
  pinMode(SENSOR_PIN, INPUT_PULLUP);


}

void loop() {
  updateMode(); // Определяем режим

  if (currentMode == MANUAL) {
    primaryButton.tick();
    secondaryButton.tick();
    vacuumButton.tick();
  } else if (currentMode == AUTO) {
    bool beamBlocked = digitalRead(SENSOR_PIN) == LOW;

    if (beamBlocked) {
      setPrimary(false);
      setSecondary(true);
    } else {
      setPrimary(true);
      setSecondary(false);
    }
  } else if (currentMode == NEUTRAL) {
  setPrimary(false);
  setSecondary(false);
  setVacuum(false);
  turnVentilationOff();
}
}

void updateMode() {
  bool autoActive = digitalRead(AUTO_PIN) == LOW;
  bool manualActive = digitalRead(MANUAL_PIN) == LOW;

  previousMode = currentMode;

  if (autoActive) {
    currentMode = AUTO;
  } else if (manualActive) {
    currentMode = MANUAL;
  } else {
    currentMode = NEUTRAL;
  }

  // Индикация режима
  digitalWrite(AUTO_LED, currentMode == AUTO ? HIGH : LOW);
  digitalWrite(MANUAL_LED, currentMode == MANUAL ? HIGH : LOW);

  
  // Автовключение вытяжки при входе в AUTO
  if ((currentMode == AUTO || currentMode == MANUAL) &&
      (previousMode != currentMode)) {
    turnVentilationOn();
  }
    if (currentMode == NEUTRAL && previousMode != NEUTRAL) {
    turnVentilationOff();
  }
  if (previousMode == MANUAL && currentMode != MANUAL && vacuumState) {
    setVacuum(false);
  }

}

void turnVentilationOn() {
  digitalWrite(VENT_RELAY_ON, LOW);
  digitalWrite(VENT_RELAY_OFF, HIGH);
  digitalWrite(VENT_ON_LED, HIGH);
  digitalWrite(VENT_OFF_LED, LOW);
}

void turnVentilationOff() {
  digitalWrite(VENT_RELAY_ON, HIGH);
  digitalWrite(VENT_RELAY_OFF, LOW);
  digitalWrite(VENT_ON_LED, LOW);
  digitalWrite(VENT_OFF_LED, HIGH);
}



void toggleRelayPrimary() {
  primaryState = !primaryState;
  setPrimary(primaryState);  
}

void toggleRelaySecondary() {
  secondaryState = !secondaryState;
  setSecondary(secondaryState);
}

void toggleRelayVacuum() {
  if (currentMode == MANUAL) {
    vacuumState = !vacuumState;
    setVacuum(vacuumState);
  }
}

void setPrimary(bool open) {
  digitalWrite(PRIMARY_OPEN, open ? LOW : HIGH);
  digitalWrite(PRIMARY_LED, open ? HIGH : LOW);
  primaryState = open;
}

void setSecondary(bool open) {
  digitalWrite(SECONDARY_OPEN, open ? LOW : HIGH);
  digitalWrite(SECONDARY_LED, open ? HIGH : LOW);
  secondaryState = open;
}

void setVacuum(bool open) {
  digitalWrite(VACUUM_OPEN, open ? LOW : HIGH);
  digitalWrite(VACUUM_LED, open ? HIGH : LOW);
  vacuumState = open;
}
