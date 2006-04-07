#include "CondCore/DBCommon/interface/DBWriter.h"
#include "CondCore/DBCommon/interface/DBSession.h"
#include "CondCore/DBCommon/interface/Exception.h"
#include "CondCore/DBCommon/interface/ServiceLoader.h"
#include "CondCore/DBCommon/interface/ConnectMode.h"
#include "CondCore/DBCommon/interface/MessageLevel.h"
#include "CondCore/IOVService/interface/IOV.h"
#include "CondCore/MetaDataService/interface/MetaData.h"
#include "FWCore/Framework/interface/IOVSyncValue.h"

#include "CondFormats/RPCObjects/interface/RPCReadOutMapping.h"

#include <string>
#include <map>
#include <iostream>
int main(){
  cond::ServiceLoader* loader=new cond::ServiceLoader;
  ::putenv("CORAL_AUTH_USER=maggim");
  ::putenv("CORAL_AUTH_PASSWORD=maggim");
  loader->loadAuthenticationService( cond::Env );
  loader->loadMessageService( cond::Error );
  try{
    cond::DBSession* session1=new cond::DBSession(std::string("sqlite_file:RPCReadOutMap.db"));
    session1->setCatalog("file:rpccatalog.xml");
    session1->connect(cond::ReadWriteCreate);
    cond::DBWriter rowriter(*session1, "ReadOutMap");
    cond::DBWriter iovwriter(*session1, "IOV");
    session1->startUpdateTransaction();
    cond::IOV* roiov=new cond::IOV;

    RPCReadOutMapping* rpcro=new RPCReadOutMapping();
    int dccId  = 10001;
    int tbId   =  2001;
    int lboxId =   301;
    int mbId   =    41;
    int lboard =     1;
    int regionId    = 0;
    int diskId      = 0;
    int stationId   = 2;
    int sectorId    = 9;
    int layerId     = 1;
    int subsectorId = 1;
    int rollId      = 1;
    
    for (int ichannel=1; ichannel <=10; ichannel++){
      int stripId = 10+ichannel;
      rpcro->insertReadOutGeometryLink(dccId,tbId,lboxId,mbId,lboard,
				       ichannel,regionId,diskId,
				       stationId,sectorId,layerId,
				       subsectorId,rollId,stripId);
      std::string mytok=rowriter.markWrite<RPCReadOutMapping>(rpcro);
      if(ichannel<=5){
	roiov->iov.insert(std::make_pair(100+ichannel,mytok)); 
      }else{
	roiov->iov.insert(std::make_pair(200+ichannel,mytok));
      }
    }

    std::string roiovToken=iovwriter.markWrite<cond::IOV>(roiov);  
    session1->commit();//commit all in one
    session1->disconnect();
    delete session1;
    cond::MetaData metadata_svc("sqlite_file:RPCReadOutMap.db",*loader);
    metadata_svc.connect();
    metadata_svc.addMapping("rpcrotest", roiovToken);
    metadata_svc.disconnect();
  }catch(const cond::Exception& er){
    std::cout<<er.what()<<std::endl;
  }catch(...){
    std::cout<<"Unforeseen error"<<std::endl;
  }
  delete loader;
}
