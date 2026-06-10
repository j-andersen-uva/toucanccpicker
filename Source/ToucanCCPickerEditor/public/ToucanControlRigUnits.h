#pragma once

#include "CoreMinimal.h"
#include "Units/RigUnit.h"
#include "Rigs/RigHierarchyDefines.h"
#include "ToucanControlRigUnits.generated.h"

UENUM(BlueprintType)
enum class EToucanControlRigKeyValueType : uint8
{
	FloatChannel UMETA(DisplayName = "Float Channel")
};

USTRUCT(BlueprintType)
struct TOUCANCCPICKEREDITOR_API FToucanWeightedCurve
{
	GENERATED_BODY()

	FToucanWeightedCurve()
		: CurveName(NAME_None)
		, Weight(1.f)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toucan|Controls", meta = (Input, CustomWidget = "CurveName"))
	FName CurveName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toucan|Controls", meta = (Input))
	float Weight;
};

USTRUCT(BlueprintType)
struct TOUCANCCPICKEREDITOR_API FToucanCurveValueMapping
{
	GENERATED_BODY()

	FToucanCurveValueMapping()
		: Name(NAME_None)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toucan|Controls", meta = (Input))
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toucan|Controls", meta = (Input, ExpandByDefault))
	TArray<FToucanWeightedCurve> Curves;
};

USTRUCT(meta = (DisplayName = "Get Highest Control Value", Category = "Toucan|Controls", Keywords = "Toucan,ControlRig,Float,Channel,Highest,Max", NodeColor = "0.0 0.364706 1.0"))
struct TOUCANCCPICKEREDITOR_API FRigUnit_ToucanGetHighestControlValue : public FRigUnit
{
	GENERATED_BODY()

	FRigUnit_ToucanGetHighestControlValue()
		: KeyValueType(EToucanControlRigKeyValueType::FloatChannel)
		, HighestValue(0.f)
		, bFound(false)
	{}

	RIGVM_METHOD()
	virtual void Execute() override;

	UPROPERTY(meta = (Input, ExpandByDefault))
	TArray<FRigElementKey> Keys;

	UPROPERTY(meta = (Input))
	EToucanControlRigKeyValueType KeyValueType;

	UPROPERTY(meta = (Output))
	FName HighestControlName;

	UPROPERTY(meta = (Output))
	FRigElementKey HighestKey;

	UPROPERTY(meta = (Output))
	float HighestValue;

	UPROPERTY(meta = (Output))
	bool bFound;

	UPROPERTY()
	TArray<FCachedRigElement> CachedKeys;
};

USTRUCT(meta = (DisplayName = "Set Mapped Curve Values", Category = "Toucan|Controls", Keywords = "Toucan,ControlRig,Curve,Mapping,Weight", NodeColor = "0.0 0.364706 1.0"))
struct TOUCANCCPICKEREDITOR_API FRigUnit_ToucanSetMappedCurveValues : public FRigUnitMutable
{
	GENERATED_BODY()

	FRigUnit_ToucanSetMappedCurveValues()
		: Name(NAME_None)
		, Value(0.f)
		, AppliedCurveCount(0)
		, bFoundMapping(false)
	{}

	RIGVM_METHOD()
	virtual void Execute() override;

	UPROPERTY(meta = (Input, ExpandByDefault))
	TArray<FToucanCurveValueMapping> Mappings;

	UPROPERTY(meta = (Input))
	FName Name;

	UPROPERTY(meta = (Input))
	float Value;

	UPROPERTY(meta = (Output))
	int32 AppliedCurveCount;

	UPROPERTY(meta = (Output))
	bool bFoundMapping;

	UPROPERTY()
	TArray<FCachedRigElement> CachedCurves;
};
