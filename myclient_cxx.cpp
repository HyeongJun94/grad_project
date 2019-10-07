#include "dr_api.h"
#include "drmgr.h"
#include "drwrap.h"
#include "drsyms.h"
#include <cstdio>
#include <iostream>
#include <string>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

#ifdef WINDOWS
#    define IF_WINDOWS_ELSE(x, y) x
#else
#    define IF_WINDOWS_ELSE(x, y) y
#endif

#ifdef WINDOWS
#    define DISPLAY_STRING(msg) dr_messagebox(msg)
#else
#    define DISPLAY_STRING(msg) dr_printf("%s\n", msg);
#endif

#define NULL_TERMINATE(buf) buf[(sizeof(buf) / sizeof(buf[0])) - 1] = '\0'

static void event_exit();
void wrap_pre(void *wrapcxt, OUT void **user_data);
void wrap_post(void *wrapcxt, OUT void *user_data);

void takePicture();
void video_streaming();
void tmp();

static void event_exit(){
	dr_printf("Event Finished\n");
	drwrap_exit();
	drsym_exit();
	drmgr_exit();
}

void wrap_pre(void *wrapcxt, OUT void **user_data){
	dr_printf("Running wrap pre\n");
	//video_streaming();
	//tmp();
	pid_t pid = fork();
	if(pid==0){
		// child process
		dr_printf("Child Process\n");
		execl("/home/hyeongjun/workspace/backup/build/myhello","myhello",NULL);
	}
	else{
		wait(NULL);
		dr_printf("Parent Process\n");
	}
}

void wrap_post(void *wrapcxt, OUT void *user_data){
	dr_printf("Running wrap post\n");
}

static void module_load_event(void *drcontext, const module_data_t *mod, bool loaded){
	//dr_printf("[For DEbug] full path \"%s\"\n",mod->full_path);
	char func_name[12]= "print_hello";
	app_pc origin;
	size_t offs;
	if(drsym_lookup_symbol(mod->full_path, func_name, &offs, DRSYM_DEMANGLE)==DRSYM_SUCCESS){
		origin = offs + mod->start;
		//dr_printf("function \"%s\" is found\n",func_name);
		bool wrapped = drwrap_wrap(origin,wrap_pre,wrap_post);
		//bool wrapped = drwrap_replace(origin, (app_pc)video_streaming, true);
		//bool wrapped = drwrap_replace(origin,(app_pc)tmp,true);
		if(wrapped){
			//dr_printf("function \"%s\" is wrapped\n",func_name);
		}
	}
}

void tmp(){
	printf("Sucess replacement\n");
}

void takePicture(){
	char buffer[128];
	string cmd = string("raspistill -o tmp.jpg");
	string result = "";
	FILE* pipe = popen(cmd.c_str(), "r");
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

void video_streaming(){
	cout << "Start Video Streaming" << endl;
	char buffer[128];
	string cmd = string("raspivid -t 0 -n -w 300 -h 300 -o - | nc -u 127.0.0.1 5000");
	string result = "";
	FILE* pipe = popen(cmd.c_str(), "r");
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


DR_EXPORT void
dr_client_main(client_id_t id, int argc, const char* argv[]){
	
//	takePicture();
	
//	video_streaming();
	
	drmgr_init();
	drsym_init(0);
	drwrap_init();
	dr_register_exit_event(event_exit);
	drmgr_register_module_load_event(module_load_event);
}
