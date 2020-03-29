def get_variables(file_name):
    lines = []
    with open(file_name, 'r') as s:
        for line in s.readlines():
            if line.startswith('.define'):
                _, name, addr = line.split()
                addr = addr.replace('$', '')
                lines.append((addr, name))

    return lines


def save_to_map_file(file_name, variables):
    cntr = 0
    with open(file_name, 'w') as d:
        for v in variables:
            d.write('{} {}\n'.format(v[0], v[1]))
            cntr += 1

        while cntr < 24:
            d.write('| |\n')
            cntr += 1


if __name__ == '__main__':
    num_to_display = 24
    variables = get_variables('nesdemia.asm')
    save_to_map_file('nesdemia.mem.txt', variables[-num_to_display:])
