print(sum(len(set(l.replace('\n',''))) for l in open('input.txt').read().split('\n\n')))
