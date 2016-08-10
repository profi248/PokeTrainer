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
          }
        ]
      }
    ]
  },
  

  {
    "type": "submit",
    "defaultValue": "Save"
  }
];