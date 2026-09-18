# Unreal migration plan

## Goal

Rebuild Crown Circuit as a Blueprint-first Unreal project while retaining a lightweight Python service for league persistence and authoritative fantasy rules. Keep the existing web build frozen as the fallback/reference version.

## System ownership

### Unreal Engine
- 3D/isometric operation maps
- lane cameras and zoom transitions
- hero actors / 2D or 3D battle presentation
- Niagara ability and environment effects
- UMG draft, roster, standings, CrownCast, hero dossier, matchup, and victory screens
- operation playback and animation
- Pixel Streaming presentation

### Python API
- accounts/session identity
- leagues and teams
- draft state
- rosters and saved lineups
- trades and waivers
- rankings and status/injury persistence
- schedules/results
- authoritative scoring inputs/results
- synchronized live-operation event stream

## Blueprint-first asset plan

Create these assets in the editor under `/Game/CrownCircuit`:

- `Core/BP_CCGameMode`
- `Core/BP_CCPlayerController`
- `Core/BP_CCOperationDirector` (child of `ACCOperationDirector`)
- `Heroes/BP_HeroBase` (child of `ACCHeroActor`)
- `Heroes/DA_Hero_*` or `DT_Heroes`
- `Maps/L_Main`
- `Maps/L_HarborDrop`
- `UI/WBP_MainShell`
- `UI/WBP_Draft`
- `UI/WBP_Roster`
- `UI/WBP_LiveOperation`
- `UI/WBP_HeroDossier`
- `UI/WBP_Encounter`
- `UI/WBP_Victory`

## First playable slice

1. Start local Python API on port 8000.
2. Open `CrownCircuit.uproject` and compile the module.
3. Create `L_Main` and the Blueprint children above.
4. On BeginPlay, get `CCBackendSubsystem` and call `GetLeagueState`.
5. Bind `OnApiResponse` in Blueprint and update UMG from returned state.
6. Build Harbor Drop as the first Unreal map.
7. Spawn six blue and six red hero actors from the saved lineup.
8. Use `BP_CCOperationDirector` to switch between overview and lane cameras.
9. Drive combat visuals from server operation events rather than calculating fantasy results from animation.

## Migration rule

Do not copy DOM/UI implementation details from the web prototype. Port game concepts and data contracts, then rebuild presentation natively in Unreal.
