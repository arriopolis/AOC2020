import re
print(sum(int(l)<=s.count(c[0])<=int(u)for l,u,c,s in map(lambda x:re.split(' |-',x),open('input.txt').readlines())))
