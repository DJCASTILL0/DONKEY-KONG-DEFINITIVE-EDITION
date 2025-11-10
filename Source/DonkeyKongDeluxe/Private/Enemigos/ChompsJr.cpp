// RUTA: Source/DonkeyKongDeluxe/Private/Enemigos/AChompsJr.cpp

#include "Enemigos/ChompsJr.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"

AChompsJr::AChompsJr()
{
	// 1. (LA CLAVE C++) Le decimos al padre que SÍ somos acuáticos
	bPatrullaSoloEnAgua = true;

	// 2. Ajustamos la gravedad C++
	GetCharacterMovement()->GravityScale = 0.0f;

	// 3. (LA CORRECCIÓN) Aumentamos la velocidad de patrulla C++
	// AEnemigoBase (el padre) tiene 150.0f. Lo hacemos más rápido.
	VelocidadPatrulla = 300.0f;

	// 4. (C++ PURO) Cargar el Mesh (Mannequin)
	const TCHAR* RutaMesh = TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin");
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshFinder(RutaMesh);

	if (MeshFinder.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshFinder.Object);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
		GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

		// Lo hacemos más pequeño (C++ Puro)
		GetMesh()->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	}
}