#ifndef __OPENCOMMBASE__HPP__
#define __OPENCOMMBASE__HPP__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CL/cl.h>

typedef struct{
  cl_command_queue ccq;
  cl_context cc;
  cl_mem cm;
}CL_PTR;

class openCommBase{
public: 
	//openCommBase();
	int createOpenCLEnv();
	int getPlatformId();
private:
	CL_PTR ptr;
};
#endif
