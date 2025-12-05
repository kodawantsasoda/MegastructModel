#include "entity.h"
#include "raylib.h"

GameState gameState;
static Entity zeroEntity;

Entity* CreateEntity(EntityType type) 
{
	int indexUpdate = -1;
	Entity* entityUpdate = NULL;

	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		if (!gameState.allEntities[i].allocated)
		{
			indexUpdate = i;
			entityUpdate = &gameState.allEntities[i];
			break;
		}
	}
	if (indexUpdate == -1)
	{
		printf("ENTITIES ARE FULL! ADJUST SIZE!\n");
		return NULL;
	}

	gameState.entityTop += 1;

	entityUpdate->allocated = true;

	gameState.generatedEntityID += 1;
	entityUpdate->eBase.id = gameState.generatedEntityID;
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
		return &zeroEntity;
	}

	Entity* entity = &gameState.allEntities[eBase.index];
	if (entity->eBase.id == eBase.id)
	{
		return entity;
	}
	else
	{
		return &zeroEntity;
	}
}

void InitZeroEntity()
{
	if (&zeroEntity)
	{
		printf("ERROR MALLOC ON ZERO ENTITY\n");
	}
	else
	{
		zeroEntity.allocated = false;
		zeroEntity.eBase.id = -1;
		zeroEntity.eBase.index = -1;
		zeroEntity.eType = UNDEFINED;
	}
}

void InitGameState(Entity& defaultEntity)
{
	if (&gameState)
	{
		printf("ERROR MALLOC ON GAME STATE STRUCT\n");
	}
	else
	{
		for (int i = 0; i < MAX_ENTITIES; i++)
		{
			gameState.allEntities[i] = defaultEntity;
		}
	}
}

void InitSprites()
{
	//later we can say stuff like if gameWorld = playscreen then load these, if title load these, unload these etc...
	Image img = LoadImage("Assets/player.png");
	gameState.allSprites[PLAYER_SPRITE] = LoadTextureFromImage(img);
	UnloadImage(img);

	img = LoadImage("Assets/alien1A.png");
	gameState.allSprites[ENEMY_SPRITE] = LoadTextureFromImage(img);
	UnloadImage(img);

	img = LoadImage("Assets/alien2A.png");
	gameState.allSprites[ENEMY_SPRITE2] = LoadTextureFromImage(img);
	UnloadImage(img);
}

void Setup()
{
	InitZeroEntity();
	InitGameState(zeroEntity);
	InitSprites();
	//gameState.worldName = "Main";
	//gameState.initialized = true;

	Entity* player;
	player = CreateEntity(PLAYER);

	Entity* enemy;
	enemy = CreateEntity(ENEMY);

	Entity* enemy2;
	enemy2 = CreateEntity(ENEMY);
	enemy2->pos = { 50, 50 };
}

void SetupPlayer(Entity* entity)
{
	entity->eType = PLAYER;
	entity->pos = { 0, 0 };
	entity->spriteIndex = PLAYER_SPRITE;
	entity->moveSpeed = 100.0f;
	entity->state = IDLE;	
	entity->collider = { entity->pos.x, entity->pos.y, 26, 16 };
	entity->colliderColor = { 206, 28, 68, 50 };
}

void SetupEnemy(Entity* entity)
{
	entity->eType = ENEMY;
	entity->pos = { 30, 30 };
	entity->spriteIndex = ENEMY_SPRITE;
	entity->collider = { entity->pos.x, entity->pos.y, 26, 16 };
	entity->colliderColor = { 206, 28, 68, 50 };
}

void MoveCollider(Entity* entity)
{
	entity->collider.x = entity->pos.x;
	entity->collider.y = entity->pos.y;
}

bool DetectCollision(Entity* entity)
{
	int upperBoundX = entity->collider.x + entity->collider.width;
	int upperBoundY = entity->collider.y + entity->collider.height;

	bool collided = false;

	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		if (entity->eBase.id != gameState.allEntities[i].eBase.id)
		{
			//entity* in question is to the LEFT of the entity that it's being compared to
			if (entity->collider.x - gameState.allEntities[i].collider.x < 0)
			{
				if (upperBoundX >= gameState.allEntities[i].collider.x)
				{
					collided = true;
				}
			}
			//entity* in question is to the RIGHT of the entity that it's being compared to
			else
			{
				if (entity->collider.x <= gameState.allEntities[i].collider.x + gameState.allEntities[i].collider.width)
				{
					collided = true;
				}
			}
			if (collided)
			{
				//entity* in question is to the ABOVE of the entity that it's being compared to
				if (entity->collider.y - gameState.allEntities[i].collider.y < 0)
				{
					if (upperBoundY >= gameState.allEntities[i].collider.y)
					{
						//collided = true;
						return true;
					}
				}
				//entity* in question is to the BELOW of the entity that it's being compared to
				else
				{
					if (entity->collider.y <= gameState.allEntities[i].collider.y + gameState.allEntities[i].collider.height)
					{
						//collided = true;
						return true;
					}
				}
			}
		}
	}
	return false;
}


void UpdatePlayer(Entity* player)
{
	Vector2 newPos = { 0,0 };

	if (IsKeyDown(KEY_RIGHT))
	{
		newPos = { player->pos.x + 1, player->pos.y };
		player->state = MOVING;
		player->pos = Vector2Lerp(player->pos, newPos, 2.0f);
	}
	if (IsKeyDown(KEY_LEFT))
	{
		newPos = { player->pos.x - 1, player->pos.y };
		player->state = MOVING;
		player->pos = Vector2Lerp(player->pos, newPos, 2.0f);
	}
	if (IsKeyDown(KEY_UP))
	{
		newPos = { player->pos.x, player->pos.y - 1 };
		player->state = MOVING;
		player->pos = Vector2Lerp(player->pos, newPos, 2.0f);
	}
	if (IsKeyDown(KEY_DOWN))
	{
		newPos = { player->pos.x, player->pos.y + 1 };
		player->state = MOVING;
		player->pos = Vector2Lerp(player->pos, newPos, 2.0f);
	}

	if (player->state == MOVING)
	{
		MoveCollider(player);
	}

	player->state = IDLE;
}

void UpdateEnemy(Entity* entity)
{
	MoveCollider(entity);
}

void Update()
{
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		switch (gameState.allEntities[i].eType)
		{
		case PLAYER:
			UpdatePlayer(&gameState.allEntities[i]);
			break;
		case ENEMY:
			UpdateEnemy(&gameState.allEntities[i]);
			break;
		}
	}
}

void Draw()
{
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		DrawTextureEx(gameState.allSprites[gameState.allEntities[i].spriteIndex], gameState.allEntities[i].pos, 0.0f, 1.0f, WHITE);
		DrawRectangleRec(gameState.allEntities[i].collider, gameState.allEntities[i].colliderColor);
		
		if (DetectCollision(&gameState.allEntities[i]))
		{
			printf("collision detected");
		}
	}
	//DrawFPS(100 + 16, 100);
	DrawText("SCORE - 1", 0, 0, 10, RED);
	DrawText("00000", 12, 12, 10, RED);
	DrawText("MIDWAY", 120, 0, 10, RED);
	DrawText("SCORE - 2", 250, 0, 10, RED);
	DrawText("00000", 260, 12, 10, RED);
}