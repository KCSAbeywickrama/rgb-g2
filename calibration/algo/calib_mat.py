import numpy as np

with open("calibration\data\calibdata1.txt") as fl:
    calib_data=fl.read().split('\n\n')

ex=np.array([tuple(map(int,line.split('\n')[0].split(','))) for line in calib_data][:3])
rd=np.array([tuple(map(int,line.split('\n')[1].split(','))) for line in calib_data][:3])


# print(ex)
# print()
# print(rd)

consts=[np.matmul(np.linalg.inv(rd),arr) for arr in np.split(ex,3,1)]

# calibration finished

with open("calibration\data\\readdata1.txt") as fl:
    calib_data=fl.read().split('\n\n')

ex=np.array([tuple(map(int,line.split('\n')[0].split(','))) for line in calib_data])
rd=np.array([tuple(map(int,line.split('\n')[1].split(','))) for line in calib_data])


print(ex)
print()
print(rd)

# for r in rd:
#     print([round(np.matmul(r,const)[0]) for const in consts])