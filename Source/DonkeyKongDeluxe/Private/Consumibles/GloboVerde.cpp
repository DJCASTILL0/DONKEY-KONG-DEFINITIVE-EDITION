// RUTA: Source/DonkeyKongDeluxe/Private/Consumibles/GloboVerde.cpp

#include "Consumibles/GloboVerde.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Personaje/DKCPlayerCharacter.h" 
#include "Componentes/ComponenteInventario.h" 
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

AGloboVerde::AGloboVerde()
{
	PrimaryActorTick.bCanEverTick = false;
	ColisionEsfera = CreateDefaultSubobject<USphereComponent>(TEXT("ColisionEsfera"));
	RootComponent = ColisionEsfera;
	MeshGlobo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshGlobo"));
	MeshGlobo->SetupAttachment(RootComponent);
	MeshGlobo->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Usamos la esfera (marcador de posición)
	const TCHAR* RutaMesh = TEXT("/Engine/BasicShapes/Sphere.Sphere");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(RutaMesh);
	if (MeshFinder.Succeeded())
	{
		MeshGlobo->SetStaticMesh(MeshFinder.Object);
		MeshGlobo->SetRelativeScale3D(FVector(0.75f, 0.75f, 0.75f));
	}
}

void AGloboVerde::BeginPlay()
{
	Super::BeginPlay();
	ColisionEsfera->SetCollisionProfileName(TEXT("Trigger"));
	ColisionEsfera->SetGenerateOverlapEvents(true);
	ColisionEsfera->OnComponentBeginOverlap.AddDynamic(this, &AGloboVerde::OnOverlap);
}

void AGloboVerde::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADKCPlayerCharacter* Jugador = Cast<ADKCPlayerCharacter>(OtherActor);
	if (Jugador)
	{
		UComponenteInventario* Inventario = Jugador->GetComponenteInventario();
		if (Inventario)
		{
			// (LA LÓGICA C++)
			Inventario->AnadirVidas(3); // Añadimos 3 vidas
			Destroy();
		}
	}
}