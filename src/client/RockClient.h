#ifndef ROCK_CLIENT_H
#define ROCK_CLIENT_H

#include "Rock.h"
#include "SpriteComponent.h"

class RockClient : public Rock
{
public:
	static	GameObjectPtr	StaticCreate()		{ return GameObjectPtr( new RockClient() ); }

	virtual void Update();
	virtual void	HandleDying() override;

	virtual void	Read( InputMemoryBitStream& inInputStream ) override;

protected:
	RockClient();


private:
	float				mTimeLocationBecameOutOfSync;
	float				mTimeVelocityBecameOutOfSync;

	SpriteComponentPtr	mSpriteComponent;
};
typedef shared_ptr< RockClient >	RockClientPtr;
#endif //PLAYER_CLIENT_H
