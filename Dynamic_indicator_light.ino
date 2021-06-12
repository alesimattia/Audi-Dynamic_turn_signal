#define ESP8266
#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <FastLED.h>

/** In my Audi A5 I will use the same led strip for the 
 *  dynamic-turn signal and for the reverse light.
 *  Because of this, the data output pin is the same (3)
 *  and the number of leds too.
 *  Anyway I'm writing the code in a more general way for applying in various use-cases.
 **/

#define ind_in 1
#define ind_data 0
#define ind_count 20
#define blink_time 550 //ms
CRGB ind_leds[ind_count];

/*----------- Reverse Light -----------*/
#define rev_in 2
#define rev_data 0  //same pin of ind_data for me
#define rev_count 50
CRGB rev_leds[rev_count];

#define COLOR_ORDER RGB


void setup()
{
    Serial.begin(115200);
    pinMode(ind_in, INPUT);
    pinMode(ind_data, OUTPUT);
    pinMode(rev_in, INPUT);
    pinMode(rev_data, OUTPUT);  

    FastLED.addLeds<WS2812, ind_data, COLOR_ORDER>
                    (ind_leds, ind_count);
    FastLED.addLeds<WS2812, rev_data, COLOR_ORDER>
                    (rev_leds, rev_count);

}

void loop()
{ 
    int ind_on = digitalRead(ind_in);
    int rev_on = digitalRead(rev_in);
    Serial.println("Indicator ON? "+ (String)ind_on);
    Serial.println("Reverse ON? "+ (String)ind_on);
    
    /*if( ind_on == HIGH )
        blink();
    else  reverse();*/
    Serial.println("---------------");
    blink();
}

void blink()
{
    FastLED.clear(true);
    for(byte i=0; i<ind_count; i++){
        ind_leds[i].setRGB(255, 65, 0);
            
        FastLED.show();
        delay( (blink_time-150)/ind_count);
    }
    delay(150);  
    /*waits a bit with the full bar enlighted
        then the car relay will automatically shut-down the system */
    
}

void reverse()
{
    FastLED.clear(true);
    for(byte i=0; i<rev_count; i++){
        rev_leds[i].setRGB(255, 255, 210);
        //rev_leds[i] = CRGB::White;
        rev_leds[i].maximizeBrightness();
    }
    FastLED.show();
    while(true){ delay(INT32_MAX); }   //unless the car relay shuts down the power}
}