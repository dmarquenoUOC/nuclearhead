#include "Banks/SetAutoBank.h"
#include "main.h"
#include "SpriteManager.h"

const UINT8 anim_idle_limit[]       = {1, 2};


void START() {
	SetSpriteAnim(THIS, anim_idle_limit, 0);
}


void UPDATE() {

}

void DESTROY() {
}