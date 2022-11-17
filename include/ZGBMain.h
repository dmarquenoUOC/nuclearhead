#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES \
_STATE(StateMenu)\
_STATE(StateStory)\
_STATE(StateGame)\
STATE_DEF_END

#define SPRITES \
_SPRITE_DMG(SpritePlayer, player_tileset)\
_SPRITE_DMG(SpritePlayerNuclear, player_nuc_tileset)\
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif