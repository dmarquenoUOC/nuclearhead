#include "Banks/SetAutoBank.h"
#include "main.h"
#include "ZGBMain.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "Scroll.h"

//PG animations
const UINT8 anim_idle[]       = {2, 0, 1};
const UINT8 anim_walk[]       = {4, 3, 4, 5, 4};
const UINT8 anim_jump[]       = {1, 6};
const UINT8 anim_fall[]       = {1, 7};
const UINT8 anim_hit[]        = {1, 2};

typedef enum  {
	PLAYER_STATE_NORMAL,
	PLAYER_STATE_JUMPING,
	PLAYER_STATE_FALLING,
	PLAYER_STATE_HIT
} PLAYER_STATE;

typedef enum  {
	NORMAL_MODE,
	NUCLEAR_MODE
} PLAYER_MODE;

typedef enum  {
	GROUNDED,
	INAIR
} MOVE_STATE;

PLAYER_STATE player_state;
MOVE_STATE move_state;
INT16 player_accel_y; // y acceleration
INT8 tile_collision_x; //to check if we are touching a tile
INT8 tile_collision_y; //to check if we are touching a tile
INT8 stop_r;
INT8 stop_l;
INT8 damage_recoil;


extern PLAYER_MODE current_mode;
extern PLAYER_MODE previous_mode;
extern UINT8 player_health;

void START() {
	SetSpriteAnim(THIS, anim_idle, 3u);
	player_state=PLAYER_STATE_NORMAL;
	player_accel_y = 0;
	damage_recoil=0;
	current_mode=NORMAL_MODE;
	previous_mode=NORMAL_MODE;
	stop_r=0;
	stop_l=0;
	if (THIS->y<96){
		move_state=INAIR;
	}else move_state=GROUNDED;
}


void MovePlayer() {

	if (!(KEY_PRESSED(J_B))) {

		if(KEY_PRESSED(J_RIGHT) && stop_r==0 && player_state!=PLAYER_STATE_HIT) {
			tile_collision_x = TranslateSprite(THIS, 1 << delta_time, 0);
			THIS->mirror = NO_MIRROR;
		} else if(KEY_PRESSED(J_LEFT) && stop_l==0 && player_state!=PLAYER_STATE_HIT) {
			tile_collision_x = TranslateSprite(THIS, -1 << delta_time, 0);
			THIS->mirror = V_MIRROR;
		}
	}

	tile_collision_y = TranslateSprite(THIS, 0, player_accel_y >> 4);
}


void UpdateWalk() {


	//Check idle anim or walk
	if((KEY_PRESSED(J_RIGHT) || KEY_PRESSED(J_LEFT)) && !(KEY_PRESSED(J_B))) {
		SetSpriteAnim(THIS, anim_walk, 15u);
	} else {
		SetSpriteAnim(THIS, anim_idle, 3u);
	}

	//Check Jumping
	if(KEY_TICKED(J_A)){
		player_state=PLAYER_STATE_JUMPING;
		player_accel_y = -35;
	} 

	//Check falling
	/*if ((player_accel_y >> 4) > 1) {
		player_state = PLAYER_STATE_FALLING;
	}*/
	if (tile_collision_y=0) {
		player_state = PLAYER_STATE_FALLING;
	}

}

void updateAcceleration(){
	
	if (player_accel_y < 35) { 
        player_accel_y += 2;
	}else if (KEY_PRESSED(J_A) && player_accel_y > -35) {
    	player_accel_y -= 2;
	}

	//Check collision with floor or Top	
	if (!tile_collision_y && delta_time != 0 && player_accel_y < 35)
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

		if (player_accel_y>15 && player_state == PLAYER_STATE_JUMPING){
			player_state = PLAYER_STATE_FALLING;
		}
	}

	
}

void checkGorundedN(){

	//Check collision with floor
	if (player_state == PLAYER_STATE_NORMAL){
		
		if (move_state==INAIR && player_accel_y < 35)
		{ //Do another iteration if there is no collision
			//player_accel_y += 2;
			tile_collision_y = TranslateSprite(THIS, 0, player_accel_y >> 4);
		}
		if (tile_collision_y!=0){
			player_accel_y = 0;
			move_state==GROUNDED;
		}
	}

	if (THIS->y<96){
		move_state=INAIR;
	}else move_state=GROUNDED;


}

void CheckNuclear(){
	if(KEY_PRESSED(J_B)  &&  player_state==PLAYER_STATE_NORMAL){
		current_mode=NUCLEAR_MODE;
		previous_mode=NORMAL_MODE;
	}	 
}

void Hit(){
		player_health--;
		player_state=PLAYER_STATE_HIT;
		SetSpriteAnim(THIS, anim_hit, 10u);		
}

void UpdateHudLife() {
	for (UINT8 i = 0; i < 3; ++i)
		UPDATE_HUD_TILE(1 + i, 0, i < player_health ? 1 : 2);	
}

void UpdateHit(){

	if (damage_recoil==5){
		damage_recoil=0;
		player_state=PLAYER_STATE_NORMAL;
	}else{
		if(THIS->mirror==V_MIRROR) {
			tile_collision_x = TranslateSprite(THIS, 3 << delta_time, 0);
		} else{
			tile_collision_x = TranslateSprite(THIS, -3 << delta_time, 0);
		}
	}
	damage_recoil++; 			
}

void UPDATE() {

	UINT8 i;
    Sprite *spr;

	switch(player_state){
		case(PLAYER_STATE_NORMAL):
			UpdateWalk();
			CheckNuclear();
		break;
		case (PLAYER_STATE_JUMPING):
			SetSpriteAnim(THIS, anim_jump, 33u);
		break;
		case PLAYER_STATE_FALLING:
			SetSpriteAnim(THIS, anim_fall, 33u);
		break;
		case PLAYER_STATE_HIT:
			 UpdateHit();
		break;
	}

	MovePlayer();
	updateAcceleration();
	checkGorundedN();

	//Check Sprites
	SPRITEMANAGER_ITERATE(i, spr) {

		//stop if touch Stone
		if (spr->type == SpriteStone) {
            if (CheckCollision(THIS, spr)) {
				if (KEY_PRESSED(J_RIGHT)){
					stop_r=1; // stop to right
					stop_l=0; // move to left	
				}else if (KEY_PRESSED(J_LEFT)){
					stop_r=0; // move to right
					stop_l=1; // stop to left
				}
            }else{
				stop_r=0; // move to right
				stop_l=0; // move to left
			} 
        }else if (spr->type == SpriteMonkey || spr->type == SpriteCocoBullet){ //Check enemy collision
			if(CheckCollision(THIS, spr)) {
					Hit();
					UpdateHudLife();
			}
		}

	}

	

}

void DESTROY() {
}