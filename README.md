# Crown Circuit — Unreal Migration

Crown Circuit is being migrated from the original Flask/HTML/JavaScript prototype into a Blueprint-first Unreal Engine client with a lightweight Python API backend.

## High-level architecture

- `CrownCircuit/` — Unreal Engine project
- `backend/` — Flask API and authoritative league state
- `shared/` — data contracts shared between Unreal and the backend
- `docs/` — migration notes, Blueprint architecture, and development workflow

The legacy web prototype is intentionally kept outside this repository as a fallback/reference implementation.

## First milestone

1. Open the Unreal project.
2. Create Blueprint assets from the supplied base classes / interfaces.
3. Import hero JSON into a Data Table or Data Assets.
4. Run the Python backend locally.
5. Connect the Unreal HTTP client to `http://127.0.0.1:8000`.
6. Rebuild the existing league → draft → roster → live operation loop.

See `docs/UNREAL_MIGRATION.md` for the full migration plan.
