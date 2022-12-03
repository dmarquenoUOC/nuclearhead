#include "Banks/SetAutoBank.h"
#include "main.h"
#include "Scroll.h"
#include "Keys.h"
#include "ZGBMain.h"

IMPORT_MAP(end_demo);

static UINT8 n_frames;

void START() {
	n_frames = 0;
	InitScroll(BANK(end_demo), &end_demo, 0, 0);
}

void UPDATE() {
	n_frames ++;

	if(KEY_TICKED(J_START) || KEY_TICKED(J_A) || KEY_TICKED(J_B)) {
    	SetState(StateMenu);
	}
}