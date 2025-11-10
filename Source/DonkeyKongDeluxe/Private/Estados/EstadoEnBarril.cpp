// RUTA: Source/DonkeyKongDeluxe/Private/Estados/EstadoEnBarril.cpp

#include "Estados/EstadoEnBarril.h"
#include "Personaje/DKCPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h" 
#include "GameFramework/Actor.h" 
#include "GameFramework/SpringArmComponent.h" 

// (NUEVO) Incluimos la clase Barril C++ para poder llamarla
#include "Interactuables/BarrilLanzadorAutomatico.h" 

void UEstadoEnBarril::OnEnter(ADKCPlayerCharacter* PersonajeReferencia, AActor* ActorReferencia)
{
	Super::OnEnter(PersonajeReferencia, ActorReferencia);
	UE_LOG(LogTemp, Warning, TEXT("Estado C++: Entrando en Barril."));

	BarrilAsociado = ActorReferencia;

	if (Personaje && BarrilAsociado)
	{
		// 1. Congelamos la cámara
		BrazoCamaraGuardado = Personaje->GetBrazoCamara();
		if (BrazoCamaraGuardado)
		{
			BrazoCamaraGuardado->Deactivate();
		}

		// 2. Ocultamos el Mesh C++
		Personaje->GetMesh()->SetVisibility(false);

		// 3. Detenemos todo movimiento C++
		Personaje->GetCharacterMovement()->StopMovementImmediately();

		// 4. Desactivamos la gravedad C++
		Personaje->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);

		// 5. Desactivamos la colisión de la cápsula C++
		Personaje->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// 6. Centramos al jugador C++ en el barril
		Personaje->SetActorLocation(BarrilAsociado->GetActorLocation());

		// 7. (NUEVO) Variable C++ pura
		VelocidadRotacionBarril = 180.0f; // Grados por segundo
	}
}

void UEstadoEnBarril::OnExit()
{
	Super::OnExit();
	UE_LOG(LogTemp, Warning, TEXT("Estado C++: Saliendo de Barril (Lanzamiento)."));

	// 1. Reactivamos la cámara C++
	if (BrazoCamaraGuardado)
	{
		BrazoCamaraGuardado->Activate();
	}

	if (Personaje)
	{
		// 2. Mostramos el Mesh C++
		Personaje->GetMesh()->SetVisibility(true);

		// 3. Devolvemos la gravedad C++
		Personaje->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);

		// 4. Reactivamos la colisión de la cápsula C++
		Personaje->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

// (NUEVA FUNCIÓN C++)
void UEstadoEnBarril::ManejarInputMoverDerecha(float Valor)
{
	if (BarrilAsociado && Valor != 0.0f)
	{
		// Aplicamos rotación C++ pura al barril
		// (Yaw es el Eje Z, rotación horizontal)
		const float Rotacion = Valor * VelocidadRotacionBarril * GetWorld()->GetDeltaSeconds();
		BarrilAsociado->AddActorLocalRotation(FRotator(0.f, Rotacion, 0.f));
	}
}

// (FUNCIÓN MODIFICADA C++)
void UEstadoEnBarril::ManejarInputMoverArriba(float Valor)
{
	if (BarrilAsociado && Valor != 0.0f)
	{
		// Aplicamos rotación C++ pura al barril
		// (Pitch es el Eje Y, rotación vertical)
		const float Rotacion = Valor * VelocidadRotacionBarril * GetWorld()->GetDeltaSeconds();
		BarrilAsociado->AddActorLocalRotation(FRotator(Rotacion, 0.f, 0.f));
	}
}

// (NUEVA FUNCIÓN C++)
void UEstadoEnBarril::ManejarInputSalto()
{
	if (BarrilAsociado)
	{
		// Intentamos "castear" (convertir) el Actor C++ a nuestra clase Barril
		ABarrilLanzadorAutomatico* Barril = Cast<ABarrilLanzadorAutomatico>(BarrilAsociado);
		if (Barril)
		{
			// Le decimos al barril C++ que nos lance AHORA
			Barril->LanzarJugador();
		}
	}
}