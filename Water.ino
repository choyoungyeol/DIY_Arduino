#define waterPin A1

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int water_value = analogRead(waterPin);
  int water_content = map(water_value, 984, 298, 0, 100);
  Serial.print("Water_value = ");
  Serial.println(water_value);
  Serial.print("Water content = ");
  Serial.println(water_content);
  delay(5000);
}
