
//*******************************libraries********************************
#include <SPI.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_Fingerprint.h> //Library link:https://github.com/adafruit/Adafruit-Fingerprint-Sensor-Library
//************************************************************************
//Fingerprint scanner Pins
#define Finger_Rx 14 //D5
#define Finger_Tx 12 //D6
//************************************************************************
SoftwareSerial mySerial(Finger_Rx, Finger_Tx);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
//************************************************************************
/* Set these to your desired credentials. */
const char *ssid = "Install Virus"; //ENTER YOUR WIFI SETTINGS
const char *password = "57309343";
//************************************************************************
String postData ; // post array that will be send to the website
//String link = "http://192.168.0.100/biometricattendance/getdata.php"; //computer IP or the server domain
String link = "http://192.168.0.100/api/login"; //computer IP or the server domain
int FingerID = 0; // The Fingerprint ID from the scanner
uint8_t id;
//*************************Biometric Icons*********************************
#define Wifi_start_width 54
#define Wifi_start_height 49
const uint8_t PROGMEM Wifi_start_bits[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x1f,0xf0,0x00,0x00,0x00
,0x00,0x03,0xff,0xff,0x80,0x00,0x00
,0x00,0x1f,0xf0,0x1f,0xf0,0x00,0x00
,0x00,0x7e,0x00,0x00,0xfc,0x00,0x00
,0x01,0xf0,0x00,0x00,0x1f,0x00,0x00
,0x03,0xc0,0x00,0x00,0x07,0xc0,0x00
,0x0f,0x00,0x00,0x00,0x01,0xe0,0x00
,0x1c,0x00,0x00,0x00,0x00,0x70,0x00
,0x38,0x00,0x07,0xc0,0x00,0x38,0x00
,0x70,0x00,0xff,0xfe,0x00,0x1e,0x00
,0xe0,0x03,0xfc,0x7f,0xc0,0x0e,0x00
,0x00,0x1f,0x80,0x03,0xf0,0x00,0x00
,0x00,0x3c,0x00,0x00,0x78,0x00,0x00
,0x00,0xf0,0x00,0x00,0x1c,0x00,0x00
,0x01,0xe0,0x00,0x00,0x0c,0x00,0x00
,0x03,0x80,0x00,0x00,0x00,0x00,0x00
,0x03,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x3f,0xf8,0x07,0x1e,0x00
,0x00,0x00,0xff,0xfe,0x1f,0xbf,0x80
,0x00,0x03,0xe0,0x04,0x7f,0xff,0xc0
,0x00,0x07,0x80,0x00,0xff,0xff,0xe0
,0x00,0x0e,0x00,0x00,0xff,0xff,0xe0
,0x00,0x0c,0x00,0x00,0x7f,0xff,0xc0
,0x00,0x00,0x00,0x00,0xfe,0x07,0xe0
,0x00,0x00,0x00,0x03,0xf8,0x03,0xf8
,0x00,0x00,0x07,0xe7,0xf9,0xf1,0xfc
,0x00,0x00,0x1f,0xe7,0xf1,0xf9,0xfc
,0x00,0x00,0x1f,0xe7,0xf3,0xf9,0xfc
,0x00,0x00,0x3f,0xe7,0xf3,0xf9,0xfc
,0x00,0x00,0x3f,0xe7,0xf1,0xf1,0xfc
,0x00,0x00,0x3f,0xe3,0xf8,0xe3,0xfc
,0x00,0x00,0x3f,0xf3,0xfc,0x07,0xf8
,0x00,0x00,0x1f,0xf0,0x7f,0x0f,0xc0
,0x00,0x00,0x0f,0xe0,0x7f,0xff,0xe0
,0x00,0x00,0x07,0xc0,0xff,0xff,0xe0
,0x00,0x00,0x00,0x00,0x7f,0xff,0xe0
,0x00,0x00,0x00,0x00,0x3f,0xff,0x80
,0x00,0x00,0x00,0x00,0x1f,0xbf,0x00
,0x00,0x00,0x00,0x00,0x03,0x18,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
#define Wifi_connected_width 63
#define Wifi_connected_height 49
const uint8_t PROGMEM Wifi_connected_bits[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x03,0xff,0xff,0x80,0x00,0x00
,0x00,0x00,0x3f,0xff,0xff,0xf8,0x00,0x00
,0x00,0x01,0xff,0xff,0xff,0xff,0x00,0x00
,0x00,0x0f,0xff,0xff,0xff,0xff,0xe0,0x00
,0x00,0x3f,0xff,0xc0,0x07,0xff,0xf8,0x00
,0x00,0xff,0xf8,0x00,0x00,0x3f,0xfe,0x00
,0x03,0xff,0x80,0x00,0x00,0x03,0xff,0x80
,0x07,0xfe,0x00,0x00,0x00,0x00,0xff,0xc0
,0x1f,0xf8,0x00,0x00,0x00,0x00,0x3f,0xf0
,0x3f,0xe0,0x01,0xff,0xff,0x00,0x0f,0xf8
,0x7f,0x80,0x0f,0xff,0xff,0xe0,0x03,0xfc
,0xff,0x00,0x7f,0xff,0xff,0xfc,0x01,0xfe
,0xfc,0x01,0xff,0xff,0xff,0xff,0x00,0x7e
,0x78,0x07,0xff,0xc0,0x07,0xff,0xc0,0x3c
,0x00,0x0f,0xfc,0x00,0x00,0x7f,0xe0,0x00
,0x00,0x1f,0xf0,0x00,0x00,0x1f,0xf0,0x00
,0x00,0x3f,0xc0,0x00,0x00,0x07,0xf8,0x00
,0x00,0x7f,0x00,0x01,0x00,0x01,0xfc,0x00
,0x00,0x7e,0x00,0x7f,0xfc,0x00,0xfc,0x00
,0x00,0x3c,0x03,0xff,0xff,0x80,0x78,0x00
,0x00,0x00,0x07,0xff,0xff,0xc0,0x00,0x00
,0x00,0x00,0x1f,0xff,0xff,0xf0,0x00,0x00
,0x00,0x00,0x3f,0xf0,0x1f,0xf8,0x00,0x00
,0x00,0x00,0x3f,0x80,0x03,0xf8,0x00,0x00
,0x00,0x00,0x3f,0x00,0x01,0xf8,0x00,0x00
,0x00,0x00,0x1c,0x00,0x00,0x70,0x00,0x00
,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x0f,0xe0,0x00,0x00,0x00
,0x00,0x00,0x00,0x1f,0xf0,0x00,0x00,0x00
,0x00,0x00,0x00,0x3f,0xf8,0x00,0x00,0x00
,0x00,0x00,0x00,0x3f,0xf8,0x00,0x00,0x00
,0x00,0x00,0x00,0x3f,0xf8,0x00,0x00,0x00
,0x00,0x00,0x00,0x3f,0xf8,0x00,0x00,0x00
,0x00,0x00,0x00,0x1f,0xf0,0x00,0x00,0x00
,0x00,0x00,0x00,0x0f,0xe0,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

//*******************************************************************************************************************

void setup() {

Serial.begin(115200);

//-----------Connect wifi-------------

connectToWiFi();

//---------------------------------------------

// set the data rate for the sensor serial port
finger.begin(57600);
Serial.println("\n\nAdafruit finger detect test");

if (finger.verifyPassword()) {
Serial.println("Found fingerprint sensor!");
} else {
Serial.println("Did not find fingerprint sensor :(");
while (1) { delay(1); }
}
//---------------------------------------------

finger.getTemplateCount();
Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
Serial.println("Waiting for valid finger...");
}
//************************************************************************
void loop() {

//check if there's a connection to WiFi or not
if(WiFi.status() != WL_CONNECTED){
connectToWiFi();
}
//---------------------------------------------
//If there no fingerprint has been scanned return -1 or -2 if there an error or 0 if there nothing, The ID start form 1 to 127
FingerID = getFingerprintID(); // Get the Fingerprint ID from the Scanner
delay(50); //don't need to run this at full speed.

//---------------------------------------------

DisplayFingerprintID();

//---------------------------------------------

//ChecktoAddID();

//---------------------------------------------

//ChecktoDeleteID();

//---------------------------------------------
}
//************Display the fingerprint ID state on the OLED*************
void DisplayFingerprintID(){
//Fingerprint has been detected
if (FingerID > 0){
SendFingerprintID( FingerID ); // Send the Fingerprint ID to the website.
}
//---------------------------------------------
//No finger detected
else if (FingerID == 0){
//Serial.println("No finger found");
}
//---------------------------------------------
//Didn't find a match
else if (FingerID == -1){
//Serial.println("Finger not match");
}
//---------------------------------------------
//Didn't find the scanner or there an error
else if (FingerID == -2){
//Serial.println("Didn't find the scanner");
}
}
//************send the fingerprint ID to the website*************
void SendFingerprintID( int finger ){

HTTPClient http; //Declare object of class HTTPClient
//Post Data
postData = "FingerID=" + String(finger); // Add the Fingerprint ID to the Post array in order to send it
// Post method

http.begin(link); //initiate HTTP request, put your Website URL or Your Computer IP
http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //Specify content-type header

int httpCode = http.POST(postData); //Send the request
String payload = http.getString(); //Get the response payload

Serial.println(httpCode); //Print HTTP return code
Serial.println(payload); //Print request response payload
Serial.println(postData); //Post Data
Serial.println(finger); //Print fingerprint ID

if (payload.substring(0, 5) == "login") {
String user_name = payload.substring(5);
Serial.println(user_name);
}
else if (payload.substring(0, 6) == "logout") {
String user_name = payload.substring(6);
Serial.println(user_name);
}
delay(1000);

postData = "";
http.end(); //Close connection
}
//********************Get the Fingerprint ID******************
int getFingerprintID() {
uint8_t p = finger.getImage();
switch (p) {
case FINGERPRINT_OK:
//Serial.println("Image taken");
break;
case FINGERPRINT_NOFINGER:
//Serial.println("No finger detected");
return 0;
case FINGERPRINT_PACKETRECIEVEERR:
//Serial.println("Communication error");
return -2;
case FINGERPRINT_IMAGEFAIL:
//Serial.println("Imaging error");
return -2;
default:
//Serial.println("Unknown error");
return -2;
}
// OK success!
p = finger.image2Tz();
switch (p) {
case FINGERPRINT_OK:
//Serial.println("Image converted");
break;
case FINGERPRINT_IMAGEMESS:
//Serial.println("Image too messy");
return -1;
case FINGERPRINT_PACKETRECIEVEERR:
//Serial.println("Communication error");
return -2;
case FINGERPRINT_FEATUREFAIL:
//Serial.println("Could not find fingerprint features");
return -2;
case FINGERPRINT_INVALIDIMAGE:
//Serial.println("Could not find fingerprint features");
return -2;
default:
//Serial.println("Unknown error");
return -2;
}
// OK converted!
p = finger.fingerFastSearch();
if (p == FINGERPRINT_OK) {
//Serial.println("Found a print match!");
} else if (p == FINGERPRINT_PACKETRECIEVEERR) {
//Serial.println("Communication error");
return -2;
} else if (p == FINGERPRINT_NOTFOUND) {
//Serial.println("Did not find a match");
return -1;
} else {
//Serial.println("Unknown error");
return -2;
}
// found a match!
//Serial.print("Found ID #"); Serial.print(finger.fingerID);
//Serial.print(" with confidence of "); Serial.println(finger.confidence);

return finger.fingerID;
}
//******************Check if there a Fingerprint ID to delete******************
void ChecktoDeleteID(){

HTTPClient http; //Declare object of class HTTPClient
//Post Data
postData = "DeleteID=check"; // Add the Fingerprint ID to the Post array in order to send it
// Post methode

http.begin(link); //initiate HTTP request, put your Website URL or Your Computer IP
http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //Specify content-type header

int httpCode = http.POST(postData); //Send the request
String payload = http.getString(); //Get the response payload

if (payload.substring(0, 6) == "del-id") {
String del_id = payload.substring(6);
Serial.println(del_id);
deleteFingerprint( del_id.toInt() );
}

http.end(); //Close connection
}
//******************Delete Finpgerprint ID*****************
uint8_t deleteFingerprint( int id) {
uint8_t p = -1;

p = finger.deleteModel(id);

if (p == FINGERPRINT_OK) {
Serial.println("Deleted!");
} else if (p == FINGERPRINT_PACKETRECIEVEERR) {
Serial.println("Communication error");
return p;
} else if (p == FINGERPRINT_BADLOCATION) {
Serial.println("Could not delete in that location");
return p;
} else if (p == FINGERPRINT_FLASHERR) {
Serial.println("Error writing to flash");
return p;
} else {
Serial.print("Unknown error: 0x"); 
Serial.println(p, HEX);
return p;
}
}
//******************Check if there a Fingerprint ID to add******************
void ChecktoAddID(){

HTTPClient http; //Declare object of class HTTPClient
//Post Data
postData = "Get_Fingerid=get_id"; // Add the Fingerprint ID to the Post array in order to send it
// Post methode

http.begin(link); //initiate HTTP request, put your Website URL or Your Computer IP
http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //Specify content-type header

int httpCode = http.POST(postData); //Send the request
String payload = http.getString(); //Get the response payload

if (payload.substring(0, 6) == "add-id") {
String add_id = payload.substring(6);
Serial.println(add_id);
id = add_id.toInt();
getFingerprintEnroll();
}
http.end(); //Close connection
}
//******************Enroll a Finpgerprint ID*****************
uint8_t getFingerprintEnroll() {

int p = -1;
while (p != FINGERPRINT_OK) {
p = finger.getImage();
switch (p) {
case FINGERPRINT_OK:
//Serial.println("Image taken");
break;
case FINGERPRINT_NOFINGER:
//Serial.println(".");
break;
case FINGERPRINT_PACKETRECIEVEERR:
break;
case FINGERPRINT_IMAGEFAIL:
Serial.println("Imaging error");
break;
default:
Serial.println("Unknown error");
break;
}
}

// OK success!

p = finger.image2Tz(1);
switch (p) {
case FINGERPRINT_OK:
break;
case FINGERPRINT_IMAGEMESS:
return p;
case FINGERPRINT_PACKETRECIEVEERR:
Serial.println("Communication error");
return p;
case FINGERPRINT_FEATUREFAIL:
Serial.println("Could not find fingerprint features");
return p;
case FINGERPRINT_INVALIDIMAGE:
Serial.println("Could not find fingerprint features");
return p;
default:
Serial.println("Unknown error");
return p;
}

//Serial.println("Remove finger");
delay(2000);
p = 0;
while (p != FINGERPRINT_NOFINGER) {
p = finger.getImage();
}
Serial.print("ID "); Serial.println(id);
p = -1;
while (p != FINGERPRINT_OK) {
p = finger.getImage();
switch (p) {
case FINGERPRINT_OK:
//Serial.println("Image taken");
break;
case FINGERPRINT_NOFINGER:
//Serial.println(".");
break;
case FINGERPRINT_PACKETRECIEVEERR:
Serial.println("Communication error");
break;
case FINGERPRINT_IMAGEFAIL:
Serial.println("Imaging error");
break;
default:
Serial.println("Unknown error");
break;
}
}

// OK success!

p = finger.image2Tz(2);
switch (p) {
case FINGERPRINT_OK:
//Serial.println("Image converted");
break;
case FINGERPRINT_IMAGEMESS:
Serial.println("Image too messy");
return p;
case FINGERPRINT_PACKETRECIEVEERR:
Serial.println("Communication error");
return p;
case FINGERPRINT_FEATUREFAIL:
Serial.println("Could not find fingerprint features");
return p;
case FINGERPRINT_INVALIDIMAGE:
Serial.println("Could not find fingerprint features");
return p;
default:
Serial.println("Unknown error");
return p;
}

// OK converted!
Serial.print("Creating model for #"); Serial.println(id);

p = finger.createModel();
if (p == FINGERPRINT_OK) {
//Serial.println("Prints matched!");
} else if (p == FINGERPRINT_PACKETRECIEVEERR) {
Serial.println("Communication error");
return p;
} else if (p == FINGERPRINT_ENROLLMISMATCH) {
Serial.println("Fingerprints did not match");
return p;
} else {
Serial.println("Unknown error");
return p;
}

Serial.print("ID "); 
Serial.println(id);
p = finger.storeModel(id);
if (p == FINGERPRINT_OK) {
//Serial.println("Stored!");
confirmAdding();
} else if (p == FINGERPRINT_PACKETRECIEVEERR) {
Serial.println("Communication error");
return p;
} else if (p == FINGERPRINT_BADLOCATION) {
Serial.println("Could not store in that location");
return p;
} else if (p == FINGERPRINT_FLASHERR) {
Serial.println("Error writing to flash");
return p;
} else {
Serial.println("Unknown error");
return p;
}
}
//******************Check if there a Fingerprint ID to add******************
void confirmAdding(){

HTTPClient http; //Declare object of class HTTPClient
//Post Data
postData = "confirm_id=" + String(id); // Add the Fingerprint ID to the Post array in order to send it
// Post methode

http.begin(link); //initiate HTTP request, put your Website URL or Your Computer IP
http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //Specify content-type header

int httpCode = http.POST(postData); //Send the request
String payload = http.getString(); //Get the response payload

delay(1000);
Serial.println(payload);

http.end(); //Close connection
}
//********************connect to the WiFi******************
void connectToWiFi(){
WiFi.mode(WIFI_OFF); //Prevents reconnection issue (taking too long to connect)
delay(1000);
WiFi.mode(WIFI_STA);
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("Connected");

Serial.print("IP address: ");
Serial.println(WiFi.localIP()); //IP address assigned to your ESP

}
