#ifndef SERVER_H
#define SERVER_H

#include "Engine.h"
#include "ClientProxy.h"
#include "Player.h"
#include "Rock.h"
#include "NetworkManagerServer.h"

class Server : public Engine
{
public:

	static bool StaticInit();

	virtual void DoFrame() override;

	virtual int Run();

	void HandleNewClient( ClientProxyPtr inClientProxy );
	void HandleLostClient( ClientProxyPtr inClientProxy );

	PlayerPtr	GetPlayer( int inPlayerId );
	RockPtr GetRock(int inRockId);
	void	SpawnPlayer( int inPlayerId );
	void	SpawnRock(int inRockId);


private:
	Server();

	bool	InitNetworkManager();
	void	SetupWorld();

};

#endif // SERVER_H
