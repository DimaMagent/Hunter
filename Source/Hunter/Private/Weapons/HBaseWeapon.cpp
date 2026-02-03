// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/HBaseWeapon.h"
#include "Components/CapsuleComponent.h"
#include "HBaseCharacter.h"

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
	const AActor* OwnerActor = GetOwner();
	if (!OwnerActor) {
		UE_LOG(LogTemp, Warning, TEXT("Weapon has no owner!"));
		return;
	}

	if (OtherActor == GetOwner()) { return; }

	AHBaseCharacter* OtherCharacter = Cast<AHBaseCharacter>(OtherActor);
	if (!OtherCharacter) { return; }

	OtherCharacter->ReceiveDamage(CurrentDamage);
}
void AHBaseWeapon::AttackDataHandle(EAttackIntent AttackIntent) {
	if (!ensure(WeaponAttack.Contains(AttackIntent))) { return; }
	LastAttackIntent = AttackIntent;
	CurrentDamage = BaseDamage * WeaponAttack[AttackIntent].GetCurrentComboAttackData().DamageModifier;
	CurrentStaminaCost = BaseStaminaCost * WeaponAttack[AttackIntent].GetCurrentComboAttackData().StaminaCostModifier;
	
}

void AHBaseWeapon::SetCollsionMode(ECollisionResponse NewMode)
{
	CapsuleComponent->SetCollisionResponseToAllChannels(NewMode);
}

void AHBaseWeapon::NextComboDataHandle(bool IsComboInputBuffered) {
	if (!WeaponAttack.Contains(LastAttackIntent)) { return; }

	IsComboInputBuffered ? WeaponAttack[LastAttackIntent].NextCombo() : WeaponAttack[LastAttackIntent].ClearCombo();
	AttackDataHandle(LastAttackIntent);
}

void AHBaseWeapon::Notify_OnComboEnd() {
	WeaponAttack[LastAttackIntent].ClearCombo();
}

UAnimMontage* AHBaseWeapon::GetCurrentComboAnim(EAttackIntent AttackIntent) const
{
	if (!WeaponAttack.Contains(AttackIntent)) { return nullptr; }
	return WeaponAttack[AttackIntent].ComboMontage;
}

bool AHBaseWeapon::GetCurrentStepName(FName& OutStepName) const {
	if (!WeaponAttack.Contains(LastAttackIntent)) { return false; }

	OutStepName = WeaponAttack[LastAttackIntent].GetCurrentComboStep().MontageSectionName;
	return true;
}