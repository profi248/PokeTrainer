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
            "label": "Trainer!",
            "value": "0" 
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