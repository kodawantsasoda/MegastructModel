#include "entity.h"

static GameState* gameState;
static Entity* zeroEntity;

Entity* CreateEntity(EntityType type) 
{
	int indexUpdate = -1;
	Entity* entityUpdate = NULL;

	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		if (!gameState->allEntities[i].allocated)
		{
			indexUpdate = i;
			entityUpdate = &gameState->allEntities[i];
			break;
		}
	}
	if (indexUpdate == -1)
	{
		printf("ENTITIES ARE FULL! ADJUST SIZE!\n");
		return NULL;
	}

	gameState->entityTop += 1;

	entityUpdate->allocated = true;

	gameState->generatedEntityID += 1;
	entityUpdate->eBase.id = gameState->generatedEntityID;
	entityUpdate->eBase.index = indexUpdate;

	//add defaults for drawing

	//setup ents
	switch (type)
	{
		case PLAYER: 
			SetupPlayer(entityUpdate);
			break;
	}

	return entityUpdate;
}

//dereferencing magic.. still gotta implement a freelist or something
void DestroyEntity(Entity* entity)
{
	*entity = Entity{};
}

EntityBase LinkedEntity(Entity* entity)
{
	return entity->eBase;
}

//to do.....
Entity* LinkedBaseEntity(EntityBase eBase)
{
	if (eBase.id == -1 && eBase.index == -1)
	{
		return zeroEntity;
	}

	Entity* entity = &gameState->allEntities[eBase.index];
	if (entity->eBase.id == eBase.id)
	{
		return entity;
	}
	else
	{
		return zeroEntity;
	}
}

void InitZeroEntity()
{
	zeroEntity = (Entity*)malloc(sizeof(Entity));
	if (!zeroEntity)
	{
		printf("ERROR MALLOC ON ZERO ENTITY");
	}
	else
	{
		zeroEntity->allocated = false;
		zeroEntity->eBase.id = -1;
		zeroEntity->eBase.index = -1;
		zeroEntity->eType = UNDEFINED;
	}
}

void InitGameState(Entity* defaultEntity)
{
	gameState = (GameState*)malloc(sizeof(GameState));
	if (!gameState)
	{
		printf("ERROR MALLOC ON GAME STATE STRUCT");
	}
	else
	{
		for (int i = 0; i < MAX_ENTITIES; i++)
		{
			gameState->allEntities[i] = *defaultEntity;
		}
	}
}

void Setup()
{
	InitZeroEntity();
	InitGameState(zeroEntity);
	//gameState->worldName = "Main";
	//gameState->initialized = true;

	Entity* player;
	player = CreateEntity(PLAYER);

	Entity* player2;
	player2 = CreateEntity(PLAYER);

	Entity* player3;
	player3 = CreateEntity(PLAYER);

	Entity* player4;
	player4 = CreateEntity(PLAYER);


	//Entity mainPlayer = *CreateEntity(player);

	//Entity player = CreateEntity(player);
}

void SetupPlayer(Entity* entity)
{
	entity->eType = PLAYER;
}

void Update()
{
	for (int i = 0; i < MAX_ENTITIES; i++)
	{

	}
}