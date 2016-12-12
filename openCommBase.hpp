#ifndef __OPENCOMMBASE__HPP__
#define __OPENCOMMBASE__HPP__
#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

class openCommBase{
public: 
	//openCommBase();
	int createOpenCLEnv();
	int getPlatformId();
};
#endif
