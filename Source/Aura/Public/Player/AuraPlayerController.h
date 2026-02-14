// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interaction/EnemyInterface.h"

#include "AuraPlayerController.generated.h"

class USplineComponent;
class UAuraAbilitySystemComponent;
struct FGameplayTag;
class UAuraInputConfig;
class UInputMappingContext; // 增强输入前置声明，指针可用
class UInputAction;
struct FInputActionValue; 
// #include "InputMappingContext.h" // 或直接引入头文件

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override; 
	
private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	
	void Move(const FInputActionValue &InputActionValue);

	void CursorTrace();
	IEnemyInterface* CurrentActor;
	IEnemyInterface* LastActor;


	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;

	// 由于频繁获取ASC并Cast,我们创建一个函数来获取ASC,以减少Cast次数
	UAuraAbilitySystemComponent* GetASC();


	FVector CachedDestination = FVector::ZeroVector; // TopDown移动的目标位置缓存
	float FollowTime = 0.f; // 记录跟随时间
	float ShortPressThreshold = 0.5f; // 短按阈值，单位为秒
	bool bAutoRunning = false; // 是否正在自动移动
	bool bTargeting = false; // 是否正在锁定目标
	
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f; // 自动移动的接受半径

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline; // 样条路径
};
