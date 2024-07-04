#ifndef G4EJDETECTORCONSTRUCTION_HH
#define G4EJDETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class DetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        DetectorConstruction(G4double stepLimit=10, G4double pressureTorr=200.);
        virtual ~DetectorConstruction();

        virtual G4VPhysicalVolume* Construct();

        G4double fStepLimit;
        G4double fPressureTorr;
};

#endif
