// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Galaga_USFX/StrategyPawnInterface.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeStrategyPawnInterface() {}
// Cross Module References
	GALAGA_USFX_API UClass* Z_Construct_UClass_UStrategyPawnInterface_NoRegister();
	GALAGA_USFX_API UClass* Z_Construct_UClass_UStrategyPawnInterface();
	COREUOBJECT_API UClass* Z_Construct_UClass_UInterface();
	UPackage* Z_Construct_UPackage__Script_Galaga_USFX();
// End Cross Module References
	void UStrategyPawnInterface::StaticRegisterNativesUStrategyPawnInterface()
	{
	}
	UClass* Z_Construct_UClass_UStrategyPawnInterface_NoRegister()
	{
		return UStrategyPawnInterface::StaticClass();
	}
	struct Z_Construct_UClass_UStrategyPawnInterface_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UStrategyPawnInterface_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UInterface,
		(UObject* (*)())Z_Construct_UPackage__Script_Galaga_USFX,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UStrategyPawnInterface_Statics::Class_MetaDataParams[] = {
		{ "ModuleRelativePath", "StrategyPawnInterface.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UStrategyPawnInterface_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<IStrategyPawnInterface>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UStrategyPawnInterface_Statics::ClassParams = {
		&UStrategyPawnInterface::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x000840A1u,
		METADATA_PARAMS(Z_Construct_UClass_UStrategyPawnInterface_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UStrategyPawnInterface_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UStrategyPawnInterface()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UStrategyPawnInterface_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UStrategyPawnInterface, 1129102774);
	template<> GALAGA_USFX_API UClass* StaticClass<UStrategyPawnInterface>()
	{
		return UStrategyPawnInterface::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UStrategyPawnInterface(Z_Construct_UClass_UStrategyPawnInterface, &UStrategyPawnInterface::StaticClass, TEXT("/Script/Galaga_USFX"), TEXT("UStrategyPawnInterface"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UStrategyPawnInterface);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
