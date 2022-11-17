#include "Banks/SetAutoBank.h"
#include "main.h"

#include "Keys.h"
#include "SpriteManager.h"

//PG animations
const UINT8 anim_idle_nuc[]       = {2, 0, 1};
const UINT8 anim_walk_nuc[]       = {4, 3, 4, 5, 4};

typedef enum  {
	PLAYER_STATE_NUCLEAR,
} PLAYER_STATE;

typedef enum  {
	NORMAL_MODE,
	NUCLEAR_MODE
} PLAYER_MODE;


PLAYER_STATE player_state_nuc;
INT8 tile_collision_nuc; //to check if we are touching a tile
extern PLAYER_MODE current_mode;
extern PLAYER_MODE previous_mode;

void START() {

	SetSpriteAnim(THIS, anim_idle_nuc, 3u);
	player_state_nuc=PLAYER_STATE_NUCLEAR;

}


void MovePlayerNuc() {

	if(KEY_PRESSED(J_RIGHT)) {
		tile_collision_nuc = TranslateSprite(THIS, 1 << delta_time, 0);
		THIS->mirror = NO_MIRROR;
	} else if(KEY_PRESSED(J_LEFT)) {
		tile_collision_nuc = TranslateSprite(THIS, -1 << delta_time, 0);
		THIS->mirror = V_MIRROR;
	}

}


void UpdateWalkNuc() {

	//Check idle anim or walk
	if(KEY_PRESSED(J_RIGHT) || KEY_PRESSED(J_LEFT) ) {
		SetSpriteAnim(THIS, anim_walk_nuc, 15u);
	} else {
		SetSpriteAnim(THIS, anim_idle_nuc, 3u);
	}
}

void CheckNormal(){

	if(KEY_PRESSED(J_B) || KEY_TICKED(J_B) ){
		current_mode=NORMAL_MODE;
		previous_mode=NUCLEAR_MODE;
	}	 
	
}

void UPDATE() {

	switch(player_state_nuc){
		case(PLAYER_STATE_NUCLEAR):
			UpdateWalkNuc();
		break;
	}

	MovePlayerNuc();

	CheckNormal();

}

void DESTROY() {
}