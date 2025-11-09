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
#include "Blueprint/UserWidget.h" // Necesario para CreateWidget

// Includes del Proyecto
#include "Componentes/ComponenteSalud.h"
#include "Componentes/ComponenteInventario.h"
#include "UI/DKCHud.h"
#include "Estados/PlayerBaseState.h"
#include "Estados/EstadoReposo.h"
#include "Estrategias/PlayerStrategy.h"
#include "Estrategias/DonkeyKongStrategy.h"
#include "Enemigos/EnemigoBase.h"

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
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PlayerMeshObject(TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin"));
	if (PlayerMeshObject.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(PlayerMeshObject.Object);
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance> PlayerAnimBPClass(TEXT("/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP_C"));
	if (PlayerAnimBPClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(PlayerAnimBPClass.Class);
	}

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
	EstrategiaActual = CreateDefaultSubobject<UDonkeyKongStrategy>(TEXT("EstrategiaPorDefecto"));
	ComponenteSalud = CreateDefaultSubobject<UComponenteSalud>(TEXT("ComponenteSalud"));
	ComponenteInventario = CreateDefaultSubobject<UComponenteInventario>(TEXT("ComponenteInventario"));

	// 5?? EVENTO DE CHOQUE Y COLISIÓN
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ADKCPlayerCharacter::OnHit);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	// Esta es la configuracion de colision robusta C++:
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap); // Bananas, Triggers
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block); // Suelo
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block); // Enemigos
}

void ADKCPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// (Mensaje de depuración - puedes quitarlo si quieres)
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("¡SOY EL PERSONAJE C++ CORRECTO (DKCPlayerCharacter)!"));
	}

	// Estado inicial
	UEstadoReposo* EstadoInicial = NewObject<UEstadoReposo>(this);
	if (EstadoInicial)
	{
		CambiarEstado(EstadoInicial);
	}

	// Estrategia inicial
	if (EstrategiaActual)
	{
		EstrategiaActual->SetPersonaje(this);
		EstrategiaActual->AjustarParametrosMovimiento();
	}

	// Salud y muerte
	if (ComponenteSalud)
	{
		ComponenteSalud->EnMuerte.AddDynamic(this, &ADKCPlayerCharacter::AlJugadorMorir);
	}

	// (El PlayerController se encarga del HUD, esta sección ya está limpia)
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
}

void ADKCPlayerCharacter::MoverDerecha(float Valor)
{
	if (Controller != nullptr && Valor != 0.0f)
	{
		AddMovementInput(FVector(0.f, -1.f, 0.f), Valor);
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

void ADKCPlayerCharacter::EjecutarRodarAccion()
{
	if (EstrategiaActual)
	{
		EstrategiaActual->EjecutarRodar(this);
	}
}

void ADKCPlayerCharacter::SetEstrategia(TSubclassOf<UPlayerStrategy> NuevaClaseEstrategia)
{
	if (NuevaClaseEstrategia)
	{
		EstrategiaActual = NewObject<UPlayerStrategy>(this, NuevaClaseEstrategia);
		if (EstrategiaActual)
		{
			EstrategiaActual->SetPersonaje(this);
			EstrategiaActual->AjustarParametrosMovimiento();
			UE_LOG(LogTemp, Warning, TEXT("Strategy Changed to: %s"), *EstrategiaActual->GetName());
		}
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
	// Esta función ahora solo se preocupa por los Enemigos
	AEnemigoBase* Enemigo = Cast<AEnemigoBase>(OtherActor);
	if (Enemigo)
	{
		if (GetVelocity().Z < 0) // Pisotón
		{
			Enemigo->GetComponenteSalud()->RecibirDanio(1.0f);
			LaunchCharacter(FVector(0.f, 0.f, 600.f), false, false);
		}
		else // Choque Lateral
		{
			ComponenteSalud->RecibirDanio(1.0f);
		}
	}
}