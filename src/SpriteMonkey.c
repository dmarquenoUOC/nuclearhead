#include "Banks/SetAutoBank.h"
#include "main.h"
#include "SpriteManager.h"
#include "Keys.h"
#include "ZGBMain.h"

//PG animations
const UINT8 anim_idle_monkey[]= {2, 1, 2};
const UINT8 anim_attack_monkey[]= {4, 2, 3, 4, 0, 0};

extern UINT8 stone1status;

void START() {
	SetSpriteAnim(THIS, anim_idle_monkey, 3u);
}


void UPDATE() {

}

void DESTROY() {
	
}