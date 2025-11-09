// RUTA: Source/DonkeyKongDeluxe/Private/Enemigos/Kritter.cpp

#include "Enemigos/Kritter.h"

// Includes para Carga de Mesh C++ Puro
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"

AKritter::AKritter()
{
	// 1. (C++ PURO) Cargar el Mesh del Kritter
	// (Usaremos el Mannequin del motor como marcador de posición)
	// (Reemplaza esta ruta por la de tu mesh de Kritter)
	const TCHAR* RutaMesh = TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin");
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshFinder(RutaMesh);

	if (MeshFinder.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshFinder.Object);
		// Ajustamos escala y posicion
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
		GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	}

	// 2. (C++ PURO) Cargar Animacion
	const TCHAR* RutaAnim = TEXT("/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP_C");
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimFinder(RutaAnim);
	if (AnimFinder.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimFinder.Class);
	}

	// 3. Hereda automáticamente la Salud = 1.0f y VelocidadPatrulla = 150.0f
	// de AEnemigoBase. No necesitamos hacer más.
}