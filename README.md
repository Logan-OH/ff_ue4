# Crown Circuit — Unreal migration

This repository is the new Unreal Engine version of Crown Circuit. The existing web build remains frozen separately as a fallback/reference implementation.

## Architecture

```text
Browser (later, Pixel Streaming)
        ↓
Unreal Engine client
Blueprints / UMG / Niagara / maps / cameras
        ↓ HTTP + WebSocket
Python API
leagues / draft / rosters / transactions / scoring / operation events
        ↓
database
```

## Repository

- `CrownCircuit/` — Unreal project and Blueprint-facing C++ foundation
- `backend/` — FastAPI service
- `shared/` — shared schemas/data
- `tools/` — hero/data migration utilities
- `docs/` — Blueprint and migration documentation

## Start here

Read `docs/FIRST_RUN.md`, then `docs/UNREAL_MIGRATION.md` and `docs/BLUEPRINT_ARCHITECTURE.md`.

The migration branch is `feature/unreal-migration`.

## Design principle

Crown Circuit is Blueprint-first. C++ only provides stable integration/data primitives. The visual game, cameras, lane flow, characters, VFX, and UMG remain editable in Blueprints.
