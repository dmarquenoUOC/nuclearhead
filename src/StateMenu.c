#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Keys.h"

IMPORT_MAP(title_map);

void START() {
	InitScroll(BANK(title_map), &title_map, 0, 0);
}

void UPDATE() {

    if(KEY_TICKED(J_START)) {
            SetState(StateGame);
    }

}