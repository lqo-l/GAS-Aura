

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameFramework/HUD.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AuraHUD.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UAuraUserWidget;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	/** Overlay */
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	/** AttributeMenu */
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);

	void InitAttributeMenu(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	
	
private:
	/** Overlay */
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;
	
	UPROPERTY(EditAnywhere) // 这个属性是为了在编辑器中设置OverlayWidget的蓝图类，实例化时用来创建OverlayWidget实例
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass; 

	UPROPERTY() 
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere) // 这个属性是为了在编辑器中设置OverlayWidgetController的蓝图类，实例化时用来创建OverlayWidgetController实例
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	/** AttributeMenu */
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> AttributeMenuWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> AttributeMenuWidgetClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
};
