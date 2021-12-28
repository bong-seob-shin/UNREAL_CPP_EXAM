// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MyCharacter.h"

UMyAnimInstance::UMyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("AnimMontage'/Game/Animations/Greystone_Skeleton_Montage.Greystone_Skeleton_Montage'"));
	if (AM.Succeeded())
	{
		AttackMontage = AM.Object;
	}
}


void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto pawn = TryGetPawnOwner(); //Apwan return

	if (IsValid(pawn))
	{
		Speed = pawn->GetVelocity().Size();
	}

	auto Character = Cast<AMyCharacter>(pawn);

	if (Character)
	{
		isFalling = Character->GetMovementComponent()->IsFalling();

		Vertical = Character->UpDownValue;
		Horizontal = Character->LeftRightValue;
	}
}

void UMyAnimInstance::PlayAttackMontage()
{
	
	Montage_Play(AttackMontage, 1.f);
	
}

void UMyAnimInstance::JumpToSection(int32 SectionIndex)
{
	FName Name = GetAttackMontageName(SectionIndex);//현재 섹션에 대한 이름추출
	Montage_JumpToSection(Name, AttackMontage);
}

FName UMyAnimInstance::GetAttackMontageName(int32 SectionIndex)
{
	return FName(*FString::Printf(TEXT("Attack%d"), SectionIndex));
}

void UMyAnimInstance::AnimNotify_AttackHit()
{
	//when character attack, call this func
}
