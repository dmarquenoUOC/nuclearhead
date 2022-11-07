#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES \
_STATE(StateMenu)\
_STATE(StateGame)\
STATE_DEF_END

#define SPRITES \
_SPRITE_DMG(SpritePlayer, pg_idle_tileset)\
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif