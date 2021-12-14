// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1_AR72614 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XADD_H
#define XADD_H

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
#include "xadd_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
#else
typedef struct {
    u16 DeviceId;
    u32 Axilites_BaseAddress;
} XAdd_Config;
#endif

typedef struct {
    u32 Axilites_BaseAddress;
    u32 IsReady;
} XAdd;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XAdd_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XAdd_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XAdd_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XAdd_ReadReg(BaseAddress, RegOffset) \
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
int XAdd_Initialize(XAdd *InstancePtr, u16 DeviceId);
XAdd_Config* XAdd_LookupConfig(u16 DeviceId);
int XAdd_CfgInitialize(XAdd *InstancePtr, XAdd_Config *ConfigPtr);
#else
int XAdd_Initialize(XAdd *InstancePtr, const char* InstanceName);
int XAdd_Release(XAdd *InstancePtr);
#endif

void XAdd_Start(XAdd *InstancePtr);
u32 XAdd_IsDone(XAdd *InstancePtr);
u32 XAdd_IsIdle(XAdd *InstancePtr);
u32 XAdd_IsReady(XAdd *InstancePtr);
void XAdd_EnableAutoRestart(XAdd *InstancePtr);
void XAdd_DisableAutoRestart(XAdd *InstancePtr);
u32 XAdd_Get_return(XAdd *InstancePtr);

u32 XAdd_Get_a_BaseAddress(XAdd *InstancePtr);
u32 XAdd_Get_a_HighAddress(XAdd *InstancePtr);
u32 XAdd_Get_a_TotalBytes(XAdd *InstancePtr);
u32 XAdd_Get_a_BitWidth(XAdd *InstancePtr);
u32 XAdd_Get_a_Depth(XAdd *InstancePtr);
u32 XAdd_Write_a_Words(XAdd *InstancePtr, int offset, int *data, int length);
u32 XAdd_Read_a_Words(XAdd *InstancePtr, int offset, int *data, int length);
u32 XAdd_Write_a_Bytes(XAdd *InstancePtr, int offset, char *data, int length);
u32 XAdd_Read_a_Bytes(XAdd *InstancePtr, int offset, char *data, int length);
u32 XAdd_Get_b_BaseAddress(XAdd *InstancePtr);
u32 XAdd_Get_b_HighAddress(XAdd *InstancePtr);
u32 XAdd_Get_b_TotalBytes(XAdd *InstancePtr);
u32 XAdd_Get_b_BitWidth(XAdd *InstancePtr);
u32 XAdd_Get_b_Depth(XAdd *InstancePtr);
u32 XAdd_Write_b_Words(XAdd *InstancePtr, int offset, int *data, int length);
u32 XAdd_Read_b_Words(XAdd *InstancePtr, int offset, int *data, int length);
u32 XAdd_Write_b_Bytes(XAdd *InstancePtr, int offset, char *data, int length);
u32 XAdd_Read_b_Bytes(XAdd *InstancePtr, int offset, char *data, int length);

void XAdd_InterruptGlobalEnable(XAdd *InstancePtr);
void XAdd_InterruptGlobalDisable(XAdd *InstancePtr);
void XAdd_InterruptEnable(XAdd *InstancePtr, u32 Mask);
void XAdd_InterruptDisable(XAdd *InstancePtr, u32 Mask);
void XAdd_InterruptClear(XAdd *InstancePtr, u32 Mask);
u32 XAdd_InterruptGetEnabled(XAdd *InstancePtr);
u32 XAdd_InterruptGetStatus(XAdd *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
