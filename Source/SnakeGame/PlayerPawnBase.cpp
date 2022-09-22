// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnBase.h"
#include <Engine/Classes/Camera/CameraComponent.h>
#include <SnakeGame/Snake.h>
#include <Components/InputComponent.h>

//#include "Engine/Classes/Camera/CameraComponent.h"
// Sets default values
APlayerPawnBase::APlayerPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Pawn Camera"));
	RootComponent = PawnCamera;

}

// Called when the game starts or when spawned
void APlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorRotation(FRotator(-90, 0, 0));
	CreateSnakeActor(); //�������� ������� �������� ������
}

// Called every frame
void APlayerPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) //����� �� ����� ����������� ��� input
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//������ �� ��� input �� ���������
	PlayerInputComponent->BindAxis("Vertical", this, &APlayerPawnBase::HandlePlayerVerticalInput);
	//��������� �����,� ������� ��������� �����.�.�. ����� ����� ���������� ������ ������ Pawn,����� this
	//��� ������ ��������� ������ ������ & ��� ������ (&AplayerPawnBase)
	//����� ����� :: ��������� ��� ������ ���������� ������ ( HandlePlayerVerticalInput / HandlePlayerHorizontallInput
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerPawnBase::HandlePlayerHorizontallInput);

}

void APlayerPawnBase::CreateSnakeActor() //������� �������� ������
{
	//GetWorld - ����� �� ����� ������� Spawn Actor
	//� < > ��������� ���������� ����� Snake 
	//����� � ( ) �� ������ �������� ��� ����� ��� ���,�� � ��������� ::StaticClass
	//����� �� ��������� ���,����� �������� ���������� � .h ����� SnakeActorClass
	//�������� Transform ����� ������ (�������� �� ����� ���������)
	SnakeActor = GetWorld()->SpawnActor<ASnake>(SnakeActorClass, FTransform()); 
}

//���������� ������ �����/����
void APlayerPawnBase::HandlePlayerVerticalInput(float value)
{ 
	//������ ����� ���� ��������� ������� �� ���� ���������
	//���� ��������� �� SnakeActor �������,�� � ����������� �� value (�� -1 �� 1) �� ������ ������ ����������� �������� ������.
	if (IsValid(SnakeActor))
	{
		if (value > 0 && SnakeActor->LastMoveDirection != EMovementDirection::DOWN) //���� value > 0,�� ������ ����� � ���� ������ ��������� �����,�� �� ����� ���� 
		{			   //�� ������� ����������� �����:
			SnakeActor->LastMoveDirection = EMovementDirection::UP; 
	     //          ���������� �����������      Enum �����
		}
		else if (value < 0 && SnakeActor->LastMoveDirection != EMovementDirection::UP) //���� �������� ������ 0,�� �������� ���� � ���� �� ����� �����,����� ����
		{
			SnakeActor->LastMoveDirection = EMovementDirection::DOWN;
		}
	}

}

//���������� ������ ������/�����
void APlayerPawnBase::HandlePlayerHorizontallInput(float value)
{
	if (IsValid(SnakeActor))
	{
		if (value > 0 && SnakeActor->LastMoveDirection!=EMovementDirection::LEFT) //���� value > 0,�� ������ D � ���� ������ ��������� ������,�� �� ����� �����
		{			   //�� ������� ����������� ������:
			SnakeActor->LastMoveDirection = EMovementDirection::RIGHT;
			//          ���������� �����������      Enum �����
		}
		else if (value < 0 && SnakeActor->LastMoveDirection != EMovementDirection::RIGHT) //�������� ������ 0,�� �������� ����� � ���� ������ ��������� �����,�� �� ����� ������
		{
			SnakeActor->LastMoveDirection = EMovementDirection::LEFT;
		}
	}
}

 