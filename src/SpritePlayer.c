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
	PLAYER_STATE_JUMPING
} PLAYER_STATE;


PLAYER_STATE player_state;
INT16 player_accel_y; // y acceleration
INT16 max_accel = 60; //maximum acceleration possible
INT8 tile_collision_x; //to check if we are touching a tile
INT8 tile_collision_y; //to check if we are touching a tile
UINT8 groundCollision; //to check if we are touching the ground.
UINT8 isjumping; //to check if we are jumping
UINT8 jumpPeak; //to check if we are in the jump Peak

void START() {
	SetSpriteAnim(THIS, anim_idle, 3u);
	player_state=PLAYER_STATE_NORMAL;
	player_accel_y = 0;
	jumpPeak = 0;
	isjumping=0;
	groundCollision=0;
}


void MovePlayer() {

	if(KEY_PRESSED(J_RIGHT)) {
		tile_collision_x = TranslateSprite(THIS, 1 << delta_time, 0);
		THIS->mirror = NO_MIRROR;
	} else if(KEY_PRESSED(J_LEFT)) {
		tile_collision_x = TranslateSprite(THIS, -1 << delta_time, 0);
		THIS->mirror = V_MIRROR;
	}
}


void UpdateWalk() {

	MovePlayer();

	if(KEY_PRESSED(J_RIGHT) || KEY_PRESSED(J_LEFT) ) {
		SetSpriteAnim(THIS, anim_walk, 15u);
	} else {
		SetSpriteAnim(THIS, anim_idle, 3u);
	}

	if(KEY_TICKED(J_A)){
		player_state=PLAYER_STATE_JUMPING;
		player_accel_y = -50;
		isjumping = 1;
		SetSpriteAnim(THIS, anim_jump, 33u);
	} 

	//Check if falling
	//if ((player_accel_y >> 4) > 1) {
	//	player_state = PLAYER_STATE_NORMAL;
	//}

}

void UpdateJump() {

	tile_collision_y = TranslateSprite(THIS, 0, (player_accel_y >> 4));

	isjumping = 1;

	if (tile_collision_y!=0){
		jumpPeak = 1;
		SetSpriteAnim(THIS, anim_fall, 33u);
	}

	if (jumpPeak == 0 && KEY_PRESSED(J_A) && player_accel_y > -35) {
    	player_accel_y -= 2;
	}else if (player_accel_y < 30) { //do another iteration 
        player_accel_y += 2;
	}

	MovePlayer();

}

void UPDATE() {

	switch(player_state){
		case(PLAYER_STATE_NORMAL):
			UpdateWalk();
		break;
		case (PLAYER_STATE_JUMPING):
			UpdateJump();
		break;
	}

	if (player_accel_y > 0) {
			groundCollision = tile_collision_y;

			if (groundCollision == 0) {
				player_state = PLAYER_STATE_JUMPING;
				isjumping = 1;
			}
			else {
				if (player_state == PLAYER_STATE_JUMPING) {
					player_state = PLAYER_STATE_NORMAL;
					isjumping=0;
				}
				player_accel_y = 0;
			}
	}
	else {
		groundCollision = 0;
		player_state == PLAYER_STATE_JUMPING;
	}
}

void DESTROY() {
}