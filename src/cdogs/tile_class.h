/*
    C-Dogs SDL
    A port of the legendary (and fun) action/arcade cdogs.
    Copyright (c) 2018 Cong Xu
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.
    Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/
#pragma once

#include <stdbool.h>

#include "c_hashmap/hashmap.h"
#include "pic_manager.h"

#define TILE_WIDTH      16
#define TILE_HEIGHT     12
#define TILE_SIZE		svec2i(TILE_WIDTH, TILE_HEIGHT)

#define X_TILES			((gGraphicsDevice.cachedConfig.Res.x + TILE_WIDTH - 1) / TILE_WIDTH + 1)

#define X_TILES_HALF    ((X_TILES + 1) / 2)

// + 1 because walls from bottom row show up one row above
#define Y_TILES			((gGraphicsDevice.cachedConfig.Res.y + TILE_HEIGHT - 1) / TILE_HEIGHT + 2)
#define Y_TILES_HALF    ((Y_TILES + 1 / 2)

typedef struct
{
	char *Name;
	const Pic *Pic;
	bool canWalk;	// can walk on tile
	bool isOpaque;	// cannot see through
	bool shootable;	// blocks bullets
	// Mainly for drawing purposes
	bool IsWall;
	bool IsFloor;
	bool IsDoor;
} TileClass;

typedef struct
{
	map_t classes;	// of TileClass *
	map_t customClasses;	// of TileClass *
} TileClasses;
extern TileClasses gTileClasses;
// TODO: remove this after making tile classes data-driven
extern TileClass gTileFloor;
extern TileClass gTileWall;
extern TileClass gTileNothing;
extern TileClass gTileExit;

void TileClassesInit(TileClasses *c);
void TileClassesClearCustom(TileClasses *c);
void TileClassesTerminate(TileClasses *c);

const TileClass *StrTileClass(const char *name);
const TileClass *TileClassesGetMaskedTile(
	TileClasses *c, const PicManager *pm, const TileClass *baseClass,
	const char *style, const char *type,
	const color_t mask, const color_t maskAlt);
const TileClass *TileClassesGetExit(
	TileClasses *c, const PicManager *pm,
	const char *style, const bool isShadow);

TileClass *TileClassAdd(
	map_t classes, const PicManager *pm, const TileClass *base,
	const char *name);
