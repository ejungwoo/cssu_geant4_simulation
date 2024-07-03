#include "SteppingAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4EventManager.hh"
#include <iomanip>

using namespace std;

SteppingAction::SteppingAction(G4String dataFileName)
    : G4UserSteppingAction()
{
    fOutput.open(dataFileName);
}

SteppingAction::~SteppingAction()
{
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    G4int eventID = G4RunManager::GetRunManager() -> GetCurrentEvent() -> GetEventID();
    G4int volumeID = step -> GetPreStepPoint() -> GetPhysicalVolume() -> GetCopyNo();
    G4double energy = step -> GetTotalEnergyDeposit();

    G4StepPoint* preStepPoint = step -> GetPreStepPoint();
    G4ThreeVector pos = preStepPoint -> GetPosition();

    if (energy>1.e-10)
        fOutput << setw(5) << eventID << setw(5) << volumeID << setw(15) << pos.x() << setw(15) << pos.y() << setw(15) << pos.z() << setw(15) << energy << endl;
}
