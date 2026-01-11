// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/HBaseWeapon.h"
#include "Components/CapsuleComponent.h"

AHBaseWeapon::AHBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponSocket");
	SetRootComponent(WeaponMesh);
	WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CollisionComponent");
	CapsuleComponent->SetupAttachment(GetRootComponent());
	CapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void AHBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	if (AActor* OwnerActor = GetOwner()) {
		CapsuleComponent->IgnoreActorWhenMoving(OwnerActor, true);
	}
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AHBaseWeapon::OnWeaponCollision);
}
void AHBaseWeapon::OnWeaponCollision(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("Collision with %s"), *OtherActor->GetName());
}
void AHBaseWeapon::Attack() const {

}

void AHBaseWeapon::SetCollsionMode(ECollisionResponse NewMode)
{
	CapsuleComponent->SetCollisionResponseToAllChannels(NewMode);
}
