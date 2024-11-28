// Fill out your copyright notice in the Description page of Project Settings.

#include "FlappyBirdClone/Public/Bird.h"
#include "Pipes.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABird::ABird()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the mesh of the bird and set as root
	BirdMesh = CreateDefaultSubobject<UStaticMeshComponent>("Bird");
	SetRootComponent(BirdMesh);

	// Enable physics, gravity and collision generation
	BirdMesh->SetSimulatePhysics(true);
	BirdMesh->SetEnableGravity(true);
	BirdMesh->SetGenerateOverlapEvents(true);

	// Set the collision types
	BirdMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BirdMesh->SetCollisionObjectType(ECC_PhysicsBody);
	BirdMesh->SetCollisionResponseToAllChannels(ECR_Overlap);

	// Bind the hit event
	BirdMesh->OnComponentBeginOverlap.AddDynamic(this, &ABird::OnHit);
}

void ABird::BeginPlay()
{
	Super::BeginPlay();

	// Get the game state
	AGameStateBase* MyGameState = UGameplayStatics::GetGameState(GetWorld());
	if (!MyGameState) return;

	// Cast the bird game state
	ABirdGameState* CastedBirdGameState = Cast<ABirdGameState>(MyGameState);
	if (!CastedBirdGameState) return;

	// Cache the bird game state
	BirdGameState = CastedBirdGameState;
}

void ABird::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	if (OtherActor == nullptr) { UE_LOG(LogTemp, Warning, TEXT("Other actor is null")); return; }
	if (OtherComp == nullptr) { UE_LOG(LogTemp, Warning, TEXT("OtherComp component is null")); return; }

	APipes* Pipes = Cast<APipes>(OtherActor);
	if (Pipes == nullptr) { UE_LOG(LogTemp, Warning, TEXT("Pipes cannot cast")); return; }

	// Check the overlap component
	if (OtherComp == Pipes->GetTopPipeMesh() || OtherComp == Pipes->GetBottomPipeMesh())
		BirdGameState->OnBirdDead();

	if (OtherComp == Pipes->GetHitPoint())
		BirdGameState->AddScore();
}

// Applies the impulse to the bird
void ABird::ApplyImpulse() const
{
	const FVector Impulse = FVector(0, 0, ImpulseForce);
	BirdMesh->AddImpulse(Impulse);
}
