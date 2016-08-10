#include <pebble.h>

uint32_t NUM_TRAINER_PKEY = 1;
uint32_t NUM_POKE_PKEY = 2;
uint32_t NUM_UNITS_PKEY = 3;

static Window *s_main_window;
static TextLayer *s_time_layer;
static TextLayer *s_weather_layer;
static TextLayer *s_time_layer, *s_date_layer;
static int s_battery_level;
static Layer *s_battery_layer;

//steps
static TextLayer *s_step_layer;

static BitmapLayer *s_background_layer;
static GBitmap *s_background_bitmap;

static BitmapLayer *s_background_layer, *s_bt_icon_layer;
static GBitmap *s_background_bitmap, *s_bt_icon_bitmap;

static BitmapLayer *s_step_icon_layer;
static GBitmap *s_step_icon_bitmap;

static BitmapLayer *s_trainerM_layer;
static GBitmap *s_trainerM_bitmap;

static BitmapLayer *s_trainerF_layer;
static GBitmap *s_trainerF_bitmap;

static BitmapLayer *s_poke025_layer;
static GBitmap *s_poke025_bitmap;

static BitmapLayer *s_poke001_layer;
static GBitmap *s_poke001_bitmap;

static BitmapLayer *s_poke004_layer;
static GBitmap *s_poke004_bitmap;

static BitmapLayer *s_poke007_layer;
static GBitmap *s_poke007_bitmap;

static GFont s_time_font;
static GFont s_weather_font;
static GFont s_time_font, s_date_font;
static GFont s_step_font;

//START STEP INFO ==================

static char s_current_steps_buffer[16];
static int s_step_count = 0, s_step_goal = 0; // s_step_average = 0;

// Is step data available?
bool step_data_is_available() {
  return HealthServiceAccessibilityMaskAvailable &
    health_service_metric_accessible(HealthMetricStepCount,
      time_start_of_today(), time(NULL));
}

// Daily step goal
static void get_step_goal() {
  const time_t start = time_start_of_today();
  const time_t end = start + SECONDS_PER_DAY;
  s_step_goal = (int)health_service_sum_averaged(HealthMetricStepCount,
    start, end, HealthServiceTimeScopeDaily);
}

// Todays current step count
static void get_step_count() {
  s_step_count = (int)health_service_sum_today(HealthMetricStepCount);
}

/*
// Average daily step count for this time of day
static void get_step_average() {
  const time_t start = time_start_of_today();
  const time_t end = time(NULL);
  s_step_average = (int)health_service_sum_averaged(HealthMetricStepCount,
    start, end, HealthServiceTimeScopeDaily);
}
*/

static void display_step_count() {
  int thousands = s_step_count / 1000;
  int hundreds = s_step_count % 1000;
  text_layer_set_text_color(s_step_layer, GColorBlack);

  if(thousands > 0) {
    snprintf(s_current_steps_buffer, sizeof(s_current_steps_buffer),
      "%d,%03d", thousands, hundreds);
  } else {
    snprintf(s_current_steps_buffer, sizeof(s_current_steps_buffer),
      "%d", hundreds);
  }

  text_layer_set_text(s_step_layer, s_current_steps_buffer);
}

static void health_handler(HealthEventType event, void *context) {
  if(event == HealthEventSignificantUpdate) {
    get_step_goal();
  }
  if(event != HealthEventSleepUpdate) {
    get_step_count();
    display_step_count();
  }
}

//end step info =============================================

//POKEMON FUNCTIONS

	static void hideAllTrainers(){
		layer_set_hidden(bitmap_layer_get_layer(s_trainerM_layer), true);
		layer_set_hidden(bitmap_layer_get_layer(s_trainerF_layer), true);
	}

	static void hideAllPoke(){
		layer_set_hidden(bitmap_layer_get_layer(s_poke025_layer), true);
		layer_set_hidden(bitmap_layer_get_layer(s_poke001_layer), true);
		layer_set_hidden(bitmap_layer_get_layer(s_poke004_layer), true);
		layer_set_hidden(bitmap_layer_get_layer(s_poke007_layer), true);
	}


//APPMESSAGE THINGIES

int tempe;
int faren;

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  // Store incoming information
  static char temperature_buffer[8];
  static char conditions_buffer[32];
  static char weather_layer_buffer[32];
	
			//TRAINER SETTINGS
	  Tuple *trainer_tuple = dict_find(iterator, MESSAGE_KEY_TRAINER);
    if (trainer_tuple) {                                          
      if(strcmp(trainer_tuple->value->cstring, "0") == 1) {        
   			layer_set_hidden(bitmap_layer_get_layer(s_trainerM_layer), true);
				layer_set_hidden(bitmap_layer_get_layer(s_trainerF_layer), false);
				int numfemale= 33;
				persist_write_int(NUM_TRAINER_PKEY, numfemale); //case female
      }    
      else{        
         layer_set_hidden(bitmap_layer_get_layer(s_trainerF_layer), true); 
				layer_set_hidden(bitmap_layer_get_layer(s_trainerM_layer), false);
				int nummale = 22;
				persist_write_int(NUM_TRAINER_PKEY, nummale); //case male
      } 
    }
			//END TRAINER SETTINGS
	
			//POKEMON SETTINGS
	  Tuple *poke_tuple = dict_find(iterator, MESSAGE_KEY_POKE);
    if (poke_tuple) {                                          
      if(strcmp(poke_tuple->value->cstring, "25") == 0) {
				hideAllPoke();
   			layer_set_hidden(bitmap_layer_get_layer(s_poke025_layer), false);
				persist_write_int(NUM_POKE_PKEY, 25); //pikachu
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
      }    
      else if(strcmp(poke_tuple->value->cstring, "1") == 0) {        
   			hideAllPoke();
				layer_set_hidden(bitmap_layer_get_layer(s_poke001_layer), false);
				persist_write_int(NUM_POKE_PKEY, 1); //bulbasaur
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
      }   
      else if(strcmp(poke_tuple->value->cstring, "4") == 0) {        
   			hideAllPoke();
				layer_set_hidden(bitmap_layer_get_layer(s_poke004_layer), false);
				persist_write_int(NUM_POKE_PKEY, 4); //charmander
				APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
      } 
      else if(strcmp(poke_tuple->value->cstring, "7") == 0) {        
   			hideAllPoke();
				layer_set_hidden(bitmap_layer_get_layer(s_poke007_layer), false);
				persist_write_int(NUM_POKE_PKEY, 7); //squirtle
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
      }
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "AFTER IF NUM_POKE_PKEY IS %d", (int)persist_read_int(NUM_POKE_PKEY));
    }
			//END POKEMON SETTINGS
	
	
		

  // Read tuples for data
  Tuple *temp_tuple = dict_find(iterator, MESSAGE_KEY_Temperature);
  Tuple *conditions_tuple = dict_find(iterator, MESSAGE_KEY_Conditions);

  // If all data is available, use it
  if(temp_tuple && conditions_tuple) {
		if(!(persist_exists(NUM_UNITS_PKEY)) || (persist_read_int(NUM_UNITS_PKEY) == 10)){
      snprintf(temperature_buffer, sizeof(temperature_buffer), "%d°", (int)temp_tuple->value->int32);
    }                                                                  
    else if ((persist_read_int(NUM_UNITS_PKEY) == 11)){                                                         
      tempe = (int)temp_tuple->value->int32;
      faren = tempe * 9/5 + 32;
      snprintf(temperature_buffer, sizeof(temperature_buffer), "%d°", faren);
    }
		//int stampa = (int)(persist_read_int(NUM_UNITS_PKEY));
    //snprintf(conditions_buffer, sizeof(conditions_buffer), "%d", stampa); //I'm printing to see if it's changing
		snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", conditions_tuple->value->cstring);

    // Assemble full string and display
    snprintf(weather_layer_buffer, sizeof(weather_layer_buffer), "%s, %s", temperature_buffer, conditions_buffer);
    text_layer_set_text(s_weather_layer, weather_layer_buffer);
  }
	
	 Tuple *weather_units_tuple = dict_find(iterator, MESSAGE_KEY_UNITS);
    if (weather_units_tuple) {                                  
      if(strcmp(weather_units_tuple->value->cstring, "0") == 0) {        
			 int numcelsius= 10;
			 persist_write_int(NUM_UNITS_PKEY, numcelsius); //case celsius
      }    
      else{          
			int numfaren= 11;
			 persist_write_int(NUM_UNITS_PKEY, numfaren); //case faren
       //APP_LOG(APP_LOG_LEVEL_INFO, "option: %d", (persist_read_int(NUM_UNITS_PKEY));
      } 
    }
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

static void battery_callback(BatteryChargeState state) {
  // Record the new battery level
  s_battery_level = state.charge_percent;
}


static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);

  // Write the current hours and minutes into a buffer
  static char s_buffer[8];
  strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ?
                                          "%H:%M" : "%I:%M", tick_time);

  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer, s_buffer);
  
  // Copy date into buffer from tm structure
static char date_buffer[24];
strftime(date_buffer, sizeof(date_buffer), "%A %d %B", tick_time);

// Show the date
text_layer_set_text(s_date_layer, date_buffer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();

  // Get weather update every 30 minutes
  if(tick_time->tm_min % 30 == 0) {
    // Begin dictionary
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);

    // Add a key-value pair
    dict_write_uint8(iter, 0, 0);

    // Send the message!
    app_message_outbox_send();
  }
}

// Battery
static void battery_update_proc(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(layer);

  // Find the width of the bar
  int width = (int)(float)(((float)s_battery_level / 100.0F) * PBL_IF_ROUND_ELSE(159.0F, 131.0F)); //remember to change the multiplier, it must be equa to the bar size

  // Draw the background
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, bounds, 0, GCornerNone);

  // Draw the bar
  graphics_context_set_fill_color(ctx, GColorDarkGray);  //battery bar color
  graphics_fill_rect(ctx, GRect(0, 0, width, bounds.size.h), 0, GCornerNone);
}

// Bluetooth

static void bluetooth_callback(bool connected) {
  // Show icon if disconnected
  layer_set_hidden(bitmap_layer_get_layer(s_bt_icon_layer), connected);

  if(!connected) {
    // Issue a vibrating alert
    vibes_double_pulse();
  }
}


static void main_window_load(Window *window) {
  // Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Create GBitmap
  s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND);

  // Create BitmapLayer to display the GBitmap
  s_background_layer = bitmap_layer_create(bounds);

  // Set the bitmap onto the layer and add to the window
  bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_background_layer));

  // Create the TextLayer with specific bounds
  s_time_layer = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(136, 105), bounds.size.w, 50));

  // Improve the layout to be more like a watchface
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);
  text_layer_set_text(s_time_layer, "00:00");
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

  // Create GFont
  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PERFECT_DOS_22));

  // Apply to TextLayer
  text_layer_set_font(s_time_layer, s_time_font);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));

  // Create date TextLayer
  s_date_layer = text_layer_create(
      GRect(PBL_IF_ROUND_ELSE(10, 0), PBL_IF_ROUND_ELSE(123, 130), 144, 30));
  text_layer_set_text_color(s_date_layer, GColorBlack);
  text_layer_set_background_color(s_date_layer, GColorClear);
  text_layer_set_text_alignment(s_date_layer, PBL_IF_ROUND_ELSE(GTextAlignmentCenter, GTextAlignmentCenter));
  
  // Add to Window
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_date_layer));

  // Date Font
  s_date_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PERFECT_DOS_12));

  //Apply Font
  text_layer_set_font(s_date_layer, s_date_font);
  
  // Create temperature Layer
  s_weather_layer = text_layer_create(
      GRect(PBL_IF_ROUND_ELSE(20, 10), PBL_IF_ROUND_ELSE(109, 145), bounds.size.w, 25));

  // Style the text
  text_layer_set_background_color(s_weather_layer, GColorClear);
  text_layer_set_text_color(s_weather_layer, GColorBlack);
  text_layer_set_text_alignment(s_weather_layer, PBL_IF_ROUND_ELSE(GTextAlignmentLeft, GTextAlignmentLeft));
  text_layer_set_text(s_weather_layer, "N/D"); //loading era qui


  // Create second custom font, apply it and add to Window
  s_weather_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PERFECT_DOS_12));
  text_layer_set_font(s_weather_layer, s_weather_font);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_weather_layer));
    
  
  // Create battery meter Layer
  s_battery_layer = layer_create(GRect(PBL_IF_ROUND_ELSE(9, 6), PBL_IF_ROUND_ELSE(106, 100), PBL_IF_ROUND_ELSE(159, 131), 2));
  layer_set_update_proc(s_battery_layer, battery_update_proc);
    
  // Add to Window
  layer_add_child(window_get_root_layer(window), s_battery_layer);
  
  // Update meter
  layer_mark_dirty(s_battery_layer);
  
  // Create the Bluetooth icon GBitmap
  s_bt_icon_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BT_ICON);
  
  // Create the BitmapLayer to display the GBitmap (Bluetooth)
  s_bt_icon_layer = bitmap_layer_create(GRect(108, 12, 32, 23));
  bitmap_layer_set_bitmap(s_bt_icon_layer, s_bt_icon_bitmap);
  bitmap_layer_set_background_color(s_bt_icon_layer, GColorClear);
  bitmap_layer_set_compositing_mode(s_bt_icon_layer, GCompOpSet);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_bt_icon_layer));

  // Show the correct state of the BT connection from the start
  bluetooth_callback(connection_service_peek_pebble_app_connection());
  
   // Create the Step icon GBitmap
  s_step_icon_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_STEP);
  
  // Create the BitmapLayer to display the GBitmap (Step)
  s_step_icon_layer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(110, 90), PBL_IF_ROUND_ELSE(110, 147), 12, 12));
  bitmap_layer_set_bitmap(s_step_icon_layer, s_step_icon_bitmap);
  bitmap_layer_set_background_color(s_step_icon_layer, GColorClear);
  bitmap_layer_set_compositing_mode(s_step_icon_layer, GCompOpSet);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_step_icon_layer));
  
   // Create a layer to hold the current step count
  s_step_layer = text_layer_create(
      GRect(PBL_IF_ROUND_ELSE(127, 105), PBL_IF_ROUND_ELSE(109, 145), bounds.size.w, 25));
  text_layer_set_background_color(s_step_layer, GColorClear);
  
  // Create and set Step font
  s_step_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PERFECT_DOS_12));
  text_layer_set_font(s_step_layer, s_step_font);
  
  text_layer_set_text_alignment(s_step_layer, GTextAlignmentLeft);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_step_layer));

  // Subscribe to health events if we can
  if(step_data_is_available()) {
    health_service_events_subscribe(health_handler, NULL);
  }
  
  
  // Trainer Male Layer!
  s_trainerM_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERM);
  s_trainerM_layer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(86,67), PBL_IF_ROUND_ELSE(51,45), 40, 50));
  bitmap_layer_set_bitmap(s_trainerM_layer, s_trainerM_bitmap);
  bitmap_layer_set_background_color(s_trainerM_layer, GColorClear);
  bitmap_layer_set_compositing_mode(s_trainerM_layer, GCompOpSet);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_trainerM_layer));
	
	 // Trainer Female Layer!
  s_trainerF_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERF);
  s_trainerF_layer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(80,61), PBL_IF_ROUND_ELSE(51,45), 45, 50));
  bitmap_layer_set_bitmap(s_trainerF_layer, s_trainerF_bitmap);
  bitmap_layer_set_background_color(s_trainerF_layer, GColorClear);
  bitmap_layer_set_compositing_mode(s_trainerF_layer, GCompOpSet);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_trainerF_layer));
	
  
 		// Pikachu Layer!
  s_poke025_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE025);
  s_poke025_layer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(47,28), PBL_IF_ROUND_ELSE(49,43), 40, 50));
  bitmap_layer_set_bitmap(s_poke025_layer, s_poke025_bitmap);
  bitmap_layer_set_background_color(s_poke025_layer, GColorClear);
  bitmap_layer_set_compositing_mode(s_poke025_layer, GCompOpSet);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_poke025_layer));
	
	 // Bulbasaur Layer!
  s_poke001_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE001);
  s_poke001_layer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(47,28), PBL_IF_ROUND_ELSE(49,43), 40, 50));
  bitmap_layer_set_bitmap(s_poke001_layer, s_poke001_bitmap);
  bitmap_layer_set_background_color(s_poke001_layer, GColorClear);
  bitmap_layer_set_compositing_mode(s_poke001_layer, GCompOpSet);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_poke001_layer));
	
	 // Charmander Layer!
  s_poke004_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE004);
  s_poke004_layer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(47,28), PBL_IF_ROUND_ELSE(49,43), 40, 50));
  bitmap_layer_set_bitmap(s_poke004_layer, s_poke004_bitmap);
  bitmap_layer_set_background_color(s_poke004_layer, GColorClear);
  bitmap_layer_set_compositing_mode(s_poke004_layer, GCompOpSet);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_poke004_layer));
	
	 // Squirtle Layer!
  s_poke007_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE007);
  s_poke007_layer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(47,28), PBL_IF_ROUND_ELSE(49,43), 40, 50));
  bitmap_layer_set_bitmap(s_poke007_layer, s_poke007_bitmap);
  bitmap_layer_set_background_color(s_poke007_layer, GColorClear);
  bitmap_layer_set_compositing_mode(s_poke007_layer, GCompOpSet);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_poke007_layer));
	
	
	//trainer setting
	
	if(persist_exists(NUM_TRAINER_PKEY)){
			if(persist_read_int(NUM_TRAINER_PKEY) == 33) {        
				hideAllTrainers();
				layer_set_hidden(bitmap_layer_get_layer(s_trainerF_layer), false);
      }    
      else if(persist_read_int(NUM_TRAINER_PKEY) == 22){        
  			hideAllTrainers();
				layer_set_hidden(bitmap_layer_get_layer(s_trainerM_layer), false);
      }
	}
	else{
			hideAllTrainers();
			layer_set_hidden(bitmap_layer_get_layer(s_trainerM_layer), false);
	}

	//pokemon setting
	
	if(!(persist_exists(NUM_POKE_PKEY)) || (((int)persist_read_int(NUM_POKE_PKEY)) == 25)) {        
		hideAllPoke();
		layer_set_hidden(bitmap_layer_get_layer(s_poke025_layer), false);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED PIKACHU BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}    
	else if(((int)persist_read_int(NUM_POKE_PKEY)) == 1) { 
		hideAllPoke();
		layer_set_hidden(bitmap_layer_get_layer(s_poke001_layer), false);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED BULBASAUR BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(((int)persist_read_int(NUM_POKE_PKEY)) == 4) {        
		hideAllPoke();
		layer_set_hidden(bitmap_layer_get_layer(s_poke004_layer), false);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED CHARMANDER BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(((int)persist_read_int(NUM_POKE_PKEY)) == 7) {        
		hideAllPoke();
		layer_set_hidden(bitmap_layer_get_layer(s_poke007_layer), false);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else{
		hideAllPoke();
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED NOTHING BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_TRAINER PKEY IS %d", (int)persist_read_int(NUM_TRAINER_PKEY));
	}

  
}

static void main_window_unload(Window *window) {
  // Destroy TextLayer
  text_layer_destroy(s_time_layer);

  // Unload GFont
  fonts_unload_custom_font(s_time_font);

  // Destroy GBitmap
  gbitmap_destroy(s_background_bitmap);

  // Destroy BitmapLayer
  bitmap_layer_destroy(s_background_layer);
  
  // Destroy Date
  fonts_unload_custom_font(s_date_font);
  text_layer_destroy(s_date_layer);

  // Destroy weather elements
  text_layer_destroy(s_weather_layer);
  fonts_unload_custom_font(s_weather_font);
  
  // Destroy Bluetooth icon
  gbitmap_destroy(s_bt_icon_bitmap);
  bitmap_layer_destroy(s_bt_icon_layer);
  
  // Destroy Step icon
  gbitmap_destroy(s_step_icon_bitmap);
  bitmap_layer_destroy(s_step_icon_layer);
  
  // Destroy Trainer icon
  gbitmap_destroy(s_trainerM_bitmap);
  bitmap_layer_destroy(s_trainerM_layer);
	
	gbitmap_destroy(s_trainerF_bitmap);
	bitmap_layer_destroy(s_trainerF_layer);
  
	// Destroy Pokemon icons
	gbitmap_destroy(s_poke025_bitmap);
	bitmap_layer_destroy(s_poke025_layer);

	gbitmap_destroy(s_poke001_bitmap);
	bitmap_layer_destroy(s_poke001_layer);

	gbitmap_destroy(s_poke004_bitmap);
	bitmap_layer_destroy(s_poke004_layer);

	gbitmap_destroy(s_poke007_bitmap);
	bitmap_layer_destroy(s_poke007_layer);
	
	
  
  //Unload Step Font
  fonts_unload_custom_font(s_step_font);
  
  // Destroy Step info
   text_layer_destroy(s_step_layer);
}




static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set the background color
  window_set_background_color(s_main_window, GColorBlack);

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);

  // Make sure the time is displayed from the start
  update_time();

  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);

  // Register callbacks
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  
  // Register for battery level updates
  battery_state_service_subscribe(battery_callback);
  
  // Ensure battery level is displayed from the start
  battery_callback(battery_state_service_peek());

  // Register for Bluetooth connection updates
  connection_service_subscribe((ConnectionHandlers) {
  .pebble_app_connection_handler = bluetooth_callback
  });
  
  
  // Open AppMessage
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
  
  //destroy Battery
  layer_destroy(s_battery_layer);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}