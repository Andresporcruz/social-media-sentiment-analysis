import joblib
import argparse
import json


# Function to load the pre-trained model and vectorizer
def load_model():
    model = joblib.load('model/sentiment_model.pkl')
    vectorizer = joblib.load('model/vectorizer.pkl')
    return model, vectorizer


# Function to predict sentiments for given texts using the loaded model and vectorizer
def predict(texts, model, vectorizer):
    texts_tfidf = vectorizer.transform(texts)  # Transform texts to TF-IDF representation
    predictions = model.predict(texts_tfidf)  # Predict sentiments
    return predictions


# Main script execution
if __name__ == "__main__":
    # Argument parser for command line input
    parser = argparse.ArgumentParser()
    parser.add_argument('texts', nargs='+')  # Accept multiple text inputs
    args = parser.parse_args()
    phrase = ' '.join(args.texts)  # Combine all input texts into a single phrase

    # Load the model and vectorizer
    model, vectorizer = load_model()

    # Predict the sentiment of the input phrase
    predictions = predict([phrase], model, vectorizer)

    # Print the input text and its predicted sentiment
    for text, prediction in zip([phrase], predictions):
        print(f"Text: {text} -> Sentiment: {prediction}")

    # Convert prediction to a list and print as JSON
    sentiment_scores = predictions.astype(int).tolist()
    print(json.dumps(sentiment_scores[0]))
