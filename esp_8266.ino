#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
int pushButton = D5;
int arduino1 = D7;
int arduino2 = D6;
int pulseintervalA1 =0;
int pulseintervalA2 = 0;
int laststate = 0;
int ardiuno_1_State = 0;
bool ard_1_State;
int ardiuno_2_State = 0;
bool ard_2_State;

//IPAddress    apIP(42, 42, 42, 42);  // Defining a static IP address: local & gateway
                                    // Default IP in AP mode is 192.168.4.1

/* This are the WiFi access point settings. Update them to your likin */
const char *ssid = "marvin's ESP";
const char *password = "qwerty12345";

// Define a web server at port 80 for HTTP
ESP8266WebServer server(80);

bool ledState = false;

void handleRoot() {
  bool arg;
//  bool ard_1_State;

  arg = server.arg("led") =="1";
  Serial.print("got arg =  ");
  Serial.println(arg);
  digitalWrite (D3, (arg)?LOW:HIGH);
  delay(50);
  ledState = arg;
  //digitalRead(D5);
  delay(50);
   int ledState = digitalRead(pushButton);
 
  // print out the state of the button:
  Serial.print("D5 =  ");
  Serial.println(ledState);
 
  //digitalRead(D7);
  //Serial.print("D7 =  ");
  //Serial.println(D7);
  
  if(ardiuno_1_State == 1)
  {
    Serial.println( "ARDUINO 1 ALIVE");
   
    
  }
  else
  {
    Serial.println( "ARDUINO 1 DEAD");
     Serial.println( "here");
  //  Serial.println(pulseintervalA1,DEC);
  //  Serial.println(ard_1_State);
    Serial.println( "here");
  }
// if(pulseintervalA1 >= 180 || pulseintervalA1 <= 220 )
//   {
//    ard_1_State=1;
//    pulseintervalA1=0;
//   }
// else
// {
//  ard_1_State=0;
//  pulseintervalA1=0;
// }
  
 
  //Serial.println(D5);
  
  

 /* Dynamically generate the LED toggle link, based on its current state (on or off)*/
  char ledText[80];
  
  if (ledState) {
    strcpy(ledText, "LED is ON. <a href=\"/?led=0\">Turn it OFF!</a>");
  }

  else {
    strcpy(ledText, "LED is OFF. <a href=\"/?led=1\">Turn it ON!</a>");
  }

   char ard_1_text[80];
  
  if (ard_1_State) {
    strcpy(ard_1_text, "ARDUINO 1 IS FUNCTIONING.");
  }

  else {
    strcpy(ard_1_text, "ARDUINO 1 IS NOT FUNCTIONING. ");
  }
  char ard_2_text[80];
  
  if (ard_2_State) {
    strcpy(ard_2_text, "ARDUINO 2 IS FUNCTIONING.");
  }

  else {
    strcpy(ard_2_text, "ARDUINO 2 IS NOT FUNCTIONING. ");
  }
  char ledstatetext[80];
  
  if (ledState) {
    strcpy(ledstatetext, "ACTUAL STATUS OF LED:HIGH");
  }

  else {
    strcpy(ledstatetext, "ACTUAL STATUS LED: LOW");
  }
 
  //ledState = digitalRead(D3);

  char html[1000];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  int brightness = analogRead(A0);
  brightness = (int)(brightness + 5) / 10; //converting the 0-1024 value to a (approximately) percentage value

// Build an HTML page to display on the web-server root address
  snprintf ( html, 1000,

"<html>\
  <head>\
    <meta http-equiv='refresh' content='10'/>\
    <title>ESP8266 WiFi Network</title>\
    <style>\
      body { background-color: #ffffff; font-family: Arial, Helvetica, Sans-Serif; font-size: 1.5em; Color: #000000; }\
      h1 { Color: #AA0000; }\
    </style>\
  </head>\
  <body>\
    <h1>ESP8266 LED Access Point</h1>\
    <p>Uptime: %02d:%02d:%02d</p>\
    <p>%s<p>\
    <p>%s<p>\
    <p>%s<p>\
    <h1>%s</h1>\
    <p>CHECK THE STATUS BY CLICKING  <a href=\"javascript:window.location.reload();\">HERE</a> .</p>\
    <p>This page refreshes every 10 seconds. Click <a href=\"javascript:window.location.reload();\">here</a> to refresh the page now.</p>\
  </body>\
</html>",

    hr, min % 60, sec % 60,
    ledText,
    ard_1_text,
    ard_2_text,
    ledstatetext
    
    
  );
  server.send ( 200, "text/html", html );
  //digitalWrite ( D3, 1 );
}

void handleNotFound() {
  //digitalWrite ( D3, 0 );
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  server.send ( 404, "text/plain", message );
  // digitalWrite ( D3, 1 ); //turn the built in LED on pin DO of NodeMCU off
}

void setup() {
  pinMode ( D3, OUTPUT );
  digitalWrite ( D3, 0 );
  pinMode(pushButton, INPUT);
  pinMode ( D7, INPUT_PULLUP );
   pinMode ( D6, INPUT_PULLUP );
  //digitalWrite ( D1, LOW );
  
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  //set-up the custom IP address
//  WiFi.mode(WIFI_AP_STA);
//  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00  
  
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
  server.on ( "/", handleRoot );
  server.on ( "/led=1", handleRoot);
  server.on ( "/led=0", handleRoot);
  server.on ( "/inline", []() {
    server.send ( 200, "text/plain", "this works as well" );
  } );
  server.onNotFound ( handleNotFound );
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
 
 pulseintervalA1 = pulseIn(arduino1, HIGH, 600000); //even if I leave Timeout_Duration blank, it times out after half a second
  Serial.println("pulseintervalA1=");
  Serial.println(pulseintervalA1,DEC); 
  if(pulseintervalA1 >= 90000 && pulseintervalA1 <= 120000 )
 {
    ardiuno_1_State = 1;
    Serial.println("ardiuno_1_State");
    Serial.println(ardiuno_1_State,DEC);
    ard_1_State=1;
   // pulseintervalA1=0;
 }
 else
 {
  ardiuno_1_State = 0;
   Serial.println("ardiuno_1_State");
  Serial.println(ardiuno_1_State,DEC);
  ard_1_State=0;
 // pulseintervalA1=0;
 }
pulseintervalA2 = pulseIn(arduino2, HIGH, 600000); //even if I leave Timeout_Duration blank, it times out after half a second
  Serial.println("pulseintervalA2");
  Serial.println(pulseintervalA2,DEC); 
  if(pulseintervalA2 >= 90000 && pulseintervalA2 <= 120000 )
 {
    ardiuno_2_State = 1;
    Serial.println("ardiuno_2_State");
    Serial.println(ardiuno_2_State,DEC);
    ard_2_State=1;
   // pulseintervalA1=0;
 }
 else
 {
  ardiuno_2_State = 0;
   Serial.println("ardiuno_2_State");
  Serial.println(ardiuno_2_State,DEC);
  ard_2_State=0;
 // pulseintervalA1=0;
 }
 server.handleClient();

}
