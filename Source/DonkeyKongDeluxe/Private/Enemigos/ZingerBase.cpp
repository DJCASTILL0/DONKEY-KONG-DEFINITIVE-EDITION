// RUTA: Source/DonkeyKongDeluxe/Private/Enemigos/ZingerBase.cpp

#include "Enemigos/ZingerBase.h"
#include "Componentes/ComponenteSalud.h" 
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h" // (Necesario para colisión C++)

AZingerBase::AZingerBase()
{

	ComponenteSalud->bEsInvencible = true;

	// 2. (C++ PURO) Hacerlo flotar (desactivar gravedad C++)
	GetCharacterMovement()->GravityScale = 0.0f;

	
	const TCHAR* RutaMesh = TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin");
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshFinder(RutaMesh);
	if (MeshFinder.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshFinder.Object);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
		GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	}
}

void AZingerBase::BeginPlay()
{

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);


	Super::AEnemigoBase::BeginPlay();
}

void AZingerBase::Tick(float DeltaTime)
{

	Super::AActor::Tick(DeltaTime);
}