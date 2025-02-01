// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "RiskyCharacter.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef RISKY_RiskyCharacter_generated_h
#error "RiskyCharacter.generated.h already included, missing '#pragma once' in RiskyCharacter.h"
#endif
#define RISKY_RiskyCharacter_generated_h

#define FID_Risky_Source_Risky_RiskyCharacter_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesARiskyCharacter(); \
	friend struct Z_Construct_UClass_ARiskyCharacter_Statics; \
public: \
	DECLARE_CLASS(ARiskyCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Risky"), NO_API) \
	DECLARE_SERIALIZER(ARiskyCharacter)


#define FID_Risky_Source_Risky_RiskyCharacter_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	ARiskyCharacter(ARiskyCharacter&&); \
	ARiskyCharacter(const ARiskyCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ARiskyCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ARiskyCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ARiskyCharacter) \
	NO_API virtual ~ARiskyCharacter();


#define FID_Risky_Source_Risky_RiskyCharacter_h_9_PROLOG
#define FID_Risky_Source_Risky_RiskyCharacter_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Risky_Source_Risky_RiskyCharacter_h_12_INCLASS_NO_PURE_DECLS \
	FID_Risky_Source_Risky_RiskyCharacter_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> RISKY_API UClass* StaticClass<class ARiskyCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Risky_Source_Risky_RiskyCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
