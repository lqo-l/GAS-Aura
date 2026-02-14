

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 单例，包含原生gameplay tags
 */

struct FAuraGameplayTags
{
public:
	static FAuraGameplayTags& Get()
	{
		static FAuraGameplayTags GameplayTags; // 懒汉式单例
		return GameplayTags;
	}
	static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;

	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;

private:
	FAuraGameplayTags() = default;
	~FAuraGameplayTags() = default;

	FAuraGameplayTags(const FAuraGameplayTags&) = delete; // 禁止拷贝构造
	FAuraGameplayTags& operator=(const FAuraGameplayTags&) = delete; // 禁止赋值操作
	
	
};

