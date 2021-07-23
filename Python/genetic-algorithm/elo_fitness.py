from itertools import count
import random

from deap import base
from deap import creator
from deap import tools

from elo import calculate_elo


def fight(individual1, individual2):
    if individual1.strenght > individual2.strenght:
        return 1, 0

    if individual1.strenght < individual2.strenght:
        return 0, 1

    return 1, 1


def elo_evaluation(individual):
    remaining_population = [foe for foe in toolbox.population() if foe.number > individual.number]

    for foe in remaining_population:
        individual_score, foe_score = fight(individual, foe)
        calculate_elo(individual.fitness, foe.fitness, individual_score, foe_score)


creator.create("FitnessMax", base.Fitness, weights=(1.0,))
creator.create("Individual", list, fitness=creator.FitnessMax)

toolbox = base.Toolbox()

N_CYCLES = 4
POPULATION_SIZE = 16

toolbox.register("number", count().__next__)
toolbox.register("strenght", random.randint, 0, 255)
toolbox.register("individual", tools.initCycle, creator.Individual,
                 (toolbox.number, toolbox.strenght), n=N_CYCLES)
toolbox.register("population", tools.initRepeat, list, toolbox.individual)
toolbox.population(n=POPULATION_SIZE)
toolbox.register("evaluate", calculate_elo)

pass
