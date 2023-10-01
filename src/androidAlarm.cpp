#include <ESPAsyncWebServer.h>
#include "deviceName.h"

AsyncWebServer androidServer(8080);
AsyncEventSource androidEvents("/events");

bool androidServerInitialized = false;

void initializeAlarmAndroidServer(){
    androidEvents.onConnect([](AsyncEventSourceClient *client){
        if(client->lastId()){
            Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
        }
        // send event with message "hello!", id current millis
        // and set reconnect delay to 1 second
        client->send("hello!", NULL, millis()); 
    });
    androidServer.addHandler(&androidEvents);
    androidServer.begin();
    androidServerInitialized = true;
}

void sendAlarmAndroidEvent(const uint16_t& cid){
    if(androidServerInitialized){
        //androidEvents.send("Message", "Event", millis());
        //Serial.println("Message:Event");
        static unsigned long ms;
        ms = millis();
        if(cid == 0xffff){
            androidEvents.send("Brak identyfikatora kamery", "Event", ms);
        }
        else {
            switch(cid){
                case 1:
                    androidEvents.send(DEV_1_NAME, "Event", ms);
                    break;
                case 2:
                    androidEvents.send(DEV_2_NAME, "Event", ms);
                    break;
                case 3:
                    androidEvents.send(DEV_3_NAME, "Event", ms);
                    break;
                case 4:
                    androidEvents.send(DEV_4_NAME, "Event", ms);
                    break;
                default:
                    androidEvents.send(("Kamera " + String(cid)).c_str(), "Event", ms);

            }
            
        }
        size_t ev_count;
        ev_count = androidEvents.count();
        Serial.println("Sent an event! " + String(ms) + "[ev_count=" + String(ev_count) + "]");
    }
    
}