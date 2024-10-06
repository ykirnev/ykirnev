import numpy as np


def get_part_of_array(X: np.ndarray) -> np.ndarray:
    return X[::4, 120:500:5]
    pass


def sum_non_neg_diag(X: np.ndarray) -> int:
    diagonal = np.diag(X)
    positive_diagonal = diagonal[diagonal >= 0]
    if positive_diagonal.size > 0:
        return positive_diagonal.sum()
    return -1
    pass


def replace_values(X: np.ndarray) -> np.ndarray:
    M = np.mean(X, axis=0)
    result = np.where((X < 0.25 * M) | (X > 1.5 * M), -1, X)
    return result
    pass
