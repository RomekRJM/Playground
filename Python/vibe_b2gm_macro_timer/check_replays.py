from collections import OrderedDict
from typing import Optional

import sc2reader


class PlayerMock:
    def __init__(self):
        self.name = ''


def convert_to_seconds(frame: Optional[int]) -> Optional[int]:
    if frame is None:
        return None

    return frame // 16


def convert_to_mm_ss(seconds: int) -> str:
    min = seconds // 60
    reminding_sec = seconds % 60

    return "{}:{}".format(str(min).zfill(2), str(reminding_sec).zfill(2))


def getattr_non_empty(x, attr, default):
    val = getattr(x, attr, default)

    return val if val else default


def update_value(d, key, value):
    if key in d:
        d[key] = d[key] + value
    else:
        d[key] = value


def sort_dict_by_key(d):
    for key in sorted(d):
        d.move_to_end(key)


if __name__ == '__main__':
    replay = sc2reader.load_replay('2022-07-12PvP.SC2Replay', load_level=4)

    player_units = [event.unit for event in replay.events if getattr_non_empty(getattr_non_empty(event, 'unit_controller', PlayerMock()), 'name', '') == 'RJM']
    player_units = [unit for unit in player_units if not unit.hallucinated]
    supply_per_second = OrderedDict()
    workers_per_second = OrderedDict()

    for unit in player_units:
        born = convert_to_seconds(unit.finished_at)
        died = convert_to_seconds(unit.died_at)

        if born:
            update_value(supply_per_second, born, unit.supply)

            if unit.is_worker:
                update_value(workers_per_second, born, unit.supply)

        if died:
            update_value(supply_per_second, died, -unit.supply)

            if unit.is_worker:
                update_value(workers_per_second, died, -unit.supply)

    sort_dict_by_key(supply_per_second)
    sort_dict_by_key(workers_per_second)

    total_supply = 12

    for t, change in supply_per_second.items():
        total_supply += change
        print("{} - {}".format(convert_to_mm_ss(t), total_supply))

    pass
