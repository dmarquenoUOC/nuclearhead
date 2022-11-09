#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "SpriteManager.h"

//PG animations
const UINT8 anim_idle[]       = {2, 0, 1};
const UINT8 anim_down[]       = {2, 0, 2};
const UINT8 anim_walk[]       = {4, 3, 4, 5, 4};
const UINT8 anim_jump[]       = {2, 6, 7};

typedef enum  {
	PLAYER_STATE_NORMAL,
	PLAYER_STATE_JUMPING,
	PLAYER_STATE_FALL_RESPAWN,
	PLAYER_STATE_HIT
} PLAYER_STATE;

PLAYER_STATE player_state;
INT16 player_accel_y;
//Walk
INT16 safe_jump_x;
INT16 safe_jump_y;
//Jump
UINT8 check_key_released_on_jump; //when J_A is no longer pressed, and speed going up reset speed to stop jump

void START() {
	SetSpriteAnim(THIS, anim_idle, 3u);
	player_state=PLAYER_STATE_NORMAL;
	player_accel_y = 0;
	safe_jump_x = THIS->x;
	safe_jump_y = THIS->y;

}

void MovePlayer() {
	if(KEY_PRESSED(J_RIGHT)) {
		TranslateSprite(THIS, 1, 0);
		THIS->mirror = NO_MIRROR;
	} else if(KEY_PRESSED(J_LEFT)) {
		TranslateSprite(THIS, -1, 0);
		THIS->mirror = V_MIRROR;
	}
}

void UpdateWalk() {
	safe_jump_x = THIS->x;
	safe_jump_y = THIS->y;

	MovePlayer();

	if(KEY_PRESSED(J_RIGHT) || KEY_PRESSED(J_LEFT) ) {
		SetSpriteAnim(THIS, anim_walk, 15);
	} else {
		SetSpriteAnim(THIS, anim_idle, 3);
	}

	if(KEY_TICKED(J_A)){
		player_state=PLAYER_STATE_JUMPING;
		SetSpriteAnim(THIS, anim_jump, 33u);
		player_accel_y = -50;
		check_key_released_on_jump = 1;
	} 

}

void UpdateJump() {

	if(check_key_released_on_jump){
		if(!KEY_PRESSED(J_A) && player_accel_y < 0) {
			player_accel_y = 0;
		}
	}
	SetSpriteAnim(THIS, anim_walk, 15);
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
}

void DESTROY() {
}