// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnBox.h"

// Sets default values
ASpawnBox::ASpawnBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// ������������� SpawnBox()
	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	RootComponent = SpawnBox;
}

// Called when the game starts or when spawned
void ASpawnBox::BeginPlay()
{
	Super::BeginPlay();
	
	// ����� ������� ������\
	// ���� ������ ����������,
	// ����� ��������� ����� ������
	if (ShouldSpawn)
	{
		ScheduleActorSpawn();
	} 

	// ������� �� ���������� ���� ������
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &ASpawnBox::GetScale, 90.f, false); // 60

	FTimerHandle Handle2;
	GetWorld()->GetTimerManager().SetTimer(Handle2, this, &ASpawnBox::GetScale2, 200.f, false); // 120

	FTimerHandle Handle3;
	GetWorld()->GetTimerManager().SetTimer(Handle3, this, &ASpawnBox::GetScale3, 310.f, false); // 180

}

void ASpawnBox::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//EEndPlayReason::Destroyed;
	// 
	//throw std::logic_error("The method or operation is not implemented.");

	// �������� �������
	//GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

// Called every frame
void ASpawnBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ASpawnBox::SpawnActor()
{
	bool SpawnedActor = false;
	// �������� ������������ �� �����,������� ����� ����������
	if (ActorClassToBeSpawned)
	{
		// ������ ������� ����
		// ������ ����� ��������� FBo�SphereBounds
		// ����� ��������� ������� ����� ��������� ��������������
		// ����� �������� GetActorTransform
		FBoxSphereBounds BoxBounds = SpawnBox->CalcBounds(GetActorTransform());
		// ���������� ���������� ��������� ������ ����
		// Origin - � �������� ����� ����
		FVector SpawnLocation = BoxBounds.Origin;
		// ������ ���������� �������������� ������
		// ������ ��������� X,Y,Z
		// ������� X,Y,Z ���� ������ ����
		// �������� �� ��������� �����
		// �� �.�. ������ ���� ���������� � ������������� � ������������� ������������
		// ������� �������� �� 2.�������� � ������������� �����������,�� �� � �������������
		// ������� ����� ������� ������ ������� ������������� ������ ����.
		// ��������� ��� Y,Z
		SpawnLocation.X += -BoxBounds.BoxExtent.X + 2 * BoxBounds.BoxExtent.X * FMath::FRand();
		SpawnLocation.Y += -BoxBounds.BoxExtent.Y + 2 * BoxBounds.BoxExtent.Y * FMath::FRand();
		SpawnLocation.Z += -BoxBounds.BoxExtent.Z + 2 * BoxBounds.BoxExtent.Z * FMath::FRand();
		// ����� ������
		SpawnedActor = GetWorld()->SpawnActor(ActorClassToBeSpawned, &SpawnLocation) != nullptr;
	}
	return SpawnedActor;
}

void ASpawnBox::ScheduleActorSpawn()
{
	// 1.���������� ���������� ��������
	float DeltaToNextSpawn = AvgSpawnTime + (-RandomSpawnTimeOffset + 2 * RandomSpawnTimeOffset * FMath::FRand());

	// 2. ������������� �����
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle,this , &ASpawnBox::SpawnActorScheduled, DeltaToNextSpawn, false);
}

void ASpawnBox::GetScale()
{
	this->SetActorScale3D(FVector(15.0,15.0,-0.25));
}

void ASpawnBox::GetScale2()
{
	this->SetActorScale3D(FVector(19.0,19.0,-0.25));
}

void ASpawnBox::GetScale3()
{
	this->SetActorLocation(FVector(55.0, 35.0, 0.0));
	this->SetActorScale3D(FVector(21.5, 46.5, -0.25));
}

void ASpawnBox::SpawnActorScheduled()
{
	//// ����� � ��������������
	if (SpawnActor())
	{
		if (ShouldSpawn)
		{
			ScheduleActorSpawn();
		}
	}
	else 
	{
		ScheduleActorSpawn();
	}
}

