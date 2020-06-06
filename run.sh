rm -rf a.out x.txt y1.txt y2.txt
g++ -pthread -O3 -march=native task2.cc
./a.out
python3 plot.py 