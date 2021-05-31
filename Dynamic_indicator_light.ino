//#define ESP8266
//#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <FastLED.h>

/** In my Audi A5 I will use the same led strip for the 
 *  dynamic-turn signal and for the reverse light.
 *  Because of this, the data output pin is the same (3)
 *  and the number of leds too.
 *  Anyway I'm writing the code in a more general way for applying in various use-cases.
 **/

#define ind_in 0  //gpio1
#define ind_data 4
#define ind_count 30
#define blink_time 650 //ms
CRGB ind_leds[ind_count]; //0 means first stripe

/*----------- Reverse Light -----------*/
#define rev_in 1
#define rev_data 4
#define rev_count 24
CRGB rev_leds[rev_count];

#define COLOR_ORDER RGB


void setup()
{
    Serial.begin(115200);
    pinMode(ind_in, INPUT);
    pinMode(ind_data, OUTPUT);
    pinMode(rev_in, INPUT);
    pinMode(rev_data, OUTPUT);  //same pin of ind_data for me

    FastLED.addLeds<WS2812B, ind_data, COLOR_ORDER>
                    (ind_leds, ind_count);
    FastLED.addLeds<WS2812B, rev_data, COLOR_ORDER>
                    (rev_leds, rev_count);
    Serial.println("Leds configured");

}

void loop()
{ 
    int ind_on = digitalRead(ind_in);
    int rev_on = digitalRead(rev_in);
    Serial.println("Indicator ON? "+ (String)ind_on);
    Serial.println("Reverse ON? "+ (String)ind_on);

    /*if( digitalRead(ind_in) == HIGH )
        blink();
    else  reverse();
    */
   reverse();
}

void blink()
{
    FastLED.clear(true);
    for(byte i=0; i<ind_count; i++){
        ind_leds[i].setRGB(255, 65, 0);
        ind_leds[i].maximizeBrightness();
            
        FastLED.show();
        delay((blink_time-150)/ind_count);
    }
    delay(150); //waits a bit with the full bar enlighted
    //then the car relay will automatically shut-down the system
}

void reverse()
{
    while(true){    //unless the car relay shuts down the power
        for(byte i=0; i<ind_count; i++){
            rev_leds[i].setRGB(255, 255, 200);
            rev_leds[i].maximizeBrightness();
        }
        FastLED.show();
    }
}