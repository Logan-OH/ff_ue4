from __future__ import annotations
from fastapi import FastAPI, WebSocket, WebSocketDisconnect
from pydantic import BaseModel
from typing import List

app = FastAPI(title="Crown Circuit API", version="0.1.0")

STATE = {
    "league": None,
    "lineup": [],
    "operation": None,
    "revision": 0,
}
SOCKETS: set[WebSocket] = set()

class LineupRequest(BaseModel):
    lineup: List[str | None]

class StartOperationRequest(BaseModel):
    mode: str = "quick"

async def broadcast(payload: dict):
    dead = []
    for socket in SOCKETS:
        try:
            await socket.send_json(payload)
        except Exception:
            dead.append(socket)
    for socket in dead:
        SOCKETS.discard(socket)

@app.get("/health")
def health():
    return {"ok": True, "service": "crown-circuit-api"}

@app.get("/api/state")
def get_state():
    return STATE

@app.post("/api/lineup")
async def save_lineup(request: LineupRequest):
    STATE["lineup"] = request.lineup[:6]
    STATE["revision"] += 1
    await broadcast({"type": "state", "state": STATE})
    return STATE

@app.post("/api/slate/start")
async def start_operation(request: StartOperationRequest):
    STATE["operation"] = {"mode": request.mode, "status": "running", "tick": 0}
    STATE["revision"] += 1
    await broadcast({"type": "operation_started", "operation": STATE["operation"]})
    return STATE

@app.websocket("/ws/live")
async def live_socket(socket: WebSocket):
    await socket.accept()
    SOCKETS.add(socket)
    await socket.send_json({"type": "state", "state": STATE})
    try:
        while True:
            await socket.receive_text()
    except WebSocketDisconnect:
        SOCKETS.discard(socket)
