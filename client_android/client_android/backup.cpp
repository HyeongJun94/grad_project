#include <cstdio>
#include <iostream>
#include <string>
#include <android/sensor.h>
#include <camera/NdkCameraManager.h>
#include <camera/NdkCameraDevice.h>
#include <camera/NdkCameraCaptureSession.h>
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

void cameraExample(){
	int camera_stat = 0;
	// Init camera manager and camera id list
	ACameraManager* camera_manager = ACameraManager_create();
	ACameraIdList* camera_id_list;
	ACameraDevice_StateCallbacks* camera_callback;
	ACameraDevice* device;
	ACaptureRequest* camera_request;
	ACaptureSessionOutputContainer* camera_output;
	ACameraCaptureSession_stateCallbacks* session_callback;
	ACameraCaptureSession* session;

	//session_callback->onActive = print_hello();
	
	ACameraCaptureSession_captureCallbacks* capture_callback;
	int id;

	camera_stat = ACameraManager_getCameraIdList(camera_manager,&camera_id_list);
	printf("[Camera Manager]Camera Stat:%d\n",camera_stat);
	printf("Id:%d\n",camera_id_list->numCameras);
	

	camera_stat = ACameraManager_openCamera(camera_manager,
																					camera_id_list->cameraIds[0],
																					camera_callback,
																					&device);
	printf("[Open Camera]Camera Stat:%d\n",camera_stat);

	camera_stat = ACameraDevice_createCaptureRequest(device,
																									 TEMPLATE_MANUAL,
																									 &camera_request);
	printf("[Capture Request]Camera Stat:%d\n",camera_stat);

	camera_stat = ACaptureSessionOutputContainer_create(&camera_output);	
	
	camera_stat = ACameraDevice_createCaptureSession(device,
																									 camera_output,
																									 session_callback,
																									 &session);
	printf("[Capture Session]Camera Stat:%d\n",camera_stat);
	
	camera_stat = ACameraCaptureSession_capture(session,
																							capture_callback,
																							1,
																							&camera_request,
																							&id);
																							
	printf("[Capture]Camera Stat:%d Id:%d\n",camera_stat,id);
	// free camera manager and camera id list
	ACameraManager_deleteCameraIdList(camera_id_list);
	ACameraManager_delete(camera_manager);
}

int main(){
	int sensor_count = 0;

	ASensorManager* sensor_manager = ASensorManager_getInstance();
	ASensorList sensor_list;
	sensor_count = ASensorManager_getSensorList(sensor_manager,&sensor_list);
	printSensorList(sensor_count,sensor_list);
	setVibrate();

	cameraExample();

	return 0;
}
