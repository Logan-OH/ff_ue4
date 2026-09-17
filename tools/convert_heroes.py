"""Convert Crown Circuit hero JSON into an Unreal Data Table import file.

Usage:
    python tools/convert_heroes.py shared/data/heroes.json CrownCircuit/Content/Data/DT_Heroes.json

The generated file is JSON text. In Unreal, create/import a Data Table whose row
struct is FCCHeroDefinition, then import this JSON as the row data.
"""
from __future__ import annotations
import argparse
import json
from pathlib import Path

ARCHETYPES = {"Vanguard", "Bruiser", "Striker", "Assassin", "Controller", "Support", "Specialist"}
STAT_KEYS = ("power", "defense", "speed", "skill", "control", "support")

def normalize(hero: dict) -> dict:
    missing = [k for k in ("id", "name", "archetype", "stats", "abilities") if k not in hero]
    if missing:
        raise ValueError(f"{hero.get('name', '<unknown>')}: missing {missing}")
    if hero["archetype"] not in ARCHETYPES:
        raise ValueError(f"{hero['name']}: invalid archetype {hero['archetype']}")
    stats = hero["stats"]
    for key in STAT_KEYS:
        value = int(stats.get(key, -1))
        if not 0 <= value <= 100:
            raise ValueError(f"{hero['name']}: {key} must be 0-100")
    combat = hero.get("combat", {})
    abilities = [
        {
            "Id": ability.get("id") or ability.get("name", "ability").lower().replace(" ", "_"),
            "Name": ability.get("name", "Ability"),
            "Description": ability.get("description", ""),
            "Type": ability.get("type", "active"),
        }
        for ability in hero.get("abilities", [])
    ]
    return {
        "Name": hero["id"],
        "Id": hero["id"],
        "Name_0": hero["name"],
        "Alias": hero.get("alias", ""),
        "Archetype": hero["archetype"],
        "SecondaryArchetype": hero.get("secondaryArchetype", ""),
        "Stats": {
            "Power": int(stats["power"]), "Defense": int(stats["defense"]), "Speed": int(stats["speed"]),
            "Skill": int(stats["skill"]), "Control": int(stats["control"]), "Support": int(stats["support"]),
        },
        "MaxHealth": int(combat.get("maxHealth", 100)),
        "BaseShield": int(combat.get("baseShield", 0)),
        "Abilities": abilities,
        "Tags": hero.get("tags", []),
    }

def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("input")
    parser.add_argument("output")
    args = parser.parse_args()
    source = json.loads(Path(args.input).read_text(encoding="utf-8"))
    if isinstance(source, dict):
        source = source.get("heroes", [])
    rows = [normalize(hero) for hero in source]
    if len({row["Id"] for row in rows}) != len(rows):
        raise ValueError("Duplicate hero IDs")
    Path(args.output).parent.mkdir(parents=True, exist_ok=True)
    Path(args.output).write_text(json.dumps(rows, indent=2), encoding="utf-8")
    print(f"Wrote {len(rows)} hero rows to {args.output}")

if __name__ == "__main__":
    main()
