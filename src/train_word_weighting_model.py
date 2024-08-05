import pandas as pd
import re
import string
import joblib
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.metrics import accuracy_score, precision_score, recall_score, confusion_matrix
from collections import defaultdict
from custom_word_weighting_algorithm import CustomWordWeightingAlgorithm

# Load the data from CSV files
def load_data():
    print("Loading data...")
    X_train = pd.read_csv(
        'data/X_train.csv')
    X_test = pd.read_csv(
        'data/X_test.csv')
    y_train = pd.read_csv(
        'data/y_train.csv')
    y_test = pd.read_csv(
        'data/y_test.csv')
    print("Data loaded.")

    print("Inspecting loaded data...")
    print(f"X_train shape: {X_train.shape}, y_train shape: {y_train.shape}")
    print(f"X_test shape: {X_test.shape}, y_test shape: {y_test.shape}")

    print("Handling missing values in loaded data...")
    X_train.dropna(inplace=True)
    X_test.dropna(inplace=True)
    y_train.dropna(inplace=True)
    y_test.dropna(inplace=True)
    print("Missing values handled.")

    print(f"X_train length after dropping NA: {len(X_train)}, y_train length after dropping NA: {len(y_train)}")
    print(f"X_test length after dropping NA: {len(X_test)}, y_test length after dropping NA: {len(y_test)}")

    return X_train, X_test, y_train, y_test

# Clean the text data
def clean_text(text):
    text = re.sub(r'http\S+', '', text)  # Remove URLs
    text = re.sub(r'<.*?>', '', text)  # Remove HTML tags
    text = text.translate(str.maketrans('', '', string.punctuation))  # Remove punctuation
    text = text.lower()  # Convert to lower case
    text = re.sub(r'\s+', ' ', text).strip()  # Remove extra white spaces
    return text

# Preprocess the data by cleaning the text
def preprocess_data(X):
    print("Preprocessing text data...")
    X['clean_text'] = X['text'].apply(clean_text)
    print("Text data preprocessed.")
    return X

# Align the indices of X and y data
def align_data(X, y):
    print("Aligning X and y indices...")
    common_indices = X.index.intersection(y.index)
    aligned_X = X.loc[common_indices].reset_index(drop=True)
    aligned_y = y.loc[common_indices].reset_index(drop=True)
    print(f"Aligned X length: {len(aligned_X)}, Aligned y length: {len(aligned_y)}")
    return aligned_X, aligned_y

# Train the model
def train_model(X_train, y_train):
    print("Vectorizing training data...")
    vectorizer = CountVectorizer(max_df=0.9, ngram_range=(1, 2))
    X_train_bow = vectorizer.fit_transform(X_train.squeeze())
    print("Training data vectorized.")

    print("Training custom word weighting algorithm...")
    model = CustomWordWeightingAlgorithm()
    model.fit(X_train.squeeze(), y_train.squeeze())
    print("Model trained.")
    return model, vectorizer

# Evaluate the model
def evaluate_model(model, vectorizer, X_test, y_test):
    print("Vectorizing test data...")
    X_test_bow = vectorizer.transform(X_test.squeeze())
    print("Test data vectorized.")

    print("Making predictions...")
    y_pred = model.predict(X_test.squeeze())
    print("Predictions made.")

    print("Evaluating model...")
    accuracy = accuracy_score(y_test, y_pred)
    precision = precision_score(y_test, y_pred, average='weighted')
    recall = recall_score(y_test, y_pred, average='weighted')
    cm = confusion_matrix(y_test, y_pred)
    print("Model evaluated.")

    return accuracy, precision, recall, cm

# Save the model and vectorizer to files
def save_model(model, vectorizer, model_path='model/simple_sentiment_model.pkl', vectorizer_path='model/simple_vectorizer.pkl'):
    joblib.dump(model, model_path)
    joblib.dump(vectorizer, vectorizer_path)
    print(f"Model saved to {model_path}")
    print(f"Vectorizer saved to {vectorizer_path}")

# Main script execution
if __name__ == "__main__":
    X_train, X_test, y_train, y_test = load_data()

    # Verify lengths before proceeding
    print("Checking lengths...")
    if len(X_train) != len(y_train):
        print(f"Length mismatch: X_train length: {len(X_train)}, y_train length: {len(y_train)}")
        print("Aligning training data...")
        X_train, y_train = align_data(X_train, y_train)

    if len(X_test) != len(y_test):
        print(f"Length mismatch: X_test length: {len(X_test)}, y_test length: {len(y_test)}")
        print("Aligning testing data...")
        X_test, y_test = align_data(X_test, y_test)

    # Train and evaluate the model if lengths match
    if len(X_train) == len(y_train) and len(X_test) == len(y_test):
        model, vectorizer = train_model(X_train, y_train)
        accuracy, precision, recall, cm = evaluate_model(model, vectorizer, X_test, y_test)

        print(f"Accuracy: {accuracy}")
        print(f"Precision: {precision}")
        print(f"Recall: {recall}")
        print(f"Confusion Matrix: \n{cm}")

        save_model(model, vectorizer)  # Save the model and vectorizer
    else:
        print(f"Length mismatch persists: X_train length: {len(X_train)}, y_train length: {len(y_train)}")
        print(f"X_test length: {len(X_test)}, y_test length: {len(y_test)}")
