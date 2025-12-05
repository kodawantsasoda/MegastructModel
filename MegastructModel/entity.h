#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>
#include <math.h>


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

typedef enum EntityState
{
	IDLE,
	MOVING, 
	HIT,
	DYING,
	DEAD,
};

typedef enum SpriteIndex
{
	PLAYER_SPRITE,
	ENEMY_SPRITE,
	ENEMY_SPRITE2,
} SpriteIndex;

//NEEDS: RECTANGLEWS FOR SCALING UP/DOWN DRAWING, COLLIDER RECTANGLES, ANIMATION SETTINGS, 
typedef struct Entity
{
	bool allocated;
	EntityType eType;
	EntityBase eBase;
	
	SpriteIndex spriteIndex;

	Vector2 pos;
	float moveSpeed;
	EntityState state;
	Rectangle collider;
	Rectangle scaleSprite;
	Color colliderColor;
	int colliderId; //make sure we deal with this being set in setup functions
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

extern GameState gameState;

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

void MoveCollider(Entity* entity);
bool DetectCollision(Entity* entity);
bool OptimizedCollion(Entity* entity);

void UpdatePlayer(Entity* player);
void UpdateEnemy(Entity* enemy);
void Update();
void Draw();
//EntityBase* getEntityArray();

#endif