#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main(){
	ifstream file("/proc/meminfo");

	if(!file.is_open()){
		cout<<"Failed to open file"<<endl;
		return 1;
	}
	
	string key;
	long long value;
	string unit;

	long long memTotal = 0;
	long long memAvailable = 0;

	while(file>>key>>value>>unit){
		if(key=="MemTotal:"){
			memTotal = value;
		}
		else if(key=="MemAvailable:"){
			memAvailable = value;
		}

		if(memTotal && memAvailable)
			break;
	}

	file.close();

	long long memUsed=memTotal - memAvailable;
	double usage = (double)memUsed/memTotal * 100.0;

	cout<<"Total Memory: "<<memTotal/1024<<" MB"<<endl;
	cout<<"Used Memory : "<<memUsed/1024<<" MB"<<endl;
	cout<<"Free Memory : "<<memAvailable/1024<<" MB"<<endl;
	cout<<"Memory Usage: "<<usage<<" %"<<endl;

	return 0;
}