import pandas as pd
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.svm import SVC
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, precision_score, recall_score, confusion_matrix
from sklearn.model_selection import GridSearchCV
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from imblearn.pipeline import Pipeline as ImbPipeline
from imblearn.over_sampling import SMOTE

def load_data(subset_size=0.01):  # Default subset size is 1%
    print("Loading data...")
    X_train = pd.read_csv('/Users/andresportillo/Documents/UF Summer 2024/social-media-sentiment-analysis/data/X_train.csv')
    X_test = pd.read_csv('/Users/andresportillo/Documents/UF Summer 2024/social-media-sentiment-analysis/data/X_test.csv')
    y_train = pd.read_csv('/Users/andresportillo/Documents/UF Summer 2024/social-media-sentiment-analysis/data/y_train.csv')
    y_test = pd.read_csv('/Users/andresportillo/Documents/UF Summer 2024/social-media-sentiment-analysis/data/y_test.csv')
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

    print(f"Sampling {subset_size*100}% of the data for a subset.")
    X_train_sample = X_train.sample(frac=subset_size, random_state=42)
    y_train_sample = y_train.loc[X_train_sample.index]
    X_test_sample = X_test.sample(frac=subset_size, random_state=42)
    y_test_sample = y_test.loc[X_test_sample.index]

    return X_train_sample.squeeze(), X_test_sample.squeeze(), y_train_sample.squeeze(), y_test_sample.squeeze()

def align_data(X, y):
    print("Aligning X and y indices...")
    common_indices = X.index.intersection(y.index)
    aligned_X = X.loc[common_indices].reset_index(drop=True)
    aligned_y = y.loc[common_indices].reset_index(drop=True)
    print(f"Aligned X length: {len(aligned_X)}, Aligned y length: {len(aligned_y)}")
    return aligned_X, aligned_y

def train_model(X_train, y_train):
    print("Setting up pipeline...")
    pipeline = ImbPipeline([
        ('tfidf', TfidfVectorizer(stop_words='english')),
        ('smote', SMOTE(random_state=42)),
        ('scaler', StandardScaler(with_mean=False)),
        ('svm', SVC())
    ])

    print("Setting up grid search...")
    param_grid = {
        'tfidf__max_df': [0.5, 0.7, 0.9],
        'tfidf__ngram_range': [(1, 1), (1, 2), (1, 3)],
        'svm__C': [0.1, 1, 10, 100],
        'svm__kernel': ['linear', 'rbf', 'poly'],
        'svm__gamma': ['scale', 'auto']
    }

    grid_search = GridSearchCV(pipeline, param_grid, cv=5, n_jobs=-1, verbose=2)

    print("Training model with grid search...")
    grid_search.fit(X_train, y_train)
    print("Best hyperparameters:", grid_search.best_params_)
    print("Model trained.")

    return grid_search.best_estimator_

def evaluate_model(model, X_test, y_test):
    print("Making predictions...")
    y_pred = model.predict(X_test)
    print("Predictions made.")

    print("Evaluating model...")
    accuracy = accuracy_score(y_test, y_pred)
    precision = precision_score(y_test, y_pred, average='weighted')
    recall = recall_score(y_test, y_pred, average='weighted')
    cm = confusion_matrix(y_test, y_pred)
    print("Model evaluated.")

    return accuracy, precision, recall, cm

if __name__ == "__main__":
    X_train, X_test, y_train, y_test = load_data(subset_size=0.005)  # Adjust subset size here

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

    if len(X_train) == len(y_train) and len(X_test) == len(y_test):
        model = train_model(X_train, y_train)
        accuracy, precision, recall, cm = evaluate_model(model, X_test, y_test)

        print(f"Accuracy: {accuracy}")
        print(f"Precision: {precision}")
        print(f"Recall: {recall}")
        print(f"Confusion Matrix: \n{cm}")
    else:
        print(f"Length mismatch persists: X_train length: {len(X_train)}, y_train length: {len(y_train)}")
        print(f"X_test length: {len(X_test)}, y_test length: {len(y_test)}")
