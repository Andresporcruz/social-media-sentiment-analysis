from collections import defaultdict

class CustomSimpleAlgorithm:
    def __init__(self):
        self.word_weights = defaultdict(self.default_value)
    
    def default_value(self):
        return [0, 0]
    
    def fit(self, X, y):
        for text, sentiment in zip(X, y):
            words = text.split()
            for word in words:
                if sentiment == 1:
                    self.word_weights[word][0] += 1  # Positive sentiment
                else:
                    self.word_weights[word][1] += 1  # Negative sentiment
    
    def predict(self, X):
        predictions = []
        for text in X:
            pos_score = 0
            neg_score = 0
            words = text.split()
            for word in words:
                if word in self.word_weights:
                    pos_score += self.word_weights[word][0]
                    neg_score += self.word_weights[word][1]
            if pos_score > neg_score:
                predictions.append(1)
            else:
                predictions.append(0)
        return predictions

