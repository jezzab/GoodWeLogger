//Wifi SSID to connect to
#define WIFI_SSID "<your wifi ssid>"

//Passowrd for WIFI
#define WIFI_PASSWORD "<your wifi pwd>"

//set the mqqt host name or ip address to your mqqt host. Leave empty to disable mqtt.
#define MQTT_HOST_NAME  "192.168.2.2"

//mqtt port for the above host
#define MQTT_PORT       1883

//if authentication is enabled for mqtt, set the username below. Leave empty to disable authentication
#define MQTT_USER_NAME  "<mqtt user name>"

//password for above user
#define MQTT_PASSWORD   "<mqtt password>"

//update interval for fast changing values in milliseconds for mqtt
#define MQTT_QUICK_UPDATE_INTERVAL  10000

//update interval for slow changing values in milliseconds for mqtt
#define MQTT_REGULAR_UPDATE_INTERVAL  60000

//set to your pvoutput api key (must have write rights). Leave empty to disable pvoutput publishing
#define PVOUTPUT_API_KEY  "<your api key for pvoutput>"

//set to the pvoutput system id to update. Only the first inverter is supported for now
#define PVOUTPUT_SYSTEM_ID  "<pvoutput system id>"

//how long between pvoutput updates. Pvoutput specifies a minimum of 5 minutes (5*60*1000)
#define PVOUTPUT_UPDATE_INTERVAL   5 * 60 * 1000

//timezone offset in hours (amsterdam is +2 in summertime). Used for posting to pvoutput
#define TIMEZONE 2

//rs485 receive pin
#define RS485_RX 25

//rs485 transmit pin
#define RS485_TX 26

//Hostname to use on local network
#define WIFI_HOSTNAME "GoodWeLogger"

//NTP server addres
#define NTP_SERVER "pool.ntp.org"

//Wifi connection timeout. If Wifi connection is lost for this long the ESP is restarted
#define WIFI_CONNECT_TIMEOUT 30*1000 

//Inverter data reset after 11 minutes (inverter reconnect timeout is 10 minutes, 1 minute extra to avoid too quick reset) 
#define INVERTER_OFFLINE_RESET_VALUES_TIMEOUT 11*60*1000 

//Enable debbugging through serial or remote
#define DEBUGGING_ENABLED true

//Enable telnet/remote debugging?
#define REMOTE_DEBUGGING_ENABLED true