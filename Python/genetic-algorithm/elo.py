k_factor = {
    0: 32,
    2100: 24,
    2400: 16
}


def calculate_elo(rating_a, rating_b, a_result, b_result):
    qa = 10 ** (rating_a / 400.0)
    qb = 10 ** (rating_b / 400.0)

    ea = qa / (qa + qb)
    eb = 1 - ea

    k_a = max([k for elo, k in k_factor.items() if rating_a > elo])
    k_b = max([k for elo, k in k_factor.items() if rating_b > elo])

    return (
        round(rating_a + k_a * (a_result - ea)),
        round(rating_b + k_b * (b_result - eb)),
    )