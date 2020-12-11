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
            newy,newx = y+dy,x+dx
            while 0 <= newy < h and 0 <= newx < w:
                if grid[newy][newx] == 'L': break
                elif grid[newy][newx] == '#':
                    ctr += 1
                    break
                newy += dy
                newx += dx
        if grid[y][x] == '#' and ctr >= 5:
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
