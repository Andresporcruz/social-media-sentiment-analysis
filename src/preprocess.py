import pandas as pd
import re
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
from sklearn.model_selection import train_test_split

# Ensure NLTK resources are downloaded
import nltk
nltk.download('stopwords')
nltk.download('punkt')

def load_data(filepath):
    data = pd.read_csv(filepath, encoding='latin-1')
    data.columns = ['target', 'ids', 'date', 'flag', 'user', 'text']
    data = data[['text', 'target']]
    data['target'] = data['target'].apply(lambda x: 1 if x == 4 else (0 if x == 2 else -1))
    return data

def clean_text(text):
    text = re.sub(r"http\S+", "", text)
    text = re.sub(r"@\w+", "", text)
    text = re.sub(r"[^A-Za-z0-9]+", " ", text)
    text = text.lower()
    text = word_tokenize(text)
    text = [word for word in text if word not in stopwords.words('english')]
    return " ".join(text)

def preprocess_data(data):
    data['clean_text'] = data['text'].apply(clean_text)
    return data

def split_data(data):
    X = data['clean_text']
    y = data['target']
    return train_test_split(X, y, test_size=0.2, random_state=42)

if __name__ == "__main__":
    filepath = 'data/sentiment140.csv'  # Update with your dataset path
    data = load_data(filepath)
    data = preprocess_data(data)
    X_train, X_test, y_train, y_test = split_data(data)
    X_train.to_csv('data/X_train.csv', index=False)
    X_test.to_csv('data/X_test.csv', index=False)
    y_train.to_csv('data/y_train.csv', index=False)
    y_test.to_csv('data/y_test.csv', index=False)
