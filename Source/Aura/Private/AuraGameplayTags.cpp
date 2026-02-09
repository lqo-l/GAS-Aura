


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	FAuraGameplayTags &GameplayTags = FAuraGameplayTags::Get();
	// 声明原生tags
	 GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("减少承伤，增强抵抗率"));
}
