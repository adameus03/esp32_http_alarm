//https://RandomNerdTutorials.com/esp32-cam-video-streaming-web-server-camera-home-assistant/
//https://plociennik.info/index.php/informatyka/systemy-wbudowane/esp8266

/*
  TODO
  [ ] Allow multiple clients to connect to the webservers #0
  [ ] Handle the limited storage of the uSD card (delete the oldest file(s)) #1
  [x] OTA upload  #2
  [x] timer interrupts to store photos 11.08.2023 #3
  [ ] OTA debug(override serial) #4
  [x] OTA upload using timer interrupt #5
  [ ] Watchdog #6


  {x} quick file timeline
      { } auto playback
  { } okresowe opróżnianie karty
  { } change camera settings
  { } push notifications
  { } speaker
  { } change camera settings according to conditions?
*/

/*
  OTA uses timer 0
  Player(<!--Gallery-->) uses timer 1
  Public OTA uses timer 2
*/

#include <ArduinoOTA.h>
#include <WiFi.h>
#include "esp_timer.h"
#include "Arduino.h"
#include "soc/soc.h" //disable brownout problems
#include "soc/rtc_cntl_reg.h"  //disable brownout problems
//#include "esp_http_server.h"

#include "webserver.hpp"
#include "ota.hpp" //

#include "player.hpp"
#include "androidAlarm.hpp"

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector
 
  Serial.begin(115200);
  Serial.setDebugOutput(false);

  
  initializeWebServer();
  initializeAlarmAndroidServer();

  //initOTA();//.
  //startHandlingOTA();//.

  startHandlingPublicOTA();
  haltPublicOTA(); // {{{not too early?}}}

  initPlayer();
  delay(3000);
  
  startWebServer(); //C//
}

void loop() {

  if(checkIfTimeForPublicOTAHandle()){
    publicOTATickImplied();
  }

  else delay(10); //////

  //Serial.println(heap_caps_get_free_size(0)); //D
  //updateTime(); //concurrent r/w??
}