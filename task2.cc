#include <iostream>
#include <time.h> 
#include <fstream>
#include <vector>
#include <thread>

using namespace std;
typedef vector<int> vectorINT;

void write_current(int Current){
	ofstream cur;
	cur.open("current.txt",fstream::app);
    cur<<Current;
    cur.close();
}

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

	if (AccessType=true){
		// get Access to random Element
		for (int i=0; i<ArraySize;i+=StepSize){
			RandomIndex=Current+rand()%(ArraySize-Current);
			Current=Array[RandomIndex];
			write_current(Current);
		}
	}	else {
			for (int i=0; i<ArraySize;i+=StepSize){
				Current=Array[i];
				write_current(Current);
			}
		}
	// end Timer
	clock_gettime (CLOCK_REALTIME, &mt2);

	long int AccessTime=1000000000*(mt2.tv_sec - mt1.tv_sec)+(mt2.tv_nsec - mt1.tv_nsec);
	return AccessTime/ArraySize/StepSize;
}

void write_data(std::vector<int> DataSize, std::vector<int> RandomTime,string Name){

	ofstream x, y;

    x.open(string("x")+Name+string(".txt"), fstream::app);
    y.open(string("y")+Name+string(".txt"), fstream::app);

    vectorINT::iterator i;
    for (i = DataSize.begin(); i != DataSize.end(); ++i)
    {
        x << *i << ",";
    }

    for (i = RandomTime.begin(); i != RandomTime.end(); ++i)
    {
        y << *i << ",";
    }

    x.close();
    y.close();
}

int MaxThreads = 10;
pair<vector<int>,vector<int>>* ThreadsData= new pair<vector<int>,vector<int>> [MaxThreads];

void run_experiment(int ArraySize,int StepSize,int NumberExp,int StepExp,bool NoThreadMode,int ThreadID){
	const int IntSize=sizeof(int);
	std::vector<int> TimeAccessRandom;
	std::vector<int> DataSize;
	std::vector<int> TimeAccessSerial;

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
	if (NoThreadMode){
		write_data(DataSize, TimeAccessRandom, string("_random"));
		write_data(DataSize, TimeAccessSerial, string("_serial"));
	}
	else{
		ThreadsData[ThreadID]= make_pair(DataSize,TimeAccessRandom);
	} 
}

void write_data_threads(int QuantityThread, int ArraySize){
	vector<int> AVGTime(ArraySize, 0);
	for (int i=0;i<ArraySize;i++){
		for(int j=0;j<QuantityThread;j++){
			AVGTime[i]+=ThreadsData[j].second[i]/QuantityThread;
		}
	}
	vector<int> DataSize = ThreadsData[0].first;
	string Name = string("_thread_")+to_string(QuantityThread);
	write_data(DataSize, AVGTime, Name);
}

void run_in_threads(int ArraySize, int StepSize, int NumberExp, int StepExp, int QuantityThread){
	
	thread* Threadvector = new thread[QuantityThread];
	bool NoThreadMode=false;
	for(int i =0; i<QuantityThread;i++) {
		thread CurrentThread(run_experiment, ArraySize, StepSize, NumberExp, StepExp,NoThreadMode,i);
		Threadvector[i] = move(CurrentThread);
	}

	for(int i =0; i<QuantityThread;i++) {
		Threadvector[i].join();
	}

	write_data_threads(QuantityThread,NumberExp);
}

int main() {
	
	int ArraySize = 10;
	int StepSize = 1;
	int NumberExp = 10;
	int StepExp = 100000;
	bool NoThreadMode=true;
	int ThreadID =0;

	// task 1-2
	run_experiment(ArraySize, StepSize, NumberExp, StepExp, NoThreadMode,ThreadID);

	// task 3
	int QuantityThread = 8;
	for (int i=2;i<=QuantityThread;i*=2){
		run_in_threads(ArraySize, StepSize, NumberExp, StepExp,i);
	}

	return 0;
}