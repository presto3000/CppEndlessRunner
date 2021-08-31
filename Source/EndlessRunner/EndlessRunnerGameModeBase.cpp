// Copyright Epic Games, Inc. All Rights Reserved.


#include "EndlessRunnerGameModeBase.h"

#include "FloorTile.h"

void AEndlessRunnerGameModeBase::BeginPlay()
{
	CreateInitialFloorTiles();
}

void AEndlessRunnerGameModeBase::CreateInitialFloorTiles()
{
	AFloorTile* Tile = AddFloorTile();
	if(Tile)
	{
		LaneSwitchValues.Add(Tile->LeftLane->GetComponentLocation().Y);
		LaneSwitchValues.Add(Tile->CenterLane->GetComponentLocation().Y);
		LaneSwitchValues.Add(Tile->RightLane->GetComponentLocation().Y);
	}

	for(float Val : LaneSwitchValues)
	{
		UE_LOG(LogTemp, Warning, TEXT("LANE VALUE: %f:"), Val);
		
	}


	
	for(int i=0; i<NumInitialFloorTiles; i++)
	{
		AddFloorTile();
	}
}

AFloorTile* AEndlessRunnerGameModeBase::AddFloorTile()
{
	UWorld* World = GetWorld();

	if(World)
	{
	AFloorTile* Tile = World->SpawnActor<AFloorTile>(FloorTileClass, NextSpawnPoint);

		if(Tile)
		{
			NextSpawnPoint = Tile->GetAttachTransform();
		}
		return Tile;
	}
	return nullptr;
	
}




