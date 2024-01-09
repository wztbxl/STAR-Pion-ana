#include "TChain.h"
#include "TSystem.h"
#include "TFile.h"
#include <iostream>

class StMuDstMaker;
StMuDstMaker* maker;

//void RunFmsJetAna_stfms(Int_t ibegin = 1, Int_t iend = 1000, const char* file = "fms7.list", const char* outfile = "stfmsAnal_run12098008.root", const char* qafile = "stfmsQAhisto_run12098008", Bool_t qa = false , const char* jetfile = "jet.root" ,const char*  skimfile="skim.root" ){
void RunFmsJetAna_stfms(Int_t ibegin = 1, Int_t iend = 15, const char* file = "fms7.list", const char* outfile = "stfmsAnal1.root", const char* qafile = "stfmsQAhisto_run12098008", int period =3 ){

//	gROOT->Macro("load.C");
	gROOT->Macro("loadMuDst.C");
//	gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
//	loadSharedLibraries();
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
		StMuDstMaker* muDstMaker = new StMuDstMaker(0,0,"",file,".",10000000,"MuDst");
	//	StMuDbReader* muDB = StMuDbReader::instance();
	//	gMessMgr->SwitchOff("D");
	//	gMessMgr->SwitchOff("I");	

	// Trigger filter
	StTriggerFilterMaker* filterMaker = new StTriggerFilterMaker;
	//filterMaker->addTrigger(89);//FMS*BEMC*JP0
	filterMaker->printTriggerId(1); 
	filterMaker->addTrigger(480809); //   FMSJP1
	filterMaker->addTrigger(480808); //   FMSJP2
	filterMaker->addTrigger(480805); //   FMSLgBS2
	filterMaker->addTrigger(480806); //   FMSLgBS3
	filterMaker->addTrigger(480802); //   FMSSmBS2
	filterMaker->addTrigger(480803); //   FMSSmBS3

	filterMaker->addTrigger(480801); //   FMSSmBS1
	filterMaker->addTrigger(480821); //   FMSSmBS1
	filterMaker->addTrigger(480841); //   FMSSmBS1
	filterMaker->addTrigger(480822); //   FMSSmBS2
	filterMaker->addTrigger(480843); //   FMSSmBS3
	filterMaker->addTrigger(480823); //   FMSSmBS3
	filterMaker->addTrigger(480804); //   FMSLgBS1
	filterMaker->addTrigger(480824); //   FMSLgBS1
	filterMaker->addTrigger(480844); //   FMSLgBS1
	filterMaker->addTrigger(480825); //   FMSLGBS2
	filterMaker->addTrigger(480826); //   FMSLgBS3
	filterMaker->addTrigger(480830); //   FMSJP0
	filterMaker->addTrigger(480828); //   FMSJP2
	filterMaker->addTrigger(480829); //   FMSJP1
	St_db_Maker *dbMk = new St_db_Maker("db","MySQL:StarDb","$STAR/StarDb");
/*
      dbMk->SetAttr("blacklist", "tpc");
      dbMk->SetAttr("blacklist", "svt");
      dbMk->SetAttr("blacklist", "ssd");
      dbMk->SetAttr("blacklist", "ist");
      dbMk->SetAttr("blacklist", "pxl");
      dbMk->SetAttr("blacklist", "pp2pp");
      dbMk->SetAttr("blacklist", "ftpc");
      dbMk->SetAttr("blacklist", "emc");
      dbMk->SetAttr("blacklist", "eemc");
      dbMk->SetAttr("blacklist", "mtd");
      dbMk->SetAttr("blacklist", "pmd");
      dbMk->SetAttr("blacklist", "tof");
      dbMk->SetFlavor("ofl");
*/

	StSpinDbMaker *spDb=new StSpinDbMaker("spinDb"); 
//	dbMk->SetDEBUG(0);
	//	dbMk->SetDateTime(20110601, 0);

	StFmsDbMaker* fmsdb = new StFmsDbMaker("fmsDb");
//	  fmsdb->readGainFromText(0);
	  fmsdb->readGainCorrFromText(1);
//	  fmsdb->forceUniformGainCorrection(0.0);
//	  fmsdb->setDebug(1);


	// Endcap database
	StEEmcDbMaker* eemcDb = new StEEmcDbMaker;
	// Barrel ADC to energy maker
	StEmcADCtoEMaker* adc = new StEmcADCtoEMaker;
	adc->saveAllStEvent(true);

	StFmsHitMaker* fmshitMk = new StFmsHitMaker();
//	fmshitMk->SetDEBUG();
//	fmshitMk->mLocalMap = true;
//	fmshitMk->RunDepBaseOverride = 12090002;

		fmshitMk->SetTimeDepCorr(0);
	    fmshitMk->SetReadMuDst(0);
//	    fmshitMk->SetCorrectAdcOffByOne(0);

	StFmsPointMaker* fmsptMk = new StFmsPointMaker();
//	fmsptMk->ReadBbcSlewing("./bbc.dat") ;
	 fmsptMk->setTry1PhotonFit();
     fmsptMk->setScaleShowerShape();


//	if(qa){
//		StFmsQAHistoMaker* fmsQa = new StFmsQAHistoMaker();
//		fmsQa->SetOutputFile(qafile);
//		fmsQa->SetFmsQA(false);
//		fmsQa->SetTrackQA(false);
//		fmsQa->SetEmcEt(0.2);
//	}
//
	cout<<"point done"<<endl;
//  StJetSkimEventMaker* skimEventMaker = new StJetSkimEventMaker("StJetSkimEventMaker",muDstMaker,skimfile);
	StJetMaker2012* jetmaker = new StJetMaker2012;


//	jetmaker->setJetFile(jetfile);

	// Jet maker
//	StJetMaker2009* jetmaker = new StJetMaker2009;
	Float_t jetPtMin = 1.5;
//	jetmaker->setJetFile(jetfile);

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
  anapars12->addTpcCut(new StjTrackCutFlag(0));
  anapars12->addTpcCut(new StjTrackCutNHits(12));
  anapars12->addTpcCut(new StjTrackCutPossibleHitRatio(0.51));
  anapars12->addTpcCut(new StjTrackCutDca(3));
  anapars12->addTpcCut(new StjTrackCutDcaPtDependent);
  anapars12->addTpcCut(new StjTrackCutTdcaPtDependent);
  anapars12->addTpcCut(new StjTrackCutChi2(0,4));
  anapars12->addTpcCut(new StjTrackCutPt(0.2,200));
  anapars12->addTpcCut(new StjTrackCutEta(-2.5,2.5));
  anapars12->addTpcCut(new StjTrackCutLastPoint(125));

  anapars12->addJetCut(new StProtoJetCutPt(.01,200));
  anapars12->addJetCut(new StProtoJetCutEta(2.1,5));

	
	jetmaker->addBranch("AntiKtR070FMS",anapars12,AntiKtR070Pars);
//	jetmaker->addBranch("AntiKtR060status",anapars13,AntiKtR060Pars);
//	jetmaker->addBranch("AntiKtR070EMC",anaparsEMC,AntiKtR070Pars);
//	jetmaker->addBranch("AntiKtR050EMC",anaparsEMC,AntiKtR050Pars);
//	jetmaker->addBranch("AntiKtR050FMS",anaparsEMC,AntiKtR050Pars);
	
    StOffAxisConesPars *off070 = new StOffAxisConesPars(0.7);
    jetmaker->addUeBranch("OffAxisConesR050", off070);
	int PP=period;
	StFmsAnalysisMaker* fms = new StFmsAnalysisMaker("StFmsAnalysisMaker",jetmaker,PP);
	fms->EnableEdepCor = false;
	fms->ReadBbcSlewing("bbc.dat") ;
	fms->SetOutputFile(outfile);

cout<<" start chain    "<<endl;
	chain->Init();
	chain->EventLoop(ibegin,iend);
	chain->Finish();
	delete chain;

}

