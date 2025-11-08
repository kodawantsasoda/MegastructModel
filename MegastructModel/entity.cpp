#include "entity.h"
#include "raylib.h"

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
		case ENEMY:
			SetupEnemy(entityUpdate);
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
		printf("ERROR MALLOC ON ZERO ENTITY\n");
	}
	else
	{
		zeroEntity->allocated = false;
		zeroEntity->eBase.id = -1;
		zeroEntity->eBase.index = -1;
		zeroEntity->eType = UNDEFINED;
	}
}

void InitGameState(Entity& defaultEntity)
{
	gameState = (GameState*)malloc(sizeof(GameState));
	if (!gameState)
	{
		printf("ERROR MALLOC ON GAME STATE STRUCT\n");
	}
	else
	{
		for (int i = 0; i < MAX_ENTITIES; i++)
		{
			gameState->allEntities[i] = defaultEntity;
		}
	}
}

void InitSprites()
{
	//later we can say stuff like if gameWorld = playscreen then load these, if title load these, unload these etc...
	gameState->allSprites[PLAYER_SPRITE] = LoadTexture("Assets/player.png");
	gameState->allSprites[ENEMY_SPRITE] = LoadTexture("Assets/alien1A.png");
	gameState->allSprites[ENEMY_SPRITE2] = LoadTexture("Assets/alien2A.png");
}

void Setup()
{
	InitZeroEntity();
	InitGameState(*zeroEntity);
	InitSprites();
	//gameState->worldName = "Main";
	//gameState->initialized = true;

	Entity* player;
	player = CreateEntity(PLAYER);

	Entity* enemy;
	enemy = CreateEntity(ENEMY);

	Entity* enemy2;
	enemy2 = CreateEntity(ENEMY);
	enemy2->pos = { 50, 50 };


	//Entity mainPlayer = *CreateEntity(player);

	//Entity player = CreateEntity(player);
}

void SetupPlayer(Entity* entity)
{
	entity->eType = PLAYER;
	entity->pos = { 0, 0 };
	entity->spriteIndex = PLAYER_SPRITE;
}

void SetupEnemy(Entity* entity)
{
	entity->eType = ENEMY;
	entity->pos = { 30, 30 };
	entity->spriteIndex = ENEMY_SPRITE;
}

void Update()
{
 	if (IsKeyDown(KEY_SPACE))
	{
		gameState->allEntities[0].pos.x += 2;
	}
}

void Draw()
{
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		DrawTextureEx(gameState->allSprites[gameState->allEntities[i].spriteIndex], gameState->allEntities[i].pos, 0.0f, 1.0f, WHITE);
	}
}