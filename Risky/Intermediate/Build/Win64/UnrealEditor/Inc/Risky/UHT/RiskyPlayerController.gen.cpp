// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Risky/RiskyPlayerController.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRiskyPlayerController() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_APlayerController();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
RISKY_API UClass* Z_Construct_UClass_ARiskyPlayerController();
RISKY_API UClass* Z_Construct_UClass_ARiskyPlayerController_NoRegister();
UPackage* Z_Construct_UPackage__Script_Risky();
// End Cross Module References

// Begin Class ARiskyPlayerController
void ARiskyPlayerController::StaticRegisterNativesARiskyPlayerController()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ARiskyPlayerController);
UClass* Z_Construct_UClass_ARiskyPlayerController_NoRegister()
{
	return ARiskyPlayerController::StaticClass();
}
struct Z_Construct_UClass_ARiskyPlayerController_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "RiskyPlayerController.h" },
		{ "ModuleRelativePath", "RiskyPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultMappingContext_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "RiskyPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MovementInput_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "RiskyPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_speed_MetaData[] = {
		{ "Category", "RiskyPlayerController" },
		{ "ModuleRelativePath", "RiskyPlayerController.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DefaultMappingContext;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MovementInput;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_speed;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ARiskyPlayerController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARiskyPlayerController_Statics::NewProp_DefaultMappingContext = { "DefaultMappingContext", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARiskyPlayerController, DefaultMappingContext), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultMappingContext_MetaData), NewProp_DefaultMappingContext_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARiskyPlayerController_Statics::NewProp_MovementInput = { "MovementInput", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARiskyPlayerController, MovementInput), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MovementInput_MetaData), NewProp_MovementInput_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ARiskyPlayerController_Statics::NewProp_speed = { "speed", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARiskyPlayerController, speed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_speed_MetaData), NewProp_speed_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ARiskyPlayerController_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARiskyPlayerController_Statics::NewProp_DefaultMappingContext,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARiskyPlayerController_Statics::NewProp_MovementInput,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARiskyPlayerController_Statics::NewProp_speed,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ARiskyPlayerController_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ARiskyPlayerController_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APlayerController,
	(UObject* (*)())Z_Construct_UPackage__Script_Risky,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ARiskyPlayerController_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ARiskyPlayerController_Statics::ClassParams = {
	&ARiskyPlayerController::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ARiskyPlayerController_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ARiskyPlayerController_Statics::PropPointers),
	0,
	0x008002A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ARiskyPlayerController_Statics::Class_MetaDataParams), Z_Construct_UClass_ARiskyPlayerController_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ARiskyPlayerController()
{
	if (!Z_Registration_Info_UClass_ARiskyPlayerController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ARiskyPlayerController.OuterSingleton, Z_Construct_UClass_ARiskyPlayerController_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ARiskyPlayerController.OuterSingleton;
}
template<> RISKY_API UClass* StaticClass<ARiskyPlayerController>()
{
	return ARiskyPlayerController::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ARiskyPlayerController);
ARiskyPlayerController::~ARiskyPlayerController() {}
// End Class ARiskyPlayerController

// Begin Registration
struct Z_CompiledInDeferFile_FID_Risky_Source_Risky_RiskyPlayerController_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ARiskyPlayerController, ARiskyPlayerController::StaticClass, TEXT("ARiskyPlayerController"), &Z_Registration_Info_UClass_ARiskyPlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ARiskyPlayerController), 3330006028U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Risky_Source_Risky_RiskyPlayerController_h_3783343919(TEXT("/Script/Risky"),
	Z_CompiledInDeferFile_FID_Risky_Source_Risky_RiskyPlayerController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Risky_Source_Risky_RiskyPlayerController_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
