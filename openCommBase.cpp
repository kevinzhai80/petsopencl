#include "openCommBase.hpp"
#include <iostream>

using namespace std;

int openCommBase::createOpenCLEnv(void)
{
    cl_int ret;
    cl_uint num_platform;
    //Get platform number and ID.
    ret = clGetPlatformIDs(0, NULL, &num_platform);
    if (CL_SUCCESS == ret || num_platform < 1)
    {
      cout << "Error getting platform number:" << ret << endl;
      return 0;
    }
    cl_platform_id platform_id = NULL;
    ret = clGetPlatformIDs(0, &platform_id, NULL);
    if (CL_SUCCESS != ret)
    {
      cout << "Error getting platform id:" << ret << endl;
      return 0;
    }
    //Get device number and ID.
    cl_uint num_device;
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 0, NULL, &num_device);
    if (CL_SUCCESS != ret)
    {
      cout << "Error getting GPU device number:" << ret << endl;
      return 0;
    }
    cl_device_id device_id;
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 0, &device_id, NULL);
    if (CL_SUCCESS != ret)
    {
      cout << "Error getting GPU device id:" << ret << endl;
      return 0;
    }
    //Create context.
    cl_context_properties prop[] = {CL_CONTEXT_PLATFORM, (cl_context_properties)platform_id, 0};
    ptr.cc = clCreateContext(prop, 1, &device_id, NULL, NULL, &ret);
    if (CL_SUCCESS != ret || ptr.cc == NULL)
    {
      cout << "Error getting context:" << ret << endl;
      return 0;
    }
    //Create command queue.
    ptr.ccq = clCreateCommandQueue(ptr.cc, device_id, 0, &ret);
    if (CL_SUCCESS != ret || ptr.ccq == NULL)
    {
      cout << "Error getting command queue:" << ret << endl;
      return 0;
    }
    //Create memory obj.
    int * host_ptr = NULL;
    int arr_size = 1000;
     
    host_ptr = (int *)malloc(arr_size*sizeof(int));
    memcpy(host_ptr, 0, arr_size*sizeof(int));
    ptr.cm = clCreateBuffer(ptr.cc, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, arr_size*sizeof(int), host_ptr, &ret);
    if (CL_SUCCESS != ret || ptr.cm == NULL)
    {
      cout << "Error getting mem obj:" << ret << endl;
      return 0;
    }
}


