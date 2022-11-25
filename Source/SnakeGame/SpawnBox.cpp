// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnBox.h"

// Sets default values
ASpawnBox::ASpawnBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Инициализация SpawnBox()
	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	RootComponent = SpawnBox;
}

// Called when the game starts or when spawned
void ASpawnBox::BeginPlay()
{
	Super::BeginPlay();
	
	// Время первого спавна\
	// Если должен спавниться,
	// тогда планируем время спавна
	if (ShouldSpawn)
	{
		ScheduleActorSpawn();
	} 

	// Таймеры на увеличение поля спавна
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

	// Удаление таймера
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
	// Проверка действителен ли класс,который будет реализован
	if (ActorClassToBeSpawned)
	{
		// Расчет размера поля
		// Расчет будет вычислять FBoхSphereBounds
		// Чтобы вычислить границы нужно локальное преобразование
		// Можем получить GetActorTransform
		FBoxSphereBounds BoxBounds = SpawnBox->CalcBounds(GetActorTransform());
		// Вычисление случайного положения внутри поля
		// Origin - в основном центр поля
		FVector SpawnLocation = BoxBounds.Origin;
		// Логика случайного местоположения спавна
		// Меняем положения X,Y,Z
		// Смещаем X,Y,Z взяв размер поля
		// Умножаем на случайное число
		// Но т.к. размер поля изменяется в положительном и отрицательном направлениях
		// Поэтому умножаем на 2.Движемся в положительном направлении,но не в отрицательном
		// Поэтому самый простой способ сделать отрицательным размер поля.
		// Повторяем для Y,Z
		SpawnLocation.X += -BoxBounds.BoxExtent.X + 2 * BoxBounds.BoxExtent.X * FMath::FRand();
		SpawnLocation.Y += -BoxBounds.BoxExtent.Y + 2 * BoxBounds.BoxExtent.Y * FMath::FRand();
		SpawnLocation.Z += -BoxBounds.BoxExtent.Z + 2 * BoxBounds.BoxExtent.Z * FMath::FRand();
		// Спавн актора
		SpawnedActor = GetWorld()->SpawnActor(ActorClassToBeSpawned, &SpawnLocation) != nullptr;
	}
	return SpawnedActor;
}

void ASpawnBox::ScheduleActorSpawn()
{
	// 1.Вычисления временного смещения
	float DeltaToNextSpawn = AvgSpawnTime + (-RandomSpawnTimeOffset + 2 * RandomSpawnTimeOffset * FMath::FRand());

	// 2. Запланировать спавн
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
	//// Спавн и перепланировка
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

