// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Snake.generated.h"

// forward declaration. ��������� ������� ������
class ASnakeElementBase; 

// ��� ����������� �������� ������������ ������������ enum
UENUM()
enum class EMovementDirection 
{
	UP,DOWN,LEFT,RIGHT
};

UCLASS()
class SNAKEGAME_API ASnake : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnake();

	// EditDefaultsOnly - ������ �������� ��� �������������� � BP
	UPROPERTY(EditDefaultsOnly)
	// ���������� � �������,� ������� ������ SnakeElement
	TSubclassOf<ASnakeElementBase> SnakeElementClass; 

	// ����������,�������� ������ �������� ������
	UPROPERTY(EditDefaultsOnly) 
		float ElementSize;		

	UPROPERTY(EditDefaultsOnly) //EditDefaultsOnly
	// ��������,���������� �� �������� ������
		float MovementSpeed;		
	   

	UPROPERTY()
	// ������ �� ����������* �� ��������
	TArray<ASnakeElementBase*> SnakeElements; 

	UPROPERTY()
	// ���������� ���������� ����������� ��������
	EMovementDirection LastMoveDirection; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Score = 0;

	// ������ ���������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int newScore = 0;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	int Life = 1;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override; 

	UFUNCTION(BlueprintCallable)
	// ��������� �������� ���������
	void AddSnakeElement(int ElementsNum = 1); 

	UFUNCTION(BlueprintCallable)
	// float DeltaTime.������� DeltaTime ������ �� ����������� � ��� ���� ������� �����.
	// ����� Move,������� ����� ��������� �� ���� DeltaTime. 
	void Move(); 
	
	// ���� ��������� ��������,�� �� SnakeOwner ����� �������� �����,
	// ��� ��� ���� ����������� � ���-����. � �������� ���������,� 
	// ���� ����� �� ����� ����� ���������� ����� ������ ���� ������
	// ������ �������.������� �������������...
	//
	// ������ ���� ����� ���� �����������,������ ��� �� ����� ����� 
	// � ��� ��� ������������.
	// 
	// �������� ������ �������� Actor`a "Other", ������� ����� ���������� Actor`a
	// � ������� ����������� ��� ����.
	UFUNCTION()
	void SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other);

	void HighSpeed();

	void HighSpeed2();

	void HighSpeed3();

	void DestroySnake();



	
	
};
