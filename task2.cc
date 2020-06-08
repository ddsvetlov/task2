#include <iostream>
#include <time.h> 
#include <fstream>
#include <vector>
#include <thread>
#include <math.h>

using namespace std;
typedef vector<int> vectorINT;
const int QuantityAccess =100000000;
const int MAX_POWER=24;
const int IntSize = sizeof(int); 

long int get_time(int* Array,int ArraySize, bool AccessType) {
	// data
	int RandomIndex =0;
	struct timespec mt1, mt2;

	// start Timer
	clock_gettime (CLOCK_REALTIME, &mt1);

	if (AccessType){
		// get Access to random Element
		for (int i=0; i<QuantityAccess;i++){
			RandomIndex=Array[RandomIndex];
		}
	}	
	else {
		for (int i=0; i<QuantityAccess;i++){
			int Current = Array[RandomIndex%ArraySize];
            RandomIndex++;
		}
	}
	// end Timer
	clock_gettime (CLOCK_REALTIME, &mt2);

	long double AccessTime=1000000000*(mt2.tv_sec - mt1.tv_sec)+(mt2.tv_nsec - mt1.tv_nsec);
	return AccessTime/QuantityAccess;
}
long int get_avg_time(int ArraySize,bool AccessType,int QuantityThread){
	int ElementQuantity = ArraySize / IntSize;
    int* Array = (int*) malloc(ElementQuantity * IntSize);

    // fill Array
    for(int Index=0; Index < ElementQuantity; Index++) {
            Array[Index] = Index; 
    }

    // swap Array Elenments
    for(int Index = 0; Index < ElementQuantity; Index++) {
            int IndexFirst = rand() % ElementQuantity;
            int IndexSecond = rand() % ElementQuantity;

            if (IndexSecond == IndexFirst) {
                IndexSecond = rand() % ElementQuantity;
            }

            int Buffer = Array[IndexFirst];
            Array[IndexFirst] = Array[IndexSecond];
            Array[IndexSecond] = Buffer;
    } 
    // create array Time for threads 
    thread* ArrayThreads = new thread[QuantityThread];
    long double* ArrayTime = new long double[QuantityThread]; 

    for (int i = 0; i < QuantityThread; i++) {
        thread current_thread([ArrayTime, Array, ElementQuantity, AccessType, i](){
            long double Time = get_time(Array, ElementQuantity, AccessType); 
            ArrayTime[i] = Time;
        });

        ArrayThreads[i] = move(current_thread); 
    }
    for (int i = 0; i < QuantityThread; i++) {
        ArrayThreads[i].join(); 
    }

    // AVG Thread
    long double AVGTime = 0;
    for (int i = 0; i < QuantityThread; i++) {
        AVGTime += ArrayTime[i];
    }
    AVGTime = AVGTime / QuantityThread;

    free(Array);
    return AVGTime;
}

void write_data(vector<int> ArraySize, vector<long double> TimeArray, string filename) {
    ofstream x;

    x.open(filename, fstream::app);

    for (int i = 0; i < ArraySize.size(); i++)
    {
        x << ArraySize[i] << "," << TimeArray[i] << endl;
    }

    x.close();
}

pair<vector<int>, vector<long double>> run_experiment(bool ThreadMode,int ThreadQuantity){
	
	std::vector<long double> TimeArray;
	std::vector<int> DataSize;
	long int AccessTime = 0;

	for (int i=2;i<MAX_POWER;i++){
		int SizeInB = pow(2,i);
        DataSize.push_back(SizeInB);

        long double AccessTime = get_avg_time(SizeInB, ThreadMode, ThreadQuantity);
        TimeArray.push_back(AccessTime);

        cout << "AVGTime: " << AccessTime << " SizeInB " << SizeInB << endl;
	}

	return make_pair(DataSize, TimeArray); 
}

string create_name(bool AccessType, int QuantityThread){
    if (AccessType){
        return string("random_")+to_string(QuantityThread)+string("_threads.txt");
    }
    else {
        return string("serial_")+to_string(QuantityThread)+string("_threads.txt");
    }
}

int main() {
	
	srand((unsigned int)time(NULL));
    const bool RandomModeON = true;
    const bool RandomModeOFF = false;
    int QuantityThread = 1;

    // Random Access
    pair<vector<int>, vector<long double>> RandomAccess = run_experiment(RandomModeON, QuantityThread);
    write_data(RandomAccess.first, RandomAccess.second, create_name(RandomModeON, QuantityThread));

    // Serial Access
    pair<vector<int>, vector<long double>> SerialAccess = run_experiment(RandomModeOFF, QuantityThread);
    write_data(SerialAccess.first, SerialAccess.second, create_name(RandomModeOFF, QuantityThread));


    QuantityThread*=2;
    // Random Access 2 Thread
    pair<vector<int>, vector<long double>> Random2Threads = run_experiment(RandomModeON, QuantityThread);
    write_data(Random2Threads.first, Random2Threads.second, create_name(RandomModeON, QuantityThread));


    QuantityThread*=2;
    // Random Access 4 Thread
    pair<vector<int>, vector<long double>> Random4Threads = run_experiment(RandomModeON, QuantityThread);
    write_data(Random4Threads.first, Random4Threads.second, create_name(RandomModeON, QuantityThread));


    QuantityThread*=2;
    // Random Access 8 Thread
    pair<vector<int>, vector<long double>> Random8Threads = run_experiment(RandomModeON, QuantityThread);
    write_data(Random8Threads.first, Random8Threads.second, create_name(RandomModeON, QuantityThread));
	return 0;
}
