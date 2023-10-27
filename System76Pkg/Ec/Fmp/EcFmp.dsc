# SPDX-License-Identifier: MPL-2.0
# SPDX-FileCopyrightText: 2023 System76, Inc.

FmpDevicePkg/FmpDxe/FmpDxe.inf {
  <Defines>
    FILE_GUID = $(EC_FMP_ESRT_GUID)
  <PcdsFixedAtBuild>
    gFmpDevicePkgTokenSpaceGuid.PcdFmpDeviceImageIdName|L"System76 EC"
    gFmpDevicePkgTokenSpaceGuid.PcdFmpDeviceBuildTimeLowestSupportedVersion|0
    gFmpDevicePkgTokenSpaceGuid.PcdFmpDeviceProgressWatchdogTimeInSeconds|0
    gFmpDevicePkgTokenSpaceGuid.PcdFmpDeviceProgressColor|0x00FBB86C
  <LibraryClasses>
    FmpPayloadHeaderLib|FmpDevicePkg/Library/FmpPayloadHeaderLibV1/FmpPayloadHeaderLibV1.inf
    FmpAuthenticationLib|MdeModulePkg/Library/FmpAuthenticationLibNull/FmpAuthenticationLibNull.inf
    FmpDependencyLib|FmpDevicePkg/Library/FmpDependencyLib/FmpDependencyLib.inf
    FmpDependencyCheckLib|FmpDevicePkg/Library/FmpDependencyCheckLibNull/FmpDependencyCheckLibNull.inf
    FmpDependencyDeviceLib|FmpDevicePkg/Library/FmpDependencyDeviceLibNull/FmpDependencyDeviceLibNull.inf
    CapsuleUpdatePolicyLib|FmpDevicePkg/Library/CapsuleUpdatePolicyLibNull/CapsuleUpdatePolicyLibNull.inf

    FmpDeviceLib|System76Pkg/Ec/Fmp/EcFmpLib.inf
}
