// 


#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true; // 启用网络复制
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace(); // 高亮光标处敌人
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer());
	
	if (Subsystem) // 不使用check(Subsystem); 因为多人情况下,仅本地玩家有Subsystem
	{
		Subsystem->AddMappingContext(AuraContext, 0); // 添加输入映射上下文
	}

	bShowMouseCursor = true; // 显示鼠标光标
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData; // 创建输入模式数据
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // 不锁定鼠标到视口
	InputModeData.SetHideCursorDuringCapture(false); // 捕获时不隐藏光标
	SetInputMode(InputModeData); // 应用输入模式
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent); // 获取增强输入组件
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>(); // 获取输入轴向量
	const FRotator Rotation = GetControlRotation(); // 获取控制器旋转
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f); // 创建仅包含偏航的旋转

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // 计算前进方向
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // 计算右侧方向
	// 注：在ActionMappingContext中，左右X轴，前后Y轴；在这里通过Matrix获取Axis时，前后X轴，左右Y轴

	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = CurrentActor;
	CurrentActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	// case A: 1 1
	// case B: null null
	// case C: null 1
	// case D: 1 null
	// case E: 1 2
	if (LastActor == CurrentActor) return; // case A B
	if (CurrentActor) // case C E
	{
		CurrentActor->HighlightActor();
	}
	if (LastActor) // case D E
	{
		LastActor->UnHighlightActor();
	}
}
