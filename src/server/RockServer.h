#ifndef ROCK_SERVER_H
#define ROCK_SERVER_H

#include "Rock.h"
#include "NetworkManagerServer.h"

/*enum ERockControlType
{
	ESCT_Human,
	ESCT_AI
};*/

class RockServer : public Rock
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn( new RockServer() ); }
	virtual void HandleDying() override;

	void RockSplit();

	virtual void Update() override;

	//void SetRockControlType( ERockControlType inRockControlType ) { mRockControlType = inRockControlType; }

	void TakeDamage( int inDamagingRockId );

protected:
	RockServer();

private:

	

	//ERockControlType	mRockControlType;


	float		mTimeOfNextShot;
	float		mTimeBetweenShots;

};

#endif // PLAYER_SERVER_H
