


#include "Character/AuraEnemy.h"

#include "Aura/Aura.h"


AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block); // 设置网格对可见性通道的碰撞响应为阻挡
}

void AAuraEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true); // 启用自定义深度渲染以实现高亮效果
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED); // 设置自定义深度模板值, 与材质对应
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}
