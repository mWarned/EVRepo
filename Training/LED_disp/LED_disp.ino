#define FOSC 16000000 //Clock speed
#define BAUD 9600 // Baud rate
#define MYUBRR FOSC/16/BAUD-1

int a = 11;
int b = 10;
int c = 9;
int d = 8;
int e = 7;
int f = 6;
int g = 5;

void display1(void) {
  clearDisplay();
  PORTB |= 0b00001001;
  PORTD |= 0b11100000;
}

void display2(void) {
  clearDisplay();
  PORTB |= 0b00000010;
  PORTD |= 0b01000000;
}

void display3(void) {
  clearDisplay();
  PORTB |= 0b00000000;
  PORTD |= 0b11000000;
}

void display4(void) {
  clearDisplay();
  PORTB |= 0b00001001;
  PORTD |= 0b10000000;
}

void display5(void) {
  clearDisplay();
  PORTB |= 0b00000100;
  PORTD |= 0b10000000;
}

void display6(void) {
  clearDisplay();
  PORTB |= 0b00000100;
  PORTD |= 0;
}

void display7(void) {
  clearDisplay();
  PORTB |= 0b00000001;
  PORTD |= 0b11100000;
}

void display8(void) {
  clearDisplay();
  PORTB |= 0;
  PORTD |= 0;
}

void display9(void) {
  clearDisplay();
  PORTB |= 0;
  PORTD |= 0b10000000;
}
void display0(void) {
  clearDisplay();
  PORTB |= 0;
  PORTD |= 0b00100000;
}

void clearDisplay(void) {
  PORTB &= 0b11110000;
  PORTD &= 0b00011111;
  for(volatile long i = 10000; i > 0; i--);
}

void setup() {
  UBRR0H = 0;
  UBRR0L = 0x67;

  UCSR0B |= 0x08;
  DDRB |= 0b00001111;
  DDRD |= 0b11100000;

  USART_Init(MYUBRR);
}


void loop() {
  unsigned char c = USART_Receive();
  while (c == '\n' || c == '\r') {
    c = USART_Receive();
  }
  int digit = c - '0';

  switch (digit) {
    case 0: display0(); break;
    case 1: display1(); break;
    case 2: display2(); break;
    case 3: display3(); break;
    case 4: display4(); break;
    case 5: display5(); break;
    case 6: display6(); break;
    case 7: display7(); break;
    case 8: display8(); break;
    case 9: display9(); break;
  }
}

unsigned char USART_Receive(void)
{
  while (!(UCSR0A & 0b10000000));
  return UDR0;
}

void USART_Init(unsigned int ubrr)
{
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;

  UCSR0B = 0b00011000;
  UCSR0C = 0b00001110;
}
