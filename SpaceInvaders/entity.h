#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include <stdint.h>
#include <string>

const int MAX_ENTITIES = 3;

typedef struct EntityBase
{
	int index;
	int id;
} EntityBase;

typedef enum EntityType
{
	UNDEFINED,
	PLAYER,
} EntityType;

typedef struct Entity
{
	bool allocated;
	EntityBase eBase;
	EntityType eType;
	
} Entity;

typedef struct GameState
{
	bool initialized;
	Entity allEntities[MAX_ENTITIES];
	uint64_t generatedEntityID;
	uint64_t entityTop;
	//std::string worldName;
	//EntityBase playerHandle;
} GameState;

static GameState* gameState;

void InitZeroEntity();
void InitGameState(Entity* defaultEntity);

Entity* CreateEntity(EntityType type);
void DestroyEntity(Entity* entity);
EntityBase LinkedEntity(Entity* entity);
Entity* LinkedBaseEntity(EntityBase eBase);

void Setup();
void SetupPlayer(Entity* entity);

void Update();
//EntityBase* getEntityArray();

#endif