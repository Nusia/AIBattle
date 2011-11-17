#include "cPreGameState.h"

void cPreGameState::Init( IrrlichtDevice* device )
{
	std::cout << "Initiating pregame state.\n";
	_bIsDone = false;
	_posLastCheckpoint = _pGameManager->GetPlayer(1)->GetPosition();
	topLeftCornerOfMap = position2d<s32>(20, 60);
	tileSizeOfMap = 16;
	//tileSizeOfMap = 1004/MAP_COLS;

	IVideoDriver* driver = device->getVideoDriver();
	gui::IGUIEnvironment* env = device->getGUIEnvironment();

	env = device->getGUIEnvironment();

	_pPlayer = driver->getTexture("../resources/character_basic_green.png");
	_pWall = driver->getTexture("../resources/wall.png");
	_pGround = driver->getTexture("../resources/ground.png");
	_pSkin = env->getSkin();
	//_pFont = env->getFont("fonthaettenschweiler.bmp");
	//_pFont = env->getBuiltInFont();
	_pFont10 = env->getFont("../resources/fonts/larabie10.png");
	_pFont08 = env->getFont("../resources/fonts/larabie08.png");
	_pFont06 = env->getFont("../resources/fonts/larabie06.png");
	//_pFont = env->getBuiltInFont();
	if( _pFont06 )
		_pSkin->setFont( _pFont08 );
	_pSkin->setFont( env->getBuiltInFont(), gui::EGDF_TOOLTIP );

	env->addButton(rect<s32>(1024-100, 10, 1024-10, 10+40), 0, GUI_ID_QUIT_BUTTON,
        L"Quit", L"Exits Program");
	env->addButton(rect<s32>(1024/2 - 50, 10, 1024/2 + 50, 10+40), 0, GUI_ID_START_GAME_BUTTON,
        L"Start game", L"Starts a match");

    // Store the appropriate data in a context structure.
	context.device = device;
    context.counter = 0;
	context.gameState = this;

	_pEventReceiver = new cPreGameEventReceiver(context);
	device->setEventReceiver( _pEventReceiver );

	std::cout << "Pregame state ready.\n";
}

void cPreGameState::Update( IrrlichtDevice* device )
{
	cMap map = *(_pGameManager->GetMap());
	cMouseState tmpMouse = *_pEventReceiver->getMouseState();
	if( _pEventReceiver->getMouseState()->LeftButtonDown )
	{
		if( GetMapRectangle().isPointInside( tmpMouse.Position ) )
		{
			std::vector<vector2d<s32>> playerPath = _pGameManager->GetPlayer(1)->GetPath();

			int xCell = (int)floorf(
				( (tmpMouse.Position.X - GetMapRectangle().UpperLeftCorner.X) / 
				( (float)(MAP_COLS * tileSizeOfMap) / MAP_COLS ) ) );
	
			int yCell = (int)floorf(
				( (tmpMouse.Position.Y - GetMapRectangle().UpperLeftCorner.Y) / 
				( (float)(MAP_ROWS * tileSizeOfMap) / MAP_ROWS ) ) );

			if( xCell >= 0 && xCell <= MAP_COLS-1 &&
				yCell >= 0 && yCell <= MAP_ROWS-1 &&
				map.IsPosWalkable( vector2d<s32>( xCell, yCell ) ) )
			{
				vector2d<s32> cellPos(xCell, yCell);
				if( playerPath.size() < 1 || 
					!(	playerPath.back().X == cellPos.X && 
						playerPath.back().Y == cellPos.Y  ) )
				{
					cAStar aStar( map.GetMap(), map.GetPlayersPos() );

					std::vector<vector2d<s32>> tmpList = aStar.GetBestPath( cellPos, _posLastCheckpoint );
					std::copy( tmpList.begin()+1, tmpList.end(), std::back_inserter( playerPath ) );
					playerPath.push_back( cellPos );

					_pGameManager->GetPlayer(1)->SetPath( playerPath );
					_posLastCheckpoint = cellPos;
				}
			}
		}
	}
	else if( _pEventReceiver->getMouseState()->RightButtonDown )
	{
		_pGameManager->GetPlayer(1)->ClearPath();
		_posLastCheckpoint = _pGameManager->GetPlayer(1)->GetPosition();
	}
	//Context.mapRect.isPointInside( 
	//vector2d<s32>(event.MouseInput.X, event.MouseInput.Y) ) )
	//		{
	
}

void cPreGameState::Draw( IrrlichtDevice* device )
{
	cMap map = *(_pGameManager->GetMap());
	IVideoDriver* driver = device->getVideoDriver();
	std::vector<std::vector<int>> map_data = map.GetMap();
	SColor currentColor;
	
	rect<s32> destRect;
	rect<s32> srcRect = rect<s32>(0, 0, TILE_WIDTH, TILE_HEIGHT);
	for( int col = 0; col < MAP_COLS; ++col )
	{
		for( int row = 0; row < MAP_ROWS; ++row )
		{
			destRect = rect<s32>(	
				topLeftCornerOfMap.X + col*tileSizeOfMap, 
				topLeftCornerOfMap.Y + row*tileSizeOfMap, 
				topLeftCornerOfMap.X + (col+1)*tileSizeOfMap, 
				topLeftCornerOfMap.Y + (row+1)*tileSizeOfMap );

			switch( map_data[col][row] )
			{
			case map.WALKABLE:
				driver->draw2DImage( _pGround, destRect, srcRect );
				break;
			case map.WALL:
				driver->draw2DImage( _pWall, destRect, srcRect );
				break;
			default:
				currentColor = SColor(255, 255, 255, 255);
				driver->draw2DRectangle( currentColor, destRect );
				break;
			}
		}
	}

	int tmpX, tmpY;
	vector2d<s32> currPos;
	vector2d<s32> prevPos = vector2d<s32>(
		topLeftCornerOfMap.X + _pGameManager->GetPlayer(1)->GetPosition().X*tileSizeOfMap + (float)tileSizeOfMap/2, 
		topLeftCornerOfMap.Y + _pGameManager->GetPlayer(1)->GetPosition().Y*tileSizeOfMap + (float)tileSizeOfMap/2
		);

	std::vector< vector2d<s32> > tmpPathList = _pGameManager->GetPlayer(1)->GetPath();

	for( std::vector<vector2d<s32>>::iterator it = tmpPathList.begin(); it != tmpPathList.end(); ++it )
	{
		tmpX = topLeftCornerOfMap.X + (*it).X*tileSizeOfMap + (float)tileSizeOfMap/2;
		tmpY = topLeftCornerOfMap.Y + (*it).Y*tileSizeOfMap + (float)tileSizeOfMap/2;
		currPos = vector2d<s32>(tmpX, tmpY);
		if( prevPos.X > -1 )
			draw2DLine( driver, prevPos, currPos, SColor( 255, 0, 0, 0 ), 5 );
		prevPos = currPos;
	}

	tmpX = topLeftCornerOfMap.X + _pGameManager->GetPlayer(1)->GetPosition().X * tileSizeOfMap;
	tmpY = topLeftCornerOfMap.Y + _pGameManager->GetPlayer(1)->GetPosition().Y * tileSizeOfMap;
	driver->draw2DImage( 
		_pPlayer, 
		rect<s32>( tmpX, tmpY, tmpX + tileSizeOfMap, tmpY + tileSizeOfMap ), 
		srcRect );	

	_pFont08->draw(	L"LeftMouse : Append path.",
                    core::rect<s32>(130,10,300,20),
					video::SColor(255,255,255,255) );
	_pFont08->draw(	L"RightMouse : Clear path.",
                    core::rect<s32>(130,25,300,45),
					video::SColor(255,255,255,255) );
}

bool cPreGameState::IsDone()
{
	return _bIsDone;
}

int cPreGameState::GetNextState()
{
	return INGAME;
}

void cPreGameState::ChangeState()
{
	_bIsDone = true;
}

rect<s32> cPreGameState::GetMapRectangle() const
{
	return rect<s32>(
		topLeftCornerOfMap.X, 
		topLeftCornerOfMap.Y, 
		topLeftCornerOfMap.X + MAP_COLS*tileSizeOfMap,
		topLeftCornerOfMap.Y + MAP_ROWS*tileSizeOfMap );
}

void cPreGameState::draw2DLine( IVideoDriver* driver, vector2d<s32> startPos, vector2d<s32> endPos, SColor color, int thickness )
{
	//Building dots in a "+"-pattern at startPos and endPos and draw lines between them.
	int counter = -floorf((float)thickness * 0.5);
	for( int i = 0; i < thickness; ++i )
	{
		driver->draw2DLine( vector2d<s32>(startPos.X, startPos.Y+counter ), vector2d<s32>( endPos.X, endPos.Y+counter ), color );
		driver->draw2DLine( vector2d<s32>(startPos.X+counter, startPos.Y ), vector2d<s32>( endPos.X+counter, endPos.Y ), color );
		counter++;
	}
}