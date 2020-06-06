#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include <list>
#include <cstdlib>
#include <thread>

using namespace std;
using namespace std::chrono;
typedef list<int> LISTINT;
typedef list<double> LISTDOUBLE;

typedef unsigned long long ull;

inline ull rdtsc()
{
    unsigned int lo, hi;
    asm volatile("rdtsc\n"
                 : "=a"(lo), "=d"(hi));
    return ((ull)hi << 32) | lo;
}

const int static_array_size = 1024;
static int static_array[static_array_size];
const int thread_num = 1;
static double thread_time[thread_num];

// 
double serial_access_time(int size, int step)
{
    int *a = new int[size];
    int sum = 0;
    int count = 100;
    double time = 0;
    // fill array random values
    for (int i = 0; i < size; i++)
    {
        a[i] = rand() % (size);
    }

    // start timer
    auto start_time = std::chrono::high_resolution_clock::now();

    // access to random element in array  
    for (int i = 0; i < size; i += step)
    {
        int index = rand() % (size);
        // do something with element in array
        sum += a[index];        
    }
 	// end timer
    auto end_time = std::chrono::high_resolution_clock::now();
    time += std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
    cout << "size: " << size * 4 << "    avg time: " << time / size * step << endl;
    delete[] a;
    // return avg speed
    return size / step / time;
}


// DEPENDENT OF ACCESS TIME TO MEMORY ON THE NUMBER OF THREADS

// helper func (for threading) to
// check time to access for each element in array
void array_access(int id)
{
    int sum = 0;
    ull t1 = rdtsc();
    for (int i = 0; i < static_array_size; i++)
    {
        sum += static_array[i];
    }
    ull t2 = rdtsc();
    thread_time[id] = t2 - t1;
}

// func to dependent of access time to memory on the number of threads
void thread_access()
{
	// fill array
    for (int i = 0; i < 1024; i++)
    {
        static_array[i] = rand() % (static_array_size - 1);
    }
    // threating
    for (int i = 0; i < thread_num; i++)
    {
        std::thread my_thread(array_access, i);
        my_thread.join();
    }
    // check time
    for (int i = 0; i < thread_num; i++)
    {
        cout << thread_time[i] << endl;
    }
}


int main()
{
    list<int> bytesList = {};
    list<double> timesList = {};

    int int_size = sizeof(int);
    int array_size = 60000;
    int steps_1 = 2400;

    cout << sizeof(int) << "bytes" << endl;

    // find data of bytes and times to set size of cash 
    for (int i = 0; i < steps_1; i++)
    {
        double time_count = serial_access_time(array_size, 1);
        bytesList.push_back(int_size * array_size);
        array_size+=100;
        timesList.push_back(time_count);

    }

    // third task
    // call func to dependent of access time to memory on the number of threads
    thread_access();

    // load data to txt file to create plot
    ofstream x, y;

    x.open("x.txt");
    y.open("y.txt");

    x << "";
    y << "";

    x.close();
    y.close();

    x.open("x.txt", fstream::app);
    y.open("y.txt", fstream::app);

    LISTINT::iterator i;

    for (i = bytesList.begin(); i != bytesList.end(); ++i)
    {
        x << *i << ",";
    }

    LISTDOUBLE::iterator d;

    for (d = timesList.begin(); d != timesList.end(); ++d)
    {
        y << *d << ",";
    }
    x.close();
    y.close();

    return 0;
}
