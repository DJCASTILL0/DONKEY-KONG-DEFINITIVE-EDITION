
#include "Enemigos/KritterSaltarinPatrullador.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h" 

// Includes para Carga de Mesh
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"

AKritterSaltarinPatrullador::AKritterSaltarinPatrullador()
{
	// 1. (C++ PURO) Cargar el Mesh (usaremos el mismo Mannequin)
	const TCHAR* RutaMesh = TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin");
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshFinder(RutaMesh);
	if (MeshFinder.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshFinder.Object);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
		GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	}

	TiempoEntreSaltos = 2.5f;
	FuerzaSalto = 600.0f;


}

void AKritterSaltarinPatrullador::BeginPlay()
{
	// Llamamos al BeginPlay de la clase padre (AEnemigoBase)
	Super::BeginPlay();

	// Iniciamos el Timer C++
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle_Salto,
		this,
		&AKritterSaltarinPatrullador::IntentarSalto,
		TiempoEntreSaltos,
		true); // true = Bucle
}


void AKritterSaltarinPatrullador::IntentarSalto()
{
	// Solo saltamos si estamos en el suelo
	if (GetCharacterMovement() && !GetCharacterMovement()->IsFalling())
	{
		LaunchCharacter(FVector(0.f, 0.f, FuerzaSalto), false, false);
	}
}