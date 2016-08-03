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
        "defaultValue": "1",
        "label": "Celsius (C) or Fahrenheit (F)?",
        "options": [
          { 
            "label": "Celsius",
            "value": "1" 
          },
          { 
            "label": "Fahrenheit",
            "value": "0" 
          }
        ]
      }
    ]
  },
  
  /*
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Trainer Settings"
      },
      {
        "type": "select",
        "messageKey": "trainer",
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
        "type": "select",
        "messageKey": "pokemon",
        "defaultValue": "pikachu",
        "label": "Choose your Starter!",
        "options": [
          { 
            "label": "Pikachu",
            "value": "025" 
          },
          { 
            "label": "Bulbasaur",
            "value": "001" 
          }
        ]
      }
    ]
  },
  
  */ 
  {
    "type": "submit",
    "defaultValue": "Save"
  }
];