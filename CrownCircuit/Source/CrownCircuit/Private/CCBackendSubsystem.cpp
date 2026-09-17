#include "CCBackendSubsystem.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "WebSocketsModule.h"
#include "IWebSocket.h"

void UCCBackendSubsystem::Deinitialize()
{
    DisconnectLiveSocket();
    Super::Deinitialize();
}

void UCCBackendSubsystem::GetLeagueState()
{
    SendJsonRequest(TEXT("GET"), TEXT("/api/state"), TEXT(""));
}

void UCCBackendSubsystem::SaveLineup(const TArray<FString>& HeroIds)
{
    TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();
    TArray<TSharedPtr<FJsonValue>> Values;
    for (const FString& Id : HeroIds) Values.Add(Id.IsEmpty() ? MakeShared<FJsonValueNull>() : MakeShared<FJsonValueString>(Id));
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

void UCCBackendSubsystem::ConnectLiveSocket()
{
    if (LiveSocket.IsValid() && LiveSocket->IsConnected()) return;

    FString SocketUrl = BaseUrl;
    SocketUrl.ReplaceInline(TEXT("https://"), TEXT("wss://"));
    SocketUrl.ReplaceInline(TEXT("http://"), TEXT("ws://"));
    SocketUrl += TEXT("/ws/live");

    LiveSocket = FWebSocketsModule::Get().CreateWebSocket(SocketUrl);
    LiveSocket->OnMessage().AddLambda([this](const FString& Message)
    {
        OnLiveMessage.Broadcast(Message);
    });
    LiveSocket->Connect();
}

void UCCBackendSubsystem::DisconnectLiveSocket()
{
    if (LiveSocket.IsValid())
    {
        LiveSocket->Close();
        LiveSocket.Reset();
    }
}

bool UCCBackendSubsystem::IsLiveSocketConnected() const
{
    return LiveSocket.IsValid() && LiveSocket->IsConnected();
}
