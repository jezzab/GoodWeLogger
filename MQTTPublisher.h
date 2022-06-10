#define MQTT_SOCKET_TIMEOUT 5
#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include "SettingsManager.h"
#include "GoodWeCommunicator.h"
#include <vector>
#include "PubSubClient.h"
#include "WiFiClient.h"
#include "Debug.h"

#define RECONNECT_TIMEOUT 15000


class MQTTPublisher
{
private:
	SettingsManager::Settings * mqttSettings;
	SettingsManager * mqttSettingsManager;
	GoodWeCommunicator * goodweCommunicator;
	bool isStarted;

	unsigned long lastConnectionAttempt = 0;		//last reconnect
	unsigned long lastSentQuickUpdate = 0;			//last update of the fast changing info
	unsigned long lastSentRegularUpdate = 0;		//last update of the regular update info

	bool publishOnMQTT(String prepend, String topic, String value);
	bool reconnect();
public:
	MQTTPublisher(SettingsManager * settingsManager, GoodWeCommunicator *goodWe);
	~MQTTPublisher();

	void start();
	void stop();
	
	void handle();
};
