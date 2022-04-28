import matplotlib.pyplot as plt
import numpy as np

if __name__ == '__main__':
    x = []
    y = []

    hull_x = []
    hull_y = []

    with open("points.txt", "r") as points_file:
        for line in points_file:
            point = line.split(" ")
            x.append(int(point[0]))
            y.append(int(point[1]))

    with open("hull.txt", "r") as hull_file:
        for line in hull_file:
            point = line.split(" ")
            hull_x.append(int(point[0]))
            hull_y.append(int(point[1]))

    plt.scatter(x, y, c='blue', s=2)
    plt.scatter(hull_x, hull_y, c='red', s=2)
    plt.show()
