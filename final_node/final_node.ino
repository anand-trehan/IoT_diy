
String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
 
String html_1 = R"=====(
<!DOCTYPE html>
<html>
 <head>
 <meta name='viewport' content='width=device-width, initial-scale=1.0'/>
 <meta charset='utf-8'>
 <style>
  body {font-size:140%;}
  h2 {text-align:center; }
  #main1 {display: table; margin: auto;  padding: 0 10px 0 10px; } 
  #LED_button1 { padding:10px 10px 10px 10px; width:100%;  background-color: #50FF50; font-size: 120%;}

   #main2 {display: table; margin: auto;  padding: 0 10px 0 10px; } 
  #LED_button2 { padding:10px 10px 10px 10px; width:100%;  background-color: #50FF50; font-size: 120%;}

   #main3 {display: table; margin: auto;  padding: 0 10px 0 10px; } 
  #LED_button3 { padding:10px 10px 10px 10px; width:100%;  background-color: #50FF50; font-size: 120%;}

   #main4 {display: table; margin: auto;  padding: 0 10px 0 10px; } 
  #LED_button4 { padding:10px 10px 10px 10px; width:100%;  background-color: #50FF50; font-size: 120%;}
  
 </style>
 
<script>
    function switchLED1() 
   {
       var button_text = document.getElementById("LED_button1").value;
     if (button_text=="Turn on Automation")
     {
       document.getElementById("LED_button1").value = "Turning on Automation";
       ajaxLoad('AutoON'); 
     }
     else
     {
       document.getElementById("LED_button1").value = "Turning on Automation";
       ajaxLoad('AutoOFF');
     }
    }

    function switchLED2() 
   {
       var button_text = document.getElementById("LED_button2").value;
     if (button_text=="Turn on the Lamp")
     {
       document.getElementById("LED_button2").value = "Turning on the Lamp";
       ajaxLoad('LampON'); 
     }
     else
     {
       document.getElementById("LED_button2").value = "Turning off the Lamp";
       ajaxLoad('LampOFF');
     }
    }

    function switchLED3() 
   {
       var button_text = document.getElementById("LED_button3").value;
     if (button_text=="Turn on the Fan")
     {
       document.getElementById("LED_button3").value = "Turning on the Fan";
       ajaxLoad('FanON'); 
     }
     else
     {
       document.getElementById("LED_button3").value = "Turning off the Fan";
       ajaxLoad('FanOFF');
     }
    }

      function switchLED4() 
   {
       var button_text = document.getElementById("LED_button4").value;
     if (button_text=="Turn on the Bulb")
     {
       document.getElementById("LED_button4").value = "Turning on the Bulb";
       ajaxLoad('BulbON'); 
     }
     else
     {
       document.getElementById("LED_button4").value = "Turning off the Bulb";
       ajaxLoad('BulbOFF');
     }
    }
 
var ajaxRequest = null;
if (window.XMLHttpRequest)  { ajaxRequest =new XMLHttpRequest(); }
else                        { ajaxRequest =new ActiveXObject("Microsoft.XMLHTTP"); }
 
 
function ajaxLoad(ajaxURL)
{
  if(!ajaxRequest){ alert("AJAX is not supported."); return; }
 
  ajaxRequest.open("GET",ajaxURL,true);
  ajaxRequest.onreadystatechange = function()
  {
    if(ajaxRequest.readyState == 4 && ajaxRequest.status==200)
    {
      var ajaxResult = ajaxRequest.responseText;
      
      if      ( ajaxResult == "Automation is on" )   { document.getElementById("LED_button1").value = "Turn off Automation"; document.getElementById("reply1").innerHTML = ajaxResult; }
      else if ( ajaxResult == "Automation is off" )  { document.getElementById("LED_button1").value = "Turn on Automation"; document.getElementById("reply1").innerHTML = ajaxResult;  }

      else if      ( ajaxResult == "Lamp is on" )   { document.getElementById("LED_button2").value = "Turn off the Lamp"; document.getElementById("reply2").innerHTML = ajaxResult;  }
      
      else if ( ajaxResult == "Lamp is off" )  { document.getElementById("LED_button2").value = "Turn on the Lamp"; document.getElementById("reply2").innerHTML = ajaxResult;  }

      else if      ( ajaxResult == "Fan is on" )   { document.getElementById("LED_button3").value = "Turn off the Fan"; document.getElementById("reply3").innerHTML = ajaxResult; }
      
      else if ( ajaxResult == "Fan is off" )  { document.getElementById("LED_button3").value = "Turn on the Fan"; document.getElementById("reply3").innerHTML = ajaxResult; }

      else if      ( ajaxResult == "Bulb is on" )   { document.getElementById("LED_button4").value = "Turn off the Bulb"; document.getElementById("reply4").innerHTML = ajaxResult; }
      
      else if ( ajaxResult == "Bulb is off" )  { document.getElementById("LED_button4").value = "Turn on the Bulb"; document.getElementById("reply4").innerHTML = ajaxResult; }
      
    }
  }
  ajaxRequest.send();
}


 
</script>
 
 <title>Home Automation Prototype</title>
</head>
<body>
  <h2>Home Automation Prototype</h2>
  
 <div id='main1'>
  <input type="button" id = "LED_button1" onclick="switchLED1()" value="Turn on Automation"  /> 
  <p id = "reply1">Reply appears here</p>
 </div>

 <div id='main2'>
  <input type="button" id = "LED_button2" onclick="switchLED2()" value="Turn on the Lamp"  /> 
  <p id = "reply2">Reply appears here</p>
 </div>

 <div id='main3'>
  <input type="button" id = "LED_button3" onclick="switchLED3()" value="Turn on the Fan"  /> 
  <p id = "reply3">Reply appears here</p>
 </div>

 <div id='main4'>
  <input type="button" id = "LED_button4" onclick="switchLED4()" value="Turn on the Bulb"  /> 
  <p id = "reply4">Reply appears here</p>
 </div>
 
</body>
</html>
 
)=====";
 
 
 
#include <ESP8266WiFi.h>

#include <SoftwareSerial.h>

#include <ArduinoJson.h>

SoftwareSerial s(D6,D7);
int data1;
int data2;
int data3;
int data4;

StaticJsonBuffer<1000> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();

// change these values to match your network
char ssid[] = "Node_mcu";       //  your network SSID (name)
char pass[] = "12345678";          //  your network password
 
WiFiServer server(80);
 
 
String request = "";
int LED_Pin1 = D0;
int LED_Pin2 = D1;
int LED_Pin3 = D2;
int LED_Pin4 = D3;
 
 
void setup() 
{
    pinMode(LED_Pin1, OUTPUT); 
    pinMode(LED_Pin2, OUTPUT); 
    pinMode(LED_Pin3, OUTPUT); 
    pinMode(LED_Pin4, OUTPUT);     
 
    Serial.begin(9600);
    Serial.println();
    Serial.println("Serial started at 9600");
    Serial.println("Home Automation");
    Serial.println();
 
    // Connect to a WiFi network
    Serial.print(F("Connecting to "));  Serial.println(ssid);
    WiFi.begin(ssid, pass);
 
    while (WiFi.status() != WL_CONNECTED) 
    {
        Serial.print(".");
        delay(500);
    }
 
    Serial.println("");
    Serial.println(F("[CONNECTED]"));
    Serial.print("[IP ");              
    Serial.print(WiFi.localIP()); 
    Serial.println("]");
 
    // start a server
    server.begin();
    Serial.println("Server started");
    s.begin(9600);
} // void setup()
 
 
 
void loop() 
{
    // Check if a client has connected
    WiFiClient client = server.available();
    if (!client)  {  return;  }
 
    // Read the first line of the request
    request = client.readStringUntil('\r');
 
    Serial.print("request: "); Serial.println(request); 
 
    if       ( request.indexOf("AutoON") > 0 )  
             { 
                digitalWrite(LED_Pin1, HIGH); 
                data1=1;
                root["LED1"]=data1;
                root.printTo(s);
                
                client.print( header );
                client.print( "Automation is on" );             
             }
    else if  ( request.indexOf("AutoOFF") > 0 ) 
             { 
                digitalWrite(LED_Pin1, LOW); 
                data1=0;
                root["LED1"]=data1;
                root.printTo(s);  
                
                client.print( header );
                client.print( "Automation is off" ); 
             }
    /*else
    {
        client.flush();
        client.print( header );
        client.print( html_1 );    
        delay(5);
    }*/
  //////////
    else if       ( request.indexOf("LampON") > 0 )  
             { 
                digitalWrite(LED_Pin2, HIGH);
                data2=1;
                root["LED2"]=data2;
                root.printTo(s);  
                
                client.print( header );
                client.print( "Lamp is on" );             
             }
    else if  ( request.indexOf("LampOFF") > 0 ) 
             { 
                digitalWrite(LED_Pin2, LOW); 
                data2=0;
                root["LED2"]=data2;
                root.printTo(s);
                   
                client.print( header );
                client.print( "Lamp is off" ); 
             }
   /* else
    {
        client.flush();
        client.print( header );
        client.print( html_1 );    
        delay(5);
    }*/
  //////////////////
 else  if       ( request.indexOf("FanON") > 0 )  
             { 
                digitalWrite(LED_Pin3, HIGH); 
                data3=1;
                root["LED3"]=data3;
                root.printTo(s);  
                
                client.print( header );
                client.print( "Fan is on" );             
             }
    else if  ( request.indexOf("FanOFF") > 0 ) 
             {  
                digitalWrite(LED_Pin3, LOW);  
                data3=0;
                root["LED3"]=data3;
                root.printTo(s); 
                
                client.print( header );        
                client.print( "Fan is off" ); 
             }
    /*else
    {
        client.flush();
        client.print( header );
        client.print( html_1 );    
        delay(5);
    }*/
  //////////////////////

  else if       ( request.indexOf("BulbON") > 0 )  
             { 
                digitalWrite(LED_Pin4, HIGH);
                data4=1;
                root["LED4"]=data4;
                root.printTo(s);  
                
                client.print( header );
                client.print( "Bulb is on" );             
             }
    else if  ( request.indexOf("BulbOFF") > 0 ) 
             { 
                digitalWrite(LED_Pin4, LOW);
                data4=0;
                root["LED4"]=data4;
                root.printTo(s);
                   
                client.print( header );
                client.print( "Bulb is off" ); 
             }
    else
    {
        client.flush();
        client.print( header );
        client.print( html_1 );    
        delay(5);
    }
 //////////
 
  // The client will actually be disconnected when the function returns and 'client' object is detroyed
} // void loop()
