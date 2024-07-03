#ifndef G4EJSTEPPINGACTION_HH
#define G4EJSTEPPINGACTION_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "globals.hh"
#include <fstream>

class SteppingAction : public G4UserSteppingAction
{
    public:
        SteppingAction(G4String dataFileName);
        virtual ~SteppingAction();

        // method from the base class
        virtual void UserSteppingAction(const G4Step*);

    private:
        std::ofstream fOutput;
};

#endif
