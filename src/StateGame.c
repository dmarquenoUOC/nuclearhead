#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "BankManager.h"
#include "Print.h"

IMPORT_TILES(blackfont);
IMPORT_MAP(stage_0_1);
IMPORT_MAP(stage_0_1_tileset);
IMPORT_MAP(hud);

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
UINT8 MAX_HEALTH=3;

// time of state
UINT8 ticks; //next frame will update the value
UINT16 countdown; 

UINT16 x_tmp;
UINT16 y_tmp;
MirroMode mirror_tmp;

void START() {

	last_sprite_loaded=104;
	scroll_target = SpriteManagerAdd(SpritePlayer, 8, 96);
	InitScroll(BANK(stage_0_1), &stage_0_1, collision_tiles_1, 0);
	current_mode=NORMAL_MODE;
	previous_mode=NORMAL_MODE;
	player_health=MAX_HEALTH;
	ticks=59;
	countdown=300;

	//Init Hud 
	INIT_HUD(hud);
	INIT_FONT(blackfont, PRINT_WIN);
	
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
			playerDead();
		}
	}
}

void checkHealth(){
	if (player_health==0){
			playerDead();
		}
}

void playerDead(){

	SpriteManagerRemoveSprite(scroll_target);
	scroll_target = 0;
	CreatePParticle(THIS->x, THIS->y,  1,  1);
	CreatePParticle(THIS->x, THIS->y,  1, -1);
	CreatePParticle(THIS->x, THIS->y, -1,  1);
	CreatePParticle(THIS->x, THIS->y, -1, -1);
	SetState(StateGameOver);
}

void UPDATE() {

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
	}

	updateTime();
	checkHealth();

}
