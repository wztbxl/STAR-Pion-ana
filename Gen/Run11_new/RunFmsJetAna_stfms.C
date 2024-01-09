#include "TChain.h"
#include "TSystem.h"
#include "TFile.h"
#include <iostream>

class StMuDstMaker;
StMuDstMaker* maker;

//void RunFmsJetAna_stfms(Int_t ibegin = 1, Int_t iend = 1000, const char* file = "fms7.list", const char* outfile = "stfmsAnal_run12098008.root", const char* qafile = "stfmsQAhisto_run12098008", Bool_t qa = false , const char* jetfile = "jet.root" ,const char*  skimfile="skim.root" ){
void RunFmsJetAna_stfms(Int_t ibegin = 1, Int_t iend = 40, const char* file = "fms7.list", const char* outfile = "test1.root", const char* qafile = "stfmsQAhisto_run12098008", Bool_t qa =false  ){
//
//	gROOT->Macro("load.C");
  gROOT->Macro("loadMuDst.C");
  gROOT->Macro("LoadLogger.C");

  gSystem->Load("StDetectorDbMaker");
  gSystem->Load("StTpcDb");
  gSystem->Load("StDbUtilities");
  gSystem->Load("StMcEvent");
  gSystem->Load("StMcEventMaker");
  gSystem->Load("StDaqLib");
  gSystem->Load("StEmcRawMaker");
  gSystem->Load("StEmcADCtoEMaker");
  gSystem->Load("StEmcSimulatorMaker");
  gSystem->Load("StDbBroker");
  gSystem->Load("St_db_Maker");
  gSystem->Load("StEEmcUtil");
  gSystem->Load("StEEmcDbMaker");
  gSystem->Load("StSpinDbMaker");
  gSystem->Load("StEmcTriggerMaker");
  gSystem->Load("StTriggerUtilities");
  gSystem->Load("StMCAsymMaker");
  gSystem->Load("StRandomSelector");
  gSystem->Load("libfastjet.so");
  gSystem->Load("libsiscone.so");
  gSystem->Load("libsiscone_spherical.so");
  gSystem->Load("libfastjetplugins.so");
 
  gSystem->Load("StJetFinder");
  gSystem->Load("StJetSkimEvent");
  gSystem->Load("StJets");
  gSystem->Load("StJetEvent");
  gSystem->Load("StUeEvent");
  gSystem->Load("StJetMaker");
  gSystem->Load("StTriggerFilterMaker");


	// Load your shared libraries here
	gSystem->Load("StFmsUtil");
	gSystem->Load("StFmsDbMaker");
	//gSystem->Load("StTriggerDataMaker");
//	gSystem->Load("StFmsJetMaker");
	gSystem->Load("libMinuit.so");

	gSystem->Load("StTriggerFilterMaker");
	gSystem->Load("StFmsHitMaker");
	gSystem->Load("StFmsPointMaker");
	gSystem->Load("StFmsAnalysisMaker");
//	gSystem->Load("StFmsQAHistoMaker");

std::cout<<"load done"<<endl;
	StChain* chain = new StChain("StChain");
	chain->SetDEBUG(0);
	StMuDstMaker* muDstMaker = new StMuDstMaker(0,0,"",file,".",1000000,"MuDst");
//	StMuDbReader* muDB = StMuDbReader::instance();
//	gMessMgr->SwitchOff("D");
//	gMessMgr->SwitchOff("I");	

	// Trigger filter
	StTriggerFilterMaker* filterMaker = new StTriggerFilterMaker;
	filterMaker->addTrigger(89);//FMS*BEMC*JP0
	filterMaker->addTrigger(320220); //   FMSJP1
	filterMaker->addTrigger(320231); //   FMSJP2
	filterMaker->addTrigger(320227); //   FMSLgBS2
	filterMaker->addTrigger(320226); //   FMSLgBS1
	filterMaker->addTrigger(320222); //   FMSSmBS1
	filterMaker->addTrigger(320223); //   FMSSmBS2
	St_db_Maker *dbMk = new St_db_Maker("db","MySQL:StarDb","$STAR/StarDb");
	StSpinDbMaker *spDb=new StSpinDbMaker("spinDb"); 
//	dbMk->SetDEBUG(0);
	//	dbMk->SetDateTime(20110601, 0);

	StFmsDbMaker* fmsdb = new StFmsDbMaker("fmsDb");
	  fmsdb->readGainFromText(1);
	  fmsdb->forceUniformGainCorrection(1.0);
//	  fmsdb->setDebug(1);
//	  fmsdb->dumpFmsGain("222.txt");
//	  fmsdb->dumpFmsGainCorrection("22.txt");


	// Endcap database
	StEEmcDbMaker* eemcDb = new StEEmcDbMaker;
	// Barrel ADC to energy maker
	StEmcADCtoEMaker* adc = new StEmcADCtoEMaker;
	adc->saveAllStEvent(true);

	StFmsHitMaker* fmshitMk = new StFmsHitMaker();
//	    fmshitMk->SetDEBUG();
	    fmshitMk->SetTimeDepCorr(1);		  //default 0
	    fmshitMk->SetReadMuDst(0);                //for simu set to 1
//	    fmshitMk->SetCorrectAdcOffByOne(0);           //default 1

	StFmsPointMaker* fmsptMk = new StFmsPointMaker();
//	fmsptMk->setMergeSmallToLarge();
//	fmsptMk->setCategorizationAlgo();

	fmsptMk->setTry1PhotonFit();
	fmsptMk->setScaleShowerShape();
	cout<<"point done"<<endl;

//      StJetSkimEventMaker* skimEventMaker = new StJetSkimEventMaker("StJetSkimEventMaker",muDstMaker,skimfile);
//	StFmsJetMaker* jetmaker = new StFmsJetMaker();
	StJetMaker2012* jetmaker = new StJetMaker2012;
//	jetmaker->setJetFile(jetfile);

	// Jet maker
	Float_t jetPtMin = 1.5;
StFastJetAreaPars *JetAreaPars = new StFastJetAreaPars;
	// Set anti-kt R=0.7 parameters
	StFastJetPars* AntiKtR070Pars = new StFastJetPars;
	AntiKtR070Pars->setJetAlgorithm(StFastJetPars::antikt_algorithm);
	AntiKtR070Pars->setRparam(0.7);
	AntiKtR070Pars->setRecombinationScheme(StFastJetPars::E_scheme);
	AntiKtR070Pars->setStrategy(StFastJetPars::Best);
	AntiKtR070Pars->setPtMin(jetPtMin);
	AntiKtR070Pars->setJetArea(JetAreaPars);
// new
  StAnaPars* anapars12 = new StAnaPars;
  anapars12->useTpc  = true;
  anapars12->useFms  = true;
  anapars12->useBemc = false;
  anapars12->useEemc = false;
/*  anapars12->addTpcCut(new StjTrackCutFlag(0));
  anapars12->addTpcCut(new StjTrackCutNHits(12));
  anapars12->addTpcCut(new StjTrackCutPossibleHitRatio(0.51));
  anapars12->addTpcCut(new StjTrackCutDca(3));
  anapars12->addTpcCut(new StjTrackCutDcaPtDependent);
  anapars12->addTpcCut(new StjTrackCutTdcaPtDependent);
  anapars12->addTpcCut(new StjTrackCutChi2(0,4));
  anapars12->addTpcCut(new StjTrackCutPt(0.2,200));
  anapars12->addTpcCut(new StjTrackCutEta(-2.5,0.5));
  anapars12->addTpcCut(new StjTrackCutLastPoint(125));


  anapars12->addBemcCut(new StjTowerEnergyCutBemcStatus(1));
  anapars12->addBemcCut(new StjTowerEnergyCutAdc(4,3)); // ADC-ped>4 AND ADC-ped>3*RMS
  anapars12->addBemcCut(new StjTowerEnergyCutEt(0.2));
  anapars12->addEemcCut(new StjTowerEnergyCutBemcStatus(1));
  anapars12->addEemcCut(new StjTowerEnergyCutAdc(4,3)); // ADC-ped>4 AND ADC-ped>3*RMS
  anapars12->addEemcCut(new StjTowerEnergyCutEt(0.2));
*/  anapars12->addJetCut(new StProtoJetCutPt(.01,200));
  anapars12->addJetCut(new StProtoJetCutEta(0,5));

// jetmaker->setJetFileUe("UE.root");
//	jetmaker->setJetFile("Jetfile.root");
	jetmaker->addBranch("AntiKtR070FMS",anapars12,AntiKtR070Pars);
    StOffAxisConesPars *off070 = new StOffAxisConesPars(0.7);
    jetmaker->addUeBranch("OffAxisConesR050", off070);
//	jetmaker->addBranch("AntiKtR060status",anapars13,AntiKtR060Pars);
//	jetmaker->addBranch("AntiKtR070EMC",anaparsEMC,AntiKtR070Pars);
//	jetmaker->addBranch("AntiKtR050EMC",anaparsEMC,AntiKtR050Pars);
//	jetmaker->addBranch("AntiKtR050FMS",anaparsEMC,AntiKtR050Pars);
	
	//move all this before jet finder 

	StFmsAnalysisMaker* fms = new StFmsAnalysisMaker("StFmsAnalysisMaker",jetmaker);
//	fms->EnableEdepCor = true;// have to do it here for jet finding;
	fms->SetOutputFile(outfile);

cout<<" start chain    "<<endl;
	chain->Init();
	chain->EventLoop(ibegin,iend);
	chain->Finish();
	delete chain;

}

