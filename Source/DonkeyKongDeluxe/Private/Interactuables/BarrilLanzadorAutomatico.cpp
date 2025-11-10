// RUTA: Source/DonkeyKongDeluxe/Private/Interactuables/BarrilLanzadorAutomatico.cpp

#include "Interactuables/BarrilLanzadorAutomatico.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h" 
#include "TimerManager.h" 
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Personaje/DKCPlayerCharacter.h"
#include "Estados/EstadoEnBarril.h" 
#include "Estados/EstadoSalto.h" 

ABarrilLanzadorAutomatico::ABarrilLanzadorAutomatico()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshBarril = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshBarril"));
	RootComponent = MeshBarril;

	ZonaOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("ZonaOverlap"));
	ZonaOverlap->SetupAttachment(RootComponent);
	ZonaOverlap->SetSphereRadius(100.0f);

	FlechaDeLanzamientoVertical = CreateDefaultSubobject<UArrowComponent>(TEXT("FlechaDeLanzamientoVertical"));
	FlechaDeLanzamientoVertical->SetupAttachment(RootComponent);
	FlechaDeLanzamientoVertical->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));

	const TCHAR* RutaMesh = TEXT("/Engine/BasicShapes/Cylinder.Cylinder");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(RutaMesh);
	if (MeshFinder.Succeeded())
	{
		MeshBarril->SetStaticMesh(MeshFinder.Object);
		MeshBarril->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
	}

	FuerzaLanzamiento = 1500.0f;
	RetrasoLanzamiento = 0.5f;
	JugadorAtrapado = nullptr;

	// (NUEVO) Por defecto C++, los barriles son automáticos
	bEsAutomatico = true;
}

void ABarrilLanzadorAutomatico::BeginPlay()
{
	Super::BeginPlay();

	MeshBarril->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	ZonaOverlap->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	ZonaOverlap->SetGenerateOverlapEvents(true);
	ZonaOverlap->OnComponentBeginOverlap.AddDynamic(this, &ABarrilLanzadorAutomatico::OnOverlapBarril);
}

void ABarrilLanzadorAutomatico::OnOverlapBarril(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADKCPlayerCharacter* Jugador = Cast<ADKCPlayerCharacter>(OtherActor);
	if (JugadorAtrapado != nullptr || !Jugador)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Barril C++: ¡Jugador Capturado!"));
	JugadorAtrapado = Jugador;

	MeshBarril->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	Jugador->CambiarEstado(NewObject<UEstadoEnBarril>(Jugador), this);

	// (LA CORRECCIÓN C++)
	// Solo iniciamos el Timer C++ si somos automáticos
	if (bEsAutomatico)
	{
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle_Lanzamiento,
			this,
			&ABarrilLanzadorAutomatico::LanzarJugador,
			RetrasoLanzamiento,
			false);
	}
}

void ABarrilLanzadorAutomatico::LanzarJugador()
{
	if (JugadorAtrapado == nullptr) return;

	// 1. Obtenemos la dirección C++ de la Flecha
	const FVector Direccion = FlechaDeLanzamientoVertical->GetForwardVector();

	// 2. Lanzamos al Jugador C++
	JugadorAtrapado->LaunchCharacter(Direccion * FuerzaLanzamiento, true, true);

	// 3. Salimos del estado C++
	JugadorAtrapado->CambiarEstado(NewObject<UEstadoSalto>(JugadorAtrapado));

	// 4. Volvemos a hacer sólido el barril C++
	MeshBarril->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

	// 5. Liberamos el barril C++
	JugadorAtrapado = nullptr;
}