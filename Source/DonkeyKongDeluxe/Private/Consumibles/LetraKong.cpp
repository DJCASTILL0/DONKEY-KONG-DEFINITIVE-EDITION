
#include "Consumibles/LetraKong.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Personaje/DKCPlayerCharacter.h" 
#include "Componentes/ComponenteInventario.h" 

ALetraKong::ALetraKong()
{
	PrimaryActorTick.bCanEverTick = false;


	ColisionEsfera = CreateDefaultSubobject<USphereComponent>(TEXT("ColisionEsfera"));
	RootComponent = ColisionEsfera;


	ColisionEsfera->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	MeshLetra = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshLetra"));
	MeshLetra->SetupAttachment(RootComponent);
	MeshLetra->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 4. Suscribir el callback de Overlap
	ColisionEsfera->OnComponentBeginOverlap.AddDynamic(this, &ALetraKong::OnOverlap);
}



void ALetraKong::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADKCPlayerCharacter* Jugador = Cast<ADKCPlayerCharacter>(OtherActor);
	if (Jugador)
	{
		UComponenteInventario* Inventario = Jugador->GetComponenteInventario();
		if (Inventario)
		{
	
			Inventario->AnadirLetraKONG();
			Destroy();
		}
	}
}