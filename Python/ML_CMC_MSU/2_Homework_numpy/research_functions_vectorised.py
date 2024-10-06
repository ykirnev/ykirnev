import numpy as np


def are_multisets_equal(x: np.ndarray, y: np.ndarray) -> bool:
    values_x, counts_x = np.unique(x, return_counts=True)
    values_y, counts_y = np.unique(y, return_counts=True)
    return np.array_equal(values_x, values_y) and np.array_equal(counts_x, counts_y)
    pass


def max_prod_mod_3(x: np.ndarray) -> int:
    if len(x) < 2:
        return -1
    tmp = x[:-1] * x[1:]
    mask = (x[:-1] % 3 == 0) | (x[1:] % 3 == 0)
    valid_products = tmp[mask]
    return int(valid_products.max()) if valid_products.size > 0 else -1
    pass

def convert_image(image: np.ndarray, weights: np.ndarray) -> np.ndarray:
    weighted_sum = np.tensordot(image, weights, axes=(2, 0))
    return weighted_sum

def rle_to_vector(rle: np.ndarray) -> np.ndarray:
    return np.repeat(rle[:, 0], rle[:, 1])

def rle_scalar(x: np.ndarray, y: np.ndarray) -> int:
    x = rle_to_vector(x)
    y = rle_to_vector(y)
    if x.size != y.size:
        return -1
    return int(np.dot(x, y))
def cosine_distance(X: np.ndarray, Y: np.ndarray) -> np.ndarray:
    X_norm = np.linalg.norm(X, axis=1, keepdims=True)
    Y_norm = np.linalg.norm(Y, axis=1, keepdims=True)
    X_norm[X_norm == 0] = 1
    Y_norm[Y_norm == 0] = 1
    X_normalized = X / X_norm
    Y_normalized = Y / Y_norm
    dot_products = np.dot(X_normalized, Y_normalized.T)
    cosine_distances = 1 - dot_products
    zero_vectors_X = np.all(X == 0, axis=1)
    zero_vectors_Y = np.all(Y == 0, axis=1)
    cosine_distances[zero_vectors_X, :] = 0
    cosine_distances[:, zero_vectors_Y] = 0
    cosine_distances = 1 - cosine_distances
    return cosine_distances
