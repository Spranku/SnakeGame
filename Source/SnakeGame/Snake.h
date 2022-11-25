// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Snake.generated.h"

// forward declaration. Указываем элемент змейки
class ASnakeElementBase; 

// Для направления движения используется перечисление enum
UENUM()
enum class EMovementDirection 
{
	UP,DOWN,LEFT,RIGHT
};

UCLASS()
class SNAKEGAME_API ASnake : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnake();

	// EditDefaultsOnly - занчит доступно для редактирования в BP
	UPROPERTY(EditDefaultsOnly)
	// Переменная с классом,в которой указан SnakeElement
	TSubclassOf<ASnakeElementBase> SnakeElementClass; 

	// Переменная,хранящая размер элемента змейки
	UPROPERTY(EditDefaultsOnly) 
		float ElementSize;		

	UPROPERTY(EditDefaultsOnly) //EditDefaultsOnly
	// Параметр,отвечающий за скорость змейки
		float MovementSpeed;		
	   

	UPROPERTY()
	// Массив из УКАЗАТЕЛЕЙ* на элементы
	TArray<ASnakeElementBase*> SnakeElements; 

	UPROPERTY()
	// Сохранение последнего направления движения
	EMovementDirection LastMoveDirection; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Score = 0;

	// Лучший результат
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int newScore = 0;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	int Life = 1;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override; 

	UFUNCTION(BlueprintCallable)
	// Дефолтное значение элементов
	void AddSnakeElement(int ElementsNum = 1); 

	UFUNCTION(BlueprintCallable)
	// float DeltaTime.Позднее DeltaTime больше не потребуется и его надо удалить везде.
	// Метод Move,который будет принимать на вход DeltaTime. 
	void Move(); 
	
	// Если указатель валидныЙ,то на SnakeOwner будем вызывать ивент,
	// что наш блок сколлизился с чем-либо. В качестве аргумента,в 
	// этот метод из блока будем передавать какой именно блок вызвал
	// данное событие.Создаем имплементацию...
	//
	// Помимо того какой блок сколлизился,змейке так же нужно знать 
	// с чем она сколлизилась.
	// 
	// Создадим второй аргумент Actor`a "Other", который будет передавать Actor`a
	// с которым сколлизился наш блок.
	UFUNCTION()
	void SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other);

	void HighSpeed();

	void HighSpeed2();

	void HighSpeed3();

	void DestroySnake();



	
	
};
