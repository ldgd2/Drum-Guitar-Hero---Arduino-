#include "UnoJoy.h"

#define PIEZO_THRESHOLD 50      //  Umbral de sensibilidad del piezoeléctrico, ajusta según sea necesario - Piezo sensitivity threshold, adjust as necessary
#define BUTTON_THRESHOLD 800    //  Umbral para los botones pulsadores, ajusta según sea necesario - Threshold for push buttons, adjust as needed 

// Definición de los pines para los botones y los sensores
#define TRIANGLE_PIEZO_PIN A0    // Pad Rojo  - Red Pad
#define CIRCLE_PIEZO_PIN A1      // Pad Amarillo - Yellow Pad
#define SQUARE_PIEZO_PIN A2      // Pad Azul - Blue Pad
#define CROSS_PIEZO_PIN A3       // Pad Naranja - Orange Pad
#define L1_PIEZO_PIN A4          // Pad Verde - Green Pad

#define DPAD_UP_BUTTON_PIN 2         // Arriba - Up
#define DPAD_DOWN_BUTTON_PIN 3     // Abajo - Down
#define START_BUTTON_PIN 4        // start
#define SELECT_BUTTON_PIN 5      // Select
#define L3_BUTTON_PIN 6          // Pedal

void setup() {
  setupPins();
  setupUnoJoy();
}

void loop() {
  dataForController_t controllerData = getControllerData();
  setControllerData(controllerData);
}

void setupPins(void) {
  // Configuración de los pines digitales para los botones pulsadores como entradas pull-up 
  // Configuring the digital pins for the push buttons as pull-up inputs
  pinMode(DPAD_UP_BUTTON_PIN, INPUT_PULLUP);
  pinMode(DPAD_DOWN_BUTTON_PIN, INPUT_PULLUP);
  pinMode(START_BUTTON_PIN, INPUT_PULLUP);
  pinMode(SELECT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(L3_BUTTON_PIN, INPUT_PULLUP);
}

dataForController_t getControllerData(void) {
  dataForController_t controllerData = getBlankDataForController();

  // Leer los valores de los pines analógicos para los sensores piezoeléctricos
  // Read the values of the analog pins for the piezoelectric sensors
  int trianglePiezoValue = analogRead(TRIANGLE_PIEZO_PIN);
  int circlePiezoValue = analogRead(CIRCLE_PIEZO_PIN);
  int squarePiezoValue = analogRead(SQUARE_PIEZO_PIN);
  int crossPiezoValue = analogRead(CROSS_PIEZO_PIN);
  int l1PiezoValue = analogRead(L1_PIEZO_PIN);

  // Verificar si se supera el umbral y establecer el estado de los botones correspondientes
  // Check if the threshold is exceeded and set the status of the corresponding buttons
  if (trianglePiezoValue >= PIEZO_THRESHOLD) {
    controllerData.triangleOn = true;
  }
  if (circlePiezoValue >= PIEZO_THRESHOLD) {
    controllerData.circleOn = true;
  }
  if (squarePiezoValue >= PIEZO_THRESHOLD) {
    controllerData.squareOn = true;
  }
  if (crossPiezoValue >= PIEZO_THRESHOLD) {
    controllerData.crossOn = true;
  }
  if (l1PiezoValue >= PIEZO_THRESHOLD) {
    controllerData.l1On = true;
  }

  // Leer el estado de los botones pulsadores y establecer el estado correspondiente
  // Read the status of push buttons and set the corresponding status
  if (digitalRead(DPAD_UP_BUTTON_PIN) == LOW) {
    controllerData.dpadUpOn = true;
  }
  if (digitalRead(DPAD_DOWN_BUTTON_PIN) == LOW) {
    controllerData.dpadDownOn = true;
  }
  if (digitalRead(START_BUTTON_PIN) == LOW) {
    controllerData.startOn = true;
  }
  if (digitalRead(SELECT_BUTTON_PIN) == LOW) {
    controllerData.selectOn = true;
  }
  if (digitalRead(L3_BUTTON_PIN) == LOW) {
    controllerData.l3On = true;
  }

  return controllerData;
}
