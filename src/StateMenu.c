#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Keys.h"
#include "Music.h"

IMPORT_MAP(title_nuc_map);
DECLARE_MUSIC(Intro);

void START() {
	InitScroll(BANK(title_nuc_map), &title_nuc_map, 0, 0);
    PlayMusic(Intro, 1);
}

void UPDATE() {

    if(KEY_TICKED(J_START)) {
            SetState(StateStory);
    }

}