// Copyright Epic Games, Inc. All Rights Reserved.

#include "AI_Test/Public/AI_TestGameMode.h"
#include "AI_Test/Public/Player/AI_TestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAI_TestGameMode::AAI_TestGameMode()
	: Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/AI_Test/Core/Characters/Player/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}