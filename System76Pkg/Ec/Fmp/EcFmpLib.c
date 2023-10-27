// SPDX-License-Identifier: MPL-2.0
// SPDX-FileCopyrightText: 2023 System76, Inc.

#include <Guid/SystemResourceTable.h>
#include <Library/BaseMemoryLib.h>
#include <Library/FmpDeviceLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <LastAttemptStatus.h>

#define US_PER_MS 1000

EFI_STATUS
EFIAPI
RegisterFmpInstaller(
    IN FMP_DEVICE_LIB_REGISTER_FMP_INSTALLER FmpInstaller
) {
    return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
RegisterFmpUninstaller(
    IN FMP_DEVICE_LIB_REGISTER_FMP_UNINSTALLER FmpUninstaller
) {
    return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
FmpDeviceSetContext(
    IN EFI_HANDLE Handle,
    IN OUT VOID **Context
) {
    return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
FmpDeviceGetSize(
    OUT UINTN *Size
) {
    if (!Size)
        return EFI_INVALID_PARAMETER;

    // TODO
    *Size = 128 * 1024;
    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
FmpDeviceGetImageTypeIdGuidPtr(
    OUT EFI_GUID **Guid
) {
    if (!Guid)
        return EFI_INVALID_PARAMETER;

    return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
FmpDeviceGetAttributes(
    OUT UINT64 *Supported,
    OUT UINT64 *Setting
) {
    if (!Supported || !Setting)
        return EFI_INVALID_PARAMETER;

    *Supported = IMAGE_ATTRIBUTE_IMAGE_UPDATABLE
        | IMAGE_ATTRIBUTE_RESET_REQUIRED
        | IMAGE_ATTRIBUTE_IN_USE;

    *Setting = IMAGE_ATTRIBUTE_IMAGE_UPDATABLE
        | IMAGE_ATTRIBUTE_RESET_REQUIRED
        | IMAGE_ATTRIBUTE_IN_USE;

    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
FmpDeviceGetLowestSupportedVersion(
    OUT UINT32 *LowestSupportedVersion
) {
    return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
FmpDeviceGetVersionString(
    OUT CHAR16 **VersionString
) {
    if (!VersionString)
        return EFI_INVALID_PARAMETER;

    // TODO
    *VersionString = AllocatePool(sizeof(L"0.3"));
    if (!(*VersionString))
        return EFI_OUT_OF_RESOURCES;

    CopyMem(VersionString, L"0.3", sizeof(L"0.3"));

    //*VersionString = NULL;
    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
FmpDeviceGetVersion(
    OUT UINT32 *Version
) {
    if (!Version)
        return EFI_INVALID_PARAMETER;

    // TODO
    *Version = 3;
    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
FmpDeviceGetHardwareInstance(
    OUT UINT64 *HardwareInstance
) {
    return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
FmpDeviceGetImage(
    OUT VOID *Image,
    IN OUT UINTN *ImageSize
) {
    // TODO
    return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
FmpDeviceCheckImageWithStatus(
    IN CONST VOID *Image,
    IN UINTN ImageSize,
    OUT UINT32 *ImageUpdatable,
    OUT UINT32 *LastAttemptStatus
) {
    if (!LastAttemptStatus)
        return EFI_INVALID_PARAMETER;

    *LastAttemptStatus = LAST_ATTEMPT_STATUS_DEVICE_LIBRARY_MIN_ERROR_CODE_VALUE;

    if (!ImageUpdatable  || !Image)
        return EFI_INVALID_PARAMETER;

    // TODO:
    *LastAttemptStatus = LAST_ATTEMPT_STATUS_SUCCESS;
    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
FmpDeviceCheckImage(
    IN CONST VOID *Image,
    IN UINTN ImageSize,
    OUT UINT32 *ImageUpdatable
) {
    UINT32 LastAttemptStatus;

    return FmpDeviceCheckImageWithStatus(Image, ImageSize, ImageUpdatable, &LastAttemptStatus);
}

EFI_STATUS
EFIAPI
FmpDeviceSetImageWithStatus (
    IN CONST VOID *Image,
    IN UINTN ImageSize,
    IN CONST VOID *VendorCode, OPTIONAL
    IN EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS Progress, OPTIONAL
    IN UINT32 CapsuleFwVersion,
    OUT CHAR16 **AbortReason,
    OUT UINT32 *LastAttemptStatus
) {
    // TODO
    EFI_STATUS Status = EFI_SUCCESS;
    UINT32 Updateable = 0;

    Status = FmpDeviceCheckImageWithStatus(Image, ImageSize, &Updateable, LastAttemptStatus);
    if (EFI_ERROR(Status)) {
        goto cleanup;
    }

    if (Updateable != IMAGE_UPDATABLE_VALID) {
        Status = EFI_ABORTED;
        goto cleanup;
    }

    if (Progress == NULL) {
        Status = EFI_INVALID_PARAMETER;
        goto cleanup;
    }

    gBS->Stall (3000 * US_PER_MS);
    Progress(15);
    gBS->Stall (2000 * US_PER_MS);

    for (int p = 20; p < 100; p++) {
        gBS->Stall (100 * US_PER_MS);
        Progress (p);
    }

cleanup:
    if (EFI_ERROR (Status)) {
      *LastAttemptStatus = LAST_ATTEMPT_STATUS_DEVICE_LIBRARY_MIN_ERROR_CODE_VALUE;
    }

    return Status;
}

EFI_STATUS
EFIAPI
FmpDeviceSetImage(
    IN CONST VOID *Image,
    IN UINTN ImageSize,
    IN CONST VOID *VendorCode, OPTIONAL
    IN EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS Progress, OPTIONAL
    IN UINT32 CapsuleFwVersion,
    OUT CHAR16 **AbortReason
) {
    UINT32 LastAttemptStatus;

    return FmpDeviceSetImageWithStatus(Image, ImageSize, VendorCode, Progress, CapsuleFwVersion, AbortReason, &LastAttemptStatus);
}

EFI_STATUS
EFIAPI
FmpDeviceLock(
    VOID
) {
    return EFI_UNSUPPORTED;
}
