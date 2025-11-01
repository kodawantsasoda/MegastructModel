#include "entity.h"

EntityBase* getEntityArray()
{
}

Entity* CreateEntity(EntityType type) 
{
	int indexUpdate = -1;
	Entity* entityUpdate;

	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		if (!gameState->allEntities[i].allocated)
		{
			indexUpdate = i;
			entityUpdate = &gameState->allEntities[i];
			break;
		}
		if (indexUpdate == -1)
		{
			printf("ENTITIES ARE FULL! ADJUST SIZE!\n");
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
			case player: 
				break;
		}

		return entityUpdate;
	}
}

//dereferencing magic
void DestroyEntity(Entity* entity)
{
	*entity = Entity{};
}

EntityBase LinkedEntity(Entity* entity)
{
	return entity->eBase;
}

//read only
Entity zeroEntity = { 0 };

//to do.....
Entity* LinkedBaseEntity(EntityBase eBase)
{
	if (eBase.id == -1 && eBase.index == -1)
	{
		return &zeroEntity;
	}

	Entity* entity = &gameState->allEntities[eBase.index];
	if (entity->eBase.id == eBase.id)
	{
		return entity;
	}
	else
	{
		return &zeroEntity;
	}
}

void Setup()
{
	gameState->initialized = true;

	//Entity player = CreateEntity(player);
}