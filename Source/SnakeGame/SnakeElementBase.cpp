// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeElementBase.h"
#include <Engine/Classes/Components/StaticMeshComponent.h>

// Sets default values
ASnakeElementBase::ASnakeElementBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Задаем статик мэш 
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent")); //Задаем статик мэш компонент 

}

// Called when the game starts or when spawned
void ASnakeElementBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASnakeElementBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Реализацию старого вида нужно удалить!!!
//void ASnakeElementBase::SetFirstElementType() 
//{
//}

void ASnakeElementBase::SetFirstElementType_Implementation() 
{
	//Реализацию этого метода в С++ мы оставим пустым,а сам метод мы перегрузим в BP
}

