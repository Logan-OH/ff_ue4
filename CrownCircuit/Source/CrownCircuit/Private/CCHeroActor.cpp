#include "CCHeroActor.h"

ACCHeroActor::ACCHeroActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ACCHeroActor::ApplyLiveState(const FCCLiveHeroState& NewState)
{
    const bool bWasActive = LiveState.bActive;
    LiveState = NewState;
    OnLiveStateChanged();
    if (bWasActive && !LiveState.bActive) PlayKnockout();
}
