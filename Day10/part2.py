print([(p,p.append(sum((q if c-d<4 else 0)for d,q in zip(x,p))+(1if c<4else 0)))[0]for x in[sorted([int(l)for l in open('input.txt')])]for p in[[]]for c in x][0][-1])
