//Nuclear Head
// TFG UOC Videojocs
#include <gb/gb.h>
#include <gb/hardware.h>
#include "utils/char_utils.h" // rutinas de manejo de metasprites (sprite formado por varios sprites)

// Tiles
#include "data/tiles/bkg_tileset.h"
#include "data/tiles/pg_idle_tileset.h"
#include "data/tiles/title_tileset.h"
//#include "data/tiles/gui_tileset.h"
// Maps
#include "data/maps/bkg_map.h"
#include "data/maps/title_map.h"
//#include "data/maps/gui_map.h"

//Constants
#define TITLE_ST            0U
#define STORY_ST            1U
#define GAME_ST             2U
#define LIGHT_TRANS_DUR     8U

// estructura basica de un personaje, id, posicion, grafico
typedef struct {
	UBYTE id;
	UBYTE x;
	UBYTE y;
	UBYTE graphic;
} Character;

//Variables
UBYTE bkg_x;
UBYTE bkg_y;
UBYTE cur_joypad;
UBYTE pre_joypad;
Character PG;
UBYTE game_state;


//Functions
void title();
void story();
void game();
void init_game();
void init_title();
void init_story();
void init_game_bkg();
void init_title_bkg();
void init_game_var();
void init_game_sprites();
void init_pg_sprite();
void read_joypad();
void lights_out_transition();
void lights_in_transition();
void lights_transition_phase(UBYTE transition_phase);


void main() {

    while (1) {
        title();
        //story();
        game();
    }
}

void title(){
    
    init_title();
    while (game_state == TITLE_ST) {
        read_joypad();
        if (cur_joypad & J_START) { // A key down
            game_state = GAME_ST;
        }   
        wait_vbl_done();
    }
    lights_out_transition();

}

void init_title(){
    
    disable_interrupts();
    DISPLAY_OFF;
    game_state = TITLE_ST;
    init_title_bkg();
    DISPLAY_ON;
    enable_interrupts();
    wait_vbl_done();
    lights_in_transition();

}

void init_title_bkg() {
    HIDE_BKG;
    SWITCH_ROM_MBC1(title_tilesetBank);
    set_bkg_data(0, 48, title_tileset);
    SWITCH_ROM_MBC1(title_mapBank);
    set_bkg_tiles(0, 0, title_mapWidth, title_mapHeight, title_map);
    move_bkg(0, 0);
    SHOW_BKG;
}

void story(){

    init_story();
    while (game_state == STORY_ST) {
        wait_vbl_done();
    }
    lights_out_transition();

}

void init_story(){

}

void game() {
    
    init_game();
    while (game_state == GAME_ST) {
        wait_vbl_done();
    }
    lights_out_transition();
        
}

void init_game() {
	
	disable_interrupts();
    DISPLAY_OFF;
    init_game_var();
    init_game_bkg();
    //init_game_gui();
    init_game_sprites();
    DISPLAY_ON;
    enable_interrupts();
    wait_vbl_done();
    lights_in_transition();

}

void init_game_var() {
    bkg_x = 0;
    bkg_y = 0;
    game_state=GAME_ST;
}

void init_game_sprites() {
    HIDE_SPRITES;
    init_pg_sprite();
    SHOW_SPRITES;
}

void init_game_bkg() {
    HIDE_BKG;
    SWITCH_ROM_MBC1(bkg_tilesetBank);                               //Select Bank Memory
    set_bkg_data(0, 16, bkg_tileset);                               //Load 16 Tiles in VRAM
    SWITCH_ROM_MBC1(bkg_mapBank);                                   //Select Banck Memory
    set_bkg_tiles(0, 0, bkg_mapWidth, bkg_mapHeight, bkg_map);      //Set tiles into Background Layer
    move_bkg(bkg_x, bkg_y);
    SHOW_BKG;
}

void init_pg_sprite(){

    SWITCH_ROM_MBC1(pg_idle_tilesetBank);
    set_sprite_data(0, 32, pg_idle_tileset);
    SPRITES_8x16;
    // asigna a cada sprite un tile, sprite (0-31), posicion del tile
    set_sprite_tile( 0, 0);
    set_sprite_tile( 0, 1);
    set_sprite_tile( 1, 2);
    set_sprite_tile( 1, 3);
    set_sprite_tile( 4, 4);
    set_sprite_tile( 4, 5);
    set_sprite_tile( 5, 6);
    set_sprite_tile( 5, 7);
    set_sprite_tile( 2, 8);
    set_sprite_tile( 2, 9);
    set_sprite_tile( 3, 10);
    set_sprite_tile( 3, 11);
    set_sprite_tile( 6, 12);
    set_sprite_tile( 6, 13);
    set_sprite_tile( 7, 14);
    set_sprite_tile( 7, 15);
    PG.id=last_sprite_id;
    PG.x = 16;
    PG.y = 96;
    moveSprite( PG.id, PG.x, PG.y, 4, 4);

}

void read_joypad() {
    pre_joypad = cur_joypad;
    cur_joypad = joypad();
}

void lights_out_transition() {
    UBYTE transition_phase;
    UBYTE transition_phase_t;
    transition_phase = 0;
    transition_phase_t = 0;
    while (transition_phase != 4) {
        lights_transition_phase(transition_phase);
        if (transition_phase_t++ == LIGHT_TRANS_DUR) {
            transition_phase_t = 0;
            transition_phase++;
        }
        wait_vbl_done();
    }
}

void lights_in_transition() {
    UBYTE transition_phase;
    UBYTE transition_phase_t;
    transition_phase = 3;
    transition_phase_t = 0;
    while (transition_phase != 255) {
        lights_transition_phase(transition_phase);
        if (transition_phase_t++ == LIGHT_TRANS_DUR) {
            transition_phase_t = 0;
            transition_phase--;
        }
        wait_vbl_done();
    }
}

void lights_transition_phase(UBYTE transition_phase) {
    if (transition_phase == 0) {
        BGP_REG = 0xE4;
        OBP0_REG = 0xE4;
        OBP1_REG = 0x1E;
    } else if (transition_phase == 1) {
        BGP_REG = 0x90;
        OBP0_REG = 0x90;
        OBP1_REG = 0x09;
    } else if (transition_phase == 2) {
        BGP_REG = 0x40;
        OBP0_REG = 0x40;
        OBP1_REG = 0x04;
    } else {
        BGP_REG = 0x00;
        OBP0_REG = 0x00;
        OBP1_REG = 0x00;        
    }
}

/*
void init_game_gui() {
    SWITCH_ROM_MBC1(gui_tilesetBank); //Select Bank Memory
    set_win_data(128, 16, gui_tileset); //Load 16 Tiles in VRAM
    SWITCH_ROM_MBC1(gui_mapBank); //Select Banck Memory
    set_win_tiles(0, 0, gui_mapWidth, gui_mapHeight, gui_map); //Set tiles into Window Layer
    move_win(7, 128);
    SHOW_WIN;
}
*/