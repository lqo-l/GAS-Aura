


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	// 声明原生tags
	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("减少承伤，增强抵抗率"));
}
