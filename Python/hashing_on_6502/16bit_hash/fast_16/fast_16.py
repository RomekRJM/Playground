PAD_RIGHT = 128
PAD_LEFT = 64
PAD_DOWN = 32
PAD_UP = 16
PAD_START = 8
PAD_SELECT = 4
PAD_B = 2
PAD_A = 1

R0 = 0
R1 = 4
R2 = 8
R3 = 12

moves_list = [
    [PAD_DOWN | PAD_LEFT | R0, PAD_B | R1],
    [PAD_DOWN | R0, PAD_LEFT | R1, PAD_DOWN | R2, PAD_B | R3],
    [PAD_LEFT | R0, PAD_DOWN | R1, PAD_LEFT | R2, PAD_B | R3],
    [PAD_DOWN | PAD_LEFT | R0, PAD_LEFT | R1, PAD_B | R2],
    [PAD_DOWN | PAD_LEFT | R0, PAD_DOWN | R1, PAD_B | R2],
    [PAD_RIGHT | R0, PAD_RIGHT | R1, PAD_B | PAD_RIGHT | R2],
    [PAD_RIGHT | R0, PAD_RIGHT | R1, PAD_B | R2],
    [PAD_RIGHT | R0, PAD_RIGHT | R1, PAD_A | PAD_RIGHT | R2],
    [PAD_RIGHT | R0, PAD_RIGHT | R1, PAD_A | R2],
    [PAD_B | PAD_RIGHT | R0],
    [PAD_RIGHT | R0, PAD_B | R1],
    [PAD_B | PAD_LEFT | R0],
    [PAD_B | PAD_UP | R0],
    [PAD_B | PAD_LEFT | PAD_UP | R0],
    [PAD_B | PAD_RIGHT | PAD_UP | R0],
    [PAD_B | PAD_DOWN | R0],
    [PAD_B | PAD_LEFT | PAD_DOWN | R0],
    [PAD_B | PAD_RIGHT | PAD_DOWN | R0],
    [PAD_B | R0],
    [PAD_A | PAD_LEFT | R0],
    [PAD_A | PAD_RIGHT | R0],
    [PAD_A | PAD_UP | R0],
    [PAD_A | PAD_LEFT | PAD_UP | R0],
    [PAD_A | PAD_RIGHT | PAD_UP | R0],
    [PAD_A | PAD_DOWN | R0],
    [PAD_A | PAD_LEFT | PAD_DOWN | R0],
    [PAD_A | PAD_RIGHT | PAD_DOWN | R0],
    [PAD_A | R0],
    [PAD_UP | PAD_RIGHT | R0],
    [PAD_UP | PAD_LEFT | R0],
    [PAD_DOWN | PAD_RIGHT | R0],
    [PAD_DOWN | PAD_LEFT | R0],
    [PAD_RIGHT | R0, PAD_RIGHT | R1],
    [PAD_LEFT | R0],
    [PAD_RIGHT | R0],
    [PAD_UP | R0],
    [PAD_DOWN | R0],
    [PAD_SELECT | PAD_DOWN | R0],
    [PAD_DOWN | R0, PAD_SELECT | R1],
    [PAD_SELECT | R0, PAD_DOWN | R1],
    [PAD_SELECT | R0],
    [0 | R0]
]


def fast_16_hashes(moves):
    lsb = 0
    msb = 0
    hs = []

    for i, move in enumerate(moves):
        if i & 1:
            msb = msb ^ move
        else:
            lsb = lsb ^ move

        h = (msb << 8) | lsb
        hs.append(h)

    return hs


if __name__ == '__main__':
    hashes = {}
    for combo in moves_list:
        hash = fast_16_hashes(combo)[len(combo) - 1]

        if hash in hashes:
            hashes[hash]['count'] += 1
            hashes[hash]['for'].append(combo)
        else:
            hashes[hash] = {
                'count': 1,
                'for': [combo]
            }

print(hashes)
