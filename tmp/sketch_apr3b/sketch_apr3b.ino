void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial1.write(0xFF);
  delay(100);

  int data = Serial1.read();
  Serial.println(data);
}
