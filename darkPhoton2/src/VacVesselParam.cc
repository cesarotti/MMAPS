/*
 *
 * parametrizes concentric rings
 *
 */

#include "VacVesselParam.hh"

#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"
#include "G4SystemOfUnits.hh"

VacVesselParam::VacVesselParam(  
        G4int    noChambers, 
        G4double startZ, 
	G4double length) 
 : G4VPVParameterisation()
{
   fNoChambers =  noChambers; 
   fStartZ     =  startZ; 
   fLength = length;
}

VacVesselParam::~VacVesselParam()
{ }

//Moves center of vessel segment

void VacVesselParam::ComputeTransformation
(const G4int copyNo, G4VPhysicalVolume* physVol) const
{
  G4int copy2 = copyNo;
  bool test=false;
  if (copy2>9)
    test = false;
  if (physVol)
    test = true;
}


void VacVesselParam::ComputeDimensions
(G4Tubs& ring, const G4int copyNo, const G4VPhysicalVolume*) const
{
  // Note: copyNo will start with zero!
  G4double rmax =  (copyNo+1)*m;
  G4double rmin =  (copyNo)*m;
  ring.SetInnerRadius(rmin);
  ring.SetOuterRadius(rmax);
  ring.SetZHalfLength(fLength/2);
  ring.SetStartPhiAngle(0.*deg);
  ring.SetDeltaPhiAngle(360.*deg);
}
