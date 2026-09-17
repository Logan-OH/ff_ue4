#include "CCBackendSubsystem.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"

void UCCBackendSubsystem::GetLeagueState()
{
    SendJsonRequest(TEXT("GET"), TEXT("/api/state"), TEXT(""));
}

void UCCBackendSubsystem::SaveLineup(const TArray<FString>& HeroIds)
{
    TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();
    TArray<TSharedPtr<FJsonValue>> Values;
    for (const FString& Id : HeroIds) Values.Add(MakeShared<FJsonValueString>(Id));
    Root->SetArrayField(TEXT("lineup"), Values);
    FString Body;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Body);
    FJsonSerializer::Serialize(Root, Writer);
    SendJsonRequest(TEXT("POST"), TEXT("/api/lineup"), Body);
}

void UCCBackendSubsystem::StartOperation(const FString& Mode)
{
    TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();
    Root->SetStringField(TEXT("mode"), Mode);
    FString Body;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Body);
    FJsonSerializer::Serialize(Root, Writer);
    SendJsonRequest(TEXT("POST"), TEXT("/api/slate/start"), Body);
}

void UCCBackendSubsystem::SendJsonRequest(const FString& Verb, const FString& Path, const FString& JsonBody)
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(BaseUrl + Path);
    Request->SetVerb(Verb);
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    if (!JsonBody.IsEmpty()) Request->SetContentAsString(JsonBody);
    Request->OnProcessRequestComplete().BindUObject(this, &UCCBackendSubsystem::HandleResponse);
    Request->ProcessRequest();
}

void UCCBackendSubsystem::HandleResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
    const bool bOk = bConnectedSuccessfully && Response.IsValid() && EHttpResponseCodes::IsOk(Response->GetResponseCode());
    OnApiResponse.Broadcast(bOk, Response.IsValid() ? Response->GetContentAsString() : TEXT(""));
}
