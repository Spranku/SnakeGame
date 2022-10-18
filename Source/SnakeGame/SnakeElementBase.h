// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"		//Подкл.класса интерфейса 
#include "SnakeElementBase.generated.h"

class UStaticMeshComponent;
class ASnake; // forvard-declaration,т.к. здесь ничего не известно о существовании Asnake. В срр файле подключим h.

UCLASS()
class SNAKEGAME_API ASnakeElementBase : public AActor, public IInteractable		//мн.наследование
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeElementBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) 
	UStaticMeshComponent* MeshComponent; //Добавление статик мэш компонента,чтобы переменную нельзя было переназначить в BP

	//Всё это время в Snake Element внешнего доступа к змейке нет.
	//Мы будем хранить указатель на змейку, которая заспавнила данный элемент.
	//Прописываем указатель на змейку, которая владеет данным блоком.
	UPROPERTY()
		ASnake* SnakeOwner; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)			   // Аргумент позволит перегурзить С++ эвент-метод в BP-наследнике
    void SetFirstElementType();				   //Event,который точно скажет элементу что он - первый.
	void SetFirstElementType_Implementation(); //Еще одна реализация метода.Реализацию этого метода в С++ мы оставим пустым
	//Эту реалищацию мы напрямую никогда не вызовем,ведь мы вызываем наш метод.

	//Добавляем имплементацию метода Interact
	virtual void Interact(AActor* Interactor , bool bIsHead) override; // добавялем bIsHead в файл

	//Напишем метод HandleBeginOverlap
	//Примитив-компонент указатель - будет overlap component
	//А так же Actor,который с`overlap`ился 
	//Далее примитив-компонент другого Actor`a,который вызвал событие overlap`а
	//После этого техническая информация типа...
	UFUNCTION()
		void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComponent,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
		//Изнутри блока будем сообщать змейке если вдруг она с чем-то столкнется.
		//Будет момент, когда змейка должна будет кушать класс Food. У нас уже есть
		//ивент SetFirstElementType, с ним будет проще показать, что змейка будет
		//есть головой, а не хвостом (для этого существует отдельный метод),а
		//поэтому нашей змейке нужно дополнительно сообщить, что элемент "голова"
		//является первым.

	UFUNCTION()
		//Необходим метод,который будем вызывать из змейки.
		void ToggleCollision();

};
