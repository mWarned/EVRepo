float alpha=0.05;
float smoothed=0;

void setup() {
  // Analor read setup
  ADMUX = 0b01000000;
  ADCSRA |= 0b10000111;

  // I2C setup
  TWSR = 0x00;
  TWBR = 72;
  TWCR |= 0b00000100;

  // AS1115 setup
  Data_write(0x0F, 0x00);
  Data_write(0x0C, 0x01);
  Data_write(0x0B, 0x03);
  Data_write(0x09, 0xFF);
  Data_write(0x0A, 0x0F);
}

void loop() {
  unsigned int serialValue = readA0();
  smoothed = smoothed + alpha * (serialValue - smoothed); // Smooth the noise from reading
  displayNumber((int)smoothed);
  for(volatile long i = 10000; i > 0; i--);
}

unsigned int readA0(){
  ADCSRA |= 0b01000000;
  while (ADCSRA & 0b01000000);

  return ADC;
}

void I2C_write(unsigned char data) {
  TWDR = data;
  TWCR = 0b10000100;
  while (!(TWCR & 0b10000000));
}

void displayNumber(unsigned int value) {
  if(value >= 0 || value <= 1024) {
    Data_write(1, value % 10);         
    Data_write(2, (value/10) % 10);
    Data_write(3, (value/100) % 10);
    Data_write(4, (value/1000) % 10);
  }
}

void Data_write(unsigned char reg, unsigned char data) {
  // Start condition
  TWCR = 0b10100100;
  while (!(TWCR & 0b10000000));

  I2C_write(0x00);
  I2C_write(reg);
  I2C_write(data);

  // Stop condition
  TWCR = 0b10010100;
}
