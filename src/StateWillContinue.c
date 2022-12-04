#include "Banks/SetAutoBank.h"
#include "main.h"
#include "Scroll.h"
#include "Keys.h"
#include "ZGBMain.h"
#include "SpriteManager.h"

IMPORT_MAP(continued);

static UINT8 n_frames;
extern UINT16 hud_map_offset;

void START() {
	hud_map_offset=0;
	n_frames = 0;
	InitScroll(BANK(continued), &continued, 0, 0);
}

void UPDATE() {
	n_frames ++;
	if(n_frames == 50 || KEY_TICKED(J_START) || KEY_TICKED(J_A) || KEY_TICKED(J_B)) {
    	SetState(StateEnd);
	}
}