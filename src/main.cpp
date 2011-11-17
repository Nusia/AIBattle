#pragma once

#ifdef _MSC_VER
// We'll define this to stop MSVC complaining about sprintf().
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif

#include <irrlicht.h>
#include "driverChoice.h"
#include "cEventReceiver.h"
#include "cAIBattle.h"

using namespace irr;

int main( int argc, char* args[] )
{
	std::cout << "AIBattle started.\n";
	
	video::E_DRIVER_TYPE driverType = driverChoiceConsole();
	if( driverType == video::EDT_COUNT )
		return 1;

	cAIBattle AIBattle( driverType );
	std::cout << "AIBattle shutting down.\n";
    return 0;
}