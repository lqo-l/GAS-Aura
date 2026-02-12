// 


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool blogNotFound) const
{
	for (const FAuraAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}

	if (blogNotFound)
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("找不到AttributeInfo [%s] 的AttributeTag [%s] 信息"), *GetNameSafe(this) ,*AttributeTag.ToString()
			);
		
	}
	return FAuraAttributeInfo();
}
