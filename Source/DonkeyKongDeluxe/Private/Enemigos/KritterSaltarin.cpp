
#include "Enemigos/KritterSaltarin.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h" // Necesario para GetWorld()->GetTimerManager()

// Includes para Carga de Mesh
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"

AKritterSaltarin::AKritterSaltarin()
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

	TiempoEntreSaltos = 2.0f; // Salta cada 2 segundos
	FuerzaSalto = 600.0f;


	VelocidadPatrulla = 0.0f;
}

void AKritterSaltarin::BeginPlay()
{

	Super::BeginPlay();

	// Iniciamos el Timer C++
	// Se repite (true) y llama a IntentarSalto
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle_Salto,
		this,
		&AKritterSaltarin::IntentarSalto,
		TiempoEntreSaltos,
		true); // true = Bucle
}

void AKritterSaltarin::Tick(float DeltaTime)
{

	Super::AActor::Tick(DeltaTime);
}

void AKritterSaltarin::IntentarSalto()
{
	// Solo saltamos si estamos en el suelo
	if (GetCharacterMovement() && !GetCharacterMovement()->IsFalling())
	{
		// Lanzamos el personaje hacia arriba
		LaunchCharacter(FVector(0.f, 0.f, FuerzaSalto), false, false);
	}
}