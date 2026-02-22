#define FOSC 16000000 //Clock speed
#define BAUD 9600 // Baud rate
#define MYUBRR FOSC/16/BAUD-1

void setup() {
  UBRR0H = 0;
  UBRR0L = 0x67;

  UCSR0B |= 0x08;
  DDRB  |= 0b00000001;

  USART_Init(MYUBRR);
}

void loop() {
  unsigned char* c = USART_Receive();

  if (c != 0) {
    PORTB |= 0b00000001;
    for(volatile long i = 100000; i > 0; i--);
    PORTB &= 0b11111110;
  }
}

unsigned char USART_Receive(void)
{
  while (!(UCSR0A & 0b10000000));
  return UDR0;
}

void USART_Flush(void)
{
  unsigned char dummy;
  while (UCSR0A & 0b10000000) dummy = UDR0;
}

void writeC(char c) {
  while (!(UCSR0A & (1 << UDRE0))) { }
  UDR0 = c;
}

void USART_Init(unsigned int ubrr)
{
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;

  UCSR0B = 0b00011000;
  UCSR0C = 0b00001110;
}
