#include <FastLED.h>
#define NUM_LEDS 27
#define LED_PIN D6
#define LEN_SIDE 3
CRGB LED_ARRAY[NUM_LEDS];
int LAYER = LEN_SIDE*LEN_SIDE;
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
  for(int LED = 0; LED < NUM_LEDS; LED++){
    for(int z = 1; z <= LEN_SIDE; z++){
      if( (z-1)*LAYER <= LED && LED <= z*LAYER ){
        LEDS_ARRAY[LED].Z_VALUE = z-1;
      }
    }
    if((LEDS_ARRAY[LED].Z_VALUE%2)==0){
      for(int LAY = 0; LAY<LEN_SIDE;LAY+=2){
        for(int y = 1;y <= LEN_SIDE;y++){
          if(LAY*LAYER+(y-1)*LEN_SIDE <= LED && LED < LAY*LAYER+y*LEN_SIDE){
            LEDS_ARRAY[LED].Y_VALUE = y-1;
          }
        }
      }

      if(LEDS_ARRAY[LED].Y_VALUE%2==0){
        if(LED%LEN_SIDE+1==0){
          LEDS_ARRAY[LED].X_VALUE = LEN_SIDE ;
        }else{
          LEDS_ARRAY[LED].X_VALUE = LED%LEN_SIDE;
        }
      }else if(LEDS_ARRAY[LED].Y_VALUE%2==1){
        if(LED%LEN_SIDE+1==0){
          LEDS_ARRAY[LED].X_VALUE = 0;
        }else{
          LEDS_ARRAY[LED].X_VALUE = LEN_SIDE-(LED%LEN_SIDE)-1;
        }
      }
    }else{
      int LAYER_POSITION = LED%LAYER;
      for(int LAY = 0; LAY < LEN_SIDE;LAY++){
        if(LAYER_POSITION <= (LAY+1)*LEN_SIDE && LAYER_POSITION >= LAY*LEN_SIDE){
          LEDS_ARRAY[LED].Y_VALUE = LEN_SIDE - LAY-1;
        }
      }
      if(LEDS_ARRAY[LED].Y_VALUE%2==0){
        if(LED%LEN_SIDE==0){
          LEDS_ARRAY[LED].X_VALUE = LEN_SIDE-1;
        }else{
          LEDS_ARRAY[LED].X_VALUE = (LEN_SIDE-LED%LEN_SIDE)-1;
        }
      }else if(LEDS_ARRAY[LED].Y_VALUE%2==1){
        if(LED%LEN_SIDE==0){
          LEDS_ARRAY[LED].X_VALUE = 0;
        }else{
          LEDS_ARRAY[LED].X_VALUE = LED%LEN_SIDE;
        }
      }
    }

  }
}
void reset(){
  for(int k = 0;k<NUM_LEDS;k++){
    LED_ARRAY[k] = CRGB(0,0,0);
  }
}
void setup() {
  FastLED.addLeds<WS2812,LED_PIN>(LED_ARRAY,NUM_LEDS);
  createCoord();
}

void loop() {
  for(int k = 0;k < NUM_LEDS;k++){
    if(LEDS_ARRAY[k].X_VALUE == 0 || LEDS_ARRAY[k].X_VALUE == 2){
      LED_ARRAY[k] = CRGB(50,50,50);
    }else{
      LED_ARRAY[k] = CRGB(0,0,0);
    }
    FastLED.show();
  }
  delay(2000);
  reset();
  FastLED.show();
  delay(2000);
  FastLED.show();
}
