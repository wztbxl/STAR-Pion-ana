// EDP is for anchor point 15GeV; 20190315




// $Id: StFmsPointMaker.cxx,v 1.1 2020/08/01 23:58:26 zwzhu Exp $
//
// $Log: StFmsPointMaker.cxx,v $
// Revision 1.1  2020/08/01 23:58:26  zwzhu
// *** empty log message ***
//
// Revision 1.12  2018/01/04 17:35:44  smirnovd
// [Cosmetic] Remove StRoot/ from include path
//
// $STAR/StRoot is already in the default path search
//
// Revision 1.11  2016/11/22 18:24:34  akio
// Using StFmsDbMaker::getLorentzVector for correct momentum calcuration based on beamline angles/offsets
//
// Revision 1.10  2016/06/07 15:51:43  akio
// Making code better based on Coverity reports
//
// Revision 1.9  2015/11/05 17:53:09  akio
// Adding setScaleShowerShape() option for scaling up shower shape function for large cell
//
// Revision 1.8  2015/11/04 21:57:43  akio
// fixing overwrting detectorId for some StFmsPoint near large/small gap when
// top cell in the cluster and the photon are in different detector
//
// Revision 1.7  2015/11/02 22:40:04  akio
// adding option for new cluster categorization
//
// Revision 1.6  2015/10/30 21:23:04  akio
// *** empty log message ***
//
// Revision 1.5  2015/10/29 21:17:41  akio
// Fix small scale differebce for small cells when converting coordinates while mMergeSmallToLarge is on
// Cleaning up debug prints
//
// Revision 1.4  2015/10/21 15:49:12  akio
// Adding 3 options to control how reconstruction works:
//   setGlobalRefit(int v=1)
//   setMergeSmallToLarge(int v=1)
//   setTry1PhotonFit(int v=1)
//
// Revision 1.3  2015/09/18 18:46:47  akio
// Move energy sum check for killing LED tail event to whole FMS, not each module
// Also make it not dependent on beam energy, so that it runs on simulation as well.
//
// Revision 1.2  2015/09/02 14:52:15  akio
// Adding readMuDst() to give options when reading back from mudst
//
/**
 \file      StFmsPointMaker.cxx
 \brief     Implementation of StFmsPointMaker, the FMS cluster/photon maker
 \author    Yuxi Pan <yuxipan@physics.ucla.edu>
 \author    Thomas Burton <tpb@bnl.gov>
 \date      2014
 */
#include "StFmsPointMaker.h"

#include "StLorentzVectorF.hh"
#include <TProcessID.h>

#include "StMessMgr.h"
#include "StEventTypes.h"
#include "StMuDSTMaker/COMMON/StMuTypes.hh"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuEmcCollection.h"
#include "StMuDSTMaker/COMMON/StMuEmcUtil.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuPrimaryVertex.h"
#include "StMuDSTMaker/COMMON/StMuTriggerIdCollection.h"


#include "StMessMgr.h"
#include "StEvent.h"
#include "StEnumerations.h"
#include "StFmsCluster.h"
#include "StFmsCollection.h"
#include "StFmsHit.h"
#include "StFmsPoint.h"
#include "StRunInfo.h"
#include "StFmsDbMaker/StFmsDbMaker.h"

#include "StFmsUtil/StFmsEventClusterer.h"
#include "StFmsUtil/StFmsFittedPhoton.h"
#include "StFmsUtil/StFmsTower.h"
#include "StFmsUtil/StFmsTowerCluster.h"
#include "StFmsUtil/StFmsConstant.h"

namespace {
  // Calculate a 4 momentum from a direction/momentum vector and energy
  // assuming zero mass i.e. E = p
    StLorentzVectorF compute4Momentum(const StThreeVectorF& xyz, Float_t energy) {
	StThreeVectorF mom3 = xyz.unit() * energy;  // Momentum vector with m = 0
	return StLorentzVectorF(mom3, energy);
    }
}  // unnamed namespace

StFmsPointMaker::StFmsPointMaker(const char* name)
    : StMaker(name), mFmsDbMaker(0), mFmsCollection(0), mObjectCount(0),
      mMaxEnergySum(255.0), mReadMuDst(0), 
      mGlobalRefit(0), mMergeSmallToLarge(0), mTry1PhotonFitWhen2PhotonFitFailed(0), 
      mCategorizationAlgo(0), mScaleShowerShape(0) , 
      mVertexZ(1) , mShowerShapeWithAngle(2)   { 
		  
		  
		  
		    for( int ew=0; ew<2; ew++ ){
				  for( int p=0; p<16; p++ ){
				     for( int c=0; c<3; c++ ) {
				         mBbcSlew[ew][p][c] = 0.0;
				        }}}
      EDepCorrection1=new TF1("EDepCorrection1","1.17731+ 0.9331*x -0.000783*x*x",0,120); //FMS energy dependent correction
      EDepCorrection2=new TF1("EDepCorrection2","0.909 + 0.963*x -0.001576*x*x",0,120); //FMS energy dependent correction

	}

StFmsPointMaker::~StFmsPointMaker() { }

Int_t StFmsPointMaker::InitRun(Int_t runNumber) {
  // Ensure we can access database information
  LOG_DEBUG << "StFmsPointMaker initializing run" << endm;
  mFmsDbMaker = static_cast<StFmsDbMaker*>(GetMaker("fmsDb"));
  if (!mFmsDbMaker) {
    LOG_ERROR << "StFmsPointMaker initializing failed due to no StFmsDbMaker" << endm;
    return kStErr;
  }
  /*
  // Set up geometry, which stays constant for each run
  if (!mGeometry.initialize(mFmsDbMaker)) {
    // Return an error if geometry initialization fails
    return kStErr;
  }  // if
  */


  return StMaker::InitRun(runNumber);
}

Int_t StFmsPointMaker::Make() {
  // Cache the current count of referenced objects, as discussed here
  // http://root.cern.ch/root/htmldoc/TRef.html
  /** \note Object count caching should probably be done in e.g. StMuDstMaker
      however we do it in StFmsPointMaker for now until we can verify changes
      with the MuDST coordinator. It should work OK as I don't think any other
      STAR makers use TRef. */
  LOG_DEBUG << "StFmsPointMaker making" << endm;
  if(mReadMuDst) return readMuDst();

  muDst = (StMuDst*)GetInputDS("MuDst");
   if(!muDst){LOG_INFO<<"StFmsPointMaker::readMuDst found no StEvent"<<endm; return kStErr;}
  // get vertex Z from BBCTime
  unsigned short bbcTimeBin = muDst->event()->bbcTriggerDetector().onlineTimeDifference();
  vertexz = 0 ;
	//Run15
	/*
      UShort_t tdc1east, tdc1west;
      UShort_t pmt1east, pmt1west;
      UShort_t adc1east, adc1west;
    unsigned int tdcMatchEast = 0;
    unsigned int tdcMatchWest = 0;

    float   bbcTdiff = 0;
        bbcTdiff = (float)muDst->event()->bbcTriggerDetector().onlineTimeDifference();
       tdc1east = muDst->event()->triggerData()->bbcEarliestTDC(east);
       tdc1west = muDst->event()->triggerData()->bbcEarliestTDC(west);

    for( int i=1; i<=16; i++ ) { 
      if( tdc1east==muDst->event()->triggerData()->bbcTDC(east, i) ) { 
        adc1east = muDst->event()->triggerData()->bbcADC(east, i); 
        pmt1east = i-1;
        ++tdcMatchEast;
      }   
      if( tdc1west==muDst->event()->triggerData()->bbcTDC(west, i) ) { 
        adc1west = muDst->event()->triggerData()->bbcADC(west, i); 
        pmt1west = i-1;
        ++tdcMatchWest;
      }   
    }   

    if( tdcMatchEast==1 && tdcMatchWest==1 ) { // BBC slewing correction (east/west)
      Float_t zEast = -0.3*( bbcTdiff - mBbcSlew[0][pmt1east][0] - mBbcSlew[0][pmt1east][1]/(mBbcSlew[0][pmt1east][2] + adc1east) );
      Float_t zWest = -0.3*( bbcTdiff - mBbcSlew[1][pmt1west][0] - mBbcSlew[1][pmt1west][1]/(mBbcSlew[1][pmt1west][2] + adc1west) );
      vertexz = (zEast + zWest)/2.0;
	 // 	cout<<"BBCin POint"<<endl;
    } else {
      vertexz = -30.0;
    }   
	
*/

if (bbcTimeBin!=0)  vertexz =  633.544 - 0.158*bbcTimeBin;
	else vertexz = -36;
  if (mVertexZ==0)    vertexz =  0;


  mObjectCount = TProcessID::GetObjectCount();
  if (!populateTowerLists()) { //this also assigns mFmsCollection
      return kStOK; //return ok even if energy sum exceed max
      //LOG_ERROR << "StFmsPointMaker::Make() - failed to initialise tower " <<
      //  "lists for the event" << endm;
      //return kStErr;
  }  // if
  clusterEvent();
  return StMaker::Make();
}

void StFmsPointMaker::Clear(Option_t* option) {
  mTowers.clear();
  // Reset the count of referenced objects to the value before the previous
  // call to Make(), in order prevent ever-growing table of objects
  TProcessID::SetObjectCount(mObjectCount);
  StMaker::Clear(option);
}

StFmsCollection* StFmsPointMaker::getFmsCollection() {
  StEvent* event = static_cast<StEvent*>(GetInputDS("StEvent"));
  StFmsCollection* fms = nullptr;
  if (event) {
    fms = event->fmsCollection();
  }  // if
  if (!fms) {
    LOG_ERROR << "StFmsPointMaker did not find "
              << "an StFmsCollection in StEvent" << endm;
  }  // if
  return fms;
}

int StFmsPointMaker::clusterEvent() {
  if (!mFmsCollection) {
    return kStErr;
  }  // if
  for (auto i = mTowers.begin(); i != mTowers.end(); ++i) {
    /* Removing LED tail was moved to populateTowerList()      
    if (!validateTowerEnergySum(i->second)) {
      continue;  // To remove LED trails
    }  // if
    */
    clusterDetector(&i->second, i->first);
  }  // for
  mFmsCollection->setMergeSmallToLarge(mMergeSmallToLarge);
  mFmsCollection->setGlobalRefit(mGlobalRefit);
  mFmsCollection->setTry1PhotonFit(mTry1PhotonFitWhen2PhotonFitFailed);
  mFmsCollection->setNewClusterCategorization(mCategorizationAlgo);
  mFmsCollection->setScaleShowerShape(mScaleShowerShape);
  mFmsCollection->sortPointsByEnergy();    
  LOG_INFO << Form("Found %d Clusters and %d Points",mFmsCollection->numberOfClusters(),mFmsCollection->numberOfPoints()) << endm;
  return kStOk;
}

/* Perform photon reconstruction on a single sub-detector */
int StFmsPointMaker::clusterDetector(TowerList* towers, const int detectorId) {
  //  FMSCluster::StFmsEventClusterer clustering(&mGeometry,detectorId);
  FMSCluster::StFmsEventClusterer clustering(mFmsDbMaker,detectorId,mGlobalRefit,mMergeSmallToLarge,
					     mTry1PhotonFitWhen2PhotonFitFailed,mCategorizationAlgo,
					     mScaleShowerShape,mShowerShapeWithAngle,vertexz);
  // Perform tower clustering, skip this subdetector if an error occurs
  if (!clustering.cluster(towers)) {  // Cluster tower list      
      //LOG_INFO << Form("clusterDetector found no cluster for det=%d ",detectorId)<<endm;
      return kStOk; // this happens if detector just had too low energy
  }  // if
  // Saved cluster info into StFmsCluster
  auto& clusters = clustering.clusters();
  for (auto cluster = clusters.begin(); cluster != clusters.end(); ++cluster) {
    processTowerCluster(cluster->get(), detectorId);
  }  // for
  LOG_DEBUG << Form("Found %d clusters for det=%d",clusters.size(),detectorId)<<endm;
  return kStOk;
}

/* Moving this to populateTowerLists()
bool StFmsPointMaker::validateTowerEnergySum(const TowerList& towers) const {
    // remove acceing centerOfMassEnergy in StEvent, which can be
    // garbage for MC. BTW, shouldn't this be 1/2 of 510/200GeV?
    // Attempt to get center-of-mass energy from StRunInfo.
    // If it can't be accessed assume 500 GeV running.
    double centerOfMassEnergy(500.);
    const StEvent* event = static_cast<const StEvent*>(GetInputDS("StEvent"));
    if (event) {
    if (event->runInfo()) {
    centerOfMassEnergy = event->runInfo()->centerOfMassEnergy();
    }  // if
    }  // if

    // Sum tower energies and test validity of the sum
    double Esum = 0.f;
    typedef TowerList::const_iterator TowerIter;
    for (TowerIter i = towers.begin(); i != towers.end(); ++i) {
	Esum += i->hit()->energy();
    }  // for
    LOG_DEBUG << Form("Esum=%f Max=%f",Esum,mMaxEnergySum) <<endm;
    return Esum >= 0.f && Esum <= mMaxEnergySum;
}
*/

bool StFmsPointMaker::processTowerCluster(
    FMSCluster::StFmsTowerCluster* towerCluster,
    const int detectorId) {
  // Update the StFmsCluster object we want to store in StEvent with information
  // not automatically propagated via StFmsTowerCluster
  StFmsCluster* cluster = towerCluster->cluster();
  // Skip clusters that don't have physically sensible coordinates
  if (!(cluster->x() > 0. && cluster->y() > 0.)) {
      LOG_INFO << "Found cluster x or y is zero, not processing this cluster" << endm;
      return false;
  }  // if
  int det=detectorId;
  float x=cluster->x();
  float y=cluster->y();
  if(mMergeSmallToLarge>0){
      if(x<8.0 && y>9.0 && y<25.0){ // Central hole, those are small cell merged to large
	  det=detectorId+2;         //put back to small cell coordinate
	  cluster->setX(x*1.5);  //ZZW 1.52?
	  cluster->setY((y-9.0)*1.5);
      }
  }
  cluster->setDetectorId(det);
  // Cluster id is id of the 1st photon, not necessarily the highest-E photon
  //cluster->setId(CLUSTER_BASE + CLUSTER_ID_FACTOR_DET * det + mFmsCollection->numberOfPoints());
  cluster->setId(200*(det-kFmsNorthLargeDetId) + mFmsCollection->numberOfPoints());
  // Cluster locations are in column-row grid coordinates so convert to cm and get STAR xyz
  StThreeVectorF xyz = mFmsDbMaker->getStarXYZfromColumnRow(det,cluster->x(),cluster->y());
  //cluster->setFourMomentum(compute4Momentum(xyz, cluster->energy()));
  cluster->setFourMomentum(mFmsDbMaker->getLorentzVector(xyz,cluster->energy()));
  // Save photons reconstructed from this cluster
  
//  if(vertexz>0) cout<<"------------------vertexz="<<vertexz<<"  D=   "<< xyz.z() - vertexz<<endl;
  if( mShowerShapeWithAngle==1 )   xyz.setZ ( 735.45   - vertexz );
  if( mShowerShapeWithAngle==0 )   xyz.setZ ( xyz.z()  - vertexz );

  for (UInt_t np = 0; np < towerCluster->photons().size(); np++) {
      StFmsPoint* point = makeFmsPoint(towerCluster->photons()[np], detectorId);
      //      point->setId(CLUSTER_BASE + CLUSTER_ID_FACTOR_DET * det + mFmsCollection->numberOfPoints());
      point->setId(200*(det-kFmsNorthLargeDetId) + mFmsCollection->numberOfPoints());
      point->setParentClusterId(cluster->id());
      point->setNParentClusterPhotons(towerCluster->photons().size());
      point->setCluster(cluster);
      // Add it to both the StFmsCollection and StFmsCluster
      // StFmsCollection owns the pointer, the cluster merely references it
      mFmsCollection->points().push_back(point);
      cluster->points().push_back(point);
  }  // for
  // Save the tower hit info.
  auto& towers = towerCluster->towers();
  for (auto i = towers.begin(); i != towers.end(); ++i) {
    if ((*i)->hit()->adc() >= 1) {  // Min ADC = 1
      cluster->hits().push_back((*i)->hit());
    }  // if
  }  // for
  // Release StFmsCluster held by towerCluster to pass ownership to
  // StFmsCollection (and hence StEvent).
  mFmsCollection->addCluster(towerCluster->release());
  return true;
}

StFmsPoint* StFmsPointMaker::makeFmsPoint(
    const FMSCluster::StFmsFittedPhoton& photon, const int detectorId) {
  StFmsPoint* point = new StFmsPoint;
  float x=photon.x; //photon xy is in detector local coordinate in [cm]
  float y=photon.y;
  int det=detectorId;
      float lwx=mFmsDbMaker->getXWidth(kFmsNorthLargeDetId);//take large cell width since all merged to large cell
      float lwy=mFmsDbMaker->getYWidth(kFmsNorthLargeDetId);
      float wx=mFmsDbMaker->getXWidth(kFmsNorthSmallDetId);
      float wy=mFmsDbMaker->getYWidth(kFmsNorthSmallDetId);
  if(mMergeSmallToLarge>0){
      if(x<8.0*lwx && y>9.0*lwy && y<25.0*lwy){ // Central hole, those are small cell merged to large
	  x = x/lwx*1.5*wx; //ZZW x=x
	  y = (y/lwy - 9.0)*1.5*wy;  
	  det+=2;
      }
  }
//  point->setEnergy(photon.energy);
 point->setEnergy(EDep(photon.energy,det));
  point->setDetectorId(det);
  //if(x<8.0*lwx && y>9.0*lwy && y<25.0*lwy)  //small cell
  //	{ x=x/wx-floor(x/wx);     y=y/wy-floor(y/wy); }
  // x=x/lwx-floor(x/lwx); y=y/lwy-floor(y/lwy); 
  point->setX(x);    //Akio propose to keep fitted local X here
  point->setY(y);    //Akio propose to keep fitted local Y here
  // Calculate photon 4 momentum
  // StFmsFittedPhoton position is in detector-local (x, y) [cm] coordinates
  // Convert to global STAR coordinates for StFmsPoint  
  StThreeVectorF xyz = mFmsDbMaker->getStarXYZ(det,x,y);
  if( mShowerShapeWithAngle==1 )   xyz.setZ ( 735.45   - vertexz );
  if( mShowerShapeWithAngle==0 )   xyz.setZ ( xyz.z()  - vertexz );

  point->setXYZ(xyz);  //This is in STAR global coordinate
  point->setFourMomentum(mFmsDbMaker->getLorentzVector(xyz,point->energy()));

//  point->setRX1(x);
//  point->setRX2(y);

  return point;
}

bool StFmsPointMaker::populateTowerLists() {
  mFmsCollection = getFmsCollection();
  if (!mFmsCollection) {
      LOG_ERROR << "mFmsCollection is null" << endm;
      return false;
  }  // if
  auto& hits = mFmsCollection->hits();
  LOG_DEBUG << "Found nhits = " << hits.size() << endm;
  float sumE[5]={0.0,0.0,0.0,0.0,0.0};
  int n=0;
  for (auto i = hits.begin(); i != hits.end(); ++i) {
    StFmsHit* hit = *i;
    int detector = hit->detectorId();
    const int row = mFmsDbMaker->getRowNumber(detector, hit->channel());
    const int column = mFmsDbMaker->getColumnNumber(detector, hit->channel());
    if (!isValidChannel(detector, row, column)) {
      continue;
    }  // if
    if(mMergeSmallToLarge>0){
	if(detector==kFmsNorthSmallDetId) detector=kFmsNorthLargeDetId;
	if(detector==kFmsSouthSmallDetId) detector=kFmsSouthLargeDetId;
    }
    if (hit->adc() > 0) {
      sumE[0]+=hit->energy();
      sumE[detector-kFmsNorthLargeDetId+1]+=hit->energy();
      // Insert a tower list for this detector ID if there isn't one already
      // This method is faster than using find() followed by insert()
      // http://stackoverflow.com/questions/97050/stdmap-insert-or-stdmap-find
      auto low = mTowers.lower_bound(detector);
      if (low == mTowers.end() || mTowers.key_comp()(detector, low->first)) {
        mTowers.insert(TowerMap::value_type(detector, TowerList()));
      }  // if
      FMSCluster::StFmsTower tower(hit);
      // Ensure tower information is valid before adding
      if (tower.initialize(mFmsDbMaker)) {
        mTowers[detector].push_back(tower);
      }  // if
      n++;
    }  // if
  }  // for
 // LOG_INFO << Form("NHit=%d NValidHit=%d Esum=%f (%f %f %f %f) Max=%f",hits.size(),n,sumE[0],sumE[1],sumE[2],sumE[3],sumE[4],mMaxEnergySum) << endm;
  if(sumE[0]<=0.0 || sumE[0]>mMaxEnergySum) {
  //    LOG_INFO << Form("Energy sum=%f exceed MaxEnergySum=%f (LED tail?) or below zero. Skipping!",sumE[0],mMaxEnergySum)<< endm;
      return false;
  }
  return true;
}

/* Test channel validity by detector and row, column in the range [1, N] */
/* the constants are defined in StFmsUtil/StFmsConstant.h*/
bool StFmsPointMaker::isValidChannel(int detector, int row, int column) {
  //printf("detector=%d row=%d column=%d LS=%d\n",detector,row,column,mFmsDbMaker->largeSmall(detector));
  // Simplest check first, test lower bounds are valid
  if (row < ROW_LOW_LIMIT || column < COL_LOW_LIMIT) {
    return false;
  }  // if
  // Omit gaps in the detector
  switch (mFmsDbMaker->largeSmall(detector)) {
  case 0:
    //case FMSCluster::kFmsNorthLarge:  // Deliberate fall-through
    //case FMSCluster::kFmsSouthLarge:  // Large-cell FMS sub-detector
    if (fabs(row - CEN_ROW_LRG) < CEN_ROW_WIDTH_LRG && column < CEN_UPPER_COL_LRG) {  // Central hole
      return false;
    }  // if
    // This cuts off a 7x7 triangle from the corners
    if (fabs(CORNER_ROW - row) + column > CORNER_LOW_COL) {
      return false;
    }  // if
    break;
  case 1:
    //case FMSCluster::kFmsNorthSmall:  // Deliberate fall-through
    //case FMSCluster::kFmsSouthSmall:  // Small-cell FMS sub-detector
    if (fabs(row - CEN_ROW_SML) < CEN_ROW_WIDTH_SML && column < CEN_UPPER_COL_SML) {  // Central hole
      return false;
    }  // if
    break;
  default:  // Don't currently support non-FMS sub-detectors
    return false;
  } // switch (largesmall)
  
  // Test row and column number against the numbers stored in the database for
  // this detector. Leave this to last to avoid database calls when possible.
  // Also serves as a double-check on detector, as the database will
  // return -1 for both numbers in case of an invalid detector number.
  const int nRows = mFmsDbMaker->nRow(detector);
  if (nRows < 0 || row > nRows) {
    return false;
  }  // if
  const int nColumns = mFmsDbMaker->nColumn(detector);
  if (nColumns < 0 || column > nColumns) {
    return false;
  }  // if
  return true;
}

Int_t StFmsPointMaker::readMuDst(){
  StEvent* event = (StEvent*)GetInputDS("StEvent");
  if(!event){LOG_INFO<<"StFmsPointMaker::readMuDst found no StEvent"<<endm; return kStErr;}
  StFmsCollection* fmscol = event->fmsCollection();
  if(!fmscol){LOG_INFO<<"StFmsPointMaker::readMuDst found no FmsCollection"<<endm; return kStErr;}
  for (unsigned i(0); i < fmscol->numberOfClusters(); ++i) {
      StFmsCluster* c = fmscol->clusters()[i];
      if(c){
	  StThreeVectorF xyz = mFmsDbMaker->getStarXYZfromColumnRow(c->detectorId(),c->x(),c->y());
	  //c->setFourMomentum(compute4Momentum(xyz, c->energy()));
	  c->setFourMomentum(mFmsDbMaker->getLorentzVector(xyz,c->energy()));
      }
  }
  for (unsigned i(0); i < fmscol->numberOfPoints(); ++i) {
    StFmsPoint* p = fmscol->points()[i];
    if(p){
      StThreeVectorF xyz  = mFmsDbMaker->getStarXYZ(p->detectorId(),p->x(),p->y());
      p->setXYZ(xyz);
      //p->setFourMomentum(compute4Momentum(xyz, p->energy()));
      p->setFourMomentum(mFmsDbMaker->getLorentzVector(xyz,p->energy()));
    }
  }
  fmscol->sortPointsByET();
  return kStOk;
}

Double_t StFmsPointMaker::EDep(double energy, int id ){
 
 
     Int_t phid = id; 
     double nlgain = 1;
     double e0 = energy;
     if(id==8 || id==9){     //large cells
     nlgain = EDepCorrection1->Eval(e0)/e0;
     }   
     else if(id==10 || id==11){  //small cells
     nlgain = EDepCorrection2->Eval(e0)/e0;
     }   
     return energy*nlgain;
 }
Int_t StFmsPointMaker::ReadBbcSlewing(const char *filename_bbc)
{
  // reading parameters for BBC slewing correction
  char s[100]; int iew, ipmt; float ca, cb, cc; 
  FILE *pFile = fopen( filename_bbc, "read" );
  fgets( s, 100, pFile);

  for( int ew=0; ew<2; ew++ )
    for( int p=0; p<16; p++ ) { 
      fscanf( pFile, " %d %d %f %f %f \n", &iew, &ipmt, &ca, &cb, &cc);
      if( ew==iew && p+1==ipmt ) { 
        mBbcSlew[ew][p][0] = ca; 
        mBbcSlew[ew][p][1] = cb; 
        mBbcSlew[ew][p][2] = cc; 
      } else {
        return kError;
      }   
    }   
  fclose( pFile );
//  cout << " BBC slewing: z(A+B/[C+adc])" << endl;
  for( int ew=0; ew<2; ew++ ) { 
    if( ew==0 ) cout << " East" << endl;
    if( ew==1 ) cout << " West" << endl;
 for( int p=0; p<16; p++ ) { 
      cout << Form("PMT%2d - %7.2f %7.2f %7.2f ", p+1, mBbcSlew[ew][p][0], mBbcSlew[ew][p][1], mBbcSlew[ew][p][2]) << endl;
    }   
  }
  return kStOK;
}

