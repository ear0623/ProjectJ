// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Weapon/Public/AmmoBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAmmoBase() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
	UPackage* Z_Construct_UPackage__Script_Weapon();
	WEAPON_API UClass* Z_Construct_UClass_AAmmoBase();
	WEAPON_API UClass* Z_Construct_UClass_AAmmoBase_NoRegister();
	WEAPON_API UEnum* Z_Construct_UEnum_Weapon_EBulletType();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EBulletType;
	static UEnum* EBulletType_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EBulletType.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EBulletType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Weapon_EBulletType, (UObject*)Z_Construct_UPackage__Script_Weapon(), TEXT("EBulletType"));
		}
		return Z_Registration_Info_UEnum_EBulletType.OuterSingleton;
	}
	template<> WEAPON_API UEnum* StaticEnum<EBulletType>()
	{
		return EBulletType_StaticEnum();
	}
	struct Z_Construct_UEnum_Weapon_EBulletType_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_Weapon_EBulletType_Statics::Enumerators[] = {
		{ "EBulletType::AR_5", (int64)EBulletType::AR_5 },
		{ "EBulletType::AR_7", (int64)EBulletType::AR_7 },
		{ "EBulletType::AR_9", (int64)EBulletType::AR_9 },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_Weapon_EBulletType_Statics::Enum_MetaDataParams[] = {
		{ "AR_5.DisplayName", "5.56mm" },
		{ "AR_5.Name", "EBulletType::AR_5" },
		{ "AR_7.DisplayName", "7.62mm" },
		{ "AR_7.Name", "EBulletType::AR_7" },
		{ "AR_9.DisplayName", "9mm" },
		{ "AR_9.Name", "EBulletType::AR_9" },
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/AmmoBase.h" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Weapon_EBulletType_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_Weapon,
		nullptr,
		"EBulletType",
		"EBulletType",
		Z_Construct_UEnum_Weapon_EBulletType_Statics::Enumerators,
		RF_Public|RF_Transient|RF_MarkAsNative,
		UE_ARRAY_COUNT(Z_Construct_UEnum_Weapon_EBulletType_Statics::Enumerators),
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_Weapon_EBulletType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_Weapon_EBulletType_Statics::Enum_MetaDataParams)
	};
	UEnum* Z_Construct_UEnum_Weapon_EBulletType()
	{
		if (!Z_Registration_Info_UEnum_EBulletType.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EBulletType.InnerSingleton, Z_Construct_UEnum_Weapon_EBulletType_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EBulletType.InnerSingleton;
	}
	void AAmmoBase::StaticRegisterNativesAAmmoBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AAmmoBase);
	UClass* Z_Construct_UClass_AAmmoBase_NoRegister()
	{
		return AAmmoBase::StaticClass();
	}
	struct Z_Construct_UClass_AAmmoBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AmmoMesh_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_AmmoMesh;
		static const UECodeGen_Private::FBytePropertyParams NewProp_AmmoType_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AmmoType_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_AmmoType;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AAmmoBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_Weapon,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AAmmoBase_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAmmoBase_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "AmmoBase.h" },
		{ "ModuleRelativePath", "Public/AmmoBase.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAmmoBase_Statics::NewProp_AmmoMesh_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "WeaponComponents" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "////////Component///////////////////////////////////////////////////////////////////\n//\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/AmmoBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Component/\n\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_AAmmoBase_Statics::NewProp_AmmoMesh = { "AmmoMesh", nullptr, (EPropertyFlags)0x004400000008001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAmmoBase, AmmoMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AAmmoBase_Statics::NewProp_AmmoMesh_MetaData), Z_Construct_UClass_AAmmoBase_Statics::NewProp_AmmoMesh_MetaData) };
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AAmmoBase_Statics::NewProp_AmmoType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAmmoBase_Statics::NewProp_AmmoType_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "WeaponComponents" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc5\xb8\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Public/AmmoBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc5\xb8\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AAmmoBase_Statics::NewProp_AmmoType = { "AmmoType", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAmmoBase, AmmoType), Z_Construct_UEnum_Weapon_EBulletType, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AAmmoBase_Statics::NewProp_AmmoType_MetaData), Z_Construct_UClass_AAmmoBase_Statics::NewProp_AmmoType_MetaData) }; // 234718900
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AAmmoBase_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAmmoBase_Statics::NewProp_AmmoMesh,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAmmoBase_Statics::NewProp_AmmoType_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAmmoBase_Statics::NewProp_AmmoType,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AAmmoBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AAmmoBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AAmmoBase_Statics::ClassParams = {
		&AAmmoBase::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AAmmoBase_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AAmmoBase_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AAmmoBase_Statics::Class_MetaDataParams), Z_Construct_UClass_AAmmoBase_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AAmmoBase_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_AAmmoBase()
	{
		if (!Z_Registration_Info_UClass_AAmmoBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AAmmoBase.OuterSingleton, Z_Construct_UClass_AAmmoBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AAmmoBase.OuterSingleton;
	}
	template<> WEAPON_API UClass* StaticClass<AAmmoBase>()
	{
		return AAmmoBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AAmmoBase);
	AAmmoBase::~AAmmoBase() {}
	struct Z_CompiledInDeferFile_FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_AmmoBase_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_AmmoBase_h_Statics::EnumInfo[] = {
		{ EBulletType_StaticEnum, TEXT("EBulletType"), &Z_Registration_Info_UEnum_EBulletType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 234718900U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_AmmoBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AAmmoBase, AAmmoBase::StaticClass, TEXT("AAmmoBase"), &Z_Registration_Info_UClass_AAmmoBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AAmmoBase), 829011953U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_AmmoBase_h_865251301(TEXT("/Script/Weapon"),
		Z_CompiledInDeferFile_FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_AmmoBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_AmmoBase_h_Statics::ClassInfo),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_AmmoBase_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_AmmoBase_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
