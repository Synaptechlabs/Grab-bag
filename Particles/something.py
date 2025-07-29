import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation, PillowWriter

# Parameters
GRID_SIZE = 100
EMERGENCE_PROB = 0.0001  # Tiny chance per cell per tick
MAX_STEPS = 200

# Initialize grid and local time
grid = np.zeros((GRID_SIZE, GRID_SIZE), dtype=int)
local_time = np.zeros((GRID_SIZE, GRID_SIZE), dtype=int)

frames = []
frame_labels = []

for step in range(MAX_STEPS):
    emergence_mask = np.random.rand(GRID_SIZE, GRID_SIZE) < EMERGENCE_PROB
    new_particles = emergence_mask.astype(int)
    grid += new_particles
    grid = np.clip(grid, 0, 1)
    local_time += new_particles

    frames.append(np.copy(local_time))
    frame_labels.append(f"Step {step + 1}")

# Animate
fig, ax = plt.subplots(figsize=(6, 6))
img = ax.imshow(frames[0], cmap='plasma', origin='lower')
text = ax.text(5, 5, frame_labels[0], color='white', fontsize=10, ha='left', va='bottom', backgroundcolor='black')

plt.title("Emergence from Nothing")
plt.axis('off')

def update(i):
    img.set_data(frames[i])
    text.set_text(frame_labels[i])
    return [img, text]

ani = FuncAnimation(fig, update, frames=len(frames), interval=100, blit=True)
ani.save("emergence_from_nothing.gif", writer=PillowWriter(fps=10))
print("Saved as emergence_from_nothing.gif")
