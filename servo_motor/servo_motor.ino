#define pm 6
void setup() {
  pinMode(pm, OUTPUT);
}

void loop() {
  analogWrite(pm, 250);

}
