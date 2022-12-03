#include "Banks/SetAutoBank.h"
#include "main.h"
#include "Scroll.h"
#include "Keys.h"
#include "ZGBMain.h"
#include "Music.h"

IMPORT_MAP(end_demo);
DECLARE_MUSIC(end);

static UINT8 n_frames;

void START() {
	n_frames = 0;
	InitScroll(BANK(end_demo), &end_demo, 0, 0);
	PlayMusic(end, 0);
}

void UPDATE() {
	n_frames ++;

	if(KEY_TICKED(J_START) || KEY_TICKED(J_A) || KEY_TICKED(J_B)) {
    	SetState(StateMenu);
	}
}