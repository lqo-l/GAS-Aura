


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerState.h"
#include "Player/AuraPlayerState.h"


AAuraCharacter::AAuraCharacter()
{
	// 2D俯视视角设置
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true; // 角色运动约束到平面
	GetCharacterMovement()->bSnapToPlaneAtStart = true; // 角色开始时贴合平面

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// Server初始化ability actor info 
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Client初始化ability actor info
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	/**
	 * 在混合复制模式下，设置AbilityActorInfo的Owner Actor的Owner必须是Controller。
	 * 对于Pawns，PossessedBy()自动将Pawn的Owner设置为Controller。
	 * PlayerState的Owner也自动设置为Controller。
	 * 这里Owner Actor是PlayerState，若不是，需要手动对OwnerActor进行SetOwner()为Controller的操作
	*/
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this); // Owner是PlayerState，Avatar是Character
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();
}
