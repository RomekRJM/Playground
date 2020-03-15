cntr = 0

with open('hellomario.asm', 'r') as s:
	with open('hellomario.mem.txt', 'w') as d:
		for line in s.readlines():
			if line.startswith('.define'):
				_, name, addr = line.split()
				addr = addr.replace('$', '')
				d.write('{} {}\n'.format(addr, name))
				cntr += 1
			
		while cntr < 24:
			d.write('| |\n')
			cntr += 1
		