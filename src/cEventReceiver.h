#pragma once
#ifdef _MSC_VER
// We'll define this to stop MSVC complaining about sprintf().
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif

#include <irrlicht.h>
#include "driverChoice.h"
#include "cMouseState.h"

using namespace irr;

class cEventReceiver : public IEventReceiver
{
public:
        // We'll create a struct to record info on the mouse state
        cMouseState MouseState;

        // This is the one method that we have to implement
        virtual bool OnEvent(const SEvent& event)
        {
			// Remember the mouse state
            if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
			{
				switch(event.MouseInput.Event)
				{
					case EMIE_LMOUSE_PRESSED_DOWN:
						MouseState.LeftButtonDown = true;
						break;

					case EMIE_LMOUSE_LEFT_UP:
						MouseState.LeftButtonDown = false;
						break;

					case EMIE_RMOUSE_PRESSED_DOWN:
						MouseState.RightButtonDown = true;
						break;

					case EMIE_RMOUSE_LEFT_UP:
						MouseState.RightButtonDown = false;
						break;
					
					case EMIE_MOUSE_MOVED:
						MouseState.Position.X = event.MouseInput.X;
						MouseState.Position.Y = event.MouseInput.Y;
						break;

					default:
							break;
				}
			}

			if( event.MouseInput.Event == EMIE_MOUSE_WHEEL )
			{
				MouseState.MouseWheelDelta += event.MouseInput.Wheel;
				if( event.MouseInput.Wheel > 0 )
					MouseState.MouseWheelUp = true;
				else
					MouseState.MouseWheelDown = true;
			}
			else
			{
				MouseState.MouseWheelUp = false;
				MouseState.MouseWheelDown = false;
			}
				
			// Remember whether each key is down or up
            if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			{
                    KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
					_bAnyKeyDown = true;
			}
			else
				_bAnyKeyDown = false;
                
            // The state of each connected joystick is sent to us
            // once every run() of the Irrlicht device.  Store the
            // state of the first joystick, ignoring other joysticks.
            // This is currently only supported on Windows and Linux.
            if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT
                    && event.JoystickEvent.Joystick == 0)
            {
                    JoystickState = event.JoystickEvent;
            }

            return false;
        }

        const SEvent::SJoystickEvent & GetJoystickState(void) const
        {
                return JoystickState;
        }

        const cMouseState & GetMouseState() const
        {
                return MouseState;
        }

		bool IsKeyDown(EKEY_CODE keyCode) const
		{
				return KeyIsDown[keyCode];
		}

		bool IsAnyKeyDown() const
		{
			return _bAnyKeyDown;
		}

        cEventReceiver()
        {
			for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
                        KeyIsDown[i] = false;
        }

private:
        SEvent::SJoystickEvent JoystickState;

		// We use this array to store the current state of each key
        bool KeyIsDown[KEY_KEY_CODES_COUNT];
		bool _bAnyKeyDown;
};