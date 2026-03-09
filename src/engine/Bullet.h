#ifndef BULLET_H_
#define BULLET_H_

#include "GameObject.h"
#include "World.h"
#include "Player.h"

class InputState;

/* We'll later create client and server versions of this class */

class Bullet : public GameObject
{
public:
	CLASS_IDENTIFICATION( 'BULL', GameObject )

	enum EBulletReplicationState
	{
		ECRS_Pose = 1 << 0,
		ECRS_Color = 1 << 1,
		ECRS_BulletId = 1 << 2,
		//ECRS_Health = 1 << 3,

		ECRS_AllState = ECRS_Pose | ECRS_Color | ECRS_BulletId 
	};


	static	GameObject*	StaticCreate()			{ return new Bullet(); }

	//Note - the code in the book doesn't provide this until the client.
	//This however limits testing.
	static	GameObjectPtr	StaticCreatePtr()			{ return GameObjectPtr(new Bullet()); }


	virtual uint32_t GetAllStateMask()	const override	{ return ECRS_AllState; }

	virtual void Update() override;

	virtual bool	HandleCollisionWithPlayer(Player* inPlayer) { (void)inPlayer; return false; }
	virtual bool	HandleCollisionWithRock(Rock* inRock) { (void)inRock; return true; }
	virtual bool	HandleCollisionWithBullet(Bullet* inBullet) { (void)inBullet; return true; }

	void ProcessInput( float inDeltaTime, const InputState& inInputState );
	void SimulateMovement( float inDeltaTime );

	void InitFromShooter(Player* player);

	void ProcessCollisions();
	void ProcessCollisionsWithScreenWalls();
	

	void		SetBulletId( uint32_t inBulletId )			{ mBulletId = inBulletId; }
	uint32_t	GetBulletId()						const 	{ return mBulletId; }

	void			SetVelocity( const Vector3& inVelocity )	{ mVelocity = inVelocity; }
	const Vector3&	GetVelocity()						const	{ return mVelocity; }


//	virtual void	Read( InputMemoryBitStream& inInputStream ) override;

	uint32_t Write( OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState ) const override;
	// For testing

	float GetMaxLinearSpeed() { return mMaxLinearSpeed; }
	float GetMaxRotationSpeed() { return mMaxRotationSpeed; }
	float GetWallRestitution() { return mWallRestitution; }
	float GetNPCRestitution() { return mNPCRestitution; }
	float GetLastMoveTimestamp() { return mLastMoveTimestamp; }
	float GetThrustDir() { return mThrustDir; }
	//int GetHealth() { return mHealth; }
	//bool IsShooting() { return mIsShooting; }

	bool operator==(Bullet &other);
protected:
	Bullet();

private:


	void	AdjustVelocityByThrust( float inDeltaTime );

	Vector3				mVelocity;


	float				mMaxLinearSpeed;
	float				mMaxRotationSpeed;

	//bounce fraction when hitting various things
	float				mWallRestitution;
	float				mNPCRestitution;


	uint32_t			mBulletId;

protected:

	///move down here for padding reasons...

	float				mLastMoveTimestamp;

	float				mThrustDir;
	//int					mHealth;

	//bool				mIsShooting;


};

typedef shared_ptr< Bullet >	BulletPtr;

#endif // PLAYER_H_
