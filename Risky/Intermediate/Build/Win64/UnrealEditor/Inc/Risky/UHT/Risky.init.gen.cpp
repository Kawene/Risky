// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRisky_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_Risky;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_Risky()
	{
		if (!Z_Registration_Info_UPackage__Script_Risky.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/Risky",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0xC6A4B2AA,
				0x8CD391AA,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_Risky.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_Risky.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_Risky(Z_Construct_UPackage__Script_Risky, TEXT("/Script/Risky"), Z_Registration_Info_UPackage__Script_Risky, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xC6A4B2AA, 0x8CD391AA));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
