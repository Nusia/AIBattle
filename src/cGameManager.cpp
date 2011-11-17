#include "cGameManager.h"

void cGameManager::Init() 
{
	_pMap = new cMap();
	_pMap->Init();
	
	_pPlayer01 = new cSoldier();
	_pPlayer02 = new cSoldier();

	_pPlayer01->SetPosition( _pMap->GetPlayer01Pos() );
}

void cGameManager::InGameUpdate( irr::IrrlichtDevice* device )
{
	_pPlayer01->Update( device );
	//_pPlayer02->Update( device );
}

cSoldier* cGameManager::GetPlayer( int playerNr ) const 
{
	if( playerNr == 1 )
		return _pPlayer01;
	else if( playerNr == 2 )
		return _pPlayer02;
}