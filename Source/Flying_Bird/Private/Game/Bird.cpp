// 3D version of Flappy Bird. Original by Dong Nguyen. Remake by Fabio Pittaccio.

#include "Game/Bird.h"
#include "Flying_Bird/Flying_Bird.h"
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

	// Enable physics and gravity
	BirdMesh->SetSimulatePhysics(false);
	BirdMesh->SetEnableGravity(false);
	
	// Set the collision types
	BirdMesh->SetGenerateOverlapEvents(true);
	BirdMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BirdMesh->SetCollisionObjectType(BIRD);

	// Set the collision response
	BirdMesh->SetCollisionResponseToAllChannels(ECR_Block);
	BirdMesh->SetCollisionResponseToChannel(BIRD, ECR_Ignore);
	BirdMesh->SetCollisionResponseToChannel(PIPE, ECR_Overlap);
	BirdMesh->SetCollisionResponseToChannel(SCORE, ECR_Overlap);

	// Set physics constraints to prevent getting stuck
	if (FBodyInstance* BodyInst = BirdMesh->GetBodyInstance())
	{
		BodyInst->bLockXRotation = true;
		BodyInst->bLockYRotation = true;
		BodyInst->bLockZRotation = true;
		BodyInst->LinearDamping = 0.5f;    // Add some air resistance
		BodyInst->MaxAngularVelocity = 0.0f; // Prevent rotation
	}

	// Bind the hit event
	BirdMesh->OnComponentBeginOverlap.AddDynamic(this, &ABird::OnHit);
}

// Called when the game starts or when spawned
void ABird::BeginPlay()
{
	Super::BeginPlay();

	// Get the bird game state
	BirdGameState = UGetter::GetBirdGameState(GetWorld());
	if (!BirdGameState) return;

	// Get the delegate to star the game
	BirdGameState->OnStartGame.AddDynamic(this, &ABird::StartGame);
}

// Called to start the game
// ReSharper disable once CppMemberFunctionMayBeConst
void ABird::StartGame()
{
	EnablePhysics();
}

// Called to enable physics
void ABird::EnablePhysics() const
{
	BirdMesh->SetSimulatePhysics(true);
	BirdMesh->SetEnableGravity(true);
}

// Called when the actor is hit
// ReSharper disable once CppParameterMayBeConstPtrOrRef
// ReSharper disable once CppMemberFunctionMayBeConst
void ABird::OnHit(UPrimitiveComponent*, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32, bool, const FHitResult&)
{
	// Check the other actor and component
	if (!OtherActor || !OtherComp) { ULogs::Error("Bird - OnHit: invalid collision"); return; }

	// Cast the pipes from the other actor
	const APipes* Pipes = Cast<APipes>(OtherActor);
	if (!Pipes) { ULogs::Error("Bird - OnHit: cannot cast pipes"); return; }

	// Check the overlap component: top pipe or bottom pipe = dead
	if (OtherComp == Pipes->GetTopPipeMesh() || OtherComp == Pipes->GetBottomPipeMesh())
		if (BirdGameState) BirdGameState->OnBirdDead();

	// Check the overlap component: hit point = score
	if (OtherComp == Pipes->GetHitPoint())
		if (BirdGameState) BirdGameState->AddScore();
}

// Applies the impulse to the bird
void ABird::ApplyImpulse() const
{
	// Check if the bird mesh is valid
	if (!BirdMesh) { ULogs::Error("Bird - ApplyImpulse: BirdMesh is null"); return; }

	// Check if the mesh is simulating physics
	if (!BirdMesh->IsSimulatingPhysics()) return;

	// Reset vertical velocity
	const FVector CurrentVelocity = BirdMesh->GetPhysicsLinearVelocity();
	const FVector NewVelocity = FVector(CurrentVelocity.X, CurrentVelocity.Y, 0);
	BirdMesh->SetPhysicsLinearVelocity(NewVelocity);
	
	// Calculate the impulse force and add to the mesh
	const FVector Impulse = FVector(0, 0, ImpulseForce);
	BirdMesh->AddImpulse(Impulse, NAME_None, true);
}
