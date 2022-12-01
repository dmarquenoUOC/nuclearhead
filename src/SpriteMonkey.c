#include "Banks/SetAutoBank.h"
#include "main.h"
#include "SpriteManager.h"
#include "Keys.h"
#include "ZGBMain.h"
#include "Math.h"

void CreateCocoBullet(UINT16 x, UINT16 y, INT8 vx, INT8 vy) BANKED;

//PG animations
const UINT8 anim_idle_monkey[]= {2, 1, 2};
const UINT8 anim_attack_monkey[]= {4, 2, 3, 4, 0, 0};

extern Sprite* scroll_target;

typedef struct {
	UINT8 time_out;
} CUSTOM_DATA;

void START() {
	CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
	SetSpriteAnim(THIS, anim_idle_monkey, 3u);
	data->time_out = 200u;
}


void UPDATE() {

	CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
	UINT8 x;

	if(data->time_out > 50) {
		if (DISTANCE(scroll_target->x, THIS->x) < 80u){
			data->time_out = 0;
			x = ((scroll_target->x - THIS->x) & 0xF000) ? -1 : 1;

			CreateCocoBullet(THIS->x + 6, THIS->y + 6, 0, 1);
		}

	}else{
		data->time_out += 1;
	}

	if(data->time_out < 20u) {
		SetSpriteAnim(THIS, anim_attack_monkey, 3u);
	} else {
		SetSpriteAnim(THIS, anim_idle_monkey, 3u);
	}

}

void DESTROY() {
	
}