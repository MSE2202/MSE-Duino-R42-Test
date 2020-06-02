


//#include <WiFi.h>
#include <ESPAsyncWebServer.h>


bool btWS_Fellover = true;

// Replace with your network credentials
const char *ssid = "BaseC2";
const char *password = "12345678";  //must be 8 characters long


IPAddress local_ip(192,168,128,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

AsyncWebServer server(80);

 
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

 <head>
  <meta charset="utf-8">
  <title>Wifi Debug R1</title>
  <link rel="shortcut icon" href="#"/>
 </head>



<style>
:root {
  --main-bg-color: gray;
  
}
html {
  margin: 0;
  padding: 0;
  
}

body{ 
    width: 80%;
    margin: 0 auto;
    <!---font: 100% Arial, Helvetica, sans-serif;--->
    padding: 1em 1em;
    background: white;
    
    }
.form input {
    position: absolute;
    left: -9999px;
}


.Setup{
  position:absolute;
  
  top:1%;
  left:10%;
  height:80%;
  width:80%;
  background:white;
}


.DebugOn{
  position:absolute;
  
  top:1%;
  left:10%;
  height:5%;
  width:20%;
  background:red;
  text-align: center;
}

#DebugOn:checked + .DebugOn{
 background: green;   
}

.DebugOn:after {
     margin: 0;
    position: absolute;
    top: 50%;
    left: 50%;
    -ms-transform: translate(-50%, -50%);
    transform: translate(-50%, -50%);
    font: Arial, Helvetica, sans-serif;
  font-size: 1vmax;
    font-weight: bold;
    content: 'Debug - On';
    color: white;
}

.DebugOff{
  position:absolute;
  
  top:1%;
  left:31%;
  height:5%;
  width:20%;
  background:red;
  text-align: center;
}

#DebugOff:checked + .DebugOff{
 background: green;   
}

.DebugOff:after {
     margin: 0;
    position: absolute;
    top: 50%;
    left: 50%;
    -ms-transform: translate(-50%, -50%);
    transform: translate(-50%, -50%);
    font: Arial, Helvetica, sans-serif;
  font-size: 1vmax;
    font-weight: bold;
    content: 'Debug - Off';
    color: white;
}


.Halt{
  position:absolute;
  
  top:1%;
  left:54%;
  height:5%;
  width:20%;
  background:red;
}

#Halt:checked + .Halt{
 background: green;   
}

.Halt:after {
    margin: 0;
    position: absolute;
    top: 50%;
    left: 50%;
    -ms-transform: translate(-50%, -50%);
    transform: translate(-50%, -50%);
    
    font: Arial, Helvetica, sans-serif;
  font-size: 1vmax;
    font-weight: bold;
    content: 'Halt Mode';
    color: white;
      
}

.Continuous{
  position:absolute;
  
  top:1%;
  left:75%;
  height:5%;
  width:20%;
  background:red;
}

#Continuous:checked + .Continuous{
 background: green;   
}

.Continuous:after {
    margin: 0;
    position: absolute;
    top: 50%;
    left: 50%;
    -ms-transform: translate(-50%, -50%);
    transform: translate(-50%, -50%);
    
    font: Arial, Helvetica, sans-serif;
  font-size: 1vmax;
    font-weight: bold;
    content: 'Continuous Mode';
    color: white;
      
}


.Table1 {
  position:absolute;
  top:8%;
  left:10%;
  height:70%;
}


table, th, td {
  border: 1px solid black;
  border-collapse: collapse;
  width:95%;
  font: Arial, Helvetica, sans-serif;
  font-weight: bold;
  font-size: 1vmax;
  
  table-layout: fixed;
}
th, td {
  padding: 15px;
  text-align: left;
  
}
table#DP01 tr:nth-child(even) {
  background-color: #eee;
}
table#DP01 tr:nth-child(odd) {
 background-color: #fff;
}
table#DP01 th {
  background-color: #eeb;
  color: black;
}


.



.Datum{
  position:absolute;
  top:84%;
  left:10%;
  font: 100% Arial, Helvetica, sans-serif;
  font-weight: bold;
}




</style>

<body>
 

 <div class="form">
  <div>
    <input type="radio" onclick="sendData(1)" id="DebugOn" value="1" name="DebugOnOff" checked />
    <label class="DebugOn" for="DebugOn"></label>
  
  </div>
  <div>
    <input type="radio" onclick="sendData(0)" id="DebugOff" value="0" name="DebugOnOff" checked />
    <label class="DebugOff" for="DebugOff"></label>
  </div>

  <div>
    <input type="radio" onclick="sendData(2)" id="Halt" value="2" name="HaltContinuous" checked/>
    <label class="Halt" for="Halt"></label>
  
  </div>
  <div>
    <input type="radio" onclick="sendData(3)" id="Continuous" value="3" name="HaltContinuous" unchecked />
    <label class="Continuous" for="Continuous"></label>
  </div>
 <div>
  
  

  <div>
  <label class = "Table1">
    <table id="DP01">
      <tr>
        <th colspan="2" style= "text-align: center;">   Debug Point 1</th>
        <th colspan="2" style= "text-align: center;">   Debug Point 2</th>
        <th colspan="2" style= "text-align: center;">   Debug Point 3</th>
        <th colspan="2" style= "text-align: center;">   Debug Point 4</th>
        <th colspan="2" style= "text-align: center;">   Debug Point 5</th>
      </tr>
      <tr>
        <td>Var Name</td> 
        <td>Data</td> 
        <td>Var Name</td> 
        <td>Data</td> 
        <td>Var Name</td> 
        <td>Data</td> 
        <td>Var Name</td> 
        <td>Data</td> 
        <td>Var Name</td> 
        <td>Data</td> 
        
      </tr>
      <tr>
        <td name = WatchName style= "word-wrap:break-word;"> Watch 0,0</td>
        <td name = WatchData style= "word-wrap:break-word;">00</td>
        <td name = WatchName style= "word-wrap:break-word;"> Watch 0,1</td>
        <td name = WatchData style= "word-wrap:break-word;">00</td>
        <td name = WatchName style= "word-wrap:break-word;"> Watch 0,2</td>
        <td name = WatchData style= "word-wrap:break-word;">00</td>
        <td name = WatchName style= "word-wrap:break-word;"> Watch 0,3</td>
        <td name = WatchData style= "word-wrap:break-word;">00</td>
        <td name = WatchName style= "word-wrap:break-word;"> Watch 0,4</td>
        <td name = WatchData style= "word-wrap:break-word;">00</td>
        
        
      </tr>
      <tr>
        <td name = WatchName style= "word-wrap:break-word;">" Watch 1,0"</td>
        <td name = WatchData style= "word-wrap:break-word;">00</td>
        <td name = WatchName style= "word-wrap:break-word;">" Watch 1,1"</td>
        <td name = WatchData style= "word-wrap:break-word;">00</td>
        <td name = WatchName style= "word-wrap:break-word;">" Watch 1,2"</td>
        <td name = WatchData style= "word-wrap:break-word;">00</td>
        <td name = WatchName style= "word-wrap:break-word;">" Watch 1,3"</td>
        <td name = WatchData style= "word-wrap:break-word;">00</td>
        <td name = WatchName style= "word-wrap:break-word;">" Watch 1,4"</td>
        <td name = WatchData style= "word-wrap:break-word;">00</td>
      </tr>
      <tr>
        <td name = WatchName style= "word-wrap:break-word;">" Watch 2,0"</td>
        <td name = WatchData style= "word-wrap:break-word;">00</td>
        <td name = WatchName style= "word-wrap:break-word;">" Watch 2,1"</td>
        <td name = WatchData style= "word-wrap:break-word;">00</td>
        <td name = WatchName style= "word-wrap:break-word;">" Watch 2,2"</td>
        <td name = WatchData style= "word-wrap:break-word;">00</td>
        <td name = WatchName style= "word-wrap:break-word;">" Watch 2,3"</td>
        <td name = WatchData style= "word-wrap:break-word;">00</td>
        <td name = WatchName style= "word-wrap:break-word;">" Watch 2,4"</td>
        <td name = WatchData style= "word-wrap:break-word;">00</td>
      </tr>
      <tr>
        <td name = WatchName style= "word-wrap:break-word;">" Watch 3,0"</td>
        <td name = WatchData style= "word-wrap:break-word;">00</td>
        <td name = WatchName style= "word-wrap:break-word;">" Watch 3,1"</td>
        <td name = WatchData style= "word-wrap:break-word;">00</td>
        <td name = WatchName style= "word-wrap:break-word;">" Watch 3,2"</td>
        <td name = WatchData style= "word-wrap:break-word;">00</td>
        <td name = WatchName style= "word-wrap:break-word;">" Watch 3,3"</td>
        <td name = WatchData style= "word-wrap:break-word;">00</td>
        <td name = WatchName style= "word-wrap:break-word;">" Watch 3,4"</td>
        <td name = WatchData style= "word-wrap:break-word;">00</td>
      </tr>
      <tr>
        <td name = WatchName style= "word-wrap:break-word;">" Watch 4,0"</td>
        <td name = WatchData style= "word-wrap:break-word;">00</td>
        <td name = WatchName style= "word-wrap:break-word;">" Watch 4,1"</td>
        <td name = WatchData style= "word-wrap:break-word;">00</td>
        <td name = WatchName style= "word-wrap:break-word;">" Watch 4,2"</td>
        <td name = WatchData style= "word-wrap:break-word;">00</td>
        <td name = WatchName style= "word-wrap:break-word;">" Watch 4,3"</td>
        <td name = WatchData style= "word-wrap:break-word;">00</td>
        <td name = WatchName style= "word-wrap:break-word;">" Watch 4,4"</td>
        <td name = WatchData style= "word-wrap:break-word;">00</td>
      </tr>
    </table>  
    
    <br>
  
    <table id="DP02">
      <tr>
        <th  style= "text-align: center; background-color: red; color: white;">   Watch Chart 0</th>
        <th  style= "text-align: center; background-color: green; color: black;">   Watch Chart 1</th>
        <th  style= "text-align: center; background-color: blue; color: white;">   Watch Chart 2</th>
        <th  style= "text-align: center; background-color: yellow; color: black;">   Watch Chart 3</th>
        <th  style= "text-align: center; background-color: orange; color: black;">   Watch Chart 4</th>
        <th  style= "text-align: center; background-color: black; color: white;">   Watch Chart 5</th>
      </tr>
      <tr>
        <td name = WatchNameChart style= "word-wrap:break-word;"> Watch Name C0</td> 
        <td name = WatchNameChart style= "word-wrap:break-word;"> Watch Name C1</td> 
        <td name = WatchNameChart style= "word-wrap:break-word;"> Watch Name C2</td> 
        <td name = WatchNameChart style= "word-wrap:break-word;"> Watch Name C3</td> 
        <td name = WatchNameChart style= "word-wrap:break-word;"> Watch Name C4</td>
        <td name = WatchNameChart style= "word-wrap:break-word;"> Watch Name C5</td>        
                
      </tr>
      <tr>
        <td name = WatchChartData" id="WatchC0" style= "word-wrap:break-word;">00</td>
        <td name = WatchChartData" id="WatchC1" style= "word-wrap:break-word;">00</td>
        <td name = WatchChartData" id="WatchC2" style= "word-wrap:break-word;">00</td>
        <td name = WatchChartData" id="WatchC3" style= "word-wrap:break-word;">00</td>
        <td name = WatchChartData" id="WatchC4" style= "word-wrap:break-word;">00</td>
        <td name = WatchChartData" id="WatchC5" style= "word-wrap:break-word;">00</td>
      </tr>
      
    </table>  
    <br>
    <canvas id="myCanvas"  onclick="sendData(5)" style="border:1px solid #d3d3d3;">
        Your browser does not support the HTML5 canvas tag.
    </canvas>
  </label>    
  </div>

  <!--

  <div>
      <label class = "Datum">
     <!--  Gravity Distance <br> <span id="SensorData">--         --          --        --</span> 
      
      SensorData - Gravity: <span id="GravityMeas">0</span>
      Distance - : <span id="DistanceMeas">0</span>
       
    </label>  
  </div>
  
  <div>
  <label class = "Graph">
  <canvas id="myCanvas" width= "10" height="50" onclick="sendData(5)" style="border:1px solid #d3d3d3;">
    Your browser does not support the HTML5 canvas tag.</canvas>
   </label>
   </div>
   -->
</div>

<script>
  
 var c = document.getElementById("myCanvas");
 var ctx = c.getContext("2d");
 var XAxis =  -2;
 var XAxisPrevious =  -2;
 var XClear = 0;
 var YAxis = [0,0,0,0,0,0];
 var YAxisPrevious = [0,0,0,0,0,0];
 var canWidth = 0;
 var canHeight = 0;
 var Flipped;
 var colors = ["red",   "green",   "blue",   "yellow",   "orange", "black"];
 var ChartForCount;
 var WVN = document.getElementsByName("WatchName")
 var WVNC = document.getElementsByName("WatchNameChart")
 var WatchVarableRowIndex = 0;
 var WatchVariableColIndex = 0;
 var ids = ["0", "1", "2", "3", "4"];
 var WatchVariableNames = [
          ["Empty", "Empty", "Empty", "Empty", "Empty"],
          ["Empty", "Empty", "Empty", "Empty", "Empty"],
          ["Empty", "Empty", "Empty", "Empty", "Empty"],
          ["Empty", "Empty", "Empty", "Empty", "Empty"],
          ["Empty", "Empty", "Empty", "Empty", "Empty"]
          ];
 var WatchVariableData = [
              [0, 0, 0, 0, 0],
              [0, 0, 0, 0, 0],
              [0, 0, 0, 0, 0],
              [0, 0, 0, 0, 0],
              [0, 0, 0, 0, 0]
               ];   

var WatchVariableNamesChart = ["Empty", "Empty", "Empty", "Empty", "Empty", "Empty"];            

 var counttmr = 0;
 ctx.moveTo(0,0);
 ctx.canvas.width = window.innerWidth* 0.85;
 ctx.canvas.height = window.innerHeight* 0.3;
 canWidth = ctx.canvas.width;
 canHeight = ctx.canvas.height;
 
 //ctx.beginPath();
 for (WatchVarableRowIndex=0;WatchVarableRowIndex<5;WatchVarableRowIndex++)  
 {
   for (WatchVariableColIndex=0;WatchVariableColIndex<5;WatchVariableColIndex++)  
   { 
    //if( WVN.id = 'WVN-' + ids[i] + ','+ ids[WatchVarableRowIndex])
  WVN[WatchVarableRowIndex + (5* WatchVariableColIndex)].innerHTML = WatchVariableNames[WatchVariableColIndex][WatchVarableRowIndex];
   }
  
 } 
 
 for (WatchVarableRowIndex=0;WatchVarableRowIndex<6;WatchVarableRowIndex++)  
 {
      
  WVNC[WatchVarableRowIndex].innerHTML = WatchVariableNamesChart[WatchVarableRowIndex];
 
 }   
   
function sendData(ButtonPressed) {
  var xhttp = new XMLHttpRequest();
  
  xhttp.open("GET", "setPressedButton?StateButton="+ButtonPressed, true);
  xhttp.send();
}

 
setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getData();
}, 250); //250mSeconds update rate
 
function getData() {
  var xhttp = new XMLHttpRequest();
  var WorkingSensorData;
 
 
 counttmr = counttmr + 1;
  if(counttmr >= 100)
  { 
     counttmr = 0;  
     //document.documentElement.style.setProperty('--main-bg-color', 'blue');
   }

  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
     WorkingSensorData = (this.responseText).split(";     ");
    
      YAxis  = parseInt(WorkingSensorData[0],10);
      
      document.getElementById("GravityMeas").innerHTML = WorkingSensorData[0];
      document.getElementById("DistanceMeas").innerHTML = WorkingSensorData[1];
        
    }
  };


  xhttp.open("GET", "readSensorData", true);
  xhttp.send();

  canWidth = Math.round(window.innerWidth* 0.85);
  canHeight = Math.round(window.innerHeight* 0.3);
  if((canHeight != ctx.canvas.height) || (canWidth != ctx.canvas.width))
  {
  ctx.canvas.width = canWidth;
  ctx.canvas.height = canHeight;
  XAxis = 0;
   
  
    
  }
  
  ctx.beginPath();
  ctx.lineWidth = "5";
  ctx.strokeStyle = "white";
  ctx.moveTo((XAxis+4),0);
  ctx.lineTo((XAxis+4),(canHeight + 1));
  ctx.stroke();
  
  
 
  
  XAxisPrevious = XAxis;
  XAxis = XAxis + 1;
  
  if(XAxis > canWidth)
  {
    XAxis = -2;
    XAxisPrevious = -2;
  
   ctx.moveTo(0,YAxisPrevious[0]);
   ctx.moveTo(1,YAxisPrevious[1]);
   ctx.moveTo(2,YAxisPrevious[2]);
   ctx.moveTo(3,YAxisPrevious[3]);
   ctx.moveTo(4,YAxisPrevious[4]);
   ctx.moveTo(5,YAxisPrevious[5]);
  }
  
  
  for (ChartForCount=0;ChartForCount<6;ChartForCount++)
  {
    ctx.beginPath();
    ctx.moveTo(XAxisPrevious,YAxisPrevious[ChartForCount]);
    ctx.strokeStyle = colors[ChartForCount%colors.length];
    ctx.lineWidth = 2;  
    ctx.lineTo(XAxis,YAxis[ChartForCount]);
    YAxisPrevious[ChartForCount] = YAxis[ChartForCount];
    ctx.stroke();
  }
  
   
 
  }

</script>
</body>
</html>



)=====";



  unsigned char ucButtonState = 9;
  unsigned char ucWorkingButtonState;
  
  unsigned int uiDistance;
  double dWS_PIDInput;
  String buttonState = "0";
  
 
  String DistanceMeas = "0";
  
  String SensorData;


void setupWEbServer(void)
{
  
  Serial.print(F("Configuring access point..."));

	
  Serial.print(F("Connecting to "));
  Serial.println(ssid);
  
  WiFi.persistent(false);
  WiFi.softAP(ssid, password);
   delay(2000);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(1000);
  
  
  IPAddress myIP = WiFi.softAPIP();
  Serial.print(F("AP IP address: "));
  Serial.println(myIP);
  
  
 server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(200, "text/html", MAIN_page);
  });
    
 
  server.on("/setPressedButton", HTTP_GET, [](AsyncWebServerRequest *request)
  {
      
      AsyncWebParameter* p;
     
     if(request->hasParam("StateButton"))
       p = request->getParam("StateButton");
       // Serial.printf("GET[%s]: %s\n", p->name().c_str(), p->value().c_str());

     String t_state = p->value().c_str();//server->arg("StateButton"); //Refer  xhttp.open("GET", "setButton?StateButton="+buttonPressed, true);
     buttonState = p->value().c_str();
     
     ucButtonState = buttonState.toInt();
    
     
    request->send(200, "text/plain", buttonState); //Send web page
   
  });

    server.on("/readSensorData", HTTP_GET, [](AsyncWebServerRequest *request)
    {
     
      SensorData = String(dWS_PIDInput) + ";     " + String(uiDistance);
     
   
    request->send(200, "text/plain", SensorData); //Send ADC value only to client ajax request
   
    });
    
 
  server.begin();
  Serial.println(F("HTTP server started"));
  //digitalWrite(INDICATORLED, HIGH);

  Serial.println(F(""));
}

void loopWEBServerButtonresponce(void)
{

   

    switch(ucButtonState)
    {
      case 0:
      default:
      {
     
       Serial.println("DebugOff");
       ucWorkingButtonState = 0;
       ucButtonState = 9;
      
       
        break;
      }
      case 1:
      {
      
       Serial.println("DebugOn");
        ucButtonState = 9;
        ucWorkingButtonState = 1;
        
        break;
      }
      case 2:
      {
        
       Serial.println("Halt");
        ucButtonState = 9;
        ucWorkingButtonState = 2;
        break;
      }
      case 3:
      {
      
       Serial.println("Continuous");
       ucButtonState = 9;
       ucWorkingButtonState = 3;
        break;
      }
      case 4:
      {
       
    
       // Serial.println("Reverse");
        ucButtonState = 9;
        ucWorkingButtonState = 4;
        break;
      }
      case 5:  //toggle servo
      {
        
        ucButtonState = 9;
       
       
        break;
      }
      case 9:
      {
        
        ucButtonState = 9;
        break;
      }
    }

}
