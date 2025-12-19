#include<iostream>
#include<fstream>

using namespace std;

int main(){
	ifstream file("/proc/uptime");

	double uptimeSeconds;
	file >> uptimeSeconds;
	file.close();

	int hours = uptimeSeconds/3600;
	int minutes = (uptimeSeconds - hours*3600)/60;
	int seconds = (int)uptimeSeconds%60;

	cout<<"System Uptime: "<<hours<<"h "<<minutes<<"m "<<seconds<<"s"<<endl;

	return 0;
}