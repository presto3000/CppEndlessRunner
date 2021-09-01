// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameModeBase.generated.h"

class AFloorTile;
class UUserWidget;

// only multicaste delegates work in blueprint and c++, multicast means we can add several functions.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoinsCountChanged, int32, CoinsCount);

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API AEndlessRunnerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<UUserWidget> GameHudClass;
	
	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<AFloorTile> FloorTileClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class UGameHud* GameHud;

	UPROPERTY(VisibleAnywhere)
	int32 TotalCoins = 0;
	
	UPROPERTY(EditAnywhere, Category = "Config")
	int32 NumInitialFloorTiles = 10;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	FTransform NextSpawnPoint;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	TArray<float> LaneSwitchValues;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
	FOnCoinsCountChanged OnCoinsCountChanged;
	

	UFUNCTION(BlueprintCallable)
	void CreateInitialFloorTiles();

	UFUNCTION(BlueprintCallable)
	AFloorTile* AddFloorTile(const bool bSpawnItems);

	UFUNCTION(BlueprintCallable)
	void AddCoin();
	
protected:
	virtual void BeginPlay() override;
	



	
};
