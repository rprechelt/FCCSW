#include "TrackingGeoSvc.h"

#include "Acts/Geometry/TrackingGeometry.hpp"
#include "Acts/Plugins/DD4hep/ConvertDD4hepDetector.hpp"

DECLARE_COMPONENT(TrackingGeoSvc)

TrackingGeoSvc::TrackingGeoSvc(const std::string& name, ISvcLocator* svc)
    : base_class(name, svc), m_trackingGeo(nullptr),
    m_geoSvc("GeoSvc", "TrackingGeoSvc") {
      declareProperty("GeoSvc", m_geoSvc);
      }


StatusCode TrackingGeoSvc::initialize() {
  if (Service::initialize().isFailure()) {
    error() << "Unable to initialize Service()" << endmsg;
    return StatusCode::FAILURE;
  }
  Acts::Logging::Level geoMsgLevel;
  switch (msgLevel()) {
  case (MSG::DEBUG):
    geoMsgLevel = Acts::Logging::DEBUG;
    break;
  case (MSG::VERBOSE):
    geoMsgLevel = Acts::Logging::VERBOSE;
    break;
  case (MSG::INFO):
    geoMsgLevel = Acts::Logging::INFO;
    break;
  case (MSG::WARNING):
    geoMsgLevel = Acts::Logging::WARNING;
    break;
  case (MSG::FATAL):
    geoMsgLevel = Acts::Logging::FATAL;
    break;
  case (MSG::ERROR):
    geoMsgLevel = Acts::Logging::ERROR;
    break;
  default:
    geoMsgLevel = Acts::Logging::VERBOSE;
  }
  m_trackingGeo = std::move(Acts::convertDD4hepDetector(m_geoSvc->getDD4HepGeo(), geoMsgLevel, Acts::equidistant,
                                                        Acts::equidistant, Acts::equidistant));
  return StatusCode::SUCCESS;
}

StatusCode TrackingGeoSvc::finalize() { return StatusCode::SUCCESS; }
