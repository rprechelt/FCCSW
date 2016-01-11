#ifndef SIMG4COMMON_GDMLDETECTORCONSTRUCTION_H
#define SIMG4COMMON_GDMLDETECTORCONSTRUCTION_H

// Geant
#include "G4VUserDetectorConstruction.hh"
#include "G4GDMLParser.hh"

// Gaudi
#include "GaudiKernel/ServiceHandle.h"
#include "GaudiKernel/IMessageSvc.h"
#include "GaudiKernel/MsgStream.h"

/** @class GdmlDetectorConstruction SimG4Common/SimG4Common/GdmlDetectorConstruction.h GdmlDetectorConstruction.h
 *
 *  Detector construction from the GDML file.
 *
 *  @author Anna Zaborowska
 */

namespace sim {
class GdmlDetectorConstruction: public G4VUserDetectorConstruction {
public:
  /**  Constructor.
   *   @param[in] aFileName Name of the GDML file with the detector description.
   */
  GdmlDetectorConstruction(const std::string& aFileName);
  virtual ~GdmlDetectorConstruction();
  /**  Create volumes using the GDML parser.
   *   @return World wolume.
   */
  virtual G4VPhysicalVolume* Construct() override;
  /**  Create sensitive detectors. User needs to provide own implementation and attach appropriate information
   *   to the GDML file (that will connect volume with a sensitive detector type).
   *   See Geant examples/extended/persistency/gdml/G04 for further details.
   */
  virtual void ConstructSDandField() override;
private:
  /// Message Service
  ServiceHandle<IMessageSvc> m_msgSvc;
  /// Message Stream
  MsgStream m_log;
  /// Parser of the GDML file
  G4GDMLParser m_parser;
  /// name of the GDML file
  std::string m_fileName;
};
}

#endif /* SIMG4COMMON_GDMLDETECTORCONSTRUCTION_H */
