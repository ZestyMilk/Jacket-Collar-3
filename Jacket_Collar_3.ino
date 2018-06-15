#include <Adafruit_NeoPixel.h>

#define PIN            12

//4 high, 28 across
#define NUMPIXELS      112
const int height = 4;  //height of frame
const int width = 28;   //width of frame

Adafruit_NeoPixel grid = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint32_t interval = 500; // delay for half a second
uint32_t lastLoop = 0;

//index LEDs by position, (column, -row)

//define a circle by position and radius
float circleX = 13.5;
float circleY = 1.5;
float circleR = 2;


//https://en.wikipedia.org/wiki/Pythagorean_theorem
bool isInCircle(float px, float py, float X, float Y, float R)
{
float sqDist = ((X-px)*(X-px)) + ((Y-py)*(Y-py));
if((R*R) > sqDist){
//we're inside
return true;
}
else
{
//outside
return false;
}
}


/*
uint8_t LEDGRID() =
  { //LED reassignments                                                                          //centre//
    {{413}, {412}, {411}, {410}, {409}, {408}, {407}, {406}, {405}, {404}, {403}, {402}, {401}, {400}, {400}, {401}, {402}, {403}, {404}, {405}, {406}, {407}, {408}, {409}, {410}, {411}, {412}, {413}}, //fourth row
    {{313}, {312}, {311}, {310}, {309}, {308}, {307}, {306}, {305}, {304}, {303}, {302}, {301}, {300}, {300}, {301}, {302}, {303}, {304}, {305}, {306}, {307}, {308}, {309}, {310}, {311}, {312}, {313}}, //third row
    {{213}, {212}, {211}, {210}, {209}, {208}, {207}, {206}, {205}, {204}, {203}, {202}, {201}, {200}, {200}, {201}, {202}, {203}, {204}, {205}, {206}, {207}, {208}, {209}, {210}, {211}, {212}, {213}}, //second row
    {{113}, {112}, {111}, {110}, {109}, {108}, {107}, {106}, {105}, {104}, {103}, {102}, {101}, {100}, {100}, {101}, {102}, {103}, {104}, {105}, {106}, {107}, {108}, {109}, {110}, {111}, {112}, {113}}  //first row
  };                                                                                             //centre//
*/
void setup() {
  grid.begin(); // This initializes the NeoPixel library.
  grid.show();
}

void loop() {
uint32_t loopTime = millis();
if(loopTime>lastLoop+interval){
lastLoop=loopTime;
//code here runs once per interval

for(int row = 0; row<height; row++)
{  //row by row
for(int col=0; col<width; col++)
{  //one pixel at a time

bool pxTest = isInCircle(col, row, circleX, circleY, circleR);

//figure out which led on the strip
int ledPos = col + (row*(width));

//set the colour
if(pxTest){
grid.setPixelColor(
ledPos,
255, 0, 0
);
}
else
{
grid.setPixelColor(
ledPos,
0, 0, 0
);
}
}//row complete
}//refresh complete
grid.show(); // This sends the updated pixel color to the hardware.
//delay(wait); // Delay for a period of time (in milliseconds).

}


  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

/*
  for(int i=0;i<NUMPIXELS;i++){
    
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    grid.setPixelColor(LEDGRID, pixels.Color(0,150,0)); // Moderately bright green color.

    grid.show(); // This sends the updated pixel color to the hardware.

    delay(wait); // Delay for a period of time (in milliseconds).
  }
*/
}
