// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "WeaponInterface.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef WEAPON_WeaponInterface_generated_h
#error "WeaponInterface.generated.h already included, missing '#pragma once' in WeaponInterface.h"
#endif
#define WEAPON_WeaponInterface_generated_h

#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponInterface_h_13_SPARSE_DATA
#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponInterface_h_13_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponInterface_h_13_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponInterface_h_13_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponInterface_h_13_ACCESSORS
#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponInterface_h_13_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UWeaponInterface(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UWeaponInterface(UWeaponInterface&&); \
	NO_API UWeaponInterface(const UWeaponInterface&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UWeaponInterface); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UWeaponInterface); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UWeaponInterface) \
	NO_API virtual ~UWeaponInterface();


#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponInterface_h_13_GENERATED_UINTERFACE_BODY() \
private: \
	static void StaticRegisterNativesUWeaponInterface(); \
	friend struct Z_Construct_UClass_UWeaponInterface_Statics; \
public: \
	DECLARE_CLASS(UWeaponInterface, UInterface, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Interface), CASTCLASS_None, TEXT("/Script/Weapon"), NO_API) \
	DECLARE_SERIALIZER(UWeaponInterface)


#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponInterface_h_13_GENERATED_BODY \
	PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponInterface_h_13_GENERATED_UINTERFACE_BODY() \
	FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponInterface_h_13_ENHANCED_CONSTRUCTORS \
private: \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponInterface_h_13_INCLASS_IINTERFACE_NO_PURE_DECLS \
protected: \
	virtual ~IWeaponInterface() {} \
public: \
	typedef UWeaponInterface UClassType; \
	typedef IWeaponInterface ThisClass; \
	virtual UObject* _getUObject() const { return nullptr; }


#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponInterface_h_10_PROLOG
#define FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponInterface_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponInterface_h_13_SPARSE_DATA \
	FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponInterface_h_13_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponInterface_h_13_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponInterface_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponInterface_h_13_ACCESSORS \
	FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponInterface_h_13_INCLASS_IINTERFACE_NO_PURE_DECLS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> WEAPON_API UClass* StaticClass<class UWeaponInterface>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Work_ProjectJ_Plugins_Weapon_Source_Weapon_Public_WeaponInterface_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
