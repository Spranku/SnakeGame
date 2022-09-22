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
	CreateSnakeActor(); //Вызываем функцию создания змейки
}

// Called every frame
void APlayerPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) //Здесь мы будем настраивать наш input
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Ивенты на наш input мы забиндили
	PlayerInputComponent->BindAxis("Vertical", this, &APlayerPawnBase::HandlePlayerVerticalInput);
	//Указываем класс,в котором находится метод.Т.к. метод будет находиться только внутри Pawn,пишем this
	//При помощи оператора взятия адреса & имя класса (&AplayerPawnBase)
	//Потом через :: указываем имя нашего созданного метода ( HandlePlayerVerticalInput / HandlePlayerHorizontallInput
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerPawnBase::HandlePlayerHorizontallInput);

}

void APlayerPawnBase::CreateSnakeActor() //Функция создания змейки
{
	//GetWorld - чтобы мы могли вызвать Spawn Actor
	//В < > указываем конкретный класс Snake 
	//Далее в ( ) мы должны передать наш класс еще раз,но с указанием ::StaticClass
	//Чтобы не указывать это,можно записать переменную и .h файла SnakeActorClass
	//Передаем Transform нашей змейке (допустим он будет дефолтным)
	SnakeActor = GetWorld()->SpawnActor<ASnake>(SnakeActorClass, FTransform()); 
}

//Реализация эвента вверх/вниз
void APlayerPawnBase::HandlePlayerVerticalInput(float value)
{ 
	//Прежде всего надо проверить валиден ли этот указатель
	//Если указатель на SnakeActor валиден,то в зависимости от value (от -1 до 1) мы должны менять направление движения змейки.
	if (IsValid(SnakeActor))
	{
		if (value > 0 && SnakeActor->LastMoveDirection != EMovementDirection::DOWN) //Если value > 0,то нажата ВВЕРХ И если змейка двигается вверх,то не равно ВНИЗ 
		{			   //Мы зададим направление вверх:
			SnakeActor->LastMoveDirection = EMovementDirection::UP; 
	     //          переменная направления      Enum класс
		}
		else if (value < 0 && SnakeActor->LastMoveDirection != EMovementDirection::UP) //Если значение меньше 0,то движение вниз И если не равно ВВЕРХ,тогда ВНИЗ
		{
			SnakeActor->LastMoveDirection = EMovementDirection::DOWN;
		}
	}

}

//Реализация эвента вправо/влево
void APlayerPawnBase::HandlePlayerHorizontallInput(float value)
{
	if (IsValid(SnakeActor))
	{
		if (value > 0 && SnakeActor->LastMoveDirection!=EMovementDirection::LEFT) //Если value > 0,то нажата D И если змейка двигается ВПРАВО,то не равно ВЛЕВО
		{			   //Мы зададим направление вправо:
			SnakeActor->LastMoveDirection = EMovementDirection::RIGHT;
			//          переменная направления      Enum класс
		}
		else if (value < 0 && SnakeActor->LastMoveDirection != EMovementDirection::RIGHT) //Значение меньше 0,то движение влево И если змейка двигается ВЛЕВО,то не равно ВПРАВО
		{
			SnakeActor->LastMoveDirection = EMovementDirection::LEFT;
		}
	}
}

 