import pandas as pd
import re
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
from sklearn.model_selection import train_test_split

# Ensure NLTK resources are downloaded
import nltk

nltk.download('stopwords')
nltk.download('punkt')


# Function to load data from a CSV file
def load_data(filepath):
    data = pd.read_csv(filepath)
    data.columns = ['sentence', 'sentiment']
    return data


# Function to clean text data
def clean_text(text):
    text = re.sub(r"http\S+", "", text)  # Remove URLs
    text = re.sub(r"@\w+", "", text)  # Remove mentions
    text = re.sub(r"[^A-Za-z0-9]+", " ", text)  # Remove non-alphanumeric characters
    text = text.lower()  # Convert text to lowercase
    text = word_tokenize(text)  # Tokenize text
    text = [word for word in text if word not in stopwords.words('english')]  # Remove stopwords
    return " ".join(text)


# Function to preprocess data by cleaning text
def preprocess_data(data):
    data['clean_text'] = data['sentence'].apply(clean_text)
    return data


# Function to split data into training and testing sets
def split_data(data):
    X = data['clean_text']
    y = data['sentiment']
    print(f"X length: {len(X)}, y length: {len(y)}")  # Print lengths before splitting
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
    print(f"X_train length: {len(X_train)}, y_train length: {len(y_train)}")  # Print lengths after splitting
    print(f"X_test length: {len(X_test)}, y_test length: {len(y_test)}")
    return X_train, X_test, y_train, y_test


# Main script execution
if __name__ == "__main__":
    filepath = 'data/train_data.csv'

    # Load data
    print("Loading data...")
    data = load_data(filepath)
    print(f"Data loaded. Data shape: {data.shape}")

    # Inspect initial data
    print("Inspecting data...")
    print(data.head())
    print(data.info())
    print(data.isnull().sum())

    # Handle missing values
    print("Handling missing values...")
    data.dropna(subset=['sentence', 'sentiment'], inplace=True)
    print("Missing values handled.")

    # Inspect data after handling missing values
    print("Inspecting data after handling missing values...")
    print(data.head())
    print(data.info())
    print(data.isnull().sum())

    # Preprocess data
    print("Preprocessing data...")
    data = preprocess_data(data)
    print("Data preprocessed.")

    # Inspect data after preprocessing
    print("Inspecting data after preprocessing...")
    print(data.head())
    print(data.info())
    print(data.isnull().sum())

    # Split data into training and testing sets
    print("Splitting data...")
    X_train, X_test, y_train, y_test = split_data(data)
    print("Data split completed.")

    # Save split data to CSV files
    print("Saving data...")
    X_train.to_csv('data/X_train.csv', index=False)
    X_test.to_csv('data/X_test.csv', index=False)
    y_train.to_csv('data/y_train.csv', index=False)
    y_test.to_csv('data/y_test.csv', index=False)
    print("Data saved.")
