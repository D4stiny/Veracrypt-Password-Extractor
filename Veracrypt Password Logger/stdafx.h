// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#ifdef MAX_PATH
#define TC_MAX_PATH		MAX_PATH
#else
#define TC_MAX_PATH		260	/* Includes the null terminator */
#endif

#define MAX_PASSWORD			64		// Maximum possible password length

typedef struct
{
	// Modifying this structure can introduce incompatibility with previous versions
	unsigned __int32 Length;
	unsigned char Text[MAX_PASSWORD + 1];
	char Pad[3]; // keep 64-bit alignment
} Password;

typedef struct
{
	int nReturnCode;					/* Return code back from driver */
	BOOL FilesystemDirty;
	BOOL VolumeMountedReadOnlyAfterAccessDenied;
	BOOL VolumeMountedReadOnlyAfterDeviceWriteProtected;

	wchar_t wszVolume[TC_MAX_PATH];		/* Volume to be mounted */
	Password VolumePassword;			/* User password */
	BOOL bCache;						/* Cache passwords in driver */
	int nDosDriveNo;					/* Drive number to mount */
	__int32 BytesPerSector;
	BOOL bMountReadOnly;				/* Mount volume in read-only mode */
	BOOL bMountRemovable;				/* Mount volume as removable media */
	BOOL bExclusiveAccess;				/* Open host file/device in exclusive access mode */
	BOOL bMountManager;					/* Announce volume to mount manager */
	BOOL bPreserveTimestamp;			/* Preserve file container timestamp */
	BOOL bPartitionInInactiveSysEncScope;		/* If TRUE, we are to attempt to mount a partition located on an encrypted system drive without pre-boot authentication. */
	int nPartitionInInactiveSysEncScopeDriveNo;	/* If bPartitionInInactiveSysEncScope is TRUE, this contains the drive number of the system drive on which the partition is located. */
	BOOL SystemFavorite;
	// Hidden volume protection
	BOOL bProtectHiddenVolume;			/* TRUE if the user wants the hidden volume within this volume to be protected against being overwritten (damaged) */
	Password ProtectedHidVolPassword;	/* Password to the hidden volume to be protected against overwriting */
	BOOL UseBackupHeader;
	BOOL RecoveryMode;
	int pkcs5_prf;
	int ProtectedHidVolPkcs5Prf;
	BOOL bTrueCryptMode;
	__int32 BytesPerPhysicalSector;
	int VolumePim;
	int ProtectedHidVolPim;
	wchar_t wszLabel[33]; // maximum label length is 32 for NTFS and 11 for FAT32
	BOOL bIsNTFS; // output only
	BOOL bDriverSetLabel;
	BOOL bCachePim;
	ULONG MaximumTransferLength;
	ULONG MaximumPhysicalPages;
	ULONG AlignmentMask;
} MOUNT_STRUCT;

// TODO: reference additional headers your program requires here
