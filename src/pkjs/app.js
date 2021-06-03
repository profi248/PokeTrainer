// Import the Clay package
var Clay = require('pebble-clay');
// Load our Clay configuration file
var clayConfig = require('./config');
// Initialize Clay
var clay = new Clay(clayConfig);

//var myAPIKey = "4d9bee927cb90e201ca2ebecd322079e"; 				//mine is 692bd55bdf307693e80b7246cf0bab96 or 4d9bee927cb90e201ca2ebecd322079e


Pebble.addEventListener('webviewclosed', function (e) {
  if (e && !e.response) return;
  var dict = clay.getSettings(e.response);

  var messageKeys = require('message_keys');

  var gotAPIKey = dict[messageKeys.weatherApiKey];
  localStorage.setItem('APIKey', gotAPIKey);
  console.log("the API key is: " + gotAPIKey);
  console.log("the persistent API key is: " + localStorage.getItem("APIKey"));

}
);

var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};

function locationSuccess(pos) {
  // Construct URL
  var url = "https://api.openweathermap.org/data/2.5/weather?lat=" +
    pos.coords.latitude + "&lon=" + pos.coords.longitude + '&appid=' + localStorage.getItem("APIKey");

  // Send request to OpenWeatherMap
  xhrRequest(url, 'GET',
    function (responseText) {
      // responseText contains a JSON object with weather info
      var json = JSON.parse(responseText);

      // Temperature in Kelvin requires adjustment
      var temperature = Math.round(json.main.temp - 273.15);
      console.log("Temperature is " + temperature);

      // Conditions
      var conditions = json.weather[0].main;
      console.log("Conditions are " + conditions);

      var sunrise = json.sys.sunrise;
      console.log("Sunrise is " + sunrise);
      var sunset = json.sys.sunset;
      console.log("Sunset is " + sunset);

      // Assemble dictionary using our keys
      var dictionary = {
        "Temperature": temperature,
        "Conditions": conditions,
        "Sunrise": sunrise,
        "Sunset": sunset
      };

      // Send to Pebble
      Pebble.sendAppMessage(dictionary,
        function (e) {
          console.log("Weather info sent to Pebble successfully!");
        },
        function (e) {
          console.log("Error sending weather info to Pebble!");
        }
      );
    }
  );
}

function locationError(err) {
  console.log("Error requesting location!");
}

function getWeather() {
  navigator.geolocation.getCurrentPosition(
    locationSuccess,
    locationError,
    { timeout: 15000, maximumAge: 60000 }
  );
}

// Listen for when the watchface is opened
Pebble.addEventListener('ready',
  function (e) {
    console.log("PebbleKit JS ready!");

    // Get the initial weather
    if (localStorage.getItem("APIKey") === '') {
      console.log("(ready)No API key set");
    }
    else {
      console.log("(ready)The API key is: " + localStorage.getItem("APIKey"));
      getWeather();
    }
  }
);

// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage',
  function (e) {
    console.log("AppMessage received!");
    if (localStorage.getItem("APIKey") === '') {
      console.log("(appmessage) No API key set");
    }
    else {
      console.log("(appmessage)The API key is: " + localStorage.getItem("APIKey"));
      getWeather();
    }
  }
);

// Listen for when settings are closed
Pebble.addEventListener('webviewclosed',
  function (e) {
    console.log("AppMessage received!");
    if (localStorage.getItem("APIKey") === '') {
      console.log("(webviewclosed) No API key set");
    }
    else {
      console.log("(webviewclosed)The API key is: " + localStorage.getItem("APIKey"));
      getWeather();
    }
  }
);
