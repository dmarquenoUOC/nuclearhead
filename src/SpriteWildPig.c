#include "Banks/SetAutoBank.h"
#include "main.h"
#include "SpriteManager.h"
#include "Keys.h"
#include "ZGBMain.h"
#include "Math.h"


//PG animations
const UINT8 anim_idle_pig[]= {2, 0, 1};
const UINT8 anim_walk_pig[]= {2, 2, 3};

extern Sprite* scroll_target;

typedef enum  {
	WILDPIG_STATE_NORMAL,
	WILDPIG_STATE_RUNNING
} WILDPIG_STATE;

INT8 move;
WILDPIG_STATE wildpig_state;
INT8 tile_collision;

void START() {
	SetSpriteAnim(THIS, anim_idle_pig, 3u);
	move=0;
	wildpig_state=WILDPIG_STATE_NORMAL;
}

void init_charge(){

	if(U_LESS_THAN(scroll_target->x, THIS->x)){	
		THIS->mirror=NO_MIRROR;
		//move=move-(INT16)(1 << delta_time);
		move=-1 << delta_time;	
	}else{
		THIS->mirror=V_MIRROR;
		//move=move+(INT16)(1 << delta_time);
		move=1 << delta_time;	
	}

	if(U_LESS_THAN(DISTANCE(scroll_target->x, THIS->x), 60)){
		if(!tile_collision){
			SetSpriteAnim(THIS, anim_walk_pig, 33u);
			wildpig_state=WILDPIG_STATE_RUNNING;
		}
	}
}

void finish_charge() {
	if(tile_collision) {
			SetSpriteAnim(THIS, anim_idle_pig, 3u);
			wildpig_state=WILDPIG_STATE_NORMAL;
			tile_collision=0;
	}

	if (wildpig_state==WILDPIG_STATE_RUNNING && !(U_LESS_THAN(DISTANCE(scroll_target->x, THIS->x), 60))){
		SetSpriteAnim(THIS, anim_idle_pig, 3u);
		wildpig_state=WILDPIG_STATE_NORMAL;
	}

}

void UPDATE() {

	switch(wildpig_state){
		case(WILDPIG_STATE_NORMAL):
		init_charge();
		break;
		case(WILDPIG_STATE_RUNNING):
		tile_collision=TranslateSprite(THIS, move, 0);
		finish_charge();
		break;
	}

}

void DESTROY() {
	
}