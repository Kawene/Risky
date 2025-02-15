// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "RiskyPlayerController.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef RISKY_RiskyPlayerController_generated_h
#error "RiskyPlayerController.generated.h already included, missing '#pragma once' in RiskyPlayerController.h"
#endif
#define RISKY_RiskyPlayerController_generated_h

#define FID_Risky_Source_Risky_RiskyPlayerController_h_21_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesARiskyPlayerController(); \
	friend struct Z_Construct_UClass_ARiskyPlayerController_Statics; \
public: \
	DECLARE_CLASS(ARiskyPlayerController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Risky"), NO_API) \
	DECLARE_SERIALIZER(ARiskyPlayerController)


#define FID_Risky_Source_Risky_RiskyPlayerController_h_21_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	ARiskyPlayerController(ARiskyPlayerController&&); \
	ARiskyPlayerController(const ARiskyPlayerController&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ARiskyPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ARiskyPlayerController); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ARiskyPlayerController) \
	NO_API virtual ~ARiskyPlayerController();


#define FID_Risky_Source_Risky_RiskyPlayerController_h_18_PROLOG
#define FID_Risky_Source_Risky_RiskyPlayerController_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Risky_Source_Risky_RiskyPlayerController_h_21_INCLASS_NO_PURE_DECLS \
	FID_Risky_Source_Risky_RiskyPlayerController_h_21_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> RISKY_API UClass* StaticClass<class ARiskyPlayerController>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Risky_Source_Risky_RiskyPlayerController_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
