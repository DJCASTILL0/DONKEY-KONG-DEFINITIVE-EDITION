// RUTA: Source/DonkeyKongDeluxe/Private/Enemigos/Octoprus.cpp

#include "Enemigos/Octoprus.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h" // Para GetPlayerCharacter
#include "TimerManager.h" // Para el Timer C++
#include "Personaje/DKCPlayerCharacter.h" // Para el Cast del Overlap

// Includes para Carga de Mesh C++ Puro
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Componentes/ComponenteSalud.h"
AOctoprus::AOctoprus()
{

	const TCHAR* RutaMesh = TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin");
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshFinder(RutaMesh);
	if (MeshFinder.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshFinder.Object);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
		GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	}


	ZonaDeteccion = CreateDefaultSubobject<USphereComponent>(TEXT("ZonaDeteccion"));
	ZonaDeteccion->SetupAttachment(RootComponent);
	ZonaDeteccion->SetSphereRadius(1000.0f); // Radio de alerta
	ZonaDeteccion->SetCollisionProfileName(TEXT("OverlapOnlyPawn")); // Solo detecta al Jugador


	EstadoActual = EOctoprusEstado::Patrullando;
	VelocidadPersecucion = 400.0f; // Más rápido que 150.0f (Patrulla)
	DuracionPersecucion = 15.0f; // 15 segundos

	bPatrullaSoloEnAgua = true; // Octoprus es acuático
	GetCharacterMovement()->GravityScale = 0.0f; // No cae
	ComponenteSalud->bEsInvencible = true;
}

void AOctoprus::BeginPlay()
{
	Super::BeginPlay(); // Llama a AEnemigoBase::BeginPlay()


	ZonaDeteccion->OnComponentBeginOverlap.AddDynamic(this, &AOctoprus::OnOverlapDeteccion);
}

void AOctoprus::Tick(float DeltaTime)
{


	switch (EstadoActual)
	{
	case EOctoprusEstado::Patrullando:
		LogicaPatrulla(DeltaTime);
		break;
	case EOctoprusEstado::Persiguiendo:
		LogicaPersecucion(DeltaTime);
		break;
	case EOctoprusEstado::Detenido:
		LogicaDetenido(DeltaTime);
		break;
	}
}



void AOctoprus::LogicaPatrulla(float DeltaTime)
{

	Super::Tick(DeltaTime);
}

void AOctoprus::LogicaPersecucion(float DeltaTime)
{

	AActor* Jugador = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Jugador) return;

	// 2. Calcular Dirección (solo Y/Z, porque somos 2.5D)
	FVector DireccionAlJugador = Jugador->GetActorLocation() - GetActorLocation();
	DireccionAlJugador.X = 0.0f; // Ignoramos la profundidad
	DireccionAlJugador.Normalize();

	// 3. Moverse hacia el jugador C++
	AddMovementInput(DireccionAlJugador, VelocidadPersecucion * DeltaTime);

	// 4. Rotar C++
	UCharacterMovementComponent* Movimiento = GetCharacterMovement();
	if (Movimiento && Movimiento->Velocity.SizeSquared() > 0.0f)
	{
		FRotator NewRotation = Movimiento->Velocity.Rotation();
		NewRotation.Pitch = 0.0f;
		NewRotation.Roll = 0.0f;
		SetActorRotation(NewRotation);
	}
}

void AOctoprus::LogicaDetenido(float DeltaTime)
{
	// Detenemos el movimiento C++
	GetCharacterMovement()->StopMovementImmediately();
}



void AOctoprus::OnOverlapDeteccion(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ¿Es el jugador C++?
	ADKCPlayerCharacter* Jugador = Cast<ADKCPlayerCharacter>(OtherActor);

	// ¿Estamos en estado de patrulla?
	if (Jugador && EstadoActual == EOctoprusEstado::Patrullando)
	{
		// ¡Iniciamos la persecución!
		EntrarEstadoPersecucion();
	}
}

void AOctoprus::EntrarEstadoPersecucion()
{
	UE_LOG(LogTemp, Warning, TEXT("Octoprus: ¡Jugador detectado! INICIANDO PERSECUCIÓN."));
	EstadoActual = EOctoprusEstado::Persiguiendo;

	// Iniciamos el Timer C++ de 15 segundos
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle_Persecucion,
		this,
		&AOctoprus::TerminarPersecucion,
		DuracionPersecucion,
		false); // false = No se repite
}

void AOctoprus::TerminarPersecucion()
{
	UE_LOG(LogTemp, Warning, TEXT("Octoprus: Persecución terminada. DETENIDO."));
	EntrarEstadoDetenido();
}

void AOctoprus::EntrarEstadoDetenido()
{
	EstadoActual = EOctoprusEstado::Detenido;

}