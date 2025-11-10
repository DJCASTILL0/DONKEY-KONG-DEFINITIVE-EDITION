// RUTA: Source/DonkeyKongDeluxe/Private/Estados/EstadoNadar.cpp

#include "Estados/EstadoNadar.h"
#include "Personaje/DKCPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void UEstadoNadar::OnEnter(ADKCPlayerCharacter* PersonajeReferencia, AActor* ActorReferencia)
{

	Super::OnEnter(PersonajeReferencia, ActorReferencia);
	UE_LOG(LogTemp, Warning, TEXT("Estado: Entrando en Nado."));

	if (Personaje && Personaje->GetCharacterMovement())
	{
		UCharacterMovementComponent* Movimiento = Personaje->GetCharacterMovement();

		// 1. Guardamos la configuración de C++ original
		GravedadOriginal = Movimiento->GravityScale;
		FriccionOriginal = Movimiento->BrakingFrictionFactor;
		bOrientacionOriginal = Movimiento->bOrientRotationToMovement;

		// 2. Aplicamos la física C++ de nado
		Movimiento->GravityScale = 0.1f;
		Movimiento->BrakingFrictionFactor = 1.0f;
		Movimiento->bOrientRotationToMovement = true;
	}
}

void UEstadoNadar::OnExit()
{
	Super::OnExit();
	UE_LOG(LogTemp, Warning, TEXT("Estado: Saliendo de Nado."));

	if (Personaje && Personaje->GetCharacterMovement())
	{
		UCharacterMovementComponent* Movimiento = Personaje->GetCharacterMovement();

		// 1. Restauramos la configuración C++ original
		Movimiento->GravityScale = GravedadOriginal;
		Movimiento->BrakingFrictionFactor = FriccionOriginal;
		Movimiento->bOrientRotationToMovement = bOrientacionOriginal;
	}
}

void UEstadoNadar::ManejarInputMoverArriba(float Valor)
{
	if (Personaje && Valor != 0.0f)
	{
		Personaje->AddMovementInput(FVector(0.f, 0.f, 1.f), Valor);
	}
}