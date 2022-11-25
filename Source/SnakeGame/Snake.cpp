// Fill out your copyright notice in the Description page of Project Settings.


#include "Snake.h"
// Подключение файла интерфейсов,чтобы его использовать
#include "Interactable.h"
// Подключение header нашего класса SnakeElement
#include "SnakeElementBase.h"	

// Sets default values
ASnake::ASnake()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// От головы змейки откладываются элементы,размером ElementSize
	ElementSize = 60.f;  

	// Скорость по умолчанию 10
	MovementSpeed = 0.5f; 
   
	// Направление движения по умолчанию
	LastMoveDirection = EMovementDirection::DOWN; 
}

// Called when the game starts or when spawned
void ASnake::BeginPlay()
{
	Super::BeginPlay();

	// Чтобы поменять частоту Tick. Т.к. это будет скорость,то мы можем исп. имеющуюся переменную MovementSpeed.
	// Но если изначально она означала см/сек,то теперь она будет абстрактно обозначать просто секунды. 
	// Раз в сколько секунд змейка будет перемещаться ровно на ElementSize;
	SetActorTickInterval(MovementSpeed);	
	// Эта строчка использовалась для проверки спавна ЗМЕЙКИ.Когда мы создаем чисто элементы - её нужно убрать!
	// GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, GetActorTransform()); //Создаем элементы змейки на BeginPlay.Передедим пока что GetActorTransform
	// При начале игры змейка будет состоять из 5 элементов
	AddSnakeElement(5); 

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &ASnake::HighSpeed, 90.f, false); // 60

	FTimerHandle Handle2;
	GetWorld()->GetTimerManager().SetTimer(Handle2, this, &ASnake::HighSpeed2, 200.f, false); // 120

	FTimerHandle Handle3;
	GetWorld()->GetTimerManager().SetTimer(Handle3, this, &ASnake::HighSpeed3, 310.f, false); // 240
}

// Called every frame
void ASnake::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Движение каждый кадр. DeltaTime нужна для того,чтобы избавиться от зависимости от кадров.
	// DeltaTime больше не нужен
	Move(); 
}

// Аргумент,который мы добавили в Snake.h (значение по умолчанию прописывать не надо!)
void ASnake::AddSnakeElement(int ElementsNum)	
{
	// Цикл от 0 до кол-ва элементов
	for (int i = 0; i < ElementsNum; ++i)		
	{
		// 1 вариант:Сперва создаётся элемент,сохраняется в переменную
		// auto NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, GetActorTransform());    //Transform каждый раз берется один и тот же
		// //Узнаем кол-во элементов:
		// SnakeElements.Num(); - если на данный момент элементов в массиве нет
		// SnakeElements.Num()*ElementSize; - Если Num больше 0,то мы умножим его на ElementSize
		// В таком случае FTransform будет:
		// auto NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass,FTransform (GetActorLocation()-FVector(SnakeElements*ElementSize,0,0));
		// Чтобы сократить эту запись, сформируем Location: FVector NewLocation(...)

		// Задали расположение Location
		FVector NewLocation(SnakeElements.Num()*ElementSize, 0, 0); 

		// FTransform NewTransform = FTransform(GetActorLocation()-FVector(SnakeElements.Num() * ElementSize, 0, 0));
		// А в скобки вместо этого всего вставим короткое имя: 
		// auto NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform())
		// В итоге получится:

		// Используем NewLocation чтобы проициализировать Transform
		FTransform NewTransform(NewLocation); 
		// Заспавнили новый элемент,сохранили его в переменной
		ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform); 
		NewSnakeElem->SetActorHiddenInGame(true);
		
		// NewSnakeElem->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform); //Присоединяем Actor`a. В качестве правил присоедиенния указываем KeepRelative
		// Позднее мы избавились этой строки,т.к. при перемещении AttachToActor будет ломать. Создадим цикл по блокам ниже.

		// При добавлении нового блока, мы будем устанавливать вручную значение SnakeOwner.
		// SnakeOwner устанавливаем в this.
		NewSnakeElem->SnakeOwner = this;

		// Запись элемента в массив
		int32 ElemIndex = SnakeElements.Add(NewSnakeElem); 
		// Во время добавления элемента можно здесь указать int32 ElemIndex = ...
		// Проверка если ElemIndex = 0,то это голова змейки
		if (ElemIndex == 0)
		{
			// Вызов метода,который точно скажет элементу что он - первый.
			NewSnakeElem->SetFirstElementType(); 

			// Код добавления элемента в змейку. Здесь можно получать из NewSnakeElem
			// MeshComponent а затем биндить на него определенное событие. 
			// Нужно подключить файл StaticMeshComponent, а заодно компонент
			// BeginOverlap.
			// NewSnakeElem->MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ASnakeElementBase::HandleBeginOverlap);
		}
	}
}

// float DeltaTime больше не нужен
void ASnake::Move() 
{
	for (int i = SnakeElements.Num() - 1; i > 0; i--)
	{
		SnakeElements[0]->SetActorHiddenInGame(false);
		SnakeElements[i]->SetActorHiddenInGame(false);
	}

	// Вектор движения
	FVector MovementVector(ForceInitToZero);
	// float DeltaTime больше не нужен
	float  MovmentSpeed = ElementSize; 

	// 1 Вариант реализации:
 
	// if (LastMoveDirection == EMovementDirection::UP) //Если последнее направление движения = ВВЕРХ,то
	// {
	//	 MovementVector = FVector(MovementSpeedDelta,0,0); // FVector() с положительным X
	// }
	//
	
	// 2 вариант реализации:
	switch (LastMoveDirection)
	{
	case EMovementDirection::UP:			//Если движение наверх,то
		MovementVector.X += MovmentSpeed; //прописываем эту конструкцию
		break;
	case EMovementDirection::DOWN:				//Если движение вниз,то
		MovementVector.X -= MovmentSpeed;  //+ изменяем на - (это противоположное движение)
		break;
	case EMovementDirection::LEFT:           //Если движение влево,то
		MovementVector.Y += MovmentSpeed; //направление меняем по оси Y
		break;
	case EMovementDirection::RIGHT:           //Соответсвтенно если направо,
		MovementVector.Y -= MovmentSpeed; //то меняем + на -
		break;
	}

	// AddActorWorldOffset(MovementVector); //Перемещаем наш Actor
	// Нужно удалить эту строку для реализации перемещения змейки по блокам 

	// Добавим вызов метода Toggle перед тем, как двигать все блоки
	// Сначала получим 0 элемент и вызовем на нём ToggleCollision
	SnakeElements[0]->ToggleCollision();

	// Для того,чтобы ближе к голове переместить все наши блоки на 1,
	// Создадим цикл for ,чтобы задавать какие именно индексы мы будем брать.
	for (int i = SnakeElements.Num() - 1; i > 0; i--)
	{
		// В теле цикла нужно получить текущий элемент:
		auto CurrentElement = SnakeElements[i];
		// Предыдущий элемент:
		auto PrevElement = SnakeElements[i - 1];
		// После этого сместим наш элемент в направлении предыдущего.
		// Для этого у пердыдущего элемента получаем точку в пространстве,которая будет равна его Location:
		FVector PrevLocation = PrevElement->GetActorLocation();
		// А текущий элемент будем смещать на место предыдущего:
		CurrentElement->SetActorLocation(PrevLocation);
	}
	SnakeElements[0]->AddActorWorldOffset(MovementVector);
	// Проведем проверку. В начале мы выключили, далее переместили
	// все блоки, переместили голову, включили коллизию обратно. 
	SnakeElements[0]->ToggleCollision();
}

// Создание реализации метода внутри змейки
// Т.к. мы ранее поправили сигнатуру в h. файле, в срр надо добавить AActor* Other
void ASnake::SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other) 
{
	// Проверяем указатель на валидность.Если указатель 
	// валиден,то мы можем найти конкретный блок.
	if (IsValid(OverlappedElement))
	{
		
		// Создадим переменную, в которую 
		// будем записывать наш индекс.
		// 
		// Возьмем весь массив SnakeElements и при помощи
		// метода Find найдем индекс требуемого элемента.
		// 
		// Запоминаем в булевую переменную bISFirst
		// значение о том,что наш блок является головой.
		// 
		// В аргументы к булевой функции зададим элемент
		// overlapped и индекс.
		int32 ElemIndex;
		SnakeElements.Find(OverlappedElement, ElemIndex);
		bool bIsFirst = ElemIndex == 0;
		// Если индекс = 0, то элемент у нас первый (голова)
		//
		// Теперь можно осуществить проверку следующего вида:
		// Создать указатель на наш интерфейс (а интерфейс -
		// это класс) и скастовать при помощи Unreal cast 
		// наш актор к этому интерфейссу.В аргументе 
		// передадим нашего Actor`a.
		IInteractable* InteractableInterface = Cast<IInteractable>(Other);
		

		// Чтобы узнать успешно ли скастовался Actor, проверяем что
		// указатель получился не нулевой:
		if (InteractableInterface)
		{
			// Мы гарантируем, что в функцию попадают все валидные
			// аргументы и что этот актор (с которым змейка сколлизилась)
			// является тем классом,который имплементирует заданный интерфейс.
			// Вызываем метод Interact и передаем объект,который
			// интерактирует с Actor`ом,реализовывающим данный 
			// интерфейс.
			InteractableInterface->Interact(this, bIsFirst);
			// Помимо самой змейки будем сообщать был ли наш элемент первый,
			// тоесть - головой (bIsFirst)
			// 
			// Дополнительно в метод будем передавать значение о том,происходит
			// ли интеракт с головой змейки.
		}
	}	
}

void ASnake::HighSpeed()
{
	SetActorTickInterval(MovementSpeed = 0.35);
}

void ASnake::HighSpeed2()
{
	SetActorTickInterval(MovementSpeed = 0.25);
}

void ASnake::HighSpeed3()
{
	SetActorTickInterval(MovementSpeed = 0.1);
}

void ASnake::DestroySnake()
{
	
}




