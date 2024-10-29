import numpy as np
import typing


class MinMaxScaler:
    def fit(self, data: np.ndarray) -> None:
        self.min_ = np.min(data, axis=0)
        self.max_ = np.max(data, axis=0)

    def transform(self, data: np.ndarray) -> np.ndarray:
        range_ = self.max_ - self.min_
        range_[range_ == 0] = 1
        return (data - self.min_) / range_


class StandardScaler:
    def fit(self, data: np.ndarray) -> None:
        self.mean_ = np.mean(data, axis=0)
        self.std_ = np.std(data, axis=0)

    def transform(self, data: np.ndarray) -> np.ndarray:
        std_ = self.std_.copy()
        std_[std_ == 0] = 1
        return (data - self.mean_) / std_