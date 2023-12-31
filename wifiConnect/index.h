const char *INDEX_HTML = R"=====(
      <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>Plant Communicator</title>
            <style>
                body {
                    font-family: Arial, sans-serif;
                    text-align: center;
                }
                
                .container {
                    display: flex;
                    flex-wrap: wrap;
                    justify-content: center;
                    align-items: center;
                    margin: 20px;
                    padding: 20px;
                    
                }
                
                .sensor-info {
                    border: 2px solid #333;
                    padding: 10px;
                    margin: 20px;
                    text-align: center;
                    flex: 1;
                    height: 20rem;
                }       
                
                
                .temperature {
                    /* color: red; */
                    background-image: url("https://cdn.midjourney.com/e523ed77-0dcd-41d2-ab71-9884c97c4d96/0_2.png");
                    background-size: cover;
                    background-position: center;
                }
                
                .moisture {
                    /* color: blue; */
                    background-image: url("https://cdn.midjourney.com/3068c732-2eca-44f0-9788-840b308629b4/0_3.png");
                    background-size: cover;
                    background-position: center;
                }
                
                .light {
                    /* color: yellow; */
                    background-image: url("https://cdn.midjourney.com/2764ece8-0ba3-4b54-aa1c-347c69d1f90a/0_3.png");
                    background-size: cover;
                    background-position: center;
                }

                .sensorContent {
                    
                    background-color: rgba(255, 255, 255, 0.7);
                    border-radius: 10px;
                    margin: 1rem;
                    height: 80%;
                    padding: 20px;
                    display: flex;
                    align-items: center;
                    flex-direction: column;
                }
            </style>
        </head>
        <body>
            
            <h1>Plant Communicator</h1>
            <h2>Your plant:</h2>
            <div class="container">
                <div class="sensor-info temperature">
                    <div class="sensorContent ">
                        <h2>Temperature</h2>
                        <p><span id="tempMarker">tempMarker °C</span></p>
                    </div>
                </div>
                <div class="sensor-info moisture">
                    <div class="sensorContent ">
                        <h2>Moisture</h2>
                        <p> <span id="moistureMarker">moistureMarker</span></p>
                    </div>
                </div>
                <div class="sensor-info light" >
                    <div class="sensorContent">
                        <h2>Light</h2>
                        <p><span id="lightMarker">lightMarker</span></p>
                    </div>
                </div>
            </div>

            <script>
                const lightMarker = document.getElementById('lightMarker');
                const lightElement = document.querySelector('.light');

                if (parseInt(lightMarker.innerText) > 30) {
                lightElement.style.backgroundImage = "url('https://cdn.midjourney.com/e0984457-606e-40d3-99a3-d5782eb5d6a9/0_2.png')";
                }
            </script>
        </body>
        </html>

      )=====";