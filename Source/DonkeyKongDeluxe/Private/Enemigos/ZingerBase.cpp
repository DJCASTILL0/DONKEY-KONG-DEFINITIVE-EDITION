// RUTA: Source/DonkeyKongDeluxe/Private/Enemigos/ZingerBase.cpp

#include "Enemigos/ZingerBase.h"
#include "Componentes/ComponenteSalud.h" 
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h" // (Necesario para colisión C++)

AZingerBase::AZingerBase()
{
	// 1. (C++ PURO) ¡Hacerlo Invencible!
	// (Heredado de AEnemigoBase, lo configuramos)
	ComponenteSalud->bEsInvencible = true;

	// 2. (C++ PURO) Hacerlo flotar (desactivar gravedad C++)
	GetCharacterMovement()->GravityScale = 0.0f;

	// 3. (C++ PURO) Cargar el Mesh (Usamos Mannequin)
	// (Reemplaza esta ruta C++ por tu mesh de Zinger)
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
	// (LA CORRECCIÓN C++ PURO)
	// Forzamos el modo de movimiento en BeginPlay para anular el Blueprint
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);

	// Llamamos al BeginPlay del ABUELO (AEnemigoBase)
	// para que configure la colisión sólida C++ (BlockAllDynamic)
	// y el delegado de muerte (aunque sea invencible).
	Super::AEnemigoBase::BeginPlay();
}

void AZingerBase::Tick(float DeltaTime)
{
	// (LA CLAVE)
	// Anulamos el Tick() de AEnemigoBase (que patrulla horizontalmente)
	// y solo llamamos al Tick() de AActor (el abuelo).
	Super::AActor::Tick(DeltaTime);
}