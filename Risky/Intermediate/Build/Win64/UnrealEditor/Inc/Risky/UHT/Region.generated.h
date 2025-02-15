// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Region.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class ACharacter;
class ARegion;
#ifdef RISKY_Region_generated_h
#error "Region.generated.h already included, missing '#pragma once' in Region.h"
#endif
#define RISKY_Region_generated_h

#define FID_Risky_Source_Risky_Public_Region_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execDecreaseUnitCount); \
	DECLARE_FUNCTION(execDeployUnits); \
	DECLARE_FUNCTION(execChangeOwnerShip); \
	DECLARE_FUNCTION(execGetBorderingRegions); \
	DECLARE_FUNCTION(execGetRegionOwner); \
	DECLARE_FUNCTION(execGetUnits);


#define FID_Risky_Source_Risky_Public_Region_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesARegion(); \
	friend struct Z_Construct_UClass_ARegion_Statics; \
public: \
	DECLARE_CLASS(ARegion, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Risky"), NO_API) \
	DECLARE_SERIALIZER(ARegion)


#define FID_Risky_Source_Risky_Public_Region_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	ARegion(ARegion&&); \
	ARegion(const ARegion&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ARegion); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ARegion); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ARegion) \
	NO_API virtual ~ARegion();


#define FID_Risky_Source_Risky_Public_Region_h_9_PROLOG
#define FID_Risky_Source_Risky_Public_Region_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Risky_Source_Risky_Public_Region_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Risky_Source_Risky_Public_Region_h_12_INCLASS_NO_PURE_DECLS \
	FID_Risky_Source_Risky_Public_Region_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> RISKY_API UClass* StaticClass<class ARegion>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Risky_Source_Risky_Public_Region_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
