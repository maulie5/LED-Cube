#include <FastLED.h>
#define NUM_LEDS 27
#define LED_PIN D6
#define LEN_SIDE 3
CRGB LED_ARRAY[NUM_LEDS];
class LED {
  public:
    LED();
    LED(int led_Position);
    int X_VALUE;
    int Y_VALUE;
    int Z_VALUE;
    int LED_POSITION;
};
LED::LED(){}
LED::LED(int led_Position){
  LED_POSITION = led_Position;
}

LED LEDS_ARRAY[NUM_LEDS];


void createCoord(){
  
  for(int POSITION = 0; POSITION < NUM_LEDS; POSITION++){
    LEDS_ARRAY[POSITION] = LED(POSITION);
  }
  for(int LED = 1; LED <= LEN_SIDE; LED++){
    for(int k = 1; k <= LEN_SIDE; k++){
      if((k-1)*pow(LEN_SIDE,2) <= LED && LED <= k*pow(LEN_SIDE,2)){
        LEDS_ARRAY[LED-1].Z_VALUE = (k-1);
      }
      if(((k-1)*pow(LEN_SIDE,2) <= LED) && (LEDS <= k*pow(LEN_SIDE,2)) && (k%2 == 1)){
        for(int j = 1; j <= LEN_SIDE; j++){
          if(((j-1)*LEN_SIDE+(k-1)*pow(LEN_SIDE,2) < LED) && (LED <= j*LEN_SIDE+k*pow(LEN_SIDE,2))){
            LEDS_ARRAY[LED-1].Y_VALUE = j-1;
          }
          if(j%2 == 1){
            if(LED%LEN_SIDE == 0){
              LEDS_ARRAY[LED-1].X_VALUE = LEN_SIDE-1;
            }else{
              LEDS_ARRAY[LED-1].X_VALUE = LED%LEN_SIDE-1;
            }
          }else{
            if(LED%LEN_SIDE == 0){
              LEDS_ARRAY[LED-1].X_VALUE = 0; 
            }else{
              LEDS_ARRAY[LED-1].X_VALUE = LED%LEN_SIDE;
            }
          }
        }
      }else if((k%2) == 1){
        for(int l = 1; l <= LEN_SIDE; l++){
          if(((k-1)*pow(LEN_SIDE,2)+(l-1)*LEN_SIDE < LED) && (LED <= ((k-1)*pow(LEN_SIDE,2)+l*LEN_SIDE)){
            LEDS_ARRAY[LED-1].Y_VALUE = LEN_SIDE-l;
          }
          if(l%2 == 1){
            if()

          }
        }
      }
    }
  }
}

void setup() {
  FastLED.addLeds<WS2812,LED_PIN,GRB>(LED_ARRAY,NUM_LEDS);
  createCoord();
}

void loop() {

}
