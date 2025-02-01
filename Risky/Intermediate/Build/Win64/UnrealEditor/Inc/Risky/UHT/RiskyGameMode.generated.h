// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "RiskyGameMode.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef RISKY_RiskyGameMode_generated_h
#error "RiskyGameMode.generated.h already included, missing '#pragma once' in RiskyGameMode.h"
#endif
#define RISKY_RiskyGameMode_generated_h

#define FID_Risky_Source_Risky_RiskyGameMode_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesARiskyGameMode(); \
	friend struct Z_Construct_UClass_ARiskyGameMode_Statics; \
public: \
	DECLARE_CLASS(ARiskyGameMode, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/Risky"), RISKY_API) \
	DECLARE_SERIALIZER(ARiskyGameMode)


#define FID_Risky_Source_Risky_RiskyGameMode_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	ARiskyGameMode(ARiskyGameMode&&); \
	ARiskyGameMode(const ARiskyGameMode&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(RISKY_API, ARiskyGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ARiskyGameMode); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ARiskyGameMode) \
	RISKY_API virtual ~ARiskyGameMode();


#define FID_Risky_Source_Risky_RiskyGameMode_h_9_PROLOG
#define FID_Risky_Source_Risky_RiskyGameMode_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Risky_Source_Risky_RiskyGameMode_h_12_INCLASS_NO_PURE_DECLS \
	FID_Risky_Source_Risky_RiskyGameMode_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> RISKY_API UClass* StaticClass<class ARiskyGameMode>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Risky_Source_Risky_RiskyGameMode_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
