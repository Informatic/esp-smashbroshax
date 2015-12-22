#include <user_config.h>
#include <SmingCore/SmingCore.h>

#define LED_PIN 2 // GPIO number
#define BTN_PIN 0 // Flash button on NodeMCU

#include "payload.h"

Timer payloadSendTimer;

void ready()
{
	wifi_station_disconnect();
	wifi_station_set_config(NULL);
	wifi_set_opmode(1); // Is that really needed?
	wifi_set_channel(6);

	Serial.println("System ready");

	payloadSendTimer.initializeMs(100, *[] {
		digitalWrite(LED_PIN, digitalRead(BTN_PIN));

		if(!digitalRead(BTN_PIN)) {
			int status = wifi_send_pkt_freedom(payload, payload_size, 0);
			Serial.printf("Payload sent, status: %d\n", status);
		}
	}).start();
}

void init()
{
	pinMode(LED_PIN, OUTPUT);
	pinMode(BTN_PIN, INPUT);

	Serial.begin(SERIAL_BAUD_RATE); // 115200 by default
	Serial.systemDebugOutput(true); // Enable debug output to serial

	WifiStation.enable(false);
	WifiAccessPoint.enable(false);

	//Change CPU freq. to 160MHZ
	System.setCpuFrequency(eCF_160MHz);
	Serial.print("New CPU frequency is:");
	Serial.println((int)System.getCpuFrequency());

	System.onReady(ready);
}
