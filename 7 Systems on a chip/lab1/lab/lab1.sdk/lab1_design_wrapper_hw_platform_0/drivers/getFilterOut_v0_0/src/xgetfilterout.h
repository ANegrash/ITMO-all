// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XGETFILTEROUT_H
#define XGETFILTEROUT_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xgetfilterout_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
#else
typedef struct {
    u16 DeviceId;
    u32 Axilites_BaseAddress;
} XGetfilterout_Config;
#endif

typedef struct {
    u32 Axilites_BaseAddress;
    u32 IsReady;
} XGetfilterout;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XGetfilterout_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XGetfilterout_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XGetfilterout_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XGetfilterout_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XGetfilterout_Initialize(XGetfilterout *InstancePtr, u16 DeviceId);
XGetfilterout_Config* XGetfilterout_LookupConfig(u16 DeviceId);
int XGetfilterout_CfgInitialize(XGetfilterout *InstancePtr, XGetfilterout_Config *ConfigPtr);
#else
int XGetfilterout_Initialize(XGetfilterout *InstancePtr, const char* InstanceName);
int XGetfilterout_Release(XGetfilterout *InstancePtr);
#endif

void XGetfilterout_Start(XGetfilterout *InstancePtr);
u32 XGetfilterout_IsDone(XGetfilterout *InstancePtr);
u32 XGetfilterout_IsIdle(XGetfilterout *InstancePtr);
u32 XGetfilterout_IsReady(XGetfilterout *InstancePtr);
void XGetfilterout_EnableAutoRestart(XGetfilterout *InstancePtr);
void XGetfilterout_DisableAutoRestart(XGetfilterout *InstancePtr);

void XGetfilterout_Set_depth(XGetfilterout *InstancePtr, u32 Data);
u32 XGetfilterout_Get_depth(XGetfilterout *InstancePtr);
u32 XGetfilterout_Get_out_correct(XGetfilterout *InstancePtr);
u32 XGetfilterout_Get_out_correct_vld(XGetfilterout *InstancePtr);
u32 XGetfilterout_Get_inputs_BaseAddress(XGetfilterout *InstancePtr);
u32 XGetfilterout_Get_inputs_HighAddress(XGetfilterout *InstancePtr);
u32 XGetfilterout_Get_inputs_TotalBytes(XGetfilterout *InstancePtr);
u32 XGetfilterout_Get_inputs_BitWidth(XGetfilterout *InstancePtr);
u32 XGetfilterout_Get_inputs_Depth(XGetfilterout *InstancePtr);
u32 XGetfilterout_Write_inputs_Words(XGetfilterout *InstancePtr, int offset, int *data, int length);
u32 XGetfilterout_Read_inputs_Words(XGetfilterout *InstancePtr, int offset, int *data, int length);
u32 XGetfilterout_Write_inputs_Bytes(XGetfilterout *InstancePtr, int offset, char *data, int length);
u32 XGetfilterout_Read_inputs_Bytes(XGetfilterout *InstancePtr, int offset, char *data, int length);
u32 XGetfilterout_Get_out_r_BaseAddress(XGetfilterout *InstancePtr);
u32 XGetfilterout_Get_out_r_HighAddress(XGetfilterout *InstancePtr);
u32 XGetfilterout_Get_out_r_TotalBytes(XGetfilterout *InstancePtr);
u32 XGetfilterout_Get_out_r_BitWidth(XGetfilterout *InstancePtr);
u32 XGetfilterout_Get_out_r_Depth(XGetfilterout *InstancePtr);
u32 XGetfilterout_Write_out_r_Words(XGetfilterout *InstancePtr, int offset, int *data, int length);
u32 XGetfilterout_Read_out_r_Words(XGetfilterout *InstancePtr, int offset, int *data, int length);
u32 XGetfilterout_Write_out_r_Bytes(XGetfilterout *InstancePtr, int offset, char *data, int length);
u32 XGetfilterout_Read_out_r_Bytes(XGetfilterout *InstancePtr, int offset, char *data, int length);

void XGetfilterout_InterruptGlobalEnable(XGetfilterout *InstancePtr);
void XGetfilterout_InterruptGlobalDisable(XGetfilterout *InstancePtr);
void XGetfilterout_InterruptEnable(XGetfilterout *InstancePtr, u32 Mask);
void XGetfilterout_InterruptDisable(XGetfilterout *InstancePtr, u32 Mask);
void XGetfilterout_InterruptClear(XGetfilterout *InstancePtr, u32 Mask);
u32 XGetfilterout_InterruptGetEnabled(XGetfilterout *InstancePtr);
u32 XGetfilterout_InterruptGetStatus(XGetfilterout *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
