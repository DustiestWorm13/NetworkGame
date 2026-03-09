#include "BulletServer.h"
#include "PlayerServer.h"
#include "ClientProxy.h"
#include "Timing.h"
#include "MoveList.h"
#include "Maths.h"

BulletServer::BulletServer() :
	//mBulletControlType( ESCT_Human ),
	mTimeOfNextShot( 0.f ),
	mTimeBetweenShots( 0.2f )
{}

void BulletServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject( this );
}

void BulletServer::Update()
{
	Bullet::Update();


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


