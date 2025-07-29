import numpy as np
import matplotlib.pyplot as plt

# Parameters
GRID_SIZE = 100
NUM_PARTICLES = 1000
MAX_STEPS = 200

# Initialize grid and local time counter
grid = np.zeros((GRID_SIZE, GRID_SIZE), dtype=int)
local_time = np.zeros((GRID_SIZE, GRID_SIZE), dtype=int)
positions = [(np.random.randint(0, GRID_SIZE), np.random.randint(0, GRID_SIZE)) for _ in range(NUM_PARTICLES)]
for x, y in positions:
    grid[y, x] += 1

# Function to compute a relational fingerprint
def compute_fingerprint(g):
    return tuple(g.flatten())

history = [compute_fingerprint(grid)]
step = 0
null_loops = 0

while step < MAX_STEPS:
    new_grid = np.zeros((GRID_SIZE, GRID_SIZE), dtype=int)
    new_local_time = np.copy(local_time)
    new_positions = []

    for (x, y) in positions:
        dx, dy = np.random.choice([-1, 0, 1]), np.random.choice([-1, 0, 1])
        nx = min(max(x + dx, 0), GRID_SIZE - 1)
        ny = min(max(y + dy, 0), GRID_SIZE - 1)
        new_grid[ny, nx] += 1
        new_positions.append((nx, ny))
        new_local_time[ny, nx] += 1  # Tentatively increment local time

    fingerprint = compute_fingerprint(new_grid)

    if fingerprint != history[-1]:
        step += 1
        positions = new_positions
        grid = new_grid
        local_time = new_local_time
        history.append(fingerprint)
        null_loops = 0
    else:
        null_loops += 1

# Plot local time map
plt.figure(figsize=(6, 6))
plt.imshow(local_time, cmap='viridis', origin='lower')
plt.title(f'Local Time Map After {step} Global Steps')
plt.colorbar(label='Local Time (ticks)')
plt.axis('off')
plt.tight_layout()
plt.show()
