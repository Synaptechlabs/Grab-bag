import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation, PillowWriter

# Parameters
GRID_SIZE = 100
INITIAL_PARTICLES = 1000
EMERGENCE_PROB = 0.00001  # Chance for new particles to appear per cell per loop
MAX_STEPS = 200

# Initialize grid, local time, and initial particle positions
grid = np.zeros((GRID_SIZE, GRID_SIZE), dtype=int)
local_time = np.zeros((GRID_SIZE, GRID_SIZE), dtype=int)
positions = [(np.random.randint(0, GRID_SIZE), np.random.randint(0, GRID_SIZE)) for _ in range(INITIAL_PARTICLES)]
for x, y in positions:
    grid[y, x] += 1

def compute_fingerprint(g):
    return tuple(g.flatten())

history = [compute_fingerprint(grid)]
step = 0
loop_counter = 0
frames = []
frame_labels = []

while step < MAX_STEPS:
    loop_counter += 1
    new_grid = np.zeros((GRID_SIZE, GRID_SIZE), dtype=int)
    new_local_time = np.copy(local_time)
    new_positions = []

    # Move existing particles
    for (x, y) in positions:
        dx, dy = np.random.choice([-1, 0, 1]), np.random.choice([-1, 0, 1])
        nx = min(max(x + dx, 0), GRID_SIZE - 1)
        ny = min(max(y + dy, 0), GRID_SIZE - 1)
        new_grid[ny, nx] += 1
        new_positions.append((nx, ny))
        new_local_time[ny, nx] += 1

    # Add new spontaneous particles
    emergence_mask = np.random.rand(GRID_SIZE, GRID_SIZE) < EMERGENCE_PROB
    new_particle_coords = np.argwhere(emergence_mask)
    for y, x in new_particle_coords:
        new_grid[y, x] += 1
        new_positions.append((x, y))
        new_local_time[y, x] += 1

    fingerprint = compute_fingerprint(new_grid)

    if fingerprint != history[-1]:
        step += 1
        positions = new_positions
        grid = new_grid
        local_time = new_local_time
        history.append(fingerprint)
        frames.append(np.copy(local_time))
        frame_labels.append(f"Step {step} / Loop {loop_counter} / Particles {len(new_positions)}")

# Create and save animation
fig, ax = plt.subplots(figsize=(6, 6))
img = ax.imshow(frames[0], cmap='viridis', origin='lower')
text = ax.text(5, 5, frame_labels[0], color='white', fontsize=10, backgroundcolor='black')

plt.title("Emergent Particle Universe")
plt.axis('off')

def update(i):
    img.set_data(frames[i])
    text.set_text(frame_labels[i])
    return [img, text]

ani = FuncAnimation(fig, update, frames=len(frames), interval=100, blit=True)
ani.save("emergent_particle_universe.gif", writer=PillowWriter(fps=10))
print("Animation saved as 'emergent_particle_universe.gif'")
