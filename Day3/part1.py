print(sum(l[3*y%(len(l)-1)]=='#'for y,l in enumerate(open('input.txt').readlines())))
