from Python.vibe_b2gm_macro_timer.data import SupplyTimeseries
from jinja2 import Environment, FileSystemLoader, select_autoescape


def render_to_html(supply_timeseries: SupplyTimeseries, output_file: str):
    env = Environment(
        loader=FileSystemLoader(searchpath="./templates"),
        autoescape=select_autoescape()
    )

    template = env.get_template("template.html")

    with open(output_file, 'w') as f:
        f.write(template.render(replay_name=supply_timeseries.replay_name))


def render_to_std_out(supply_timeseries: SupplyTimeseries):
    timeseries = supply_timeseries.sort_and_get()

    total_supply = 0
    worker_supply = 0

    for t, delta in timeseries.items():
        total_supply += delta.supply_delta
        worker_supply += delta.worker_delta
        print("{} - workers: {}, army: {}, total: {}"
              .format(t, worker_supply, total_supply - worker_supply, total_supply))