#ifndef __OPENCOMMBASE__HPP__
#define __OPENCOMMBASE__HPP__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CL/cl.h>

class openCommBase{
public: 
	//openCommBase();
	int createOpenCLEnv();
	int processKernelProgram(char *ksource, char *kname);
	int eqNDRangeKernel(cl_uint work_dim, size_t *g_work_offect, size_t *g_work_size, size_t *l_work_size);
	void release();
        char* getProgramBuildInfo(int logSize);
private:
  	cl_command_queue ccq;
	cl_context cc;
  	cl_mem cm;
  	cl_device_id device_id;
	cl_platform_id platform_id;
	cl_uint num_device;
	cl_uint num_platform;
	cl_program cp;
	cl_kernel ck;
};
#endif
