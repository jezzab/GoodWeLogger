#pragma once
#include <WiFi.h>

class SettingsManager
{
public:
	struct Settings
	{
	public:
		//mqtt settings
		String mqttHostName;
		int mqttPort;
		String mqttUserName;
		String mqttPassword;
		int mqttQuickUpdateInterval;
		int mqttRegularUpdateInterval;

		//pvoutput settings
		String pvoutputApiKey;
		String pvoutputSystemId;
		int pvoutputUpdateInterval;

		//wifi settings
		String wifiHostname;		//Set hostname for ESP8266
		String wifiSSID;
		String wifiPassword;
		int wifiConnectTimeout;

		//general settings
		int RS485Rx = 25;		//default set because added later
		int RS485Tx = 26;
		int inverterOfflineDataResetTimeout;
		int timezone;

		//NTP
		String ntpServer;


	};
	SettingsManager();
	~SettingsManager();

	Settings * GetSettings();
};
