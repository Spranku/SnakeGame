// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeElementBase.generated.h"

class UStaticMeshComponent;

UCLASS()
class SNAKEGAME_API ASnakeElementBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeElementBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) 
	UStaticMeshComponent* MeshComponent; //Добавление статик мэш компонента,чтобы переменную нельзя было переназначить в BP

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

};
