print(
    sum(
        [
            (
                r.update({y : (r[y] if y in r else 0) + r[x]*b for y,b in g[x].items()}) if x in r else None,
                r
            )
            for o,g in [
                [
                    [
                        (
                            o.extend(l),
                            [h[y].pop(x,None) for y in h for x in l],
                            [h.pop(x) for x in l]
                        )
                        for l in [[x for x in h if len(h[x]) == 0]]
                    ] + [(o,g)]
                    for g in [
                        {
                            l[0] + ' ' + l[1] : {b + ' ' + c : int(a) for a,b,c in zip(l[2::3],l[3::3],l[4::3])}
                            for l in map(
                                lambda l : l.replace('bags','').replace('bag','').replace('contain',' ').replace('no other','').replace('.','').replace(',','').replace('\n','').replace('  ',' ').replace('  ',' ').strip().split(),
                                open('input.txt')
                            )
                        }
                    ] for h in [{k : v.copy() for k,v in g.items()}] for o in [[]]*len(g)
                ][0][-1]
            ] for r in [{'shiny gold' : 1}] for x in reversed(o)
        ][0][-1].values()
    ) - 1
)
