// 


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	// 拿到属性结构体，获取当前值并广播
	UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(AttributeSet);

	check(AttributeInfo);
	FAuraAttributeInfo Strength = AttributeInfo->FindAttributeInfoForTag(FAuraGameplayTags::Get().Attributes_Primary_Strength);
	float StrengthValue = AS->GetStrength();
	Strength.AttributeValue = StrengthValue;
	
	AttributeInfoDelegate.Broadcast(Strength);
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
}
