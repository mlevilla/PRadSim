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
// HyCalParameterisation.hh
// Developer : Chao Peng, Chao Gu
// History:
//   Aug 2012, C. Peng, Original version.
//   Jan 2017, C. Gu, Rewrite with ROOT support.
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef HyCalParameterisation_h
#define HyCalParameterisation_h 1

#include "ConfigObject.h"

#include "G4VPVParameterisation.hh"

#include <string>
#include <vector>

class G4Box;
class G4Material;
class G4VPhysicalVolume;

// Dummy declarations to get rid of warnings ...
class G4Trd;
class G4Trap;
class G4Cons;
class G4Orb;
class G4Sphere;
class G4Torus;
class G4Para;
class G4Hype;
class G4Tubs;
class G4Polycone;
class G4Polyhedra;
class G4Ellipsoid;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HyCalParameterisation : public G4VPVParameterisation, public ConfigObject
{
public:
    enum HyCal_Module_Type {
        Lead_Glass,
        Lead_Tungstate,
    };

    struct HyCal_Module {
        std::string name;
        HyCal_Module_Type type;
        double sizex;
        double sizey;
        double length;
        double x;
        double y;
        double z;
        HyCal_Module() {}
        HyCal_Module(std::string n, HyCal_Module_Type t, double sx, double sy, double l, double xx, double yy, double zz) : name(n), type(t), sizex(sx), sizey(sy), length(l), x(xx), y(yy), z(zz) {}
    };

public:
    HyCalParameterisation(const std::string &path = "", G4int conf = 0);
    virtual ~HyCalParameterisation();

    void Configure(const std::string &path);
    void LoadModuleList(const std::string &path);

    void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const;
    void ComputeDimensions(G4Box &CalBlock, const G4int copyNo, const G4VPhysicalVolume *physVol) const;
    G4Material *ComputeMaterial(const G4int copyNo, G4VPhysicalVolume *currVol, const G4VTouchable *pTouch = NULL);

    inline size_t GetNumber();

private: // Dummy declarations to get rid of warnings ...
    void ComputeDimensions(G4Trd &, const G4int, const G4VPhysicalVolume *) const {}
    void ComputeDimensions(G4Trap &, const G4int, const G4VPhysicalVolume *) const {}
    void ComputeDimensions(G4Cons &, const G4int, const G4VPhysicalVolume *) const {}
    void ComputeDimensions(G4Sphere &, const G4int, const G4VPhysicalVolume *) const {}
    void ComputeDimensions(G4Orb &, const G4int, const G4VPhysicalVolume *) const {}
    void ComputeDimensions(G4Torus &, const G4int, const G4VPhysicalVolume *) const {}
    void ComputeDimensions(G4Para &, const G4int, const G4VPhysicalVolume *) const {}
    void ComputeDimensions(G4Hype &, const G4int, const G4VPhysicalVolume *) const {}
    void ComputeDimensions(G4Tubs &, const G4int, const G4VPhysicalVolume *) const {}
    void ComputeDimensions(G4Polycone &, const G4int, const G4VPhysicalVolume *) const {}
    void ComputeDimensions(G4Polyhedra &, const G4int, const G4VPhysicalVolume *) const {}
    void ComputeDimensions(G4Ellipsoid &, const G4int, const G4VPhysicalVolume *) const {}

private:
    std::vector<HyCal_Module> moduleList;
    
    G4int fConfig;
};

inline size_t HyCalParameterisation::GetNumber()
{
    return moduleList.size();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
