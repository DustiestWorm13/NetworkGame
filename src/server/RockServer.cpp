#include "PlayerServer.h"
#include "BulletServer.h"
#include "RockServer.h"
#include "Bullet.h"
#include "Rock.h"
#include "ClientProxy.h"
#include "Timing.h"
#include "MoveList.h"
#include "Maths.h"
#include "GameObjectRegistry.h"

RockServer::RockServer() :
	//mRockControlType( ESCT_Human ),
	mTimeOfNextShot( 0.f ),
	mTimeBetweenShots( 0.2f )
{}

void RockServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject( this );
	RockServer::RockSplit();
}

void RockServer::Update()
{
	Rock::Update();


	Vector3 oldLocation = GetLocation();
	Vector3 oldVelocity = GetVelocity();
	float oldRotation = GetRotation();
	float deltaTime = Timing::sInstance.GetDeltaTime();
	SimulateMovement(deltaTime);

	

	if( !Maths::Is2DVectorEqual( oldLocation, GetLocation() ) ||
		!Maths::Is2DVectorEqual( oldVelocity, GetVelocity() ) ||
		oldRotation != GetRotation() )
	{
		NetworkManagerServer::sInstance->SetStateDirty( GetNetworkId(), ECRS_Pose );
	}
}

/***
* /brief rock splits each time it is shot
* 
* the rock uses the SetHealth to set the number of times it splits before dying
* the code also gets a new rotation for each new rockA
* 
*/
void RockServer::RockSplit()
{
	if (this->GetHealth() - 1 != 0)
	{
		for (int i = 0; i < 2; i++)
		{
			RockPtr rock = std::static_pointer_cast<Rock>(GameObjectRegistry::sInstance->CreateGameObject('ROCK'));

			rock->SetHealth(this->GetHealth() - 1);

			rock->SetScale(2.0f);

			rock->SetLocation(this->GetLocation());

			if (i == 0)
			{
				rock->SetRotation(this->GetRotation() + 45.0f);
			}
			else
			{
				rock->SetRotation(this->GetRotation() - 45.0f);
			}

		}
	}
}


	
