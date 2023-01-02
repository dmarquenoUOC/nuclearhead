#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "BankManager.h"
#include "Print.h"
#include "Music.h"
#include "Sounds.h"

IMPORT_TILES(blackfont);
IMPORT_MAP(stage_0_1);
IMPORT_MAP(stage_0_1_tileset);
IMPORT_MAP(hud);
DECLARE_MUSIC(stage0);
DECLARE_MUSIC(nuclear);


struct MapInfoBanked {
	UINT8 bank;
	struct MapInfo* map;
};
#define BANKED_MAP(MAP) {BANK(MAP), &MAP}

const struct MapInfoBanked levels[] = {
	BANKED_MAP(stage_0_1),
};
UINT8 current_stage = 0;

const UINT8 collision_tiles_1[] = {4, 5, 7, 8, 16,17,18,19,20,21,50,51,53,58,0};
extern INT16 last_sprite_loaded;
INT16 last_sprite_loaded_tmp;

typedef enum  {
	NORMAL_MODE,
	NUCLEAR_MODE
} PLAYER_MODE;

PLAYER_MODE current_mode;
PLAYER_MODE previous_mode;
UINT8 player_health;
UINT8 player_dead;
UINT8 MAX_HEALTH=3;

// time of state
UINT8 ticks; //next frame will update the value
UINT8 wait_end_time;
UINT16 countdown;
UINT16 nuclear_time;
UINT16 nuclear_time_MAX;
UINT16 nuclear_time_80;
UINT16 nuclear_time_70;
UINT16 nuclear_time_50;
UINT16 nuclear_time_40;
UINT16 nuclear_time_20;  


UINT16 x_tmp;
UINT16 y_tmp;
MirroMode mirror_tmp;

//keys
BYTE open[] = {0, 0, 0, 0, 0};
BYTE open_door;
BYTE key_stage;
UINT16 n_frames;

void START() {
	//Init level Map
	const UINT8* coll_list = 0;
	switch(current_stage) {
		case 0:  
			coll_list = collision_tiles_1;
			break;
	}

	InitScroll(levels->bank, levels->map, coll_list, 0);
	//InitScroll(BANK(stage_0_1), &stage_0_1, collision_tiles_1, 0);
	
	//Init PJ
	last_sprite_loaded=104;
	scroll_target = SpriteManagerAdd(SpritePlayer, 8, 96);
	
	//Init Variables
	key_stage=0;
	open_door=0;
	n_frames=0;
	current_mode=NORMAL_MODE;
	previous_mode=NORMAL_MODE;
	player_health=MAX_HEALTH;
	player_dead=0;
	ticks=59;
	wait_end_time=0;
	countdown=300;  
	nuclear_time_MAX=200;
	nuclear_time_80=nuclear_time_MAX*0.8;
	nuclear_time_70=nuclear_time_MAX*0.7;
	nuclear_time_50=nuclear_time_MAX*0.5;
	nuclear_time_40=nuclear_time_MAX*0.4;
	nuclear_time_20=nuclear_time_MAX*0.2;
	nuclear_time=nuclear_time_MAX;

	//Init Hud 
	INIT_HUD(hud);
	INIT_FONT(blackfont, PRINT_WIN);

	PlayMusic(stage0, 1);
	
}

void checkPlayerMode(){

	if (previous_mode==NORMAL_MODE && current_mode==NUCLEAR_MODE){
		x_tmp=scroll_target->x;
		y_tmp=scroll_target->y;
		mirror_tmp=scroll_target->mirror;
		disable_interrupts();
        DISPLAY_OFF;
		SpriteManagerRemoveSprite(scroll_target);
		last_sprite_loaded_tmp=last_sprite_loaded;
		last_sprite_loaded=scroll_target->first_tile+104;
		spriteIdxs[SpritePlayerNuclear]=128;
		scroll_target = SpriteManagerAdd(SpritePlayerNuclear, x_tmp, y_tmp);
		last_sprite_loaded=last_sprite_loaded_tmp;
		DISPLAY_ON;
        enable_interrupts();
		scroll_target->mirror=mirror_tmp;
		current_mode=NUCLEAR_MODE;
	    previous_mode=NUCLEAR_MODE;
		gbt_stop();
		PlayMusic(nuclear,1);

	}else if (previous_mode==NUCLEAR_MODE && current_mode==NORMAL_MODE){
		x_tmp=scroll_target->x;
		y_tmp=scroll_target->y;
		mirror_tmp=scroll_target->mirror;
		disable_interrupts();
        DISPLAY_OFF;
		SpriteManagerRemoveSprite(scroll_target);
		last_sprite_loaded_tmp=last_sprite_loaded;
		last_sprite_loaded=scroll_target->first_tile+104;
		spriteIdxs[SpritePlayer]=128;
		scroll_target = SpriteManagerAdd(SpritePlayer, x_tmp, y_tmp);
		last_sprite_loaded=last_sprite_loaded_tmp;
		DISPLAY_ON;
        enable_interrupts();
		scroll_target->mirror=mirror_tmp;
		current_mode=NORMAL_MODE;
	    previous_mode=NORMAL_MODE;
		gbt_stop();
		PlayMusic(stage0,1);
	}

}

void updateTime(){

	ticks++;
	if(ticks == 60) {
		ticks = 0;
		countdown--;
		PRINT_POS(17, 0);
		Printf("%d", countdown);
		if (countdown==0){
			//Time up!
			SetState(StateGameOver);
		}
	}
}

void checkHealth(){
	if (player_dead==1){
		wait_end_time ++;
		if(wait_end_time > 80) {
			wait_end_time = 0;
			SetState(StateGameOver);
		}
	}
}

void updateNuclearHudSprite(){

	if(nuclear_time == 0){
		UPDATE_HUD_TILE(9, 0, 5);
		UPDATE_HUD_TILE(8, 0, 3);
		UPDATE_HUD_TILE(7, 0, 4);
	}else if(nuclear_time < nuclear_time_20){
		UPDATE_HUD_TILE(9, 0, 5);
		UPDATE_HUD_TILE(8, 0, 3);
		UPDATE_HUD_TILE(7, 0, 10);
	}else if(nuclear_time < nuclear_time_40){
		UPDATE_HUD_TILE(9, 0, 5);
		UPDATE_HUD_TILE(8, 0, 3);
		UPDATE_HUD_TILE(7, 0, 7);
	}else if(nuclear_time < nuclear_time_50){
		UPDATE_HUD_TILE(9, 0, 5);
		UPDATE_HUD_TILE(8, 0, 9);
		UPDATE_HUD_TILE(7, 0, 7);
	}else if(nuclear_time < nuclear_time_70){
		UPDATE_HUD_TILE(9, 0, 5);
		UPDATE_HUD_TILE(8, 0, 6);
		UPDATE_HUD_TILE(7, 0, 7);
	}else if(nuclear_time < nuclear_time_80){
		UPDATE_HUD_TILE(9, 0, 11);
		UPDATE_HUD_TILE(8, 0, 6);
		UPDATE_HUD_TILE(7, 0, 7);
	}else {
		UPDATE_HUD_TILE(9, 0, 8);
		UPDATE_HUD_TILE(8, 0, 6);
		UPDATE_HUD_TILE(7, 0, 7);	
	}
}

void updateNuclearBar(){

	if (current_mode==NUCLEAR_MODE){
		nuclear_time--;
		if (nuclear_time==0){
			previous_mode=NUCLEAR_MODE;
			current_mode=NORMAL_MODE;	
		}
	}else{
		if(nuclear_time<nuclear_time_MAX)
			nuclear_time++;	
	}

	updateNuclearHudSprite();
	
}

void checkLevelKey(){

	if (key_stage){
		PlayFx(FX_OBJECT);
		UPDATE_HUD_TILE(12, 0, 17);
	}

}

void checkDoor(){
	if(open_door){
		n_frames ++;
		open[current_stage]=open_door;

		if(n_frames==25){
			SetState(StateWillContinue);
		}

	}
}

void UPDATE() {

	checkPlayerMode();
	updateTime();
	updateNuclearBar();
	checkHealth();
	checkLevelKey();
	checkDoor();

}
