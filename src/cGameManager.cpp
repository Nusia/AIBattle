#include "cGameManager.h"

void cGameManager::Init() 
{
	_pMap = new cMap();
	
	_pPlayer01 = new cSoldier();
	_pPlayer02 = new cSoldier();

	_pPlayer01->SetPosition( _pMap->GetPlayer01Pos() );
	_pPlayer02->SetPosition( _pMap->GetPlayer02Pos() );
}

void cGameManager::InGameUpdate( irr::IrrlichtDevice* device )
{
	_pPlayer01->Update( device, _pPlayer02->GetSoldierData() );
	//_pPlayer02->Update( device );
}

cSoldier* cGameManager::GetPlayer( int playerNr ) const 
{
	if( playerNr == 1 )
		return _pPlayer01;
	else if( playerNr == 2 )
		return _pPlayer02;
	else
		exit( EXIT_FAILURE );
}