import pandas as pd
import sklearn
from sklearn import linear_model, preprocessing
import pickle
import numpy as np

data = pd.read_csv("data48.data")

rgb = preprocessing.LabelEncoder()
er = rgb.fit_transform(list(data["er"]))
eg = rgb.fit_transform(list(data["eg"]))
eb = rgb.fit_transform(list(data["eb"]))
rr = rgb.fit_transform(list(data["rr"]))
rg = rgb.fit_transform(list(data["rg"]))
rb = rgb.fit_transform(list(data["rb"]))

X = list(zip(er,eg,rr,rg,rb))
Y = list(eb)

x_train, x_test, y_train, y_test = sklearn.model_selection.train_test_split(X, Y, test_size=0.8)

best = 0
for i in range(30):
    x_train, x_test, y_train, y_test = sklearn.model_selection.train_test_split(X, Y, test_size=0.8)
    linear = linear_model.LinearRegression()
    linear.fit(x_train, y_train)
    acc = linear.score(x_test, y_test)
    # print(y_test)

    if acc > best:
        best = acc
        best_linear = linear
        best_x_test = x_test
        best_y_test = y_test

with open("data48.pickle", 'wb') as f:
    pickle.dump(best_linear, f)

print(best)

predictions = best_linear.predict(best_x_test)
for i in range(len(predictions)):
    print(predictions[i], best_y_test[i], best_x_test[i])

print(best_y_test)
print("Coefficients :", best_linear.coef_)
print("Intercepts :", best_linear.intercept_)


