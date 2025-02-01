// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Risky/RiskyGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRiskyGameMode() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
RISKY_API UClass* Z_Construct_UClass_ARiskyGameMode();
RISKY_API UClass* Z_Construct_UClass_ARiskyGameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_Risky();
// End Cross Module References

// Begin Class ARiskyGameMode
void ARiskyGameMode::StaticRegisterNativesARiskyGameMode()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ARiskyGameMode);
UClass* Z_Construct_UClass_ARiskyGameMode_NoRegister()
{
	return ARiskyGameMode::StaticClass();
}
struct Z_Construct_UClass_ARiskyGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "RiskyGameMode.h" },
		{ "ModuleRelativePath", "RiskyGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ARiskyGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ARiskyGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_Risky,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ARiskyGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ARiskyGameMode_Statics::ClassParams = {
	&ARiskyGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008802ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ARiskyGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ARiskyGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ARiskyGameMode()
{
	if (!Z_Registration_Info_UClass_ARiskyGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ARiskyGameMode.OuterSingleton, Z_Construct_UClass_ARiskyGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ARiskyGameMode.OuterSingleton;
}
template<> RISKY_API UClass* StaticClass<ARiskyGameMode>()
{
	return ARiskyGameMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ARiskyGameMode);
ARiskyGameMode::~ARiskyGameMode() {}
// End Class ARiskyGameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_Risky_Source_Risky_RiskyGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ARiskyGameMode, ARiskyGameMode::StaticClass, TEXT("ARiskyGameMode"), &Z_Registration_Info_UClass_ARiskyGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ARiskyGameMode), 3252349725U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Risky_Source_Risky_RiskyGameMode_h_3350853102(TEXT("/Script/Risky"),
	Z_CompiledInDeferFile_FID_Risky_Source_Risky_RiskyGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Risky_Source_Risky_RiskyGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
