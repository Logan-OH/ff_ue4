from __future__ import annotations
from dataclasses import dataclass, asdict
from random import Random
from typing import Iterable

@dataclass
class LiveHero:
    hero_id: str
    team_id: str
    lane_id: str
    health: float
    max_health: float
    shield: float = 0.0
    points: float = 0.0
    active: bool = True

@dataclass
class OperationEvent:
    type: str
    lane_id: str
    hero_id: str
    other_hero_id: str | None
    message: str
    points: float = 0.0

class OperationSimulator:
    """Deterministic strategic simulator.

    Unreal consumes these events and decides how to animate/present them. The
    simulator deliberately does not depend on Unreal animation timing.
    """
    def __init__(self, seed: int, heroes: Iterable[LiveHero]):
        self.rng = Random(seed)
        self.heroes = {hero.hero_id: hero for hero in heroes}
        self.tick_index = 0

    def tick(self) -> list[dict]:
        self.tick_index += 1
        active = [h for h in self.heroes.values() if h.active]
        if len(active) < 2:
            return []
        attacker = self.rng.choice(active)
        opponents = [h for h in active if h.team_id != attacker.team_id]
        if not opponents:
            return []
        defender = self.rng.choice(opponents)
        damage = self.rng.randint(6, 18)
        absorbed = min(defender.shield, damage)
        defender.shield -= absorbed
        defender.health = max(0.0, defender.health - (damage - absorbed))
        attacker.points += round(damage * 0.11, 1)
        if defender.health <= 0:
            defender.active = False
        event = OperationEvent(
            type="engagement" if defender.active else "knockout",
            lane_id=attacker.lane_id,
            hero_id=attacker.hero_id,
            other_hero_id=defender.hero_id,
            message=f"{attacker.hero_id} hits {defender.hero_id} for {damage} damage",
            points=round(damage * 0.11, 1),
        )
        return [{"event": asdict(event), "heroes": [asdict(attacker), asdict(defender)]}]
