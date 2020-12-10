print(
    len(
        [
            (
                [
                    rev[w].add(v) if w in rev else rev.update([(w,set([v]))])
                    for v,es in {
                        l[0] + ' ' + l[1] : {b + ' ' + c : int(a) for a,b,c in zip(l[2::3],l[3::3],l[4::3])}
                        for l in map(
                            lambda l : l.replace('bags','').replace('bag','').replace('contain',' ').replace('no other','').replace('.','').replace(',','').replace('\n','').replace('  ',' ').replace('  ',' ').strip().split(),
                            open('input.txt')
                        )
                    }.items() for w,n in es.items()
                ], [
                    (
                        visited.update(to_visit),
                        to_visit.update(sum([list(rev[v]) for v in to_visit if v in rev],[])),
                        to_visit.difference_update(visited),
                        visited
                    )[-1] for visited,to_visit in [(set(),rev['shiny gold'].copy())]*len(rev)
                ][0]
            )[1] for rev in [{}]
        ][0]
    )
)
