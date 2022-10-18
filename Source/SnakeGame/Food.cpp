// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "Snake.h" //Подключение header`а змейки для проверки события

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

//Имплементация метода остается пока пуста
void AFood::Interact(AActor* Interactor, bool bIsHead) // добавялем bIsHead в срр файл
{
	// Условие проверки: Если наступило событие, и это - голова,
	// то в змейку надо добавить один элемент. Для этого 
	// подключим заголовочный Snake.h
	if (bIsHead)
	{
		
		//Каст интеракта к змейке.
		auto Snake = Cast<ASnake>(Interactor);
	    //Проверка полученного указателя на валидность
		if (IsValid(Snake))
		{
			// Пропишем в Food вызов одного элемента.
			// Пустые скобки подразумевают,что будет 
			// добавлен один элемент по умолчанию.
			Snake->AddSnakeElement();

			//Уничтожение еды после overlap
			this->Destroy();
			
		}

	}
}

