# Blueprint architecture

Crown Circuit should remain Blueprint-first. C++ in this repository exists mainly to expose clean Blueprint nodes for HTTP/data operations and stable base actor contracts.

## BP_CCOperationDirector

Responsibilities:
- own overview camera and one camera per lane
- receive lane selection from UMG
- call `FocusLane(LaneId)`
- blend camera to lane over ~0.75 seconds
- spawn/show only heroes associated with the selected lane
- return to overview when `global` is selected

Suggested graph:

`OnLaneButtonClicked -> FocusLane -> BP_FocusLane -> Find Lane Camera -> Set View Target With Blend`

## BP_HeroBase

Responsibilities:
- display the hero visual
- apply team outline/color
- maintain HP/shield/status visuals
- expose animation/VFX events for attack, support, reposition, KO
- never decide fantasy scoring itself

Suggested graph:

`OnLiveStateChanged -> Update Health UI -> Update Shield FX -> Update Current Action`

`PlayAbility -> Switch on Ability ID/Tag -> Montage/VFX -> Impact reaction`

## WBP_LiveOperation

Responsibilities:
- matchup score and progression chart
- operation clock
- lane buttons
- CrownCast feed
- selected-hero telemetry
- league board

## Data flow

`Python API -> UCCBackendSubsystem -> Blueprint event -> UI / Operation Director / Hero actors`

For live play, move from polling to `/ws/live` once the first local vertical slice is working.
