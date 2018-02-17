#include <iostream>
#include <cmath>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

vector <int> *vector_of_digits = new vector<int>;
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
	int elapsed_seconds = chrono::duration_cast<chrono::nanoseconds>(end1-start).count();
	if(!not_simple)
	{
		m_mutex.lock();
		counter++;
		vector_of_digits->push_back(index);
		cout << "counter: " << counter << ". Digit: " << digit << ". Time(ms):" << elapsed_seconds <<endl;
		m_mutex.unlock();
	}
}

int main()//int argc, char *argv[]
{

	vector_of_digits->resize(1000000);
	for(int i = 3; i <= 100000; i+=2)//numeric_limits<int>::max()
	{
		thread thr(calculation_of_simple, i);
		thr.detach();
		std::this_thread::sleep_for(std::chrono::microseconds(rand()%100));
	}
	delete [] vector_of_digits;
	return 0;
}
