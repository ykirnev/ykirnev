from collections import Counter
from typing import List


def are_multisets_equal(x: List[int], y: List[int]) -> bool:
    def count_elements(vec: List[int]) -> dict:
        counts = {}
        for element in vec:
            if element in counts:
                counts[element] += 1
            else:
                counts[element] = 1
        return counts
    cnt1 = count_elements(x)
    cnt2 = count_elements(y)
    return cnt1 == cnt2
    pass


def max_prod_mod_3(x: List[int]) -> int:
    mx = -1
    for i in range(len(x) - 1):
        tmp = x[i] * x[i + 1]
        if x[i] % 3 == 0 or x[i + 1] % 3 == 0:
            if tmp > mx:
                mx = tmp

    return mx
    pass


def convert_image(image: List[List[List[float]]], weights: List[float]) -> List[List[float]]:
    height = len(image)
    width = len(image[0])
    result = [[0.0 for _ in range(width)] for _ in range(height)]
    for i in range(height):
        for j in range(width):
            weighted_sum = sum(image[i][j][k] * weights[k] for k in range(len(weights)))
            result[i][j] = weighted_sum
    return result
    pass


def rle_to_vector(rle: List[List[int]]) -> List[int]:
    vector = []
    for value, count in rle:
        vector.extend([value] * count)
    return vector


def rle_scalar(x: List[List[int]], y: List[List[int]]) -> int:
    x = rle_to_vector(x)
    y = rle_to_vector(y)
    if len(x) != len(y):
        return -1
    return (sum(x_i * y_i for x_i, y_i in zip(x, y)))


def norm(vector: List[float]) -> float:
    return sum(x ** 2 for x in vector)**0.5

def cosine_distance(X: List[List[float]], Y: List[List[float]]) -> List[List[float]]:
    n = len(X)
    m = len(Y)
    cosine_distances = [[0] * m for _ in range(n)]
    X_norm = [norm(x) if norm(x) != 0 else 1 for x in X]
    Y_norm = [norm(y) if norm(y) != 0 else 1 for y in Y]
    X_normalized = [[x[i] / X_norm[idx] for i in range(len(x))] for idx, x in enumerate(X)]
    Y_normalized = [[y[i] / Y_norm[idx] for i in range(len(y))] for idx, y in enumerate(Y)]
    for i in range(n):
        for j in range(m):
            dot_product = sum(X_normalized[i][k] * Y_normalized[j][k] for k in range(len(X_normalized[i])))
            cosine_distances[i][j] = 1 - dot_product
    for i in range(n):
        if all(x == 0 for x in X[i]):
            cosine_distances[i] = [0] * m

    for j in range(m):
        if all(y == 0 for y in Y[j]):
            for i in range(n):
                cosine_distances[i][j] = 0
    for i in range(n):
        for j in range(m):
            if cosine_distances[i][j] == 1.0:
                cosine_distances[i][j] = 0
            elif cosine_distances[i][j] == 0.0:
                cosine_distances[i][j] = 1
            else:
                cosine_distances[i][j] = 1 - cosine_distances[i][j]
    return cosine_distances
