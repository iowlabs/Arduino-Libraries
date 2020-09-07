#ifndef __MYSQLHELPER_H__
#define __MYSQLHELPER_H__

#include <DNSServer.h>
#include <EEPROM.h>
#include "ConfigManager.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

class mysql_helper {
	public:
		mysql_helper() {}
		
		void setup_mysql();
		void handleClientMySQL();
		void handleRootMySQL();
		void handleMySQL();
};

#endif /* __MYSQLHELPER_H__ */
