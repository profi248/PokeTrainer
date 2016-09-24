#include <pebble.h>

uint32_t NUM_TRAINER_PKEY = 1;
uint32_t NUM_POKE_PKEY = 2;
uint32_t NUM_UNITS_PKEY = 3;
uint32_t NUM_OCCUPATION_PKEY = 4;
uint32_t NUM_NIGHTMODE_PKEY = 5;

static Window *s_main_window;
static TextLayer *s_time_layer;
static TextLayer *s_weather_layer;
static TextLayer *s_time_layer, *s_date_layer;
static int s_battery_level;
static Layer *s_battery_layer;

static TextLayer *s_step_layer;

static BitmapLayer *s_background_layer;
static GBitmap *s_background_bitmap, *s_backgroundNight_bitmap;

static BitmapLayer *s_background_layer, *s_bt_icon_layer;
static GBitmap *s_background_bitmap, *s_bt_icon_bitmap;

static BitmapLayer *s_step_icon_layer;
static GBitmap *s_step_icon_bitmap;

//TRAINERS

static BitmapLayer *s_trainer_layer;
static GBitmap *s_trainer_bitmap;

//POKEMON

static BitmapLayer *s_poke_layer;
static GBitmap *s_poke_bitmap;

static GFont s_time_font;
static GFont s_weather_font;
static GFont s_time_font, s_date_font;
static GFont s_step_font;



//========================== FUNCTIONS ==================================================================


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

	
	// =========================================================================== STEP PART =====================================================================
	
  text_layer_set_text(s_step_layer, s_current_steps_buffer);
	if(s_step_count<2500){					//<2500, basic
		if((persist_read_int(NUM_POKE_PKEY) == 2) ||(persist_read_int(NUM_POKE_PKEY) == 3)){ 								// case Bulbasaur
			persist_write_int(NUM_POKE_PKEY, 1);
			gbitmap_destroy(s_poke_bitmap);  																															
			s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE001);
			bitmap_layer_set_bitmap(s_poke_layer, s_poke_bitmap);
		}
		else if((persist_read_int(NUM_POKE_PKEY) == 5) ||(persist_read_int(NUM_POKE_PKEY) == 6)){ 					// case Charmander
			persist_write_int(NUM_POKE_PKEY, 4);
			gbitmap_destroy(s_poke_bitmap);  																															
			s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE004);
			bitmap_layer_set_bitmap(s_poke_layer, s_poke_bitmap);
		}
		else if((persist_read_int(NUM_POKE_PKEY) == 8) ||(persist_read_int(NUM_POKE_PKEY) == 9)){ 					// case Squirtle
			persist_write_int(NUM_POKE_PKEY, 7);
			gbitmap_destroy(s_poke_bitmap);  																															
			s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE007);
			bitmap_layer_set_bitmap(s_poke_layer, s_poke_bitmap);
		}
		else if((persist_read_int(NUM_POKE_PKEY) == 134) ||(persist_read_int(NUM_POKE_PKEY) == 135)||(persist_read_int(NUM_POKE_PKEY) == 136)||
						(persist_read_int(NUM_POKE_PKEY) == 196)||(persist_read_int(NUM_POKE_PKEY) == 197)||(persist_read_int(NUM_POKE_PKEY) == 470)||
						(persist_read_int(NUM_POKE_PKEY) == 471)||(persist_read_int(NUM_POKE_PKEY) == 700)){ 				// case Eevee
			persist_write_int(NUM_POKE_PKEY, 133);
			gbitmap_destroy(s_poke_bitmap);  																															
			s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE133);
			bitmap_layer_set_bitmap(s_poke_layer, s_poke_bitmap);
		}
	}
	else if(s_step_count>2500 && s_step_count<5000){			//>2500, first ev
		if(persist_read_int(NUM_POKE_PKEY) == 1){ 																													// case Ivysaur
			persist_write_int(NUM_POKE_PKEY, 2);
			gbitmap_destroy(s_poke_bitmap);  															
			s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE002);
			bitmap_layer_set_bitmap(s_poke_layer, s_poke_bitmap);
			vibes_long_pulse();
		}
		else if(persist_read_int(NUM_POKE_PKEY) == 4){ 																											// case Charmeleon
			persist_write_int(NUM_POKE_PKEY, 5);
			gbitmap_destroy(s_poke_bitmap);  															
			s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE005);
			bitmap_layer_set_bitmap(s_poke_layer, s_poke_bitmap);
			vibes_long_pulse();
		}
		else if(persist_read_int(NUM_POKE_PKEY) == 7){ 																											// case Wartortle
			persist_write_int(NUM_POKE_PKEY, 8);
			gbitmap_destroy(s_poke_bitmap);  															
			s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE008);
			bitmap_layer_set_bitmap(s_poke_layer, s_poke_bitmap);
			vibes_long_pulse();
		}
	}
	else if(s_step_count>5000 && s_step_count<10000){			//>5000, only ev
		if(persist_read_int(NUM_POKE_PKEY) == 133){ 																												// case Eeveelution
			int eeveelution[8] = {134, 135, 136, 196, 197, 470, 471, 700};
			int n = rand()%8;
			persist_write_int(NUM_POKE_PKEY, eeveelution[n]);
			APP_LOG(APP_LOG_LEVEL_DEBUG, "the eeveelution number is %d, so NUM_POKE_KEY IS %d", eeveelution[n], (int)persist_read_int(NUM_POKE_PKEY));
			gbitmap_destroy(s_poke_bitmap);  	
			switch (eeveelution[n]) {
			case 134:
				 s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE134);
				 break;
			case 135:
				 s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE135);
				 break;
			case 136:
				 s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE136);
				 break;
			case 196:
				 s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE196);
				 break;
			case 197:
				 s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE197);
				 break;
			case 470:
				 s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE470);
				 break;
			case 471:
				 s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE471);
				 break;
			case 700:
			   s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE700);
				 break;
			default:
				 s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE133);
				 break;
			}										
			bitmap_layer_set_bitmap(s_poke_layer, s_poke_bitmap);
			vibes_long_pulse();
		}
	}
	else if(s_step_count>10000){
		if(persist_read_int(NUM_POKE_PKEY) == 2){																														// case Venusaur
			persist_write_int(NUM_POKE_PKEY, 3);
			gbitmap_destroy(s_poke_bitmap);  																										
			s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE003);
			bitmap_layer_set_bitmap(s_poke_layer, s_poke_bitmap);
			vibes_long_pulse();
		}
		else if(persist_read_int(NUM_POKE_PKEY) == 5){																											// case Charizard
			persist_write_int(NUM_POKE_PKEY, 6);
			gbitmap_destroy(s_poke_bitmap);  																										
			s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE006);
			bitmap_layer_set_bitmap(s_poke_layer, s_poke_bitmap);
			vibes_long_pulse();
		}
		else if(persist_read_int(NUM_POKE_PKEY) == 8){																											// case Blastoise
			persist_write_int(NUM_POKE_PKEY, 9);
			gbitmap_destroy(s_poke_bitmap);  																										
			s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE009);
			bitmap_layer_set_bitmap(s_poke_layer, s_poke_bitmap);
			vibes_long_pulse();
		}
	}
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

//TRAINER & POKEMON FUNCTIONS


	static void destroyAllTrainers(){
		gbitmap_destroy(s_trainer_bitmap);
		bitmap_layer_destroy(s_trainer_layer);
	}

	static void destroyAllPoke(){
		gbitmap_destroy(s_poke_bitmap);
		bitmap_layer_destroy(s_poke_layer);
	}


// ========================================== APPMESSAGE THINGIES =======================================================

int tempe;
int faren;

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  // Store incoming information
  static char temperature_buffer[8];
  static char conditions_buffer[32];
  static char weather_layer_buffer[32];
	
			//TRAINER SETTINGS
	  Tuple *trainer_tuple = dict_find(iterator, MESSAGE_KEY_TRAINER);
		Tuple *occup_tuple = dict_find(iterator, MESSAGE_KEY_OCCUPATION);
	
    if (trainer_tuple) {                                          
      if(strcmp(trainer_tuple->value->cstring, "0") == 1) { 					 //case female
				persist_write_int(NUM_TRAINER_PKEY, 33);
   			if(occup_tuple){
					if(strcmp(occup_tuple->value->cstring, "0") == 0){ 								//trainer
						destroyAllTrainers();
						s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERF);
						persist_write_int(NUM_OCCUPATION_PKEY, 0);
					}
					else if(strcmp(occup_tuple->value->cstring, "1") == 0){ 					//ranger
						destroyAllTrainers();
						s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERFrng);
						persist_write_int(NUM_OCCUPATION_PKEY, 1);
					}
					else if(strcmp(occup_tuple->value->cstring, "2") == 0){ 					//kid
						destroyAllTrainers();
						s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERFkid);
						persist_write_int(NUM_OCCUPATION_PKEY, 2);
					}
					else if(strcmp(occup_tuple->value->cstring, "3") == 0){ 					//scientist
						destroyAllTrainers();
						s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERFscn);
						persist_write_int(NUM_OCCUPATION_PKEY, 3);
					}
					else if(strcmp(occup_tuple->value->cstring, "4") == 0){ 					//gym leader
						destroyAllTrainers();
						s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERFgym);
						persist_write_int(NUM_OCCUPATION_PKEY, 4);
					}
					else if(strcmp(occup_tuple->value->cstring, "5") == 0){ 					//rocket
						destroyAllTrainers();
						s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERFrkt);
						persist_write_int(NUM_OCCUPATION_PKEY, 5);
					}
					else if(strcmp(occup_tuple->value->cstring, "6") == 0){ 					//Johto
						destroyAllTrainers();
						s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERFJohto);
						persist_write_int(NUM_OCCUPATION_PKEY, 6);
					}
					else if(strcmp(occup_tuple->value->cstring, "7") == 0){ 					//Hoenn
						destroyAllTrainers();
						s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERFHoenn);
						persist_write_int(NUM_OCCUPATION_PKEY, 7);
					}
					else if(strcmp(occup_tuple->value->cstring, "8") == 0){ 					//Beauty
						destroyAllTrainers();
						s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERFbeauty);
						persist_write_int(NUM_OCCUPATION_PKEY, 8);
					}
					else if(strcmp(occup_tuple->value->cstring, "9") == 0){ 					//Police
						destroyAllTrainers();
						s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERFpolice);
						persist_write_int(NUM_OCCUPATION_PKEY, 9);
					}
					else if(strcmp(occup_tuple->value->cstring, "10") == 0){ 					//Medium
						destroyAllTrainers();
						s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERFmedium);
						persist_write_int(NUM_OCCUPATION_PKEY, 10);
					}
				}
				s_trainer_layer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(78,59), PBL_IF_ROUND_ELSE(49,43), 45, 54));
				bitmap_layer_set_bitmap(s_trainer_layer, s_trainer_bitmap);
				bitmap_layer_set_background_color(s_trainer_layer, GColorClear);
				bitmap_layer_set_compositing_mode(s_trainer_layer, GCompOpSet);
				layer_add_child(window_get_root_layer(s_main_window), bitmap_layer_get_layer(s_trainer_layer));
      }    
      else{        																										 //case male
				persist_write_int(NUM_TRAINER_PKEY, 22);
				if(occup_tuple){
					if(strcmp(occup_tuple->value->cstring, "0") == 0){ 								//trainer
						destroyAllTrainers();
						s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERM);
						persist_write_int(NUM_OCCUPATION_PKEY, 0);
					}
					else if(strcmp(occup_tuple->value->cstring, "1") == 0){ 					//ranger
						destroyAllTrainers();
						s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERMrng);
						persist_write_int(NUM_OCCUPATION_PKEY, 1);
					}
					else if(strcmp(occup_tuple->value->cstring, "2") == 0){ 					//kid
						destroyAllTrainers();
						s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERMkid);
						persist_write_int(NUM_OCCUPATION_PKEY, 2);
					}
					else if(strcmp(occup_tuple->value->cstring, "3") == 0){ 					//scientist
						destroyAllTrainers();
						s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERMscn);
						persist_write_int(NUM_OCCUPATION_PKEY, 3);
					}
					else if(strcmp(occup_tuple->value->cstring, "4") == 0){ 					//gym leader
						destroyAllTrainers();
						s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERMgym);
						persist_write_int(NUM_OCCUPATION_PKEY, 4);
					}
					else if(strcmp(occup_tuple->value->cstring, "5") == 0){ 					//rocket
						destroyAllTrainers();
						s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERMrkt);
						persist_write_int(NUM_OCCUPATION_PKEY, 5);
					}
					else if(strcmp(occup_tuple->value->cstring, "6") == 0){ 					//Johto
						destroyAllTrainers();
						s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERMJohto);
						persist_write_int(NUM_OCCUPATION_PKEY, 6);
					}
					else if(strcmp(occup_tuple->value->cstring, "7") == 0){ 					//Hoenn
						destroyAllTrainers();
						s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERMHoenn);
						persist_write_int(NUM_OCCUPATION_PKEY, 7);
					}
					else if(strcmp(occup_tuple->value->cstring, "8") == 0){ 					//Beauty
						destroyAllTrainers();
						s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERMbeauty);
						persist_write_int(NUM_OCCUPATION_PKEY, 8);
					}
					else if(strcmp(occup_tuple->value->cstring, "9") == 0){ 					//Police
						destroyAllTrainers();
						s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERMpolice);
						persist_write_int(NUM_OCCUPATION_PKEY, 9);
					}
					else if(strcmp(occup_tuple->value->cstring, "10") == 0){ 					//Medium
						destroyAllTrainers();
						s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERMmedium);
						persist_write_int(NUM_OCCUPATION_PKEY, 10);
					}
				}
				s_trainer_layer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(78,59), PBL_IF_ROUND_ELSE(49,43), 45, 54));
				bitmap_layer_set_bitmap(s_trainer_layer, s_trainer_bitmap);
				bitmap_layer_set_background_color(s_trainer_layer, GColorClear);
				bitmap_layer_set_compositing_mode(s_trainer_layer, GCompOpSet);
				layer_add_child(window_get_root_layer(s_main_window), bitmap_layer_get_layer(s_trainer_layer));
      } 
    }
			//END TRAINER SETTINGS
	
			//POKEMON SETTINGS
	  Tuple *poke_tuple = dict_find(iterator, MESSAGE_KEY_POKE);
    if (poke_tuple) {                                          
      if(strcmp(poke_tuple->value->cstring, "25") == 0) {
				destroyAllPoke();
				s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE025);
				persist_write_int(NUM_POKE_PKEY, 25);																													 //pikachu
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
      }    
      else if(strcmp(poke_tuple->value->cstring, "1") == 0) {        
				destroyAllPoke();
				if(s_step_count<2500){
					s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE001);
					persist_write_int(NUM_POKE_PKEY, 1);																													//bulbasaur
					APP_LOG(APP_LOG_LEVEL_DEBUG, "step count is %d", s_step_count);
				}
				else if(s_step_count>=2500 && s_step_count<10000){
					s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE002);
					persist_write_int(NUM_POKE_PKEY, 2);																													//ivysaur
					APP_LOG(APP_LOG_LEVEL_DEBUG, "step count is %d", s_step_count);
				}
				else if(s_step_count>=10000){
					s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE003);
					persist_write_int(NUM_POKE_PKEY, 3);																													//venusaur
					APP_LOG(APP_LOG_LEVEL_DEBUG, "step count is %d", s_step_count);
				}
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
      }   
      else if(strcmp(poke_tuple->value->cstring, "4") == 0) {        
   			destroyAllPoke();
				if(s_step_count<2500){
					s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE004);
					persist_write_int(NUM_POKE_PKEY, 4);																													//charmander
					APP_LOG(APP_LOG_LEVEL_DEBUG, "step count is %d", s_step_count);
				}
				else if(s_step_count>=2500 && s_step_count<10000){
					s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE005);
					persist_write_int(NUM_POKE_PKEY, 5);																													//charmeleon
					APP_LOG(APP_LOG_LEVEL_DEBUG, "step count is %d", s_step_count);
				}
				else if(s_step_count>=10000){
					s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE006);
					persist_write_int(NUM_POKE_PKEY, 6);																													//charizard
					APP_LOG(APP_LOG_LEVEL_DEBUG, "step count is %d", s_step_count);
				} 																														//charmander
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
      } 
      else if(strcmp(poke_tuple->value->cstring, "7") == 0) {        
   			destroyAllPoke();
				if(s_step_count<2500){
					s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE007);
					persist_write_int(NUM_POKE_PKEY, 7);																													//squirtle
					APP_LOG(APP_LOG_LEVEL_DEBUG, "step count is %d", s_step_count);
				}
				else if(s_step_count>=2500 && s_step_count<10000){
					s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE008);
					persist_write_int(NUM_POKE_PKEY, 8);																													//wartortle
					APP_LOG(APP_LOG_LEVEL_DEBUG, "step count is %d", s_step_count);
				}
				else if(s_step_count>=10000){
					s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE009);
					persist_write_int(NUM_POKE_PKEY, 9);																													//blastoise
					APP_LOG(APP_LOG_LEVEL_DEBUG, "step count is %d", s_step_count);
				}																													 //squirtle
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
      } 
      else if(strcmp(poke_tuple->value->cstring, "16") == 0) {        
   			destroyAllPoke();
				s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE016);
				persist_write_int(NUM_POKE_PKEY, 16); 																														//pidgey
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
      }
    else if(strcmp(poke_tuple->value->cstring, "19") == 0) {        
   			destroyAllPoke();
			  s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE019);
				persist_write_int(NUM_POKE_PKEY, 19); 																														//rattata
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
      } 
      else if(strcmp(poke_tuple->value->cstring, "41") == 0) {        
   			destroyAllPoke();
				s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE041);
				persist_write_int(NUM_POKE_PKEY, 41); 																														//zubat
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
      }
			else if(strcmp(poke_tuple->value->cstring, "95") == 0) {        
   			destroyAllPoke();
				s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE095);
				persist_write_int(NUM_POKE_PKEY, 95); 																														//onix
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
      } 
      else if(strcmp(poke_tuple->value->cstring, "120") == 0) {        
   			destroyAllPoke();
				s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE120);
				persist_write_int(NUM_POKE_PKEY, 120); 																													//staryu
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
      } 
      else if(strcmp(poke_tuple->value->cstring, "133") == 0) {        
   			destroyAllPoke();
				if(s_step_count>5000){
					int eeveelution[8] = {134, 135, 136, 196, 197, 470, 471, 700};
					int n = rand()%8;
					APP_LOG(APP_LOG_LEVEL_DEBUG, "the eeveelution number is %d, so NUM_POKE_KEY IS %d", eeveelution[n], (int)persist_read_int(NUM_POKE_PKEY));
					switch (eeveelution[n]) {
					case 134:
						 s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE134);
						 break;
					case 135:
						 s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE135);
						 break;
					case 136:
						 s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE136);
						 break;
					case 196:
						 s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE196);
						 break;
					case 197:
						 s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE197);
						 break;
					case 470:
						 s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE470);
						 break;
					case 471:
						 s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE471);
						 break;
					case 700:
						 s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE700);
						 break;
					default:
						 s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE133);
						 break;
					}
					persist_write_int(NUM_POKE_PKEY, eeveelution[n]); 																								//eeveelution
				}
				else{
				s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE133);
				persist_write_int(NUM_POKE_PKEY, 133); 																													//eevee
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
				}
      } 
      else if(strcmp(poke_tuple->value->cstring, "137") == 0) {        
   			destroyAllPoke();
				s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE137);
				persist_write_int(NUM_POKE_PKEY, 137); //porygon
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
      }
      else if(strcmp(poke_tuple->value->cstring, "152") == 0) {        
   			destroyAllPoke();
				s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE152);
				persist_write_int(NUM_POKE_PKEY, 152); //porygon
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
      }
      else if(strcmp(poke_tuple->value->cstring, "155") == 0) {        
   			destroyAllPoke();
				s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE155);
				persist_write_int(NUM_POKE_PKEY, 155); //porygon
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
      }
      else if(strcmp(poke_tuple->value->cstring, "158") == 0) {        
   			destroyAllPoke();
				s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE158);
				persist_write_int(NUM_POKE_PKEY, 158); //porygon
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
      }
      else if(strcmp(poke_tuple->value->cstring, "252") == 0) {        
   			destroyAllPoke();
				s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE252);
				persist_write_int(NUM_POKE_PKEY, 252); //porygon
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
      }
      else if(strcmp(poke_tuple->value->cstring, "255") == 0) {        
   			destroyAllPoke();
				s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE255);
				persist_write_int(NUM_POKE_PKEY, 255); //porygon
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
      }
      else if(strcmp(poke_tuple->value->cstring, "258") == 0) {        
   			destroyAllPoke();
				s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE258);
				persist_write_int(NUM_POKE_PKEY, 258); //porygon
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
      }
      else if(strcmp(poke_tuple->value->cstring, "35") == 0) {        
   			destroyAllPoke();
				s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE035);
				persist_write_int(NUM_POKE_PKEY, 35); //porygon
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
      }
      else if(strcmp(poke_tuple->value->cstring, "39") == 0) {        
   			destroyAllPoke();
				s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE039);
				persist_write_int(NUM_POKE_PKEY, 39); //porygon
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
      }
      else if(strcmp(poke_tuple->value->cstring, "58") == 0) {        
   			destroyAllPoke();
				s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE058);
				persist_write_int(NUM_POKE_PKEY, 58); //porygon
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
      }
      else if(strcmp(poke_tuple->value->cstring, "92") == 0) {        
   			destroyAllPoke();
				s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE092);
				persist_write_int(NUM_POKE_PKEY, 92); //porygon
				//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
      }
			s_poke_layer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(29,10), PBL_IF_ROUND_ELSE(44,38), 55, 55)); //era 46, 58
			bitmap_layer_set_bitmap(s_poke_layer, s_poke_bitmap);
			bitmap_layer_set_background_color(s_poke_layer, GColorClear);
			bitmap_layer_set_compositing_mode(s_poke_layer, GCompOpSet);
			layer_add_child(window_get_root_layer(s_main_window), bitmap_layer_get_layer(s_poke_layer));
			//APP_LOG(APP_LOG_LEVEL_DEBUG, "AFTER IF NUM_POKE_PKEY IS %d", (int)persist_read_int(NUM_POKE_PKEY));
    }
			//END POKEMON SETTINGS
	
	
	
	
		

  // Read tuples for data
  Tuple *temp_tuple = dict_find(iterator, MESSAGE_KEY_Temperature);
  Tuple *conditions_tuple = dict_find(iterator, MESSAGE_KEY_Conditions);

  // If all data is available, use it
  if(temp_tuple && conditions_tuple) {
		if(!(persist_exists(NUM_UNITS_PKEY)) || (persist_read_int(NUM_UNITS_PKEY) == 10)){		//case celsius
      snprintf(temperature_buffer, sizeof(temperature_buffer), "%d°", (int)temp_tuple->value->int32);
			//layer_mark_dirty(s_weather_layer);
    }                                                                  
    else if ((persist_read_int(NUM_UNITS_PKEY) == 11)){   																//case farhenheit                                                      
      tempe = (int)temp_tuple->value->int32;
      faren = tempe * 9/5 + 32;
      snprintf(temperature_buffer, sizeof(temperature_buffer), "%d°", faren);
    }
		//int stampa = (int)(persist_read_int(NUM_UNITS_PKEY));
    //snprintf(conditions_buffer, sizeof(conditions_buffer), "%d", stampa); //I'm printing to see if it's changing
		snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", conditions_tuple->value->cstring);

    // Assemble full string and display
    snprintf(weather_layer_buffer, sizeof(weather_layer_buffer), "%s, %s", conditions_buffer, temperature_buffer);
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
	
	// change background based on NIGHT MODE
	if( (tick_time->tm_hour >= 18 || tick_time->tm_hour <= 4) && (persist_read_int(NUM_NIGHTMODE_PKEY) != 1) ){
		persist_write_int(NUM_NIGHTMODE_PKEY, 1);
		//layer_mark_dirty(bitmap_layer_get_layer(s_background_layer));
		bitmap_layer_set_bitmap(s_background_layer, s_backgroundNight_bitmap);
	}
	else if( (tick_time->tm_hour < 18 && tick_time->tm_hour > 4) && (persist_read_int(NUM_NIGHTMODE_PKEY) != 0) ){
		persist_write_int(NUM_NIGHTMODE_PKEY, 0);
		//layer_mark_dirty(bitmap_layer_get_layer(s_background_layer));
		bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
	}
	
	
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

//NEW SDK
uint8_t relative_pixel(int16_t percent, int16_t max) {
  return (max * percent) / 100;
}

//====================================== MAIN WINDOW LOAD ==================================================================

//NEW SDK (DA SISTEMARE)

static void prv_unobstructed_change(AnimationProgress progress, void *context) {
  // Get the total available screen real-estate
	Layer *window_layer = window_get_root_layer(s_main_window);
	GRect bounds = layer_get_bounds(window_layer);
  GRect un_bounds = layer_get_unobstructed_bounds(window_layer);
	int bounds_int = bounds.size.h;
	int un_bounds_int = un_bounds.size.h;
	int res_bounds =  un_bounds_int - bounds_int;
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "I PRINT BOUNDS: %d, UNBOUNDS : %d, RESBOUNDS: %d", bounds_int, un_bounds_int, res_bounds);
  // Get the current position of the needed layers
  GRect frame = layer_get_frame(bitmap_layer_get_layer(s_background_layer));
	GRect frame2 = layer_get_frame(bitmap_layer_get_layer(s_trainer_layer));
	GRect frame3 = layer_get_frame(bitmap_layer_get_layer(s_poke_layer));
	GRect frame4 = layer_get_frame(text_layer_get_layer(s_time_layer));
	GRect frame5 = layer_get_frame(text_layer_get_layer(s_date_layer));
	GRect frame6 = layer_get_frame(text_layer_get_layer(s_weather_layer));
	GRect frame7 = layer_get_frame(s_battery_layer);
	GRect frame8 = layer_get_frame(bitmap_layer_get_layer(s_bt_icon_layer));
	GRect frame9 = layer_get_frame(text_layer_get_layer(s_step_layer));
	GRect frame10 = layer_get_frame(bitmap_layer_get_layer(s_step_icon_layer));
  // Shift the Y coordinate
  frame.origin.y = res_bounds;
	// Declare initial positions
	frame2.origin.y = 43 + res_bounds; // 43 is trainer y position on basalt
	frame3.origin.y = 38 + res_bounds;
	frame4.origin.y = 105 + res_bounds;
	frame5.origin.y = 130 + res_bounds;
	frame6.origin.y = 145 + res_bounds;
	frame7.origin.y = 100 + res_bounds;
	frame8.origin.y = 12 + res_bounds;
	frame9.origin.y = 145 + res_bounds;
	frame10.origin.y = 147 + res_bounds;
  // Apply the new location
  layer_set_frame(bitmap_layer_get_layer(s_background_layer), frame);
	layer_set_frame(bitmap_layer_get_layer(s_trainer_layer), frame2);
	layer_set_frame(bitmap_layer_get_layer(s_poke_layer), frame3);
	layer_set_frame(text_layer_get_layer(s_time_layer), frame4);
	layer_set_frame(text_layer_get_layer(s_date_layer), frame5);
	layer_set_frame(text_layer_get_layer(s_weather_layer), frame6);
	layer_set_frame(s_battery_layer, frame7);
	layer_set_frame(bitmap_layer_get_layer(s_bt_icon_layer), frame8);
	layer_set_frame(text_layer_get_layer(s_step_layer), frame9);
	layer_set_frame(bitmap_layer_get_layer(s_step_icon_layer), frame10);
}

static void main_window_load(Window *window) {
  // Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
	
	//NEW SDK
	UnobstructedAreaHandlers handler = {
    .change = prv_unobstructed_change
  };
  unobstructed_area_service_subscribe(handler, NULL);

  // Create GBitmap BASED ON NIGHT MODE
	
	s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND);
	s_backgroundNight_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUNDNIGHT);
	/*
	if(persist_read_int(NUM_NIGHTMODE_PKEY) == 0){
  	s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "DAY BACKGROUND BECAUSE NUM_POKE_PKEY IS %d", (int)persist_read_int(NUM_NIGHTMODE_PKEY));
	}
	else{
		s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUNDNIGHT);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "NORMAL NIGHT BACKGROUND BECAUSE NUM_NIGHTMODE_PKEY IS  %d", (int)persist_read_int(NUM_NIGHTMODE_PKEY));
	}
	
	*/

  // Create BitmapLayer to display the GBitmap
  s_background_layer = bitmap_layer_create(bounds);

  // Set the bitmap onto the layer and add to the window
		if(persist_read_int(NUM_NIGHTMODE_PKEY) == 0){
  	bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Day Background applied, because NUM_NIGHTMODE_PKEY is %d", (int)persist_read_int(NUM_NIGHTMODE_PKEY));
	}
	else{
		bitmap_layer_set_bitmap(s_background_layer, s_backgroundNight_bitmap);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Night Background applied, because NUM_NIGHTMODE_PKEY is %d", (int)persist_read_int(NUM_NIGHTMODE_PKEY));
	}
	
  // bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
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
      GRect(PBL_IF_ROUND_ELSE(20, 10), PBL_IF_ROUND_ELSE(110, 145), bounds.size.w, 25));

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
  s_step_icon_layer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(111, 90), PBL_IF_ROUND_ELSE(110, 147), 12, 12));
  bitmap_layer_set_bitmap(s_step_icon_layer, s_step_icon_bitmap);
  bitmap_layer_set_background_color(s_step_icon_layer, GColorClear);
  bitmap_layer_set_compositing_mode(s_step_icon_layer, GCompOpSet);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_step_icon_layer));
  
   // Create a layer to hold the current step count
  s_step_layer = text_layer_create(
      GRect(PBL_IF_ROUND_ELSE(127, 105), PBL_IF_ROUND_ELSE(110, 145), bounds.size.w, 25));
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
	
  // ======================================== trainer setting
	
	if(persist_exists(NUM_TRAINER_PKEY)){
		int occupation = persist_read_int(NUM_OCCUPATION_PKEY);
			if(persist_read_int(NUM_TRAINER_PKEY) == 33) {  	//female      
				destroyAllTrainers();
				switch (occupation) {
					case 0:
					s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERF);
						break;
					case 1:
					s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERFrng);
						break;
					case 2:
					s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERFkid);
						break;
					case 3:
					s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERFscn);
						break;
					case 4:
					s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERFgym);
						break;
					case 5:
					s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERFrkt);
						break;
					case 6:
					s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERFJohto);
						break;
					case 7:
					s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERFHoenn);
						break;
					case 8:
					s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERFbeauty);
						break;
					case 9:
					s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERFpolice);
						break;
					case 10:
					s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERFmedium);
						break;
					default:
					s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERF);
						break;
				}
				s_trainer_layer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(78,59), PBL_IF_ROUND_ELSE(49,43), 45, 54));
				bitmap_layer_set_bitmap(s_trainer_layer, s_trainer_bitmap);
				bitmap_layer_set_background_color(s_trainer_layer, GColorClear);
				bitmap_layer_set_compositing_mode(s_trainer_layer, GCompOpSet);
				layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_trainer_layer));
      }    
      else if(persist_read_int(NUM_TRAINER_PKEY) == 22){   //male      
  			destroyAllTrainers();
				switch (occupation) {
					case 0:
					s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERM);
						break;
					case 1:
					s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERMrng);
						break;
					case 2:
					s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERMkid);
						break;
					case 3:
					s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERMscn);
						break;
					case 4:
					s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERMgym);
						break;
					case 5:
					s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERMrkt);
						break;
					case 6:
					s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERMJohto);
						break;
					case 7:
					s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERMHoenn);
						break;
					case 8:
					s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERMbeauty);
						break;
					case 9:
					s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERMpolice);
						break;
					case 10:
					s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERMmedium);
						break;
					default:
					s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERM);
						break;
				}
				s_trainer_layer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(78,59), PBL_IF_ROUND_ELSE(49,43), 45, 52));
				bitmap_layer_set_bitmap(s_trainer_layer, s_trainer_bitmap);
				bitmap_layer_set_background_color(s_trainer_layer, GColorClear);
				bitmap_layer_set_compositing_mode(s_trainer_layer, GCompOpSet);
				layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_trainer_layer));
      }
	}
	else{
			destroyAllTrainers();
			s_trainer_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRAINERM);
			s_trainer_layer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(78,59), PBL_IF_ROUND_ELSE(49,43), 45, 52));
			bitmap_layer_set_bitmap(s_trainer_layer, s_trainer_bitmap);
			bitmap_layer_set_background_color(s_trainer_layer, GColorClear);
			bitmap_layer_set_compositing_mode(s_trainer_layer, GCompOpSet);
			layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_trainer_layer));
	}

  // ======================================== pokemon setting
	
	if(!(persist_exists(NUM_POKE_PKEY)) || (persist_read_int(NUM_POKE_PKEY) == 25)) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE025);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED PIKACHU BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}    
	else if(persist_read_int(NUM_POKE_PKEY) == 1) { 
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE001);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED BULBASAUR BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 2) { 
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE002);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED IVYSAUR BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 3) { 
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE003);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED VENUSAUR BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 4) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE004);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED CHARMANDER BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 5) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE005);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED CHARMELEON BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 6) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE006);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED CHARIZARD BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 7) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE007);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 8) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE008);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 9) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE009);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 16) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE016);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED PIDGEY BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 19) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE019);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED RATTATA BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 41) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE041);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED ZUBAT BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 95) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE095);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 120) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE120);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 133) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE133);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 137) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE137);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 152) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE152);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 155) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE155);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 158) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE158);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 252) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE252);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 255) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE255);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 258) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE258);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 35) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE035);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 39) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE039);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 58) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE058);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 92) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE092);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 134) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE134);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 135) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE135);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 136) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE136);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 196) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE196);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 197) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE197);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 470) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE470);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 471) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE471);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else if(persist_read_int(NUM_POKE_PKEY) == 700) {        
		destroyAllPoke();
		s_poke_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POKE700);
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED SQUIRTLE BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
	}
	else{
		destroyAllPoke();
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "I ADDED NOTHING BECAUSE NUM_POKE_PKEY IS NOW %d", (int)persist_read_int(NUM_POKE_PKEY));
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "NUM_TRAINER PKEY IS %d", (int)persist_read_int(NUM_TRAINER_PKEY));
	}
    s_poke_layer = bitmap_layer_create(GRect(PBL_IF_ROUND_ELSE(29,10), PBL_IF_ROUND_ELSE(44,38), 55, 55)); //era 40 50
    bitmap_layer_set_bitmap(s_poke_layer, s_poke_bitmap);
    bitmap_layer_set_background_color(s_poke_layer, GColorClear);
    bitmap_layer_set_compositing_mode(s_poke_layer, GCompOpSet);
    layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_poke_layer));

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
  
  // Destroy Trainer icons
	gbitmap_destroy(s_trainer_bitmap);
	bitmap_layer_destroy(s_trainer_layer);
  
	// Destroy Pokemon icons
	gbitmap_destroy(s_poke_bitmap);
	bitmap_layer_destroy(s_poke_layer);
  
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
  app_message_open(128, app_message_outbox_size_maximum());
}

static void deinit() {
  // Destroy Window
  //window_destroy(s_main_window);
  
  //destroy Battery
  layer_destroy(s_battery_layer);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}