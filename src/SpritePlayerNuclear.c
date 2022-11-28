#include "Banks/SetAutoBank.h"
#include "main.h"
#include "ZGBMain.h"
#include "Keys.h"
#include "SpriteManager.h"

//PG animations
const UINT8 anim_idle_nuc[]       = {2, 0, 1};
const UINT8 anim_walk_nuc[]       = {4, 3, 4, 5, 4};
const UINT8 anim_beat_nuc[]       = {1, 2};
const UINT8 anim_barrier_nuc[]    = {2, 6, 7};

typedef enum  {
	PLAYER_STATE_NUCLEAR,
	PLAYER_STATE_NUC_FALLING
} PLAYER_STATE;

typedef enum  {
	NORMAL_MODE,
	NUCLEAR_MODE
} PLAYER_MODE;

typedef enum  {
	GROUNDED,
	INAIR
} MOVE_STATE;


PLAYER_STATE player_state_nuc;
MOVE_STATE move_nuc_state;
INT8 tile_collision_nuc_x; //to check if we are touching a tile
INT8 tile_collision_nuc_y; //to check if we are touching a tile
INT8 stop_nuc_r;
INT8 stop_nuc_l;
INT16 player_nuc_accel_y; // y acceleration

extern PLAYER_MODE current_mode;
extern PLAYER_MODE previous_mode;
extern UINT8 stone1status;

void START() {

	SetSpriteAnim(THIS, anim_idle_nuc, 3u);
	player_state_nuc=PLAYER_STATE_NUCLEAR;
	stop_nuc_r=0;
	stop_nuc_l=0;
	player_nuc_accel_y=0;
	if (THIS->y<96){
		move_nuc_state=INAIR;
	}else move_nuc_state=GROUNDED;

}

void MovePlayerNuc() {

	if (!(KEY_PRESSED(J_B))) {
		if(KEY_PRESSED(J_RIGHT) && stop_nuc_r==0) {
			tile_collision_nuc_x = TranslateSprite(THIS, 1 << delta_time, 0);
			THIS->mirror = NO_MIRROR;
		} else if(KEY_PRESSED(J_LEFT) && stop_nuc_l==0) {
			tile_collision_nuc_x = TranslateSprite(THIS, -1 << delta_time, 0);
			THIS->mirror = V_MIRROR;
		}
	}

	tile_collision_nuc_y = TranslateSprite(THIS, 0, player_nuc_accel_y >> 4);




}


void CheckGrounded(){ //Check if player is not in grounded

	//Check collision with floor or Top	
	if (move_nuc_state==INAIR && player_nuc_accel_y < 35)
	{ //Do another iteration if there is no collision
		player_nuc_accel_y += 2;
		tile_collision_nuc_y = TranslateSprite(THIS, 0, player_nuc_accel_y >> 4);
	}
	if (tile_collision_nuc_y!=0){

		player_nuc_accel_y = 0;
		move_nuc_state==GROUNDED;

	}

	if (THIS->y<96){
		move_nuc_state=INAIR;
	}else move_nuc_state=GROUNDED;

}


void UpdateWalkNuc() {

	//Check idle anim or walk
	if((KEY_PRESSED(J_RIGHT) || KEY_PRESSED(J_LEFT)) && !(KEY_PRESSED(J_B))) {
		SetSpriteAnim(THIS, anim_walk_nuc, 15u);
	} else {
		SetSpriteAnim(THIS, anim_idle_nuc, 3u);
	}
}

void UpdateBarrierNuc() {

	if(KEY_TICKED(J_DOWN)) {
		SetSpriteAnim(THIS, anim_barrier_nuc, 3u);
	}
}

void UpdateBeat(){

	if (KEY_PRESSED(J_A)){
		SetSpriteAnim(THIS, anim_beat_nuc, 3u);
	}

}

void CheckNormal(){

	if(KEY_PRESSED(J_B) || KEY_TICKED(J_B)){
		current_mode=NORMAL_MODE;
		previous_mode=NUCLEAR_MODE;
	}	 
	
}

void UPDATE() {

	UINT8 i;
    Sprite *spr;

	switch(player_state_nuc){
		case(PLAYER_STATE_NUCLEAR):
			UpdateWalkNuc();
		break;
	}

	UpdateBeat();
	UpdateBarrierNuc();
	MovePlayerNuc();
	CheckGrounded();
	CheckNormal();

	//Check Sprites
	SPRITEMANAGER_ITERATE(i, spr) {

		//stop if touch Stone
		if (spr->type == SpriteStone) {
            if (CheckCollision(THIS, spr)) {
				if (KEY_PRESSED(J_RIGHT)){
					stop_nuc_r=1; // stop to right
					stop_nuc_l=0; // move to left	
				}else if (KEY_PRESSED(J_LEFT)){
					stop_nuc_r=0; // move to right
					stop_nuc_l=1; // stop to left
				}else if (KEY_PRESSED(J_A)){
					stone1status=1;
					stop_nuc_r=0; // move to right
					stop_nuc_l=0; // move to left
				}
            }else{
				stop_nuc_r=0; // move to right
				stop_nuc_l=0; // move to left
			} 

			
        }

	}

}

void DESTROY() {
}