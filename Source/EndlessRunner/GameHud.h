// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "EndlessRunnerGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "GameHud.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API UGameHud : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CoinsCount;
	
public: 
	UFUNCTION(BlueprintCallable)
	void InitializeHUD(AEndlessRunnerGameModeBase* RunGameMode);

	UFUNCTION(BlueprintCallable)
	void SetCoinsCount(int32 Count);
};
