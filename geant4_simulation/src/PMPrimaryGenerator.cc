#include "PMPrimaryGenerator.hh"

PMPrimaryGenerator::PMPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);

    // Posición de partícula (16 cm desde la cara externa del aluminio)
    G4double x = 0. * cm;
    G4double y = 0. * cm;
    G4double z = 19.25 * cm;

    G4ThreeVector pos(x, y, z);

    // Dirección de partícula (isotrópica por decaimiento → no importa aquí)
    G4double px = 0.;
    G4double py = 0.;
    G4double pz = 0.;

    G4ThreeVector mom(px, py, pz);

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
}

PMPrimaryGenerator::~PMPrimaryGenerator()
{
    delete fParticleGun;
}

void PMPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    // =========================================================
    // SELECCIÓN DE LA FUENTE RADIACTIVA
    // Descomentar únicamente la fuente que se desea utilizar
    // =========================================================

    // -------------------------
    // Fuente de 60Co
    // Descomentar para utilizar
    // -------------------------
    /*
    G4int Z = 27;
    G4int A = 60;
    */

    // -------------------------
    // Fuente de 137Cs
    // Descomentar para utilizar
    // -------------------------
    G4int Z = 55;
    G4int A = 137;

    // -------------------------
    // Fuente de 152Eu
    // Descomentar para utilizar
    // -------------------------
    /*
    G4int Z = 63;
    G4int A = 152;
    */

    G4double charge = 0. * eplus;
    G4double energy = 0. * keV;

    G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z, A, energy);
    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(charge);
    fParticleGun->SetParticleEnergy(energy);

    // Crear vertex
    fParticleGun->GeneratePrimaryVertex(anEvent);
}