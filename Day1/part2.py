import itertools as i
print([x*y*z for x,y,z in i.product(map(int,open('input.txt').readlines()),repeat=3)if x+y+z==2020][0])
