// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Galaga_USFX/CircularStrategy.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCircularStrategy() {}
// Cross Module References
	GALAGA_USFX_API UClass* Z_Construct_UClass_ACircularStrategy_NoRegister();
	GALAGA_USFX_API UClass* Z_Construct_UClass_ACircularStrategy();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_Galaga_USFX();
	GALAGA_USFX_API UClass* Z_Construct_UClass_UStrategyInterface_NoRegister();
// End Cross Module References
	void ACircularStrategy::StaticRegisterNativesACircularStrategy()
	{
	}
	UClass* Z_Construct_UClass_ACircularStrategy_NoRegister()
	{
		return ACircularStrategy::StaticClass();
	}
	struct Z_Construct_UClass_ACircularStrategy_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ACircularStrategy_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_Galaga_USFX,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACircularStrategy_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "CircularStrategy.h" },
		{ "ModuleRelativePath", "CircularStrategy.h" },
	};
#endif
		const UE4CodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_ACircularStrategy_Statics::InterfaceParams[] = {
			{ Z_Construct_UClass_UStrategyInterface_NoRegister, (int32)VTABLE_OFFSET(ACircularStrategy, IStrategyInterface), false },
		};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ACircularStrategy_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACircularStrategy>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ACircularStrategy_Statics::ClassParams = {
		&ACircularStrategy::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		InterfaceParams,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		UE_ARRAY_COUNT(InterfaceParams),
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ACircularStrategy_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ACircularStrategy_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ACircularStrategy()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ACircularStrategy_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ACircularStrategy, 1063127450);
	template<> GALAGA_USFX_API UClass* StaticClass<ACircularStrategy>()
	{
		return ACircularStrategy::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ACircularStrategy(Z_Construct_UClass_ACircularStrategy, &ACircularStrategy::StaticClass, TEXT("/Script/Galaga_USFX"), TEXT("ACircularStrategy"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ACircularStrategy);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif