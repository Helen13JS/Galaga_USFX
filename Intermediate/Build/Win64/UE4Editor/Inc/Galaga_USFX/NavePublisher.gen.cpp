// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Galaga_USFX/NavePublisher.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNavePublisher() {}
// Cross Module References
	GALAGA_USFX_API UClass* Z_Construct_UClass_ANavePublisher_NoRegister();
	GALAGA_USFX_API UClass* Z_Construct_UClass_ANavePublisher();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_Galaga_USFX();
// End Cross Module References
	void ANavePublisher::StaticRegisterNativesANavePublisher()
	{
	}
	UClass* Z_Construct_UClass_ANavePublisher_NoRegister()
	{
		return ANavePublisher::StaticClass();
	}
	struct Z_Construct_UClass_ANavePublisher_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ANavePublisher_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_Galaga_USFX,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ANavePublisher_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "NavePublisher.h" },
		{ "ModuleRelativePath", "NavePublisher.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ANavePublisher_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ANavePublisher>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ANavePublisher_Statics::ClassParams = {
		&ANavePublisher::StaticClass,
		"Engine",
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
		METADATA_PARAMS(Z_Construct_UClass_ANavePublisher_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ANavePublisher_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ANavePublisher()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ANavePublisher_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ANavePublisher, 255278419);
	template<> GALAGA_USFX_API UClass* StaticClass<ANavePublisher>()
	{
		return ANavePublisher::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ANavePublisher(Z_Construct_UClass_ANavePublisher, &ANavePublisher::StaticClass, TEXT("/Script/Galaga_USFX"), TEXT("ANavePublisher"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ANavePublisher);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif