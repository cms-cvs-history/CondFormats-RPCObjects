
/*----------------------------------------------------------------------

Toy EDProducers and EDProducts for testing purposes only.

----------------------------------------------------------------------*/

#include <stdexcept>
#include <string>
#include <iostream>
#include <map>
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "CondFormats/RPCObjects/test/stubs/RPCReadOutMapPrint.h"
#include "CondFormats/RPCObjects/interface/RPCReadOutMapping.h"
#include "CondFormats/DataRecord/interface/RPCReadOutMappingRcd.h"


RPCReadOutMapPrint::RPCReadOutMapPrint(edm::ParameterSet const& p) 
{}

RPCReadOutMapPrint::RPCReadOutMapPrint(int i) 
{}

RPCReadOutMapPrint::~RPCReadOutMapPrint() 
{}

void 
RPCReadOutMapPrint::analyze(const edm::Event& e,

			    const edm::EventSetup& context) 
{
  //  using namespace edm::eventsetup;

  std::cout <<"Run Number ="<<e.id().run();
    std::cout <<" Event Number= "<<e.id().event() <<std::endl;

    edm::ESHandle<RPCReadOutMapping> rpcmap;
    context.get<RPCReadOutMappingRcd>().get(rpcmap);

    std::cout << std::distance( rpcmap->begin(), rpcmap->end() ) 
	      << " connections in the map" << std::endl;
}
DEFINE_FWK_MODULE(RPCReadOutMapPrint)
