#include "openCommBase.hpp"
int main()
{
    openCommBase cl_base;
    cl_uint work_dim = 2;
    size_t g_work_offect[] = {0, 0, 0};
    size_t g_work_size[] = {1000, 0, 0};
    size_t *l_work_size = NULL;
    char* kernel_source = 
    "__kernel void test(__global int *sum)\n"
    "{\n"
    "int index = get_global_id(0)\n"
    "sum[index] += sum[index]\n"
    "}\n";
    cl_base.createOpenCLEnv();
    cl_base.processKernelProgram(kernel_source, "test");
    cl_base.eqNDRangeKernel(work_dim, g_work_offect,
    g_work_size, l_work_size);
    return 0;
}
