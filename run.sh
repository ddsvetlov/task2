rm -rf a.out x.txt y.txt
g++ -pthread -O3 -march=native task2.cc
./a.out
python3 plot.py 