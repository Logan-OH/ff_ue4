#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCDataTypes.h"
#include "CCHeroActor.generated.h"

UCLASS(Blueprintable)
class CROWNCIRCUIT_API ACCHeroActor : public AActor
{
    GENERATED_BODY()
public:
    ACCHeroActor();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Crown Circuit|Hero") FCCHeroDefinition Definition;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Crown Circuit|Hero") FCCLiveHeroState LiveState;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Crown Circuit|Hero") FName TeamId;

    UFUNCTION(BlueprintCallable, Category="Crown Circuit|Hero") void ApplyLiveState(const FCCLiveHeroState& NewState);
    UFUNCTION(BlueprintImplementableEvent, Category="Crown Circuit|Hero") void OnLiveStateChanged();
    UFUNCTION(BlueprintImplementableEvent, Category="Crown Circuit|Hero") void PlayAbility(FName AbilityId, AActor* Target);
    UFUNCTION(BlueprintImplementableEvent, Category="Crown Circuit|Hero") void PlayKnockout();
};
