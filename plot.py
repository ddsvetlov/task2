import matplotlib.pyplot as plt

for i in (1,2,4,8):
    x=[]
    y=[]
    fil = open('random_' + str(i) + '_threads.txt', 'r')
    for elem in fil:
        print(elem)
        elem=elem.replace('\n','')
        data = elem.split(',')
    
        x.append(int(data[0]))
        y.append(int(data[1]))
    plt.plot(x,y, label='random_thread_' + str(i))   


x=[]
y=[]
fil = open('serial_' + str(1) + '_threads.txt', 'r')
for elem in fil:
    print(elem)
    elem=elem.replace('\n','')
    data = elem.split(',')

    x.append(int(data[0]))
    y.append(int(data[1]))
plt.plot(x,y, label='serial_thread_' + str(1))   




plt.legend()
# plt.savefig("benchmark.png")
plt.show()
