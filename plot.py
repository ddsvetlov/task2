import matplotlib.pyplot as plt

for i in (2,4,8):
  x = open('x_thread_' + str(i) + '.txt', 'r')
  x=x.read()
  x=(x.split(',')[:-1])
  x=[int(i) for i in x]

  y = open('y_thread_' + str(i) + '.txt', 'r')
  y=y.read()
  y=(y.split(',')[:-1])
  y=[float(i) for i in y]

  plt.plot(x,y, label='thread_' + str(i))

x = open('x_random.txt', 'r')
x=x.read()
x=(x.split(',')[:-1])
x=[int(i) for i in x]

y = open('y_random.txt', 'r')
y=y.read()
y=(y.split(',')[:-1])
y=[float(i) for i in y]

plt.plot(x,y, label='random')


x = open('x_serial.txt', 'r')
x=x.read()
x=(x.split(',')[:-1])
x=[int(i) for i in x]

y = open('y_serial.txt', 'r')
y=y.read()
y=(y.split(',')[:-1])
y=[float(i) for i in y]

plt.plot(x,y, label='serial')


plt.legend()
plt.savefig("benchmark.png")

