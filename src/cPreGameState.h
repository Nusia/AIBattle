#pragma once

#include <irrlicht.h>
#include <vector>
#include <iterator>
#include "iGameState.h"
#include "cGameManager.h"
#include "cAStar.h"
#include "event.h"
#include "cMap.h"

//#include "cEventReceiver.h"

//#define COLORKEY 255, 0, 255 //Your Transparent colour

//template <class Object> class Button;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class cPreGameState;

struct sAppContext
{
	IrrlichtDevice*	device;
	s32				counter;
	iGameState*		gameState;
};

enum
{
	GUI_ID_QUIT_BUTTON = 101,
	GUI_ID_START_GAME_BUTTON, 
};

class cPreGameEventReceiver : public IEventReceiver
{
public:
	cPreGameEventReceiver( sAppContext & context ) : Context(context) 
	{
		MouseState = new cMouseState();
	}
	cMouseState* getMouseState() { return MouseState; }

	virtual bool OnEvent(const SEvent& event)
    {
		MouseState->Position.X = event.MouseInput.X;
		MouseState->Position.Y = event.MouseInput.Y;

		//MOUSE EVENTS
		if( event.EventType == EET_MOUSE_INPUT_EVENT )
		{
			switch(event.MouseInput.Event)
			{
				case EMIE_LMOUSE_PRESSED_DOWN:
					MouseState->LeftButtonDown = true;
					break;

				case EMIE_LMOUSE_LEFT_UP:
					MouseState->LeftButtonDown = false;
					break;

				case EMIE_RMOUSE_PRESSED_DOWN:
					MouseState->RightButtonDown = true;
					break;

				case EMIE_RMOUSE_LEFT_UP:
					MouseState->RightButtonDown = false;
					break;

				default:
						break;
			}	
		}

		//GUI EVENTS
		if( event.EventType == EET_GUI_EVENT )
		{
			s32 id = event.GUIEvent.Caller->getID();
			IGUIEnvironment* env = Context.device->getGUIEnvironment();

			switch(event.GUIEvent.EventType)
			{
				case EGET_BUTTON_CLICKED:
					switch(id)
					{
					case GUI_ID_QUIT_BUTTON:
						Context.device->closeDevice();
						return true;

					case GUI_ID_START_GAME_BUTTON:
						Context.gameState->ChangeState();
						return true;

					default:
						return false;
					}
					break;

				default:
					break;
			}
		}

		return false;
    }

private:
	sAppContext & Context;
	cMouseState* MouseState;
};

class cPreGameState : public iGameState
{
public:
	cPreGameState( cGameManager* gameManager ) : _pGameManager(gameManager) {};
	void ChangeState();
	void Init( IrrlichtDevice* device );
	void Update( IrrlichtDevice* device );
	void Draw( IrrlichtDevice* device );
	bool IsDone();
	int GetNextState();

private:
	//Funcs
	//-----
	rect<s32> GetMapRectangle() const;
	void draw2DLine( video::IVideoDriver* driver, vector2d<s32> startPos, vector2d<s32> endPos, SColor color, int thickness );

	//Vars
	//----
	cGameManager* _pGameManager;

	sAppContext context;
	cPreGameEventReceiver* _pEventReceiver;

	IGUIFont* _pFont06;
	IGUIFont* _pFont08;
	IGUIFont* _pFont10;
	IGUISkin* _pSkin;
	IGUIFont* _pBasicFont;
	video::ITexture* _pPlayer;
	video::ITexture* _pGround;
	video::ITexture* _pWall;

	irr::core::vector2d<irr::s32> _posLastCheckpoint;

	position2d<s32> topLeftCornerOfMap;
	int tileSizeOfMap;

	bool _bIsDone;
};
