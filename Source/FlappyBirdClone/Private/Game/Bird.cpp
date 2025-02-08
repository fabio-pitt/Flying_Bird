// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#include "Game/Bird.h"
#include "Pipes/Pipes.h"
#include "Other/Getter.h"
#include "Other/Logs.h"

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

// Called when the game starts or when spawned
void ABird::BeginPlay()
{
	Super::BeginPlay();

	// Get the bird game state
	BirdGameState = UGetter::GetBirdGameState(GetWorld());
}

// Called when the actor is hit
// ReSharper disable once CppParameterMayBeConstPtrOrRef
// ReSharper disable once CppMemberFunctionMayBeConst
void ABird::OnHit(UPrimitiveComponent*, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32, bool, const FHitResult&)
{
	// Check the other actor and component
	if (OtherActor == nullptr) { ULogs::Error("Bird - OnHit: OtherActor is null"); return; }
	if (OtherComp == nullptr) { ULogs::Error("Bird - OnHit: OtherComp is null"); return; }

	const APipes* Pipes = Cast<APipes>(OtherActor);
	if (Pipes == nullptr) { ULogs::Error("Bird - OnHit: Pipes is null"); return; }

	// Check the overlap component
	if (OtherComp == Pipes->GetTopPipeMesh() || OtherComp == Pipes->GetBottomPipeMesh())
		if (BirdGameState) BirdGameState->OnBirdDead();

	if (OtherComp == Pipes->GetHitPoint())
		if (BirdGameState) BirdGameState->AddScore();
}

// Applies the impulse to the bird
void ABird::ApplyImpulse() const
{
	const FVector Impulse = FVector(0, 0, ImpulseForce * ImpulseMultiplier);
	BirdMesh->AddImpulse(Impulse);
}
