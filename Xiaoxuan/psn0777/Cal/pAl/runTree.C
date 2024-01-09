// forward declarations
#include <fstream>
class StChain;
class StMuDstMaker;    

// global variables
StChain            *analysisChain = 0;

void runTree(char* fnamelist="test.list",  unsigned int neventsIn = 0){  
  // If nEvents is negative, reset to the maximum possible value for an Int_t
  if( neventsIn <= 0 ) neventsIn = 1<<31-1;

//TString fname;
string fname;
string str_read;
std::ifstream file_read(fnamelist);
getline(file_read,str_read);
//fname = str_read.str();
fname = str_read;
fname[fname.size()-1] = '\0';
cout << fname << ","<< endl;
char* dir=".";

  TChain* trees = new TChain();
	  //if ( fname.EndsWith(".root")) {
	      //cout << Form("Adding %s to TChain",fname.Data())<<endl;
	      //trees->Add(fname.data());
	      trees->AddFile(Form("%s/dipi0",fname.data()));
	  //}

  // load the shared libraries
  std::cout << "***** Loading libraries *****" << endl;
  LoadLibs();

  // Create the analysis chain
  analysisChain = new StChain("dipi0Chain");
  //cout << "Constructing StFmsDbMaker" << endl;
  //StFmsDbMaker* fmsDbMkr = new StFmsDbMaker( "fmsDb" );
  //fmsDbMkrName = fgtDbMkr->GetName();

  gSystem->Load("StFmsDiPi0");
  StFmsDiPi0* dipi0=new StFmsDiPi0;
  TString filenameDiPi0(Form("%s/dipi0.root",dir));
  cout << "DiPi0 outfile name = " << filenameDiPi0.Data()<<endl;
  dipi0->setFileName(filenameDiPi0.Data());
  dipi0->setReadTree(trees);
  dipi0->setBBCCut(3000.0,8000.0,15000.0,30000000.0);

  analysisChain->Init();

  Int_t ierr  = kStOK;  // err flag
  Int_t nevents = 0;    // cumulative number of events in
  neventsIn= trees->GetEntries();
cout<<"Nevt="<<neventsIn<<endl;
  for( ; nevents < neventsIn && !ierr; ++nevents ){
    if(nevents%10000==0) cout <<"event: "<< nevents <<endl;
    analysisChain->Clear();
    ierr = analysisChain->Make();
  } 
  analysisChain->Finish(); 
  analysisChain->Delete();
  return;
};


void LoadLibs() {
  // commong shared libraries
  gROOT->Macro("loadMuDst.C");
  gSystem->Load("StStarLogger");
  //gSystem->Load("StTpcDb");
  //gSystem->Load("StDbUtilities");
  //gSystem->Load("StDetectorDbMaker");
  //gSystem->Load("StMagF");
  //gSystem->Load("StFmsUtil");
  //gSystem->Load("StFmsDbMaker");
};
