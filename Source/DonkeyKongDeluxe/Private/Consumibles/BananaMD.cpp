// RUTA: Source/DonkeyKongDeluxe/Private/Consumibles/BananaMD.cpp

#include "Consumibles/BananaMD.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Personaje/DKCPlayerCharacter.h" 
#include "Componentes/ComponenteInventario.h" 
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

ABananaMD::ABananaMD()
{
	PrimaryActorTick.bCanEverTick = false;

	ColisionEsfera = CreateDefaultSubobject<USphereComponent>(TEXT("ColisionEsfera"));
	RootComponent = ColisionEsfera;

	MeshBananaMD = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshBananaMD"));
	MeshBananaMD->SetupAttachment(RootComponent);
	MeshBananaMD->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Usamos el mismo mesh de esfera (marcador de posición)
	const TCHAR* RutaMesh = TEXT("/Engine/BasicShapes/Sphere.Sphere");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(RutaMesh);
	if (MeshFinder.Succeeded())
	{
		MeshBananaMD->SetStaticMesh(MeshFinder.Object);
		// Lo hacemos un poco más grande para diferenciarlo
		MeshBananaMD->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	}
}

void ABananaMD::BeginPlay()
{
	Super::BeginPlay();

	// Usamos el perfil "Trigger" C++
	ColisionEsfera->SetCollisionProfileName(TEXT("Trigger"));
	ColisionEsfera->SetGenerateOverlapEvents(true);
	ColisionEsfera->OnComponentBeginOverlap.AddDynamic(this, &ABananaMD::OnOverlap);
}

void ABananaMD::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADKCPlayerCharacter* Jugador = Cast<ADKCPlayerCharacter>(OtherActor);
	if (Jugador)
	{
		UComponenteInventario* Inventario = Jugador->GetComponenteInventario();
		if (Inventario)
		{
			// (LA LÓGICA C++)
			Inventario->AnadirBananas(6); // Añadimos 6 bananas
			Destroy();
		}
	}
}