#include <FastLED.h>
#define NUM_LED_ARRAY 27
#define LED_PIN D6
CRGB LED_ARRAY[NUM_LED_ARRAY];

class LED {
  private:
    int X_VALUE;
    int Y_VALUE;
    int Z_VALUE;
    int RED_VALUE;
    int GREEN_VALUE;
    int BLUE_VALUE;
    int LED_POSITION;
    
  public:
    LED(int led_Position){
      LED_POSITION = led_Position;
      RED_VALUE = 0;
      GREEN_VALUE = 0;
      BLUE_VALUE = 0;
      
    }
    
    //setter
    void setR_Value(int red_Value){
      RED_VALUE = red_Value;
      LED_ARRAY[LED_POSITION].r = RED_VALUE; 
    }
    
    void setG_Value(int green_Value){
      GREEN_VALUE = green_Value;
      LED_ARRAY[LED_POSITION].g = GREEN_VALUE;
    }
    
    void setB_Value(int blue_Value){
      BLUE_VALUE = blue_Value;
      LED_ARRAY[LED_POSITION].b = BLUE_VALUE;
    }

    void setRGB_Values(int red_Value, int green_Value, int blue_Value){
      RED_VALUE = red_Value;
      GREEN_VALUE = green_Value;
      BLUE_VALUE = blue_Value;
      LED_ARRAY[LED_POSITION] = CRGB(
        red_Value,
        green_Value, 
        blue_Value
      );
    }

    //getter 

    int getX_Value(){
      return X_VALUE;
    }

    int getY_Value(){
      return Y_VALUE;
    }

    int getZ_Value(){
      return Z_VALUE;
    }

    int getR_Value(){
      return RED_VALUE;
    }

    int getG_Value(){
      return GREEN_VALUE;
    }

    int getB_Value(){
      return BLUE_VALUE;
    }
};



void createCoord(){
  }

void setup() {
  FastLED.addLED_ARRAY<WS2812,LED_PIN,GRB>(LED_ARRAY,NUM_LED_ARRAY);
  createCoord();
}

void loop() {

}
