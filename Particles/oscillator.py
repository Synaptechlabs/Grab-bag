import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import random

# Define relational states and their display colors
RELATIONAL_STATES = ['Identical', 'Overlapping', 'Touching', 'Independent']
STATE_COLORS = {
    'Identical': 'green',
    'Overlapping': 'blue',
    'Touching': 'orange',
    'Independent': 'red'
}

# Particle class
class Particle:
    def __init__(self, id, position):
        self.id = id
        self.position = position

# Oscillator class (2 particles)
class Oscillator:
    def __init__(self, p1, p2):
        self.p1 = p1
        self.p2 = p2
        self.state_index = 0  # start in "Identical"

    def update_state(self):
        self.state_index = (self.state_index + 1) % len(RELATIONAL_STATES)

    def current_state(self):
        return RELATIONAL_STATES[self.state_index]

# Create 4 particles with random positions
particles = [
    Particle(i, np.array([random.uniform(-1, 1), random.uniform(-1, 1)]))
    for i in range(4)
]

# Create 2 oscillators (each with 2 particles)
oscillators = [
    Oscillator(particles[0], particles[1]),
    Oscillator(particles[2], particles[3])
]

# Setup plot
fig, ax = plt.subplots()
scat = ax.scatter([], [], s=200)

def init():
    ax.set_xlim(-2, 2)
    ax.set_ylim(-2, 2)
    ax.set_title("Relational Oscillator Simulation")
    return scat,

def animate(frame):
    positions = []
    colors = []

    # Update oscillator states
    for osc in oscillators:
        osc.update_state()
        color = STATE_COLORS[osc.current_state()]
        # Apply color to both particles in the oscillator
        colors.append(color)
        colors.append(color)
        positions.append(osc.p1.position)
        positions.append(osc.p2.position)

    scat.set_offsets(positions)
    scat.set_color(colors)
    return scat,

# Create animation
ani = animation.FuncAnimation(
    fig, animate, init_func=init, frames=200, interval=500, blit=True
)

plt.show()
