# First local run

## 1. Clone the repo

```powershell
git clone https://github.com/Logan-OH/ff_ue4.git
cd ff_ue4
git checkout feature/unreal-migration
```

## 2. Start the API

```powershell
cd backend
py -m venv .venv
.venv\Scripts\Activate.ps1
pip install -r requirements.txt
uvicorn app.main:app --reload --port 8000
```

Verify `http://127.0.0.1:8000/health`.

## 3. Generate Unreal project files

Right-click `CrownCircuit/CrownCircuit.uproject` and choose **Generate Visual Studio project files** (or use your installed Unreal version's GenerateProjectFiles workflow).

Open the project and allow Unreal to compile the C++ module.

## 4. Create the initial Blueprint assets

Create `/Game/CrownCircuit/Maps/L_Main` first so the configured startup map exists. Then create:

- `BP_CCOperationDirector` from `ACCOperationDirector`
- `BP_HeroBase` from `ACCHeroActor`
- `WBP_MainShell`
- `WBP_LiveOperation`
- `WBP_Roster`

## 5. Test API from Blueprint

On BeginPlay:

`Get Game Instance Subsystem (CCBackendSubsystem) -> Bind OnApiResponse -> GetLeagueState`

Print the returned JSON to screen first. Once this works, wire it to UMG.

## 6. Connect the live socket

`CCBackendSubsystem -> Bind OnLiveMessage -> ConnectLiveSocket`

The WebSocket is the long-term path for CrownCast/live operation events.
