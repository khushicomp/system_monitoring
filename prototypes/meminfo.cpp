#include<iostream>
#include<fstream>
#include<string>

using namespace std;


int main(){
	ifstream file("/proc/meminfo");

	if(!file.is_open()){
		cout<<"Failed to open the file" <<endl;
		return 1;
	}

	string line;
	while(getline(file, line)){
		cout<<line<<endl;
	}

	file.close();
	return 0;
}