import pandas as pd

def inspect_columns(filepath):
    data = pd.read_csv(filepath)
    print(data.columns)

if __name__ == "__main__":
    filepath = 'data/train_data.csv'
    inspect_columns(filepath)

