// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UPauseMenu::NativeConstruct()
{
	if(ContinueBtn)
	{
		ContinueBtn->OnClicked.AddDynamic(this, &UPauseMenu::OnContinueClick);
	}

	if(RestartBtn)
	{
		RestartBtn->OnClicked.AddDynamic(this, &UPauseMenu::OnRestartClick);
		
	}
	
}

void UPauseMenu::OnContinueClick()
{

		UGameplayStatics::SetGamePaused(GetWorld(), false);
		//remove the widget created
		RemoveFromParent();

}

void UPauseMenu::OnRestartClick()
{
	//restart the level console command
	UWorld* World = GetWorld();
	if(World)
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(World, TEXT("RestartLevel"));
	}
	
}
