// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Risky/Public/Region.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRegion() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_ACharacter_NoRegister();
RISKY_API UClass* Z_Construct_UClass_ARegion();
RISKY_API UClass* Z_Construct_UClass_ARegion_NoRegister();
UPackage* Z_Construct_UPackage__Script_Risky();
// End Cross Module References

// Begin Class ARegion Function ChangeOwnerShip
struct Z_Construct_UFunction_ARegion_ChangeOwnerShip_Statics
{
	struct Region_eventChangeOwnerShip_Parms
	{
		ACharacter* newOwner;
		int32 unitsAmount;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Region.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_newOwner;
	static const UECodeGen_Private::FIntPropertyParams NewProp_unitsAmount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ARegion_ChangeOwnerShip_Statics::NewProp_newOwner = { "newOwner", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Region_eventChangeOwnerShip_Parms, newOwner), Z_Construct_UClass_ACharacter_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ARegion_ChangeOwnerShip_Statics::NewProp_unitsAmount = { "unitsAmount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Region_eventChangeOwnerShip_Parms, unitsAmount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ARegion_ChangeOwnerShip_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ARegion_ChangeOwnerShip_Statics::NewProp_newOwner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ARegion_ChangeOwnerShip_Statics::NewProp_unitsAmount,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ARegion_ChangeOwnerShip_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ARegion_ChangeOwnerShip_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ARegion, nullptr, "ChangeOwnerShip", nullptr, nullptr, Z_Construct_UFunction_ARegion_ChangeOwnerShip_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ARegion_ChangeOwnerShip_Statics::PropPointers), sizeof(Z_Construct_UFunction_ARegion_ChangeOwnerShip_Statics::Region_eventChangeOwnerShip_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ARegion_ChangeOwnerShip_Statics::Function_MetaDataParams), Z_Construct_UFunction_ARegion_ChangeOwnerShip_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_ARegion_ChangeOwnerShip_Statics::Region_eventChangeOwnerShip_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ARegion_ChangeOwnerShip()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ARegion_ChangeOwnerShip_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ARegion::execChangeOwnerShip)
{
	P_GET_OBJECT(ACharacter,Z_Param_newOwner);
	P_GET_PROPERTY(FIntProperty,Z_Param_unitsAmount);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ChangeOwnerShip(Z_Param_newOwner,Z_Param_unitsAmount);
	P_NATIVE_END;
}
// End Class ARegion Function ChangeOwnerShip

// Begin Class ARegion Function DecreaseUnitCount
struct Z_Construct_UFunction_ARegion_DecreaseUnitCount_Statics
{
	struct Region_eventDecreaseUnitCount_Parms
	{
		int32 unitsRemoved;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Region.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_unitsRemoved;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ARegion_DecreaseUnitCount_Statics::NewProp_unitsRemoved = { "unitsRemoved", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Region_eventDecreaseUnitCount_Parms, unitsRemoved), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ARegion_DecreaseUnitCount_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ARegion_DecreaseUnitCount_Statics::NewProp_unitsRemoved,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ARegion_DecreaseUnitCount_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ARegion_DecreaseUnitCount_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ARegion, nullptr, "DecreaseUnitCount", nullptr, nullptr, Z_Construct_UFunction_ARegion_DecreaseUnitCount_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ARegion_DecreaseUnitCount_Statics::PropPointers), sizeof(Z_Construct_UFunction_ARegion_DecreaseUnitCount_Statics::Region_eventDecreaseUnitCount_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ARegion_DecreaseUnitCount_Statics::Function_MetaDataParams), Z_Construct_UFunction_ARegion_DecreaseUnitCount_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_ARegion_DecreaseUnitCount_Statics::Region_eventDecreaseUnitCount_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ARegion_DecreaseUnitCount()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ARegion_DecreaseUnitCount_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ARegion::execDecreaseUnitCount)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_unitsRemoved);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DecreaseUnitCount(Z_Param_unitsRemoved);
	P_NATIVE_END;
}
// End Class ARegion Function DecreaseUnitCount

// Begin Class ARegion Function DeployUnits
struct Z_Construct_UFunction_ARegion_DeployUnits_Statics
{
	struct Region_eventDeployUnits_Parms
	{
		int32 unitsAmount;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Region.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_unitsAmount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ARegion_DeployUnits_Statics::NewProp_unitsAmount = { "unitsAmount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Region_eventDeployUnits_Parms, unitsAmount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ARegion_DeployUnits_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ARegion_DeployUnits_Statics::NewProp_unitsAmount,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ARegion_DeployUnits_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ARegion_DeployUnits_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ARegion, nullptr, "DeployUnits", nullptr, nullptr, Z_Construct_UFunction_ARegion_DeployUnits_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ARegion_DeployUnits_Statics::PropPointers), sizeof(Z_Construct_UFunction_ARegion_DeployUnits_Statics::Region_eventDeployUnits_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ARegion_DeployUnits_Statics::Function_MetaDataParams), Z_Construct_UFunction_ARegion_DeployUnits_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_ARegion_DeployUnits_Statics::Region_eventDeployUnits_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ARegion_DeployUnits()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ARegion_DeployUnits_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ARegion::execDeployUnits)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_unitsAmount);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DeployUnits(Z_Param_unitsAmount);
	P_NATIVE_END;
}
// End Class ARegion Function DeployUnits

// Begin Class ARegion Function GetBorderingRegions
struct Z_Construct_UFunction_ARegion_GetBorderingRegions_Statics
{
	struct Region_eventGetBorderingRegions_Parms
	{
		TArray<ARegion*> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Region.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ARegion_GetBorderingRegions_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_ARegion_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ARegion_GetBorderingRegions_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000008000582, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Region_eventGetBorderingRegions_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnValue_MetaData), NewProp_ReturnValue_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ARegion_GetBorderingRegions_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ARegion_GetBorderingRegions_Statics::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ARegion_GetBorderingRegions_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ARegion_GetBorderingRegions_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ARegion_GetBorderingRegions_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ARegion, nullptr, "GetBorderingRegions", nullptr, nullptr, Z_Construct_UFunction_ARegion_GetBorderingRegions_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ARegion_GetBorderingRegions_Statics::PropPointers), sizeof(Z_Construct_UFunction_ARegion_GetBorderingRegions_Statics::Region_eventGetBorderingRegions_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ARegion_GetBorderingRegions_Statics::Function_MetaDataParams), Z_Construct_UFunction_ARegion_GetBorderingRegions_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_ARegion_GetBorderingRegions_Statics::Region_eventGetBorderingRegions_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ARegion_GetBorderingRegions()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ARegion_GetBorderingRegions_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ARegion::execGetBorderingRegions)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<ARegion*>*)Z_Param__Result=P_THIS->GetBorderingRegions();
	P_NATIVE_END;
}
// End Class ARegion Function GetBorderingRegions

// Begin Class ARegion Function GetRegionOwner
struct Z_Construct_UFunction_ARegion_GetRegionOwner_Statics
{
	struct Region_eventGetRegionOwner_Parms
	{
		const ACharacter* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Region.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ARegion_GetRegionOwner_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000582, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Region_eventGetRegionOwner_Parms, ReturnValue), Z_Construct_UClass_ACharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnValue_MetaData), NewProp_ReturnValue_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ARegion_GetRegionOwner_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ARegion_GetRegionOwner_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ARegion_GetRegionOwner_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ARegion_GetRegionOwner_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ARegion, nullptr, "GetRegionOwner", nullptr, nullptr, Z_Construct_UFunction_ARegion_GetRegionOwner_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ARegion_GetRegionOwner_Statics::PropPointers), sizeof(Z_Construct_UFunction_ARegion_GetRegionOwner_Statics::Region_eventGetRegionOwner_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ARegion_GetRegionOwner_Statics::Function_MetaDataParams), Z_Construct_UFunction_ARegion_GetRegionOwner_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_ARegion_GetRegionOwner_Statics::Region_eventGetRegionOwner_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ARegion_GetRegionOwner()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ARegion_GetRegionOwner_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ARegion::execGetRegionOwner)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(const ACharacter**)Z_Param__Result=P_THIS->GetRegionOwner();
	P_NATIVE_END;
}
// End Class ARegion Function GetRegionOwner

// Begin Class ARegion Function GetUnits
struct Z_Construct_UFunction_ARegion_GetUnits_Statics
{
	struct Region_eventGetUnits_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Region.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ARegion_GetUnits_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Region_eventGetUnits_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ARegion_GetUnits_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ARegion_GetUnits_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ARegion_GetUnits_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ARegion_GetUnits_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ARegion, nullptr, "GetUnits", nullptr, nullptr, Z_Construct_UFunction_ARegion_GetUnits_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ARegion_GetUnits_Statics::PropPointers), sizeof(Z_Construct_UFunction_ARegion_GetUnits_Statics::Region_eventGetUnits_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ARegion_GetUnits_Statics::Function_MetaDataParams), Z_Construct_UFunction_ARegion_GetUnits_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_ARegion_GetUnits_Statics::Region_eventGetUnits_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ARegion_GetUnits()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ARegion_GetUnits_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ARegion::execGetUnits)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetUnits();
	P_NATIVE_END;
}
// End Class ARegion Function GetUnits

// Begin Class ARegion
void ARegion::StaticRegisterNativesARegion()
{
	UClass* Class = ARegion::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ChangeOwnerShip", &ARegion::execChangeOwnerShip },
		{ "DecreaseUnitCount", &ARegion::execDecreaseUnitCount },
		{ "DeployUnits", &ARegion::execDeployUnits },
		{ "GetBorderingRegions", &ARegion::execGetBorderingRegions },
		{ "GetRegionOwner", &ARegion::execGetRegionOwner },
		{ "GetUnits", &ARegion::execGetUnits },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ARegion);
UClass* Z_Construct_UClass_ARegion_NoRegister()
{
	return ARegion::StaticClass();
}
struct Z_Construct_UClass_ARegion_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Region.h" },
		{ "ModuleRelativePath", "Public/Region.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RegionOwner_MetaData[] = {
		{ "Category", "Region" },
		{ "ModuleRelativePath", "Public/Region.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UnitsInRegion_MetaData[] = {
		{ "Category", "Region" },
		{ "ModuleRelativePath", "Public/Region.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BorderingRegions_MetaData[] = {
		{ "Category", "Region" },
		{ "ModuleRelativePath", "Public/Region.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RegionOwner;
	static const UECodeGen_Private::FIntPropertyParams NewProp_UnitsInRegion;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BorderingRegions_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_BorderingRegions;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ARegion_ChangeOwnerShip, "ChangeOwnerShip" }, // 3111125138
		{ &Z_Construct_UFunction_ARegion_DecreaseUnitCount, "DecreaseUnitCount" }, // 268303611
		{ &Z_Construct_UFunction_ARegion_DeployUnits, "DeployUnits" }, // 3089501759
		{ &Z_Construct_UFunction_ARegion_GetBorderingRegions, "GetBorderingRegions" }, // 444612376
		{ &Z_Construct_UFunction_ARegion_GetRegionOwner, "GetRegionOwner" }, // 3510090618
		{ &Z_Construct_UFunction_ARegion_GetUnits, "GetUnits" }, // 3787308601
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ARegion>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARegion_Statics::NewProp_RegionOwner = { "RegionOwner", nullptr, (EPropertyFlags)0x0020080000000004, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARegion, RegionOwner), Z_Construct_UClass_ACharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RegionOwner_MetaData), NewProp_RegionOwner_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ARegion_Statics::NewProp_UnitsInRegion = { "UnitsInRegion", nullptr, (EPropertyFlags)0x0020080000000004, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARegion, UnitsInRegion), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UnitsInRegion_MetaData), NewProp_UnitsInRegion_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARegion_Statics::NewProp_BorderingRegions_Inner = { "BorderingRegions", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_ARegion_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ARegion_Statics::NewProp_BorderingRegions = { "BorderingRegions", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ARegion, BorderingRegions), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BorderingRegions_MetaData), NewProp_BorderingRegions_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ARegion_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARegion_Statics::NewProp_RegionOwner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARegion_Statics::NewProp_UnitsInRegion,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARegion_Statics::NewProp_BorderingRegions_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARegion_Statics::NewProp_BorderingRegions,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ARegion_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ARegion_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_Risky,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ARegion_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ARegion_Statics::ClassParams = {
	&ARegion::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ARegion_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ARegion_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ARegion_Statics::Class_MetaDataParams), Z_Construct_UClass_ARegion_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ARegion()
{
	if (!Z_Registration_Info_UClass_ARegion.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ARegion.OuterSingleton, Z_Construct_UClass_ARegion_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ARegion.OuterSingleton;
}
template<> RISKY_API UClass* StaticClass<ARegion>()
{
	return ARegion::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ARegion);
ARegion::~ARegion() {}
// End Class ARegion

// Begin Registration
struct Z_CompiledInDeferFile_FID_Risky_Source_Risky_Public_Region_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ARegion, ARegion::StaticClass, TEXT("ARegion"), &Z_Registration_Info_UClass_ARegion, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ARegion), 2058145U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Risky_Source_Risky_Public_Region_h_3793553372(TEXT("/Script/Risky"),
	Z_CompiledInDeferFile_FID_Risky_Source_Risky_Public_Region_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Risky_Source_Risky_Public_Region_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
