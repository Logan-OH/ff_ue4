#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CCDataTypes.generated.h"

UENUM(BlueprintType)
enum class ECCHeroArchetype : uint8
{
    Vanguard, Bruiser, Striker, Assassin, Controller, Support, Specialist
};

USTRUCT(BlueprintType)
struct CROWNCIRCUIT_API FCCHeroStats
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Power = 50;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Defense = 50;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Speed = 50;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Skill = 50;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Control = 50;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Support = 50;
};

USTRUCT(BlueprintType)
struct CROWNCIRCUIT_API FCCAbilityDefinition
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName Id;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Name;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Description;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName Type;
};

USTRUCT(BlueprintType)
struct CROWNCIRCUIT_API FCCHeroDefinition : public FTableRowBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName Id;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Name;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Alias;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) ECCHeroArchetype Archetype = ECCHeroArchetype::Specialist;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName SecondaryArchetype;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FCCHeroStats Stats;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 MaxHealth = 100;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 BaseShield = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FCCAbilityDefinition> Abilities;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> Tags;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TSoftObjectPtr<UTexture2D> Portrait;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TSoftObjectPtr<UObject> BattleVisual;
};

USTRUCT(BlueprintType)
struct CROWNCIRCUIT_API FCCLiveHeroState
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite) FName HeroId;
    UPROPERTY(BlueprintReadWrite) FName TeamId;
    UPROPERTY(BlueprintReadWrite) FName LaneId;
    UPROPERTY(BlueprintReadWrite) float Points = 0.f;
    UPROPERTY(BlueprintReadWrite) float Health = 100.f;
    UPROPERTY(BlueprintReadWrite) float MaxHealth = 100.f;
    UPROPERTY(BlueprintReadWrite) float Shield = 0.f;
    UPROPERTY(BlueprintReadWrite) int32 Damage = 0;
    UPROPERTY(BlueprintReadWrite) int32 Healing = 0;
    UPROPERTY(BlueprintReadWrite) int32 Objectives = 0;
    UPROPERTY(BlueprintReadWrite) bool bActive = true;
    UPROPERTY(BlueprintReadWrite) FText CurrentAction;
};

USTRUCT(BlueprintType)
struct CROWNCIRCUIT_API FCCOperationEvent
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite) FName Type;
    UPROPERTY(BlueprintReadWrite) FName LaneId;
    UPROPERTY(BlueprintReadWrite) FName HeroId;
    UPROPERTY(BlueprintReadWrite) FName OtherHeroId;
    UPROPERTY(BlueprintReadWrite) FText Message;
    UPROPERTY(BlueprintReadWrite) float Points = 0.f;
};
