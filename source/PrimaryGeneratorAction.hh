#ifndef G4EJPRIMARYGENERATORACTION_HH
#define G4EJPRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include "globals.hh"

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
    public:
        PrimaryGeneratorAction(
                G4String particleName = "proton",
                G4double particleEnergy = 40,
                G4double px = 0.,
                G4double py = 0.,
                G4double pz = 1.
                );
        virtual ~PrimaryGeneratorAction();
        virtual void GeneratePrimaries(G4Event*);         

    private:
        G4ParticleGun* fParticleGun;
};

#endif
