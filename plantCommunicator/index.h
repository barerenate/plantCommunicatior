const char *INDEX_HTML = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Plant Communicator</title>
    <style>
        body {
            font-family: Arial, Helvetica, sans-serif;
            background-color: #F9FEF9;
            margin: 0;
            margin-top: 50px;
        }
        
        .header {
            width: 100%;
            height: 55px;
            margin: 0;
            position: absolute;
            background-color: #7FD277;
            top: 0;
        }

        .header h1 {
            margin: 0;
            padding: 16px;
            font-size: 1.3rem;
            font-weight: 200;
        }

        .row {
            display: flex;
            flex-wrap: wrap;
            margin-left: 70px;
            margin-right: 70px;
            gap: 40px;
        }

        .column {
            display: flex;
            flex-wrap: wrap;
            flex-direction: column;
            margin-top: 40px;
            flex: 1;
        }

        .desc {
            background-color: #F8FB5F;
            border-radius: 15px;
        }

        .desc p {
            margin: 20px;
            font-weight: 200;
            text-align: left;
        }

        #status {
            background-color: #82B7B3;
            border-radius: 15px;
        }
        
        #status h3 {
            margin: 20px;
            margin-bottom: 5px;
            font-size: 1.2rem;
            font-weight: 500;
        }

        #status p {
            margin: 20px;
            margin-top: 5px;
        }
        
        .sensor-info {
            text-align: center;
            height: 350px;
            width: 250px;
            border-radius: 0 0 800px 800px / 0 0 700px 700px;
            background-color: #7FD277;
        }

        .sensor-info h2 {
            text-align: center;
            font-size: 2rem;
            font-weight: 300;
        }

        .sensorContent {
            margin-left: 25px;
            margin-top: 50px;
            width: 200px;
            height: 200px;
            background-color: rgba(255, 255, 255, 1);
            border-radius: 50%;
        }

        .sensorContent p {
            font-size: 3.5rem;
            text-align: center;
            font-weight: 500;
            padding-top: 67px;
            margin: 0;
        }
        
        .averages {
            height: 320px;
            width: 250px;
            background-color: #82B7B3;
            border-radius: 15px;
        }

        .averages h4 {
            text-align: center;
            margin: 20px 20px 0 20px;
            font-size: 1rem;
            font-weight: 400;
        }

        .averages p {
            margin: 10px 0 0 100px;
            line-height: 50px;
            text-align: center;
            width: 50px;
            height: 50px;
            background-color: #F9FEF9;
            border-radius: 360px;
        }
        
        .sensorExtraContent {
            display: none;
            position: relative;
            top: 20px;
        }


        .lightButton {
            /* bold */
            font-size: 1.5rem;
            
        }
        .lightButton:hover {
            
            font-weight: 700;
            /* background-color: rgb(202, 255, 195); */
            color: rgb(109, 155, 52);
            cursor: pointer;
        }

    </style>
</head>
<body>
    <header class="header">
        <h1>Plant Communicator</h1>
    </header>
    
    <div class="row">
    <div class="column">
        <div id="status">
            <h3>Plant status</h3>
            <p>Plant is <span id="plantStatus">alive</span></p>
            <p>wateringStatus</p>
            <p>The plant has been in the sun for sunnyMarker minutes</p>
            <p>The plant has been in the shade for shadeMarker minutes</p>
            <p>The plant has been in the dark for darknessMarker minutes</p>
        </div>
    </div>
    <div class="column">
        <div class="desc">
            <p>The plant communicator will help take care of your plant's health.
                <br> <br> 
            See how your plant is doing below!</p>
        </div>
    </div>
    </div>

    <div class="row">
    <div class="column">
        <div class="sensor-info">
            <h2>Temperature</h2>
            <div class="sensorContent">
                <p>tempMarker °C</p>
            </div>
        </div>
    </div>
    <div class="column">
        <div class="sensor-info">
            <h2>Moisture</h2>
            <div class="sensorContent">
                <p>moistureMarker</p>     
            </div>
        </div>
    </div>
    <div class="column">
        <div class="sensor-info"> 
            <h2>Light</h2>
            <div class="sensorContent">
                <p>lightMarker</p>
            </div>
        </div>
    </div>
    <div class="column">
        <div class="averages">
            <h4>Average temperature</h4>
            <p>meanMarker °C</p>
            <h4>Average moisture level</h4>
            <p>30</p>
            <h4>Average light level</h4>
            <p>100</p>
        </div>
    </div>
    </div>

    <script>
        const lightMarker = document.getElementById('lightMarker');
        const lightElement = document.querySelector('.light');
        const lightValue = parseInt(lightMarker.innerText);

        let plantHealth;

        if (lightValue < 30) {
        lightElement.style.backgroundImage = "url('https://cdn.midjourney.com/e0984457-606e-40d3-99a3-d5782eb5d6a9/0_2.png')";
        }

        

        if (lightValue > 70) {
        plantHealth = 'Excellent';
        } else if (lightValue > 50) {
        plantHealth = 'Good';
        } else if (lightValue > 30) {
        plantHealth = 'Fair';
        } else {
        plantHealth = 'Poor';
        }

        console.log(`The plant's health is ${plantHealth}.`);

        function lightButton() {
            var x = document.getElementById("lightContent");
            if (x.style.display === "none") {
            x.style.display = "block";
            } else {
            x.style.display = "none";
            }
        }
    </script>
</body>
</html>
      )=====";