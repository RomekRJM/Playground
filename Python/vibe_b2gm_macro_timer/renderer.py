from Python.vibe_b2gm_macro_timer.data import SupplyTimeseries


def render_html(supply_timeseries: SupplyTimeseries):
    pass


def render_to_std_out(supply_timeseries: SupplyTimeseries):
    timeseries = supply_timeseries.sort_and_get()

    total_supply = 0
    worker_supply = 0

    for t, delta in timeseries.items():
        total_supply += delta.supply_delta
        worker_supply += delta.worker_delta
        print("{} - workers: {}, army: {}, total: {}"
              .format(t, worker_supply, total_supply - worker_supply, total_supply))