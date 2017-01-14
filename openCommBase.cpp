#include "openCommBase.hpp"
#include <iostream>

using namespace std;

int openCommBase::createOpenCLEnv(void)
{
    cl_int ret = 0;
#if 0
    //Get platform number and ID.
    ret = clGetPlatformIDs(0, NULL, &num_platform);
    if (CL_SUCCESS == ret || num_platform < 1)
    {
      cout << "Error getting platform number:" << ret << endl;
      return -1;
    }
#endif    
    ret = clGetPlatformIDs(1, &platform_id, NULL);
    if (CL_SUCCESS != ret)
    {
      cout << "Error getting platform id:" << ret << endl;
      return -1;
    }
    //Get device number and ID.
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 0, NULL, &num_device);
    if (CL_SUCCESS != ret)
    {
      cout << "Error getting GPU device number:" << ret << endl;
      return -1;
    }
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, num_device, &device_id, NULL);
    if (CL_SUCCESS != ret)
    {
      cout << "Error getting GPU device id:" << ret << endl;
      return -1;
    }
    //Create context.
    cl_context_properties prop[] = {CL_CONTEXT_PLATFORM, (cl_context_properties)platform_id, 0};
    cc = clCreateContext(prop, 1, &device_id, NULL, NULL, &ret);
    if (CL_SUCCESS != ret || cc == NULL)
    {
      cout << "Error getting context:" << ret << endl;
      return -1;
    }
    //Create command queue.
    ccq = clCreateCommandQueue(cc, device_id, 0, &ret);
    if (CL_SUCCESS != ret || ccq == NULL)
    {
      cout << "Error getting command queue:" << ret << endl;
      return -1;
    }
    //Create memory obj.
    int *host_ptr = NULL;
    int arr_size = 1000;
    host_ptr = (int *)malloc(arr_size*sizeof(int));
    if (host_ptr == NULL)
    {
      cout << "get memory failed" <<endl;
    }
    memset(host_ptr, '0', arr_size*sizeof(int));
    cm = clCreateBuffer(cc, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, arr_size*sizeof(int), host_ptr, &ret);
    if (CL_SUCCESS != ret || cm == NULL)
    {
      cout << "Error getting mem obj:" << ret << endl;
      return -1;
    }
    free(host_ptr);
    return ret;
}

char* openCommBase::getProgramBuildInfo(int log_size)
{
    size_t len;
    char* program_log;

    program_log = (char*)malloc(log_size*sizeof(char));
    if (program_log == NULL)
    {
      cout << "get log memory failed" << endl;
      return NULL;
    }
    cout << "log_size:" << log_size << endl;
    memset(program_log, '\0', log_size);

    clGetProgramBuildInfo(cp, device_id, CL_PROGRAM_BUILD_LOG, log_size+1, program_log, &len);

    cout << "log:" << program_log << endl;
}

int openCommBase::processKernelProgram(char *ksource, char *kname)
{
    cl_int ret = 0;
    //Create program.
    cp = clCreateProgramWithSource(cc, 1, (const char **)&ksource, NULL, &ret);
    if (CL_SUCCESS != ret || cp == NULL)
    {
      cout << "Error create kernel program:" << ret << endl;
      return -1;
    }
    ret = clBuildProgram(cp, 1, &device_id, NULL, NULL, NULL);
    if (ret == CL_BUILD_PROGRAM_FAILURE)
    cout << "buildProgram ret:" << ret << endl;
    if (CL_SUCCESS != ret)
    {
      cout << "Error build program:" << ret << endl;
      getProgramBuildInfo(100);
      return -1;
    }
    ck = clCreateKernel(cp, kname, &ret);
    if (ret != CL_SUCCESS || ck == NULL)
    {
      cout << "Error create kernel:" << ret << endl;
      return -1;
    }
    ret = clSetKernelArg(ck, 0, sizeof(cl_mem), (void*)&cm);
    if (CL_SUCCESS != ret)
    {
      cout << "Error set kernel arg:" << ret << endl;
      return -1;
    }
    return ret;
}

int openCommBase::eqNDRangeKernel(cl_uint work_dim, size_t *g_work_offect, size_t *g_work_size, size_t *l_work_size)
{
    cl_int ret = 0;
    clEnqueueNDRangeKernel(ccq, ck, work_dim, g_work_offect, g_work_size, l_work_size, 0, NULL, NULL);
    if (ret != CL_SUCCESS)
    {
      cout << "Error enqueue kenrel:" << ret << endl;
      return -1;
    }
    return ret;
}

void openCommBase::release()
{
    if (ccq != NULL) clReleaseCommandQueue(ccq);
    if (cc != NULL) clReleaseContext(cc);
    if (cp != NULL) clReleaseProgram(cp);
    if (ck != NULL) clReleaseKernel(ck);
}

