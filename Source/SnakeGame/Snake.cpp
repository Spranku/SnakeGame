// Fill out your copyright notice in the Description page of Project Settings.


#include "Snake.h"
// ����������� ����� �����������,����� ��� ������������
#include "Interactable.h"
// ����������� header ������ ������ SnakeElement
#include "SnakeElementBase.h"	

// Sets default values
ASnake::ASnake()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �� ������ ������ ������������� ��������,�������� ElementSize
	ElementSize = 60.f;  

	// �������� �� ��������� 10
	MovementSpeed = 0.5f; 
   
	// ����������� �������� �� ���������
	LastMoveDirection = EMovementDirection::DOWN; 
}

// Called when the game starts or when spawned
void ASnake::BeginPlay()
{
	Super::BeginPlay();

	// ����� �������� ������� Tick. �.�. ��� ����� ��������,�� �� ����� ���. ��������� ���������� MovementSpeed.
	// �� ���� ���������� ��� �������� ��/���,�� ������ ��� ����� ���������� ���������� ������ �������. 
	// ��� � ������� ������ ������ ����� ������������ ����� �� ElementSize;
	SetActorTickInterval(MovementSpeed);	
	// ��� ������� �������������� ��� �������� ������ ������.����� �� ������� ����� �������� - � ����� ������!
	// GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, GetActorTransform()); //������� �������� ������ �� BeginPlay.��������� ���� ��� GetActorTransform
	// ��� ������ ���� ������ ����� �������� �� 5 ���������
	AddSnakeElement(5); 

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &ASnake::HighSpeed, 90.f, false); // 60

	FTimerHandle Handle2;
	GetWorld()->GetTimerManager().SetTimer(Handle2, this, &ASnake::HighSpeed2, 200.f, false); // 120

	FTimerHandle Handle3;
	GetWorld()->GetTimerManager().SetTimer(Handle3, this, &ASnake::HighSpeed3, 310.f, false); // 240
}

// Called every frame
void ASnake::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// �������� ������ ����. DeltaTime ����� ��� ����,����� ���������� �� ����������� �� ������.
	// DeltaTime ������ �� �����
	Move(); 
}

// ��������,������� �� �������� � Snake.h (�������� �� ��������� ����������� �� ����!)
void ASnake::AddSnakeElement(int ElementsNum)	
{
	// ���� �� 0 �� ���-�� ���������
	for (int i = 0; i < ElementsNum; ++i)		
	{
		// 1 �������:������ �������� �������,����������� � ����������
		// auto NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, GetActorTransform());    //Transform ������ ��� ������� ���� � ��� ��
		// //������ ���-�� ���������:
		// SnakeElements.Num(); - ���� �� ������ ������ ��������� � ������� ���
		// SnakeElements.Num()*ElementSize; - ���� Num ������ 0,�� �� ������� ��� �� ElementSize
		// � ����� ������ FTransform �����:
		// auto NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass,FTransform (GetActorLocation()-FVector(SnakeElements*ElementSize,0,0));
		// ����� ��������� ��� ������, ���������� Location: FVector NewLocation(...)

		// ������ ������������ Location
		FVector NewLocation(SnakeElements.Num()*ElementSize, 0, 0); 

		// FTransform NewTransform = FTransform(GetActorLocation()-FVector(SnakeElements.Num() * ElementSize, 0, 0));
		// � � ������ ������ ����� ����� ������� �������� ���: 
		// auto NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform())
		// � ����� ���������:

		// ���������� NewLocation ����� ����������������� Transform
		FTransform NewTransform(NewLocation); 
		// ���������� ����� �������,��������� ��� � ����������
		ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform); 
		NewSnakeElem->SetActorHiddenInGame(true);
		
		// NewSnakeElem->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform); //������������ Actor`a. � �������� ������ ������������� ��������� KeepRelative
		// ������� �� ���������� ���� ������,�.�. ��� ����������� AttachToActor ����� ������. �������� ���� �� ������ ����.

		// ��� ���������� ������ �����, �� ����� ������������� ������� �������� SnakeOwner.
		// SnakeOwner ������������� � this.
		NewSnakeElem->SnakeOwner = this;

		// ������ �������� � ������
		int32 ElemIndex = SnakeElements.Add(NewSnakeElem); 
		// �� ����� ���������� �������� ����� ����� ������� int32 ElemIndex = ...
		// �������� ���� ElemIndex = 0,�� ��� ������ ������
		if (ElemIndex == 0)
		{
			// ����� ������,������� ����� ������ �������� ��� �� - ������.
			NewSnakeElem->SetFirstElementType(); 

			// ��� ���������� �������� � ������. ����� ����� �������� �� NewSnakeElem
			// MeshComponent � ����� ������� �� ���� ������������ �������. 
			// ����� ���������� ���� StaticMeshComponent, � ������ ���������
			// BeginOverlap.
			// NewSnakeElem->MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ASnakeElementBase::HandleBeginOverlap);
		}
	}
}

// float DeltaTime ������ �� �����
void ASnake::Move() 
{
	for (int i = SnakeElements.Num() - 1; i > 0; i--)
	{
		SnakeElements[0]->SetActorHiddenInGame(false);
		SnakeElements[i]->SetActorHiddenInGame(false);
	}

	// ������ ��������
	FVector MovementVector(ForceInitToZero);
	// float DeltaTime ������ �� �����
	float  MovmentSpeed = ElementSize; 

	// 1 ������� ����������:
 
	// if (LastMoveDirection == EMovementDirection::UP) //���� ��������� ����������� �������� = �����,��
	// {
	//	 MovementVector = FVector(MovementSpeedDelta,0,0); // FVector() � ������������� X
	// }
	//
	
	// 2 ������� ����������:
	switch (LastMoveDirection)
	{
	case EMovementDirection::UP:			//���� �������� ������,��
		MovementVector.X += MovmentSpeed; //����������� ��� �����������
		break;
	case EMovementDirection::DOWN:				//���� �������� ����,��
		MovementVector.X -= MovmentSpeed;  //+ �������� �� - (��� ��������������� ��������)
		break;
	case EMovementDirection::LEFT:           //���� �������� �����,��
		MovementVector.Y += MovmentSpeed; //����������� ������ �� ��� Y
		break;
	case EMovementDirection::RIGHT:           //�������������� ���� �������,
		MovementVector.Y -= MovmentSpeed; //�� ������ + �� -
		break;
	}

	// AddActorWorldOffset(MovementVector); //���������� ��� Actor
	// ����� ������� ��� ������ ��� ���������� ����������� ������ �� ������ 

	// ������� ����� ������ Toggle ����� ���, ��� ������� ��� �����
	// ������� ������� 0 ������� � ������� �� �� ToggleCollision
	SnakeElements[0]->ToggleCollision();

	// ��� ����,����� ����� � ������ ����������� ��� ���� ����� �� 1,
	// �������� ���� for ,����� �������� ����� ������ ������� �� ����� �����.
	for (int i = SnakeElements.Num() - 1; i > 0; i--)
	{
		// � ���� ����� ����� �������� ������� �������:
		auto CurrentElement = SnakeElements[i];
		// ���������� �������:
		auto PrevElement = SnakeElements[i - 1];
		// ����� ����� ������� ��� ������� � ����������� �����������.
		// ��� ����� � ����������� �������� �������� ����� � ������������,������� ����� ����� ��� Location:
		FVector PrevLocation = PrevElement->GetActorLocation();
		// � ������� ������� ����� ������� �� ����� �����������:
		CurrentElement->SetActorLocation(PrevLocation);
	}
	SnakeElements[0]->AddActorWorldOffset(MovementVector);
	// �������� ��������. � ������ �� ���������, ����� �����������
	// ��� �����, ����������� ������, �������� �������� �������. 
	SnakeElements[0]->ToggleCollision();
}

// �������� ���������� ������ ������ ������
// �.�. �� ����� ��������� ��������� � h. �����, � ��� ���� �������� AActor* Other
void ASnake::SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other) 
{
	// ��������� ��������� �� ����������.���� ��������� 
	// �������,�� �� ����� ����� ���������� ����.
	if (IsValid(OverlappedElement))
	{
		
		// �������� ����������, � ������� 
		// ����� ���������� ��� ������.
		// 
		// ������� ���� ������ SnakeElements � ��� ������
		// ������ Find ������ ������ ���������� ��������.
		// 
		// ���������� � ������� ���������� bISFirst
		// �������� � ���,��� ��� ���� �������� �������.
		// 
		// � ��������� � ������� ������� ������� �������
		// overlapped � ������.
		int32 ElemIndex;
		SnakeElements.Find(OverlappedElement, ElemIndex);
		bool bIsFirst = ElemIndex == 0;
		// ���� ������ = 0, �� ������� � ��� ������ (������)
		//
		// ������ ����� ����������� �������� ���������� ����:
		// ������� ��������� �� ��� ��������� (� ��������� -
		// ��� �����) � ���������� ��� ������ Unreal cast 
		// ��� ����� � ����� �����������.� ��������� 
		// ��������� ������ Actor`a.
		IInteractable* InteractableInterface = Cast<IInteractable>(Other);
		

		// ����� ������ ������� �� ����������� Actor, ��������� ���
		// ��������� ��������� �� �������:
		if (InteractableInterface)
		{
			// �� �����������, ��� � ������� �������� ��� ��������
			// ��������� � ��� ���� ����� (� ������� ������ ������������)
			// �������� ��� �������,������� �������������� �������� ���������.
			// �������� ����� Interact � �������� ������,�������
			// ������������� � Actor`��,��������������� ������ 
			// ���������.
			InteractableInterface->Interact(this, bIsFirst);
			// ������ ����� ������ ����� �������� ��� �� ��� ������� ������,
			// ������ - ������� (bIsFirst)
			// 
			// ������������� � ����� ����� ���������� �������� � ���,����������
			// �� �������� � ������� ������.
		}
	}	
}

void ASnake::HighSpeed()
{
	SetActorTickInterval(MovementSpeed = 0.35);
}

void ASnake::HighSpeed2()
{
	SetActorTickInterval(MovementSpeed = 0.25);
}

void ASnake::HighSpeed3()
{
	SetActorTickInterval(MovementSpeed = 0.1);
}

void ASnake::DestroySnake()
{
	
}




