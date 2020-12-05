print([len(x) == 7 and 'cid' not in x or len(x) == 8 for x in map(lambda l : [x.split(':')[0] for x in l.split()], open('input.txt').read().split('\n\n'))].count(True))
