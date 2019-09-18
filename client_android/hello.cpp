#include <cstdio>
#include <iostream>
#include <string>
#include <android/sensor.h>
#include "myheader.h"
using namespace std;

void setVibrate(){
	char buffer[128];
	string cmd = string("echo ") + string("100") + string(" > /sys/class/timed_output/vibrator/enable");
	string result = "";
	FILE* pipe = popen(cmd.c_str(),"r");
	if(!pipe) 
	try{
		while(fgets(buffer,sizeof buffer, pipe)!=NULL){
			result += buffer;
		}
	}catch(...){
		pclose(pipe);
		throw;
	}
	pclose(pipe);

	cout << result << endl;
}

void printSensorList(int count, ASensorList sensor_list){
	cout << "========Print Sensor List=======" << endl;
	for(int i=0; i<count;i++){
		cout << ASensor_getName(sensor_list[i])<<endl;
	}
}

int main(){
	int sensor_count = 0;

	ASensorManager* sensor_manager = ASensorManager_getInstance();
	ASensorList sensor_list;
	sensor_count = ASensorManager_getSensorList(sensor_manager,&sensor_list);
	printSensorList(sensor_count,sensor_list);
	myheader_test();
	setVibrate();
	return 0;
}
