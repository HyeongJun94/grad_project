#include <cstdio>
#include <iostream>
#include <string>
#include <unistd.h>

#include <android/looper.h>
#include <android/sensor.h>
#include <android/log.h>

using namespace std;

#define LOG_TAG "Grad Project"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define ASSERT(cond, fmt, ...)  \
  if(!cond){  \
    __android_log_assert(#cond,LOG_TAG,fmt,##__VA_ARGS__);  \
  } \


const int event_count = 1;

void setVibrate(string time){
  char buffer[128];
  string cmd = string("echo ") + time + string(" > /sys/class/timed_output/vibrator/enable");
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

void openImage(char* path){
  char buffer[128];
  string cmd = string("am start -t image -d file:///") + string("storage/emulated/0/DCIM/Camera/") + string("testImg.png");
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


class MySensor{
  private:
    ASensorManager* sensor_manager;
    ASensorEventQueue* queue;
  public:
    MySensor(){
      sensor_manager = ASensorManager_getInstance();
      queue = ASensorManager_createEventQueue(
              sensor_manager,
              ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS),
              1,
              NULL,
              NULL);
    }
    ~MySensor(){
      int status = ASensorManager_destroyEventQueue(sensor_manager, queue);
      ASSERT(!status, "Failed to destroy event queue");
    }


    void PrintSensorList(){
      ASensorList sensor_list;
      int sensor_count = ASensorManager_getSensorList(sensor_manager, &sensor_list);
      
      printf("Num of Sensors : %d\n",sensor_count);
      for(int i=0;i<sensor_count;i++){
        printf("Found : %s\n",ASensor_getName(sensor_list[i]));
      }
    }

    void AccessSensor(int type){
      if(type == ASENSOR_TYPE_ACCELEROMETER){
        LOGI("Access accelerometer");
      } else if(type == ASENSOR_TYPE_GYROSCOPE) {
        LOGI("Access gyroscope");
      }
      const ASensor* sensor = ASensorManager_getDefaultSensor(sensor_manager, type);
      if(sensor && !ASensorEventQueue_enableSensor(queue,sensor)){
 
        for(int i=0; i< 10; i++){
          int ident = ALooper_pollAll(1000,NULL,NULL,NULL);
          if(ident == 1){
            ASensorEvent event;
            if(ASensorEventQueue_getEvents(queue,&event,1)){
              if(type == ASENSOR_TYPE_ACCELEROMETER){
                printf("Acc: x=%f, y=%f, z=%f\n",
                        event.acceleration.x,
                        event.acceleration.y,
                        event.acceleration.z);
              } else if(type == ASENSOR_TYPE_GYROSCOPE) {
                printf("Gyro: x-axis:%f, y-axis:%f, z-axis%f\n",event.data[0],event.data[1],event.data[2]);
              } else if(type == ASENSOR_TYPE_MAGNETIC_FIELD){
                printf("Magnetic: x:%f, y:%f, z:%f\n",
                        event.magnetic.x,
                        event.magnetic.y,
                        event.magnetic.z);
              } else if(type == ASENSOR_TYPE_PROXIMITY){
                printf("Proxy: %f\n",event.distance);
              } else if(type == ASENSOR_TYPE_LIGHT){
                printf("Light: %f\n",event.light);
              }
            }
          }
        }
      }

     int status = ASensorEventQueue_disableSensor(queue,sensor);
     ASSERT(!status,"Failed to disable sensor");
    }

    void AccessAcc(){
      AccessSensor(ASENSOR_TYPE_ACCELEROMETER);
    }

    void AccessGyro(){
      AccessSensor(ASENSOR_TYPE_GYROSCOPE);
    }

    void AccessMag(){
      AccessSensor(ASENSOR_TYPE_MAGNETIC_FIELD);
    }

    void AccessProx(){
      AccessSensor(ASENSOR_TYPE_PROXIMITY);
    }

    void AccessLight(){
      AccessSensor(ASENSOR_TYPE_LIGHT);
    }

    void AccessAll(){
      AccessAcc();
      AccessGyro();
      AccessMag();
      AccessProx();
      AccessLight();
    }
};

int main(int argc, char* argv[]){
  printf("Exec client android\n");
  MySensor* my_sensor= new MySensor();
 
  if(argc<2){
    my_sensor->AccessAll();
    delete my_sensor;
    return 0;
  }

  if(argv[1][0] == '1'){
    my_sensor->AccessAcc();
  } else if(argv[1][0] == '2') {
    my_sensor->AccessGyro();
  } else if(argv[1][0] == '3'){
    my_sensor->AccessMag();
  } else if(argv[1][0] == '4') {
    my_sensor->AccessProx();
  } else if(argv[1][0] == '5') {
    my_sensor->AccessLight();
  } else {
    openImage(argv[1]);
    setVibrate(string("200"));
  }

  delete my_sensor;

  return 0;
}
