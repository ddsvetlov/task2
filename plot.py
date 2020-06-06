import matplotlib.pyplot as plt


x = open('x.txt',"r")
x=x.read()
x=(x.split(',')[:-1])
x=[int(i) for i in x]


y = open('y.txt',"r")
y=y.read()
y=(y.split(',')[:-1])
y=[float(i) for i in y]
print(x)
print(y)

plt.plot(x,y)
plt.show()