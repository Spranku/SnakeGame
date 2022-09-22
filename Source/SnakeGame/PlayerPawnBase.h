// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawnBase.generated.h"

class UCameraComponent;	 //forward declaration. �������� �����������,��� ���������� ����� UCamera Component
class ASnake;			 //forward declaration. ����� ������������ � � .h ����� ������.������� � - ������ ��� ����������� �� Actor

UCLASS()
class SNAKEGAME_API APlayerPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawnBase();

	UPROPERTY(BlueprintReadWrite)	
	UCameraComponent* PawnCamera;	//���������� ��������� ������

	UPROPERTY(BlueprintReadWrite)	//����� ������ ������������ ���-��� ������ ������,�� ����� ������������� �� �++ ������ � ��.� ��� ����,
	ASnake* SnakeActor;				//����� ������� �� ����� ��� ��,��� ����� ����������,�� ����� ������� ���������� ����������� ������ ������,������� ����� ����������� � Spawn Actor

	UPROPERTY(EditDefaultsOnly)				//��������,��� �� ����� ������������� ��� ���������� ������ � ��������� ���������� ������ (������ � ������ ���� ���������� � UE)
	TSubclassOf<ASnake> SnakeActorClass;	//��� ������������ ����������,������� ������������ ����� �����.��������� �� �� ������,� ��� �� ���� �����,
											//������� �� ����� ��������� � �������� ��������� ��� spawn

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void CreateSnakeActor(); //������� �������� ������

	UFUNCTION()
		void HandlePlayerVerticalInput(float value);    //����� �� ������������ input
	UFUNCTION()
		void HandlePlayerHorizontallInput(float value); //����� �� �������������� input

};
