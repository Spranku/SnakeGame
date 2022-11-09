// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnBase.h"
#include <Engine/Classes/Camera/CameraComponent.h> // #include "Engine/Classes/Camera/CameraComponent.h" �� �������� � UE5
#include <SnakeGame/Snake.h>
#include "Food.h"
#include <Components/InputComponent.h>

// Sets default values
APlayerPawnBase::APlayerPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ������� ��������� ������
	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Pawn Camera"));
	RootComponent = PawnCamera;
	
}

// Called when the game starts or when spawned
void APlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();

	SetActorRotation(FRotator(-90, 0, 0));
	//�������� ������� �������� ������
	CreateSnakeActor(); 
	//�������� ������� �������� ���
	CreateFoodActor();
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

	// ������ �� ��� input �� ���������
	PlayerInputComponent->BindAxis("Vertical", this, &APlayerPawnBase::HandlePlayerVerticalInput);
	// ��������� �����,� ������� ��������� �����.�.�. ����� ����� ���������� ������ ������ Pawn,����� this
	// ��� ������ ��������� ������ ������ & ��� ������ (&AplayerPawnBase)
	// ����� ����� :: ��������� ��� ������ ���������� ������ ( HandlePlayerVerticalInput / HandlePlayerHorizontallInput
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerPawnBase::HandlePlayerHorizontallInput);

}

// ������� �������� ������
void APlayerPawnBase::CreateSnakeActor() 
{
	// GetWorld - ����� �� ����� ������� Spawn Actor
	// � < > ��������� ���������� ����� Snake 
	// ����� � ( ) �� ������ �������� ��� ����� ��� ���,�� � ��������� ::StaticClass
	// ����� �� ��������� ���,����� �������� ���������� � .h ����� SnakeActorClass
	// �������� Transform ����� ������ (�������� �� ����� ���������)
	SnakeActor = GetWorld()->SpawnActor<ASnake>(SnakeActorClass, FTransform()); 
}
//������� ������ ���
void APlayerPawnBase::CreateFoodActor()
{
	Food = GetWorld()->SpawnActor<AFood>(FoodActorClass, FTransform());
	Food->SetActorLocation(FVector(14.0, -108, -2.0));
}

// ���������� ������ �����/����
void APlayerPawnBase::HandlePlayerVerticalInput(float value)
{ 
	// ������ ����� ���� ��������� ������� �� ���� ���������.���� ��������� �� SnakeActor �������,
	// �� � ����������� �� value (�� -1 �� 1) �� ������ ������ ����������� �������� ������.
	if (IsValid(SnakeActor))
	{
		//���� value > 0,�� ������ ����� � ���� ������ ��������� �����,�� �� ����� ����
		if (value > 0 && SnakeActor->LastMoveDirection != EMovementDirection::DOWN)  
		{			   // �� ������� ����������� �����:
			SnakeActor->LastMoveDirection = EMovementDirection::UP; 
	     //          ���������� �����������      Enum �����
		}
		//���� �������� ������ 0,�� �������� ���� � ���� �� ����� �����,����� ����
		else if (value < 0 && SnakeActor->LastMoveDirection != EMovementDirection::UP) 
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
		//���� value > 0,�� ������ D � ���� ������ ��������� ������,�� �� ����� �����
		if (value > 0 && SnakeActor->LastMoveDirection!=EMovementDirection::LEFT) 
		{			   //�� ������� ����������� ������:
			SnakeActor->LastMoveDirection = EMovementDirection::RIGHT;
			//          ���������� �����������      Enum �����
		}
		//�������� ������ 0,�� �������� ����� � ���� ������ ��������� �����,�� �� ����� ������
		else if (value < 0 && SnakeActor->LastMoveDirection != EMovementDirection::RIGHT) 
		{
			SnakeActor->LastMoveDirection = EMovementDirection::LEFT;
		}
	}
}






 