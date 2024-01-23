// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xgetfilterout.h"

extern XGetfilterout_Config XGetfilterout_ConfigTable[];

XGetfilterout_Config *XGetfilterout_LookupConfig(u16 DeviceId) {
	XGetfilterout_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XGETFILTEROUT_NUM_INSTANCES; Index++) {
		if (XGetfilterout_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XGetfilterout_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XGetfilterout_Initialize(XGetfilterout *InstancePtr, u16 DeviceId) {
	XGetfilterout_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XGetfilterout_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XGetfilterout_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

