// Fill out your copyright notice in the Description page of Project Settings.


#include "Snake.h"
#include "Interactable.h"		//����������� ����� �����������,����� ��� ������������
#include "SnakeElementBase.h"	//����������� header ������ ������ SnakeElement

// Sets default values
ASnake::ASnake()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ElementSize = 100.f;  //������ �� ������ ������ ������������� ��������,�������� ElementSize

	MovementSpeed = 10.f; //�������� �� ��������� 10

	LastMoveDirection = EMovementDirection::DOWN; // ����������� �������� �� ���������
}

// Called when the game starts or when spawned
void ASnake::BeginPlay()
{
	Super::BeginPlay();

	//����� �������� ������� Tick. �.�. ��� ����� ��������,�� �� ����� ���. ��������� ���������� MovementSpeed.
	//�� ���� ���������� ��� �������� ��/���,�� ������ ��� ����� ���������� ���������� ������ �������. 
	//��� � ������� ������ ������ ����� ������������ ����� �� ElementSize;
	SetActorTickInterval(MovementSpeed);

	//��� ������� �������������� ��� �������� ������ ������.����� �� ������� ����� �������� - � ����� ������!
	//GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, GetActorTransform()); //������� �������� ������ �� BeginPlay.��������� ���� ��� GetActorTransform

	AddSnakeElement(5); //��� ������ ���� ������ ����� �������� �� 5 ���������
}

// Called every frame
void ASnake::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(); // �������� ������ ����. DeltaTime ����� ��� ����,����� ���������� �� ����������� �� ������.//DeltaTime ������ �� �����
}

void ASnake::AddSnakeElement(int ElementsNum)	//��������,������� �� �������� � Snake.h (�������� �� ��������� ����������� �� ����!)
{
	for (int i = 0; i < ElementsNum; ++i)		//���� �� 0 �� ���-�� ���������
	{
		//1 �������:������ �������� �������,����������� � ����������
		//auto NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, GetActorTransform());    //Transform ������ ��� ������� ���� � ��� ��
		// //������ ���-�� ���������:
		//SnakeElements.Num(); - ���� �� ������ ������ ��������� � ������� ���
		//SnakeElements.Num()*ElementSize; - ���� Num ������ 0,�� �� ������� ��� �� ElementSize
		// � ����� ������ FTransform �����:
		// auto NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass,FTransform (GetActorLocation()-FVector(SnakeElements*ElementSize,0,0));
		// ����� ��������� ��� ������, ���������� Location: FVector NewLocation(...)

		FVector NewLocation(SnakeElements.Num()*ElementSize, 0, 0); //������ ������������ Location

		//FTransform NewTransform = FTransform(GetActorLocation()-FVector(SnakeElements.Num() * ElementSize, 0, 0));
		// � � ������ ������ ����� ����� ������� �������� ���: 
		// auto NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform())
		//� ����� ���������:

		FTransform NewTransform(NewLocation); //���������� NewLocation ����� ����������������� Transform
		ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform); //���������� ����� �������,��������� ��� � ����������

		//NewSnakeElem->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform); //������������ Actor`a. � �������� ������ ������������� ��������� KeepRelative
		//������� �� ���������� ���� ������,�.�. ��� ����������� AttachToActor ����� ������. �������� ���� �� ������ ����.

		//��� ���������� ������ �����, �� ����� ������������� ������� �������� SnakeOwner.
		//SnakeOwner ������������� � this.
		NewSnakeElem->SnakeOwner = this;

		int32 ElemIndex = SnakeElements.Add(NewSnakeElem); //������ �������� � ������
		//�� ����� ���������� �������� ����� ����� ������� int32 ElemIndex = ...
		//�������� ���� ElemIndex = 0,�� ��� ������ ������
		if (ElemIndex == 0)
		{
			NewSnakeElem->SetFirstElementType(); // ����� ������,������� ����� ������ �������� ��� �� - ������.
		}
	}

}

void ASnake::Move() //float DeltaTime ������ �� �����
{
	FVector MovementVector(ForceInitToZero); //������ ��������
	float  MovmentSpeed = ElementSize; //float DeltaTime ������ �� �����

	//1 ������� ����������:
 
	//if (LastMoveDirection == EMovementDirection::UP) //���� ��������� ����������� �������� = �����,��
	//{
	//	MovementVector = FVector(MovementSpeedDelta,0,0); // FVector() � ������������� X
	//}
	//
	
	//2 ������� ����������:
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

	//AddActorWorldOffset(MovementVector); //���������� ��� Actor
	//����� ������� ��� ������ ��� ���������� ����������� ������ �� ������ 

	//��� ����,����� ����� � ������ ����������� ��� ���� ����� �� 1,
	//�������� ���� for ,����� �������� ����� ������ ������� �� ����� �����.
	for (int i = SnakeElements.Num() - 1; i > 0; i--)
	{
		//� ���� ����� ����� �������� ������� �������:
		auto CurrentElement = SnakeElements[i];
		//���������� �������:
		auto PrevElement = SnakeElements[i - 1];
		//����� ����� ������� ��� ������� � ����������� �����������.
		//��� ����� � ����������� �������� �������� ����� � ������������,������� ����� ����� ��� Location:
		FVector PrevLocation = PrevElement->GetActorLocation();
		//� ������� ������� ����� ������� �� ����� �����������:
		CurrentElement->SetActorLocation(PrevLocation);
	}
	SnakeElements[0]->AddActorWorldOffset(MovementVector);
}

//�������� ���������� ������ ������ ������
void ASnake::SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other) //�.�. �� ����� ��������� ��������� � h. �����, � ��� ���� �������� AActor* Other
{
	//��������� ��������� �� ����������.���� ��������� 
	//�������,�� �� ����� ����� ���������� ����.
	if (IsValid(OverlappedElement))
	{
		//�������� ����������, � ������� 
		//����� ���������� ��� ������.
		// 
		//������� ���� ������ SnakeElements � ��� ������
		// ������ Find ������ ���������� ��������.
		// 
		//���������� � ������� ���������� bISFirst
		//�������� � ���,��� ��� ���� �������� �������.
		// 
		//� ��������� � ������� ������� ������� �������
		//overlapped � ������.
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
			//������ ����� ������ ����� �������� ��� �� ��� ������� ������,
			// ������ - ������� (bIsFirst)
			// 
			//������������� � ����� ����� ���������� �������� � ���,����������
			//�� �������� � ������� ������.
		}
	}
	
}

