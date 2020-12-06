from functools import reduce
print(sum(len(reduce(lambda x,y : x.intersection(y), [set(x) for x in l.split()])) for l in open('input.txt').read().split('\n\n')))
