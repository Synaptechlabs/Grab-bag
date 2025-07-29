import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation, PillowWriter

# Parameters
GRID_SIZE = 1000
NUM_PARTICLES = 1000000
MAX_STEPS = 200

# Initialize grid, local time, and particle positions
grid = np.zeros((GRID_SIZE, GRID_SIZE), dtype=int)
local_time = np.zeros((GRID_SIZE, GRID_SIZE), dtype=int)
positions = [(np.random.randint(0, GRID_SIZE), np.random.randint(0, GRID_SIZE)) for _ in range(NUM_PARTICLES)]
for x, y in positions:
    grid[y, x] += 1

def compute_fingerprint(g):
    return tuple(g.flatten())

history = [compute_fingerprint(grid)]
step = 0
loop_counter = 0
frames = []
frame_labels = []

# Simulation loop for animation
while step < MAX_STEPS:
    loop_counter += 1
    new_grid = np.zeros((GRID_SIZE, GRID_SIZE), dtype=int)
    new_local_time = np.copy(local_time)
    new_positions = []

    for (x, y) in positions:
        dx, dy = np.random.choice([-1, 0, 1]), np.random.choice([-1, 0, 1])
        nx = min(max(x + dx, 0), GRID_SIZE - 1)
        ny = min(max(y + dy, 0), GRID_SIZE - 1)
        new_grid[ny, nx] += 1
        new_positions.append((nx, ny))
        new_local_time[ny, nx] += 1

    fingerprint = compute_fingerprint(new_grid)

    if fingerprint != history[-1]:
        step += 1
        positions = new_positions
        grid = new_grid
        local_time = new_local_time
        history.append(fingerprint)
        frames.append(np.copy(local_time))
        frame_labels.append(f"Step {step} / Loop {loop_counter}")

# Create animation
fig, ax = plt.subplots(figsize=(6, 6))
img = ax.imshow(frames[0], cmap='viridis', origin='lower')
text = ax.text(5, 5, frame_labels[0], color='white', fontsize=10, ha='left', va='bottom', backgroundcolor='black')

plt.title("Local Time Evolution")
plt.axis('off')

def update(i):
    img.set_data(frames[i])
    text.set_text(frame_labels[i])
    return [img, text]

ani = FuncAnimation(fig, update, frames=len(frames), interval=100, blit=True)

# Save animation
ani.save("local_time_evolution_labeled_loops.gif", writer=PillowWriter(fps=10))
print("Animation saved as 'local_time_evolution_labeled_loops.gif'")
