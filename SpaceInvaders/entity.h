#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include <stdint.h>
#include <string>

const int MAX_ENTITIES = 50;

typedef struct EntityBase
{
	int index;
	int id;
}EntityBase;

typedef enum EntityType
{
	undefined,
	player,
}EntityType;

typedef struct Entity
{
	bool allocated;
	EntityBase eBase;
	EntityType eType;
}Entity;

typedef struct GameState
{
	bool initialized;
	Entity allEntities[MAX_ENTITIES];
	uint64_t generatedEntityID;
	uint64_t entityTop;
	std::string worldName;
	EntityBase playerHandle;
}GameState;

static GameState* gameState;

Entity* CreateEntity(EntityType type);
void DestroyEntity(Entity* entity);
EntityBase AttachedEntity(Entity* base);

//EntityBase* getEntityArray();

#endif