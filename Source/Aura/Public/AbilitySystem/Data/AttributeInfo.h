// 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"

USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;

};

/**
 * 一个可以通过GameplayTag查询属性信息的DataAsset，包含属性标签、名称、描述和数值等信息
 */
UCLASS()
class AURA_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	/**
	 * 
	 * @param AttributeTag FGameplayTag类型的属性标签，用于查询属性信息
	 * @param blogNotFound 未找到时是否记录日志
	 * @return 对应属性结构体
	 */
	FAuraAttributeInfo FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool blogNotFound = false) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraAttributeInfo> AttributeInformation;
	
};
