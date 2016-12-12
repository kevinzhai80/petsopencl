#include "openCommBase.hpp"
#include <iostream>

using namespace std;

int openCommBase::createOpenCLEnv(void)
{
    cl_int ret;
    cl_uint num_platform;

    ret = clGetPlatformIDs(0, NULL, &num_platform);
    cout<<"ret="<<ret<<"num_platform"<<num_platform<<endl;
    if (CL_SUCCESS == ret || num_platform < 1)
    {
      cout<<"Error getting platform number:"<<ret<<endl;
      return 0;
    }
}


