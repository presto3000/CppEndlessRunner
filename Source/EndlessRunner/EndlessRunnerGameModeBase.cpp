// Copyright Epic Games, Inc. All Rights Reserved.


#include "EndlessRunnerGameModeBase.h"

#include "FloorTile.h"
#include "GameHud.h"


#include "Blueprint/UserWidget.h"
#include "Chaos/ChaosPerfTest.h"
#include "Kismet/GameplayStatics.h"

void AEndlessRunnerGameModeBase::BeginPlay()
{

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	GameHud = Cast<UGameHud>(CreateWidget(GetWorld(), GameHudClass));
	check(GameHud);

	//Broadcasting:
	GameHud->InitializeHUD(this);
	GameHud->AddToViewport();

	//Setting number of lives to max lives
	NumberOfLives = MaxLives;
	
	CreateInitialFloorTiles();
}

void AEndlessRunnerGameModeBase::CreateInitialFloorTiles()
{
	AFloorTile* Tile = AddFloorTile(false);
	if(Tile)
	{
		LaneSwitchValues.Add(Tile->LeftLane->GetComponentLocation().Y);
		LaneSwitchValues.Add(Tile->CenterLane->GetComponentLocation().Y);
		LaneSwitchValues.Add(Tile->RightLane->GetComponentLocation().Y);
	}

	// for(float Val : LaneSwitchValues)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("LANE VALUE: %f:"), Val);
	// 	
	// }

	AddFloorTile(false);
	AddFloorTile(false);
	
	for(int i=0; i<NumInitialFloorTiles; i++)
	{
		AddFloorTile(true);
	}
}

AFloorTile* AEndlessRunnerGameModeBase::AddFloorTile(const bool bSpawnItems)
{
	UWorld* World = GetWorld();

	if(World)
	{
	AFloorTile* Tile = World->SpawnActor<AFloorTile>(FloorTileClass, NextSpawnPoint);

		if(Tile)
		{
			//Adding Tiles, later to destroy after character losing live
			FloorTiles.Add(Tile);
			if(bSpawnItems)
			{
				Tile->SpawnItems();
				
			}
			NextSpawnPoint = Tile->GetAttachTransform();
		}
		return Tile;
	}
	return nullptr;
	
}

void AEndlessRunnerGameModeBase::AddCoin()
{
	TotalCoins += 1;

	OnCoinsCountChanged.Broadcast(TotalCoins);
	
	UE_LOG(LogTemp, Warning, TEXT("TOTAL COINS: %d"), TotalCoins);
}

void AEndlessRunnerGameModeBase::PlayerDied()
{
	NumberOfLives -= 1;
	OnLivesCountChanged.Broadcast(NumberOfLives);

	if(NumberOfLives > 0)
	{
		//Iterate all FloorTiles and call DestroryFloorTiles
		// for(AFloorTile* Tile : FloorTiles)
		for(auto Tile : FloorTiles)
		{
			Tile->DestroyFloorTile();
		}
		//Empty our array

		FloorTiles.Empty();

		//Next SpawnPoin to initial value
		NextSpawnPoint = FTransform();
		//Create our Initial Floor tiles
		CreateInitialFloorTiles();
		//Broadcast Level reset event
		OnLevelReset.Broadcast();
	}
	else
	{
		//GameOver
	}
	
}

void AEndlessRunnerGameModeBase::RemoveTile(AFloorTile* Tile)
{
	FloorTiles.Remove(Tile);
	
}




