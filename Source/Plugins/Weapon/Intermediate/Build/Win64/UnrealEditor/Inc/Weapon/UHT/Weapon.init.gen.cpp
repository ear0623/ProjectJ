// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWeapon_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_Weapon;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_Weapon()
	{
		if (!Z_Registration_Info_UPackage__Script_Weapon.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/Weapon",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0xF422A6F1,
				0xD2E274D3,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_Weapon.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_Weapon.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_Weapon(Z_Construct_UPackage__Script_Weapon, TEXT("/Script/Weapon"), Z_Registration_Info_UPackage__Script_Weapon, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xF422A6F1, 0xD2E274D3));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
