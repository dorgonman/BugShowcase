#include "BugShowcasePrivatePCH.h"
#include "DerivedCustomization.h"
#include "DerivedClass.h"

#define LOCTEXT_NAMESPACE "DerivedCustomization"


TSharedRef<IDetailCustomization> FDerivedCustomization::MakeInstance()
{
	return MakeShareable(new FDerivedCustomization);
}

void FDerivedCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	// So now we're customizing UDerivedClass object
	// First, try to hide an inherited property
	{
		// 'HideMe' property is defined in UBaseClass
		TSharedPtr<IPropertyHandle> PropertyToHide = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UDerivedClass, HideMe));

		PropertyToHide->MarkHiddenByCustomization();
	}
	
	
	{
		// Now grab any struct property (or property that has customized property value widget)
		// Note that this is property defined in UDerivedClass!
		TSharedPtr<IPropertyHandle> TestProperty = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UDerivedClass, Vector2dProperty));

		// Hide this property
		TestProperty->MarkHiddenByCustomization();

		// Get a category so we can add a TestProperty back to the panel
		IDetailCategoryBuilder& DerivedCategory = DetailLayout.EditCategory("Derived");
		DerivedCategory.AddCustomRow(LOCTEXT("DerivedObjectLabel", "Derived"))
			.NameContent()
			[
				TestProperty->CreatePropertyNameWidget()
			]
		.ValueContent()
			[
				// This will return NullWidget - thats the problem
				TestProperty->CreatePropertyValueWidget()
			];
	}
}

#undef LOCTEXT_NAMESPACE