#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4UserLimits.hh"
#include <iostream>

DetectorConstruction::DetectorConstruction()
    : G4VUserDetectorConstruction()
{
}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{  
    G4NistManager* nist = G4NistManager::Instance();

    // -------------------------------------------------------------------------------------
    // World
    G4Material* world_mat = nist -> FindOrBuildMaterial("G4_Galactic");
    G4double world_size = 200*mm;

    G4Box* solidWorld = new G4Box("World", 0.5*world_size, 0.5*world_size, 0.5*world_size);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, true);

    // -------------------------------------------------------------------------------------
    // Detector
    G4double pressure = 26664.5*hep_pascal; // 200 Torr
    G4double temperature = 293.15*kelvin; //
    G4double density = 0.947*mg/cm3;
    G4Material* detector_mat = new G4Material("CF4", density,2,kStateGas,temperature,pressure);
    G4Element* element_C = nist -> FindOrBuildElement("C");
    G4Element* element_F = nist -> FindOrBuildElement("F");
    detector_mat -> AddElement(element_C,1);
    detector_mat -> AddElement(element_F,4);

    G4double wx = 120*mm;
    G4double wy = 120*mm;
    G4double wz = 200*mm;
    G4double detector_offset_z = 50*mm + 0.5*wz;
    G4Box* solidDetector = new G4Box("Detector", 0.5*wx, 0.5*wy, 0.5*wz);
    G4LogicalVolume* logicDetector = new G4LogicalVolume(solidDetector, detector_mat, "Detector");
    logicDetector -> SetUserLimits(new G4UserLimits(.1*mm));
    new G4PVPlacement(0, G4ThreeVector(0,0,detector_offset_z), logicDetector, "Detector", logicWorld, false, 1, true);

    return physWorld;
}
