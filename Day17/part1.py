import numpy as np
import matplotlib.pyplot as plt
import itertools as it
from mpl_toolkits.mplot3d import Axes3D

grid = set()
with open('test.txt') as f:
    for i,line in enumerate(f):
        for j,c in enumerate(line.strip()):
            if c == '#': grid.add((0,i,j))
mins = [0,0,0]
maxs = [0,i,j]

grids = [grid]
for i in range(20):
    print("Generating data for frame:", i+1, end = '\r')
    new_grid = set()
    new_mins = [float("inf")]*len(mins)
    new_maxs = [float("-inf")]*len(maxs)
    for x in it.product(*(range(m-1,n+2) for m,n in zip(mins,maxs))):
        ctr = 0
        for dx in it.product(range(-1,2), repeat = len(x)):
            if all(d == 0 for d in dx): continue
            y = tuple([i+di for i,di in zip(x,dx)])
            if y in grid: ctr += 1
        if ctr == 3 or (ctr == 2 and x in grid):
            new_grid.add(x)
            new_mins = [min(a,b) for a,b in zip(new_mins,x)]
            new_maxs = [max(a,b) for a,b in zip(new_maxs,x)]
    grid = new_grid
    mins = new_mins
    maxs = new_maxs
    grids.append(grid)
print()

fig = plt.figure()
fig.subplots_adjust(top = 1, bottom = 0, right = 1, left = 0, hspace = 0, wspace = 0)
ax = fig.add_subplot(111, projection = '3d')
for i,grid in enumerate(grids):
    print("Generating frame:", i, end = '\r')
    ax.clear()
    ax.axis('off')
    for z,x,y in grid:
        ax.plot_surface(*np.meshgrid([x,x+1],[y,y+1]), np.array([[z]*2]*2), color = 'b')
        ax.plot_surface(*np.meshgrid([x,x+1],[y,y+1]), np.array([[z+1]*2]*2), color = 'b')
        ax.plot_surface(np.array([[x]*2]*2), *np.meshgrid([y,y+1],[z,z+1]), color = 'b')
        ax.plot_surface(np.array([[x+1]*2]*2), *np.meshgrid([y,y+1],[z,z+1]), color = 'b')
        xs,zs = np.meshgrid([x,x+1],[z,z+1])
        ax.plot_surface(xs, np.array([[y]*2]*2), zs, color = 'b')
        ax.plot_surface(xs, np.array([[y+1]*2]*2), zs, color = 'b')
    ax.set_zlim((.6*mins[0],.6*maxs[0]))
    ax.set_xlim((.55*mins[1],.65*maxs[1]))
    ax.set_ylim((.6*mins[2],.6*maxs[2]))
    fig.savefig('frames/frame{}.png'.format(i))
    plt.pause(.1)
print()
plt.show()
