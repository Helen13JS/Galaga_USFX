// Copyright Epic Games, Inc. All Rights Reserved.

#include "Galaga_USFXPawn.h"
#include "Galaga_USFXProjectile.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

#include "InventoryComponent.h"
#include "Capsulas.h"
#include "CapsulasEnergia.h"
#include "CapsulasArmas.h"
#include "Containers/Queue.h"

const FName AGalaga_USFXPawn::MoveForwardBinding("MoveForward");
const FName AGalaga_USFXPawn::MoveRightBinding("MoveRight");
const FName AGalaga_USFXPawn::FireForwardBinding("FireForward");
const FName AGalaga_USFXPawn::FireRightBinding("FireRight");

AGalaga_USFXPawn::AGalaga_USFXPawn()
{	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);
	
	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	// Movement
	MoveSpeed = 1000.0f;
	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = true;


	NumProyectilesDisparados = 0;
	MaxProyectilesDisparados = 5; //Establece el n�mero m�ximo de proyectiles disparados
	MyInventory =
		CreateDefaultSubobject<UInventoryComponent>("MyInventory");
	NumItems = 0;
}

void AGalaga_USFXPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAxis(FireForwardBinding);
	PlayerInputComponent->BindAxis(FireRightBinding);


	PlayerInputComponent->BindAction("DropItem",
		EInputEvent::IE_Pressed, this,
		&AGalaga_USFXPawn::DropItem);

	PlayerInputComponent->BindAction("ReloadAmmo", IE_Pressed, this, &AGalaga_USFXPawn::ReloadAmmo);
	PlayerInputComponent->BindAction("ReloadEnergy", IE_Pressed, this, &AGalaga_USFXPawn::ReloadEnergy);
}

void AGalaga_USFXPawn::Tick(float DeltaSeconds)
{
	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate  movement
	const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

	// If non-zero size, move this actor
	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
		
		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}
	
	// Create fire direction vector
	const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
	const float FireRightValue = GetInputAxisValue(FireRightBinding);
	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f);

	// Try and fire a shot
	FireShot(FireDirection);
}

void AGalaga_USFXPawn::FireShot(FVector FireDirection)
{
	// If it's ok to fire again
	if (bCanFire == true && NumProyectilesDisparados < MaxProyectilesDisparados)
	{
		// Incrementa el contador de proyectiles disparados

		// If we are pressing fire stick in a direction
		if (FireDirection.SizeSquared() > 0.0f)
		{
			const FRotator FireRotation = FireDirection.Rotation();
			// Spawn projectile at an offset from this pawn
			const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				// spawn the projectile
				//World->SpawnActor<AGalaga_USFXProjectile>(SpawnLocation, FireRotation);
			

				// spawn the projectile
				// Spawn the three projectiles
				//float BulletSpacing = 100.0f; // Ajusta el valor seg�n sea necesario

				for (int i = 0; i < 3; ++i)
				{
					//World->SpawnActor<AGalaga_USFX_L01Projectile>(SpawnLocation, FireRotation);
					FRotator ModifiedRotation = FireRotation;
					// Modify rotation for each projectile
					ModifiedRotation.Yaw += (i - 1) * 20.0f; // Offset rotation by 10 degrees

					// Calcular la ubicaci�n de spawn de la bala actual
					//FVector BulletSpawnLocation = SpawnLocation + FireRotation.RotateVector(FVector(0.f, i * BulletSpacing, 0.f));

					// Spawn the projectile
					//World->SpawnActor<AGalaga_USFX_L01Projectile>(BulletSpawnLocation, FireRotation);


					const FVector ModifiedSpawnLocation = GetActorLocation() + ModifiedRotation.RotateVector(GunOffset);

					//// Spawn the projectile
					World->SpawnActor<AGalaga_USFXProjectile>(ModifiedSpawnLocation, ModifiedRotation);
				}
			
			
			}
			// Restablece el contador cuando se alcance el l�mite m�ximo
			if (NumProyectilesDisparados >= MaxProyectilesDisparados)
			{
				bCanFire = false;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AGalaga_USFXPawn::ShotTimerExpired, FireRate);
			}


			bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AGalaga_USFXPawn::ShotTimerExpired, FireRate);

			// try and play the sound if specified
			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}

			bCanFire = false;
		}
	}
}

void AGalaga_USFXPawn::ShotTimerExpired()
{

	// Restablece el contador y permite disparar de nuevo
	++NumProyectilesDisparados; // Incrementa el contador de proyectiles disparados en 1

	if (NumProyectilesDisparados >= MaxProyectilesDisparados)
	{
		//NumProyectilesDisparados = 0;
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "No tienes municiones");
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Presiona Q para recargar");


		}
	}

	bCanFire = true;
}


void AGalaga_USFXPawn::DropItem()
{
	if (MyInventory->CurrentInventory.IsEmpty())//MyInventory->CurrentInventory.Num() == 0
	{
		if (GEngine)
		{
			FString Message = FString::Printf(TEXT("Tienes %d objetos en tu inventario"), NumItems);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, Message);
		}
		return;
	}
	ACapsulas* Item = nullptr;
	MyInventory->CurrentInventory.Dequeue(Item);//MyInventory->CurrentInventory.Last();
	//MyInventory->CurrentInventory.Last();
//MyInventory->RemoveFromInventory(Item);
	NumItems -= 1;
	// Obt�n la ubicaci�n actual de la nave
	FVector ShipLocation = GetActorLocation();
	FVector ItemOrigin;
	FVector ItemBounds;
	Item->GetActorBounds(false, ItemOrigin, ItemBounds);

	// Ajusta la posici�n para centrar el objeto con respecto a la nave
	float DropDistance = 200.0f; // Distancia adicional para dejar caer el objeto
	FVector DropOffset = FVector(0.0f, 0.0f, ItemBounds.Z * 0.5f); // Ajusta la posici�n verticalmente para centrar el objeto
	FTransform PutDownLocation = FTransform(GetActorRotation(), ShipLocation + DropOffset +
		(RootComponent->GetForwardVector() * DropDistance)); // Combina la ubicaci�n de la nave con el desplazamiento vertical y horizontal

	Item->PutDown(PutDownLocation);

	//Verifica el inventario despu�s de soltar un objeto
	CheckInventory();
}

void AGalaga_USFXPawn::NotifyHit(class UPrimitiveComponent*
	MyComp, AActor* Other, class UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal,
	FVector NormalImpulse, const FHitResult& Hit)
{
	ACapsulas* InventoryItem =
		Cast<ACapsulas>(Other);
	if (InventoryItem != nullptr)
	{
		TakeItem(InventoryItem);
	}
}
void AGalaga_USFXPawn::TakeItem(ACapsulas*
	InventoryItem)
{
	InventoryItem->PickUp();
	MyInventory->AddToInventory(InventoryItem);
	// Declarar un TimerHandle

	NumItems += 1;

	// Configurar el temporizador con SetTimer
	float DelayInSeconds = 10.0f; // Tiempo de retraso en segundos
	bool bLooping = false; // Si el temporizador debe repetirse autom�ticamente o no
	ACapsulasArmas* AmmoItem = Cast<ACapsulasArmas>(InventoryItem);
	if (AmmoItem)
	{
		FTimerHandle MyTimerHandle1;
		GetWorldTimerManager().SetTimer(MyTimerHandle1, this, &AGalaga_USFXPawn::ReloadAmmo, DelayInSeconds, bLooping);
	}

	ACapsulasEnergia* EnergyItem = Cast<ACapsulasEnergia>(InventoryItem);
	if (EnergyItem)
	{
		FTimerHandle MyTimerHandle2;
		GetWorldTimerManager().SetTimer(MyTimerHandle2, this, &AGalaga_USFXPawn::ReloadEnergy, DelayInSeconds, bLooping);

	}

	//GetWorldTimerManager().SetTimer(MyTimerHandle1, this, &AGalaga_USFX_L01Pawn::ReloadAmmo, DelayInSeconds, bLooping);

	//Verifica el inventario despu�s de recoger un objeto
	CheckInventory();
}

void AGalaga_USFXPawn::ReloadAmmo()
{
	// Bandera para verificar si se encontr� un objeto de munici�n
	bool bFoundAmmo = false;

	// Itera sobre los objetos en el inventario para encontrar uno de munici�n
	ACapsulas* InventoryItem = nullptr;

	//for (AInventoryActor* InventoryItem : MyInventory->CurrentInventory)
	while (MyInventory->CurrentInventory.Dequeue(InventoryItem))
	{
		// Intenta hacer un cast a AInventoryActorMunicion
		ACapsulasArmas* AmmoItem = Cast<ACapsulasArmas>(InventoryItem);
		if (AmmoItem)
		{
			// Se encontr� un objeto de munici�n en el inventario
			bFoundAmmo = true;

			// Se encontr� un objeto de munici�n en el inventario
			// Elimina el objeto de munici�n del inventario			
			//MyInventory->RemoveFromInventory(AmmoItem);
			NumProyectilesDisparados = 0; // Restablece el contador de proyectiles disparados.
			MaxProyectilesDisparados = 20; // Establece el n�mero m�ximo de proyectiles disparados
			bCanFire = true; // Permite al jugador disparar nuevamente.

			if (GEngine)
			{
				FString Message = FString::Printf(TEXT("Se recargaron +%d de municion"), MaxProyectilesDisparados);
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Message);
			}

			NumItems -= 1; // Disminuye el contador de objetos en el inventario
			CheckInventory();

			// Sal del bucle ya que encontraste y manejaste un objeto de munici�n
			break;
		}
	}

	// Verifica si no se encontr� ning�n objeto de munici�n
	if (!bFoundAmmo)
	{
		// Muestra un mensaje indicando que no se encontr� ning�n objeto de munici�n
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "No tienes municion para recargar");
		}
	}
}

void AGalaga_USFXPawn::CheckInventory()
{

	// Verifica si el componente de inventario existe
	if (MyInventory)
	{
		// Obtiene el n�mero de objetos de inventario en el inventario del jugador
		//Artificio para tener el numero de objetos en el inventario


		// Inicializa una variable para contar el n�mero de elementos
		// Declarar la cola y obtener un puntero a ella
		// Obtener un puntero a la cola de inventario


		//int32 NumItems = MyInventory->CurrentInventory.Num();

		// Puedes hacer lo que quieras con NumItems, como mostrarlo en pantalla, usarlo en l�gica de juego, etc.
		if (GEngine)
		{
			FString Message = FString::Printf(TEXT("Tienes %d objetos en tu inventario"), NumItems);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, Message);
		}
	}
	else
	{

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "No tienes un Items de municion en el inventario");
		}
	}
}



void AGalaga_USFXPawn::ReloadEnergy()
{
	// Bandera para verificar si se encontr� un objeto de munici�n
	bool bFoundEnergy = false;
	// Itera sobre los objetos en el inventario para encontrar uno de Energia
	ACapsulas* InventoryItem = nullptr;
	//for (AInventoryActor* InventoryItem : MyInventory->CurrentInventory)
	while (MyInventory->CurrentInventory.Dequeue(InventoryItem))
	{
		// Intenta hacer un cast a AInventoryActorEnergy
		ACapsulasEnergia* EnergyItem = Cast<ACapsulasEnergia>(InventoryItem);
		if (EnergyItem)
		{
			// Se encontr� un objeto de munici�n en el inventario
			bFoundEnergy = true;
			// Se encontr� un objeto de Energia en el inventario
			// Elimina el objeto de munici�n del inventario
			//MyInventory->RemoveFromInventory(EnergyItem);

			// Muestra un mensaje de depuraci�n
			if (GEngine)
			{
				//FString Message = FString::Printf(TEXT("Se recargaron %d de municion"), MaxProyectilesDisparados);
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Se restablecio 100 pts de vida");
			}
			NumItems -= 1;
			CheckInventory();
			// Sal del bucle ya que encontraste y manejaste un objeto de munici�n
			break;
		}

	}
	// Verifica si no se encontr� ning�n objeto de munici�n
	if (!bFoundEnergy)
	{
		// Muestra un mensaje indicando que no se encontr� ning�n objeto de munici�n
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "No tienes Energia para recargar");
		}
	}
}
