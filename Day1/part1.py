import itertools as i
print([x*y for x,y in i.product(map(int,open('input.txt').readlines()),repeat=2)if x+y==2020][0])
