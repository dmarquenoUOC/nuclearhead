#include "Banks/SetAutoBank.h"
#include "main.h"
#include "SpriteManager.h"
#include "ZGBMain.h"

typedef struct {
	INT8 vx;
	INT8 vy;
} CUSTOM_DATA;

void CreateCocoBullet(UINT16 x, UINT16 y, INT8 vx, INT8 vy) BANKED {
	Sprite* spr = SpriteManagerAdd(SpriteCocoBullet, x, y);
	CUSTOM_DATA* data = (CUSTOM_DATA*)spr->custom_data;

	data->vx = vx;
	data->vy = vy;
}

void START() {
}


void UPDATE() {
	CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
	
	THIS->x += (INT16)data->vx << delta_time;
	THIS->y += (INT16)data->vy << delta_time;

}

void DESTROY() {
	
}