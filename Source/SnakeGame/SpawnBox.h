// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "SpawnBox.generated.h"

UCLASS()
class SNAKEGAME_API ASpawnBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Вызывается когда актор перестает играть
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Функция спавна еды в поле
	UFUNCTION(BlueprintCallable)
	bool SpawnActor();

	// расписание спавна
	void ScheduleActorSpawn();

	// Методы изменения размера поля спавна
	void GetScale();
	void GetScale2();
	void GetScale3();

private:
	// График спавна
	UFUNCTION()
		void SpawnActorScheduled();
public:
	// Актор,который нужно заспавнить
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorClassToBeSpawned;

	// Откл.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ShouldSpawn = true;

	// Среднее время появления между спавнами(без рандома)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AvgSpawnTime = 3.f;

	// Рандом +/- Случайное смещение времени появления
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RandomSpawnTimeOffset = 1.f;
private:
	// Поле,в котором будет спавн еды
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* SpawnBox;

	// Помощник для определения времени
	FTimerHandle SpawnTimerHandle;

};
