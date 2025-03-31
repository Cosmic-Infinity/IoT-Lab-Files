#include <SPI.h>

const int MPU_CS = 10;  // Chip Select Pin
int16_t gx, gy, gz;

void setup() {
  Serial.begin(115200); // Set baud rate to match MultiWii Serial Protocol
  pinMode(MPU_CS, OUTPUT);
  digitalWrite(MPU_CS, HIGH);  // Disable chip select

  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  SPI.setDataMode(SPI_MODE3);
  SPI.setBitOrder(MSBFIRST);

  initMPU();
}

void loop() {
  gx = readMPU(0x43) << 8 | readMPU(0x44);
  gy = readMPU(0x45) << 8 | readMPU(0x46);
  gz = readMPU(0x47) << 8 | readMPU(0x48);

  // Format data according to MultiWii Serial Protocol
  Serial.write(0x20); // Start byte
  Serial.write(0x01); // Message ID (for example)
  Serial.write((byte*)&gx, sizeof(gx));
  Serial.write((byte*)&gy, sizeof(gy));
  Serial.write((byte*)&gz, sizeof(gz));
  Serial.write(0x00); // Checksum or end byte as needed

  delay(10);
}

void initMPU() {
  writeMPU(0x6B, 0x00);  // Wake up the MPU-6050
}

void writeMPU(byte reg, byte data) {
  digitalWrite(MPU_CS, LOW);
  SPI.transfer(reg);
  SPI.transfer(data);
  digitalWrite(MPU_CS, HIGH);
}

byte readMPU(byte reg) {
  digitalWrite(MPU_CS, LOW);
  SPI.transfer(reg | 0x80);  // Set the MSB to 1 to indicate a read operation
  byte data = SPI.transfer(0x00);
  digitalWrite(MPU_CS, HIGH);
  return data;
}
