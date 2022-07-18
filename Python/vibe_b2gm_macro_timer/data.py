from collections import OrderedDict
from datetime import datetime


class DeltaSupply:
    def __init__(self):
        self.supply_delta = 0
        self.worker_delta = 0


class SupplyTimeseries:
    def __init__(self, replay_name: str, replay_date: datetime):
        self.replay_name = replay_name
        self.replay_date = replay_date
        self.supply_timeseries = OrderedDict()

    def add_data_point(self, timer: str, supply_delta: int, is_worker: bool):
        if timer in self.supply_timeseries:
            delta = self.supply_timeseries[timer]
            delta.supply_delta += supply_delta

            if is_worker:
                delta.worker_delta += supply_delta
        else:
            self.supply_timeseries[timer] = DeltaSupply()

    def sort_and_get(self):
        for timer in sorted(self.supply_timeseries):
            self.supply_timeseries.move_to_end(timer)

        return self.supply_timeseries
