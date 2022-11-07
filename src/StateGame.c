#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

IMPORT_MAP(stage_1_1);

void START() {

	scroll_target = SpriteManagerAdd(SpritePlayer, 8, 96);
	InitScroll(BANK(stage_1_1), &stage_1_1, 0, 0);
	
}

void UPDATE() {

}
