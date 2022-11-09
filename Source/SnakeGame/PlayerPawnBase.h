// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Food.h"
#include "PlayerPawnBase.generated.h"

// forward declaration. �������� �����������,��� ���������� ����� UCamera Component
class UCameraComponent;	 
// forward declaration. ����� ������������ � � .h ����� ������.������� � - ������ ��� ����������� �� Actor
class ASnake;			 

UCLASS()
class SNAKEGAME_API APlayerPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawnBase();

	//���������� ��������� ������
	UPROPERTY(BlueprintReadWrite)	
	UCameraComponent* PawnCamera;	

	// ����� ������ ������������ ���-��� ������ ������,�� ����� ������������� �� �++ ������ � ��.
	// � ��� ����,����� ������� �� ����� ��� ��,��� ����� ����������,�� ����� ������� 
	// ���������� ����������� ������ ������,������� ����� ����������� � Spawn Actor
	UPROPERTY(BlueprintReadWrite)	
	ASnake* SnakeActor;	
	
	// EditDefaultsOnly ��������,��� �� ����� ������������� ��� ���������� ������ 
	// � ��������� ���������� ������ (������ � ������ ���� ���������� � UE)
	UPROPERTY(EditDefaultsOnly)				
	TSubclassOf<ASnake> SnakeActorClass;
	// ��� ������������ ����������,������� ������������ ����� �����.��������� 
	// �� �� ������,� ��� �� ���� �����,������� �� ����� ��������� � �������� ��������� ��� spawn
	
	UPROPERTY(BlueprintReadWrite)
	AFood* Food;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFood> FoodActorClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//������� �������� ������
	void CreateSnakeActor(); 
	// ������� �������� ���
	void CreateFoodActor();

	// ������ �� ������������ � �������������� input`�
	UFUNCTION()
	void HandlePlayerVerticalInput(float value);  

	UFUNCTION()
	void HandlePlayerHorizontallInput(float value); 

	
	


};
