// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeElementBase.h"
#include <Engine/Classes/Components/StaticMeshComponent.h>
#include "Snake.h"			//header змейки

// Sets default values
ASnakeElementBase::ASnakeElementBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Задаем статик мэш компонент
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));  

	//Добавляем мэш,который может коллизиться с любым объектом
	//Зададим коллизию на overlap,а в () укажем Quarry only.
	//Физика нам не нужна,но нужен просчет overlap`ов
	//Можно сразу задавать ответ по всем каналам в случае столкновения:
	//Выберем  ECR_Overlap
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

// Called when the game starts or when spawned
void ASnakeElementBase::BeginPlay()
{
	Super::BeginPlay();

	//Нужно получать сообщение,что произошёл overlap.
	//Для этого нужно получать с overlap`a данные события.
	//Биндимся на событиe overlap у mesh component
	//После точки пишем AddDynamic. В () указываем класс,
	//в котором находится ивент,который будем биндить.
	//В качестве второго аргумента указываем адрес, сначала на нащ класс,
	//затем через :: нужно указать функцию (метод) класса, который по сигнатуре 
	//будет совпадать с необходимым методом для Component Begin Overlapp.
	//После создания метода класса в SnakeElementBase можно указать HandleBeginOverlap.
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ASnakeElementBase::HandleBeginOverlap);
	//Теперь,когда Mesh Component будет срабатывать на метод OnComponenntBeginOverlapp,
	//будет вызываться наш метод HandleBeginOverlap
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

//Имплементация метода пока что пустой реализации 
void ASnakeElementBase::Interact(AActor* Interactor)
{
}

void ASnakeElementBase::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{

	//Внутри метода обработки overlap`a проверим валидность указателя на змейку,
		//введя конструкцию:
	if (IsValid(SnakeOwner))
	
		//Вызовем на SnakeOwner метод,который только что создали.В качестве
		//аргумента указываем эелемент,который змейка будет обрабатывать.
		//Через запятую передадим OtherActor
		SnakeOwner->SnakeElementOverlap(this, OtherActor);
		//Теперь змейка знает КАКОЙ блок сколлизился.Знает С ЧЕМ он сколлизился!
}