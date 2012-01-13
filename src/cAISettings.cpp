#include "cAISettings.h"

cAISettings::cAISettings( cSoldierData* soldierData )
{
	_pSoldierData = soldierData;
	Init();
}

void cAISettings::Init()
{
	_bToClose = false;
}

void cAISettings::Update( cSoldierData* player02 )
{
	int tmpDistance = distanceBetweenPoints( _pSoldierData->GetPosition(), player02->GetPosition() );
	if( tmpDistance < _nToCloseAlertDistance )
	{
		if( !_bToClose )
			cMessageBoxInGame::GetInstance()->AddMessage( _cToCloseString );
		_bToClose = true;
	}
	else
	{
		if( _bToClose )
			cMessageBoxInGame::GetInstance()->AddMessage( _cNotToCloseString );
		_bToClose = false;
	}
}

void cAISettings::SetToCloseAlertDistance( int distance )
{
	 _nToCloseAlertDistance = distance;

	char integerString[32];
	std::sprintf(integerString, "%d", _nToCloseAlertDistance);
	char tmpString01[64] = "The enemy is within your specified alertrange. (";
	std::strcat(tmpString01, integerString);
	std::strcat(tmpString01, ")");
	std::strcpy(_cToCloseString, tmpString01);

	char tmpString02[64] = "The enemy is no longer within your specified alertrange. (";
	std::strcat(tmpString02, integerString);
	std::strcat(tmpString02, ")");
	std::strcpy(_cNotToCloseString, tmpString02);
}

irr::s32 cAISettings::distanceBetweenPoints( vector2d<s32> p1, vector2d<s32> p2 )
{
	float width = (float)abs( p2.X - p1.X );
	float height = (float)abs( p2.Y - p1.Y );
	float hyp = sqrtf( width*width + height*height );
	return floor32( hyp );
}