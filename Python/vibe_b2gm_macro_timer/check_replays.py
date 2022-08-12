from datetime import datetime
from typing import Optional

import sc2reader

from Python.vibe_b2gm_macro_timer.data import SupplyTimeseries
from Python.vibe_b2gm_macro_timer.renderer import render_to_html


class PlayerMock:
    def __init__(self):
        self.name = ''


def convert_to_mm_ss(frame: Optional[int]) -> Optional[str]:
    if frame is None:
        return None

    seconds = frame // 16
    min = seconds // 60
    reminding_sec = seconds % 60

    return "{}:{}".format(str(min).zfill(2), str(reminding_sec).zfill(2))


def getattr_non_empty(x, attr, default):
    val = getattr(x, attr, default)

    return val if val else default


if __name__ == '__main__':
    replay = sc2reader.load_replay('2022-07-12PvP.SC2Replay', load_level=4)

    player_units = [event.unit for event in replay.events if
                    getattr_non_empty(getattr_non_empty(event, 'unit_controller', PlayerMock()), 'name',
                                      '') == 'RJM']
    player_units = [unit for unit in player_units if not unit.hallucinated and (unit.is_worker or unit.is_army)]

    timeseries = SupplyTimeseries('{}, {} vs {}'
                                  .format(replay.map_name, replay.humans[0].name, replay.humans[1].name),
                                  datetime.utcnow()
                                  )

    for unit in player_units:
        born = convert_to_mm_ss(unit.finished_at)
        died = convert_to_mm_ss(unit.died_at)

        if born:
            timeseries.add_data_point(born, unit.supply, unit.is_worker)

        if died:
            timeseries.add_data_point(died, -unit.supply, unit.is_worker)

    render_to_html(timeseries.compute_supply_info(), 'chart.html')
