#pragma once

#include <irrlicht.h>

using namespace irr;

class cMouseState
{
public:
	cMouseState() : 
		LeftButtonDown(false), 
		RightButtonDown(false), 
		MouseWheelUp(false), 
		MouseWheelDown(false),
		MouseWheelDelta(0)
	{ };
	bool IsButtonPressed() const
	{ 
		return RightButtonDown || LeftButtonDown || MouseWheelUp || MouseWheelDown; 
	};  
    core::position2di Position;
    bool LeftButtonDown;
	bool MouseWheelUp;
	bool MouseWheelDown;
	bool RightButtonDown;
	irr::f32 MouseWheelDelta;
};