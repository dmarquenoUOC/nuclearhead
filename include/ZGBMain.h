#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES \
_STATE(StateEngine)\
_STATE(StateMenu)\
_STATE(StateStory)\
_STATE(StateGame)\
_STATE(StateGameOver)\
_STATE(StateWillContinue)\
_STATE(StateEnd)\
STATE_DEF_END

#define SPRITES \
_SPRITE_DMG(SpritePlayer, player_tileset)\
_SPRITE_DMG(SpritePlayerNuclear, player_nuc_tileset)\
_SPRITE_DMG(SpriteMonkey, EnemyMonkey_tileset)\
_SPRITE_DMG(SpriteStone, stone_tileset)\
_SPRITE_DMG(SpriteCocoBullet, cocoBullet_tileset)\
_SPRITE_DMG(SpritePlayerParticle, playerParticle)\
_SPRITE_DMG(SpriteKey, key_tileset)\
_SPRITE_DMG(SpriteHit, hit_tileset)\
_SPRITE_DMG(SpriteWildPig, EnemyWildPig_tileset)\
_SPRITE_DMG(SpriteGrass, grass_tileset)\
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif