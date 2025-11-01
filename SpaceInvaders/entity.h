#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include <stdint.h>
#include <string>

const int MAX_ENTITIES = 50;

typedef struct EntityBase
{
	int index = -1;
	int id = -1;
} EntityBase;

typedef enum EntityType
{
	undefined,
	player,
} EntityType;

typedef struct Entity
{
	bool allocated = false;
	EntityBase eBase;
	EntityType eType;
} Entity;

typedef struct GameState
{
	bool initialized = false;
	Entity allEntities[MAX_ENTITIES];
	uint64_t generatedEntityID = 0;
	uint64_t entityTop = 0;
	std::string worldName = "";
	EntityBase playerHandle;
} GameState;

static GameState* gameState;

Entity* CreateEntity(EntityType type);
void DestroyEntity(Entity* entity);
EntityBase LinkedEntity(Entity* entity);
Entity* LinkedBaseEntity(EntityBase eBase);

void Setup();
//EntityBase* getEntityArray();

#endif