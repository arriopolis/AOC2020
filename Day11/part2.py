print(
    [
        list(
            [
                g.update({
                    (i,j) : '#'if o=='L'and s==0 else'L'if o=='#'and s>=5 else o
                    for i,j in g for s,o in [(
                        sum(
                            1
                            for k,l in [(-1,-1),(-1,0),(-1,1),(0,-1),(0,1),(1,-1),(1,0),(1,1)]
                            for s in [list(filter(lambda x:x!='.',[g[(i+m*k,j+m*l)]for m in range(1,max(h,w))if 0<=i+m*k<=h and 0<=j+m*l<=w]))]
                            if s and s[0]=='#'
                        ),
                        g[(i,j)])]}
                    ),
                print("Iteration:", z),
                print('\n'.join(''.join(g[(i,j)] for j in range(w)) for i in range(h))),
                g
            ][-1].values()
        ).count('#')
        for z,g in enumerate([{(i,j) : c for i,l in enumerate(open('input.txt')) for j,c in enumerate(l[:-1])}]*100)
        for h,w in [max(g)]
    ][-1]
)
