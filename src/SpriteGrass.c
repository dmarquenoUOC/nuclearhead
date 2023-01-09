#include "Banks/SetAutoBank.h"
#include "main.h"
#include "SpriteManager.h"
#include "Keys.h"
#include "ZGBMain.h"

//PG animations
const UINT8 anim_idle_grass[]= {1, 0};

void START() {
		SetSpriteAnim(THIS, anim_idle_grass, 0);
}

void UPDATE() {

}

void DESTROY() {
	
}