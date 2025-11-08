#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include <stdint.h>
#include <string>
#include <raylib.h>

const int MAX_ENTITIES = 3;
const int MAX_SPRITES = 3;

typedef struct EntityBase
{
	int index;
	int id;
} EntityBase;

typedef enum EntityType
{
	UNDEFINED,
	PLAYER,
	ENEMY,
} EntityType;

typedef enum SpriteIndex
{
	PLAYER_SPRITE,
	ENEMY_SPRITE,
	ENEMY_SPRITE2,
} SpriteIndex;

typedef struct Entity
{
	bool allocated;
	EntityType eType;
	EntityBase eBase;
	
	SpriteIndex spriteIndex;

	Vector2 pos;
	//Texture2D* texture;
	
} Entity;

typedef struct GameState
{
	bool initialized;
	bool loadingWorld;
	Entity allEntities[MAX_ENTITIES];
	Texture2D allSprites[MAX_SPRITES];
	uint64_t generatedEntityID;
	uint64_t entityTop;
	//std::string worldName;
	//EntityBase playerHandle;
} GameState;

void InitZeroEntity();
void InitGameState(Entity& defaultEntity);

//here the goal for the init sprites.... we're gonna have all of our textures ready to go. we only load when need be... we're gonna use indexs instead of pointers via enum
void InitSprites();

Entity* CreateEntity(EntityType type);
void DestroyEntity(Entity* entity);
EntityBase LinkedEntity(Entity* entity);
Entity* LinkedBaseEntity(EntityBase eBase);

void Setup();
void SetupPlayer(Entity* entity);
void SetupEnemy(Entity* entity);

void Update();
void Draw();
//EntityBase* getEntityArray();

#endif