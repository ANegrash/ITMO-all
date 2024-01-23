// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xgetfilterout.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XGetfilterout_CfgInitialize(XGetfilterout *InstancePtr, XGetfilterout_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Axilites_BaseAddress = ConfigPtr->Axilites_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XGetfilterout_Start(XGetfilterout *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XGetfilterout_ReadReg(InstancePtr->Axilites_BaseAddress, XGETFILTEROUT_AXILITES_ADDR_AP_CTRL) & 0x80;
    XGetfilterout_WriteReg(InstancePtr->Axilites_BaseAddress, XGETFILTEROUT_AXILITES_ADDR_AP_CTRL, Data | 0x01);
}

u32 XGetfilterout_IsDone(XGetfilterout *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XGetfilterout_ReadReg(InstancePtr->Axilites_BaseAddress, XGETFILTEROUT_AXILITES_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XGetfilterout_IsIdle(XGetfilterout *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XGetfilterout_ReadReg(InstancePtr->Axilites_BaseAddress, XGETFILTEROUT_AXILITES_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XGetfilterout_IsReady(XGetfilterout *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XGetfilterout_ReadReg(InstancePtr->Axilites_BaseAddress, XGETFILTEROUT_AXILITES_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XGetfilterout_EnableAutoRestart(XGetfilterout *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XGetfilterout_WriteReg(InstancePtr->Axilites_BaseAddress, XGETFILTEROUT_AXILITES_ADDR_AP_CTRL, 0x80);
}

void XGetfilterout_DisableAutoRestart(XGetfilterout *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XGetfilterout_WriteReg(InstancePtr->Axilites_BaseAddress, XGETFILTEROUT_AXILITES_ADDR_AP_CTRL, 0);
}

void XGetfilterout_Set_depth(XGetfilterout *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XGetfilterout_WriteReg(InstancePtr->Axilites_BaseAddress, XGETFILTEROUT_AXILITES_ADDR_DEPTH_DATA, Data);
}

u32 XGetfilterout_Get_depth(XGetfilterout *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XGetfilterout_ReadReg(InstancePtr->Axilites_BaseAddress, XGETFILTEROUT_AXILITES_ADDR_DEPTH_DATA);
    return Data;
}

u32 XGetfilterout_Get_out_correct(XGetfilterout *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XGetfilterout_ReadReg(InstancePtr->Axilites_BaseAddress, XGETFILTEROUT_AXILITES_ADDR_OUT_CORRECT_DATA);
    return Data;
}

u32 XGetfilterout_Get_out_correct_vld(XGetfilterout *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XGetfilterout_ReadReg(InstancePtr->Axilites_BaseAddress, XGETFILTEROUT_AXILITES_ADDR_OUT_CORRECT_CTRL);
    return Data & 0x1;
}

u32 XGetfilterout_Get_inputs_BaseAddress(XGetfilterout *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Axilites_BaseAddress + XGETFILTEROUT_AXILITES_ADDR_INPUTS_BASE);
}

u32 XGetfilterout_Get_inputs_HighAddress(XGetfilterout *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Axilites_BaseAddress + XGETFILTEROUT_AXILITES_ADDR_INPUTS_HIGH);
}

u32 XGetfilterout_Get_inputs_TotalBytes(XGetfilterout *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XGETFILTEROUT_AXILITES_ADDR_INPUTS_HIGH - XGETFILTEROUT_AXILITES_ADDR_INPUTS_BASE + 1);
}

u32 XGetfilterout_Get_inputs_BitWidth(XGetfilterout *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XGETFILTEROUT_AXILITES_WIDTH_INPUTS;
}

u32 XGetfilterout_Get_inputs_Depth(XGetfilterout *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XGETFILTEROUT_AXILITES_DEPTH_INPUTS;
}

u32 XGetfilterout_Write_inputs_Words(XGetfilterout *InstancePtr, int offset, int *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XGETFILTEROUT_AXILITES_ADDR_INPUTS_HIGH - XGETFILTEROUT_AXILITES_ADDR_INPUTS_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Axilites_BaseAddress + XGETFILTEROUT_AXILITES_ADDR_INPUTS_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XGetfilterout_Read_inputs_Words(XGetfilterout *InstancePtr, int offset, int *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XGETFILTEROUT_AXILITES_ADDR_INPUTS_HIGH - XGETFILTEROUT_AXILITES_ADDR_INPUTS_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Axilites_BaseAddress + XGETFILTEROUT_AXILITES_ADDR_INPUTS_BASE + (offset + i)*4);
    }
    return length;
}

u32 XGetfilterout_Write_inputs_Bytes(XGetfilterout *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XGETFILTEROUT_AXILITES_ADDR_INPUTS_HIGH - XGETFILTEROUT_AXILITES_ADDR_INPUTS_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Axilites_BaseAddress + XGETFILTEROUT_AXILITES_ADDR_INPUTS_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XGetfilterout_Read_inputs_Bytes(XGetfilterout *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XGETFILTEROUT_AXILITES_ADDR_INPUTS_HIGH - XGETFILTEROUT_AXILITES_ADDR_INPUTS_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Axilites_BaseAddress + XGETFILTEROUT_AXILITES_ADDR_INPUTS_BASE + offset + i);
    }
    return length;
}

u32 XGetfilterout_Get_out_r_BaseAddress(XGetfilterout *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Axilites_BaseAddress + XGETFILTEROUT_AXILITES_ADDR_OUT_R_BASE);
}

u32 XGetfilterout_Get_out_r_HighAddress(XGetfilterout *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Axilites_BaseAddress + XGETFILTEROUT_AXILITES_ADDR_OUT_R_HIGH);
}

u32 XGetfilterout_Get_out_r_TotalBytes(XGetfilterout *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XGETFILTEROUT_AXILITES_ADDR_OUT_R_HIGH - XGETFILTEROUT_AXILITES_ADDR_OUT_R_BASE + 1);
}

u32 XGetfilterout_Get_out_r_BitWidth(XGetfilterout *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XGETFILTEROUT_AXILITES_WIDTH_OUT_R;
}

u32 XGetfilterout_Get_out_r_Depth(XGetfilterout *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XGETFILTEROUT_AXILITES_DEPTH_OUT_R;
}

u32 XGetfilterout_Write_out_r_Words(XGetfilterout *InstancePtr, int offset, int *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XGETFILTEROUT_AXILITES_ADDR_OUT_R_HIGH - XGETFILTEROUT_AXILITES_ADDR_OUT_R_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Axilites_BaseAddress + XGETFILTEROUT_AXILITES_ADDR_OUT_R_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XGetfilterout_Read_out_r_Words(XGetfilterout *InstancePtr, int offset, int *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XGETFILTEROUT_AXILITES_ADDR_OUT_R_HIGH - XGETFILTEROUT_AXILITES_ADDR_OUT_R_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Axilites_BaseAddress + XGETFILTEROUT_AXILITES_ADDR_OUT_R_BASE + (offset + i)*4);
    }
    return length;
}

u32 XGetfilterout_Write_out_r_Bytes(XGetfilterout *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XGETFILTEROUT_AXILITES_ADDR_OUT_R_HIGH - XGETFILTEROUT_AXILITES_ADDR_OUT_R_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Axilites_BaseAddress + XGETFILTEROUT_AXILITES_ADDR_OUT_R_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XGetfilterout_Read_out_r_Bytes(XGetfilterout *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XGETFILTEROUT_AXILITES_ADDR_OUT_R_HIGH - XGETFILTEROUT_AXILITES_ADDR_OUT_R_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Axilites_BaseAddress + XGETFILTEROUT_AXILITES_ADDR_OUT_R_BASE + offset + i);
    }
    return length;
}

void XGetfilterout_InterruptGlobalEnable(XGetfilterout *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XGetfilterout_WriteReg(InstancePtr->Axilites_BaseAddress, XGETFILTEROUT_AXILITES_ADDR_GIE, 1);
}

void XGetfilterout_InterruptGlobalDisable(XGetfilterout *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XGetfilterout_WriteReg(InstancePtr->Axilites_BaseAddress, XGETFILTEROUT_AXILITES_ADDR_GIE, 0);
}

void XGetfilterout_InterruptEnable(XGetfilterout *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XGetfilterout_ReadReg(InstancePtr->Axilites_BaseAddress, XGETFILTEROUT_AXILITES_ADDR_IER);
    XGetfilterout_WriteReg(InstancePtr->Axilites_BaseAddress, XGETFILTEROUT_AXILITES_ADDR_IER, Register | Mask);
}

void XGetfilterout_InterruptDisable(XGetfilterout *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XGetfilterout_ReadReg(InstancePtr->Axilites_BaseAddress, XGETFILTEROUT_AXILITES_ADDR_IER);
    XGetfilterout_WriteReg(InstancePtr->Axilites_BaseAddress, XGETFILTEROUT_AXILITES_ADDR_IER, Register & (~Mask));
}

void XGetfilterout_InterruptClear(XGetfilterout *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XGetfilterout_WriteReg(InstancePtr->Axilites_BaseAddress, XGETFILTEROUT_AXILITES_ADDR_ISR, Mask);
}

u32 XGetfilterout_InterruptGetEnabled(XGetfilterout *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XGetfilterout_ReadReg(InstancePtr->Axilites_BaseAddress, XGETFILTEROUT_AXILITES_ADDR_IER);
}

u32 XGetfilterout_InterruptGetStatus(XGetfilterout *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XGetfilterout_ReadReg(InstancePtr->Axilites_BaseAddress, XGETFILTEROUT_AXILITES_ADDR_ISR);
}

