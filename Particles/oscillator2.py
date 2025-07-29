import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import random
from itertools import combinations

# Grid size and number of particles
GRID_SIZE = 10
NUM_PARTICLES = 99

# Relational states and their associated display colors
RELATIONAL_STATES = ['Identical', 'Touching', 'Overlapping', 'Independent']
STATE_COLORS = {
    'Identical': 'green',
    'Touching': 'purple',
    'Overlapping': 'blue',
    'Independent': 'red'
}

# Particle class
class Particle:
    def __init__(self, id, position):
        self.id = id
        self.position = position
        self.color = 'gray'

    def move(self):
        # Random move in the grid: up, down, left, right, or stay
        dx, dy = random.choice([(0, 0), (0, 1), (0, -1), (1, 0), (-1, 0)])
        new_x = max(0, min(GRID_SIZE - 1, self.position[0] + dx))
        new_y = max(0, min(GRID_SIZE - 1, self.position[1] + dy))
        self.position = (new_x, new_y)

# Initialize particles at random positions
particles = []
occupied = set()
while len(particles) < NUM_PARTICLES:
    pos = (random.randint(0, GRID_SIZE - 1), random.randint(0, GRID_SIZE - 1))
    if pos not in occupied:
        occupied.add(pos)
        particles.append(Particle(len(particles), pos))

# Compute Manhattan distance between two particles
def manhattan_distance(p1, p2):
    return abs(p1.position[0] - p2.position[0]) + abs(p1.position[1] - p2.position[1])

# Determine relational state from distance
def relational_state(d):
    if d == 0:
        return 'Identical'
    elif d == 1:
        return 'Touching'
    elif d == 2:
        return 'Overlapping'
    else:
        return 'Independent'

# Update each particle's dominant relational state (color)
def update_relational_states():
    pair_states = {}
    for p1, p2 in combinations(particles, 2):
        d = manhattan_distance(p1, p2)
        state = relational_state(d)
        pair_states[(p1.id, p2.id)] = state

    # ✅ New logic: color = closest relational state to any other particle
    for p in particles:
        closest_state = 'Independent'
        min_dist = float('inf')
        for other in particles:
            if other.id != p.id:
                d = manhattan_distance(p, other)
                if d < min_dist:
                    min_dist = d
                    closest_state = relational_state(d)
        p.color = STATE_COLORS[closest_state]

# Plot setup
fig, ax = plt.subplots()
scat = ax.scatter([], [], s=300)

def init():
    ax.set_xlim(-0.5, GRID_SIZE - 0.5)
    ax.set_ylim(-0.5, GRID_SIZE - 0.5)
    ax.set_xticks(range(GRID_SIZE))
    ax.set_yticks(range(GRID_SIZE))
    ax.grid(True)
    ax.set_title("Game of Universe v0.1 — Emergent Oscillators")
    return scat,

# Animation update per frame
def animate(frame):
    for p in particles:
        p.move()
    update_relational_states()
    positions = np.array([[p.position[0], p.position[1]] for p in particles])
    colors = [p.color for p in particles]
    scat.set_offsets(positions)
    scat.set_color(colors)
    return scat,

# Run animation
ani = animation.FuncAnimation(
    fig, animate, init_func=init, frames=200, interval=500, blit=True
)

plt.show()
