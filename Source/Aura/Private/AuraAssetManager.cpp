// 


#include "AuraAssetManager.h"

#include "AuraGameplayTags.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);
	// GEngine->AssetManager是ue5的全局单例对象
	UAuraAssetManager* AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	return *AuraAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FAuraGameplayTags::InitializeNativeGameplayTags(); // 在此处（游戏开始时）初始化自定义的游戏tags
}

