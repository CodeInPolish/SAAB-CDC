#include "RN52impl.h"

/**
 * Reads the input (if any) from UART over software serial connection
 */

void RN52impl::readFromUART() {
    while (softSerial.available()) {
        char c = softSerial.read();
        fromUART(c);
    }
}


/**
 * Formats a message and writes it to UART over software serial
 */

void RN52impl::toUART(const char* c, int len){
    for(int i = 0; i < len; i++)
        softSerial.write(c[i]);
};

void RN52impl::fromSPP(const char* c, int len){
    // bytes received from phone via SPP
    
    // to send bytes back to the phone call rn52.toSPP
};

void RN52impl::setMode(Mode mode){
    if (mode == COMMAND) {
        digitalWrite(BT_CMD_PIN, LOW);
    } else if (mode == DATA) {
        digitalWrite(BT_CMD_PIN, HIGH);
    }
};

const char *CMD_QUERY = "Q\r";
void RN52impl::onGPIO2() {
    queueCommand(CMD_QUERY);
}

void RN52impl::onProfileChange(BtProfile profile, bool connected) {
    switch(profile) {
        case A2DP:bt_a2dp = connected;
            if (connected && playing) {
                Serial.println("DEBUG: RN52 connection ok; 'auto-play' should kick in now!");
                sendAVCRP(RN52::RN52driver::PLAY);
            }
            break;
        case SPP:bt_spp = connected;break;
        case IAP:bt_iap = connected;break;
        case HFP:bt_hfp = connected;break;
    }
}

/**
 * Initializes Atmel pins and software serial for their initial state on startup
 */

void RN52impl::initialize() {
    softSerial.begin(9600);
    pinMode(BT_EVENT_INDICATOR_PIN,INPUT);
    pinMode(BT_CMD_PIN, OUTPUT);
    pinMode(BT_FACT_RST_PIN,INPUT);             // Some REALLY crazy stuff is going on if this pin is set as output and pulled low. Leave it alone! Trust me...
    pinMode(BT_PWREN_PIN,OUTPUT);
    digitalWrite(BT_EVENT_INDICATOR_PIN,HIGH);  // Default state of GPIO2, per data sheet, is HIGH
    digitalWrite(BT_CMD_PIN,HIGH);              // Default state of GPIO9, per data sheet, is HIGH
    digitalWrite(BT_PWREN_PIN,HIGH);            // Keeping the PWREN pin HIGH for now to keep the module ON at all times. TODO: implement go-to-sleep/wakeup function.
}