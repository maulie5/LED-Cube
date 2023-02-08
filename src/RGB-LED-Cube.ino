//libaries
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FastLED.h>
#define NUM_LEDS 27
#define LED_PIN D6
#define LEN_SIDE 3

//variable declaration for later use
CRGB LED_ARRAY[NUM_LEDS];
static u_int32_t currentMillis;
u_int32_t nextMillis;
int LAYER = LEN_SIDE*LEN_SIDE;
ESP8266WebServer server(80);
const char* htmlMessage="<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>RGB-LED-Cube</title>"
        "<style>"

        "</style>"
    "</head>"
    "<body>"
        "<div>"
            "<div>Hello World</div>"
            "<div>"

            "</div>"
            "<div>"

            "</div>"
        "</div>"
    "</body>"
"</html>";

//class LED for asossiation of a LED with a coordiate
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


void setAll(u_int8_t red, u_int8_t green, u_int8_t blue){
  for(u_int8_t k = 0; k<NUM_LEDS; k++){
    LED_ARRAY[k] = CRGB(red, green, blue);
  }
}
void setAllX(u_int8_t x_value, u_int8_t red, u_int8_t green, u_int8_t blue){
  for(u_int8_t k = 0; k<NUM_LEDS; k++){
    if(LEDS_ARRAY[k].X_VALUE == x_value){
      LED_ARRAY[k] = CRGB(red, green, blue);
    }
  }
}
void setAllY(u_int8_t y_value, u_int8_t red, u_int8_t green, u_int8_t blue){
  for(u_int8_t k = 0; k<NUM_LEDS; k++){
    if(LEDS_ARRAY[k].Y_VALUE == y_value){
      LED_ARRAY[k] = CRGB(red, green, blue);
    }
  }
}
void setAllZ(u_int8_t z_value, u_int8_t red, u_int8_t green, u_int8_t blue){
  for(u_int8_t k = 0; k<NUM_LEDS; k++){
    if(LEDS_ARRAY[k].Z_VALUE == z_value){
      LED_ARRAY[k] = CRGB(red, green, blue);
    }
  }
}
void test(){
  setAll(255,255,255);FastLED.show();
  delay(10000);
  u_int8_t k = 0;
  while(LED_ARRAY[k].r >= 5 && LED_ARRAY[k].b >= 5 ){
    for(u_int8_t l = 0;l<NUM_LEDS;l++){
      LED_ARRAY[l].r -=1;
      LED_ARRAY[l].b -=1;
    }
    FastLED.show();
    delay(100);
    k++;
  }
  setAll(0,255,0);FastLED.show();
  delay(5000);
  setAll(255,255,255);FastLED.show();
  delay(5000);
  k = 0;
  while(LED_ARRAY[k].g >= 5 && LED_ARRAY[k].b >= 5 ){
    for(u_int8_t l = 0;l<NUM_LEDS;l++){
      LED_ARRAY[l].g -=1;
      LED_ARRAY[l].b -=1;
    }
    FastLED.show();
    delay(100);
    k++;
  }
  setAll(255,0,0);FastLED.show();
  delay(5000);
  setAll(255,255,255);FastLED.show();
  delay(5000);
  k = 0;
  while(LED_ARRAY[k].r >= 5 && LED_ARRAY[k].g >= 5 ){
    for(u_int8_t l = 0;l<NUM_LEDS;l++){
      LED_ARRAY[l].r -=1;
      LED_ARRAY[l].g -=1;
    }
    FastLED.show();
    delay(100);
    k++;
  }
  setAll(0,0,255);FastLED.show();
  delay(5000);

}
/*void snake(){
  setAll(0,0,0);
  for(u_int8_t o = 0;o<NUM_LEDS;o++){

  }
}*/

//-----------------------
void setup() {
  Serial.begin(9600);

  currentMillis = millis();
  Serial.println("First time messurement");

  FastLED.addLeds<WS2812,LED_PIN>(LED_ARRAY,NUM_LEDS);
  createCoord();
  Serial.println("Coordinate system was created");

  WiFi.begin("Home-Net.com","NobodyIsPerfect");
  Serial.print("Waiting to connect...");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Successfully connect to WiFi");


  Serial.print("IP adress: ");
  Serial.println(WiFi.localIP());
  
  WiFi.setHostname("ESP8266-12e RGB-LED");
  Serial.print("Hostname: ");
  Serial.println(WiFi.getHostname());

  server.on("/",[](){
    server.send(200,"text/html",htmlMessage);
  });
  server.on("/test",[](){
    server.send(200,"text / plain","Hello World");
    });
  server.begin();
  Serial.println("Server started and is listening to requests");
}
void loop() {
  server.handleClient();
  nextMillis = millis();
  u_int32_t millisDifference = nextMillis - currentMillis;
  Serial.println(millisDifference);
  //test();
  /*if(millisDifference <= 2000){
    for(int k = 0;k < NUM_LEDS;k++){
      LED_ARRAY[k] = CRGB(0,0,random8());
      LED_ARRAY[k].r = LED_ARRAY[k].b/10;

      FastLED.show();
    }
    delay(1000);
  }*/ 
}
