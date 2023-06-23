import os
from dataclasses import dataclass

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

PUNCH = 130
KICK = 131
JUMP_KICK = 132
DRILL = 133
DASHING_PUNCH = 134
DASHING_KICK = 135
DUCKING_PUNCH = 136
PUNCH_OR_THROW = 137

MOVES_LIST_FILE = 'moves_list.txt'

moves_list = [
    [DRILL, PAD_DOWN | PAD_LEFT | R0, PAD_B | R1],
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


@dataclass
class Move:
    move_name: str
    hash_lsb: str
    hash_msb: str
    is_special: bool
    move_length: int


def fast_16_hashes(moves):
    lsb = 0
    msb = 0
    hs = []

    for i, move in enumerate(moves):
        if i & 1:
            msb = msb ^ move
        else:
            lsb = lsb ^ move

        hs.append(lsb)
        hs.append(msb)

    return hs


def compute_hashes_for_moves_list():
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


def read_moves():
    with open(MOVES_LIST_FILE, 'r') as f:
        moves_list_lines = f.readlines()

    move_hashes = []
    for line in moves_list_lines:
        parts = [x.strip() for x in line.split(',')]
        move_name = parts[0]
        move_type = parts[1] == 'SPECIAL_MOVE'
        moves = parts[2:]
        move_lenght = len(moves)

        input_states = [0] * len(moves)

        for i, sequence in enumerate(moves):
            keys = [x.strip() for x in sequence.split('|')]

            for key in keys:
                input_states[i] = input_states[i] | globals()[key]

        computed_hashes = fast_16_hashes(input_states)

        move_hashes.append(Move(move_name, computed_hashes[-2], computed_hashes[-1],
                                move_type, move_lenght))

    return move_hashes


def translate_move_hashes_to_c_array(move_hashes):
    count_moves = {}

    for move_hash in move_hashes:
        if move_hash.move_name in count_moves:
            count_moves[move_hash.move_name] += 1
        else:
            count_moves[move_hash.move_name] = 1

    c_code = ""

    for move_name, count in count_moves.items():
        control_byte = ""
        c_code += f"\n{move_name}, "
        for move_hash in move_hashes:
            if move_hash.move_name == move_name:
                if not control_byte:
                    control_byte = "SPECIAL_MOVE" if move_hash.is_special else "BASIC_MOVE"
                    control_byte += f" | {count}"
                    c_code += f"{control_byte}, "

                c_code += f"{move_hash.hash_lsb}, {move_hash.hash_msb}, "

    return c_code[:-2]


def write_hashes():
    path = 'hash_py.txt'

    if os.path.exists(path):
        os.remove(path)

    with open(path, 'w') as f:
        for tmp1 in range(255):
            for tmp2 in range(255):
                for tmp3 in range(2):
                    for tmp4 in range(2):
                        moves = [tmp1, tmp2, tmp3, tmp4]
                        hashes = [str(h) for h in fast_16_hashes(moves)]
                        hashes_s = ", ".join(hashes)
                        f.write(f"{tmp1}, {tmp2}, {tmp3}, {tmp4}: fast_16b_hash({hashes_s})\n")


if __name__ == '__main__':
    # compute_hashes_for_moves_list()
    # write_hashes()
    move_hashes_from_file = read_moves()
    move_hashes_as_c_code = translate_move_hashes_to_c_array(move_hashes_from_file)
    print(move_hashes_as_c_code)
