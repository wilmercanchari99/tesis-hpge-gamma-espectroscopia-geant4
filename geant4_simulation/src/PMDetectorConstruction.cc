#include "PMDetectorConstruction.hh"

PMDetectorConstruction::PMDetectorConstruction() {}

PMDetectorConstruction::~PMDetectorConstruction() {}

G4VPhysicalVolume *PMDetectorConstruction::Construct() {
    // Opción para activar/desactivar la verificación de superposición de volúmenes
    G4bool checkOverlaps = true;
    G4NistManager *nist = G4NistManager::Instance();

    // Parámetros del entorno
    G4double env_sizeX = 1.5 * m;

    // Definir materiales
    G4Material *world_mat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material *plomo = nist->FindOrBuildMaterial("G4_Pb");
    G4Material *aluminio = nist->FindOrBuildMaterial("G4_Al");
    G4Material *aire = nist->ConstructNewGasMaterial("Coldair", "G4_AIR", 77. * kelvin, 0.71 * atmosphere);

    // =========================================================
    // DEFINICIÓN DEL MATERIAL DE LA FUENTE
    // Descomentar únicamente la fuente que se desea utilizar
    // =========================================================

    // -------------------------
    // Fuente de 60Co
    // Descomentar para utilizar
    // -------------------------
    /*
    G4Isotope *Co60 = new G4Isotope("Co60", 27, 60, 59.933 * g / mole);
    G4Element *elCo60 = new G4Element("Cobalt-60", "Co60", 1);
    elCo60->AddIsotope(Co60, 100.0 * perCent);
    G4Material *matFuente = new G4Material("Co60Source", 8.9 * g / cm3, 1);
    matFuente->AddElement(elCo60, 100.0 * perCent);
    */

    // -------------------------
    // Fuente de 137Cs
    // Descomentar para utilizar
    // -------------------------
    G4Isotope *Cs137 = new G4Isotope("Cs137", 55, 137, 136.907 * g / mole);
    G4Element *elCs137 = new G4Element("Cesium-137", "Cs137", 1);
    elCs137->AddIsotope(Cs137, 100.0 * perCent);
    G4Material *matFuente = new G4Material("Cs137Source", 1.93 * g / cm3, 1);
    matFuente->AddElement(elCs137, 100.0 * perCent);

    // -------------------------
    // Fuente de 152Eu
    // Descomentar para utilizar
    // -------------------------
    /*
    G4Isotope *Eu152 = new G4Isotope("Eu152", 63, 152, 151.922 * g / mole);
    G4Element *elEu152 = new G4Element("Europium-152", "Eu152", 1);
    elEu152->AddIsotope(Eu152, 100.0 * perCent);
    G4Material *matFuente = new G4Material("Eu152Source", 5.24 * g / cm3, 1);
    matFuente->AddElement(elEu152, 100.0 * perCent);
    */

    // Mundo
    G4Box *solidWorld = new G4Box("World", env_sizeX, env_sizeX, env_sizeX);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(
        0, G4ThreeVector(), logicWorld, "World", 0, false, 0, checkOverlaps);

    // Fuente
    G4double sourceRadius = 1. * mm;
    G4Sphere *solidSource = new G4Sphere("solidSource", 0.0, sourceRadius, 0.0, 360. * deg, 0.0, 180. * deg);
    G4LogicalVolume *logicSource = new G4LogicalVolume(solidSource, matFuente, "logicSource");
    new G4PVPlacement(0, G4ThreeVector(0., 0., 19.25 * cm), logicSource, "physSource", logicWorld, 0, checkOverlaps);

    // Mismo color para cualquiera de las tres fuentes
    G4VisAttributes *sourceVisAtt = new G4VisAttributes(G4Color(0.83, 0.69, 0.22, 1.0));
    sourceVisAtt->SetForceSolid(true);
    logicSource->SetVisAttributes(sourceVisAtt);

    // Blindaje de Plomo
    G4Tubs *blindaje = new G4Tubs("bs", 5.82 * cm, 10.1 * cm, 3.5 * cm, 0. * deg, 360. * deg);
    G4LogicalVolume *logic_blindaje = new G4LogicalVolume(blindaje, plomo, "bl");
    new G4PVPlacement(0, G4ThreeVector(), logic_blindaje, "bf", logicWorld, false, 0, checkOverlaps);

    G4VisAttributes *blinVisAtt = new G4VisAttributes(G4Color(0.5, 0.5, 0.5, 1.0));
    blinVisAtt->SetForceSolid(true);
    logic_blindaje->SetVisAttributes(blinVisAtt);

    // Recubrimiento de Aluminio
    G4Tubs *recubrimiento = new G4Tubs("rs", 0 * cm, 3.8 * cm, 3.25 * cm, 0. * deg, 360. * deg);
    G4LogicalVolume *logic_recubrimiento = new G4LogicalVolume(recubrimiento, aluminio, "rl");
    new G4PVPlacement(0, G4ThreeVector(0.*cm, 0.*cm, 0.*cm), logic_recubrimiento, "rf", logicWorld, false, 0, checkOverlaps);

    // Enfriamiento con aire
    G4Tubs *enfriamiento = new G4Tubs("es", 0 * cm, 3.7 * cm, 3.15 * cm, 0. * deg, 360. * deg);
    G4LogicalVolume *logic_enfriamiento = new G4LogicalVolume(enfriamiento, aire, "el");
    new G4PVPlacement(0, G4ThreeVector(0.*cm, 0.*cm, 0.*cm), logic_enfriamiento, "ef", logic_recubrimiento, false, 0, checkOverlaps);

    // Germanio
    G4Material *germanio = new G4Material("ge", 32, 72.64, 5.32 * g / cm3, kStateSolid, 77 * kelvin, 0.71 * atmosphere);
    G4Tubs *s_germanio = new G4Tubs("gs", 0.0 * cm, 3.3 * cm, 3.2 * cm, 0. * deg, 360. * deg);
    logic_ger1 = new G4LogicalVolume(s_germanio, germanio, "gl");
    new G4PVPlacement(0, G4ThreeVector(0.*cm, 0.*cm, 0.*cm), logic_ger1, "gf", logic_enfriamiento, false, 0, checkOverlaps);

    G4VisAttributes *detVisAtt = new G4VisAttributes(G4Color(0.2, 0.2, 0.2, 1.0));
    detVisAtt->SetForceSolid(true);
    logic_ger1->SetVisAttributes(detVisAtt);

    return physWorld;
}

void PMDetectorConstruction::ConstructSDandField() {
    PMSensitiveDetector *sensDet = new PMSensitiveDetector("SensitveDetector");
    logic_ger1->SetSensitiveDetector(sensDet);
    G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);
}