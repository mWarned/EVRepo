#define FOSC 16000000 //Clock speed
#define BAUD 9600 // Baud rate
#define MYUBRR FOSC/16/BAUD-1

void setup() {
  UBRR0H = 0;
  UBRR0L = 0x67;

  UCSR0B |= 0x08;
  DDRB  |= 0b00000001;

  ADMUX = 0b01000000;
  ADCSRA |= 0b10000111;

  USART_Init(MYUBRR);
}

void loop() {
  unsigned int serialValue = readA0();
  char buf[8];
  itoa(serialValue, buf, 10);

  unsigned char* s = (unsigned char*)buf;

  while (*s) {
    writeC(*s++);
  }
  writeC('\r');
  writeC('\n');
  for(volatile long i = 10000; i > 0; i--);
}

void USART_Init(unsigned int ubrr)
{
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;

  UCSR0B = 0b00011000;
  UCSR0C = 0b00001110;
}

void writeC(char c) {
  while (!(UCSR0A & 0b00100000));
  UDR0 = c;
}

unsigned int readA0(){
  ADCSRA |= 0b01000000;
  while (ADCSRA & 0b01000000);

  return ADC;
}
