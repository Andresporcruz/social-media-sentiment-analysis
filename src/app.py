from flask import Flask, render_template, request
import pandas as pd

app = Flask(__name__)

@app.route('/')
def home():
    return render_template('index.html')

@app.route('/results', methods=['POST'])
def results():
    if request.method == 'POST':
        text = request.form['text']
        # Process the input text and get prediction
        prediction = "Positive"  # Example, replace with actual model prediction
        return render_template('results.html', prediction=prediction)

if __name__ == "__main__":
    app.run(debug=True)
