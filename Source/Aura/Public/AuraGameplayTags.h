

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
		// static FAuraGameplayTags GameplayTags; // 懒汉式单例
		return GameplayTags;
	}
	static void InitializeNativeGameplayTags();
protected:

private:
	FAuraGameplayTags() = default;
	~FAuraGameplayTags() = default;

	FAuraGameplayTags(const FAuraGameplayTags&) = delete; // 禁止拷贝构造
	FAuraGameplayTags& operator=(const FAuraGameplayTags&) = delete; // 禁止赋值操作
	
	inline static FAuraGameplayTags GameplayTags; // 或者饿汉式单例
};

