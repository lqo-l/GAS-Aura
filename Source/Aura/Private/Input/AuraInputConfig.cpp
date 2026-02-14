// 


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
	bool BlogNotFound) const
{
	for (const FAuraInputAction& Action : AbilityInputActions)
	{
		if (Action.InputTag.MatchesTagExact(InputTag))
		{
			return Action.InputAction;
		}
	}

	if (BlogNotFound)
	{
		UE_LOG(
			LogTemp, Error,
			TEXT("找不到InputAction [%s] 的InputTag [%s] 信息"), *GetNameSafe(this) ,*InputTag.ToString()
			);
		
	}
	return nullptr;
}
