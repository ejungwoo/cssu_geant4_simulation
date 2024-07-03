#include "PrimaryGeneratorAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction(
        G4String particleName,
        G4double particleEnergy,
        G4double px,
        G4double py,
        G4double pz
        )
: G4VUserPrimaryGeneratorAction()
{
    fParticleGun = new G4ParticleGun(1);
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable -> FindParticle(particleName);
    fParticleGun -> SetParticleDefinition(particle);
    fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(px,py,pz));
    fParticleGun -> SetParticleEnergy(particleEnergy*MeV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    fParticleGun -> GeneratePrimaryVertex(anEvent);
}
