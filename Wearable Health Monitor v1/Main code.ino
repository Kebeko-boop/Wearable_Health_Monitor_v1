// Wearable  health sensor Montitor 1

const int pulsePin = A1; // potentiometer connected to A1
const int tempPin = A0; // potentiometer connected to A0
const int ledPin = 13; // LED connected to 13 

const int threshold = 600; // threshold value to detect heartbeat 
const int numberofSam = 10; // avarage number of samples

void setup() {
  Serial.begin(9600); // Start serial monitor
  pinMode(ledPin, OUTPUT); //set LED pin as output

}

void loop() {
  // Pulse Monitoring
  int sum = 0;

  // to read the pluse signals multiplle times
  for (int i =0; i < numberofSam; i++)
   {
    sum += analogRead(pulsePin);
    delay(5); // small delay between readings
  }

  int averagePulse = sum / numberofSam;// read analog input

  bool heartbeatDetected = false;

  if (averagePulse > threshold){
    digitalWrite(ledPin, HIGH); // turn Led on
    heartbeatDetected = true;
  }
  else{
    digitalWrite(ledPin, LOW);
  }

  // for temperature monitoring
  int tempreading = analogRead(tempPin);
  float voltage = (tempreading * 5.0) / 1023.0;
  float temperatureC = (voltage - 0.5) * 100.0;

  // Display
  Serial.println ("=================================");
  Serial.print("Pulse (avg): ");
  Serial.println(averagePulse);

  if (heartbeatDetected) {
    Serial.println("Heartbeat detected");
  }
  else {
    Serial.println("No heartbeat detected");
  }

  Serial.print("Body Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" C");

  // Fever alert
  if (temperatureC > 38.0){
    Serial.println("Warning possible fever!");
  }
   
  Serial.println("=================================\n");

  delay(1000); // to make it readable delays it small
}
