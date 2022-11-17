#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Keys.h"

IMPORT_MAP(title_nuc_map);

void START() {
	InitScroll(BANK(title_nuc_map), &title_nuc_map, 0, 0);
}

void UPDATE() {

    if(KEY_TICKED(J_START)) {
            SetState(StateStory);
    }

}