int tdsSensorValue = 0; // Variable to store the analog value
float TDS = 0.0;
int phSamples = 10;
float adc_resolution = 1023.0;

void setup() {
  Serial.begin(9600); // Initialize serial communication
  delay(1000);
  Serial.println("Setting up sensor routine");
}

void loop() {
  //tdsRoutine(A0);
  phRoutine(A1);
  //phRoutine(A2);
}

void tdsRoutine(int sensorPin){
  tdsSensorValue = analogRead(sensorPin); // Read the analog value
  TDS = tds(tdsSensorValue);
  Serial.print("TDS value for "+String(sensorPin)+": ");
  Serial.println(TDS);
  delay(100); // Wait for 100 milliseconds
}

void phRoutine(int sensorPin){
  int phMesures=0;
  for (int i = 0; i < phSamples; i++){
    phMesures += analogRead(sensorPin);
    delay(10);
  }

  float voltage = 5 / adc_resolution * (phMesures/phSamples);
  float phTwo = -5.70 * voltage + 21.32;
  Serial.print("PH value for "+String(sensorPin)+":  ");
  Serial.println(String(phTwo)+" or "+String(ph(voltage)));
  delay(3000);
}

float ph (float voltage) {
    return 7 + ((2.5 - voltage) / 0.18);
}

float tds (float sensorValue){
  return 2.15 * sensorValue + 22;
}
