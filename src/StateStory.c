#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Keys.h"

IMPORT_MAP(story_map);

UINT16 scroll_counter;
UINT16 bkg_x;
UINT16 bkg_y;
UINT8 ix;
extern UINT16 hud_map_offset;


void START() {

	hud_map_offset=0;
	InitScroll(BANK(story_map), &story_map, 0, 0);
	scroll_counter=0;
	bkg_y=0;

}

void UPDATE() {

	if(KEY_TICKED(J_START)) {
            SetState(StateGame);
    }

	if (!(scroll_counter++ & 0x03)){
		bkg_y++;
        if (bkg_y > 112) {
            bkg_y = 112;
        }
	}
	delay(50);
	MoveScroll(0,bkg_y);

}
