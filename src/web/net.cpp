#include "headers/net.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void initWifi()
{
	WiFi.begin(ssid, password);
}

void initTime()
{
	configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

	onTime.tm_hour = 7;
	onTime.tm_min = 0;

	offTime.tm_hour = 23;
	offTime.tm_min = 0;

	Serial.println("Time initialized");
}

bool getWifiStatus()
{
	return (WiFi.status() == WL_CONNECTED);
}

bool getTime(struct tm *timeinfo)
{
	if (!getLocalTime(timeinfo))
	{
		Serial.println("Failed to obtain time");
		return false;
	}
	//Serial.println("getTime ");
	return true;
}

String getLocalTimeString(const char *format)
{
	struct tm timeinfo;
	if (!getTime(&timeinfo))
	{
		return "Error";
	}
	return getTimeString(timeinfo, format);
}
String getTimeString(struct tm time, const char *format) {
  char buffer[64];
	strftime(buffer, sizeof(buffer), format, &time);
	return String(buffer);
}

String getTimeString(struct tm time) {
  char buffer[6]; // Format hh:mm
  snprintf(buffer, sizeof(buffer), "%02d:%02d", time.tm_hour, time.tm_min);
  return String(buffer);
}

String getLocalAddress()
{
	return WiFi.localIP().toString();
}

bool isBetweenTime()
{
	struct tm timeinfo;
	if (!getTime(&timeinfo))
	{
		return false;
	}
	return ((onTime.tm_hour * 60) + onTime.tm_min < (timeinfo.tm_hour * 60) + timeinfo.tm_min) &&
			((offTime.tm_hour * 60) + offTime.tm_min > (timeinfo.tm_hour * 60) + timeinfo.tm_min);
}