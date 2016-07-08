/*
 * Dark Photon  Detector Messenger 
 * !!!History 
 *    CJC 6.15.14 created
 * 
 * This class is important as it implements the commands necessary 
 * for complete construction of the detector geometry and materials
 */

#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"

DetectorMessenger::DetectorMessenger(DetectorConstruction* Det)
 : G4UImessenger(),
   fDetectorConstruction(Det)
{
  fDirectory = new G4UIdirectory("/darkPhotons/");
  fDirectory->SetGuidance("UI commands specific to this eample.");

  fDetDirectory = new G4UIdirectory("/darkPhotons/det/");
  fDetDirectory->SetGuidance("Detector construction control");

  fCalMatCmd = new G4UIcmdWithAString("/darkPhotons/det/setCalorMaterial",this);
  fCalMatCmd->SetGuidance("Select Material of the Calorimeter");
  fCalMatCmd->SetParameterName("choice",false);
  fCalMatCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  fStepMaxCmd = new G4UIcmdWithADoubleAndUnit("/darkPhotons/det/stepMax",this);
  fStepMaxCmd->SetGuidance("Define a step max");
  fStepMaxCmd->SetParameterName("stepMax", false);
  fStepMaxCmd->SetUnitCategory("Length");
  fStepMaxCmd->AvailableForStates(G4State_Idle);

  fCalPosCmd = new G4UIcmdWithADoubleAndUnit("/darkPhotons/det/setCalorPos", this); 
  fCalPosCmd->SetGuidance("Define position of calorimeter"); 
  fCalPosCmd->SetParameterName("calorPos", false); 
  fCalPosCmd->SetUnitCategory("Length");
  fCalPosCmd->AvailableForStates(G4State_Idle); 

  fChamNumCmd = new G4UIcmdWithAnInteger("/darkPhotons/det/setChamNum", this);
  fChamNumCmd->SetGuidance("Define number of chambers");
  fChamNumCmd->SetParameterName("chamNum", false);
  fChamNumCmd->AvailableForStates(G4State_Idle);

}


DetectorMessenger::~DetectorMessenger()
{
  //delete fTargMatCmd;
  delete fCalMatCmd;
  delete fStepMaxCmd;
  delete fChamNumCmd;
  delete fCalPosCmd; 
  delete fDirectory;
  delete fDetDirectory;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  /*
  if( command == fTargMatCmd )
   { fDetectorConstruction->SetTargetMaterial(newValue);}
  */

  if( command == fCalMatCmd )
   { fDetectorConstruction->SetCalorMaterial(newValue);}

  if( command == fStepMaxCmd ) {
    fDetectorConstruction
      ->SetMaxStep(fStepMaxCmd->GetNewDoubleValue(newValue));
  }   

  if( command == fCalPosCmd ) {
    // fDetectorConstruction
    //     ->SetCalorDist(fCalPosCmd->GetNewDoubleValue(newValue)); 
  }

  if( command == fChamNumCmd ) {
    //fDetectorConstruction
    // ->SetChamberNumber(fChamNumCmd->GetNewIntValue(newValue));
  }

  
}
