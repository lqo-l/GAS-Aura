


#include "Character/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"


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
