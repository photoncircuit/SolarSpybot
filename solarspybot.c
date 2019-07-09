//define pin used#
#define sw1 PORTC.F0
#define buzzer PORTC.F7
#define servo_motor1 PORTB.F0
#define servo_motor2 PORTB.F1
#define flag_on flag.F0
#define led1 PORTB.F6
#define led2 PORTB.F7
//declare variables
char sensorL, sensorR;
char flag;
char servo_value;
char temp, temp1;
char x, y;
//define function prototype
void move_servo_base(char);
void move_servo_top(char);
void beep(void);
//***********************************
//main function
void main(void) {
  ADCON1 = 0x80; //set porta to on adc read analogue
  TRISA = 0xFF; //set porta as input
  TRISC = 0b00000001; //portc 0 as input for
  switch
  for camera rotation
  TRISB = 0b00111100; //portb as op/input
  PORTA = PORTB = PORTC = 0x00; //clear all ports
  PORTB = 0x00;
  PORTC = 0x00;
  flag = 0x00;
  sensorR = sensorL = 0x00; //clear sensor
  temp = 50; //temp value for servo place
  servo motor to middle
  flag_on = 0; //flag for system to turn on
  INTCON = 0xA0; //for timer use
  for (y = 0; y <= 10; y++) //loop to start motor at
    middle position {
      move_servo_top(50); //control solar servo
      delay_ms(18);
    }
  //endelss loop
  //main routine
  do {
    sensorL = adc_read(0) / 4; //read 1st analogue
    and save in sensorL
    sensorR = adc_read(1) / 4; //read 2nd analogue
    if (flag_on) //when flag is in on position then
      rotate the camera {
        for (y = 0; y <= 10; y++) //loop 10x
        {
          move_servo_top(50); //start from middle
          delay_ms(18);
        }
        delay_ms(500); //delay 1/2sec
        for (y = 0; y <= 10; y++) {
          move_servo_top(70); //move to 70
          delay_ms(18);
        }
        delay_ms(500);
        for (y = 0; y <= 10; y++) {
          move_servo_top(90); //move to 90 %
          delay_ms(18);
        }
        delay_ms(500);
        for (y = 0; y <= 10; y++) {
          move_servo_top(70); //move to 70 %
          delay_ms(18);
        }
        delay_ms(500);
        for (y = 0; y <= 10; y++) {
          move_servo_top(50); //move 50 %
          delay_ms(18);
        }
        delay_ms(500);
        for (y = 0; y <= 10; y++) {
          move_servo_top(30); //move to 30%
          delay_ms(18);
        }
        delay_ms(500);
        for (y = 0; y <= 10; y++) {
          move_servo_top(1); //move to 1%
          delay_ms(18);
        }
        delay_ms(500);
        for (y = 0; y <= 10; y++) {
          move_servo_top(30); //move to 50 %
          delay_ms(18);
        }
        delay_ms(500); //and save in sensorR
        //convert to ADC 8bit(255 max)
        if ((sensorL - sensorR) >= 15) //compare the value
          (15 / 255) * 5 = 0.29 Volts {
            temp = temp + 1; //increase temp value by
            1
            if (temp >= 100) //max to go 100 = 180deg
              temp = 100;
          }
        else if ((sensorR - sensorL) >= 15) //compare right to
          left > 0.29 Volts {
            temp = temp - 1; //decrease temp value by
            1
            if (temp <= 1)
              temp = 1; //min value is 1
          }
        else //else remain in middle
        {
          temp = 50;
        }
        if (sw1) //when sw1 is press
        {
          if (flag_on) //if flag on for rotation then
          {
            flag_on = 0; //toggle off
            for (y = 0; y <= 20; y++) //move servo to middle
              for 20 loops {
                move_servo_top(50);
                delay_ms(18);
              }
          } else //else turn on flag
            flag_on = 1;
          beep(); //beep sound
          while (sw1); //wait till it release
        }
      }
    move_servo_base(temp); //maintain camera servo value
    move_servo_top(temp1); //maintain solar servo value
    Delay_Ms(18);
  } while (1); //looping
}
//***********************************
void beep(void) //routine to beep
{
  buzzer = 1; //turn on/off buzzer
  delay_ms(100);
  buzzer = 0;
  delay_ms(100);
}
void move_servo_base(char y) //servo motor routine for
camera {
  char x, t;
  servo_motor1 = 1; //on servo1
  for (x = 0; x <= y; x++) //delay from 1 to 100
    Delay_Us(10);
  Delay_Us(500); //base value =500us
  servo_motor1 = 0; //turn motor off to pulse the
  motor
}
void move_servo_top(char y) //servo motor routine for
solar {
  char x, t;
  servo_motor2 = 1; //on servo 2
  for (x = 0; x <= y; x++)
    Delay_Us(10);
  Delay_Us(500);
  servo_motor2 = 0;
}