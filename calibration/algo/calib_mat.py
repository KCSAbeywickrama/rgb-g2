import numpy as np

with open("calibration\data\stage2\calibset2.txt") as fl:
    calib_data=fl.read().split('\n\n')

R,G,B,K,W=calib_data
sel_calib_data=R,G,B,W
ex=np.array([tuple(map(int,line.split('\n')[0].split(','))) for line in sel_calib_data])
rd=np.array([tuple(map(int,line.split('\n')[1].split(','))) for line in sel_calib_data])


print(ex)
print()
print(rd)

consts=[np.matmul(np.linalg.inv(rd),arr) for arr in np.split(ex,3,1)]

# calibration finished

with open("calibration\data\\readdata1.txt") as fl:
    read_data=fl.read().split('\n\n')

ex=np.array([tuple(map(int,line.split('\n')[0].split(','))) for line in read_data])
rd=np.array([tuple(map(int,line.split('\n')[1].split(','))) for line in read_data])


# print(ex)
# print()
# print(rd)

for i in range(len(rd)):
    e=np.array(ex[i])
    r=np.array([round(np.matmul(rd[i],const)[0]) for const in consts])
    print(e)
    print(r)
    print(e-r)
    print()