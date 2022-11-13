#include "Banks/SetAutoBank.h"
#include "main.h"

#include "Keys.h"
#include "SpriteManager.h"

//PG animations
const UINT8 anim_idle[]       = {2, 0, 1};
const UINT8 anim_down[]       = {2, 0, 2};
const UINT8 anim_walk[]       = {4, 3, 4, 5, 4};
const UINT8 anim_jump[]       = {1, 6};
const UINT8 anim_fall[]       = {1, 7};

typedef enum  {
	PLAYER_STATE_NORMAL,
	PLAYER_STATE_JUMPING,
	PLAYER_STATE_FALLING
} PLAYER_STATE;


PLAYER_STATE player_state;
INT16 player_accel_y; // y acceleration
INT16 current_height; // Current height
INT8 tile_collision_x; //to check if we are touching a tile
INT8 tile_collision_y; //to check if we are touching a tile
UINT8 groundCollision; //to check if we are touching the ground.
UINT8 jumpPeak; //to check if we are in the jump Peak

void START() {
	SetSpriteAnim(THIS, anim_idle, 3u);
	player_state=PLAYER_STATE_NORMAL;
	player_accel_y = 0;
	jumpPeak = 0;
	groundCollision=0;
	current_height = THIS->y;
}


void MovePlayer() {

	if(KEY_PRESSED(J_RIGHT)) {
		tile_collision_x = TranslateSprite(THIS, 1 << delta_time, 0);
		THIS->mirror = NO_MIRROR;
	} else if(KEY_PRESSED(J_LEFT)) {
		tile_collision_x = TranslateSprite(THIS, -1 << delta_time, 0);
		THIS->mirror = V_MIRROR;
	}

	tile_collision_y = TranslateSprite(THIS, 0, player_accel_y >> 4);
}


void UpdateWalk() {

	//Check idle anim or walk
	if(KEY_PRESSED(J_RIGHT) || KEY_PRESSED(J_LEFT) ) {
		SetSpriteAnim(THIS, anim_walk, 15u);
	} else {
		SetSpriteAnim(THIS, anim_idle, 3u);
	}

	//Check Jumping
	if(KEY_TICKED(J_A)){
		player_state=PLAYER_STATE_JUMPING;
		player_accel_y = -60;
	} 

	//Check falling
	if ((player_accel_y >> 4) > 1) {
		player_state = PLAYER_STATE_FALLING;
	}

}

void updateAcceleration(){

	
	if (player_accel_y < 60) { 
        player_accel_y += 2;
	}else if (KEY_PRESSED(J_A) && player_accel_y > -60) {
    	player_accel_y -= 2;
	}

	//Check collision with floor or Top	
	if (!tile_collision_y && delta_time != 0 && player_accel_y < 60)
	{ //Do another iteration if there is no collision
		player_accel_y += 2;
		tile_collision_y = TranslateSprite(THIS, 0, player_accel_y >> 4);
	}
	if (tile_collision_y!=0){

		player_accel_y = 0;

		if (player_state == PLAYER_STATE_JUMPING)
		{
			player_state = PLAYER_STATE_FALLING;

		}else if (player_state == PLAYER_STATE_FALLING)
		{
			player_state = PLAYER_STATE_NORMAL;
		}

	}else{

		if (player_accel_y>0 && player_state == PLAYER_STATE_JUMPING){
			player_state = PLAYER_STATE_FALLING;
		}
	}	

}

void UPDATE() {

	switch(player_state){
		case(PLAYER_STATE_NORMAL):
			UpdateWalk();
		break;
		case (PLAYER_STATE_JUMPING):
			SetSpriteAnim(THIS, anim_jump, 33u);
		break;
		case PLAYER_STATE_FALLING:
			SetSpriteAnim(THIS, anim_fall, 33u);
		break;
	}

	MovePlayer();
	updateAcceleration();

}

void DESTROY() {
}