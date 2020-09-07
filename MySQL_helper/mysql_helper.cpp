#include "mysql_helper.h"
#include "mysql_html_char.h"

#define MYSQL_OFFSET 200

ESP8266WebServer serverMySQL(80);

void mysql_helper::setup_mysql() {
	Serial.println("MySQL SETUP");
    serverMySQL.on("/", std::bind(&mysql_helper::handleRootMySQL, this));
    serverMySQL.on("/action_page", HTTPMethod::HTTP_POST, std::bind(&mysql_helper::handleMySQL, this));
	serverMySQL.begin();
}

void mysql_helper::handleClientMySQL() {
	Serial.println("DEBUG HANDLE");
    serverMySQL.handleClient();
}

void mysql_helper::handleRootMySQL() {
	Serial.println("DEBUG ROOT");
	String s = MAIN_page;
	serverMySQL.send(200, "text/html", s);
	/*SPIFFS.begin();
	fs::File f = SPIFFS.open("/mysql.html", "r");
	serverMySQL.streamFile(f, "text/html");
	

    f.close();*/
}

void mysql_helper::handleMySQL() {

	Serial.println("DEBUG :(");
    
	String mysql_server;
    String mysql_pass;
    String mysql_user;
    String mysql_db;

    char mysql_serverChar[32];
    char mysql_passChar[64];
	char mysql_userChar[64];
    char mysql_dbChar[64];

    mysql_server = serverMySQL.arg("mysql_server");
    mysql_pass = serverMySQL.arg("mysql_pass");
    mysql_user = serverMySQL.arg("mysql_user");
    mysql_db = serverMySQL.arg("mysql_db");

	
    if (mysql_server.length() == 0) {
        serverMySQL.send(400, "text/plain", "Invalid server name.");
        return;
    }
    if (mysql_pass.length() == 0) {
        serverMySQL.send(400, "text/plain", "Invalid password.");
        return;
    }
    if (mysql_user.length() == 0) {
        serverMySQL.send(400, "text/plain", "Invalid user.");
        return;
    }
    if (mysql_db.length() == 0) {
        serverMySQL.send(400, "text/plain", "Invalid database.");
        return;
    }
	
	Serial.println("DEBUG1");

    /*strncpy(mysql_serverChar, mysql_server.c_str(), sizeof(mysql_serverChar));
    strncpy(mysql_passChar, mysql_pass.c_str(), sizeof(mysql_passChar));
	strncpy(mysql_userChar, mysql_user.c_str(), sizeof(mysql_userChar));
    strncpy(mysql_dbChar, mysql_db.c_str(), sizeof(mysql_dbChar));*/
	
	EEPROM.begin(512);

	Serial.println("BEGIN");

    EEPROM.write(MYSQL_OFFSET, mysql_serverChar);

	Serial.println("WRITE 1");
    EEPROM.write(MYSQL_OFFSET + 16, mysql_passChar);

	Serial.println("WRITE 2");
    EEPROM.write(MYSQL_OFFSET + 80, mysql_userChar);

	Serial.println("WRITE 3");
    EEPROM.write(MYSQL_OFFSET + 144, mysql_dbChar);

	Serial.println("WRITE 4");

    EEPROM.commit();

    serverMySQL.send(204, "text/plain", "Saved. Will attempt to reboot.");

	
	Serial.println("RESTART");

    ESP.restart();
}
