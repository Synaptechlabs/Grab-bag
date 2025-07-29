import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation, PillowWriter

# Parameters
radius = 25
points = []

# Generate Gaussian integers within a circular bound
for a in range(-radius, radius + 1):
    for b in range(-radius, radius + 1):
        if a**2 + b**2 <= radius**2:
            points.append((a, b))

points = np.array(points)
num_points = len(points)

# Shuffle points
shuffled = points.copy()
np.random.seed(42)
np.random.shuffle(shuffled)

# Sort by modulus (distance) and angle
complex_points = shuffled[:, 0] + 1j * shuffled[:, 1]
modulus = np.abs(complex_points)
angles = np.angle(complex_points)

sorted_indices = np.lexsort((angles, modulus))
sorted_points = shuffled[sorted_indices]

# Set up plot
fig, ax = plt.subplots(figsize=(6, 6))
scat = ax.scatter(shuffled[:, 0], shuffled[:, 1],
                  c=modulus, cmap='plasma', s=8)
ax.set_xlim(-radius - 1, radius + 1)
ax.set_ylim(-radius - 1, radius + 1)
ax.set_aspect('equal')
ax.set_title("Gaussian Integer Sorting Animation")

# Animation function
def animate(i):
    t = i / 60  # normalize to [0, 1]
    interp = (1 - t) * shuffled + t * sorted_points
    new_mod = np.abs(interp[:, 0] + 1j * interp[:, 1])
    scat.set_offsets(interp)
    scat.set_array(new_mod)
    return scat,

# Create animation
ani = FuncAnimation(fig, animate, frames=61, interval=100, blit=True)

# Save as GIF
ani.save("gaussian_sorting.gif", writer=PillowWriter(fps=10))
print("Saved as gaussian_sorting.gif")
