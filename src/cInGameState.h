#include "iGameState.h"
#include "cAStar.h"
#include "cMouse.h"
#include "Math.h"

class cInGameState : public iGameState
{
public:
	cInGameState( cMouse* pMouse);
	void Init();
	void HandleInput( SDL_Event* event );
	void Update();
	void Draw( SDL_Surface* screen );
	bool IsDone();
	int GetNextState();

private:
	//Variables
	//---------
	cMap map;
	std::vector< cPosition > tmp_list_;

	cPosition cam_pos_;
	
	SDL_Surface* _pCharacterPlayer01Sprite;
	SDL_Surface* _pCharacterPlayer02Sprite;
	SDL_Surface* _pGround;
	SDL_Surface* _pWall;

	bool _isMouseScrollCamera;
	cPosition _posMouseScrollOrigo;

	cMouse* _pMouse;
};