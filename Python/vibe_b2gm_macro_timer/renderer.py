from Python.vibe_b2gm_macro_timer.data import SupplyInfo
from jinja2 import Environment, FileSystemLoader, select_autoescape


def render_to_html(supply_info: SupplyInfo, output_file: str):
    env = Environment(
        loader=FileSystemLoader(searchpath="./templates"),
        autoescape=select_autoescape()
    )

    template = env.get_template("template.html.j2")

    with open(output_file, 'w') as f:
        f.write(
            template.render(
                replay_name=supply_info.replay_name,
                time_mm_ss=supply_info.time_mm_ss,
                workers=supply_info.workers,
                total=supply_info.total,
            )
        )


def render_to_std_out(supply_info: SupplyInfo):
    for i in range(supply_info.size):
        print("{} - workers: {}, army: {}, total: {}"
              .format(supply_info.time_mm_ss[i], supply_info.workers[i],
                      supply_info.total[i] - supply_info.workers[i], supply_info.total[i]))