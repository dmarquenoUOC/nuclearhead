#include "Banks/SetAutoBank.h"
#include "main.h"
#include "Scroll.h"
#include "Keys.h"
#include "ZGBMain.h"
#include "Music.h"

DECLARE_MUSIC(gameover);
IMPORT_MAP(game_over);

static UINT8 n_frames_over;

void START() {
	HIDE_WIN;
	n_frames_over = 0;
	InitScroll(BANK(game_over), &game_over, 0, 0);
	PlayMusic(gameover, 0);
}

void UPDATE() {
	n_frames_over ++;

	if(n_frames_over == 300 || KEY_TICKED(J_START) || KEY_TICKED(J_A) || KEY_TICKED(J_B)) {
    	SetState(StateMenu);
	}
}