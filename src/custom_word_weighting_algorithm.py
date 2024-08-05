from collections import defaultdict

class CustomWordWeightingAlgorithm:
    def __init__(self):
        self.word_weights = defaultdict(self.default_weight)
        self.alpha = 1.0  # Smoothing factor

    def default_weight(self):
        return [0, 0]

    # Fit the model on the training data
    def fit(self, X, y):
        positive_count = 0
        negative_count = 0

        for text, sentiment in zip(X, y):
            words = text.split()
            for word in words:
                if sentiment == 1:
                    self.word_weights[word][0] += 1  # Positive sentiment
                    positive_count += 1
                else:
                    self.word_weights[word][1] += 1  # Negative sentiment
                    negative_count += 1

        self.total_words = positive_count + negative_count
        self.positive_prob = positive_count / self.total_words
        self.negative_prob = negative_count / self.total_words

    # Predict sentiments for the given data
    def predict(self, X):
        predictions = []
        for text in X:
            pos_score = self.positive_prob
            neg_score = self.negative_prob
            words = text.split()
            for word in words:
                if word in self.word_weights:
                    pos_score *= (self.word_weights[word][0] + self.alpha) / (
                                self.total_words + self.alpha * len(self.word_weights))
                    neg_score *= (self.word_weights[word][1] + self.alpha) / (
                                self.total_words + self.alpha * len(self.word_weights))
                else:
                    pos_score *= self.alpha / (self.total_words + self.alpha * len(self.word_weights))
                    neg_score *= self.alpha / (self.total_words + self.alpha * len(self.word_weights))
            if pos_score > neg_score:
                predictions.append(1)
            else:
                predictions.append(0)
        return predictions
