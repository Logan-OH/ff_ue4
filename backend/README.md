# Crown Circuit backend

The Unreal client owns presentation. This API owns persistent league state and authoritative fantasy-league rules.

Run locally:

```powershell
py -m venv .venv
.venv\Scripts\Activate.ps1
pip install -r requirements.txt
uvicorn app.main:app --reload --port 8000
```

Health check: `http://127.0.0.1:8000/health`

The first migration milestone exposes state, lineup saving, operation start, and a WebSocket endpoint. The legacy simulator will be ported into this package after the new 100-character data file is imported.
