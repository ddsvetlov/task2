

// // DEPENDENT OF ACCESS TIME TO MEMORY ON THE NUMBER OF THREADS

// // helper func (for threading) to
// // check time to access for each element in array
// void array_access(int id)
// {
//     int sum = 0;
//     ull t1 = rdtsc();
//     for (int i = 0; i < static_array_size; i++)
//     {
//         sum += static_array[i];
//     }
//     ull t2 = rdtsc();
//     thread_time[id] = t2 - t1;
// }

// // func to dependent of access time to memory on the number of threads
// void thread_access()
// {
// 	// fill array
//     for (int i = 0; i < 1024; i++)
//     {
//         static_array[i] = rand() % (static_array_size - 1);
//     }
//     // threating
//     for (int i = 0; i < thread_num; i++)
//     {
//         std::thread my_thread(array_access, i);
//         my_thread.join();
//     }
//     // check time
//     for (int i = 0; i < thread_num; i++)
//     {
//         cout << thread_time[i] << endl;
//     }
// }


//     // third task
//     // call func to dependent of access time to memory on the number of threads
//     thread_access();

#include <iostream>
#include <time.h> 
#include <fstream>
#include <list>

using namespace std;
typedef list<int> LISTINT;

long int get_time(int ArraySize,int StepSize, bool AccessType) {
	// data
	int *Array = new int[ArraySize];
	int RandomIndex =0;
	int Current =0;
	struct timespec mt1, mt2;

	// fill arr
	for (int i=0; i<ArraySize;i++){
		Array[i]=rand()%100;
	}

	// start Timer
	clock_gettime (CLOCK_REALTIME, &mt1);

	if (AccessType){
		// get Access to random Element
		for (int i=0; i<ArraySize;i+=StepSize){
			RandomIndex=rand()%ArraySize;
			Current=Array[RandomIndex];
		}
	}	
	else {
		for (int i=0; i<ArraySize;i+=StepSize){
			Current=Array[i];
		}
	}
	// end Timer
	clock_gettime (CLOCK_REALTIME, &mt2);

	long int AccessTime=1000000000*(mt2.tv_sec - mt1.tv_sec)+(mt2.tv_nsec - mt1.tv_nsec);
	// cout << sizeof(*a) * ArraySize << endl;
	return AccessTime/ArraySize;
}

void write_data(std::list<int> DataSize, std::list<int> RandomTime,  std::list<int> SerialTime){
	ofstream x, y1, y2;

    x.open("x.txt", fstream::app);
    y1.open("y1.txt", fstream::app);
    y2.open("y2.txt", fstream::app);


    LISTINT::iterator i;

    for (i = DataSize.begin(); i != DataSize.end(); ++i)
    {
        x << *i << ",";
    }

    for (i = RandomTime.begin(); i != RandomTime.end(); ++i)
    {
        y1 << *i << ",";
    }

    for (i = SerialTime.begin(); i != SerialTime.end(); ++i)
    {
        y2 << *i << ",";
    }
    
    x.close();
    y1.close();
    y2.close();
}

void run_experiment(int ArraySize,int StepSize,int NumberExp,int StepExp){
	const int IntSize=sizeof(int);
	std::list<int> TimeAccessRandom;
	std::list<int> DataSize;
	std::list<int> TimeAccessSerial;
	long int AccessTime = 0;
	const bool RandomType = true;
	const bool SerialType = false;

	for (int i=0; i<NumberExp;i++){
		// access to random index
		AccessTime = get_time(ArraySize, StepSize, RandomType);
		TimeAccessRandom.push_back(AccessTime);

		// serial access
		AccessTime = get_time(ArraySize, StepSize, SerialType);
		TimeAccessSerial.push_back(AccessTime);

		DataSize.push_back(ArraySize*IntSize);
		ArraySize+=StepExp;
	}
	write_data(DataSize, TimeAccessRandom, TimeAccessSerial);
}


int main() {
	
	int ArraySize = 1;
	int StepSize = 1;
	int NumberExp = 50;
	int StepExp = 1000;

	run_experiment(ArraySize, StepSize, NumberExp, StepExp);
	
	return 0;
}