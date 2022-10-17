// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeElementBase.h"
#include <Engine/Classes/Components/StaticMeshComponent.h>
#include "Snake.h"			//header ������

// Sets default values
ASnakeElementBase::ASnakeElementBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//������ ������ ��� ���������
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));  

	//��������� ���,������� ����� ����������� � ����� ��������
	//������� �������� �� overlap,� � () ������ Quarry only.
	//������ ��� �� �����,�� ����� ������� overlap`��
	//����� ����� �������� ����� �� ���� ������� � ������ ������������:
	//�������  ECR_Overlap
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

// Called when the game starts or when spawned
void ASnakeElementBase::BeginPlay()
{
	Super::BeginPlay();

	//����� �������� ���������,��� ��������� overlap.
	//��� ����� ����� �������� � overlap`a ������ �������.
	//�������� �� ������e overlap � mesh component
	//����� ����� ����� AddDynamic. � () ��������� �����,
	//� ������� ��������� �����,������� ����� �������.
	//� �������� ������� ��������� ��������� �����, ������� �� ��� �����,
	//����� ����� :: ����� ������� ������� (�����) ������, ������� �� ��������� 
	//����� ��������� � ����������� ������� ��� Component Begin Overlapp.
	//����� �������� ������ ������ � SnakeElementBase ����� ������� HandleBeginOverlap.
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ASnakeElementBase::HandleBeginOverlap);
	//������,����� Mesh Component ����� ����������� �� ����� OnComponenntBeginOverlapp,
	//����� ���������� ��� ����� HandleBeginOverlap
}

// Called every frame
void ASnakeElementBase::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

}

//���������� ������� ���� ����� �������!!!
//void ASnakeElementBase::SetFirstElementType() 
//{
//}

void ASnakeElementBase::SetFirstElementType_Implementation() 
{
	//���������� ����� ������ � �++ �� ������� ������,� ��� ����� �� ���������� � BP
}

//������������� ������ ���� ��� ������ ���������� 
void ASnakeElementBase::Interact(AActor* Interactor)
{
}

void ASnakeElementBase::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{

	//������ ������ ��������� overlap`a �������� ���������� ��������� �� ������,
		//����� �����������:
	if (IsValid(SnakeOwner))
	
		//������� �� SnakeOwner �����,������� ������ ��� �������.� ��������
		//��������� ��������� ��������,������� ������ ����� ������������.
		//����� ������� ��������� OtherActor
		SnakeOwner->SnakeElementOverlap(this, OtherActor);
		//������ ������ ����� ����� ���� �����������.����� � ��� �� �����������!
}