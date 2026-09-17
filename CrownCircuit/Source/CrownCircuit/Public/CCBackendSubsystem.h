#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/IHttpRequest.h"
#include "CCBackendSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCCApiResponse, bool, bSuccess, const FString&, Json);

UCLASS(BlueprintType)
class CROWNCIRCUIT_API UCCBackendSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Crown Circuit|API") FString BaseUrl = TEXT("http://127.0.0.1:8000");
    UPROPERTY(BlueprintAssignable, Category="Crown Circuit|API") FCCApiResponse OnApiResponse;

    UFUNCTION(BlueprintCallable, Category="Crown Circuit|API") void GetLeagueState();
    UFUNCTION(BlueprintCallable, Category="Crown Circuit|API") void SaveLineup(const TArray<FString>& HeroIds);
    UFUNCTION(BlueprintCallable, Category="Crown Circuit|API") void StartOperation(const FString& Mode = TEXT("quick"));
    UFUNCTION(BlueprintCallable, Category="Crown Circuit|API") void SendJsonRequest(const FString& Verb, const FString& Path, const FString& JsonBody);

private:
    void HandleResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
};
