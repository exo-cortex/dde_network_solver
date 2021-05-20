#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np

file1 = np.loadtxt("output1.txt")

fig, ax = plt.subplots(figsize=(10,10), dpi=176/2)
# ax.plot(file1[:,0], file1[:,1], linewidth=0.5, c=(0,0,0,1))
# ax.plot(file1[:,0], file1[:,2], linewidth=0.5, c=(1,0,0,1))
ax.plot(file1[:,1], file1[:,2], linewidth=0.25, c=(0,0,0,1))
plt.show()