#include<iostream>
#include<sys/statvfs.h>

using namespace std;

int main(){
	struct statvfs stat;

	if(statvfs("/", &stat)!=0){
		cout<<"Failed to get disk info"<<endl;
		return 1;
	}
	
	unsigned long long total = stat.f_blocks*stat.f_frsize;
	unsigned long long free = stat.f_bfree*stat.f_frsize;
	unsigned long long used = total - free;

	cout<<"Total Disk: "<<total/(1024*1024*1024)<<" GB"<<endl;
	cout<<"Used Disk: "<<used/(1024*1024*1024)<<" GB"<<endl;
	cout<<"Free Disk: "<<free/(1024*1024*1024)<<" GB"<<endl;

	return 0;
}