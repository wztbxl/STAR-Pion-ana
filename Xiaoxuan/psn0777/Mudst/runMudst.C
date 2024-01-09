/** Macro to test FMS code on MuDST input. */

class StMaker;
class StChain;
class StMudstMaker;

void runMudst(char* file="inFiles_fms_test_pp.list",
	      int ifile=-1, Int_t nevt=-1, char* outdir="hist", int opt=4, int readMuDst=0, int print=0){  
  gROOT->Macro("load.C");  // Load all required libraries
  //gSystem->Load("StEventMaker");
  //gSystem->Load("StMuDSTMaker");
  gSystem->Load("StFmsDiPi0");

  StChain* chain = new StChain("StChain"); chain->SetDEBUG(0);
  StMuDstMaker* muDstMaker = new StMuDstMaker(0, 0, "", file,".", 1000, "MuDst");
  //int n=10;
  int n=muDstMaker->tree()->GetEntries();
  printf("Found %d entries in Mudst\n",n);
  int start=0, stop=n;
  if(ifile>=0){
      int start=ifile*nevt;
      int stop=(ifile+1)*nevt-1;
      if(n<start) {printf(" No event left. Exiting\n"); return;}
      if(n<stop)  {printf(" Overwriting end event# stop=%d\n",n); stop=n;}
  }else if(nevt>=0 && nevt<n){
      stop=nevt;
  }else if(nevt==-2){
      stop=2000000000; 
  }
//test
stop = 10;
  printf("Doing Event=%d to %d\n",start,stop);

  int filter=1;
  if(filter){
      StTriggerFilterMaker* filterMaker = new StTriggerFilterMaker;
      filterMaker->printTriggerId();
      const int TIDBASE=480800;
      const int NBEAM=4;
      const int MAXVERSION=3;
      const int NTRG=11;  //123=FMS-sm-bs123,456=FMS-lg-bs123,7=FMS-DiBS,8910=FMS-JP012,11=FMS-DiJP,13=LED
      filterMaker->addTrigger(42);
      filterMaker->addTrigger(50);
      for(int k=0; k<NBEAM; k++){
	  for(int j=0; j<MAXVERSION; j++){
	      for(int i=1; i<=NTRG; i++){
		  int id=TIDBASE + 10000*k + 20*j + i; 
		  printf("Adding TriggerId=%d to the filter\n",id);
		  filterMaker->addTrigger(id);
	      }	      
	      int id=TIDBASE + 10000*k + 20*j + 13;  //Veto LED events 
	      printf("Adding TriggerId=%d to VETO\n",id);
	      filterMaker->addVetoTrigger(id);
	  }
      } 
      printf("Adding TriggerId=%d to VETO\n",54);
      filterMaker->addVetoTrigger(54);//LED before production id
  }
  
/*
 int filter=1;
  if(filter){
        StTriggerFilterMaker* filterMaker = new StTriggerFilterMaker;
        filterMaker->printTriggerId();
        filterMaker->addTrigger(480001);
        filterMaker->addTrigger(480007);
  }
*/
  St_db_Maker* dbMk = new St_db_Maker("db","MySQL:StarDb","$STAR/StarDb"); 
  //dbMk->SetDEBUG(2); //dbMk->SetDateTime(20150301,0);

  StFmsDbMaker* fmsdb = new StFmsDbMaker("fmsDb");  
  //fmsdb->setDebug(1); 
  //fmsdb->readGainFromText();
  fmsdb->readGainCorrFromText();
  //fmsdb->readRecParamFromFile();

  StEventMaker* eventMk = new StEventMaker();
  StFmsHitMaker* fmshitMk = new StFmsHitMaker();
  StFmsPointMaker* pointMaker = new StFmsPointMaker("StFmsPointMaker");;  
  if(opt==0) {pointMaker->setMergeSmallToLarge(0);}
  else       {pointMaker->setMergeSmallToLarge(1);}
  if(opt>=2) {pointMaker->setCategorizationAlgo(1);}
  else       {pointMaker->setCategorizationAlgo(0);}
  if(opt>=3) {pointMaker->setTry1PhotonFit(1);}
  else       {pointMaker->setTry1PhotonFit(0);}
  if(opt>=4) {pointMaker->setScaleShowerShape(1);}
  else       {pointMaker->setScaleShowerShape(0);}
  if(readMuDst){
    fmshitMk->SetReadMuDst();
    pointMaker->SetReadMuDst();
  }

  StFmsFpsMaker* fmsfps = new StFmsFpsMaker(); 
  fmsfps->setReadMuDST();

  StFmsOfflineQaMaker* fmsqa = new StFmsOfflineQaMaker();
  fmsqa->setPrint(print);
  TString filename(file);
  filename.ReplaceAll("mudst",outdir);
  filename.ReplaceAll(".list",".MuDst.root");
  if(ifile<0){
      filename.ReplaceAll(".MuDst.root",".fmsqa.root");
  }else{
      filename.ReplaceAll(".MuDst.root",Form(".%d.fmsqa.root",ifile));
  }
  cout << "StFmsQaMaker Output File Name = " << filename.Data()<<endl;
  fmsqa->setFileName(filename.Data());

  if(print>=10){
      gSystem->Load("StFmsEventDisplay");
      StFmsEventDisplay* fmsed = new StFmsEventDisplay();
      fmsed->setMaxEvents(100);
      TString filenameED(file);
      filenameED.ReplaceAll("mudst",outdir);
      filenameED.ReplaceAll(".MuDst.root",".eventDisplay.png");
      filenameED.ReplaceAll(".list",".eventDisplay.root");
      fmsed->setFileName(filenameED.Data());
      if(print==11) fmsed->setFilter(1);
      if(print==12) fmsed->setFilter(2);
  }

  gSystem->Load("StFmsDiPi0");
  StFmsDiPi0* dipi0 = new StFmsDiPi0();
  TString filenameDiPi0(file);
  filenameDiPi0.ReplaceAll("mudst",outdir);
  filenameDiPi0.ReplaceAll(".list",".MuDst.root");
  if(ifile<0){
      filenameDiPi0.ReplaceAll(".MuDst.root",".dipi0.root");
  }else{
      filenameDiPi0.ReplaceAll(".MuDst.root",Form(".%d.dipi0.root",ifile));
  }
  cout << "DiPi0 outfile name = " << filenameDiPi0.Data()<<endl;
 // dipi0->setFileName(filenameDiPi0.Data());
  TString filenameTree(filenameDiPi0);
  filenameTree.ReplaceAll(".dipi0.root",".tree.root");
  dipi0->setTreeFileName(filenameTree.Data());
  dipi0->setWriteTree();
  dipi0->setBBCCut(3000.0,5000.0,8000.0,12000.0);
  //dipi0->VpdTimingCutUp(1300); cout <<"WARNING! VPD west upper timing cut is being applied!\n" <<endl;//added by Xiaoxuan
  //dipi0->VpdTimingCutLow(1);cout <<"WARNING! VPD west lower timing cut is being applied!\n" <<endl;//added by Xiaoxuan

  chain->Init();
  //chain->EventLoop(start,stop);
  chain->EventLoop();
  chain->Finish();
  delete chain;
}
