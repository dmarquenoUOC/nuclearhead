#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "SpriteManager.h"

void START() {
}

void UPDATE() {
	if(KEY_PRESSED(J_LEFT)) {
		THIS->x --;
	}
	if(KEY_PRESSED(J_RIGHT)) {
		THIS->x ++;
	}
}

void DESTROY() {
}