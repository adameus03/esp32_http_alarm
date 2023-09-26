#include <Arduino.h>
#include <Ticker.h>
#include "sound/dog_sounds.h"

#define RELAY_1_PIN 16
#define RELAY_2_PIN 17
#define TDA_2030_IN 25

#define PLAYING_TIMER_PRESCALER 80 // 80MHz/80 = 1MHz ==> PLAYING_TIMER_VAL tells how many us need to elapse in order for the interrupt to be generated
#define PLAYING_TIMER_VAL 10000000 // 10s
#define PLAYING_TIMER_INDEX 1

//volatile bool isPlaying = false;
//bool timerInitialized = false;
//hw_timer_t* playingTimer = NULL;

bool isPlaying = false;
Ticker playingTicker;

void initPlayer(){
    pinMode(RELAY_1_PIN, OUTPUT);
    pinMode(RELAY_2_PIN, OUTPUT);
    digitalWrite(RELAY_1_PIN, HIGH);
    digitalWrite(RELAY_2_PIN, HIGH);

    //playingTimer = timerBegin(PLAYING_TIMER_INDEX, PLAYING_TIMER_PRESCALER, false);
}

/*void IRAM_ATTR onPlayingTimer(){
    isPlaying = false;
    digitalWrite(RELAY_1_PIN, HIGH);
    Serial.println("Hello from playing timer interrupt ISR");
}*/
void onPlayingTicker(){
    isPlaying = false;
    digitalWrite(RELAY_1_PIN, HIGH);
    Serial.println("Hello from playing ticker interrupt handler");
}

/*void startPlayingTimer(){
    Serial.println("timerAttachInterrupt(playingTimer, &onPlayingTimer, true);");
    timerAttachInterrupt(playingTimer, &onPlayingTimer, true);
    
    Serial.println("timerAlarmWrite(playingTimer, PLAYING_TIMER_VAL, false);");
    timerAlarmWrite(playingTimer, PLAYING_TIMER_VAL, false);
    yield();

    Serial.println("timerAlarmEnable(playingTimer);");
    timerAlarmEnable(playingTimer);

    
    
    
}*/

void playSound(){ //maybe add timer for turning off relay after time of inactivity?
    playingTicker.once_ms(10000, onPlayingTicker);
    digitalWrite(RELAY_1_PIN, LOW);
    /*if(isPlaying){
        //timerRestart(playingTimer); // zxc
        //timerWrite(playingTimer, 0); //zxc
        timerAlarmDisable(playingTimer);
        timerAlarmWrite(playingTimer, PLAYING_TIMER_VAL, false);
        timerRestart(playingTimer);
        yield();
        timerAlarmEnable(playingTimer);
    }
    else {
        isPlaying = true;
        digitalWrite(RELAY_1_PIN, LOW);
        if(timerInitialized){
            //timerRestart(playingTimer); //gre
            //timerWrite(playingTimer, 0); //gre
            timerAlarmDisable(playingTimer);
            timerAlarmWrite(playingTimer, PLAYING_TIMER_VAL, false);
            timerRestart(playingTimer);
            yield();
            timerAlarmEnable(playingTimer);
        }
        else {
            timerInitialized = true;
            startPlayingTimer();
            delay(1);
        }

    }*/
    
    for(unsigned long long i=0x0; i</*_home_mundus_snap_audacity_current_pryc_raw_len*//*_home_mundus_Downloads_bytedata_raw_len*/_home_mundus_snap_audacity_current_dog_single_raw_len; i++){
        dacWrite(TDA_2030_IN, /*_home_mundus_snap_audacity_current_pryc_raw[i]*//*128+_home_mundus_Downloads_bytedata_raw[i]*/_home_mundus_snap_audacity_current_dog_single_raw[i]);
        delayMicroseconds(120);
    }
    //digitalWrite(RELAY_1_PIN, HIGH);
}