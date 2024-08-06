import joblib
import argparse
import json
import re

# Function to load the pre-trained model and vectorizer
def load_model(model_to_load):
    if model_to_load == "nb": # Load model based on option user selected
        model = joblib.load('model/nb_sentiment_model.pkl')
        vectorizer = joblib.load('model/nb_vectorizer.pkl')
    else:
        model = joblib.load('model/simple_sentiment_model.pkl')
        vectorizer = joblib.load('model/simple_vectorizer.pkl')
    return model, vectorizer


# Function to predict sentiments for given texts using the loaded model and vectorizer
def predict(texts, model, vectorizer, model_loaded):
    if model_loaded == "nb": # Make prediction based on option user selected
        texts_tfidf = vectorizer.transform(texts)  # Transform texts to TF-IDF representation
        predictions = model.predict(texts_tfidf)  # Predict sentiments
    else:
        predictions = model.predict(texts) # Predict sentiments
    return predictions


# Main script execution
if __name__ == "__main__":
    # Argument parser for command line input
    parser = argparse.ArgumentParser()
    parser.add_argument('texts', nargs='+')  # Accept multiple text inputs
    args = parser.parse_args()
    phrase = ' '.join(args.texts[1:])  # Combine all input texts into a single phrase
    phrase = re.sub(r"[^A-Za-z0-9]+", " ", phrase)
    model_requested = args.texts[0]

    # Load the model and vectorizer
    model, vectorizer = load_model(model_requested) # Use first input to determine model to run

    # Predict the sentiment of the input phrase
    predictions = predict([phrase], model, vectorizer, model_requested)

    # Print the input text and its predicted sentiment
    for text, prediction in zip([phrase], predictions):
        print(f"Text: {text} -> Sentiment: {prediction}")

    # Convert prediction to a list and print as JSON
    if model_requested == "nb":
        sentiment_scores = predictions.astype(int).tolist()
        print(json.dumps(sentiment_scores[0]))
    else:
        print(json.dumps(predictions[0]))
