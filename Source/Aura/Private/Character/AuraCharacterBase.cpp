


#include "Character/AuraCharacterBase.h"


AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon"); // 创建武器网格组件
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket")); // 将武器附加到角色网格的武器手插槽
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 禁用碰撞
}

// Called when the game starts or when spawned
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
}


