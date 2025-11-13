// RUTA: Source/DonkeyKongDeluxe/Private/Enemigos/KingKRool.cpp

#include "Enemigos/KingKRool.h"
#include "Componentes/ComponenteSalud.h" 
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h" // Para Timers C++
#include "Kismet/GameplayStatics.h" // Para Spawneo C++
#include "Kismet/KismetMathLibrary.h" // (NUEVO) Para rotación C++
#include "Personaje/DKCPlayerCharacter.h" 

#include "Proyectiles/CoronaProyectil.h"
#include "Proyectiles/BalaDeCanion.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"

AKingKRool::AKingKRool()
{
	// 1. (C++ PURO) Cargar el Mesh (Mannequin)
	const TCHAR* RutaMesh = TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin");
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshFinder(RutaMesh);
	if (MeshFinder.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshFinder.Object);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
		GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	}

	// 2. Salud C++
	ComponenteSalud->SaludMaxima = 20.0f;
	ComponenteSalud->bEsInvencible = true;

	// 3. Variables C++ de Fase 1
	TiempoEntreLanzamientosCorona = 5.0f;

	// 4. Variables C++ de Fase 2
	DuracionFase2 = 15.0f;
	TiempoEntreBalas = 0.5f;

	// 5. (IMPORTANTE) Desactivamos la patrulla C++ por defecto
	VelocidadPatrulla = 0.0f;
}

void AKingKRool::BeginPlay()
{
	// Llamamos al BeginPlay del PADRE (AEnemigoBase)
	Super::BeginPlay();

	// (NUEVO) Nos suscribimos al evento C++ de recibir daño
	ComponenteSalud->EnDanoRecibido.AddDynamic(this, &AKingKRool::AlRecibirDano);

	// Iniciamos la IA C++
	EntrarFase1();
}

void AKingKRool::Tick(float DeltaTime)
{
	// (LA CLAVE DE LA FSM C++)
	// Decidimos qué lógica C++ ejecutar según nuestro estado

	switch (EstadoActualJefe)
	{
	case EEstadoJefe::Fase1_LanzandoCorona:
		LogicaFase1(DeltaTime);
		break;
	case EEstadoJefe::Fase2_LluviaDeBalas:
		LogicaFase2(DeltaTime);
		break;
	}
}

// --- LÓGICA DE FASES C++ ---

void AKingKRool::LogicaFase1(float DeltaTime)
{
	// (TU REQUISITO C++)
	// "tiene que estar viendome todo momento"

	AActor* Jugador = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (Jugador)
	{
		// Calculamos la rotación C++ para mirar al jugador (solo en Yaw/Z)
		FRotator RotacionMirar = UKismetMathLibrary::FindLookAtRotation(
			GetActorLocation(),
			Jugador->GetActorLocation()
		);

		// Aplicamos la rotación C++ (solo Yaw)
		SetActorRotation(FRotator(0.f, RotacionMirar.Yaw, 0.f));
	}

	// El Timer C++ se encarga de llamar a LanzarCorona()
}

void AKingKRool::LogicaFase2(float DeltaTime)
{
	// (TU REQUISITO C++)
	// "cuando termine la lluvia se activa la primera fase y nos vuelve a lanzar su corona"
	// (Nota: "cuando termine la lluvia" = Fase 2)
	// (TU REQUISITO C++)
	// "todos esos 15 segundos de de la lluvia de balas de canion king k krool tiene que estar patrullando"

	// (REUTILIZACIÓN C++)
	// Llamamos al Tick() del padre (AEnemigoBase)
	// que contiene la lógica de patrulla C++ que ya funciona.
	Super::Tick(DeltaTime);
}

// --- FASE 1: VULNERABLE (LANZAR CORONA) ---

void AKingKRool::EntrarFase1()
{
	UE_LOG(LogTemp, Warning, TEXT("K. ROOL (C++): Entrando en Fase 1 (Vulnerable)"));
	EstadoActualJefe = EEstadoJefe::Fase1_LanzandoCorona;

	// ¡Vulnerable!
	ComponenteSalud->bEsInvencible = false;

	// Detenemos la patrulla C++
	VelocidadPatrulla = 0.0f;

	// (Iniciamos el Timer C++ para el primer lanzamiento)
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle_LanzamientoCorona,
		this,
		&AKingKRool::LanzarCorona,
		TiempoEntreLanzamientosCorona,
		false);
}

void AKingKRool::LanzarCorona()
{
	if (EstadoActualJefe != EEstadoJefe::Fase1_LanzandoCorona) return;
	UE_LOG(LogTemp, Warning, TEXT("K. ROOL (C++): ¡Lanzando Corona!"));

	// (LA CORRECCIÓN C++)
	// Ahora el proyectil C++ se mueve solo, solo necesitamos spawnearlo
	// con la rotación C++ correcta (la nuestra).
	FVector UbicacionSpawn = GetActorLocation() + (GetActorForwardVector() * 100.f);
	ACoronaProyectil* Corona = GetWorld()->SpawnActor<ACoronaProyectil>(
		ACoronaProyectil::StaticClass(),
		UbicacionSpawn,
		GetActorRotation() // Usamos nuestra rotación C++
	);

	if (Corona)
	{
		// Le pasamos la referencia C++ del jefe
		Corona->IniciarBumeran(this);
	}

	// Reiniciamos el Timer C++
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle_LanzamientoCorona,
		this,
		&AKingKRool::LanzarCorona,
		TiempoEntreLanzamientosCorona,
		false);
}

// --- FASE 2: INVULNERABLE (PATRULLA Y LLUVIA) ---

// (NUEVO) Esto se llama cuando el jugador golpea a K. Rool en Fase 1
void AKingKRool::AlRecibirDano()
{
	// Solo reaccionamos si estamos en Fase 1
	if (EstadoActualJefe == EEstadoJefe::Fase1_LanzandoCorona)
	{
		UE_LOG(LogTemp, Warning, TEXT("K. ROOL (C++): ¡GOLPEADO! Iniciando Fase 2."));

		// Limpiamos el timer C++ de "volver a lanzar corona"
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_LanzamientoCorona);

		// ¡Iniciamos la Fase 2 C++!
		EntrarFase2();
	}
}

void AKingKRool::EntrarFase2()
{
	UE_LOG(LogTemp, Warning, TEXT("K. ROOL (C++): Entrando en Fase 2 (Invulnerable)"));
	EstadoActualJefe = EEstadoJefe::Fase2_LluviaDeBalas;

	// ¡Invulnerable!
	ComponenteSalud->bEsInvencible = true;

	// (TU REQUISITO C++) Activamos la patrulla C++
	VelocidadPatrulla = 150.0f;

	// Iniciamos el Timer C++ de 15 segundos (Duración de la Fase)
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle_DuracionFase2,
		this,
		&AKingKRool::TerminarFase2,
		DuracionFase2,
		false);

	// Iniciamos el Timer C++ de la lluvia (Repetitivo)
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle_LluviaDeBalas,
		this,
		&AKingKRool::GenerarBalaDeCanion,
		TiempoEntreBalas,
		true); // true = Bucle
}

void AKingKRool::GenerarBalaDeCanion()
{
	AActor* Jugador = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Jugador) return;

	FVector UbicacionJugador = Jugador->GetActorLocation();
	FVector UbicacionSpawn = UbicacionJugador + FVector(0.f, 0.f, 1500.f);
	FRotator RotacionSpawn = FRotator(0.f, 0.f, 0.f);

	GetWorld()->SpawnActor<ABalaDeCanion>(
		ABalaDeCanion::StaticClass(),
		UbicacionSpawn,
		RotacionSpawn
	);
}

void AKingKRool::TerminarFase2()
{
	UE_LOG(LogTemp, Warning, TEXT("K. ROOL (C++): Fase 2 Terminada."));

	// 1. Detenemos la lluvia C++
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_LluviaDeBalas);

	// 2. Volvemos a Fase 1 C++
	EntrarFase1();
}