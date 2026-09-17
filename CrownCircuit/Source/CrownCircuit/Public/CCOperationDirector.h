#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCOperationDirector.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCCLaneFocusChanged, FName, LaneId);

UCLASS(Blueprintable)
class CROWNCIRCUIT_API ACCOperationDirector : public AActor
{
    GENERATED_BODY()
public:
    ACCOperationDirector();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Crown Circuit|Operation") FName OperationId;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Crown Circuit|Operation") FName FocusLane = TEXT("global");
    UPROPERTY(BlueprintAssignable, Category="Crown Circuit|Operation") FCCLaneFocusChanged OnLaneFocusChanged;

    UFUNCTION(BlueprintCallable, Category="Crown Circuit|Operation") void FocusLane(FName LaneId);
    UFUNCTION(BlueprintImplementableEvent, Category="Crown Circuit|Operation") void BP_FocusLane(FName LaneId);
    UFUNCTION(BlueprintImplementableEvent, Category="Crown Circuit|Operation") void BP_ReturnToOverview();
};
