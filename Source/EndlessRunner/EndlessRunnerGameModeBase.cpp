// Copyright Epic Games, Inc. All Rights Reserved.


#include "EndlessRunnerGameModeBase.h"

void AEndlessRunnerGameModeBase::BeginPlay()
{
	CreateInitialFloorTiles();
}

void AEndlessRunnerGameModeBase::CreateInitialFloorTiles()
{
	for(int i=0; i<NumInitialFloorTiles; i++)
	{
		AddFloorTile();
	}
}

void AEndlessRunnerGameModeBase::AddFloorTile()
{
	UWorld* World = GetWorld();

	if(World)
	{
	AFloorTile* Tile = World->SpawnActor<AFloorTile>(FloorTileClass, NextSpawnPoint);

		if(Tile)
		{
			NextSpawnPoint = Tile->GetAttachTransform();
		}
	
	}
}




