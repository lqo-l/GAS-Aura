// 


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	// 拿到属性结构体，获取当前值并广播
	UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(AttributeSet);

	check(AttributeInfo);

	for (TPair<FGameplayTag, TDelegate<FGameplayAttribute()>>& Pair : AS->TagsToAttributes)
	{
		FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
		Info.AttributeValue = Pair.Value.Execute().GetNumericValue(AS);
		AttributeInfoDelegate.Broadcast(Info);
	}
	
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
}
