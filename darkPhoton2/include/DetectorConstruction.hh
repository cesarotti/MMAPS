/*
 *Dark Photon Detector Construction
 *!!!History
 * CJC 6.15.14 created
 *
 */

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "tls.hh"

#include <iostream>
#include <fstream>
#include <vector>

class G4Tubs;
class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4UserLimits;
class G4GlobalMagFieldMessenger;
class DetectorMessenger;

/*
 * Detector definition includes information regarding
 * materials, calorimeters, regions of space
 * fields, or geometry in general
 */

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  DetectorConstruction();
  DetectorConstruction(G4double, G4int );
  virtual ~DetectorConstruction();

public:
  //constructs the geometries
  virtual G4VPhysicalVolume* Construct();
  //applies the sensitive detectors
  virtual void ConstructSDandField();

  //set methods
  //!!!
  void SetTargetMaterial (G4String );
  void SetCalorMaterial (G4String );
  void SetMaxStep(G4double );
  void SetCalorDist(G4double );
  void SetChamberMaterial (G4String ); //Changes material of vacuum chamber from detector messenger
  void SetChamberNumber(G4int );
  void SetCheckOverlaps(G4bool );
  void PositionChambers(G4double );

  //get methods
  // G4double GetCalorDistance();



private:
  //methods
  void DefineMaterials(); //defines materials for elements of the detector
  G4VPhysicalVolume* DefineVolumes(); //defines geometry

  //Target Members
  G4LogicalVolume* fLogicTarget; //pointer to logical target
  G4Material* fTargetMaterial; // pointer to target material    
  G4double fTargetLength;
  G4double fTargetFace;
  G4double fTargetPos;

  //Magnet Members
  G4double fMagnetLength; 
  G4double fTarToMagDist;
  G4double fMagnetFace;


  //Calorimeter Members
  G4double fCrystalLength;
  G4double fCalorSpacing;
  G4double fCrystalFace;
  G4double fCalTol;


  //Omni Detector 
  G4double fThetaMin; 
  G4double fThetaMax;

  //Vacuum chamber members
  G4double fChamThickness;


  //data members
  G4Tubs** fSolidCham; //Pointer to solids of chamber
  G4Tubs** fSolidCaps; //Pointer to caps on chamber

  G4LogicalVolume** fLogicCalor; //pointer to calorimeter
  G4LogicalVolume** fLogicCham;
  G4LogicalVolume** fLogicCaps;
  
  //for setCalorPos command
  G4VPhysicalVolume** fPhysCalor; //pointer to calorimeter physical volumes
  G4VPhysicalVolume** fPhysCham; //pointer to physical volumes of chambers
  G4VPhysicalVolume** fPhysCaps;

  G4VPhysicalVolume** fVolumesShiftedByCalorDist; //duh
  G4double fCalorDist; //distance from middle of target to center of crystal
  G4int fNchambers; // Number of chambers in vacuum vessel
  G4double fCapThickness; //thickness of caps in vacuum vessel
  G4LogicalVolume* worldLV; //the world logical vol
 
  G4Material* fCalorMaterial; // pointer to calorimeter material
  G4Material* fWallMaterial; // wall material
  G4Material* fBeamDumpMaterial; //beam dump material
  G4Material* fCapMaterial;
  G4Material* fCLEOMaterial; // pointer to CLEO 'stuff'
  G4Material* fWorldMaterial; // pointer to world material
  G4Material* fSpaceMaterial; //Variable to determine
  G4Material* fLiningMaterial; // pointer to material for lining calorimeter
  G4Material* fVacuumMaterial; // vacuum
  G4Material* fBeamLineMaterial; //duh
  G4Material* fScintillatorMaterial;
  G4Material* fMagnetMaterial; 


 
  G4UserLimits* fStepLimit; // pointer to user step limits

  DetectorMessenger* fMessenger; // messenger

  G4bool fCheckOverlaps; // option to turn on or off overlap checking.

  G4bool CLEObool; //determines if running simulation with CLEO 'stuff'

  //G4double fCenterToFront; //distance from center fo the target to the 

  static G4ThreadLocal G4GlobalMagFieldMessenger* fMagFieldMessenger;



};

#endif
