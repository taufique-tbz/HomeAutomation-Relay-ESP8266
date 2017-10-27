#include <ESP8266WiFi.h>
#include <aREST.h>
#include <aREST_UI.h>

aREST_UI rest = aREST_UI();

const char* ssid = "XXX";
const char* password = "XXX";

#define LISTEN_PORT           80

WiFiServer server(LISTEN_PORT);
void setup(void)
{  
  Serial.begin(115200);
  
  rest.title("Relay Control");
  rest.button(2);
    
  rest.set_id("1");
  rest.set_name("esp8266");
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  server.begin();
  Serial.println("Server started");
  
  Serial.println(WiFi.localIP());
  
}
void loop() {
  
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client); 
}
