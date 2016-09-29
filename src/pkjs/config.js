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
				"label": "Enable Weather",
				"defaultValue": false
			},
			{
				"type": "input",
				"messageKey": "weatherApiKey",
				"defaultValue": "",
				"description": "If weather is turned on, you should insert your API KEY!",
				"label": "OpenWeatherMap API Key",
				"attributes": {
					"placeholder": "ex: 692bd55bdf307693e80b7246cf0bab69",
					"limit": 12,
					"type": "text"
				}
			},
			{
				"type": "input",
				"messageKey": "weatherText",
				"defaultValue": "",
				"description": "Here you can choose a text to show instead of the weather! (max 12 characters)",
				"label": "Custom Text",
				"attributes": {
					"placeholder": "ex: PokeTrainer!",
					"limit": 12,
					"type": "text"
				}
			},
			
			
			{
					"type": "select",
					"messageKey": "UNITS",
					"defaultValue": "0",
					"label": "Celsius (C) or Fahrenheit (F)?",
				 "description": "After changing this setting, please refresh the weather info by pressing a button while the watchface is open (example: view timeline).",
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
        "defaultValue": "<font size='2'>Bulbasaur, Charmander & Squirtle will evolve at 2500 steps, then at 10000 steps. <br>Eevee will evolve *randomly* at 5000 steps!</font>"
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
		"defaultValue": "Thanks to:<br> <font size='2'>Northeastpaw, twaider, TheRedHairedHero for the help;<br>Dragoon, Dazz for the sprites;<br>Nintendo, Game Freak for Pokémon!</font><br><br>© rentsmdi 2016"
  }
];