#include <iostream>
#include <cmath>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

struct thread_data
{
	int prime_number;
	int elapsed_seconds;
};

vector <thread_data> *vector_of_digits = new vector<thread_data>;
chrono::time_point<chrono::system_clock> start, end1;
mutex m_mutex;
int counter = 0;

void calculation_of_simple(int digit)
{
	start = chrono::system_clock::now();
	int index = 2;
	bool not_simple = false;

	for(; index<=sqrt(digit); index++)
	{
		if(!(digit%index))
		{
			not_simple = true;
			break;
		}
		else
		{
			not_simple = false;
		}
	}
	end1 = chrono::system_clock::now();

	thread_data data_set;
	data_set.elapsed_seconds = chrono::duration_cast<chrono::milliseconds>(end1-start).count();
	data_set.prime_number = digit;

	if(!not_simple)
	{
		m_mutex.lock();
		counter++;
		vector_of_digits->push_back(data_set);
		cout << "counter: " << counter << ". Digit: " << data_set.prime_number << ". Time(ms):" << data_set.elapsed_seconds << endl;
		m_mutex.unlock();
	}
}

int main()//int argc, char *argv[]
{

	vector_of_digits->resize(1000000);
	for(int i = 3; i <= 100000; i+=2)//numeric_limits<int>::max()
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(rand()%200));
		thread thr(calculation_of_simple, i);
		thr.detach();
	}
	delete [] vector_of_digits;
	return 0;
}
