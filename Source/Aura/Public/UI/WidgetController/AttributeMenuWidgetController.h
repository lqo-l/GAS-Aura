// 

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AttributeMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, FAuraAttributeInfo, NewValue);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class AURA_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override; // 初始化时广播属性值,更新UI
	virtual void BindCallbacksToDependencies() override; // 绑定属性变化的回调函数
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;

};
