// RUTA: Source/DonkeyKongDeluxe/Private/Enemigos/KritterSaltarin.cpp

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
	// (Puedes cargar una Animacion diferente si quieres)

	// 2. (C++ PURO) Variables de Salto
	TiempoEntreSaltos = 2.0f; // Salta cada 2 segundos
	FuerzaSalto = 600.0f;

	// 3. (IMPORTANTE) Desactivamos la patrulla heredada de AEnemigoBase
	// Al poner la velocidad en 0, no se moverá en el Tick (aunque anularemos Tick)
	VelocidadPatrulla = 0.0f;
}

void AKritterSaltarin::BeginPlay()
{
	// IMPORTANTE: Llamamos al BeginPlay de la clase padre (AEnemigoBase)
	// para que suscriba el ComponenteSalud a la muerte.
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
	// ¡NO LLAMAMOS A Super::Tick(DeltaTime)!
	// Esto es intencional. El Tick() de AEnemigoBase contiene 
	// la logica de AddMovementInput(VelocidadPatrulla).
	// Al anular el Tick y dejarlo vacío (o casi), evitamos que patrulle.

	// Solo llamamos al Tick base de AActor si es necesario (para físicas, etc.)
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