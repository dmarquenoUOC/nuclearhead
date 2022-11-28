#include "Banks/SetAutoBank.h"
#include "main.h"
#include "SpriteManager.h"
#include "Keys.h"
#include "ZGBMain.h"

//PG animations
const UINT8 anim_idle_stone[]= {1, 1};
const UINT8 anim_explosion_stone[]= {4, 2, 3, 4, 0, 0};

UINT8 stone1status;
extern Sprite* scroll_target;

typedef struct {
	UINT8 time_out;
} CUSTOM_DATA;

void START() {
	SetSpriteAnim(THIS, anim_idle_stone, 0);
	stone1status=0;
	if (scroll_target->mirror == NO_MIRROR){
		THIS->mirror = NO_MIRROR;
	}else{
		THIS->mirror = V_MIRROR;
	}
}


void UPDATE() {

	if (stone1status==1){

		
		SetSpriteAnim(THIS, anim_explosion_stone, 10u);
		
		if(THIS->anim_frame == 3) {
			SpriteManagerRemoveSprite(THIS);
		}	

	}

}

void DESTROY() {
	
}