"""
Game of Universe: Emergent Local Time Simulator
==============================================

Description:
------------
This simulation models a simplified emergent universe on a 2D grid where 
particles move randomly and new particles may spontaneously appear over time. 
Each grid cell tracks its own "local time" — a counter that increases every 
time a particle visits or appears at that cell.

The system is governed by fully local rules — there is no absolute clock or 
external timekeeper. Instead, time is defined relationally, based on particle 
interactions with space. The result is a dynamic heatmap showing how time 
emerges non-uniformly across space.

Core Concepts:
--------------
- Particles are initialized randomly on a 2D grid.
- Each particle moves randomly in 2D each time step.
- With a small probability, new particles spontaneously appear on any cell.
- Each time a particle lands in a cell, that cell's `local_time` counter increments.
- No global changes are forced — all structure arises emergently.

Outputs:
--------
1. A **live animation** of the 2D "local time map" as it evolves over 
   200 global steps.
2. A **final static heatmap** showing the total accumulated local time 
   per cell after the full simulation.
3. Colors indicate relative passage of time in different regions of space:
   - Blue = untouched or low activity
   - Green/Yellow = highly active, frequently visited regions

Why It Matters:
---------------
This model demonstrates how structured temporal behavior — and even 
cosmological-like textures — can arise from minimal assumptions:
- No predefined spacetime
- No external clock
- No imposed laws of physics beyond motion and emergence

It serves as an abstract "Game of Universe," with potential to resemble:
- Early universe structure (CMB-like textures)
- Time as a local phenomenon
- Spontaneous emergence of complexity from simple stochastic rules

Author: Scott Douglass
Date: 2025
"""


import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# Parameters
GRID_SIZE = 1000
INITIAL_PARTICLES = 10
EMERGENCE_PROB = 0.0005
MAX_STEPS = 2000000

# Initialize
grid = np.zeros((GRID_SIZE, GRID_SIZE), dtype=int)
local_time = np.zeros((GRID_SIZE, GRID_SIZE), dtype=int)
positions = [(np.random.randint(0, GRID_SIZE), np.random.randint(0, GRID_SIZE)) for _ in range(INITIAL_PARTICLES)]
for x, y in positions:
    grid[y, x] += 1

# Setup animation
fig, ax = plt.subplots(figsize=(6, 6))
#img = ax.imshow(local_time, cmap='plasma', origin='lower', vmin=0, vmax=5)
img = ax.imshow(local_time, cmap='viridis', origin='lower')

text = ax.text(5, 5, "", color='white', fontsize=10, backgroundcolor='black')
plt.title("Local Time Map (Emergent Universe)")
plt.axis('off')

def update(frame_num):
    global grid, local_time, positions
    new_grid = np.zeros((GRID_SIZE, GRID_SIZE), dtype=int)
    new_local_time = np.copy(local_time)
    new_positions = []

    # Move particles
    for (x, y) in positions:
        dx, dy = np.random.choice([-1, 0, 1]), np.random.choice([-1, 0, 1])
        nx = min(max(x + dx, 0), GRID_SIZE - 1)
        ny = min(max(y + dy, 0), GRID_SIZE - 1)
        new_grid[ny, nx] += 1
        new_positions.append((nx, ny))
        new_local_time[ny, nx] += 1

    # New spontaneous particles
    emergence_mask = np.random.rand(GRID_SIZE, GRID_SIZE) < EMERGENCE_PROB
    new_particle_coords = np.argwhere(emergence_mask)
    for y, x in new_particle_coords:
        new_grid[y, x] += 1
        new_positions.append((x, y))
        new_local_time[y, x] += 1

    positions = new_positions
    grid = new_grid
    local_time = new_local_time

    img.set_data(local_time)
    text.set_text(f"Global Step: {frame_num + 1}")
    return img, text

# Run animation
ani = FuncAnimation(fig, update, frames=MAX_STEPS, interval=100, blit=True)
plt.show()

# Save final frame
plt.figure(figsize=(8, 8))
plt.title("Local Time Map After 2000 Global Steps")
cmap = plt.imshow(local_time, cmap='viridis', origin='lower')
cbar = plt.colorbar(cmap)
cbar.set_label("Local Time (ticks)")
plt.axis('off')
plt.tight_layout()
plt.savefig("local_time_map_200_steps.png", dpi=150)
plt.show()
