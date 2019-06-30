#include <SPI.h>
#include <UIPEthernet.h> 
 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 
byte ip[] = { 192, 168, 0, 175 }; 
EthernetServer server(80); 
 
//int ledPin = 8; //PINO DIGITAL UTILIZADO PELO LED
String readString = String(30); 
int status = 0; 
int testPin = 7;
void setup(){
  Ethernet.begin(mac, ip); 
  server.begin(); 
  //pinMode(ledPin, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(testPin, OUTPUT);
  digitalWrite(testPin, LOW); 
  }
void loop(){
EthernetClient client = server.available(); 
  if (client) { 
    while (client.connected()) {
   if (client.available()) { 
    char c = client.read(); 
    if (readString.length() < 100) 
      {
        readString += c; 
      }  
        if (c == '\n') { 
          if (readString.indexOf("?") <0){ 
          }
          else 
        if(readString.indexOf("ledParam=1") >0){ 
             digitalWrite(testPin, HIGH); 
             client.println("<body style=background-color:#99ff99>"); 
             status = 1; 
           }else{ 
             digitalWrite(testPin, LOW); 
             client.println("<body style=background-color:#ff6666>"); 
             status = 0; 
           }
          client.println("HTTP/1.1 200 OK"); 
          client.println("Content-Type: text/html"); 
          client.println();
          
          client.println("<body style=background-color:#ffb366>"); 
          client.println("<center><font color='white'><h1>TRABALHO MICRO 2</font></center></h1>"); 
          client.println("<h1><center><font size='5' >CONTROLE DE LAMPADA</center></h1>"); 
          if (status == 1){ 
          client.println("<center><form method=get name=LED><input type=hidden name=ledParam value=0 /><input type=submit value=Turn_OFF></form></center>");
          }else{ 
          client.println("<center><form method=get name=LED><input type=hidden name=ledParam value=1 /><input type=submit value=Turn_ON></form></center>");
          }
          client.println("<center><font size='5'>Status da lampada: </center>"); 
          if (status == 1){ 
              client.println("<center></h1><font color='green' size='7'>ON</center>"); 
          }else{ 
              client.println("<center></h1><font color='e60000' size='7'>OFF</center>"); 
          }    
          
          client.println("</body></html>"); 
          readString=""; 
          client.stop(); 
            }
          }
        }
      }
}