//Nuclear Head
// TFG UOC Videojocs
#include <gb/gb.h>
#include <gb/hardware.h>

// Tiles
#include "data/tiles/bkg_tileset.h"
//#include "data/tiles/gui_tileset.h"
// Maps
#include "data/maps/bkg_map.h"
//#include "data/maps/gui_map.h"

//Variables
UBYTE bkg_x;
UBYTE bkg_y;

//Functions
void game();
void init();
void init_game_var();
void init_game_bkg();
void init_game_gui();


void main() {
    game();
}

void game() {
    
    init();

    while (1) {
        
        // sincroniza la pantalla
	    wait_vbl_done();
        
    }
}

void init() {
	
	disable_interrupts();
    DISPLAY_OFF;
    init_game_var();
    init_game_bkg();
    //init_game_gui();
    DISPLAY_ON;
    enable_interrupts();

}

void init_game_var() {
    bkg_x = 0;
    bkg_y = 0;
}

void init_game_bkg() {
    SWITCH_ROM_MBC1(bkg_tilesetBank);                               //Select Bank Memory
    set_bkg_data(0, 16, bkg_tileset);                               //Load 16 Tiles in VRAM
    SWITCH_ROM_MBC1(bkg_mapBank);                                   //Select Banck Memory
    set_bkg_tiles(0, 0, bkg_mapWidth, bkg_mapHeight, bkg_map);      //Set tiles into Background Layer
    move_bkg(bkg_x, bkg_y);
    SHOW_BKG;
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