"""
Removes all rom files unsupported by KrzysIO Cart from a given directory.
"""
import argparse
import os

SUPPORTED_MAPPERS = [0, 1, 2, 3, 4, 7, 15, 71, 232]


def is_valid_krzysiocart_rom(f):
    try:
        header = f.read(16)

        if len(header) != 16:
            return False

        if header[0] != 0x4e and header[1] != 0x45 and header[2] != 0x53 and header[3] != 0x1a:
            return False

        mapper_lower_nimble = header[6] >> 4

        if len(list(filter(lambda x: x != 0, header[11:]))):
            mapper_higher_nimble = 0
        else:
            mapper_higher_nimble = header[7] & int('0b11110000', 2)

        mapper = mapper_higher_nimble | mapper_lower_nimble

        if mapper not in SUPPORTED_MAPPERS:
            return False

    except IOError as e:
        print(str(e))
        return False

    return True


def clean_up(directory):
    for dirpath, dirnames, filenames in os.walk(directory):
        for name in filenames:
            process_file(directory, dirpath, name)


def process_file(directory, dirpath, name):
    full_path = os.path.join(directory, dirpath, name)
    delete = False
    if full_path.endswith('.nes'):
        with open(full_path, "rb") as f:
            if not is_valid_krzysiocart_rom(f):
                delete = True

        if delete:
            print("{} is invalid rom - deleting.".format(full_path))
            os.unlink(full_path)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("path", help="path to a directory", type=str)
    args = parser.parse_args()

    clean_up(directory=args.path)