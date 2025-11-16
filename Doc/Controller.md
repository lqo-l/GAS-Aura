# Aura 项目 UE5 PlayerController 与 Enhanced Input 集成说明

> 目标：说明如何在 Aura 项目中使用 UE5 Enhanced Input 系统为自定义 `AAuraPlayerController` 绑定输入，并实现基础移动逻辑，支持后续扩展。

---
## 目录
1. 功能简介与目标  
2. 前置条件与环境准备  
3. 核心类与概念  
4. 集成实现步骤（从零到运行）  
5. 关键代码片段精讲  
6. 常见错误与排查  
7. 可扩展建议  
8. 最终验证清单  
9. FAQ（可选后续补充）

---
## 1. 功能简介与目标
`AAuraPlayerController` 管理本地玩家输入、光标显示与输入模式。通过 Enhanced Input：
- 使用 `UInputMappingContext` 定义输入映射集合。
- 使用 `UInputAction` 抽象一个“动作”（如移动、视角、跳跃）。
- 通过 `UEnhancedInputLocalPlayerSubsystem` 将 Mapping Context 应用到当前本地玩家。
- 在 `SetupInputComponent()` 中绑定动作回调，实现角色移动。

结果：运行游戏后按下 WASD（或绑定的方向键/手柄）角色正确移动，鼠标可见（游戏+UI 模式）。

---
## 2. 前置条件与环境准备
| 项 | 要求 |
|----|------|
| 引擎版本 | UE5.x（建议 5.2+，Enhanced Input 默认可用） |
| 插件 | 确认启用 Enhanced Input（Editor: Plugins → 搜索 “Enhanced Input” 勾选） |
| Build.cs | 已在 `PublicDependencyModuleNames` 中添加 `"EnhancedInput"` 与 `"InputCore"` |
| 资产 | 至少 1 个 `Input Mapping Context`（如：`IMC_Default`）和 1 个 `Input Action`（如：`IA_Move`，Value Type = Axis2D） |
| GameMode | GameMode / GameModeBase 指定默认 PlayerController 类为 `AAuraPlayerController` |

示例（已存在）：`Source/Aura/Aura.Build.cs` 中：
```
PublicDependencyModuleNames.AddRange(new [] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
```

---
## 3. 核心类与概念
- `AAuraPlayerController`：继承自 `APlayerController`，主入口：`BeginPlay()`、`SetupInputComponent()`。
- `UInputMappingContext`：输入动作与物理按键/轴映射集合，可设置优先级（Priority）。
- `UInputAction`：抽象输入动作，支持不同 Value Type（Bool、Axis1D、Axis2D、Axis3D 等）。
- `UEnhancedInputLocalPlayerSubsystem`：本地玩家的输入子系统，负责添加/移除映射上下文。
- `UEnhancedInputComponent`：替代旧 `UInputComponent` 的增强组件，支持 BindAction 的触发事件、触发器与修饰器。
- 事件枚举：`ETriggerEvent::Started / Ongoing / Triggered / Completed / Canceled`；连续轴输入通常使用 `Triggered`。

---
## 4. 集成实现步骤（从零到运行）
1. 创建 C++ 类：继承 `APlayerController` → 命名 `AAuraPlayerController`。
2. 在头文件前置声明：`class UInputMappingContext; class UInputAction; struct FInputActionValue;`。
3. 属性声明：
   - `UPROPERTY(EditAnywhere, Category="Input") TObjectPtr<UInputMappingContext> AuraContext;`
   - `UPROPERTY(EditAnywhere, Category="Input") TObjectPtr<UInputAction> MoveAction;`
   （推荐在后续调整为 `EditDefaultsOnly, BlueprintReadOnly` 降低误改风险）
4. 编辑器中（Class Defaults / Blueprint 派生）：为 `AuraContext` 指定你的 `IMC_Default` 资源，为 `MoveAction` 指定 `IA_Move`。
5. `BeginPlay()`：获取 Subsystem → 添加 Mapping Context：
   ```cpp
   UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
   Subsystem->AddMappingContext(AuraContext, 0);
   ```
6. 设置鼠标与输入模式：
   ```cpp
   bShowMouseCursor = true;
   FInputModeGameAndUI Mode; Mode.SetHideCursorDuringCapture(false); SetInputMode(Mode);
   ```
7. `SetupInputComponent()`：
   - Cast 为 `UEnhancedInputComponent`。
   - Bind 移动动作：
     ```cpp
     EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
     ```
8. 实现 `Move(const FInputActionValue& Value)`：
   - 取 `FVector2D Axis = Value.Get<FVector2D>();`
   - 基于控制器旋转获取水平面前/右方向：
     ```cpp
     const FRotator YawRot(0.f, GetControlRotation().Yaw, 0.f);
     const FVector Fwd = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
     const FVector Right = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
     ```
   - 调用 Pawn 移动：`Pawn->AddMovementInput(Fwd, Axis.Y); Pawn->AddMovementInput(Right, Axis.X);`
9. 编译，运行 PIE，测试移动与鼠标状态。

---
## 5. 关键代码片段精讲（节选）
只列出关键点，避免重复完整文件：

头文件节选（`AuraPlayerController.h`）：
```cpp
class UInputMappingContext; 
class UInputAction; 
struct FInputActionValue; 

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController {
    GENERATED_BODY()
    // ...existing code...
private:
    UPROPERTY(EditAnywhere, Category="Input")
    TObjectPtr<UInputMappingContext> AuraContext;
    UPROPERTY(EditAnywhere, Category="Input")
    TObjectPtr<UInputAction> MoveAction;
    void Move(const FInputActionValue& InputActionValue);
};
```

`BeginPlay()` 关键逻辑：
```cpp
check(AuraContext);
UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
check(Subsystem);
Subsystem->AddMappingContext(AuraContext, 0);
```

`SetupInputComponent()`：
```cpp
UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
```

`Move()`：
```cpp
const FVector2D Axis = InputActionValue.Get<FVector2D>();
const FRotator YawRot(0.f, GetControlRotation().Yaw, 0.f);
const FVector Forward = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
const FVector Right   = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
if (APawn* P = GetPawn()) {
    P->AddMovementInput(Forward, Axis.Y);
    P->AddMovementInput(Right, Axis.X);
}
```

---
## 6. 常见错误与排查
| 问题 | 可能原因 | 排查与解决 |
|------|----------|------------|
| C2065 未声明标识符（如 `UEnhancedinputLocalPlayerSubsystem`） | 拼写大小写错误 | 使用正确名称 `UEnhancedInputLocalPlayerSubsystem`；包含 `EnhancedInputSubsystems.h` |
| 编译找不到类型 `UInputMappingContext` | 缺少模块或头文件 | 确认 Build.cs 有 `EnhancedInput`；包含 `InputMappingContext.h` 或使用前置声明 |
| Subsystem 为 nullptr | 在非本地控制器或过早调用 | 确认在 `BeginPlay()` 且控制器为本地玩家，调试 `GetLocalPlayer()` |
| MoveAction 不触发 | 资产未绑定或触发事件选错 | 在细节面板检查引用；使用 `Triggered` 对连续 Axis 输入 |
| 方向错乱（前后/左右反） | Axis 与矩阵方向理解差异 | 记录：InputAction Axis X=左右，Y=前后；矩阵 X=前，Y=右；对应乘法不要混淆 |
| 断言 `check(AuraContext)` 崩溃 | 未在蓝图/默认实例赋值 | 在编辑器为 Controller 类设置默认资产 |
| 多人游戏出现重复映射 | 服务端也调用 | 只在本地（`IsLocalController()`）时 AddMappingContext |
| 光标不显示 | 输入模式未设置或被 UI 覆盖 | 调用 `SetShowMouseCursor(true)` + `FInputModeGameAndUI` 设置 |

调试小技巧：在绑定后临时添加：`UE_LOG(LogTemp, Warning, TEXT("Axis: %s"), *Axis.ToString());` 验证输入值。

---
## 7. 可扩展建议
1. 多 MappingContext：基础 (Movement) / 战斗 (Combat) / UI (Menus) 按优先级切换。  
2. Look 输入：添加 `LookAction`（Axis2D）并调用 `AddYawInput / AddPitchInput`。  
3. 输入修饰器与触发器：DeadZone 降低摇杆噪声；Hold/DoubleTap 触发技能。  
4. 动态启用/禁用：进入 UI 或对话时移除或降低某些 Context 优先级。  
5. 网络拓展：只在客户端处理输入，角色移动交由服务器校验（后续可接入预测）。  
6. 输入重绑定 UI：遍历 MappingContext 中的 Mappings 构建设置面板。  
7. 封装管理：提取一个 `UAuraInputManager`（ActorComponent）集中管理添加/移除 Context。  
8. 数据驱动：使用 DataAsset 描述一组 Action/Context 组合，减少硬编码。  

---
## 8. 最终验证清单
- [ ] Build.cs 已含 `EnhancedInput`。  
- [ ] 插件启用，无 Editor 警告。  
- [ ] Controller 默认类设置到 GameMode。  
- [ ] 在编辑器中设置 `AuraContext` 与 `MoveAction`。  
- [ ] 运行 PIE：无崩溃，日志无标识符未声明错误。  
- [ ] Subsystem 非 nullptr（可断点或打印）。  
- [ ] 按 WASD / 手柄摇杆时角色正确移动。  
- [ ] 移动方向与摄像机水平一致。  
- [ ] 鼠标光标显示且不被锁定。  
- [ ] 多人测试：只有本地玩家响应输入。  
- [ ] 可新增新 Action（如 Jump）无需重构 Controller。  

---
## 9. FAQ
| 问题 | 简答 |
|------|------|
| 可以在 `Constructor` 添加 MappingContext 吗？ | 不推荐，需存在 LocalPlayer；使用 `BeginPlay()` 或 PostLogin。 |
| 是否必须包含全部头文件？ | 指针成员可前置声明；需要访问方法时再包含。 |
| 优先级参数的意义？ | 数字越大优先级越高；高优先级可覆盖低优先级的相同动作绑定。 |
| 旧输入系统还能共存吗？ | 技术上可，但建议迁移统一到 Enhanced Input 以避免混乱。 |
| 移动使用 `Triggered` 还是 `Ongoing`？ | 连续轴值推荐 `Triggered`（每帧更新）。 |

---
## 后续可补充
- 输入触发器与修饰器示例表。  
- 网络同步/预测最小样板。  
- 动态重绑定 UI 设计范式。  

---
**版本历史**  
- v1.0 初稿：基础集成与移动说明。  

