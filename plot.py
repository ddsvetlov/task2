import matplotlib.pyplot as plt
import numpy as np

x = open('x.txt',"r")
x=x.read()
x=(x.split(',')[:-1])
x=[int(i) for i in x]
# x=np.array(x)

y1 = open('y1.txt',"r")
y1=y1.read()
y1=(y1.split(',')[:-1])
y1=[float(i) for i in y1]
# y1=np.array(y1)

y2 = open('y2.txt',"r")
y2=y2.read()
y2=(y2.split(',')[:-1])
y2=[float(i) for i in y2]
# y2=np.array(y2)

print(len(x))
print(len(y1))
print(len(y2))

plt.plot(x,y1)
plt.plot(x,y2)
plt.show()