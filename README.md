# Social Media Sentiment Analysis

## To run the code using the User Interface
- Clone the github project to your local machine
- Configure SFML to compile on your computer by following the instructions here: https://www.sfml-dev.org/tutorials/2.6/start-vc.php 
- Ensure your working directory is set to "social-media-sentiment-analysis" and not that src/main.cpp contains all of the SFML code for the project
- When you launch the SFML project the UI can be run and used

## To run the code without configuring SFML
- Clone the github project to your local machine
- Set your working directory to "social-media-sentiment-analysis"
- First run "python train_word_weighting_model.py" and "python train_nb_model.py" to train the models
- Next use the command "python src/predict.py [simple or nb] [phrase]" to either run the simple or naive bayes algorithm to determine the sentiment of the input phrase
- Run "python visuals/visualize_[positive or negative]_[simple or nb]" to generate a word cloud showing the most frequent words that appear in the positive or negative sentiment phrases determine by each algorithm

## Team Members
- Maiah Jaffa
- Andres Portillo
- Martin Wall

## Project Overview
Our goal is to use social media data analysis to ascertain public opinion on a range of subjects. We will classify posts as positive, negative, or neutral, focusing on understanding people's feelings about various topics, events, or entities.

## Features
- Sentiment analysis with at least 85% accuracy
- Visualization of sentiment trends
- Interactive dashboard for exploring sentiment data

## Tools and Libraries
### C++
- MITIE
- Pytorch C++
- Apache Arrow
- matplotlib
- SFML

### Python
- NLTK
- scikit-learn
- pandas
- matplotlib and seaborn
- Flask/Django (optional)

## Data
We will use the [Sentiment140 dataset](https://www.kaggle.com/datasets/krishbaisoya/tweets-sentiment-analysis) from Kaggle.

## Roles
- **Martin Wall**: Data preprocessing and interface development
- **Andres Portillo**: Machine Learning model training
- **Maiah Jaffa**: Data analysis and visualization


## Setup Instructions

Follow these steps to set up the project on your local machine:

### 1. Clone the Repository

Open a terminal and navigate to the directory where you want to clone the repository. Then, run the following commands:

git clone git@github.com:Andresporcruz/social-media-sentiment-analysis.git

cd social-media-sentiment-analysis

### 2. Set Up the Virtual Environment
Create and activate a virtual environment:

python3 -m venv venv
source venv/bin/activate  # On Windows, use `venv\Scripts\activate`

### 3. Install Dependencies
Install the required Python packages from requirements.txt:

pip install -r requirements.txt

### 4. Make Changes to the Project
Open the project in your preferred text editor or IDE (e.g., PyCharm, VSCode). Make your changes to the code.

### 5. Add and Commit Changes
After making changes, add the changes to the staging area:

git add .
Commit the changes 

git commit -m "Your descriptive commit message"

### 6. Push Changes to GitHub
Push your committed changes to the remote repository:

git push origin main

git pull origin main

Set Up SSH Keys: Ensure that your SSH key is set up correctly for GitHub to avoid permission issues.
