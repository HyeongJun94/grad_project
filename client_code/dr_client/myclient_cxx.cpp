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

void wrap_pre(void *wrapcxt, OUT void **user_data);
void wrap_pre_acc(void *wrapcxt, OUT void **user_data);
void wrap_pre_gyro(void *wrapcxt, OUT void **user_data);
void wrap_pre_mag(void *wrapcxt, OUT void **user_data);
void wrap_pre_prox(void *wrapcxt, OUT void **user_data);
void wrap_pre_light(void *wrapcxt, OUT void **user_data);
void wrap_pre_image(void *wrapcxt, OUT void **user_data);
void wrap_post(void *wrapcxt, OUT void *user_data);
void module_load_event(void *drcontext, const module_data_t *mod, bool loaded);

static void event_exit(){
	dr_printf("Event Finished\n");
	drwrap_exit();
	drsym_exit();
	drmgr_exit();
}
void wrap_pre(void *wrapcxt, OUT void **user_data){
	dr_printf("Running wrap pre\n");

	pid_t pid = fork();
	if(pid==0){
		dr_printf("Child Process\n");
		execl("/system/build_android/client_android", "client_android", NULL);
	}
	else {
		wait(NULL);
		dr_printf("Parent Process\n");
	}
}

void wrap_pre_acc(void *wrapcxt, OUT void **user_data){
	dr_printf("Running wrap pre acc\n");

	pid_t pid = fork();
	if(pid==0){
		dr_printf("Child Process\n");
		execl("/system/build_android/client_android", "client_android", "1", NULL);
	}
	else {
		wait(NULL);
		dr_printf("Parent Process\n");
	}
};

void wrap_pre_gyro(void *wrapcxt, OUT void **user_data){
	dr_printf("Running wrap pre gyro\n");

	pid_t pid = fork();
	if(pid==0){
		dr_printf("Child Process\n");
		execl("/system/build_android/client_android", "client_android","2", NULL);
	}
	else {
		wait(NULL);
		dr_printf("Parent Process\n");
	}
};
void wrap_pre_mag(void *wrapcxt, OUT void **user_data){
	dr_printf("Running wrap pre mag\n");

	pid_t pid = fork();
	if(pid==0){
		dr_printf("Child Process\n");
		execl("/system/build_android/client_android", "client_android", "3",NULL);
	}
	else {
		wait(NULL);
		dr_printf("Parent Process\n");
	}
};
void wrap_pre_prox(void *wrapcxt, OUT void **user_data){
	dr_printf("Running wrap pre prox\n");

	pid_t pid = fork();
	if(pid==0){
		dr_printf("Child Process\n");
		execl("/system/build_android/client_android", "client_android","4",NULL);
	}
	else {
		wait(NULL);
		dr_printf("Parent Process\n");
	}
};
void wrap_pre_light(void *wrapcxt, OUT void **user_data){
	dr_printf("Running wrap pre light\n");

	pid_t pid = fork();
	if(pid==0){
		dr_printf("Child Process\n");
		execl("/system/build_android/client_android", "client_android", "5",NULL);
	}
	else {
		wait(NULL);
		dr_printf("Parent Process\n");
	}
};

void wrap_pre_image(void *wrapcxt, OUT void **user_data){
  dr_printf("Running wrap pre image\n");

  pid_t pid = fork();
  if(pid==0){
    dr_printf("Child Process\n");
    execl("/system/build_android/client_android", "client_android", "6", NULL);
  }
	else {
    wait(NULL);
    dr_printf("Parent Process\n");
  }
};

void wrap_post(void *wrapcxt, OUT void *user_data){
	dr_printf("Running wrap post\n");
}

void module_load_event(void *drcontext, const module_data_t *mod, bool loaded){
  char func_all[12]="AccessAll";
  char func_acc[12]="AccessAcc";
  char func_gyro[11]="AccessGyro";
  char func_mag[10]="AccessMag";
  char func_prox[11]="AccessProx";
  char func_light[12]="AccessLight";
  char func_image[13]="AccessImage";

	app_pc origin;
	size_t offs;

  bool wrapped = true;
  
  if(drsym_lookup_symbol(mod->full_path, func_all,&offs, DRSYM_DEMANGLE)==DRSYM_SUCCESS){
    origin = offs + mod->start;
    wrapped = drwrap_wrap(origin,wrap_pre,wrap_post);
  }
  else if(drsym_lookup_symbol(mod->full_path, func_acc, &offs, DRSYM_DEMANGLE) == DRSYM_SUCCESS){
    origin = offs + mod->start;
   // wrapped = drwrap_wrap(origin,wrap_pre_acc,wrap_post);
    wrapped = drwrap_wrap(origin,wrap_pre_image,wrap_post);
  }
  else if(drsym_lookup_symbol(mod->full_path, func_gyro, &offs, DRSYM_DEMANGLE) == DRSYM_SUCCESS){
    origin = offs + mod->start;
    wrapped = drwrap_wrap(origin,wrap_pre_gyro,wrap_post);
  }
  else if(drsym_lookup_symbol(mod->full_path, func_mag, &offs, DRSYM_DEMANGLE) == DRSYM_SUCCESS){
    origin = offs + mod->start;
    wrapped = drwrap_wrap(origin,wrap_pre_mag,wrap_post);
  }
  else if(drsym_lookup_symbol(mod->full_path, func_prox, &offs, DRSYM_DEMANGLE) == DRSYM_SUCCESS){
    origin = offs + mod->start;
    wrapped = drwrap_wrap(origin,wrap_pre_prox,wrap_post);
  }
  else if(drsym_lookup_symbol(mod->full_path, func_light, &offs, DRSYM_DEMANGLE) == DRSYM_SUCCESS){
    origin = offs + mod->start;
    wrapped = drwrap_wrap(origin,wrap_pre_light,wrap_post);
  }
  else if(drsym_lookup_symbol(mod->full_path, func_image, &offs, DRSYM_DEMANGLE)==DRSYM_SUCCESS){
    origin = offs + mod->start;
    wrapped = drwrap_wrap(origin,wrap_pre_image,wrap_post);
  }
}

DR_EXPORT void
dr_client_main(client_id_t id, int argc, const char* argv[]){
	dr_printf("Exec Client\n");

	drmgr_init();
	drsym_init(0);
	drwrap_init();
	dr_register_exit_event(event_exit);
	drmgr_register_module_load_event(module_load_event);
}
