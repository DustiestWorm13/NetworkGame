#ifndef BULLET_SERVER_H
#define BULLET_SERVER_H

#include "Bullet.h"
#include "NetworkManagerServer.h"

enum EBulletControlType
{
	//ESCT_Human,
	//ESCT_AI
};

class BulletServer : public Bullet
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn( new BulletServer() ); }
	virtual void HandleDying() override;

	virtual void Update() override;

	void SetBulletControlType( EBulletControlType inBulletControlType ) { mBulletControlType = inBulletControlType; }
	
	//void TakeDamage( int inDamagingPlayerId );

protected:
	BulletServer();

private:

	

	EBulletControlType	mBulletControlType;


	float		mTimeOfNextShot;
	float		mTimeBetweenShots;

};

#endif // PLAYER_SERVER_H
