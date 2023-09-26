#include <ESPAsyncWebServer.h>

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

void sendAlarmAndroidEvent(){
    if(androidServerInitialized){
        //androidEvents.send("Message", "Event", millis());
        //Serial.println("Message:Event");
        static unsigned long ms;
        ms = millis();
        androidEvents.send("Message sent from ESP32", "Event", ms);
        size_t ev_count;
        ev_count = androidEvents.count();
        Serial.println("Sent an event! " + String(ms) + "[ev_count=" + String(ev_count) + "]");
    }
    
}