/**
 * Senseo coffee maker by Equisense.
 *
 * By Kamel Tighidet <kamel@equisense.fr>
 * and Yoan Tournade <yoan@ytotech.com>
 */

// We set the push delay
// (delay between the high and low signal to simulate a push button action).
int PUSH_BTN_DELAY = 500;
// Wired to the Senseo Power push button. 
int PIN_POWER = 2;
// Wired to the Senseo Short Coffee push button.
// If we put that to high it make a short coffee: obvious man being obvious here.
int PIN_MAKE_SHORT = 3;
// Wired to the Senseo Long Coffee push button.
int PIN_MAKE_LONG = 4;
// Wired to the RPi, so it can order a short coffee.
int PIN_ORDER_SHORT = 5;
// Wired to the RPi, so it can order a short coffee.
int PIN_ORDER_LONG = 6;
// Wired to the moisture sensor (to sense the water level)
int PIN_MOISTURE_SENSOR = 7;
// Wired the the relay (to activate the water pump)
int PIN_WATER_PUMP_RELAY = 8;
int is_short_ordered;
int is_long_ordered;
int is_tank_not_full;

void setup() {
  Serial.begin(9600);
  // We init the in/out pins
  pinMode(PIN_POWER, OUTPUT);
  digitalWrite(PIN_POWER, HIGH);
  pinMode(PIN_MAKE_SHORT, OUTPUT);
  digitalWrite(PIN_MAKE_SHORT, HIGH);
  pinMode(PIN_MAKE_LONG, OUTPUT);
  digitalWrite(PIN_MAKE_LONG, HIGH);
  pinMode(PIN_ORDER_SHORT, INPUT);
  pinMode(PIN_ORDER_LONG, INPUT);
  pinMode(PIN_WATER_PUMP_RELAY, OUTPUT);
  pinMode(PIN_MOISTURE_SENSOR, INPUT);
}

void loop() {
  is_tank_not_full = digitalRead(PIN_MOISTURE_SENSOR);
  if(is_tank_not_full){
    Serial.println("Tank not full. Activating water pump");
  }
  digitalWrite(PIN_WATER_PUMP_RELAY, is_tank_not_full); 
  is_short_ordered = digitalRead(PIN_ORDER_SHORT);
  is_long_ordered = digitalRead(PIN_ORDER_LONG);
  if((is_short_ordered || is_long_ordered) && !is_tank_not_full) {
    Serial.println("Powering the Senseo machine");
    digitalWrite(PIN_POWER, LOW); 
    delay(PUSH_BTN_DELAY);
    digitalWrite(PIN_POWER, HIGH);
    delay(10000);
    if(is_short_ordered) {
      Serial.println("Start a short coffee");
      digitalWrite(PIN_MAKE_SHORT, LOW);
      delay(PUSH_BTN_DELAY);
      digitalWrite(PIN_MAKE_SHORT, HIGH);
    } else {
      Serial.println("Start a long coffeee");
      digitalWrite(PIN_MAKE_LONG, LOW);
      delay(PUSH_BTN_DELAY);
      digitalWrite(PIN_MAKE_LONG, HIGH);
    }
    Serial.println("Wait for the coffee to be ready");
    delay(30000);
  }
}

