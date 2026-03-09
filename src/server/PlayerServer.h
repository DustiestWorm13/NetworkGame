#ifndef PLAYER_SERVER_H
#define PLAYER_SERVER_H

#include "Player.h"
#include "NetworkManagerServer.h"

enum EPlayerControlType
{
	ESCT_Human,
	ESCT_AI
};

class PlayerServer : public Player
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn( new PlayerServer() ); }
	virtual void HandleDying() override;

	virtual void Update() override;

	void SetPlayerControlType( EPlayerControlType inPlayerControlType ) { mPlayerControlType = inPlayerControlType; }

	void TakeDamage( int inDamagingPlayerId );

protected:
	PlayerServer();

private:

	void HandleShooting();

	EPlayerControlType	mPlayerControlType;


	float		mTimeOfNextShot;
	float		mTimeBetweenShots;

};

#endif // PLAYER_SERVER_H
