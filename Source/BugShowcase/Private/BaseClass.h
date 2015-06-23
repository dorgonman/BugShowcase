#pragma once

#include "BaseClass.generated.h"

UCLASS()
class UBaseClass : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	FVector DontHideMe;

	// I'll try to ONLY this property in UDerivedClass customization
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	FVector HideMe;
};