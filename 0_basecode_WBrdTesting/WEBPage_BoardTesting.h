/*
//Western Engineering base code 
March 21,2020
  
\WEB Page code for Board Testing


*/

#ifndef BOARDTESTINGWEBPAGE_H
#define BOARDTESTINGWEBPAGE_H 1

 
const char BoardTesting_page[] PROGMEM = R"=====(
<!DOCTYPE html>

<head>
    <meta charset="utf-8">
    <title>MSE-Duino Board Testing</title>
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



.ContinuePB{
  position:absolute;
  
  top:1%;
  left:75%;
  height:5%;
  width:10%;
  background:red;
  text-align: center;
}

#ContinuePB:checked + .ContinuePB{
 background: green;   
}

.ContinuePB:after {
     margin: 0;
    position: absolute;
    top: 50%;
    left: 50%;
    -ms-transform: translate(-50%, -50%);
    transform: translate(-50%, -50%);
    font: Arial, Helvetica, sans-serif;
  font-size: 1vmax;
    font-weight: bold;
    content: 'Continue';
    color: white;
}

.BackPB{
  position:absolute;
  
  top:10%;
  left:75%;
  height:5%;
  width:10%;
  background:red;
  text-align: center;
}

#BackPB:checked + .BackPB{
 background: green;   
}

.BackPB:after {
     margin: 0;
    position: absolute;
    top: 50%;
    left: 50%;
    -ms-transform: translate(-50%, -50%);
    transform: translate(-50%, -50%);
    font: Arial, Helvetica, sans-serif;
  font-size: 1vmax;
    font-weight: bold;
    content: 'Back';
    color: white;
}

.SkipPB{
  position:absolute;
  
  top:20%;
  left:75%;
  height:5%;
  width:10%;
  background:red;
  text-align: center;
}

#SkipPB:checked + .SkipPB{
 background: green;   
}



.SkipPB:after {
     margin: 0;
    position: absolute;
    top: 50%;
    left: 50%;
    -ms-transform: translate(-50%, -50%);
    transform: translate(-50%, -50%);
    font: Arial, Helvetica, sans-serif;
  font-size: 1vmax;
    font-weight: bold;
    content: 'Skip';
    color: white;
}

.MainReturn{
  position:absolute;
 
  top:30%;
  left:75%;
  height:5%;
  width:10%;
  background-color: yellow;
 
}
.MainReturn:after {
    margin: 0;
    position: absolute;
    top: 50%;
    left: 50%;
    -ms-transform: translate(-50%, -50%);
    transform: translate(-50%, -50%);
    
   font: Arial, Helvetica, sans-serif;
  font-size: 1vmax;
  font-weight: bold;
  content: 'Main';
  color: black;
 }
  
.Table1 {
  position:absolute;
  top:40%;
  left:65%;
  width:30%;
}



   


</style>


<body>
    <canvas id='c' >
    </canvas>


	<div class="form">
	
	  <div>
		<input type="radio" onclick="sendData(0)" id="ContinuePB" value="0" name="ContinuePB" checked />
		<label class="ContinuePB" for="ContinuePB"></label>
	  
	  </div>
	  
	  <div>
		<input type="radio" onclick="sendData(1)" id="BackPB" value="1" name="BackPB" checked />
		<label class="BackPB" for="BackPB"></label>
	  </div>
	  
	  <div>
		<input type="radio" onclick="sendData(2)" id="SkipPB" value="1" name="SkipPB" checked />
		<label class="SkipPB" for="SkipPB"></label>
	  </div>

	 
	   <div>
		<input type="radio" onclick="sendData(3)" id="MainReturn" value="7" name="MainReturn" checked />
		<label class="MainReturn" for="MainReturn"></label>
	  </div>
    
	 <label class = "Table1">
      <table id="table" onclick="sendData(4)" >
       <tr>
          
        <td id = "Instructions" style= "word-wrap:break-word; white-space:pre-wrap"> Empty</td>
       </tr>
      </table> 
     </label>

	 </div>

   



    <script>
	  
    var img = new Image();
    
	var vRecX = 0;
	var vRecY = 0;
	var vRecW = 0;
	var vRecL = 0;
  
    var htmlCanvas = document.getElementById('c');
        // Obtain a graphics context on the canvas element for drawing.
    var context = htmlCanvas.getContext('2d');

    var vInstructions = [];  
	var vInstructionsIndex = 0; 
/*	   
	var connection = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);

	connection.onopen = function () {
	  connection.send('Connect ' + new Date());
	  sendData(6);   //load graph/chart with names for debugging
	  
	};
	connection.onerror = function (error) { console.log('WebSocket Error ', error);};
	connection.onmessage = function (e) { onMessage(e)};
	connection.onclose = function () { console.log('WebSocket connection closed');};
*/

    
    initialize();
	
	

// Called when a message is received from the server
function onMessage(e) 
{
 
    // Print out our received message
    console.log("Received: " + e.data);
    vWorkingData = (e.data).split(";");
   if(vWorkingData[0] == "N#^")  //variable names so load charts/tables
   {
    getNames();
   }
   if(vWorkingData[0] == "V#^")  //Variable data , put in chart/table
   {
    WatchCommandIndex = 0;
    WatchVariableIndex = 0;
    getData();
   }
}
 
// Start listening to resize events and draw canvas.
    function initialize() 
	{
           // Register an event listener to call the resizeCanvas() function 
           // each time the window is resized.
        window.addEventListener('resize', resizeCanvas, false);
           // Draw canvas border for the first time.
        resizeCanvas();
		
		 vInstructions[0] = "Welcome to the MSE_Duimo test page.<br/><br/>Press 'Continue' to proceed to next instruction, 'Back' to go to last instructions,  'Skip' to jump to next test or 'Main' to exit.<br/><br/>First test is to check your Smart LEDS.";
		document.getElementById("Instructions").innerHTML = vInstructions[vInstructionsIndex];
    }

        // Display custom canvas. In this case it's a blue, 5 pixel 
        // border that resizes along with the browser window.
    function redraw() 
	{
      
		context.drawImage(img, 
        0, 0, img.width, img.height, 
        0, 0, htmlCanvas.width, htmlCanvas.height
        );	 
		LoadInstructions();
		PrintInstructions();
		DrawRec();
		
        	
		
	}

        // Runs each time the DOM window resize event fires.
        // Resets the canvas dimensions to match window,
        // then draws the new borders accordingly.
    function resizeCanvas()
	{
	    htmlCanvas.height = window.innerHeight * 0.9;
		htmlCanvas.width = htmlCanvas.height * 0.676;  //window.innerWidth;
        if(htmlCanvas.width > window.innerWidth * 0.50)
		{
		   htmlCanvas.width = window.innerWidth * 0.5; 
		   htmlCanvas.height = htmlCanvas.width * 1.33;
		}
			
        redraw();
		
			 
    }
    window.onload = function()
	{
        
        // Obtain a reference to the canvas element using its id.
		 context.drawImage(img, 
        0, 0, img.width, img.height, 
        0, 0, htmlCanvas.width, htmlCanvas.height
        );
       

    };
	function sendData(ButtonPressed)
	{

	  //To send data to server

	  switch(ButtonPressed)
	  {
		case 0:   //Continue on button pressed
		{
		  //connection.send("C"); 
		  vInstructionsIndex = vInstructionsIndex + 1;
		  LoadInstructions();
		  redraw(); 
		   
		  break;
		}
		case 1:  //Back button pressed
		{
		  if(vInstructionsIndex != 0)
		  {
		    vInstructionsIndex = vInstructionsIndex - 1;
			LoadInstructions();
		  redraw(); 
		  }
		  else
		  {
		    vInstructionsIndex = 0;
		  }
		  
		  //connection.send("B");
		   
		  break;
		}
		case 2:  //Skip button pressed
		{
		  //connection.send("S");
		   
		  break;
		}
		case 3:   //Main button pressed
		{
		  location.replace("/")
		  break;
		}
	   
	  }
	 
	 
	}
	function percentToPxHor(intPx)
	{
      return intPx * canvas.width / 100;
	}
   
    function DrawRec()
	{
	  context.beginPath();
	  context.lineWidth = "4";
	  context.strokeStyle = "yellow";
	  context.rect(vRecX, vRecY,vRecW, vRecL);
	  context.stroke();
	
	}
	
	function PrintInstructions()
	{
	  document.getElementById("Instructions").innerHTML = vInstructions[vInstructionsIndex];
	}
    
	function percentToPxVert(intPx)
	{
		return intPx * canvas.height / 100;
	}
    function LoadInstructions()
	{
	  switch(vInstructionsIndex)
	  {
		case 0:   
		{
		 
		  vRecX = 0;
		  vRecY = 0;
		  vRecW = 0;
		  vRecL = 0;
		  
		   
		  break;
		}
		case 1:   
		{
		
		 vRecX = htmlCanvas.width * 0.7;
		 vRecY = htmlCanvas.height * 0.55;
		 vRecW = htmlCanvas.width * 0.1;
		 vRecL = htmlCanvas.height * 0.05;
		 	   
		  break;
		}
	  }
	}	
//Instructions Strings
    vInstructions[1] = "Smart LED test.<br/><br/> Connect shorting jumper acrossed JP5";


//convert file at https://base64.guru/converter/encode/image
//using output format DataURI -- data:content/type;base64
//img.src = 


img.src =
"data:image/jpeg;base64,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";



    </script>
</body> 
</html>

       
    }
    window.onload = function()
  {
        
        // Obtain a reference to the canvas element using its id.
     context.drawImage(img, 
        0, 0, img.width, img.height, 
        0, 0, htmlCanvas.width, htmlCanvas.height
        );
       

    };
  

)=====";

















#endif