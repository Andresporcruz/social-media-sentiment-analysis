import argparse
import json
import pandas as pd

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        'texts',
        nargs='+'
    )
    args = parser.parse_args()
    phrase = ' '.join(args.texts).lower()
    words = phrase.split(' ')

    data_frame = pd.read_csv("model/simple_algorithm_model.csv")
    sentiment_dictionary = data_frame.to_dict(orient='list')
    sentiment_total = 0
    words_checked = 0

    for word in words:
        if word in sentiment_dictionary:
            words_checked += 1
            sentiment_total += sentiment_dictionary[word][0]

    if words_checked == 0:
        words_checked = 1
    print(json.dumps(sentiment_total / words_checked))
    
