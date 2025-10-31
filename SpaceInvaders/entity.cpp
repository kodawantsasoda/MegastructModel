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

//to do.....
Entity* LinkedBaseEntity(EntityBase eBase)
{
	if (eBase == EntityBase{})
}