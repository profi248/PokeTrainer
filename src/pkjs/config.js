module.exports = [
  {
    "type": "heading",
    "defaultValue": "Poke Trainer Settings"
  },
  {
    "type": "text",
    "defaultValue": "Here you can configure your watchface."
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Watch Settings"
      },

      {
        "type": "toggle",
        "messageKey": "enableWeather",
        "label": "Enable Weather and Dynamic Night Mode",
        "defaultValue": false,
        "description": "If you turn it on you have to add your OpenWeatherMap API Key.<br>You will see the current weather in your location right on the watch face, and night mode will switch based on current sunset/sunrise times!<br>Else you can set a custom text."
      },

      {
        "type": "input",
        "messageKey": "weatherApiKey",
        "defaultValue": "",
        "description": "Get it here once, and for free: <a href='http://openweathermap.org/appid'>OpenWeatherMap</a>",
        "label": "OpenWeatherMap API Key",
        "attributes": {
          "placeholder": "eg: 692bd55bdf307693e80b7246cf0bab69",
          "limit": 35,
          "type": "text"
        }
      },
      {
        "type": "select",
        "messageKey": "UNITS",
        "defaultValue": "0",
        "label": "Celsius (C) or Fahrenheit (F)?",
        "description": "Choose the unit for the temperature!",
        "options": [
          {
            "label": "Celsius",
            "value": "0"
          },
          {
            "label": "Fahrenheit",
            "value": "1"
          }
        ]
      },
      {
        "type": "input",
        "messageKey": "weatherText",
        "defaultValue": "",
        "description": "Here you can choose a text to show instead of the weather! (max 12 characters)",
        "label": "Custom Text",
        "attributes": {
          "placeholder": "eg: Poke Trainer!",
          "limit": 12,
          "type": "text"
        }
      }
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Trainer Settings"
      },
      {
        "type": "select",
        "messageKey": "TRAINER",
        "defaultValue": "0",
        "label": "Are you a Boy or a Girl?",
        "options": [
          {
            "label": "Boy",
            "value": "0"
          },
          {
            "label": "Girl",
            "value": "1"
          }
        ]
      },
      {
        "type": "radiogroup",
        "messageKey": "OCCUPATION",
        "defaultValue": "0",
        "label": "What do you do for a living?",
        "options": [
          {
            "label": "Kanto Trainer!",
            "value": "0"
          },
          {
            "label": "Johto Trainer!",
            "value": "6"
          },
          {
            "label": "Hoenn Trainer!",
            "value": "7"
          },
          {
            "label": "Pokémon Ranger!",
            "value": "1"
          },
          {
            "label": "Kid!",
            "value": "2"
          },
          {
            "label": "Scientist!",
            "value": "3"
          },
          {
            "label": "Gym Leader!",
            "value": "4"
          },
          {
            "label": "Team Rocket Grunt!",
            "value": "5"
          },
          {
            "label": "Beauty!",
            "value": "8"
          },
          {
            "label": "Police Officer!",
            "value": "9"
          },
          {
            "label": "Medium!",
            "value": "10"
          },
          {
            "label": "FireBreather!",
            "value": "11"
          },
          {
            "label": "Skier!",
            "value": "12"
          }
        ]
      }
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Pokémon Settings"
      },
      {
        "type": "text",
        "defaultValue": "<font size='2'>Pokémon with evolutions will evolve based on your daily step count.<br>The ones with 3 stages will reach their final form when you conquer your average daily step count. Their first evolution will happen at half that amount.<br>Eevee will evolve *randomly* when you reach your average daily step count!</font>"
      },
      {
        "type": "radiogroup",
        "messageKey": "POKE",
        "defaultValue": "25",
        "label": "Choose your Starter!",
        "options": [
          {
            "label": "Pikachu",
            "value": "25"
          },
          {
            "label": "Bulbasaur",
            "value": "1"
          },
          {
            "label": "Charmander",
            "value": "4"
          },
          {
            "label": "Squirtle",
            "value": "7"
          },
          {
            "label": "Chikorita",
            "value": "152"
          },
          {
            "label": "Cyndaquil",
            "value": "155"
          },
          {
            "label": "Totodile",
            "value": "158"
          },
          {
            "label": "Treecko",
            "value": "252"
          },
          {
            "label": "Torchic",
            "value": "255"
          },
          {
            "label": "Mudkip",
            "value": "258"
          },
          {
            "label": "Eevee",
            "value": "133"
          },
          {
            "label": "Pidgey",
            "value": "16"
          },
          {
            "label": "Rattata",
            "value": "19"
          },
          {
            "label": "Porygon",
            "value": "137"
          },
          {
            "label": "Onix",
            "value": "95"
          },
          {
            "label": "Staryu",
            "value": "120"
          },
          {
            "label": "Zubat",
            "value": "41"
          },
          {
            "label": "Jigglypuff",
            "value": "39"
          },
          {
            "label": "Clefairy",
            "value": "35"
          },
          {
            "label": "Growlithe",
            "value": "58"
          },
          {
            "label": "Gastly",
            "value": "92"
          },
          {
            "label": "Vulpix",
            "value": "37"
          },
          {
            "label": "Seel",
            "value": "86"
          }
        ]
      }
    ]
  },
  {
    "type": "submit",
    "defaultValue": "Save"
  },
  {
    "type": "text",
    "defaultValue": "<br><a href='https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=3LKRSW9JZP8LL'>Buy Me A Coffee</a><br>Or tea. Or Vodka, who knows.<br>"
  },
  {
    "type": "text",
    "defaultValue": "Version 3.6.0"
  },
  {
    "type": "text",
    "defaultValue": "Thanks to:<br> <font size='2'>Northeastpaw, twaider, TheRedHairedHero for the help;<br>Dragoon, Dazz for the sprites;<br>Nintendo, Game Freak for Pokémon!</font><br><br>© rentsmdi 2016<br>Updated by profi248 in 2021-2022"
  }
];