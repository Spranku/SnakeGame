// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Food.h"
#include "PlayerPawnBase.generated.h"

// forward declaration. Сообщаем компилятору,что используем класс UCamera Component
class UCameraComponent;	 
// forward declaration. Чтобы использовать её в .h файле класса.Перфикс А - потому что наследовано от Actor
class ASnake;			 

UCLASS()
class SNAKEGAME_API APlayerPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawnBase();

	//Подключаем компонент камеры
	UPROPERTY(BlueprintReadWrite)	
	UCameraComponent* PawnCamera;	

	// Чтобы удобно настравивать исп-мые ассеты змейки,мы будем наследоваться от С++ класса в ВР.
	// И для того,чтобы указать ВР класс как то,что нужно заспавнить,мы будем хранить 
	// переменную конкретного класса змейки,которую будем передвавать в Spawn Actor
	UPROPERTY(BlueprintReadWrite)	
	ASnake* SnakeActor;	
	
	// EditDefaultsOnly означает,что мы можем редактировать эту переменную только 
	// в дефолтных настройках класса (увидим в правом меню наследника в UE)
	UPROPERTY(EditDefaultsOnly)				
	TSubclassOf<ASnake> SnakeActorClass;
	// Так записывается переменная,которая представляет собой конкр.указатель 
	// на НЕ ОБЪЕКТ,а сам по себе КЛАСС,который мы будем передвать в качестве параметра для spawn
	
	UPROPERTY(BlueprintReadWrite)
	AFood* Food;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFood> FoodActorClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Функция создания змейки
	void CreateSnakeActor(); 
	// Функция создания еды
	void CreateFoodActor();

	// Методы на вертикальный и горизонтальный input`ы
	UFUNCTION()
	void HandlePlayerVerticalInput(float value);  

	UFUNCTION()
	void HandlePlayerHorizontallInput(float value); 

	
	


};
