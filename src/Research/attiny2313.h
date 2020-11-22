//help
//0000 = 0
//0001 = 1
//0010 = 2
//0011 = 3
//0100 = 4
//0101 = 5
//0110 = 6
//0111 = 7
//1000 = 8
//1001 = 9
//1010 = A
//1011 = B
//1100 = C
//1101 = D
//1110 = E
//1111 = F
// x = 0000 0001; x &= ~(1 << 0); //x = 0000 0000
// x2 = 0000 0000; x2 |= (1 << 0); //x2 = 0000 0001
// (x2 & 0x00) returns false;
// (x2 & 0000 0001) returns true;
// (x2 & (1 << 0)) returns true;

//Timer
#define CLOCK_MODE_CTC (TCCR0A |= (1 << WGM01)) // Clock mode: Clear Timer on Compare Match (CTC) mode.
#define CLOCK_MODE_FREQ_PRESCALER_1024 TCCR0B = ((1 << CS00) | (1 << CS02))
#define CLOCK_NUMBER_TO_COUNT_UP_TO OCR0A // 0 - 255 -  The counter will count up to the value in this register and then trigger.
#define CLOCK_TIMED_OUT (TIFR & (1 << OCF0A))
#define CLOCK_RESET (TIFR |= (1 << OCF0A))