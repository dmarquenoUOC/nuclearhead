#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

IMPORT_MAP(stage_0_1);
const UINT8 collision_tiles_1[] = {4, 5, 0};

void START() {

	scroll_target = SpriteManagerAdd(SpritePlayer, 8, 96);
	InitScroll(BANK(stage_0_1), &stage_0_1, collision_tiles_1, 0);
	
}

void UPDATE() {

}
