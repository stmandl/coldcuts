# This problem was asked by Google.
# Given a set of points (x, y) on a 2D cartesian plane, find the two closest points. For example, given the points

Q = [(1, 1), (-1, -1), (3, 4), (6, 1), (-1, -6), (-4, -3)]

# return
S = [(-1, -1), (1, 1)]


from math import sqrt

def dist(p1, p2):
    return sqrt((p1[0]-p2[0]) ** 2 + (p1[1]-p2[1]) ** 2)

def closest(points):
    min_dist = None
    best = None
    for p1,p2 in zip(points, points[1:]):
        if min_dist is None or dist(p1,p2) < min_dist:
            best = [p1,p2]
            min_dist = dist(p1,p2)
    return best

print(closest(Q))
