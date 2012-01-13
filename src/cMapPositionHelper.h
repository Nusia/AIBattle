#pragma once

#include <irrlicht.h>
#include <math.h>

class cMapPositionHelper
{
public:

	static const irr::core::vector2d<irr::s32> PixelToSquarePos( const irr::core::vector2d<irr::s32> pos )
	{
		irr::core::vector2d<irr::s32> tmpPos;
		tmpPos.X = (irr::s32)floor(pos.X / 10.f);
		tmpPos.Y = (irr::s32)floor(pos.Y / 10.f);
		return tmpPos;
	}
};

