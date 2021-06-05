import pandas as pd
import sklearn
from sklearn import linear_model, preprocessing
import pickle
import numpy as np

data = pd.read_csv("data5.data")

rgb5 = preprocessing.LabelEncoder()
er5 = rgb5.fit_transform(list(data["er"]))
eg5 = rgb5.fit_transform(list(data["eg"]))
eb5 = rgb5.fit_transform(list(data["eb"]))
rr5 = rgb5.fit_transform(list(data["rr"]))
rg5 = rgb5.fit_transform(list(data["rg"]))
rb5 = rgb5.fit_transform(list(data["rb"]))

data = pd.read_csv("data43.data")

rgb43 = preprocessing.LabelEncoder()
er43 = rgb43.fit_transform(list(data["er"]))
eg43 = rgb43.fit_transform(list(data["eg"]))
eb43 = rgb43.fit_transform(list(data["eb"]))
rr43 = rgb43.fit_transform(list(data["rr"]))
rg43 = rgb43.fit_transform(list(data["rg"]))
rb43 = rgb43.fit_transform(list(data["rb"]))

X5 = list(zip(er5,eg5,rr5,rg5,rb5))
Y5 = list(eb5)

X43 = list(zip(er43,eg43,rr43,rg43,rb43))
Y43 = list(eb43)

x_train, x_test, y_train, y_test = X43, X5, Y43, Y5

# best = 0
# for i in range(30):
#     x_train, x_test, y_train, y_test = sklearn.model_selection.train_test_split(X, Y, test_size=0.0)

linear = linear_model.LinearRegression()
linear.fit(x_train, y_train)
acc = linear.score(x_test, y_test)

# if acc > best:
#     best = acc
#     best_linear = linear
#     best_x_test = x_test
#     best_y_test = y_test

with open("data5.pickle", 'wb') as f:
    pickle.dump(linear, f)

print(acc)
