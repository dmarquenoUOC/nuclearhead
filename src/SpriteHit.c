#include "Banks/SetAutoBank.h"
#include "main.h"
#include "SpriteManager.h"

const UINT8 hit_anim[] = {4, 1, 2, 2, 2};

void START() {
	SetSpriteAnim(THIS, hit_anim, 33);
}

void UPDATE() {
		SpriteManagerRemove(THIS_IDX);
}

void DESTROY () {
}