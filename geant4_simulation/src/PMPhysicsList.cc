#include "PMPhysicsList.hh"

PMPhysicsList::PMPhysicsList()
{
    // Física electromagenetico
    RegisterPhysics(new G4EmStandardPhysics());

    // Física decaimiento radiactivo
    RegisterPhysics(new G4RadioactiveDecayPhysics());

    // Física decaimiento
    RegisterPhysics(new G4DecayPhysics());
}

PMPhysicsList::~PMPhysicsList()
{
}