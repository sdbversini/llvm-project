//===--- cuda/dynamic_cuda/cuda.h --------------------------------- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// The parts of the cuda api that are presently in use by the openmp cuda plugin
//
//===----------------------------------------------------------------------===//

#ifndef DYNAMIC_CUDA_CUDA_H_INCLUDED
#define DYNAMIC_CUDA_CUDA_H_INCLUDED

#include <cstddef>
#include <cstdint>

typedef int CUdevice;
typedef uintptr_t CUdeviceptr;
typedef struct CUmod_st *CUmodule;
typedef struct CUctx_st *CUcontext;
typedef struct CUfunc_st *CUfunction;
typedef struct CUstream_st *CUstream;

typedef enum cudaError_enum {
  CUDA_SUCCESS = 0,
  CUDA_ERROR_INVALID_VALUE = 1,
} CUresult;

typedef enum CUstream_flags_enum {
  CU_STREAM_DEFAULT = 0x0,
  CU_STREAM_NON_BLOCKING = 0x1,
} CUstream_flags;

typedef enum CUdevice_attribute_enum {
  CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_X = 2,
  CU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_X = 5,
  CU_DEVICE_ATTRIBUTE_WARP_SIZE = 10,
} CUdevice_attribute;

typedef enum CUfunction_attribute_enum {
  CU_FUNC_ATTRIBUTE_MAX_THREADS_PER_BLOCK = 0,
} CUfunction_attribute;

typedef enum CUctx_flags_enum {
  CU_CTX_SCHED_BLOCKING_SYNC = 0x04,
  CU_CTX_SCHED_MASK = 0x07,
} CUctx_flags;

CUresult cuCtxGetDevice(CUdevice *);
CUresult cuDeviceGet(CUdevice *, int);
CUresult cuDeviceGetAttribute(int *, CUdevice_attribute, CUdevice);
CUresult cuDeviceGetCount(int *);
CUresult cuFuncGetAttribute(int *, CUfunction_attribute, CUfunction);

CUresult cuGetErrorString(CUresult, const char **);
CUresult cuInit(unsigned);
CUresult cuLaunchKernel(CUfunction, unsigned, unsigned, unsigned, unsigned,
                        unsigned, unsigned, unsigned, CUstream, void **,
                        void **);

CUresult cuMemAlloc_v2(CUdeviceptr *, size_t);
CUresult cuMemcpyDtoDAsync_v2(CUdeviceptr, CUdeviceptr, size_t, CUstream);

CUresult cuMemcpyDtoH_v2(void *, CUdeviceptr, size_t);
CUresult cuMemcpyDtoHAsync_v2(void *, CUdeviceptr, size_t, CUstream);
CUresult cuMemcpyHtoD_v2(CUdeviceptr, const void *, size_t);
CUresult cuMemcpyHtoDAsync_v2(CUdeviceptr, const void *, size_t, CUstream);

CUresult cuMemFree_v2(CUdeviceptr);
CUresult cuModuleGetFunction(CUfunction *, CUmodule, const char *);
CUresult cuModuleGetGlobal_v2(CUdeviceptr *, size_t *, CUmodule, const char *);

CUresult cuModuleUnload(CUmodule);
CUresult cuStreamCreate(CUstream *, unsigned);
CUresult cuStreamDestroy_v2(CUstream);
CUresult cuStreamSynchronize(CUstream);
CUresult cuCtxSetCurrent(CUcontext);
CUresult cuDevicePrimaryCtxRelease_v2(CUdevice);
CUresult cuDevicePrimaryCtxGetState(CUdevice, unsigned *, int *);
CUresult cuDevicePrimaryCtxSetFlags_v2(CUdevice, unsigned);
CUresult cuDevicePrimaryCtxRetain(CUcontext *, CUdevice);
CUresult cuModuleLoadDataEx(CUmodule *, const void *, unsigned, void *,
                            void **);

CUresult cuDeviceCanAccessPeer(int *, CUdevice, CUdevice);
CUresult cuCtxEnablePeerAccess(CUcontext, unsigned);
CUresult cuMemcpyPeerAsync(CUdeviceptr, CUcontext, CUdeviceptr, CUcontext,
                           size_t, CUstream);

#endif
