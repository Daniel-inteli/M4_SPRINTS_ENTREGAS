#define SDA_PIN 9
#define SCL_PIN 10
#include <WiFi.h>
#include <WebServer.h>
#include <LiquidCrystal_I2C.h>

int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

const char* ssid = "SHARE-RESIDENTE";
const char* password = "Share@residente";

WebServer server(80);

void jogador1(){ 
  server.send(200);
  delay(1000);
  Serial.println("aeeeee");
  lcd.setCursor(0, 0); 
  lcd.print("Jogador 1 ganhou");
  delay(5000);
  lcd.clear();
   

}

void jogador2(){ 
  server.send(200); 
  delay(1000);
  Serial.println("aeeeee");
  lcd.setCursor(0,1);
  lcd.print("jogador 2 ganhou");
  delay(5000);
  lcd.clear();
  
  
}

void setup() { 
  Serial.begin(115200);
  Serial.print("Connecting to "); 
  Serial.println(ssid);  
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.on("/jogador1", jogador1);
  server.on("/jogador2", jogador2);

  server.begin();

  Wire.begin(SDA_PIN, SCL_PIN);
  lcd.init();
  
  lcd.backlight();

}


void loop() {
  server.handleClient();
}
