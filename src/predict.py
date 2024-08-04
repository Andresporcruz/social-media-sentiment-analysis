import joblib
import argparse
import json

def load_model():
    model = joblib.load('C:/Users/readt/source/repos/social-media-sentiment-analysis/model/sentiment_model.pkl')
    vectorizer = joblib.load('C:/Users/readt/source/repos/social-media-sentiment-analysis/model/vectorizer.pkl')
    return model, vectorizer

def predict(texts, model, vectorizer):
    texts_tfidf = vectorizer.transform(texts)
    predictions = model.predict(texts_tfidf)
    return predictions

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        'texts',
        nargs='+'
    )
    args = parser.parse_args()
    phrase = ' '.join(args.texts)

    model, vectorizer = load_model()
    #texts = ["I love this product!", "This restaurant was horrible", "I like tacos", "not", "I don't like tacos", "tacos", "I do not hate tacos"]
    predictions = predict([phrase], model, vectorizer)
    for text, prediction in zip([phrase], predictions):
        print(f"Text: {text} -> Sentiment: {prediction}")

    sentiment_scores = predictions.astype(int).tolist()

    print(json.dumps(sentiment_scores[0]))
