// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Weapon/Public/WeaponBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWeaponBase() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UParticleSystem_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USphereComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
	UPackage* Z_Construct_UPackage__Script_Weapon();
	WEAPON_API UClass* Z_Construct_UClass_AWeaponBase();
	WEAPON_API UClass* Z_Construct_UClass_AWeaponBase_NoRegister();
	WEAPON_API UClass* Z_Construct_UClass_UWeaponInterface_NoRegister();
	WEAPON_API UEnum* Z_Construct_UEnum_Weapon_EWeaponType();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EWeaponType;
	static UEnum* EWeaponType_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EWeaponType.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EWeaponType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Weapon_EWeaponType, (UObject*)Z_Construct_UPackage__Script_Weapon(), TEXT("EWeaponType"));
		}
		return Z_Registration_Info_UEnum_EWeaponType.OuterSingleton;
	}
	template<> WEAPON_API UEnum* StaticEnum<EWeaponType>()
	{
		return EWeaponType_StaticEnum();
	}
	struct Z_Construct_UEnum_Weapon_EWeaponType_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_Weapon_EWeaponType_Statics::Enumerators[] = {
		{ "EWeaponType::ShotGun", (int64)EWeaponType::ShotGun },
		{ "EWeaponType::AssaultRifle", (int64)EWeaponType::AssaultRifle },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_Weapon_EWeaponType_Statics::Enum_MetaDataParams[] = {
		{ "AssaultRifle.DisplayName", "AR" },
		{ "AssaultRifle.Name", "EWeaponType::AssaultRifle" },
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/WeaponBase.h" },
		{ "ShotGun.DisplayName", "SG" },
		{ "ShotGun.Name", "EWeaponType::ShotGun" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Weapon_EWeaponType_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_Weapon,
		nullptr,
		"EWeaponType",
		"EWeaponType",
		Z_Construct_UEnum_Weapon_EWeaponType_Statics::Enumerators,
		RF_Public|RF_Transient|RF_MarkAsNative,
		UE_ARRAY_COUNT(Z_Construct_UEnum_Weapon_EWeaponType_Statics::Enumerators),
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_Weapon_EWeaponType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_Weapon_EWeaponType_Statics::Enum_MetaDataParams)
	};
	UEnum* Z_Construct_UEnum_Weapon_EWeaponType()
	{
		if (!Z_Registration_Info_UEnum_EWeaponType.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EWeaponType.InnerSingleton, Z_Construct_UEnum_Weapon_EWeaponType_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EWeaponType.InnerSingleton;
	}
	DEFINE_FUNCTION(AWeaponBase::execDropWeapon)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DropWeapon_Implementation();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AWeaponBase::execEquipWeapon_Multicast)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->EquipWeapon_Multicast_Implementation();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AWeaponBase::execEquipWeapon)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->EquipWeapon_Implementation();
		P_NATIVE_END;
	}
	static FName NAME_AWeaponBase_DropWeapon = FName(TEXT("DropWeapon"));
	void AWeaponBase::DropWeapon()
	{
		ProcessEvent(FindFunctionChecked(NAME_AWeaponBase_DropWeapon),NULL);
	}
	static FName NAME_AWeaponBase_EquipWeapon = FName(TEXT("EquipWeapon"));
	void AWeaponBase::EquipWeapon()
	{
		ProcessEvent(FindFunctionChecked(NAME_AWeaponBase_EquipWeapon),NULL);
	}
	static FName NAME_AWeaponBase_EquipWeapon_Multicast = FName(TEXT("EquipWeapon_Multicast"));
	void AWeaponBase::EquipWeapon_Multicast()
	{
		ProcessEvent(FindFunctionChecked(NAME_AWeaponBase_EquipWeapon_Multicast),NULL);
	}
	void AWeaponBase::StaticRegisterNativesAWeaponBase()
	{
		UClass* Class = AWeaponBase::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "DropWeapon", &AWeaponBase::execDropWeapon },
			{ "EquipWeapon", &AWeaponBase::execEquipWeapon },
			{ "EquipWeapon_Multicast", &AWeaponBase::execEquipWeapon_Multicast },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AWeaponBase_DropWeapon_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AWeaponBase_DropWeapon_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/WeaponBase.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AWeaponBase_DropWeapon_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AWeaponBase, nullptr, "DropWeapon", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AWeaponBase_DropWeapon_Statics::Function_MetaDataParams), Z_Construct_UFunction_AWeaponBase_DropWeapon_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_AWeaponBase_DropWeapon()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AWeaponBase_DropWeapon_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AWeaponBase_EquipWeapon_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AWeaponBase_EquipWeapon_Statics::Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/////////\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd///////////////////////////////////////////////////////////////////\n" },
#endif
		{ "ModuleRelativePath", "Public/WeaponBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd/" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AWeaponBase_EquipWeapon_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AWeaponBase, nullptr, "EquipWeapon", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00220CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AWeaponBase_EquipWeapon_Statics::Function_MetaDataParams), Z_Construct_UFunction_AWeaponBase_EquipWeapon_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_AWeaponBase_EquipWeapon()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AWeaponBase_EquipWeapon_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AWeaponBase_EquipWeapon_Multicast_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AWeaponBase_EquipWeapon_Multicast_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/WeaponBase.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AWeaponBase_EquipWeapon_Multicast_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AWeaponBase, nullptr, "EquipWeapon_Multicast", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00024CC0, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AWeaponBase_EquipWeapon_Multicast_Statics::Function_MetaDataParams), Z_Construct_UFunction_AWeaponBase_EquipWeapon_Multicast_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_AWeaponBase_EquipWeapon_Multicast()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AWeaponBase_EquipWeapon_Multicast_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AWeaponBase);
	UClass* Z_Construct_UClass_AWeaponBase_NoRegister()
	{
		return AWeaponBase::StaticClass();
	}
	struct Z_Construct_UClass_AWeaponBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_WeaponMesh_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_WeaponMesh;
		static const UECodeGen_Private::FBytePropertyParams NewProp_WeaponType_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_WeaponType_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_WeaponType;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SphereCollision_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_SphereCollision;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TriggerEffect_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_TriggerEffect;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OwnedCharacter_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_OwnedCharacter;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AWeaponBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_Weapon,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AWeaponBase_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_AWeaponBase_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AWeaponBase_DropWeapon, "DropWeapon" }, // 726939960
		{ &Z_Construct_UFunction_AWeaponBase_EquipWeapon, "EquipWeapon" }, // 2300819567
		{ &Z_Construct_UFunction_AWeaponBase_EquipWeapon_Multicast, "EquipWeapon_Multicast" }, // 203810444
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AWeaponBase_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWeaponBase_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "WeaponBase.h" },
		{ "ModuleRelativePath", "Public/WeaponBase.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWeaponBase_Statics::NewProp_WeaponMesh_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "WeaponComponents" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "////////Component///////////////////////////////////////////////////////////////////\n//\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/WeaponBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Component/\n\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_AWeaponBase_Statics::NewProp_WeaponMesh = { "WeaponMesh", nullptr, (EPropertyFlags)0x004400000008001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWeaponBase, WeaponMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWeaponBase_Statics::NewProp_WeaponMesh_MetaData), Z_Construct_UClass_AWeaponBase_Statics::NewProp_WeaponMesh_MetaData) };
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AWeaponBase_Statics::NewProp_WeaponType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWeaponBase_Statics::NewProp_WeaponType_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "WeaponComponents" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc5\xb8\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Public/WeaponBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc5\xb8\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AWeaponBase_Statics::NewProp_WeaponType = { "WeaponType", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWeaponBase, WeaponType), Z_Construct_UEnum_Weapon_EWeaponType, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWeaponBase_Statics::NewProp_WeaponType_MetaData), Z_Construct_UClass_AWeaponBase_Statics::NewProp_WeaponType_MetaData) }; // 2745359555
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWeaponBase_Statics::NewProp_SphereCollision_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "WeaponComponents" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//\xef\xbf\xbd\xdd\xb8\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd//\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/WeaponBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xdd\xb8\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_AWeaponBase_Statics::NewProp_SphereCollision = { "SphereCollision", nullptr, (EPropertyFlags)0x004400000008001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWeaponBase, SphereCollision), Z_Construct_UClass_USphereComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWeaponBase_Statics::NewProp_SphereCollision_MetaData), Z_Construct_UClass_AWeaponBase_Statics::NewProp_SphereCollision_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWeaponBase_Statics::NewProp_TriggerEffect_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Variable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "////////Variable/////////////////////////////////////////////////////////////////////\n" },
#endif
		{ "ModuleRelativePath", "Public/WeaponBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Variable" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_AWeaponBase_Statics::NewProp_TriggerEffect = { "TriggerEffect", nullptr, (EPropertyFlags)0x0044000000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWeaponBase, TriggerEffect), Z_Construct_UClass_UParticleSystem_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWeaponBase_Statics::NewProp_TriggerEffect_MetaData), Z_Construct_UClass_AWeaponBase_Statics::NewProp_TriggerEffect_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWeaponBase_Statics::NewProp_OwnedCharacter_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Variable" },
		{ "ModuleRelativePath", "Public/WeaponBase.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_AWeaponBase_Statics::NewProp_OwnedCharacter = { "OwnedCharacter", nullptr, (EPropertyFlags)0x0014000000000014, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWeaponBase, OwnedCharacter), Z_Construct_UClass_ACharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWeaponBase_Statics::NewProp_OwnedCharacter_MetaData), Z_Construct_UClass_AWeaponBase_Statics::NewProp_OwnedCharacter_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AWeaponBase_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWeaponBase_Statics::NewProp_WeaponMesh,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWeaponBase_Statics::NewProp_WeaponType_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWeaponBase_Statics::NewProp_WeaponType,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWeaponBase_Statics::NewProp_SphereCollision,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWeaponBase_Statics::NewProp_TriggerEffect,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWeaponBase_Statics::NewProp_OwnedCharacter,
	};
		const UECodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_AWeaponBase_Statics::InterfaceParams[] = {
			{ Z_Construct_UClass_UWeaponInterface_NoRegister, (int32)VTABLE_OFFSET(AWeaponBase, IWeaponInterface), false },  // 111292206
		};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AWeaponBase_Statics::InterfaceParams) < 64);
	const FCppClassTypeInfoStatic Z_Construct_UClass_AWeaponBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AWeaponBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AWeaponBase_Statics::ClassParams = {
		&AWeaponBase::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_AWeaponBase_Statics::PropPointers,
		InterfaceParams,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_AWeaponBase_Statics::PropPointers),
		UE_ARRAY_COUNT(InterfaceParams),
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWeaponBase_Statics::Class_MetaDataParams), Z_Construct_UClass_AWeaponBase_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AWeaponBase_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_AWeaponBase()
	{
		if (!Z_Registration_Info_UClass_AWeaponBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AWeaponBase.OuterSingleton, Z_Construct_UClass_AWeaponBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AWeaponBase.OuterSingleton;
	}
	template<> WEAPON_API UClass* StaticClass<AWeaponBase>()
	{
		return AWeaponBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AWeaponBase);
	AWeaponBase::~AWeaponBase() {}
	struct Z_CompiledInDeferFile_FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_Statics::EnumInfo[] = {
		{ EWeaponType_StaticEnum, TEXT("EWeaponType"), &Z_Registration_Info_UEnum_EWeaponType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2745359555U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AWeaponBase, AWeaponBase::StaticClass, TEXT("AWeaponBase"), &Z_Registration_Info_UClass_AWeaponBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AWeaponBase), 1878901851U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_3700418245(TEXT("/Script/Weapon"),
		Z_CompiledInDeferFile_FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_Statics::ClassInfo),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
