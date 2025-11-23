// 


#include "Actor/AuraEffectActor.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
}


void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

}

void AAuraEffectActor::ApplyEffectToActor(AActor* TargetActor, TSubclassOf<UGameplayEffect> EffectClass)
{
	// 获取Actor的ASC的一种方式：通过Interface
	// if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(Target))
	// 	UAbilitySystemComponent* ASC = ASCInterface->GetAbilitySystemComponent();

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor); // 另一种方式：通过BlueprintLibrary
	if (TargetASC == nullptr) return;

	check(EffectClass);
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(EffectClass, 1.f, EffectContextHandle);
	TargetASC->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), TargetASC);
}



