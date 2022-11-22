#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "Print.h"

IMPORT_MAP(stage_0_1);
const UINT8 collision_tiles_1[] = {4, 5, 7, 8, 16,17,18,19,20,21,44,45,46,0};

typedef enum  {
	NORMAL_MODE,
	NUCLEAR_MODE
} PLAYER_MODE;

PLAYER_MODE current_mode;
PLAYER_MODE previous_mode;

UINT16 x_tmp;
UINT16 y_tmp;
MirroMode mirror_tmp;
Sprite *stone1;

void START() {

	scroll_target = SpriteManagerAdd(SpritePlayer, 8, 96);
	InitScroll(BANK(stage_0_1), &stage_0_1, collision_tiles_1, 0);
	current_mode=NORMAL_MODE;
	previous_mode=NORMAL_MODE;
	
}

void UPDATE() {

	if (previous_mode==NORMAL_MODE && current_mode==NUCLEAR_MODE){
		x_tmp=scroll_target->x;
		y_tmp=scroll_target->y;
		mirror_tmp=scroll_target->mirror;
		SpriteManagerRemoveSprite(scroll_target);
		scroll_target = SpriteManagerAdd(SpritePlayerNuclear, x_tmp, y_tmp);
		scroll_target->mirror=mirror_tmp;
		current_mode=NUCLEAR_MODE;
	    previous_mode=NUCLEAR_MODE;

	}else if (previous_mode==NUCLEAR_MODE && current_mode==NORMAL_MODE){
		x_tmp=scroll_target->x;
		y_tmp=scroll_target->y;
		mirror_tmp=scroll_target->mirror;
		SpriteManagerRemoveSprite(scroll_target);
		scroll_target = SpriteManagerAdd(SpritePlayer, x_tmp, y_tmp);
		scroll_target->mirror=mirror_tmp;
		current_mode=NORMAL_MODE;
	    previous_mode=NORMAL_MODE;
		
	}

	if (scroll_x==80){
		stone1 = SpriteManagerAdd(SpriteStone, scroll_x+160, 80);	
	}
	


}
