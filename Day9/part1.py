print([n[k]for n in[[int(l)for l in open('input.txt')]]for k in range(25,len(n))if not any(n[i]+n[j]==n[k]for j in range(k-25,k)for i in range(k-25,j))][0])
