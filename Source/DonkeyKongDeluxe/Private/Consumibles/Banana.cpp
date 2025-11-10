// RUTA: Source/DonkeyKongDeluxe/Private/Consumibles/Banana.cpp

#include "Consumibles/Banana.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Personaje/DKCPlayerCharacter.h" 
#include "Componentes/ComponenteInventario.h" 
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

ABanana::ABanana()
{
	PrimaryActorTick.bCanEverTick = false;

	// 1. Crear Componentes
	ColisionEsfera = CreateDefaultSubobject<USphereComponent>(TEXT("ColisionEsfera"));
	RootComponent = ColisionEsfera;

	MeshBanana = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshBanana"));
	MeshBanana->SetupAttachment(RootComponent);

	// 2. (C++ PURO) Cargar el Mesh
	// Estas ruta es del motor y SIEMPRE funcionan, por el momento hasta que tengamops las animaciones y modelos
	const TCHAR* RutaMesh = TEXT("/Engine/BasicShapes/Sphere.Sphere");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(RutaMesh);
	if (MeshFinder.Succeeded())
	{
		MeshBanana->SetStaticMesh(MeshFinder.Object);
		MeshBanana->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	}
}

void ABanana::BeginPlay()
{
	Super::BeginPlay();

	// Usamos el perfil "Trigger" (Disparador)
	ColisionEsfera->SetCollisionProfileName(TEXT("Trigger"));

	// "Trigger" significa:
	// - Tipo Objeto = WorldDynamic
	// - Respuesta a Todo = Overlap

	ColisionEsfera->OnComponentBeginOverlap.AddDynamic(this, &ABanana::OnOverlap);
}



void ABanana::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADKCPlayerCharacter* Jugador = Cast<ADKCPlayerCharacter>(OtherActor);
	if (Jugador)
	{
		UComponenteInventario* Inventario = Jugador->GetComponenteInventario();
		if (Inventario)
		{
	
			Inventario->AnadirBanana();
			Destroy();
		}
	}
}