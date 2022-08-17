#include <ESP8266WiFi.h>

 

const char* ssid = "Pondus 2";    //  Your Wi-Fi Name

const char* password = "Ponduspondus8";   // Wi-Fi Password

 

int LED = LED_BUILTIN;   // led connected to GPIO2 (D4)

WiFiServer server(80);

 

void setup()

{

  Serial.begin(115200); //Default Baudrate

  pinMode(LED, OUTPUT);

  digitalWrite(LED, LOW);

 

  Serial.print("Connecting to the Newtork");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)

  {

    delay(500);

    Serial.print(".");

  }

  Serial.println("WiFi connected"); 

  server.begin();  // Starts the Server

  Serial.println("Server started");

 

  Serial.print("IP Address of network: "); // will IP address on Serial Monitor

  Serial.println(WiFi.localIP());

  Serial.print("Copy and paste the following URL: https://"); // Will print IP address in URL format

  Serial.print(WiFi.localIP());

  Serial.println("/");

}

 

void loop()

{

  WiFiClient client = server.available();

  if (!client)

  {

    return;

  }

  Serial.println("Waiting for new client");

  while(!client.available())

  {

    delay(1);

  }

 

  String request = client.readStringUntil('\r');

  Serial.println(request);

  client.flush();
 

  int value = LOW;

  // TOP - BOTTOM
  // 0 = Off
  // 1 = Left
  // 2 = Right

  
  if(request.indexOf("/STATUS=1") != -1) {
    digitalWrite(LED, HIGH); // Turn LED ON
    value = HIGH;
  } else if () {
    
  }

  if(request.indexOf("/LED=OFF") != -1)

  {

    digitalWrite(LED, LOW); // Turn LED OFF

    value = LOW;

  }

 

//*------------------HTML Page Code---------------------*//

 

  client.println("HTTP/1.1 200 OK"); //

  client.println("Content-Type: text/html");

  client.println("");

  client.println("<!DOCTYPE HTML>");

  client.println("<html>");

 

  client.print(" CONTROL LED: ");

 

  if(value == LOW)

  {

    client.print("ON");

  }

  else

  {

    client.print("OFF");

  }

  client.println("<br><br>");

  client.println("<a href=\"/LED=OFF\"\"><button>ON</button></a>");

  client.println("<a href=\"/LED=ON\"\"><button>OFF</button></a><br />");

  client.println("</html>");

 

  delay(1);

  Serial.println("Client disonnected");

  Serial.println("");

}
