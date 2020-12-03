from functools import reduce
print(reduce(lambda x,y:x*y,[sum(l[a*y//b%(len(l)-1)]=='#'for y,l in enumerate(open('input.txt').readlines())if y%b==0)for a,b in[(1,1),(3,1),(5,1),(7,1),(1,2)]]))
