#This small yet effective Project predicts with close to 95% accuracy whether or not an article is Fake News 
import numpy as np
import pandas as pd
import sklearn 

from sklearn.model_selection import train_test_split
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.svm import LinearSVC

#Open DataSet
data = pd.read_csv("fake_or_real_news.csv")
#Add new column to DataSet 0 for True , 1 for Fake 
data['fake'] = data['label'].apply(lambda x: 0 if x=='REAL' else 1)

#Split and Vectorize Data
X,y = data['text'] , data['fake']
X_train, X_test, y_train, y_test = train_test_split(X, y,test_size =0.2)
vectorizer = TfidfVectorizer(stop_words='english' , max_df=0.7)
X_train_vectorized = vectorizer.fit_transform(X_train)
X_test_vectorized =vectorizer.transform(X_test)

#Train the model 
clf = LinearSVC()
clf.fit(X_train_vectorized, y_train)

#Accuracy Score
score = clf.score(X_test_vectorized,y_test)
print (score)



#Predict new article from the Web
from newspaper import Article

#You replace the URL with any article written in English
url = 'https://www.euronews.com/green/2023/11/09/shell-is-suing-greenpeace-for-2-million-after-activists-boarded-oil-vessel-near-canary-isl'

article = Article(url)


article.download()
article.parse()
my_article = article.text


vectorized_article = vectorizer.transform([my_article])

prediction = clf.predict(vectorized_article)
print(prediction)

if prediction == 0:
	print ("REAL News")
elif prediction == 1:
	print('FAKE News')
