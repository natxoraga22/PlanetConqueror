//
//  Constants.h
//  PlanetConqueror
//
//  Created by Ignacio Raga Llorens on 13/11/15.
//
//

#ifndef Constants_h
#define Constants_h


using namespace std;

// Generic menu
static const float MENU_TITLE_Y_POSITION_RATIO = 0.7;

static const float MENU_LOGO_SIZE_RATIO = 1.0/3.0;
static const float MENU_LOGO_OFFSET_RATIO = 1.0/32.0;

static const float MENU_BUTTON_TEXT_FONT_SIZE = 125.0;
static const float MENU_BUTTON_SIZE_RATIO = 0.4;

// Main menu
static const float MAIN_MENU_GAME_TITLE_FONT_SIZE = 72.0;
static const float MAIN_MENU_DIFFICULTY_FONT_SIZE = 48.0;

static const float PLAY_BUTTON_Y_POSITION_RATIO = 0.48;
static const float DIFFICULTY_Y_POSITION_RATIO = 0.3;

static const float NEXT_BUTTON_SIZE_RATIO = 1.0/18.0;

static const string GAME_TITLE = "Planet Conqueror";
static const string PLAY_BUTTON_TITLE = "Play Game";
static const string EASY_DIFFICULTY_TITLE = "Easy";
static const string MEDIUM_DIFFICULTY_TITLE = "Medium";
static const string HARD_DIFFICULTY_TITLE = "Hard";

// End game menu
static const float ENDGAME_MENU_TITLE_FONT_SIZE = 108.0;

static const float PLAY_AGAIN_BUTTON_Y_POSITION_RATIO = 0.48;
static const float MAIN_MENU_BUTTON_Y_POSITION_RATIO = 0.3;

static const string GAME_OVER_MENU_TITLE = "Game Over";
static const string WIN_MENU_TITLE = "You Win!";
static const string PLAY_AGAIN_BUTTON_TITLE = "Play Again";
static const string MAIN_MENU_BUTTON_TITLE = "Main Menu";

// Pause/Resum & sound/mute buttons
static const float PAUSE_BUTTON_SIZE_RATIO = 1.0/15.0;
static const float PAUSE_BUTTON_OFFSET_RATIO = 1.0/128.0;

static const float MUTE_BUTTON_SIZE_RATIO = 1.0/12.0;
static const float MUTE_BUTTON_OFFSET_RATIO = 1.0/64.0;

// Planets
static const int MAX_NUMBER_OF_PLANETS = 18;
static const int MIN_NUMBER_OF_PLANETS = 15;

static const float PLANET_MAX_SIZE_RATIO = 1.0/7.0;
static const float PLANET_MIN_SIZE_RATIO = 1.0/15.0;

static const float MIN_DISTANCE_BETWEEN_PLANETS_RATIO = 1.0/20.0;

static const int PLANET_LAYOUT_MAX_ERRORS = 10000;

// Ships
static const float PLANET_SHIP_COUNTER_FONT_SIZE = 60.0;

static const float PLAYER_SHIP_SIZE_RATIO = 1.0/25.0;
static const float CPU_SHIP_SIZE_RATIO = 1.0/20.0;

static const float INCREMENT_SHIPS_INTERVAL = 0.66;

static const int MIN_MAX_SHIPS_PER_PLANET = MIN_NUMBER_OF_PLANETS;
static const int MAX_MAX_SHIPS_PER_PLANET = MAX_NUMBER_OF_PLANETS;

static const int MIN_SHIP_SPEED = 100.0;
static const int MAX_SHIP_SPEED = 130.0;

// AI
static const float COMPUTE_AI_INTERVAL = 1.0;

// User defaults
static const char* MUTE_KEY = "MUTE";


#endif /* Constants_h */
