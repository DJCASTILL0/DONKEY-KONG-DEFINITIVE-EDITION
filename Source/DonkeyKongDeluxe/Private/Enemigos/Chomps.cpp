// RUTA: Source/DonkeyKongDeluxe/Private/Enemigos/Chomps.cpp

#include "Enemigos/Chomps.h"
#include "GameFramework/CharacterMovementComponent.h" // Para la gravedad C++
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"

AChomps::AChomps()
{
	// 1. (LA CLAVE C++) Le decimos al padre que SÍ somos acuáticos
	bPatrullaSoloEnAgua = true;

	// 2. Ajustamos la gravedad C++ para que no caiga al suelo si no hay agua
	GetCharacterMovement()->GravityScale = 0.0f;

	// 3. (C++ PURO) Cargar el Mesh del Chomps
	// (Usaremos el Mannequin del motor como marcador de posición)
	// (Reemplaza esta ruta por la de tu mesh de Chomps)
	const TCHAR* RutaMesh = TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin");
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshFinder(RutaMesh);

	if (MeshFinder.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshFinder.Object);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
		GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	}

	// (Los Chomps no usan AnimBP de Mannequin, así que no cargamos animación)
}