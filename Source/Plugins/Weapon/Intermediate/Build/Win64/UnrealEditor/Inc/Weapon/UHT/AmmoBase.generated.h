// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "AmmoBase.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef WEAPON_AmmoBase_generated_h
#error "AmmoBase.generated.h already included, missing '#pragma once' in AmmoBase.h"
#endif
#define WEAPON_AmmoBase_generated_h

#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_AmmoBase_h_22_SPARSE_DATA
#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_AmmoBase_h_22_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_AmmoBase_h_22_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_AmmoBase_h_22_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_AmmoBase_h_22_ACCESSORS
#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_AmmoBase_h_22_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAAmmoBase(); \
	friend struct Z_Construct_UClass_AAmmoBase_Statics; \
public: \
	DECLARE_CLASS(AAmmoBase, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Weapon"), NO_API) \
	DECLARE_SERIALIZER(AAmmoBase)


#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_AmmoBase_h_22_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AAmmoBase(AAmmoBase&&); \
	NO_API AAmmoBase(const AAmmoBase&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AAmmoBase); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AAmmoBase); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AAmmoBase) \
	NO_API virtual ~AAmmoBase();


#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_AmmoBase_h_19_PROLOG
#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_AmmoBase_h_22_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_AmmoBase_h_22_SPARSE_DATA \
	FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_AmmoBase_h_22_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_AmmoBase_h_22_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_AmmoBase_h_22_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_AmmoBase_h_22_ACCESSORS \
	FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_AmmoBase_h_22_INCLASS_NO_PURE_DECLS \
	FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_AmmoBase_h_22_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> WEAPON_API UClass* StaticClass<class AAmmoBase>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_AmmoBase_h


#define FOREACH_ENUM_EBULLETTYPE(op) \
	op(EBulletType::AR_5) \
	op(EBulletType::AR_7) \
	op(EBulletType::AR_9) 

enum class EBulletType : uint8;
template<> struct TIsUEnumClass<EBulletType> { enum { Value = true }; };
template<> WEAPON_API UEnum* StaticEnum<EBulletType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
