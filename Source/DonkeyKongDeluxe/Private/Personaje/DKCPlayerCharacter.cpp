// RUTA: Source/DonkeyKongDeluxe/Private/Personaje/DKCPlayerCharacter.cpp

#include "Personaje/DKCPlayerCharacter.h"

// Includes del Motor
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DonkeyKongDeluxeGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"

// Includes del Proyecto
#include "Estados/EstadoEnBarril.h"
#include "Componentes/ComponenteSalud.h"
#include "Componentes/ComponenteInventario.h"
#include "Estados/PlayerBaseState.h"
#include "Estados/EstadoReposo.h"
#include "Estados/EstadoNadar.h"
#include "Estados/EstadoRodarTierra.h" 
#include "Estrategias/PlayerStrategy.h"
#include "Estrategias/DonkeyKongStrategy.h"
#include "Estrategias/DiddyKongStrategy.h" // (NUEVO)
#include "Enemigos/EnemigoBase.h"
#include "Estados/EstadoSalto.h"


ADKCPlayerCharacter::ADKCPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// 1?? AJUSTAR MOVIMIENTO 2.5D
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(1.0f, 0.0f, 0.0f));

	// 2?? CONFIGURACION DEL MESH
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	// Malla Donkey (Mannequin normal)
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MallaDonkeyObj(TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin"));
	if (MallaDonkeyObj.Succeeded())
	{
		MallaDonkey = MallaDonkeyObj.Object;
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimDonkeyClass(TEXT("/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP_C"));
	if (AnimDonkeyClass.Succeeded())
	{
		AnimClassDonkey = AnimDonkeyClass.Class;
	}

	// Malla Diddy (Mannequin Femenino como marcador de posición C++)
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MallaDiddyObj(TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin_Female.SK_Mannequin_Female"));
	if (MallaDiddyObj.Succeeded())
	{
		MallaDiddy = MallaDiddyObj.Object;
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimDiddyClass(TEXT("/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP_C"));
	if (AnimDiddyClass.Succeeded())
	{
		AnimClassDiddy = AnimDiddyClass.Class;
	}

	// Asignamos la malla C++ por defecto (Donkey)
	GetMesh()->SetSkeletalMesh(MallaDonkey);
	GetMesh()->SetAnimInstanceClass(AnimClassDonkey);


	// 3?? CAMARA
	BrazoCamara = CreateDefaultSubobject<USpringArmComponent>(TEXT("BrazoCamara"));
	BrazoCamara->SetupAttachment(RootComponent);
	BrazoCamara->SetRelativeLocation(FVector(0.f, 0.f, 60.f));
	BrazoCamara->TargetArmLength = 500.0f;
	BrazoCamara->bUsePawnControlRotation = true;

	CamaraSeguimiento = CreateDefaultSubobject<UCameraComponent>(TEXT("CamaraSeguimiento"));
	CamaraSeguimiento->SetupAttachment(BrazoCamara, USpringArmComponent::SocketName);
	CamaraSeguimiento->bUsePawnControlRotation = false;

	// 4?? ESTRATEGIA Y COMPONENTES
	EstrategiaActual = nullptr; // Se asigna en BeginPlay
	ComponenteSalud = CreateDefaultSubobject<UComponenteSalud>(TEXT("ComponenteSalud"));
	ComponenteSalud->bPuedeSerInvulnerable = true;
	ComponenteInventario = CreateDefaultSubobject<UComponenteInventario>(TEXT("ComponenteInventario"));

	// 5?? EVENTO DE CHOQUE Y COLISIÓN
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ADKCPlayerCharacter::OnHit);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	// Configuración de colisión C++ (robusta)
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap); // Bananas, Triggers
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block); // Suelo, Llantas Sólidas
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block); // Enemigos
}

void ADKCPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// (Mensaje de depuración)
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("¡SOY EL PERSONAJE C++ CORRECTO (DKCPlayerCharacter)!"));
	}

	// Establecemos la Estrategia C++ inicial
	SetEstrategia(UDonkeyKongStrategy::StaticClass());

	// Estado inicial
	UEstadoReposo* EstadoInicial = NewObject<UEstadoReposo>(this);
	if (EstadoInicial)
	{
		CambiarEstado(EstadoInicial);
	}

	// Salud y muerte
	if (ComponenteSalud)
	{
		ComponenteSalud->EnMuerte.AddDynamic(this, &ADKCPlayerCharacter::AlJugadorMorir);
	}
}


void ADKCPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EstadoActual)
	{
		EstadoActual->TickState(DeltaTime);
	}
}

void ADKCPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &ADKCPlayerCharacter::MoverDerecha);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADKCPlayerCharacter::SaltarPresionado);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &ADKCPlayerCharacter::RodarPresionado);
	PlayerInputComponent->BindAxis("MoveUp", this, &ADKCPlayerCharacter::MoverArriba);

	// (NUEVO) Input C++ para cambiar de personaje
	PlayerInputComponent->BindAction("CambiarPersonaje", IE_Pressed, this, &ADKCPlayerCharacter::CambiarPersonajePresionado);
}

void ADKCPlayerCharacter::MoverDerecha(float Valor)
{
	// (NUEVO) Delegamos el input C++ al estado actual
	if (EstadoActual)
	{
		// Si estamos en UEstadoEnBarril, él rotará el barril.
		// Si estamos en UEstadoReposo, él moverá el personaje.
		EstadoActual->ManejarInputMoverDerecha(Valor);
	}
}

void ADKCPlayerCharacter::MoverArriba(float Valor)
{
	if (EstadoActual)
	{
		EstadoActual->ManejarInputMoverArriba(Valor);
	}
}

void ADKCPlayerCharacter::SaltarPresionado()
{
	if (EstadoActual)
	{
		EstadoActual->ManejarInputSalto();
	}
}

void ADKCPlayerCharacter::RodarPresionado()
{
	if (EstadoActual)
	{
		EstadoActual->ManejarInputRodar();
	}
}

void ADKCPlayerCharacter::CambiarEstado(UPlayerBaseState* NuevoEstado, AActor* ActorReferencia)
{
	if (EstadoActual)
	{
		EstadoActual->OnExit();
	}
	EstadoActual = NuevoEstado;
	if (EstadoActual)
	{
		// Pasamos la referencia C++ al nuevo estado
		EstadoActual->OnEnter(this, ActorReferencia);
	}
}

void ADKCPlayerCharacter::Jump()
{
	Super::Jump();
}

void ADKCPlayerCharacter::EjecutarRodarAccion()
{
	if (EstrategiaActual)
	{
		EstrategiaActual->EjecutarRodar(this);
	}
}

// (FUNCIÓN SetEstrategia MODIFICADA)
void ADKCPlayerCharacter::SetEstrategia(TSubclassOf<UPlayerStrategy> NuevaClaseEstrategia)
{
	if (NuevaClaseEstrategia)
	{
		EstrategiaActual = NewObject<UPlayerStrategy>(this, NuevaClaseEstrategia);
		if (EstrategiaActual)
		{
			EstrategiaActual->SetPersonaje(this);
			EstrategiaActual->AjustarParametrosMovimiento();

			// (CORREGIDO) Pasamos 'this' (este) como referencia
			EstrategiaActual->AplicarMallaEAnimacion(this);

			UE_LOG(LogTemp, Warning, TEXT("Estrategia C++ Cambiada a: %s"), *EstrategiaActual->GetName());
		}
	}
}

// (NUEVA FUNCIÓN C++)
void ADKCPlayerCharacter::CambiarPersonajePresionado()
{
	if (!EstrategiaActual) return;

	// Lógica de cambio C++
	if (EstrategiaActual->IsA<UDonkeyKongStrategy>())
	{
		SetEstrategia(UDiddyKongStrategy::StaticClass());
	}
	else
	{
		SetEstrategia(UDonkeyKongStrategy::StaticClass());
	}
}


void ADKCPlayerCharacter::AlJugadorMorir()
{
	UE_LOG(LogTemp, Warning, TEXT("EL JUGADOR HA SIDO NOTIFICADO DE SU MUERTE."));
	DisableInput(nullptr);

	ADonkeyKongDeluxeGameMode* GameMode = Cast<ADonkeyKongDeluxeGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->JugadorMurio(GetController());
	}
}

void ADKCPlayerCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 1. ¿Chocamos con un Enemigo?
	AEnemigoBase* Enemigo = Cast<AEnemigoBase>(OtherActor);
	if (Enemigo)
	{
		// 1b. (NUEVO) ¿El enemigo es invencible?
		if (Enemigo->GetComponenteSalud() && Enemigo->GetComponenteSalud()->EsInvencible())
		{
			// Si es invencible (Zinger), NOSOTROS recibimos daño.
			ComponenteSalud->RecibirDanio(1.0f);
			return; // No hay pisotón ni roll
		}

		// --- Si NO es invencible ---

		// 2. ¿Es un Pisotón? (Jugador cayendo)
		if (GetVelocity().Z < 0)
		{
			Enemigo->GetComponenteSalud()->RecibirDanio(5.0f);
			LaunchCharacter(FVector(0.f, 0.f, 600.f), false, false); // Rebote normal
		}
		// 3. ¿Estamos Rodando?
		else if (EstadoActual && EstadoActual->EstaAtacando())
		{
			Enemigo->GetComponenteSalud()->RecibirDanio(3.0f);
		}
		// 4. Si no es Pisotón ni Roll... es Choque Lateral (recibimos daño)
		else
		{
			ComponenteSalud->RecibirDanio(1.0f);
		}
	}
}

void ADKCPlayerCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);

	if (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Swimming)
	{
		if (EstadoActual && !EstadoActual->IsA<UEstadoNadar>())
		{
			// (MODIFICADO) Usamos la nueva firma C++
			CambiarEstado(NewObject<UEstadoNadar>(this));
		}
	}
	else if (PrevMovementMode == EMovementMode::MOVE_Swimming)
	{
		if (EstadoActual && !EstadoActual->IsA<UEstadoReposo>())
		{
			// (MODIFICADO) Usamos la nueva firma C++
			CambiarEstado(NewObject<UEstadoReposo>(this));
		}
	}
}