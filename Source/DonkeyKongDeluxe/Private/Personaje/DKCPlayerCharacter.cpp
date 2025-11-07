// RUTA: Source/DonkeyKongDeluxe/Private/Personaje/DKCPlayerCharacter.cpp

#include "Personaje/DKCPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h" // AÑADIR ESTE INCLUDE
#include "Components/SkeletalMeshComponent.h" // AÑADIR ESTE INCLUDE
#include "Animation/AnimInstance.h" // AÑADIR ESTE INCLUDE
// INCLUDES DE PATRONES
#include "Estados/PlayerBaseState.h"
#include "Estados/EstadoReposo.h" 
#include "Estrategias/PlayerStrategy.h" 
#include "Estrategias/DonkeyKongStrategy.h" 


ADKCPlayerCharacter::ADKCPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// 1. AJUSTAR MOVIMIENTO 2.5D
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(1.0f, 0.0f, 0.0f));

	// 2. CONFIGURACION DEL MESH
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PlayerMeshObject(TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin"));
	if (PlayerMeshObject.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(PlayerMeshObject.Object);
	}

	// Opcional: Asignar una clase de animación por defecto (Mannequin's AnimBP)
	static ConstructorHelpers::FClassFinder<UAnimInstance> PlayerAnimBPClass(TEXT("/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP_C"));
	if (PlayerAnimBPClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(PlayerAnimBPClass.Class);
	}
	// 3. CONFIGURACION DE LA CAMARA
	BrazoCamara = CreateDefaultSubobject<USpringArmComponent>(TEXT("BrazoCamara"));
	BrazoCamara->SetupAttachment(RootComponent);
	BrazoCamara->SetRelativeLocation(FVector(0.f, 0.f, 60.f));
	BrazoCamara->TargetArmLength = 500.0f;
	BrazoCamara->bUsePawnControlRotation = true;

	CamaraSeguimiento = CreateDefaultSubobject<UCameraComponent>(TEXT("CamaraSeguimiento"));
	CamaraSeguimiento->SetupAttachment(BrazoCamara, USpringArmComponent::SocketName);
	CamaraSeguimiento->bUsePawnControlRotation = false;

	// 4. INICIALIZACION DE LA ESTRATEGIA POR DEFECTO
	EstrategiaActual = CreateDefaultSubobject<UDonkeyKongStrategy>(TEXT("EstrategiaPorDefecto"));
}


void ADKCPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Configuracion del Estado Inicial
	UEstadoReposo* EstadoInicial = NewObject<UEstadoReposo>(this);
	if (EstadoInicial)
	{
		CambiarEstado(EstadoInicial);
	}

	// Configuramos la estrategia inicial
	if (EstrategiaActual)
	{
		EstrategiaActual->SetPersonaje(this);
		EstrategiaActual->AjustarParametrosMovimiento();
	}
}


void ADKCPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Delegamos la logica de Tick al estado actual
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

	// ELIMINACION: La funcion MoverArriba para lianas/nado ha sido eliminada.
}


// LOGICA DE MOVIMIENTO
void ADKCPlayerCharacter::MoverDerecha(float Valor)
{
	if (Controller != nullptr && Valor != 0.0f)
	{
		AddMovementInput(FVector(0.f, -1.f, 0.f), Valor);
	}
}

// DELEGACION DE INPUTS AL ESTADO
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


// LOGICA DE ESTADO
void ADKCPlayerCharacter::CambiarEstado(UPlayerBaseState* NuevoEstado)
{
	if (EstadoActual)
	{
		EstadoActual->OnExit();
	}

	EstadoActual = NuevoEstado;

	if (EstadoActual)
	{
		EstadoActual->OnEnter(this);
	}
}

void ADKCPlayerCharacter::Jump()
{
	Super::Jump();
}


// LOGICA DE ESTRATEGIA
void ADKCPlayerCharacter::EjecutarRodarAccion()
{
	if (EstrategiaActual)
	{
		// La estrategia de DK/Diddy decide *como* se ejecuta el roll
		EstrategiaActual->EjecutarRodar(this);
	}
}

void ADKCPlayerCharacter::SetEstrategia(TSubclassOf<UPlayerStrategy> NuevaClaseEstrategia)
{
	if (NuevaClaseEstrategia)
	{
		// Recreamos la estrategia
		EstrategiaActual = NewObject<UPlayerStrategy>(this, NuevaClaseEstrategia);
		if (EstrategiaActual)
		{
			EstrategiaActual->SetPersonaje(this);
			EstrategiaActual->AjustarParametrosMovimiento();
			UE_LOG(LogTemp, Warning, TEXT("Strategy Changed to: %s"), *EstrategiaActual->GetName());
		}
	}
}

// ELIMINACION: La lógica de Overlap y lianas ha sido removida.