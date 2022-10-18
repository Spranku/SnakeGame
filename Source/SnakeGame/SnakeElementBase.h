// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"		//�����.������ ���������� 
#include "SnakeElementBase.generated.h"

class UStaticMeshComponent;
class ASnake; // forvard-declaration,�.�. ����� ������ �� �������� � ������������� Asnake. � ��� ����� ��������� h.

UCLASS()
class SNAKEGAME_API ASnakeElementBase : public AActor, public IInteractable		//��.������������
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeElementBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) 
	UStaticMeshComponent* MeshComponent; //���������� ������ ��� ����������,����� ���������� ������ ���� ������������� � BP

	//�� ��� ����� � Snake Element �������� ������� � ������ ���.
	//�� ����� ������� ��������� �� ������, ������� ���������� ������ �������.
	//����������� ��������� �� ������, ������� ������� ������ ������.
	UPROPERTY()
		ASnake* SnakeOwner; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)			   // �������� �������� ����������� �++ �����-����� � BP-����������
    void SetFirstElementType();				   //Event,������� ����� ������ �������� ��� �� - ������.
	void SetFirstElementType_Implementation(); //��� ���� ���������� ������.���������� ����� ������ � �++ �� ������� ������
	//��� ���������� �� �������� ������� �� �������,���� �� �������� ��� �����.

	//��������� ������������� ������ Interact
	virtual void Interact(AActor* Interactor , bool bIsHead) override; // ��������� bIsHead � ����

	//������� ����� HandleBeginOverlap
	//��������-��������� ��������� - ����� overlap component
	//� ��� �� Actor,������� �`overlap`���� 
	//����� ��������-��������� ������� Actor`a,������� ������ ������� overlap`�
	//����� ����� ����������� ���������� ����...
	UFUNCTION()
		void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComponent,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
		//������� ����� ����� �������� ������ ���� ����� ��� � ���-�� ����������.
		//����� ������, ����� ������ ������ ����� ������ ����� Food. � ��� ��� ����
		//����� SetFirstElementType, � ��� ����� ����� ��������, ��� ������ �����
		//���� �������, � �� ������� (��� ����� ���������� ��������� �����),�
		//������� ����� ������ ����� ������������� ��������, ��� ������� "������"
		//�������� ������.

	UFUNCTION()
		//��������� �����,������� ����� �������� �� ������.
		void ToggleCollision();

};
