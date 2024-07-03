#include "globals.hh"

#include "G4RunManager.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"

#include "QGSP_BERT.hh"
#include "FTFP_BERT.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "SteppingAction.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4Random.h"

int main(int argc, char** argv)
{
    G4Random::setTheSeed(time(0));

    G4RunManager* runManager = new G4RunManager;

    G4VModularPhysicsList* physicsList = new QGSP_BERT;
    physicsList -> RegisterPhysics(new G4StepLimiterPhysics());
    runManager -> SetUserInitialization(physicsList);

    G4String particleName = "alpha";
    G4double particleEnergy = 5.486; // MeV (241Am 85.2 %)
    //G4double particleEnergy = 5.443; // MeV (241Am 12.8 %)
    G4double px = 0;
    G4double py = 0;
    G4double pz = 1;
    G4String outputFileName = "data/sim_alpha1.txt";

    PrimaryGeneratorAction* pga = new PrimaryGeneratorAction(particleName,particleEnergy,px,py,pz);
    DetectorConstruction* det = new DetectorConstruction();
    SteppingAction* step = new SteppingAction(outputFileName);

    runManager -> SetUserInitialization(det);
    runManager -> SetUserAction(pga);
    runManager -> SetUserAction(step);
    runManager -> Initialize();

    G4VisManager* visManager = new G4VisExecutive;
    visManager -> Initialize();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    if (argc>1) {
        UImanager -> ApplyCommand(G4String("/control/execute ")+argv[1]);
    }
    else {
        G4UIExecutive* ui = new G4UIExecutive(argc, argv);
        UImanager -> ApplyCommand("/control/execute vis.mac"); 
        ui -> SessionStart();
        delete ui;
    }

    delete visManager;
    delete runManager;

    return 0;
}
