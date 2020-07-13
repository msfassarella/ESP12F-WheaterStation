#include "Arduino.h"

String Not_Found_Page = R"=====(
<!DOCTYPE html> <html>
    <head><meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">  
     <title>ESP8266 Web Server</title>  
     <style>html { font-family: 'Open Sans', sans-serif; display: block; margin: 0px auto; text-align: center;color: #333333;}  
     body{margin-top: 50px;}  
     h1 {margin: 50px auto 30px;}  
     .side-by-side{display: inline-block;vertical-align: middle;position: relative;}  
     .humidity-icon{background-color: #3498db;width: 30px;height: 30px;border-radius: 50%;line-height: 36px;}  
     .humidity-text{font-weight: 600;padding-left: 15px;font-size: 19px;width: 160px;text-align: left;}  
     .humidity{font-weight: 300;font-size: 60px;color: #3498db;}  
     .temperature-icon{background-color: #f39c12;width: 30px;height: 30px;border-radius: 50%;line-height: 40px;}  
     .temperature-text{font-weight: 600;padding-left: 15px;font-size: 19px;width: 160px;text-align: left;}  
     .temperature{font-weight: 300;font-size: 60px;color: #f39c12;}  
     .superscript{font-size: 17px;font-weight: 600;position: absolute;right: -20px;top: 15px;}  
     .data{padding: 10px;}  
     </style>  
    
     </head>  
     <body>  

     <div id="notfoundpage">  
     
      <h1>P&Aacute;GINA N&AtildeO ENCONTRADA</h1>  
    <div>
    <svg version="1.1">
      		<linearGradient id="SVGID_1_" gradientUnits="userSpaceOnUse" x1="359.2049" y1="551.429" x2="357.9008" y2="430.1575">
			<stop  offset="0" style="stop-color:#FF0000"/>
			<stop  offset="1" style="stop-color:#D00400"/>
		</linearGradient>
		<path class="st0" d="M165.1,323.3h385.7c63.8,0,115.6,51.8,115.6,115.6v0c0,63.8-51.8,115.6-115.6,115.6H165.1
			c-63.8,0-115.6-51.8-115.6-115.6v0C49.5,375.1,101.3,323.3,165.1,323.3z"/>
		<circle class="st1" cx="165.5" cy="438.9" r="111.7"/>
		<path class="st1" d="M413.9,477.3c-0.2,5.3-1.2,10.1-3.2,14.2c-1.6,3.5-4.1,6.9-7.6,9.6c-3.5,2.8-8.3,4.4-14.7,4.4
			s-11.3-1.6-14.9-4.4c-3.5-2.7-5.8-6-7.4-9.6c-1.9-4.1-3-8.8-3.2-14.2v-76.6c0.2-5.1,1.2-9.9,3.2-14c1.6-3.5,3.9-7.1,7.4-9.7
			c3.5-2.7,8.5-4.4,14.9-4.4s11.1,1.8,14.7,4.4c3.5,2.7,6,6.2,7.6,9.7c1.9,4.1,3,8.8,3.2,14V477.3z M394.8,400.6
			c0-3.5-0.7-6-2.4-8.1c0,0,0,0-0.1-0.1c-0.9-0.9-2.3-1.4-3.9-1.4c-3.4,0-5,2.5-5.7,4.8c-0.5,1.4-0.7,3-0.7,4.8v76.6
			c0,3.7,0.9,6.2,2.7,8.1c0.9,0.9,2.1,1.4,3.7,1.4c3.4,0,4.9-2.1,5.7-4.7c0,0,0,0,0-0.1c0.5-1.2,0.7-2.8,0.7-4.8V400.6z"/>
		<path class="st1" d="M471.7,393.5h-25.2c-0.3,0-0.6,0.3-0.6,0.6v32.9c0,0.3,0.3,0.6,0.6,0.6H463c0.3,0,0.6,0.3,0.6,0.6v18.4
			c0,0.3-0.3,0.6-0.6,0.6h-16.5c-0.3,0-0.6,0.3-0.6,0.6v55.4c0,0.3-0.3,0.6-0.6,0.6h-17.9c-0.3,0-0.6-0.3-0.6-0.6V374.5
			c0-0.3,0.3-0.6,0.6-0.6h44.3c0.3,0,0.6,0.3,0.6,0.6v18.4C472.3,393.3,472,393.5,471.7,393.5z"/>
		<path class="st1" d="M524.9,393.5h-25.2c-0.3,0-0.6,0.3-0.6,0.6v32.9c0,0.3,0.3,0.6,0.6,0.6h16.5c0.3,0,0.6,0.3,0.6,0.6v18.4
			c0,0.3-0.3,0.6-0.6,0.6h-16.5c-0.3,0-0.6,0.3-0.6,0.6v55.4c0,0.3-0.3,0.6-0.6,0.6h-17.9c-0.3,0-0.6-0.3-0.6-0.6V374.5
			c0-0.3,0.3-0.6,0.6-0.6h44.3c0.3,0,0.6,0.3,0.6,0.6v18.4C525.5,393.3,525.3,393.5,524.9,393.5z"/>
      <\svg version="1.1">
      <\div>
     </body>  
     </html>  
	 )=====";
