lookup_table = [212, 78, 136, 183, 192, 158, 100, 101, 20, 141, 111, 102, 138, 169, 47, 247, 149, 195, 157, 189, 3, 106,
                250, 75, 135, 146, 32, 211, 167, 180, 29, 217, 41, 121, 114, 230, 199, 134, 127, 16, 241, 197, 63, 220,
                128, 113, 8, 105, 10, 228, 55, 168, 28, 99, 71, 76, 125, 239, 126, 205, 89, 226, 50, 13, 227, 110, 144,
                243, 186, 133, 30, 132, 170, 85, 86, 148, 152, 69, 18, 236, 81, 196, 2, 140, 165, 34, 90, 98, 201, 255,
                26, 191, 190, 221, 174, 59, 67, 234, 80, 123, 14, 229, 25, 171, 248, 35, 70, 56, 62, 49, 249, 218, 252,
                68, 173, 117, 193, 203, 92, 91, 159, 7, 187, 66, 185, 206, 176, 46, 245, 115, 194, 181, 208, 223, 104,
                60, 53, 107, 33, 42, 31, 23, 39, 19, 240, 242, 109, 184, 143, 1, 58, 37, 96, 0, 207, 4, 6, 87, 200, 213,
                188, 15, 65, 120, 11, 244, 45, 119, 172, 118, 150, 38, 43, 103, 5, 164, 137, 204, 163, 139, 82, 162,
                161, 88, 130, 51, 12, 74, 160, 44, 93, 129, 232, 253, 155, 209, 147, 116, 210, 95, 27, 154, 40, 214,
                156, 166, 222, 202, 97, 215, 131, 94, 21, 61, 64, 84, 124, 108, 9, 233, 57, 112, 142, 178, 52, 216, 225,
                79, 83, 198, 145, 219, 175, 179, 24, 235, 77, 73, 122, 177, 251, 224, 54, 36, 72, 17, 22, 246, 254, 48,
                153, 238, 231, 237, 151, 182]

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
]


def double_pearson_hash(moves):
    t = 0
    h = 0
    for move in moves:
        index = t ^ move
        t = lookup_table[index]

        if t & 1:
            h = h ^ (t << 8)
        else:
            h = h ^ t

    return h


if __name__ == '__main__':
    hashes = {}
    for combo in moves_list:
        hash = double_pearson_hash(combo)

        if hash in hashes:
            hashes[hash]['count'] += 1
            hashes[hash]['for'].append(combo)
        else:
            hashes[hash] = {
                'count': 1,
                'for': [combo]
            }

print(hashes)
