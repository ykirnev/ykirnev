import numpy as np


class Preprocessor:

    def __init__(self):
        pass

    def fit(self, X, Y=None):
        pass

    def transform(self, X):
        pass

    def fit_transform(self, X, Y=None):
        pass


class MyOneHotEncoder(Preprocessor):

    def __init__(self, dtype=np.float64):
        super(Preprocessor).__init__()
        self.dtype = dtype

    def fit(self, X, Y=None):
        """
        param X: training objects, pandas-dataframe, shape [n_objects, n_features]
        param Y: unused
        """
        if not isinstance(X, np.ndarray):
            X = X.to_numpy()

        if X.ndim == 1:
            X = X.reshape(-1, 1)

        self.encoding = []
        for column in X.T:
            unique_vals = np.unique(column)
            mapping = {val: idx for idx, val in enumerate(sorted(unique_vals))}
            self.encoding.append(mapping)

    def transform(self, X):
        """
        param X: objects to transform, pandas-dataframe, shape [n_objects, n_features]
        returns: transformed objects, numpy-array, shape [n_objects, |f1| + |f2| + ...]
        """
        if not isinstance(X, np.ndarray):
            X = X.to_numpy()

        if X.ndim == 1:
            X = X.reshape(-1, 1)

        result = []
        for column, mapping in zip(X.T, self.encoding):
            encoded = np.zeros((len(column), len(mapping)), dtype=int)
            for i, value in enumerate(column):
                encoded[i, mapping[value]] = 1
            result.append(encoded)
        return np.hstack(result)

    def fit_transform(self, X, Y=None):
        self.fit(X)
        return self.transform(X)

    def get_params(self, deep=True):
        return {"dtype": self.dtype}


class SimpleCounterEncoder:

    def __init__(self, dtype=np.float64):
        self.dtype = dtype

    def fit(self, X, Y):
        """
        param X: training objects, pandas-dataframe, shape [n_objects, n_features]
        param Y: target for training objects, pandas-series, shape [n_objects,]
        """
        X = X.to_numpy() if not isinstance(X, np.ndarray) else X
        Y = Y.to_numpy() if not isinstance(Y, np.ndarray) else Y

        if X.ndim == 1:
            X = X.reshape(-1, 1)

        self.encoding = [{} for _ in range(X.shape[1])]

        for col_idx, column in enumerate(X.T):
            unique_values = np.unique(column)
            for val in unique_values:
                is_val = (column == val)
                selected_Y = Y[is_val]
                success_rate = selected_Y.mean() if len(selected_Y) > 0 else 0
                proportion = is_val.sum() / len(X)
                self.encoding[col_idx][val] = (success_rate, proportion)

    def transform(self, X, a=1e-5, b=1e-5):
        """
        param X: objects to transform, pandas-dataframe, shape [n_objects, n_features]
        param a: constant for counters, float
        param b: constant for counters, float
        returns: transformed objects, numpy-array, shape [n_objects, 3]
        """
        X = X.to_numpy() if not isinstance(X, np.ndarray) else X

        if X.ndim == 1:
            X = X.reshape(-1, 1)

        num_features = X.shape[1]
        transformed_data = np.empty((X.shape[0], num_features * 3))

        for col_idx, (column, encoder) in enumerate(zip(X.T, self.encoding)):
            encoded_values = np.array([
                encoder.get(val, (0, 0)) for val in column
            ])
            success_rates, proportions = encoded_values.T
            smoothed_values = (success_rates + a) / (proportions + b)
            transformed_data[:, col_idx * 3: (col_idx + 1) * 3] = np.vstack(
                [success_rates, proportions, smoothed_values]
            ).T

        return transformed_data

    def fit_transform(self, X, Y, a=1e-5, b=1e-5):
        self.fit(X, Y)
        return self.transform(X, a, b)

    def get_params(self, deep=True):
        return {"dtype": self.dtype}


def group_k_fold(size, n_splits=3, seed=1):
    idx = np.arange(size)
    np.random.seed(seed)
    idx = np.random.permutation(idx)
    n_ = size // n_splits
    for i in range(n_splits - 1):
        yield idx[i * n_: (i + 1) * n_], np.hstack((idx[:i * n_], idx[(i + 1) * n_:]))
    yield idx[(n_splits - 1) * n_:], idx[:(n_splits - 1) * n_]


class FoldCounters:

    def __init__(self, n_folds=3, dtype=np.float64):
        self.dtype = dtype
        self.n_folds = n_folds

    def fit(self, X, Y, seed=1):
        """
        param X: training objects, pandas-dataframe, shape [n_objects, n_features]
        param Y: target for training objects, pandas-series, shape [n_objects,]
        param seed: random seed, int
        """
        X = X.to_numpy() if not isinstance(X, np.ndarray) else X
        Y = Y.to_numpy() if not isinstance(Y, np.ndarray) else Y
        if X.ndim == 1:
            X = X.reshape(-1, 1)
        self.split = list(group_k_fold(len(X), self.n_folds, seed))
        self.index_to_fold = {idx: fold_idx for fold_idx, (test, _) in enumerate(self.split) for idx in test}
        self.encoding = []
        for _, train_indices in self.split:
            fold_encoding = [{} for _ in range(X.shape[1])]
            for feature_idx, column in enumerate(X[train_indices].T):
                unique_vals = np.unique(column)
                for val in unique_vals:
                    val_mask = (column == val)
                    corresponding_Y = Y[train_indices][val_mask]
                    mean_success = corresponding_Y.mean() if len(corresponding_Y) > 0 else 0
                    relative_freq = val_mask.sum() / len(train_indices)
                    fold_encoding[feature_idx][val] = (mean_success, relative_freq)
            self.encoding.append(fold_encoding)

    def transform(self, X, a=1e-5, b=1e-5):
        """
        param X: objects to transform, pandas-dataframe, shape [n_objects, n_features]
        param a: constant for counters, float
        param b: constant for counters, float
        returns: transformed objects, numpy-array, shape [n_objects, 3]
        """
        X = X.to_numpy() if not isinstance(X, np.ndarray) else X
        if X.ndim == 1:
            X = X.reshape(-1, 1)
        transformed_data = np.zeros((len(X), X.shape[1] * 3), dtype=self.dtype)
        for row_idx, row_features in enumerate(X):
            current_fold_encoder = self.encoding[self.index_to_fold[row_idx]]
            for feature_idx, feature_value in enumerate(row_features):
                encoded_value = current_fold_encoder[feature_idx].get(feature_value, (0, 0))
                mean_success, relative_freq = encoded_value
                smoothed_value = (mean_success + a) / (relative_freq + b)
                transformed_data[row_idx, feature_idx * 3: (feature_idx + 1) * 3] = [mean_success, relative_freq,
                                                                                     smoothed_value]

        return transformed_data

    def fit_transform(self, X, Y, a=1e-5, b=1e-5):
        self.fit(X, Y)
        return self.transform(X, a, b)


def weights(x, y):
    """
    param x: training set of one feature, numpy-array, shape [n_objects,]
    param y: target for training objects, numpy-array, shape [n_objects,]
    returns: optimal weights, numpy-array, shape [|x unique values|,]
    """
    X = MyOneHotEncoder().fit_transform(x)
    weights = []

    def calculate_weight(mask):
        return y[mask].sum() / mask.sum()

    for one_hot_vector in np.identity(X.shape[1], dtype=bool):
        mask = np.all(X == one_hot_vector, axis=1)
        weights.append(calculate_weight(mask))
    weights = np.array(weights)
    return weights
