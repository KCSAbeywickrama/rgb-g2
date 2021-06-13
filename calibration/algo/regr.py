import numpy as np
import matplotlib.pyplot as plt
from scipy import stats
from sklearn.metrics import r2_score

with open("calibration\data\\dataset5.txt") as fl:
    calib_data=fl.read().split('\n\n')

ex=np.array([tuple(map(int,line.split('\n')[0].split(','))) for line in calib_data])
rd=np.array([tuple(map(int,line.split('\n')[1].split(','))) for line in calib_data])

y=np.split(ex,3,1)[1].reshape(12)
x=np.split(rd,3,1)[1].reshape(12)

mymodel = np.poly1d(np.polyfit(x, y, 3))

myline = np.linspace(50, 350, 100)

plt.scatter(x, y)
plt.plot(myline, mymodel(myline))
plt.show()

print(r2_score(y, mymodel(x)))
