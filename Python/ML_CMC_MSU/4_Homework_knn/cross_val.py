import numpy as np
import typing
from collections import defaultdict


def kfold_split(num_objects: int, num_folds: int) -> typing.List[typing.Tuple[np.ndarray, np.ndarray]]:
    indices = np.arange(num_objects)
    fold_size = num_objects // num_folds
    folds = []

    for i in range(num_folds):
        start = i * fold_size
        end = (i + 1) * fold_size if i != num_folds - 1 else num_objects
        folds.append(indices[start:end])

    result = []
    for i in range(num_folds):
        val_indices = folds[i]
        train_indices = np.concatenate([folds[j] for j in range(num_folds) if j != i])
        result.append((train_indices, val_indices))

    return result


def knn_cv_score(X: np.ndarray, y: np.ndarray, parameters: dict[str, list],
                 score_function: callable,
                 folds: list[tuple[np.ndarray, np.ndarray]],
                 knn_class: object) -> dict[str, float]:
    result = {}

    for normalizer, normalizer_name in parameters['normalizers']:
        for n_neighbors in parameters['n_neighbors']:
            for metric in parameters['metrics']:
                for weight in parameters['weights']:
                    scores = []
                    for train_indices, test_indices in folds:
                        X_train, X_test = X[train_indices], X[test_indices]
                        y_train, y_test = y[train_indices], y[test_indices]

                        if normalizer is not None:
                            normalizer.fit(X_train)
                            X_train = normalizer.transform(X_train)
                            X_test = normalizer.transform(X_test)

                        knn = knn_class(n_neighbors=n_neighbors, weights=weight, metric=metric)
                        knn.fit(X_train, y_train)
                        y_pred = knn.predict(X_test)
                        scores.append(score_function(y_test, y_pred))

                    result[(normalizer_name, n_neighbors, metric, weight)] = np.mean(scores)

    return result