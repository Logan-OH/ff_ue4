#include "CCOperationDirector.h"

ACCOperationDirector::ACCOperationDirector()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ACCOperationDirector::FocusLane(FName LaneId)
{
    FocusLane = LaneId;
    OnLaneFocusChanged.Broadcast(LaneId);
    if (LaneId == TEXT("global")) BP_ReturnToOverview();
    else BP_FocusLane(LaneId);
}
