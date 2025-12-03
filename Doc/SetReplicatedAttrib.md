```c++
// .h
UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
int32 Level = 1;

UFUNCTION()
void OnRep_Level(int32 OldLevel);

// .cpp
virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override{
    //DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always); // 无条件rep，并且总是触发OnRep函数
     DOREPLIFETIME(AAuraPlayerState, Level); // 默认COND_None、REPNOTIFY_OnChanged
}
```
