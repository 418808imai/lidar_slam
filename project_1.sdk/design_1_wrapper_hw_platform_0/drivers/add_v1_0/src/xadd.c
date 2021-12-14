// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1_AR72614 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xadd.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XAdd_CfgInitialize(XAdd *InstancePtr, XAdd_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Axilites_BaseAddress = ConfigPtr->Axilites_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XAdd_Start(XAdd *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAdd_ReadReg(InstancePtr->Axilites_BaseAddress, XADD_AXILITES_ADDR_AP_CTRL) & 0x80;
    XAdd_WriteReg(InstancePtr->Axilites_BaseAddress, XADD_AXILITES_ADDR_AP_CTRL, Data | 0x01);
}

u32 XAdd_IsDone(XAdd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAdd_ReadReg(InstancePtr->Axilites_BaseAddress, XADD_AXILITES_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XAdd_IsIdle(XAdd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAdd_ReadReg(InstancePtr->Axilites_BaseAddress, XADD_AXILITES_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XAdd_IsReady(XAdd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAdd_ReadReg(InstancePtr->Axilites_BaseAddress, XADD_AXILITES_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XAdd_EnableAutoRestart(XAdd *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAdd_WriteReg(InstancePtr->Axilites_BaseAddress, XADD_AXILITES_ADDR_AP_CTRL, 0x80);
}

void XAdd_DisableAutoRestart(XAdd *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAdd_WriteReg(InstancePtr->Axilites_BaseAddress, XADD_AXILITES_ADDR_AP_CTRL, 0);
}

u32 XAdd_Get_return(XAdd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAdd_ReadReg(InstancePtr->Axilites_BaseAddress, XADD_AXILITES_ADDR_AP_RETURN);
    return Data;
}
u32 XAdd_Get_a_BaseAddress(XAdd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Axilites_BaseAddress + XADD_AXILITES_ADDR_A_BASE);
}

u32 XAdd_Get_a_HighAddress(XAdd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Axilites_BaseAddress + XADD_AXILITES_ADDR_A_HIGH);
}

u32 XAdd_Get_a_TotalBytes(XAdd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XADD_AXILITES_ADDR_A_HIGH - XADD_AXILITES_ADDR_A_BASE + 1);
}

u32 XAdd_Get_a_BitWidth(XAdd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XADD_AXILITES_WIDTH_A;
}

u32 XAdd_Get_a_Depth(XAdd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XADD_AXILITES_DEPTH_A;
}

u32 XAdd_Write_a_Words(XAdd *InstancePtr, int offset, int *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XADD_AXILITES_ADDR_A_HIGH - XADD_AXILITES_ADDR_A_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Axilites_BaseAddress + XADD_AXILITES_ADDR_A_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XAdd_Read_a_Words(XAdd *InstancePtr, int offset, int *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XADD_AXILITES_ADDR_A_HIGH - XADD_AXILITES_ADDR_A_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Axilites_BaseAddress + XADD_AXILITES_ADDR_A_BASE + (offset + i)*4);
    }
    return length;
}

u32 XAdd_Write_a_Bytes(XAdd *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XADD_AXILITES_ADDR_A_HIGH - XADD_AXILITES_ADDR_A_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Axilites_BaseAddress + XADD_AXILITES_ADDR_A_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XAdd_Read_a_Bytes(XAdd *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XADD_AXILITES_ADDR_A_HIGH - XADD_AXILITES_ADDR_A_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Axilites_BaseAddress + XADD_AXILITES_ADDR_A_BASE + offset + i);
    }
    return length;
}

u32 XAdd_Get_b_BaseAddress(XAdd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Axilites_BaseAddress + XADD_AXILITES_ADDR_B_BASE);
}

u32 XAdd_Get_b_HighAddress(XAdd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Axilites_BaseAddress + XADD_AXILITES_ADDR_B_HIGH);
}

u32 XAdd_Get_b_TotalBytes(XAdd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XADD_AXILITES_ADDR_B_HIGH - XADD_AXILITES_ADDR_B_BASE + 1);
}

u32 XAdd_Get_b_BitWidth(XAdd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XADD_AXILITES_WIDTH_B;
}

u32 XAdd_Get_b_Depth(XAdd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XADD_AXILITES_DEPTH_B;
}

u32 XAdd_Write_b_Words(XAdd *InstancePtr, int offset, int *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XADD_AXILITES_ADDR_B_HIGH - XADD_AXILITES_ADDR_B_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Axilites_BaseAddress + XADD_AXILITES_ADDR_B_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XAdd_Read_b_Words(XAdd *InstancePtr, int offset, int *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XADD_AXILITES_ADDR_B_HIGH - XADD_AXILITES_ADDR_B_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Axilites_BaseAddress + XADD_AXILITES_ADDR_B_BASE + (offset + i)*4);
    }
    return length;
}

u32 XAdd_Write_b_Bytes(XAdd *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XADD_AXILITES_ADDR_B_HIGH - XADD_AXILITES_ADDR_B_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Axilites_BaseAddress + XADD_AXILITES_ADDR_B_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XAdd_Read_b_Bytes(XAdd *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XADD_AXILITES_ADDR_B_HIGH - XADD_AXILITES_ADDR_B_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Axilites_BaseAddress + XADD_AXILITES_ADDR_B_BASE + offset + i);
    }
    return length;
}

void XAdd_InterruptGlobalEnable(XAdd *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAdd_WriteReg(InstancePtr->Axilites_BaseAddress, XADD_AXILITES_ADDR_GIE, 1);
}

void XAdd_InterruptGlobalDisable(XAdd *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAdd_WriteReg(InstancePtr->Axilites_BaseAddress, XADD_AXILITES_ADDR_GIE, 0);
}

void XAdd_InterruptEnable(XAdd *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XAdd_ReadReg(InstancePtr->Axilites_BaseAddress, XADD_AXILITES_ADDR_IER);
    XAdd_WriteReg(InstancePtr->Axilites_BaseAddress, XADD_AXILITES_ADDR_IER, Register | Mask);
}

void XAdd_InterruptDisable(XAdd *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XAdd_ReadReg(InstancePtr->Axilites_BaseAddress, XADD_AXILITES_ADDR_IER);
    XAdd_WriteReg(InstancePtr->Axilites_BaseAddress, XADD_AXILITES_ADDR_IER, Register & (~Mask));
}

void XAdd_InterruptClear(XAdd *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAdd_WriteReg(InstancePtr->Axilites_BaseAddress, XADD_AXILITES_ADDR_ISR, Mask);
}

u32 XAdd_InterruptGetEnabled(XAdd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XAdd_ReadReg(InstancePtr->Axilites_BaseAddress, XADD_AXILITES_ADDR_IER);
}

u32 XAdd_InterruptGetStatus(XAdd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XAdd_ReadReg(InstancePtr->Axilites_BaseAddress, XADD_AXILITES_ADDR_ISR);
}

