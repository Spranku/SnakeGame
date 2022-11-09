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

	// ���������� ����� ����� ��������� ������
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ������� ������ ��� � ����
	UFUNCTION(BlueprintCallable)
	bool SpawnActor();

	// ���������� ������
	void ScheduleActorSpawn();

	// ������ ��������� ������� ���� ������
	void GetScale();
	void GetScale2();
	void GetScale3();

private:
	// ������ ������
	UFUNCTION()
		void SpawnActorScheduled();
public:
	// �����,������� ����� ����������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorClassToBeSpawned;

	// ����.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ShouldSpawn = true;

	// ������� ����� ��������� ����� ��������(��� �������)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AvgSpawnTime = 3.f;

	// ������ +/- ��������� �������� ������� ���������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RandomSpawnTimeOffset = 1.f;
private:
	// ����,� ������� ����� ����� ���
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* SpawnBox;

	// �������� ��� ����������� �������
	FTimerHandle SpawnTimerHandle;

};
