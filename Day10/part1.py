print([d.count(1)*(d.count(3)+1)for d in[[a-b for x in[[0]+sorted([int(l)for l in open('input.txt')])]for a,b in zip(x[1:],x[:-1])]]][0])
