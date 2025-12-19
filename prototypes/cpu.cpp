#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<unistd.h>

using namespace std;

long long getTotalCPUTime(long long &idleTime){
	ifstream file("/proc/stat");
	string line;

	getline(file, line);
	
	string cpu;
	long long user, nice, system, idle, iowait, irq, softirq, steal;

	stringstream ss(line);
	ss>>cpu>>user>>nice>>system>>idle>>iowait>>irq>>softirq>>steal;
	idleTime= idle+iowait;
	
	return user+nice+system+idle+iowait+irq+softirq+steal;
}

int main(){
	long long idle1, idle2;
	long long total1 = getTotalCPUTime(idle1);

	sleep(1);

	long long total2 = getTotalCPUTime(idle2);

	long long totalDiff=total2-total1;
	long long idleDiff= idle2-idle1;

	double cpuUsage= (double)(totalDiff-idleDiff)/totalDiff * 100.0;

	cout<<"CPU Usage: "<<cpuUsage<<" %"<<endl;

	return 0;
}