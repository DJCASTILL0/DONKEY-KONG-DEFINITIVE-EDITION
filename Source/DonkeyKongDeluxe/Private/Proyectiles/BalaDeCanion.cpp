// RUTA: Source/DonkeyKongDeluxe/Private/Proyectiles/BalaDeCanion.cpp

#include "Proyectiles/BalaDeCanion.h"
#include "GameFramework/ProjectileMovementComponent.h" // (NUEVO) Incluimos el componente C++ del padre
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

ABalaDeCanion::ABalaDeCanion()
{
	// --- (LA CLAVE C++) ---
	// Anulamos (Override) las variables C++ del padre (AProyectilBase)

	// 1. No tiene velocidad inicial C++ (aparece y cae)
	MovimientoProyectil->InitialSpeed = 0.0f;
	MovimientoProyectil->MaxSpeed = 1000.0f; // Velocidad terminal C++ (para que no caiga demasiado rápido)

	// 2. Usamos la gravedad C++ completa del motor
	MovimientoProyectil->ProjectileGravityScale = 1.0f;

	// 3. No necesita rotar si cae recto
	MovimientoProyectil->bRotationFollowsVelocity = false;

	// 4. (Opcional) Aumentamos el daño C++
	Dano = 2.0f;

	// 5. (C++ PURO) Cargamos un Mesh diferente (opcional)
	// (Usaremos la misma esfera C++ pero la haremos más grande)
	const TCHAR* RutaMesh = TEXT("/Engine/BasicShapes/Sphere.Sphere");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(RutaMesh);
	if (MeshFinder.Succeeded())
	{
		MeshProyectil->SetStaticMesh(MeshFinder.Object);
		MeshProyectil->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f)); // Más grande que AProyectilBase
	}
}