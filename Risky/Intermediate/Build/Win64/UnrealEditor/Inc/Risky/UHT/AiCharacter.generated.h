// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "AiCharacter.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef RISKY_AiCharacter_generated_h
#error "AiCharacter.generated.h already included, missing '#pragma once' in AiCharacter.h"
#endif
#define RISKY_AiCharacter_generated_h

#define FID_Risky_Source_Risky_Public_AiCharacter_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAAiCharacter(); \
	friend struct Z_Construct_UClass_AAiCharacter_Statics; \
public: \
	DECLARE_CLASS(AAiCharacter, ABaseCharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Risky"), NO_API) \
	DECLARE_SERIALIZER(AAiCharacter)


#define FID_Risky_Source_Risky_Public_AiCharacter_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AAiCharacter(); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AAiCharacter(AAiCharacter&&); \
	AAiCharacter(const AAiCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AAiCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AAiCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AAiCharacter) \
	NO_API virtual ~AAiCharacter();


#define FID_Risky_Source_Risky_Public_AiCharacter_h_12_PROLOG
#define FID_Risky_Source_Risky_Public_AiCharacter_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Risky_Source_Risky_Public_AiCharacter_h_15_INCLASS_NO_PURE_DECLS \
	FID_Risky_Source_Risky_Public_AiCharacter_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> RISKY_API UClass* StaticClass<class AAiCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Risky_Source_Risky_Public_AiCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
