// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "WeaponBase.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef WEAPON_WeaponBase_generated_h
#error "WeaponBase.generated.h already included, missing '#pragma once' in WeaponBase.h"
#endif
#define WEAPON_WeaponBase_generated_h

#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_27_SPARSE_DATA
#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_27_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_27_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_27_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execDropWeapon); \
	DECLARE_FUNCTION(execEquipWeapon_Multicast); \
	DECLARE_FUNCTION(execEquipWeapon);


#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_27_ACCESSORS
#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_27_CALLBACK_WRAPPERS
#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_27_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAWeaponBase(); \
	friend struct Z_Construct_UClass_AWeaponBase_Statics; \
public: \
	DECLARE_CLASS(AWeaponBase, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Weapon"), NO_API) \
	DECLARE_SERIALIZER(AWeaponBase) \
	virtual UObject* _getUObject() const override { return const_cast<AWeaponBase*>(this); }


#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_27_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AWeaponBase(AWeaponBase&&); \
	NO_API AWeaponBase(const AWeaponBase&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AWeaponBase); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AWeaponBase); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AWeaponBase) \
	NO_API virtual ~AWeaponBase();


#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_24_PROLOG
#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_27_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_27_SPARSE_DATA \
	FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_27_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_27_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_27_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_27_ACCESSORS \
	FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_27_CALLBACK_WRAPPERS \
	FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_27_INCLASS_NO_PURE_DECLS \
	FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h_27_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> WEAPON_API UClass* StaticClass<class AWeaponBase>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponBase_h


#define FOREACH_ENUM_EWEAPONTYPE(op) \
	op(EWeaponType::ShotGun) \
	op(EWeaponType::AssaultRifle) 

enum class EWeaponType : uint8;
template<> struct TIsUEnumClass<EWeaponType> { enum { Value = true }; };
template<> WEAPON_API UEnum* StaticEnum<EWeaponType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
