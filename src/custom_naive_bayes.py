import numpy as np


class CustomNaiveBayes:
    def __init__(self, alpha=1.0):
        self.alpha = alpha
        self.class_log_prior_ = None
        self.feature_log_prob_ = None

    def fit(self, X, y):
        count_sample = X.shape[0]
        self.classes_ = np.unique(y)
        count_class_samples = np.array([np.sum(y == c) for c in self.classes_])
        self.class_log_prior_ = np.log(count_class_samples / count_sample)

        self.feature_log_prob_ = np.zeros((len(self.classes_), X.shape[1]))
        for i, c in enumerate(self.classes_):
            X_c = X[y == c]
            smoothed_count = X_c.sum(axis=0) + self.alpha
            smoothed_feature_count = smoothed_count / smoothed_count.sum()
            self.feature_log_prob_[i, :] = np.log(smoothed_feature_count)

    def predict(self, X):
        jll = self._joint_log_likelihood(X)
        return self.classes_[np.argmax(jll, axis=1)]

    def _joint_log_likelihood(self, X):
        return (X @ self.feature_log_prob_.T) + self.class_log_prior_

    def score(self, X, y):
        return np.mean(self.predict(X) == y)
