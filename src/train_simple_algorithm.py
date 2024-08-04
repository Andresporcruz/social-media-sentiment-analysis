import argparse
import json
import pandas as pd

if __name__ == "__main__":
    sentiment_dictionary = {}

    phrases = pd.read_csv("data/X_train.csv", skiprows = 1, names = ["Phrase"], dtype = str)
    sentiment_values = pd.read_csv("data/y_train.csv", skiprows = 1, names = ["Sentiment"], dtype = int)
    
    for phrase_row, sentiment_row in zip(phrases.iterrows(), sentiment_values.iterrows()):
        _, phrase_data = phrase_row
        _, sentiment_data = sentiment_row

        training_phrase = str(phrase_data['Phrase'])
        sentiment = sentiment_data['Sentiment']

        training_words = training_phrase.split()
        for word in training_words:
            if word not in sentiment_dictionary:
                if float(sentiment) == 0:
                    sentiment_dictionary[word] = [1, 0]
                else:
                    sentiment_dictionary[word] = [0, 1]
                
            else:
                if float(sentiment) == 0:
                    sentiment_dictionary[word] = [sentiment_dictionary[word][0] + 1, sentiment_dictionary[word][1]]
                else:
                    sentiment_dictionary[word] = [sentiment_dictionary[word][0], sentiment_dictionary[word][1] + 1]

    parsed_dictionary = {k: [v[1] / (v[0] + v[1])] for k, v in sentiment_dictionary.items()}
    data_frame = pd.DataFrame(parsed_dictionary)
    data_frame.to_csv("model/simple_algorithm_model.csv", index=False)
    