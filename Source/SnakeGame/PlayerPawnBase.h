// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawnBase.generated.h"

class UCameraComponent;	 //forward declaration. Сообщаем компилятору,что используем класс UCamera Component
class ASnake;			 //forward declaration. Чтобы использовать её в .h файле класса.Перфикс А - потому что наследовано от Actor

UCLASS()
class SNAKEGAME_API APlayerPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawnBase();

	UPROPERTY(BlueprintReadWrite)	
	UCameraComponent* PawnCamera;	//Подключаем компонент камеры

	UPROPERTY(BlueprintReadWrite)	//Чтобы удобно настравивать исп-мые ассеты змейки,мы будем наследоваться от С++ класса в ВР.И для того,
	ASnake* SnakeActor;				//чтобы указать ВР класс как то,что нужно заспавнить,мы будем хранить переменную конкретного класса змейки,которую будем передвавать в Spawn Actor

	UPROPERTY(EditDefaultsOnly)				//Означает,что мы можем редактировать эту переменную только в дефолтных настройках класса (увидим в правом меню наследника в UE)
	TSubclassOf<ASnake> SnakeActorClass;	//Так записывается переменная,которая представляет собой конкр.указатель на НЕ ОБЪЕКТ,а сам по себе КЛАСС,
											//который мы будем передвать в качестве параметра для spawn

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void CreateSnakeActor(); //Функция создания змейки

	UFUNCTION()
		void HandlePlayerVerticalInput(float value);    //Метод на вертикальный input
	UFUNCTION()
		void HandlePlayerHorizontallInput(float value); //Метод на горизонтальный input

};
