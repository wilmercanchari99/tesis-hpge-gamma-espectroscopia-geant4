#ifndef PMDETECTORCONSTRUCTION_HH
#define PMDETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"

#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"
#include "G4ThreeVector.hh"

// carga clases para la definición de materiales
#include "G4Isotope.hh"
#include "G4Element.hh"

#include "globals.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4SDManager.hh"

#include "PMSensitiveDetector.hh"

// clases para operaciones booleanas
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"

class PMDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    PMDetectorConstruction();
    virtual ~PMDetectorConstruction();

    virtual G4VPhysicalVolume *Construct();

private:
    G4LogicalVolume *logic_ger1;

    virtual void ConstructSDandField();
};

#endif
