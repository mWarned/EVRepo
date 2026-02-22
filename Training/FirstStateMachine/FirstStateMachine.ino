void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  DDRD = 0x31;
  PORTB = 0x00;
}

// the loop function runs over and over again forever
void loop() {
  static bool ledState = 0;
  static bool check = 1;
  while(PIND & 0x01){
    if(check){
      ledState = !ledState;
      if(ledState){
        PORTD &= ~0x20;
        PORTD |= 0x10;
        check = 0;
      } else {
        PORTD &= ~0x10;
        PORTD |= 0x20;
        check = 0;
      }
    }
    
    for(volatile long int i = 1000;i>0;i--);
  }

  check = 1;

  // for(volatile long int i = 1000;i>0;i--);
  // PORTB = 0x20;
  // for(volatile long int i = 1000;i>0;i--);
  // PORTB = 0x10;
  // i = 100000;
  // while(i--);
  // PORTB = 0x08;
  // i = 100000;
  // while(i--);
}
