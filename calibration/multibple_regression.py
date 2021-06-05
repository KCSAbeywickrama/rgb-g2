import pandas
from sklearn import linear_model

df5 = pandas.read_csv("data5.data")
df43 = pandas.read_csv("data43.data")

X_5 = df5[['rr', 'rg', 'rb']]
yr_5 = df5['er']
yg_5 = df5['eg']
yb_5 = df5['eb']

Xr_43 = df43['rr']
Xg_43 = df43['rg']
Xb_43 = df43['rb']
yr_43 = df43['er']
yg_43 = df43['eg']
yb_43 = df43['eb']

reg = linear_model.LinearRegression()
reg.fit(X_5, yb_5)

for i in range(len(yb_43)):
    predicted_yb = reg.predict([[Xr_43[i], Xg_43[i], Xb_43[i]]])
    print(round(predicted_yb[0], 2), yb_43[i], round(predicted_yb[0], 2)-yb_43[i], sep="\t")
