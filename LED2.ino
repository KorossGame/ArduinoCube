/*
 * Author: Oleg Jakovlev
 * E-Mail: olegjakovlevlive@gmail.com
 */

//Library to work with strip
#include <Adafruit_NeoPixel.h>

//how much LEDS you have
#define LED_COUNT 192

//Width
#define width 6

//Height
#define height 8

//Pin strip is connected to
#define LED_PIN 6

//Max LEDS lightened
#define MAX_LIGHT 165;


bool LED_lightened[LED_COUNT];
int max_lightented = MAX_LIGHT;
unsigned long int delay_time = 50;

int lightened_counter = 0;

//How much LEDS on side
int LED_COUNT_SIDE = width*height;
int gamma_array[12][3]={{252, 240, 9},{252, 184, 22},{247, 148, 31},{243, 111, 36},{236, 27, 59},{162, 36, 143},{93, 47, 145},{15, 92, 170},{7, 115, 187},{26, 171, 174},{43, 180, 76},{164, 207, 58}};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

//Variable to store command to be executed
String command;

//All the effects available
void oneLEDColor(),Policai(),GenerateColor(),RunningGamma(),snow(),Full_LED_Gamma();

//Interval between function
unsigned long old_time = 0;
unsigned long interval = 25;

void setup()
{
  ADMUX = 1<<REFS1 | 1<<REFS0; //Main frequency from inside generator

  Serial.begin(9600);
  strip.setBrightness(25);    // brightness [0-255]
  strip.begin();
  randomSeed(analogRead(A1));
}

void serialEvent() {
  command=Serial.readString();
  Serial.print(command);
  
  if (command == "0\n")
  {
    reset();
  }
  
  else if (command == "1\n")
  {
    reset();
    while (!Serial.available()){
      if(millis() >= old_time + interval){
        old_time += interval;
        oneLEDColor(); 
      }
    }
  }

  else if (command == "2\n")
  {
    reset();
    while (!Serial.available()){
      if(millis() >= old_time + interval){
        old_time += interval;
        FullLEDColor(); 
      }
    }
  }

  else if (command == "3\n")
  {
    reset();
    while (!Serial.available()){
      if(millis() >= old_time + interval){
        old_time += interval;
        RunningLEDColor();
      }
    }
  }

  else if (command == "4\n")
  {
    reset();
    while (!Serial.available()){
      if(millis() >= old_time + interval){
        old_time += interval;
        RandomColorTwinkle();
      }
    }
  }

  else if (command == "5\n")
  {
    reset();
    while (!Serial.available()){
      if(millis() >= old_time + interval){
        old_time += interval;
        strobe();
      }
    }
  }

  else if (command == "6\n")
  {
    reset();
    while (!Serial.available()){
      if(millis() >= old_time + interval){
        old_time += interval;
        Sparkle();
      }
    }
  }

  else if (command == "delay\n")
  {  
    //change_delay == true;
  }
  
  else 
  {
    reset();  
  }
}

void loop(){
  //
}

void reset()
{  
  for (int i=0;i<LED_COUNT;i++)
  {
    strip.setPixelColor(i,strip.Color(0,0,0));
  }
  strip.show();
}

void oneLEDColor()
{
  for (int i=0;i<LED_COUNT;i++)
  {
    if (!Serial.available())
    {
      strip.setPixelColor(i,strip.Color(255,255,255));
      strip.show(); 
    }
    else
    {
      break;
    }
  }
}

void FullLEDColor()
{
  for (int i=0;i<12;i++)
  {
    for (int j=0;j<LED_COUNT;j++)
    {
      if (!Serial.available())
      {
        strip.setPixelColor(j,strip.Color(gamma_array[i][0],gamma_array[i][1],gamma_array[i][2]));
      }
      else
      {
        break;
      }
    }
    strip.show();
    delay(delay_time);
  }
}

void RunningLEDColor()
{
  for (int i=0;i<12;i++)
  {
    for (int j=0;j<LED_COUNT;j++)
    {
      if (!Serial.available())
      {
        strip.setPixelColor(j,strip.Color(gamma_array[i][0],gamma_array[i][1],gamma_array[i][2]));
        strip.show();
      }
      else
      {
        break;
      }
    }
  }
}

void Sparkle()
{
  int led_number = random(0,LED_COUNT);
  int led_number2 = random(0,LED_COUNT);
  
  if (!Serial.available())
  {
    strip.setPixelColor(led_number,strip.Color(255,255,255));
    strip.setPixelColor(led_number2,strip.Color(255,255,255));
    strip.show();

    delay(delay_time);

    strip.setPixelColor(led_number,strip.Color(0,0,0));
    strip.setPixelColor(led_number2,strip.Color(0,0,0));
    strip.show();
  }
}

void strobe()
{
  for (int i=0; i<LED_COUNT; i++)
  {
    if (!Serial.available())
    {
      strip.setPixelColor(i,strip.Color(255,255,255));
    }
    else 
    {
      break;
    }
  }
  strip.show();

  delay(delay_time);

  for (int i=0; i<LED_COUNT; i++)
  {
    if (!Serial.available())
    {
      strip.setPixelColor(i,strip.Color(0,0,0));
    }
    else
    {
      break;
    }
  }
  strip.show();

  delay(delay_time);
}

void RandomColorTwinkle()
{
  lightened_counter = 0;

  for (int i=0; i<LED_COUNT; i++)
  {
    LED_lightened[i] = false;
  }
  
  while (lightened_counter<max_lightented)
  {
    int randomLED = random(0,LED_COUNT);
    
    if (!LED_lightened[randomLED])
    {
      if (!Serial.available())
      {
        lightened_counter++;
        LED_lightened[randomLED] = true;
        strip.setPixelColor(randomLED,strip.Color(random(10,255),random(10,255),random(10,255)));
        strip.show();
      }
      else
      {
        break;
      }
    }
    else
    {
      while (LED_lightened[randomLED])
      {
        if (!Serial.available())
        {
          randomLED = random(0,LED_COUNT); 
        }
        else
        {
          break;
        }
      }
    }
  }

  reset();
}
