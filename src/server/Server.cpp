
#include "Server.h"
#include "GameObjectRegistry.h"
#include "StringUtils.h"
#include "Colors.h"
#include "PlayerServer.h"
#include "BulletServer.h"
#include "RockServer.h"

#include <random>

//uncomment this when you begin working on the server

bool Server::StaticInit()
{
	sInstance.reset( new Server() );

	return true;
}

Server::Server()
{

	GameObjectRegistry::sInstance->RegisterCreationFunction( 'PLYR', PlayerServer::StaticCreate );
	GameObjectRegistry::sInstance->RegisterCreationFunction('BULL', BulletServer::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('ROCK', RockServer::StaticCreate);
//	GameObjectRegistry::sInstance->RegisterCreationFunction( 'MOUS', MouseServer::StaticCreate );
//	GameObjectRegistry::sInstance->RegisterCreationFunction( 'YARN', YarnServer::StaticCreate );

	InitNetworkManager();

	// Setup latency
	float latency = 0.0f;
	string latencyString = StringUtils::GetCommandLineArg( 2 );
	if( !latencyString.empty() )
	{
		latency = stof( latencyString );
	}
	NetworkManagerServer::sInstance->SetSimulatedLatency( latency );
}


int Server::Run()
{
	SetupWorld();

	return Engine::Run();
}

bool Server::InitNetworkManager()
{
	string portString = StringUtils::GetCommandLineArg( 1 );
	uint16_t port = stoi( portString );

	return NetworkManagerServer::StaticInit( port );
}

/***
* /brief spawns 5 rocks
* 
* uses a for loop to spawn 5 rocks
* number of rocks can be adjusted 
* 
* 
* 
*/
void Server::SetupWorld()
{
	// Static game objects and NPCs here.
	for (int i = 0; i < 5; i++)
	{
		SpawnRock(0);
	}
	
}

void Server::DoFrame()
{
	NetworkManagerServer::sInstance->ProcessIncomingPackets();

	NetworkManagerServer::sInstance->CheckForDisconnects();

	NetworkManagerServer::sInstance->RespawnPlayers();

	Engine::DoFrame();

	NetworkManagerServer::sInstance->SendOutgoingPackets();
}

void Server::HandleNewClient( ClientProxyPtr inClientProxy )
{

	int playerId = inClientProxy->GetPlayerId();

	//ScoreBoardManager::sInstance->AddEntry( playerId, inClientProxy->GetName() );
	SpawnPlayer( playerId );
}

void Server::SpawnPlayer( int inPlayerId )
{
	PlayerPtr player = std::static_pointer_cast< Player >( GameObjectRegistry::sInstance->CreateGameObject( 'PLYR' ) );
	//player->SetColor( Colors::Red );//ScoreBoardManager::sInstance->GetEntry( inPlayerId )->GetColor() );
	player->SetPlayerId( inPlayerId );
	//gotta pick a better spawn location than this...
	player->SetLocation( Vector3( 1.f - static_cast< float >( inPlayerId ), 0.0f, 0.0f ) );

}
/**
* /brief rock randomly spawns in different locations and rotations
* 
* 
* the rock spawn uses random X,Y,Z locations to randomly spawn the rock
* the rock has a random X to randomly spawn the rock at different rotations
* 
* 
*/
void Server::SpawnRock(int inRockId)
{
	RockPtr rock = std::static_pointer_cast<Rock>(GameObjectRegistry::sInstance->CreateGameObject('ROCK'));
	//rock->SetColor(Colors::Red);//ScoreBoardManager::sInstance->GetEntry( inPlayerId )->GetColor() );
	// 
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(-5.5f, 5.5f);

	float randomX = dis(gen);
	float randomZ = dis(gen);
	float randomY = dis(gen);

	rock->SetRockId(inRockId);

	rock->SetLocation(Vector3(randomX, randomY, randomZ));
	rock->SetRotation(randomX);
}

void Server::HandleLostClient( ClientProxyPtr inClientProxy )
{
	//kill client's player
	//remove client from scoreboard
	int playerId = inClientProxy->GetPlayerId();

	//ScoreBoardManager::sInstance->RemoveEntry( playerId );
	PlayerPtr player = GetPlayer( playerId );
	if( player )
	{
		player->SetDoesWantToDie( true );
	}
}

PlayerPtr Server::GetPlayer( int inPlayerId )
{
	//run through the objects till we find the Player...
	//it would be nice if we kept a pointer to the Player on the clientproxy
	//but then we'd have to clean it up when the Player died, etc.
	//this will work for now until it's a perf issue
	const auto& gameObjects = World::sInstance->GetGameObjects();
	for( int i = 0, c = gameObjects.size(); i < c; ++i )
	{
		GameObjectPtr go = gameObjects[ i ];

		/* Original code did this in a weird way, used a method in the base (GameObject) which
		returned a player object if a game object is the player and null otherwise */

		uint32_t type = go->GetClassId();

		//Player* player = dynamic_cast<Player*>(*go);
		PlayerPtr player = nullptr;
		if(type == 'PLYR')
		{
			player = std::static_pointer_cast< Player >(go);
		}

		if(player && player->GetPlayerId() == inPlayerId )
		{
			return player;
		}
	}

	return nullptr;

}
