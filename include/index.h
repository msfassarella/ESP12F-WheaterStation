#include "Arduino.h"

String MAIN_page = R"=====(
<!DOCTYPE html> <html>
    <head><meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">  
      <link href="https://fonts.googleapis.com/css?family=Open+Sans:300,400,600" rel="stylesheet">  
      <script src="https://code.highcharts.com/highcharts.js"></script>
     <title>ESP8266 Weather Report</title>  
     <style>
      * {
        box-sizing: border-box;
       }
     html { 
        font-family: 'Open Sans', sans-serif; 
        display: block; 
        margin: 0px auto; 
        text-align: center;
        color: #333333;
        }  

     body{
        background-color: white;
        margin-top: 50px;
     }  

     h1 {
        margin: 50px auto 30px;
        }  

      nav {
        float: left;
        width: 30%;
        height: 300px; 
        padding: 10px;
      }

      article {
        float: left;
        padding: 10px;
        width: 70%;
        background-color: #f1f1f1;
        height: 300px; 
        color: teal;
      }

     
      /* Clear floats after the columns */
      section:after {
        content: "";
        display: table;
        clear: both;
      }

      /* Style the footer */
      footer {
        background-color: #777;
        padding: 10px;
        text-align: center;
        color: white;
      }

      @media (max-width: 600px) {
        nav, article {
          width: 100%;
          height: auto;
        }
      }
     .side-by-side{
        display: inline-block;
        vertical-align: middle;
        position: relative;
      }  

     .humidity-icon{
        background-color: #3498db;
        width: 30px;
        height: 30px;
        border-radius: 50%;
        line-height: 36px;
      }  

     .humidity-text{
        font-weight: 600;
        padding-left: 15px;
        font-size: 19px;
        width: 160px;
        text-align: left;
      }  

     .humidity{
        font-weight: 300;
        font-size: 60px;
        color: #3498db;
      }  
     .temperature-icon{
        background-color: #f39c12;
        width: 30px;
        height: 30px;
        border-radius: 50%;
        line-height: 40px;
      }  
     .temperature-text{
        font-weight: 600;
        padding-left: 15px;
        font-size: 19px;
        width: 160px;
        text-align: left;
      }  
     .temperature{
        font-weight: 300;
        font-size: 60px;
        color: #f39c12;
        }  
     .superscript{
        font-size: 17px;
        font-weight: 600;
        position: absolute;
        right: -20px;
        top: 15px;
      }  
     .data{
        padding: 10px;
      }

   table {
     font-family: arial, sans-serif;
     border-collapse: collapse;
     width: 100%;
   }

   td, th {
     border: 1px solid #dddddd;
     text-align: left;
     padding: 8px;
   }

   tr:nth-child(even) {
     background-color: #dddddd;
   }  
     </style>  
    
	<script>  
    setInterval(loadDoc,15000);  
    function loadDoc() {  
    var xhttp = new XMLHttpRequest();  
    xhttp.onreadystatechange = function() {  
    if (this.readyState == 4 && this.status == 200) {  
       document.getElementById("webpage").innerHTML = this.responseText}  
    };  
    xhttp.open("GET", "/", true);  
    xhttp.send();  
    }  
    </script>  

   </head>  
   <body>  
    
      <div id="webpage">  
     
      <h2>My Environment - %HORA%</h2>  
      <section>
      <nav>
      <div class="data">  
        <div class="side-by-side temperature-icon">  
          <svg version="1.1" id="Layer_1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px"  
          width="9.915px" height="22px" viewBox="0 0 9.915 22" enable-background="new 0 0 9.915 22" xml:space="preserve">  
          <path fill="#FFFFFF" d="M3.498,0.53c0.377-0.331,0.877-0.501,1.374-0.527C5.697-0.04,6.522,0.421,6.924,1.142  
          c0.237,0.399,0.315,0.871,0.311,1.33C7.229,5.856,7.245,9.24,7.227,12.625c1.019,0.539,1.855,1.424,2.301,2.491  
          c0.491,1.163,0.518,2.514,0.062,3.693c-0.414,1.102-1.24,2.038-2.276,2.594c-1.056,0.583-2.331,0.743-3.501,0.463  
          c-1.417-0.323-2.659-1.314-3.3-2.617C0.014,18.26-0.115,17.104,0.1,16.022c0.296-1.443,1.274-2.717,2.58-3.394  
          c0.013-3.44,0-6.881,0.007-10.322C2.674,1.634,2.974,0.955,3.498,0.53z"/>  
          </svg>  
        </div>  
        <div class="side-by-side temperature-text">Temperature</div>  
        <div class="side-by-side temperature">%TEMP%<span class="superscript">&deg C</span></div>  
      </div>  
     
      <div class="data">  
       <div class="side-by-side humidity-icon">  
         <svg version="1.1" id="Layer_2" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px" \  width="12px" height="17.955px" viewBox="0 0 13 17.955" enable-background="new 0 0 13 17.955" xml:space="preserve">  
         <path fill="#FFFFFF" d="M1.819,6.217C3.139,4.064,6.5,0,6.5,0s3.363,4.064,4.681,6.217c1.793,2.926,2.133,5.05,1.571,7.057  
         c-0.438,1.574-2.264,4.681-6.252,4.681c-3.988,0-5.813-3.107-6.252-4.681C-0.313,11.267,0.026,9.143,1.819,6.217"></path>  
         </svg>  
       </div>  
       <div class="side-by-side humidity-text">Humidity</div>  
       <div class="side-by-side humidity">%HUMI%<span class="superscript">%</span></div>  
      </div>
   </nav>
   <article>
      <table>
         <tr>
           <th>Week Day</th>
           <th>Min</th>
           <th>Med</th>
           <th>Max</th>
         </tr>
         <tr>
          <th>Sunday</th>
          <th>%MIN_D0%</th>
          <th>%MED_D0%</th>
          <th>%MAX_D0%</th>
        </tr>         
         <tr>
          <th>Monday</th>
          <th>%MIN_D1%</th>
          <th>%MED_D1%</th>
          <th>%MAX_D1%</th>
        </tr>
        <tr>
          <th>Tuesday</th>
          <th>%MIN_D2%</th>
          <th>%MED_D2%</th>
          <th>%MAX_D2%</th>
        </tr>
         <tr>
          <th>Wednesday</th>
          <th>%MIN_D3%</th>
          <th>%MED_D3%</th>
          <th>%MAX_D3%</th>
        </tr>
        <tr>
          <th>Thursday</th>
          <th>%MIN_D4%</th>
          <th>%MED_D4%</th>
          <th>%MAX_D4%</th>
        </tr>
        <tr>
          <th>Friday</th>
          <th>%MIN_D5%</th>
          <th>%MED_D5%</th>
          <th>%MAX_D5%</th>
        </tr>
        <tr>
          <th>Saturday</th>
          <th>%MIN_D6%</th>
          <th>%MED_D6%</th>
          <th>%MAX_D6%</th>
       </tr>
         
       </table>
   </article>
   
   </section>
   <div id="chart-temperature" class="container"></div>
   </div>    
   </body>  
</html>
	 )=====";

	