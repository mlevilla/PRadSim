//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// TrackingAction.cc
// Developer : Chao Gu
// History:
//   Mar 2017, C. Gu, Rewrite sensitive detectors.
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TrackingAction.hh"

#include "TrackInformation.hh"
#include "TrackingMessenger.hh"

#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "G4TrackVector.hh"
#include "G4TrackingManager.hh"
#include "G4UserTrackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackingAction::TrackingAction() : G4UserTrackingAction(), fNoSecondary(false)
{
    trackingMessenger = new TrackingMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackingAction::~TrackingAction()
{
    //
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackingAction::PreUserTrackingAction(const G4Track *aTrack)
{
    if (aTrack->GetParentID() != 0 && fNoSecondary) {
        fpTrackingManager->GetTrack()->SetTrackStatus(fKillTrackAndSecondaries);
        return;
    }

    if (aTrack->GetParentID() == 0 && aTrack->GetUserInformation() == 0) {
        TrackInformation *aTrackInfo = new TrackInformation(aTrack);
        G4Track *theTrack = (G4Track *)aTrack;
        theTrack->SetUserInformation(aTrackInfo);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackingAction::PostUserTrackingAction(const G4Track *aTrack)
{
    G4TrackVector *theSecondaries = fpTrackingManager->GimmeSecondaries();

    if (theSecondaries) {
        TrackInformation *theTrackInfo = (TrackInformation *)(aTrack->GetUserInformation());
        size_t nSecondaries = theSecondaries->size();

        if (nSecondaries > 0) {
            for (size_t i = 0; i < nSecondaries; i++) {
                if ((*theSecondaries)[i]->GetUserInformation() == 0) {
                    TrackInformation *newTrackInfo = new TrackInformation(theTrackInfo);
                    (*theSecondaries)[i]->SetUserInformation(newTrackInfo);
                }
            }
        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
