#pragma once

#include "BaseClass.h"
#include "DerivedClass.generated.h"

UCLASS()
class UDerivedClass : public UBaseClass
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Derived")
	int32 SampleProperty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Derived")
	FVector2D Vector2dProperty;
};