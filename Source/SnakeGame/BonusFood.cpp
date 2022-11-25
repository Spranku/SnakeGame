// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusFood.h"
#include "Snake.h" //Подключение header`а змейки для проверки события
#include "PlayerPawnBase.h"

void ABonusFood::BeginPlay() 
{
	Super::BeginPlay();

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &ABonusFood::SetLocation, 100.f, false);

	FTimerHandle Handle2;
	GetWorld()->GetTimerManager().SetTimer(Handle2, this, &ABonusFood::SetLocation2, 400.f, false);

	FTimerHandle Handle3;
	GetWorld()->GetTimerManager().SetTimer(Handle3, this, &ABonusFood::SetLocation3, 800.f, false);
}

void ABonusFood::Interact(AActor* Interactor, bool bIsHead)   // ��������� bIsHead � ��� ����
{
	// Пишем усоовия проверки: если наступило событие и это
	// голова - то в змейку нужно добавить 1 элемент 
	// Для этого подключим заголовочный Snake.h
	if (bIsHead)
	{
		// Каст интеракта к змейке.
		auto Snake = Cast<ASnake>(Interactor);
		// После проверим полученный указатель на валидность 
		if (IsValid(Snake))
		{
			//Snake->DestroySnake();
			//Snake->DestroySnake();
			Snake->Score+= Bonus;
			Snake->newScore = Snake->Score;
			// Возможная конструкция для спавна еды?
			// if(Snake->Score > 10)
			// {
			//	 this =  GetWorld()->SpawnActor(....
			// }
			// 
			// Уничтожение еды после overlap
			this->Destroy();
		}
	}
}

void ABonusFood::SetLocation()
{
	this->SetActorLocation(FVector(100, -100, -2.0));
}

void ABonusFood::SetLocation2()
{
	this->SetActorLocation(FVector(363, -894, -2.0));
}

void ABonusFood::SetLocation3()
{
	this->SetActorLocation(FVector(753, -1090, -2.0));
}
