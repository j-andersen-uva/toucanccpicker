#include "ToucanControlRigUnits.h"

#include "Rigs/RigHierarchy.h"
#include "Units/RigUnitContext.h"

namespace
{
	static bool isFloatControl(const FRigControlElement* controlElement)
	{
		if (!controlElement)
		{
			return false;
		}

		const ERigControlType controlType = controlElement->Settings.ControlType;
		return controlType == ERigControlType::Float || controlType == ERigControlType::ScaleFloat;
	}
}

FRigUnit_ToucanGetHighestControlValue_Execute()
{
	DECLARE_SCOPE_HIERARCHICAL_COUNTER_RIGUNIT()

	HighestControlName = NAME_None;
	HighestKey = FRigElementKey();
	HighestValue = 0.f;
	bFound = false;

	URigHierarchy* Hierarchy = ExecuteContext.Hierarchy;
	if (!Hierarchy || Keys.IsEmpty())
	{
		CachedKeys.Reset();
		return;
	}

	CachedKeys.SetNum(Keys.Num());

	for (int32 KeyIndex = 0; KeyIndex < Keys.Num(); ++KeyIndex)
	{
		const FRigElementKey ControlKey(Keys[KeyIndex].Name, ERigElementType::Control);
		if (!CachedKeys[KeyIndex].UpdateCache(ControlKey, Hierarchy))
		{
			continue;
		}

		const FRigControlElement* ControlElement = Hierarchy->Get<FRigControlElement>(CachedKeys[KeyIndex]);
		if (!isFloatControl(ControlElement))
		{
			continue;
		}

		float CurrentValue = 0.f;
		switch (KeyValueType)
		{
			case EToucanControlRigKeyValueType::FloatChannel:
			{
				CurrentValue = Hierarchy->GetControlValue(CachedKeys[KeyIndex]).Get<float>();
				break;
			}
			default:
			{
				continue;
			}
		}

		if (!bFound || CurrentValue > HighestValue)
		{
			bFound = true;
			HighestValue = CurrentValue;
			HighestKey = ControlKey;
			HighestControlName = ControlKey.Name;
		}
	}
}

FRigUnit_ToucanSetMappedCurveValues_Execute()
{
	DECLARE_SCOPE_HIERARCHICAL_COUNTER_RIGUNIT()

	AppliedCurveCount = 0;
	bFoundMapping = false;

	URigHierarchy* Hierarchy = ExecuteContext.Hierarchy;
	if (!Hierarchy || Name.IsNone() || Mappings.IsEmpty())
	{
		CachedCurves.Reset();
		return;
	}

	const FToucanCurveValueMapping* FoundMapping = nullptr;
	for (const FToucanCurveValueMapping& Mapping : Mappings)
	{
		if (Mapping.Name == Name)
		{
			FoundMapping = &Mapping;
			break;
		}
	}

	if (!FoundMapping)
	{
		CachedCurves.Reset();
		return;
	}

	bFoundMapping = true;
	CachedCurves.SetNum(FoundMapping->Curves.Num());

	for (int32 CurveIndex = 0; CurveIndex < FoundMapping->Curves.Num(); ++CurveIndex)
	{
		const FToucanWeightedCurve& WeightedCurve = FoundMapping->Curves[CurveIndex];
		if (WeightedCurve.CurveName.IsNone())
		{
			continue;
		}

		const FRigElementKey CurveKey(WeightedCurve.CurveName, ERigElementType::Curve);
		if (!CachedCurves[CurveIndex].UpdateCache(CurveKey, Hierarchy))
		{
			continue;
		}

		Hierarchy->SetCurveValueByIndex(CachedCurves[CurveIndex], Value * WeightedCurve.Weight);
		++AppliedCurveCount;
	}
}
