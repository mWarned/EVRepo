#include <avr/io.h>

static bool ledState = 1; // Which led is being powered

// Interrupt with button
// ISR(INT0_vect) {
//   if(ledState){
//     PORTD &= ~0x10;
//     PORTD |= 0x20;
//   } else {
//     PORTD &= ~0x20;
//     PORTD |= 0x10;
//   }

//   ledState = !ledState;
// }

// Interrup from timer
// ISR(TIMER1_COMPA_vect) {
//   if(ledState){
//     PORTD |= 0x10;
//   } else {
//     PORTD &= ~0x10;
//   }

//   ledState = !ledState;
// }

void setup() {
  // DDRD |= 0x30;    // Setup PD4/5 as output
  // DDRD |= 0x04;    // Setup PD2 as output(input)
  // EICRA |= 0x03;   // Setup INT0 to trigger on rising edge
  // EIMSK |= 0x01;   // Enable INT0 interrupts

  DDRB |= 0x04;

  // TCCR1A = 0x00;   // normal port operation
  // TCCR1B = 0x0D;   // Enable clk/1024 prescale
  // OCR1A  = 1953;   // 3907 ticks (0.25s)
  // TIMSK1 = 0x02;   // enable compare-A interrupt


  TCCR1A = 0x22;   // normal port operation / fast PWM
  TCCR1B = 0x1A;   // clk/8 prescaler + 

  ICR1 = 1999;     // 2000 ticks for clk/8 preskale for 1KHz
  OCR1B = 999;     // Duty cycle 50%

  // PORTD |= 0x10;   // Power the first led

  // sei();
}

void loop() {

}
