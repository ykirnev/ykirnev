from typing import List
from copy import deepcopy


def get_part_of_array(X: List[List[float]]) -> List[List[float]]:
    mas = []
    for i in range(0, len(X), 4):
        res = []
        for j in range(120, min(500, len(X[i])), 5):
            res.append(X[i][j])
        if res:
            mas.append(res)
    return mas


def sum_non_neg_diag(X: List[List[int]]) -> int:
    result = 0
    n = len(X)
    m = len(X[0])
    zero_flag = 0
    for i in range(min(m, n)):
        if X[i][i] >= 0:
            result += X[i][i]
            zero_flag = 1
    if result > 0 or zero_flag:
        return result
    return -1

def replace_values(X: List[List[float]]) -> List[List[float]]:
    result = [[0] * len(X[0]) for _ in range(len(X))]
    for j in range(len(X[0])):
        col = [X[i][j] for i in range(len(X))]
        M = sum(col) / len(col)
        for i in range(len(X)):
            if X[i][j] < 0.25 * M or X[i][j] > 1.5 * M:
                result[i][j] = -1
            else:
                result[i][j] = X[i][j]
    return result
    pass
