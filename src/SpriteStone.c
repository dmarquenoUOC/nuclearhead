#include "Banks/SetAutoBank.h"
#include "main.h"
#include "SpriteManager.h"

//PG animations
const UINT8 anim_idle_stone[]       = {1, 2};


void START() {
	SetSpriteAnim(THIS, anim_idle_stone, 0);
}


void UPDATE() {

}

void DESTROY() {
}