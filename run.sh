rm -rf *.txt *.png *.out
g++ -pthread -O0 -o task2.out task2.cc
./task2.out
python3 plot.py

