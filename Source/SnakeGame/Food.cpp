// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "Snake.h" //Подключение header`а змейки для проверки события
#include "Block.h"
#include "PlayerPawnBase.h"



// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//������������� ������ �������� ���� �����
void AFood::Interact(AActor* Interactor, bool bIsHead) // ��������� bIsHead � ��� ����
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
		    // Пропишем в  Food вызов одного эдемента.
		    // Мы уже определили AddSnakeElement 
			// () - по умолчанию добавляется 1 элемент.
			Snake->AddSnakeElement();
			Snake->Score++;
			Snake->newScore = Snake->Score;

			// Возможная конструкция для спавна еды?
			// if(Snake->Score > 10)
			// {
			//	 this =  GetWorld()->SpawnActor(....
			// }
				
			// Уничтожение еды после overlap
			this->Destroy();
		}
	}
}








	








