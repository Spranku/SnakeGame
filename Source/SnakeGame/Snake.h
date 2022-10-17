// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Snake.generated.h"

class ASnakeElementBase; //forward declaration. Указываем элемент змейки

UENUM()
enum class EMovementDirection //Для направления движения используется перечисление enum
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

	UPROPERTY(EditDefaultsOnly)//Доступно для редактирования в BP
	TSubclassOf<ASnakeElementBase> SnakeElementClass; //Переменная с классом,в которой указан SnakeElement

	UPROPERTY(EditDefaultsOnly) //Доступно для редактирования в BP
		float ElementSize;		//переменная,хранящая размер элемента змейки

	UPROPERTY(EditDefaultsOnly) //Доступно для редактирования в BP
		float MovementSpeed;		//Параметр,отвечающий за скорость змейки

	UPROPERTY()
	TArray<ASnakeElementBase*> SnakeElements; // Массив из УКАЗАТЕЛЕЙ* на элементы

	UPROPERTY()
	EMovementDirection LastMoveDirection; //Сохранение последнего направления движения

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override; 

	UFUNCTION(BlueprintCallable)
	void AddSnakeElement(int ElementsNum = 1); // Дефолтное значение элементов

	UFUNCTION(BlueprintCallable)
	void Move(); //float DeltaTime Метод Move,который будет принимать на вход DeltaTime. Позднее DeltaTime больше не потребуется и его надо удалить везде.

	//Если указатель валидныЙ,то на SnakeOwner будем вызывать ивент,
	//что наш блок сколлизился с чем-либо. В качестве аргумента,в 
	//этот метод из блока будем передавать какой именно блок вызвал
	//данное событие.Создаем имплементацию...
	//
	//Помимо того какой блок сколлизился,змейке так же нужно знать 
	//с чем она сколлизилась.
	// 
	//Создадим второй аргумент Actor`a "Other", который будет передавать Actor`a
	//с которым сколлизился наш блок.
	UFUNCTION()
	void SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other);
	
};
