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
{std::cout <<"Construct :"<<std::endl;}

RPCReadOutMapPrint::RPCReadOutMapPrint(int i) 
{std::cout <<"Construct :"<<i<<std::endl;}

RPCReadOutMapPrint::~RPCReadOutMapPrint() 
{std::cout <<"DeConstruct :"<<std::endl;}

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
    const RPCReadOutMapping* _m=rpcmap.product();
    for (RPCReadOutMapping::const_iterator i=_m->begin(); i<_m->end();
	 i++){
      std::cout<<"dcc="<<i->dccId<<" rmb="<<i->tbId<<" lbox="<<i->lboxId
	       <<" mb="<<i->mbId<<" lboard="<<i->lboardId
	       <<" channel="<<i->channelId<<"\n----->\n"
	       <<"region="<<i->regionId<<" disk="<<i->diskId
	       <<" station="<<i->stationId<<" sector="<<i->sectorId
	       <<" layer="<<i->layerId<<" subsector"<<i->subsectorId
	       <<" roll="<<i->rollId<<" strip="<<i->stripId
	       <<"\n=============================================\n"
	       <<std::endl;
    }
    
}
DEFINE_FWK_MODULE(RPCReadOutMapPrint)
