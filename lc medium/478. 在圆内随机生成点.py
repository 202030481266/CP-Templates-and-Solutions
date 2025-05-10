import numpy as np
import math # math.cos, math.sin or np.cos, np.sin

# Assuming List is from typing
from typing import List

class Solution:
    def __init__(self, radius: float, x_center: float, y_center: float):
        self.a = x_center
        self.b = y_center
        self.r = radius

    def randPoint_original_incorrect(self) -> List[float]:
        # Your original code for comparison
        angle = np.random.uniform(0, 2 * np.pi)
        # Incorrect: radius = random.uniform(0, self.r) # Assuming random was from import random
        radius = np.random.uniform(0, self.r) # Using numpy's uniform
        return [self.a + radius * math.cos(angle), self.b + radius * math.sin(angle)]

    def randPoint_rejection(self) -> List[float]:
        while True:
            # Generate a point within the bounding square
            px = np.random.uniform(self.a - self.r, self.a + self.r)
            py = np.random.uniform(self.b - self.r, self.b + self.r)
            
            # Check if the point is inside the circle
            # (px - self.a)^2 + (py - self.b)^2 <= self.r^2
            if (px - self.a)**2 + (py - self.b)**2 <= self.r**2:
                return [px, py]

    def randPointMath(self) -> List[float]:
        # Corrected method
        # Generate a random angle uniformly
        angle = np.random.uniform(0, 2 * np.pi)
        
        # Generate a random number for radius scaling, then take sqrt
        # This ensures that points are uniformly distributed by area
        # u ~ U(0, 1) => sqrt(u) gives the correct distribution for radius
        random_val_for_radius_squared = np.random.uniform(0, 1)
        radius = self.r * np.sqrt(random_val_for_radius_squared)
        
        # Convert polar to Cartesian coordinates and add center offset
        x = self.a + radius * np.cos(angle) # Using np.cos for consistency
        y = self.b + radius * np.sin(angle) # Using np.sin for consistency
        return [x, y]
    
    def randPoint(self) -> List[float]:
        return self.randPoint_rejection()