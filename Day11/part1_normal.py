import itertools as it

grid = []
for line in open('input.txt'):
    grid.append(list(line.strip()))

h,w = len(grid),len(grid[0])
changed = True
while changed:
    changed = False
    new_grid = [['.']*w for _ in range(h)]
    for y,x in it.product(range(h),range(w)):
        ctr = 0
        if grid[y][x] == '.': continue
        for dy,dx in it.product(range(-1,2),repeat=2):
            if dy == dx == 0: continue
            if not 0 <= y+dy < h: continue
            if not 0 <= x+dx < w: continue
            if grid[y+dy][x+dx] == '#': ctr += 1
        if grid[y][x] == '#' and ctr >= 4:
            changed = True
            new_grid[y][x] = 'L'
        elif grid[y][x] == 'L' and ctr == 0:
            changed = True
            new_grid[y][x] = '#'
        else:
            new_grid[y][x] = grid[y][x]
    grid = new_grid
    print('\n'.join(''.join(r) for r in grid))
    print()
print("Number of occupied seats:", sum(x.count('#') for x in grid))
