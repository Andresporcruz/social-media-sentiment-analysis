import numpy as np

# Custom implementation of Naive Bayes classifier
class CustomNaiveBayes:
    def __init__(self, alpha=1.0):
        # Initialize the Naive Bayes classifier with smoothing parameter alpha
        self.alpha = alpha
        self.class_log_prior_ = None  # Log prior probabilities of classes
        self.feature_log_prob_ = None  # Log probabilities of features given classes

    def fit(self, X, y):
        # Fit the Naive Bayes classifier according to X, y
        count_sample = X.shape[0]  # Number of samples
        self.classes_ = np.unique(y)  # Unique classes
        count_class_samples = np.array([np.sum(y == c) for c in self.classes_])  # Count samples for each class
        self.class_log_prior_ = np.log(count_class_samples / count_sample)  # Log prior probabilities of classes

        self.feature_log_prob_ = np.zeros((len(self.classes_), X.shape[1]))  # Initialize log probabilities of features
        for i, c in enumerate(self.classes_):
            X_c = X[y == c]  # Samples belonging to class c
            smoothed_count = X_c.sum(axis=0) + self.alpha  # Smoothed feature counts
            smoothed_feature_count = smoothed_count / smoothed_count.sum()  # Normalized feature counts
            self.feature_log_prob_[i, :] = np.log(smoothed_feature_count)  # Log probabilities of features given class

    def predict(self, X):
        # Perform classification on an array of test vectors X
        jll = self._joint_log_likelihood(X)  # Calculate joint log likelihood
        return self.classes_[np.argmax(jll, axis=1)]  # Predict class with highest joint log likelihood

    def _joint_log_likelihood(self, X):
        # Calculate the joint log likelihood of X
        return (X @ self.feature_log_prob_.T) + self.class_log_prior_  # Compute joint log likelihood

    def score(self, X, y):
        # Return the mean accuracy on the given test data and labels
        return np.mean(self.predict(X) == y)  # Calculate accuracy
