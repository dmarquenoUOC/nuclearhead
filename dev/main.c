//Nuclear Head
// TFG UOC Videojocs
#include <gb/gb.h>
#include <gb/hardware.h>

// Tiles
#include "data/tiles/bkg_tileset.h"
#include "data/tiles/pg_idle_tileset.h"
//#include "data/tiles/gui_tileset.h"
// Maps
#include "data/maps/bkg_map.h"
//#include "data/maps/gui_map.h"

// rutinas de manejo de metasprites (sprite formado por varios sprites)
#include "utils/char_utils.h"

//Variables
UBYTE bkg_x;
UBYTE bkg_y;

// estructura basica de un personaje, id, posicion, grafico
typedef struct {
	UBYTE id;
	UBYTE x;
	UBYTE y;
	UBYTE graphic;
} Character;

Character PG;
UBYTE sprPlayer; // variable para guardar la memoria del sprite

//Functions
void game();
void init();
void init_game_var();
void init_game_sprite();
void init_game_bkg();
//void init_game_gui();


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
    init_game_sprite();
    DISPLAY_ON;
    enable_interrupts();

}

void init_game_var() {
    bkg_x = 0;
    bkg_y = 0;
}

void init_game_sprite() {
    HIDE_SPRITES;
    SWITCH_ROM_MBC1(pg_idle_tilesetBank);
    set_sprite_data(0, 32, pg_idle_tileset);
    SPRITES_8x16;
    
    // asigna a cada sprite un tile, sprite (0-39), posicion del tile
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
    set_sprite_tile( 8, 15);

    //sprPlayer = loadSpriteGraphics( pg_idle_tileset, 128);
    //PG.id = setupSprite(last_sprite_id, 4, 4 );
    PG.id=last_sprite_id;
    PG.x = 16;
    PG.y = 88;
    moveSprite( PG.id, PG.x, PG.y, 4, 4);
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