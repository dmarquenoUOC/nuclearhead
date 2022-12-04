#include "Banks/SetAutoBank.h"
#include "main.h"
#include "Scroll.h"
#include "Keys.h"
#include "ZGBMain.h"
#include "Music.h"

IMPORT_MAP(end_demo);
DECLARE_MUSIC(end);
extern UINT16 hud_map_offset;

void START() {
	hud_map_offset=0;
	InitScroll(BANK(end_demo), &end_demo, 0, 0);
	PlayMusic(end, 0);
}

void UPDATE() {

	if(KEY_TICKED(J_START) || KEY_TICKED(J_A) || KEY_TICKED(J_B)) {
    	SetState(StateMenu);
	}
}