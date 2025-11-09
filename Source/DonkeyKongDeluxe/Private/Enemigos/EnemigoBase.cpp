// RUTA: Source/DonkeyKongDeluxe/Private/Enemigos/EnemigoBase.cpp

#include "Enemigos/EnemigoBase.h"

// Includes del Motor
#include "Components/CapsuleComponent.h" // <-- ¡ESTE ES EL INCLUDE CORREGIDO!
#include "GameFramework/CharacterMovementComponent.h"
#include "Componentes/ComponenteSalud.h"
#include "Personaje/DKCPlayerCharacter.h" 

AEnemigoBase::AEnemigoBase()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(1.0f, 0.0f, 0.0f));

	// 1. Crear el Componente de Salud y configurar su vida maxima
	ComponenteSalud = CreateDefaultSubobject<UComponenteSalud>(TEXT("ComponenteSalud"));
	ComponenteSalud->SaludMaxima = 1.0f;

	// 2. Valores de Patrulla
	VelocidadPatrulla = 150.0f;
	DireccionActual = 1.0f;

	// 3. Adjuntar la funcion de choque (Hit) a la capsula de colision
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AEnemigoBase::OnHit);
}

void AEnemigoBase::BeginPlay()
{
	Super::BeginPlay();

	if (ComponenteSalud)
	{
		ComponenteSalud->EnMuerte.AddDynamic(this, &AEnemigoBase::AlEnemigoMorir);
	}
}

void AEnemigoBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Lógica de Patrulla Básica
	AddMovementInput(FVector(0.f, -1.f, 0.f), DireccionActual * VelocidadPatrulla * DeltaTime);

	// Rotar al enemigo para que mire en la direccion de movimiento (visual)
	if (GetCharacterMovement()->Velocity.SizeSquared() > 0.0f)
	{
		FRotator NewRotation = GetCharacterMovement()->Velocity.Rotation();
		NewRotation.Pitch = 0.0f;
		NewRotation.Roll = 0.0f;
		SetActorRotation(NewRotation);
	}
}

void AEnemigoBase::AlEnemigoMorir()
{
	UE_LOG(LogTemp, Warning, TEXT("Enemigo %s ha muerto. Destruyendo..."), *GetName());
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->DisableMovement();
	Destroy();
}

void AEnemigoBase::InvertirDireccion()
{
	DireccionActual *= -1.0f;
	UE_LOG(LogTemp, Warning, TEXT("Direccion de Enemigo invertida."));
}

void AEnemigoBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ADKCPlayerCharacter* Jugador = Cast<ADKCPlayerCharacter>(OtherActor);
	if (Jugador)
	{
		// Logica de choque con Jugador (se maneja en el jugador)
	}
	else
	{
		// Invertimos la direccion al chocar con una pared
		if (FMath::Abs(Hit.Normal.Z) < 0.1f)
		{
			InvertirDireccion();
		}
	}
}