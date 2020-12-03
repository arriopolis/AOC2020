import re
print(sum((s[int(l)-1]==c[0])!=(s[int(u)-1]==c[0])for l,u,c,s in map(lambda x:re.split(' |-',x),open('input.txt').readlines())))
