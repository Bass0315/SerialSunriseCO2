#include "User_PCF8574.h"
#include "User_SerialSunriseCO2.h"

// User_SerialSunriseCO2
extern int readPeriodMs;
extern uint16_t state[];

// PCF8574
PCF8574 PCF_8574(0x70);

/**
   @brief  This function runs once at the start.

   @retval None
*/
void setup() {


  /* Wait for sensor start-up and stabilization */
  delay(STABILIZATION_MS);

  /* Begin serial communication */
  Serial.begin(115200);
  while (!Serial);


  PCF_8574.begin();
  delay(500);
  
  SunriseSerial.begin(9600);
  
  for (uint8_t i = 0; i < 8; i++)
  {
    doLow(i);
  }

  Serial.println("Initialization complete \n");
  for (uint8_t iPin = 0; iPin < 8; iPin++)
  {
    //doHigh(iPin);
    Serial.println(" CH: " + String(iPin));
    /* Read the sensor's Device ID */
    if (read_sensor_id(SUNRISE_ADDR))
    {
      Serial.println(" Device ID OK ");
    }

    /* Read the sensor's configs */
    if (read_sensor_config(SUNRISE_ADDR))
    {
      Serial.println(" Sensor's Measurement Configs OK");
    }

    /* Change measurement mode if continuous */
    change_measurement_mode(SUNRISE_ADDR);

    /* Initial measurement */
    Serial.println("Inital Measurement");
    init_measurement(SUNRISE_ADDR);

    delay(readPeriodMs);
    //doLow(iPin);
  }
}
/**
   @brief  The main function loop. Reads the sensor's current
           CO2 value and error status and prints them to the
           Serial Monitor.

   @retval None
*/
void loop() {
  static int pin_value = HIGH;
  static unsigned long last_abc_stamp = 0;

  /* When an hour has passed, increase ABC Time */
  if (3600000 < (unsigned long)((long)millis() - (long)last_abc_stamp)) {
    /* Use ABC time stored in the sensor state */
    state[0] = state[0] + 1;
    last_abc_stamp = millis();
    Serial.println("ABC time incremented.");
  }

  /* Read measurements */
  read_sensor_measurements(SUNRISE_ADDR);

  /* Delay between readings */
  Serial.println("\nWaiting...\n");
  delay(readPeriodMs);

  pin_value  = ((pin_value == HIGH) ? LOW : HIGH);
}
