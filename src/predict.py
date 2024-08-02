import joblib

def load_model():
    model = joblib.load('model/sentiment_model.pkl')
    vectorizer = joblib.load('model/vectorizer.pkl')
    return model, vectorizer

def predict(texts, model, vectorizer):
    texts_tfidf = vectorizer.transform(texts)
    predictions = model.predict(texts_tfidf)
    return predictions

if __name__ == "__main__":
    model, vectorizer = load_model()
    texts = ["I love this product!", "This restaurant was horrible"]
    predictions = predict(texts, model, vectorizer)
    for text, prediction in zip(texts, predictions):
        print(f"Text: {text} -> Sentiment: {prediction}")
