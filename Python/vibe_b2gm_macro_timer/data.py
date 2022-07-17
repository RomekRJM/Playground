from collections import OrderedDict
from datetime import datetime


class SupplyTimeseries:
    def __init__(self, replay_name: str, replay_date: datetime,
                 supply_timeseries: OrderedDict, worker_timeseries: OrderedDict):
        self.replay_name = replay_name
        self.replay_date = replay_date
        self.supply_timeseries = supply_timeseries
        self.worker_timeseries = worker_timeseries
