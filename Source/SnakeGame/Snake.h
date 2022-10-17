// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Snake.generated.h"

class ASnakeElementBase; //forward declaration. ��������� ������� ������

UENUM()
enum class EMovementDirection //��� ����������� �������� ������������ ������������ enum
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

	UPROPERTY(EditDefaultsOnly)//�������� ��� �������������� � BP
	TSubclassOf<ASnakeElementBase> SnakeElementClass; //���������� � �������,� ������� ������ SnakeElement

	UPROPERTY(EditDefaultsOnly) //�������� ��� �������������� � BP
		float ElementSize;		//����������,�������� ������ �������� ������

	UPROPERTY(EditDefaultsOnly) //�������� ��� �������������� � BP
		float MovementSpeed;		//��������,���������� �� �������� ������

	UPROPERTY()
	TArray<ASnakeElementBase*> SnakeElements; // ������ �� ����������* �� ��������

	UPROPERTY()
	EMovementDirection LastMoveDirection; //���������� ���������� ����������� ��������

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override; 

	UFUNCTION(BlueprintCallable)
	void AddSnakeElement(int ElementsNum = 1); // ��������� �������� ���������

	UFUNCTION(BlueprintCallable)
	void Move(); //float DeltaTime ����� Move,������� ����� ��������� �� ���� DeltaTime. ������� DeltaTime ������ �� ����������� � ��� ���� ������� �����.

	//���� ��������� ��������,�� �� SnakeOwner ����� �������� �����,
	//��� ��� ���� ����������� � ���-����. � �������� ���������,� 
	//���� ����� �� ����� ����� ���������� ����� ������ ���� ������
	//������ �������.������� �������������...
	//
	//������ ���� ����� ���� �����������,������ ��� �� ����� ����� 
	//� ��� ��� ������������.
	// 
	//�������� ������ �������� Actor`a "Other", ������� ����� ���������� Actor`a
	//� ������� ����������� ��� ����.
	UFUNCTION()
	void SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other);
	
};
