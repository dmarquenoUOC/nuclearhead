#include "Banks/SetAutoBank.h"
#include "main.h"
#include "Scroll.h"
#include "Keys.h"
#include "ZGBMain.h"

IMPORT_MAP(uoc_logo);

static UINT8 n_frames;

void START() {
	n_frames = 0;
	InitScroll(BANK(uoc_logo), &uoc_logo, 0, 0);
}

void UPDATE() {
	n_frames ++;

	if(n_frames == 100 || KEY_TICKED(J_START) || KEY_TICKED(J_A) || KEY_TICKED(J_B)) {
    	SetState(StateMenu);
	}
}