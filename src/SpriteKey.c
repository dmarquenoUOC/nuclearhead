#include "Banks/SetAutoBank.h"
#include "main.h"
#include "SpriteManager.h"
#include "Keys.h"
#include "ZGBMain.h"

//PG animations
const UINT8 anim_idle_key[]= {1, 0};
extern BYTE key_stage;

void START() {
	if (key_stage==0){
		SetSpriteAnim(THIS, anim_idle_key, 0);
	}else{
		SpriteManagerRemoveSprite(THIS);
	}
}

void UPDATE() {

	if (key_stage==0){
		SetSpriteAnim(THIS, anim_idle_key, 0);
	}else{
		SpriteManagerRemoveSprite(THIS);
	}	

}

void DESTROY() {
	
}