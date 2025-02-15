// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Risky/Public/AiCharacter.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAiCharacter() {}

// Begin Cross Module References
RISKY_API UClass* Z_Construct_UClass_AAiCharacter();
RISKY_API UClass* Z_Construct_UClass_AAiCharacter_NoRegister();
RISKY_API UClass* Z_Construct_UClass_ABaseCharacter();
UPackage* Z_Construct_UPackage__Script_Risky();
// End Cross Module References

// Begin Class AAiCharacter
void AAiCharacter::StaticRegisterNativesAAiCharacter()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AAiCharacter);
UClass* Z_Construct_UClass_AAiCharacter_NoRegister()
{
	return AAiCharacter::StaticClass();
}
struct Z_Construct_UClass_AAiCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "AiCharacter.h" },
		{ "ModuleRelativePath", "Public/AiCharacter.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AAiCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AAiCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ABaseCharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_Risky,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AAiCharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AAiCharacter_Statics::ClassParams = {
	&AAiCharacter::StaticClass,
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
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AAiCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_AAiCharacter_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AAiCharacter()
{
	if (!Z_Registration_Info_UClass_AAiCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AAiCharacter.OuterSingleton, Z_Construct_UClass_AAiCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AAiCharacter.OuterSingleton;
}
template<> RISKY_API UClass* StaticClass<AAiCharacter>()
{
	return AAiCharacter::StaticClass();
}
AAiCharacter::AAiCharacter() {}
DEFINE_VTABLE_PTR_HELPER_CTOR(AAiCharacter);
AAiCharacter::~AAiCharacter() {}
// End Class AAiCharacter

// Begin Registration
struct Z_CompiledInDeferFile_FID_Risky_Source_Risky_Public_AiCharacter_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AAiCharacter, AAiCharacter::StaticClass, TEXT("AAiCharacter"), &Z_Registration_Info_UClass_AAiCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AAiCharacter), 2671511445U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Risky_Source_Risky_Public_AiCharacter_h_425419339(TEXT("/Script/Risky"),
	Z_CompiledInDeferFile_FID_Risky_Source_Risky_Public_AiCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Risky_Source_Risky_Public_AiCharacter_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
