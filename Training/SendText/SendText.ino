void setup() {
  UBRR0H = 0;
  UBRR0L = 0x67;

  UCSR0B |= 0x08;
  // UCSR0C |= 0x06; / Default configuration anyway 
}

void loop() {
  const char* s = "Hello world!";
  while (*s) {
    writeC(*s++);
  }
  writeC('\r');
  writeC('\n');
  for(volatile long i = 1000000; i > 0; i--);
}

void writeC(char c) {
  while (!(UCSR0A & (1 << UDRE0))) { }
  UDR0 = c;
}
