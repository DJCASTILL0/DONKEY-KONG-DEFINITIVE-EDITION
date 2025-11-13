// RUTA: Source/DonkeyKongDeluxe/Private/Proyectiles/ProyectilBase.cpp

#include "Proyectiles/ProyectilBase.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

// Includes de Lógica C++
#include "Personaje/DKCPlayerCharacter.h"
#include "Componentes/ComponenteSalud.h"

AProyectilBase::AProyectilBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// 1. Esfera de Colisión C++ (Raíz)
	ColisionEsfera = CreateDefaultSubobject<USphereComponent>(TEXT("ColisionEsfera"));
	RootComponent = ColisionEsfera;
	ColisionEsfera->SetSphereRadius(16.f);
	ColisionEsfera->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	ColisionEsfera->SetNotifyRigidBodyCollision(true);

	// 2. Mesh Visual C++
	MeshProyectil = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshProyectil"));
	MeshProyectil->SetupAttachment(RootComponent);
	MeshProyectil->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 3. Cargar Mesh C++ (Usamos la esfera)
	const TCHAR* RutaMesh = TEXT("/Engine/BasicShapes/Sphere.Sphere");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(RutaMesh);
	if (MeshFinder.Succeeded())
	{
		MeshProyectil->SetStaticMesh(MeshFinder.Object);
		MeshProyectil->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	}

	// 4. Configuración del Movimiento C++
	MovimientoProyectil = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovimientoProyectil"));
	MovimientoProyectil->SetUpdatedComponent(RootComponent);
	MovimientoProyectil->InitialSpeed = 1500.0f;
	MovimientoProyectil->MaxSpeed = 1500.0f;
	MovimientoProyectil->bRotationFollowsVelocity = true;
	MovimientoProyectil->bShouldBounce = false;

	// (LA CORRECCIÓN C++)
	// Ponemos la gravedad C++ a 0.0f por defecto (como en tu código)
	MovimientoProyectil->ProjectileGravityScale = 0.0f;

	// 5. Variable C++ pura
	Dano = 1.0f;

	// 6. Suscripción C++
	ColisionEsfera->OnComponentHit.AddDynamic(this, &AProyectilBase::OnHitProyectil);
}

void AProyectilBase::OnHitProyectil(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 1. ¿Chocamos con el Jugador C++?
	ADKCPlayerCharacter* Jugador = Cast<ADKCPlayerCharacter>(OtherActor);
	if (Jugador)
	{
		UComponenteSalud* SaludJugador = Jugador->GetComponenteSalud();
		if (SaludJugador)
		{
			SaludJugador->RecibirDanio(Dano);
		}
	}
	Destroy();
}