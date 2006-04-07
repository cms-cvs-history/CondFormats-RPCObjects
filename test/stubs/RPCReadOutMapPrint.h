
/*----------------------------------------------------------------------

Toy EDProducers and EDProducts for testing purposes only.

----------------------------------------------------------------------*/

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


class RPCReadOutMapPrint : public edm::EDAnalyzer
{
 public:
  explicit  RPCReadOutMapPrint(edm::ParameterSet const& p);
  explicit  RPCReadOutMapPrint(int i) ;
  virtual ~ RPCReadOutMapPrint();
  virtual void analyze(const edm::Event& e, const edm::EventSetup& c);
};
