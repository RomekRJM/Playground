from collections import OrderedDict
from datetime import datetime


class DeltaSupply:
    def __init__(self):
        self.supply_delta = 0
        self.worker_delta = 0


class SupplyInfo:
    def __init__(self, replay_name):
        self.replay_name = replay_name
        self.time_mm_ss = []
        self.workers = []
        self.total = []
        self.size = 0

    def insert(self, time_mm_ss, workers, total):
        self.time_mm_ss.append(time_mm_ss)
        self.workers.append(workers)
        self.total.append(total)
        self.size += 1


class SupplyTimeseries:
    def __init__(self, replay_name: str, replay_date: datetime):
        self.replay_name = replay_name
        self.replay_date = replay_date
        self.delta_supply_timeseries = OrderedDict()

    def add_data_point(self, timer: str, supply_delta: int, is_worker: bool):
        if timer in self.delta_supply_timeseries:
            delta = self.delta_supply_timeseries[timer]
            delta.supply_delta += supply_delta

            if is_worker:
                delta.worker_delta += supply_delta
        else:
            self.delta_supply_timeseries[timer] = DeltaSupply()

    def compute_supply_info(self) -> SupplyInfo:
        for timer in sorted(self.delta_supply_timeseries):
            self.delta_supply_timeseries.move_to_end(timer)

        worker_supply = 0
        total_supply = 0

        supply_info = SupplyInfo(self.replay_name)

        for t, delta in self.delta_supply_timeseries.items():
            worker_supply += delta.worker_delta
            total_supply += delta.supply_delta

            supply_info.insert(t, worker_supply, total_supply)

        return supply_info
