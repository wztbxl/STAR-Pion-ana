#include "dihadron_theory.h"

static const int kNPtBin=6;
static float ptcut[kNPtBin+1]={0.5,1.0,1.5,2.0,2.5,3.0,5.0};
//static float ptcut[kNPtBin+1]={0.5,1.0, 1.4, 2.0, 2.4, 2.8, 5.0};//Xiaoxuan

//static const int NCUT=20;
static const int NCUT=26;//Xiaoxuan
/*static const char* CCUT[3][NCUT+1]={{"Before Mass Cut","Inclusive","No BBCE cut",
				     "BBCE<3000","3000<BBCE<5000","5000<BBCE<8000",
				     "Abort Gap","Jet Trigger","Double Triggers",
				     "On/Off Mass","Off/On Mass","Off/Off Mass",
				     "SmallBS","LargeBS","Top2",
				     "8000<BBCE<12000","12000<BBCE","NoBBCTOF",
				     "Top","Bottom",
				     "RealPi0"},
				    {"Before Mass Cut","Inclusive","No BBCE cut",
                                     "BBCE<3000","3000<BBCE<10000","10000<BBCE<15000",
                                     "Abort Gap","Jet Trigger","Double Triggers",
                                     "On/Off Mass","Off/On Mass","Off/Off Mass",
                                     "SmallBS","LargeBS","Top2",
                                     "15000<BBCE<20000","20000<BBCE","NoBBCTOF",
				     "Top","Bottom",
                                     "RealPi0"},
				    {"Before Mass Cut","Inclusive","No BBCE cut",
                                     "BBCE<3000","3000<BBCE<12000","12000<BBCE<24000",
                                     "Abort Gap","Jet Trigger","Double Triggers",
                                     "On/Off Mass","Off/On Mass","Off/Off Mass",
                                     "SmallBS","LargeBS","Top2",
                                     "24000<BBCE<36000","36000<BBCE","NoBBCTOF",
				     "Top","Bottom",
                                     "RealPi0"}};

*/
static const char* CCUT[3][NCUT+1]={{"Before Mass Cut","Inclusive","MinBias",
				     "BBCE<3000","3000<BBCE<6000","6000<BBCE<10000",
				     "Abort Gap","Jet Trigger","Double Triggers",
				     "On/Off Mass","Off/On Mass","Off/Off Mass",
				     "SmallBS","LargeBS","Top2",
				     "10000<BBCE<15000","BBCE>15000","NoBBCTOF",
				     "Top","Bottom",
				     "SmallBS1","SmallBS2","SmallBS3","LargeBS1",
				     "LargeBS2","LargeBS3",
				     "RealPi0"},
				    {"Before Mass Cut","Inclusive","MinBias",
                                     "BBCE<3000","3000<BBCE<8000","8000<BBCE<15000",
                                     "Abort Gap","Jet Trigger","Double Triggers",
                                     "On/Off Mass","Off/On Mass","Off/Off Mass",
                                     "SmallBS","LargeBS","Top2",
                                     "BBCE>15000","","NoBBCTOF",
				     "Top","Bottom",
			             "SmallBS1","SmallBS2","SmallBS3","LargeBS1",
				     "LargeBS2","LargeBS3",
				     "RealPi0"},
				    {"Before Mass Cut","Inclusive","MinBias",
                                     "BBCE<3000","3000<BBCE<12000","12000<BBCE<24000",
                                     "Abort Gap","Jet Trigger","Double Triggers",
                                     "On/Off Mass","Off/On Mass","Off/Off Mass",
                                     "SmallBS","LargeBS","Top2",
                                     "24000<BBCE<36000","BBCE>36000","NoBBCTOF",
				     "Top","Bottom",
				     "SmallBS1","SmallBS2","SmallBS3","LargeBS1",
				     "LargeBS2","LargeBS3",
				     "RealPi0"}};
//!!!!!!!!!!!!!!!!!!!!!!!!!!check if "RealPi0" is in the right order!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!It can be from Pythia!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//add trigger dependence by Xiaoxuan

static int QM=0;

static const char CBEAM[20];
static const char* CLS[2]={"large","small"};
static int IBEAM,JBEAM;

static int MINEVT=17000;

static const double PI=TMath::Pi();
static const double twoPI=PI*2.0;

const float MassCut0=0.07;
const float MassCut1=0.2;
const float MassCut2=0.35;
static Double_t ZggCut=0.7;
static int OPT=4;
static int RUN=1;
static int RUNpp=16077027;
static int RUNpAu=16125053;
static TCanvas *c1;
static TCanvas *c2;
static TCanvas *c3;
static TString* FILENAME;
TFile* mTFile;
static float NNN=0;

float PAR0[kNPtBin][kNPtBin][3];
float PAR1[kNPtBin][kNPtBin][3];
float PAR2[kNPtBin][kNPtBin][3];
float PAR3[kNPtBin][kNPtBin][3];
float PAR4[kNPtBin][kNPtBin][3];
float ERR0[kNPtBin][kNPtBin][3];
float ERR1[kNPtBin][kNPtBin][3];
float ERR2[kNPtBin][kNPtBin][3];
float ERR3[kNPtBin][kNPtBin][3];
float ERR4[kNPtBin][kNPtBin][3];
float CHI[kNPtBin][kNPtBin][3];
float PT1[kNPtBin][kNPtBin][3];
float PT2[kNPtBin][kNPtBin][3];
float BBC[kNPtBin][kNPtBin][3];
int NEV[kNPtBin][kNPtBin][3];

Double_t pi0fcn( Double_t *x, Double_t *par ){
    //par[0]: xi (location), par[1]: omega (scale), par[2]: alpha (shape), par[3]: overall normalization
    Double_t arg = 0;
    if(par[1]!=0) arg = (x[0]-par[0])/par[1];
    Double_t fitval = 0;
    //fitval = par[3]*(2/par[1])*TMath::Gaus(arg,0,1)*0.5*(1+TMath::Erf(par[2]*arg/TMath::Sqrt(2)));
    fitval = par[2]*(2/par[1])*TMath::Gaus(arg,0,1);
    return fitval;
}

Double_t bkgfcn( Double_t *x, Double_t *par ){ //background is described by pol3
    return par[4]*(par[0] + par[1]*x[0] + par[2]*x[0]*x[0]+ par[3]*x[0]*x[0]*x[0]); //par[4] is floating: overall normalization         
}

Double_t fitFcn( Double_t *x, Double_t *par ){
    return pi0fcn(x,par) + bkgfcn(x,&par[3]);
}

TLatex* drawLatex(Double_t x, Double_t y, TString text, Int_t textFont, Double_t textSize, Int_t colorIndex){
  TLatex *latex = new TLatex(x,y,text);
  latex->SetNDC();
  latex->SetTextFont(textFont);
  latex->SetTextSize(textSize);
  latex->SetTextColor(colorIndex);
  latex->Draw("same");
  return latex;
}


double wrapAround(double phi){
    double res=phi;
    while(res>=1.5*PI) {res-=twoPI;}
    while(res<-0.5*PI) {res+=twoPI;}
    return res;
}

void mixing(TH1F* h1, TH1F* h2, TH1F* d, TH1F* mix, int sub=1){
    int t1=h1->GetEntries();
    int t2=h1->GetEntries();
    int n1=h1->GetNbinsX();
    int n2=h2->GetNbinsX();
    for(int i=1; i<=n1; i++){
	double p1=h1->GetBinCenter(i);
	double c1=h1->GetBinContent(i);
	for(int j=1; j<=n2; j++){
	    double p2=h2->GetBinCenter(j);
	    double c2=h2->GetBinContent(j);
	    double dp=wrapAround(p1-p2+PI/n1/100.0);
	    mix->Fill(dp,c1*c2);
	}
    }
    if(sub==1) mix->Add(d,-1.0);
    mix->Scale(n1/mix->Integral());
}

void mixsim(int run, int cut, int bin1, int bin2, TCanvas* c=0, int nevt=1000, int seed=1){
    readfile(OPT,run);
    TH1F *h3,*h4,*h5;
    h3= (TH1F*)mTFile->Get(Form("phi1_%1d%1d_c%d",bin1,bin2,cut))->Clone();
    h4= (TH1F*)mTFile->Get(Form("phi2_%1d%1d_c%d",bin1,bin2,cut))->Clone();
    h5= (TH1F*)mTFile->Get(Form("dphi_%1d%1d_c%d",bin1,bin2,cut))->Clone();
    int nbin=h5->GetNbinsX();
    h3->Scale(nbin/h3->GetEntries());
    h4->Scale(nbin/h4->GetEntries());
    h5->Scale(nbin/h5->GetEntries());

    TH1F *PHI1,*PHI2,*DPHI0;
    TH1F *DPHI1,*DMIX1,*DCOR1;
    PHI1 =new TH1F("PHI1", "PHI1", nbin,-0.5*PI,1.5*PI);
    PHI2 =new TH1F("PHI2", "PHI2", nbin,-0.5*PI,1.5*PI);
    DPHI0=new TH1F("DPHI0","DPHI0",nbin,-0.5*PI,1.5*PI);
    DPHI1=new TH1F("DPHI1","DPHI1",nbin,-0.5*PI,1.5*PI);
    DMIX1=new TH1F("DMIX1","DMIX1",nbin,-0.5*PI,1.5*PI);
    DCOR1=new TH1F("DCOR1","DCOR1",nbin,-0.5*PI,1.5*PI);
    TRandom2* RND=new TRandom2(seed);
    float p1,p2,dp,w3,w4,w5;
    for(int i=0; i<nevt*nbin; i++){
	p1 = wrapAround(RND->Rndm()*2.0*PI);
	dp = wrapAround(RND->Rndm()*2.0*PI);
	p2 = wrapAround(p1-dp);
	w3= h3->GetBinContent(h3->FindBin(p1));
	w4= h4->GetBinContent(h4->FindBin(p2));
	w5= h5->GetBinContent(h5->FindBin(dp));
	PHI1->Fill(p1,w3);
	PHI2->Fill(p2,w3*w4*w5);	
	DPHI0->Fill(dp,w5);
	DPHI1->Fill(dp,w3*w4*w5);
	//printf("%d p1,p2,dp=%5.3f %5.3f %5.3f\n",i,p1,p2,dp);
    }
    mixing(PHI1,PHI2,DPHI1,DMIX1,0);
    DCOR1->Divide(DPHI1,DMIX1);

    TH1F *ratio;
    ratio = (TH1F*)DCOR1->Clone();
    ratio->Divide(DPHI0);

    if(c){
	gStyle->SetOptStat(0);
	TText* t;
	c->Divide(3,2);

	c->cd(1); 
	PHI1->SetLineWidth(2); PHI1->Draw("same");
	t= new TText(0.70, 0.80,"Phi1"); t->SetTextSize(0.05); t->SetTextColor(1); t->SetNDC(); t->Draw();
	
	c->cd(2); 
	PHI2->SetLineWidth(2); PHI2->Draw("same");
	t= new TText(0.70, 0.80,"Phi2"); t->SetTextSize(0.05); t->SetTextColor(1); t->SetNDC(); t->Draw();
       	
	c->cd(3);
	DMIX1->SetLineWidth(2); DMIX1->Draw("same");
	//t= new TText(0.40, 0.20,"Mix (Phi1*Phi2)"); t->SetTextSize(0.05); t->SetTextColor(1); t->SetNDC(); t->Draw();
	
	c->cd(4);  
	float m3=DPHI1->GetBinContent(DPHI1->GetNbinsX()*3/4);
	DPHI1->SetMinimum(0);
	DPHI1->SetMaximum(m3*1.6);
	DPHI1->SetLineWidth(4); DPHI1->SetLineColor(4); DPHI1->Draw();
	DCOR1->SetLineWidth(2); DCOR1->SetLineColor(2); DCOR1->Draw("same");
	DPHI0->SetLineWidth(3); DPHI0->SetLineColor(1); DPHI0->Draw("same");
	t= new TText(0.60, 0.85,"Input");       t->SetTextSize(0.04); t->SetTextColor(1); t->SetNDC(); t->Draw();
	t= new TText(0.60, 0.81,"UnCorrected"); t->SetTextSize(0.04); t->SetTextColor(4); t->SetNDC(); t->Draw();
	t= new TText(0.60, 0.77,"Corrected");   t->SetTextSize(0.04); t->SetTextColor(2); t->SetNDC(); t->Draw();

	c->cd(5);
	ratio->SetLineWidth(1);ratio->Draw();
	t= new TText(0.60, 0.85,"Corrected/Input");t->SetTextSize(0.04);t->SetNDC(); t->Draw();

	c->cd(6);
	t = new TText(0.35, 0.85,Form("pT1=%3.1f-%3.1f GeV",ptcut[bin1],ptcut[bin1+1])); t->SetNDC(); t->SetTextSize(0.04); t->Draw();
	t = new TText(0.35, 0.80, Form("pT2=%3.1f-%3.1f GeV",ptcut[bin2],ptcut[bin2+1])); t->SetNDC(); t->SetTextSize(0.04); t->Draw();

	c->SaveAs(Form("plot/mixsim_r%d_%d%d_c%d.png",run,bin1,bin2,cut));
    }
}

Double_t twoGaus(Double_t *x, Double_t *par){
    Double_t OP=1.0/sqrt(2.0*PI);
    Double_t x1 = x[0];
    while(x1<-PI) x1+=2.0*PI;
    while(x1>=PI) x1-=2.0*PI;
    Double_t x2 = x[0]-PI;
    while(x2<-PI) x2+=2.0*PI;
    while(x2>=PI) x2-=2.0*PI;
    Double_t f = par[0]/2.0/PI;
    //revised by Xiaoxuan, to be consistent with one gaus fit
    f += par[3]*OP/par[4]*exp(-x1*x1/2.0/par[4]/par[4]);
    f += par[1]*OP/par[2]*exp(-x2*x2/2.0/par[2]/par[2]);
    return f;
}

Double_t oneGaus(Double_t *x, Double_t *par){
    Double_t OP=1.0/sqrt(2.0*PI);
    Double_t x1 = x[0]+PI;
    while(x1<-PI) x1+=2.0*PI;
    while(x1>=PI) x1-=2.0*PI;
    Double_t f = par[0]/2.0/PI;
    f += par[1]*OP/par[2]*exp(-x1*x1/2.0/par[2]/par[2]);
    return f;
}

//Xiaoxuan, OPT=4, CBEAM[20], RUN=1, RUNpp=16077027, RUNpAu=16125053 for warnings
void readfile(int opt=-1, int run=-1){
    char file[100]; 
    IBEAM=0; JBEAM=0;
    if(opt<0) opt=OPT;
    //if(run<0)   {sprintf(file,"FPS/hist_opt%d/st_fms_%d_raw_merged.dipi0.root",opt,RUN); sprintf(CBEAM,"%d",RUN);}
    if(run<0)   {sprintf(file,"/star/u/xchu/pwg/DiPion0Corr/pp15/jobs_withoutTDCCut/merged.local.tree.root",opt,RUN); sprintf(CBEAM,"%d",RUN);}
    if(run>100) {sprintf(file,"FPS/hist_opt%d/st_fms_%d_raw_merged.dipi0.root",opt,run); sprintf(CBEAM,"%d",run);}
    if(run==1)  {sprintf(file,"FPS/hist_opt%d/st_fms_%d_raw_merged.dipi0.root",opt,RUNpp);sprintf(CBEAM,"%d",RUNpp);}
    if(run==2)  {sprintf(file,"FPS/hist_opt%d/st_fms_%d_raw_merged.dipi0.root",opt,RUNpAu);sprintf(CBEAM,"%d",RUNpAu);}
    if(run==11) {sprintf(file,"YourDirectory/pp/Hist/pp.Hist.root");  sprintf(CBEAM,"pp");   IBEAM=0; JBEAM=0;}
    //if(run==15) {sprintf(file,"/star/u/xchu/pwg/DiPion0Corr/pAu15_NewPair/NewPair_allPtBin_firsthalf_withoutBsSm3/merged.root");     sprintf(CBEAM,"pAu1"); IBEAM=3; JBEAM=2;}
    if(run==15) {sprintf(file,"YourDirectory/pAu/Hist/pAu.Hist.root");     sprintf(CBEAM,"pAu"); IBEAM=3; JBEAM=2;}
    if(run==12) {sprintf(file,"/star/u/xchu/pwg/DiPion0Corr/pAu15_NewPair/NewPair_allPtBin_secondhalf/merged.root");     sprintf(CBEAM,"pAu2"); IBEAM=2; JBEAM=2;}
    //if(run==13) {sprintf(file,"/star/u/xchu/pwg/DiPion0Corr/pp15/day9193/merged.local.tree.root"); sprintf(CBEAM,"pAl");  IBEAM=1; JBEAM=1;}
    if(run==13) {sprintf(file,"YourDirectory/pAl/Hist/pAl.Hist.root");sprintf(CBEAM,"pAl");  IBEAM=1; JBEAM=1;}
    //if(run==20) {sprintf(file,"FPS/hist_pythia6/dipi0.all.root"); sprintf(CBEAM,"pythia"); IBEAM=4; JBEAM=2;}    
    if(run==20) {sprintf(file,"/star/u/xchu/pwg/DiPion0Corr/pp15/pptotal/merged.root"); sprintf(CBEAM,"pythia"); IBEAM=4; JBEAM=2;}  //Xiaoxuan
    printf("Reading %s\n",file);
    mTFile = new TFile(file);
}

void openCanvas(){
  c3 = new TCanvas("DiPi0_3","DiPi0_3",80,60,1300,900);
  c2 = new TCanvas("DiPi0_2","DiPi0_2",60,40,1300,900);
  c1 = new TCanvas("DiPi0_1","DiPi0_1",40,20,1300,900);
  gStyle->SetPalette(1);
  gStyle->SetStatW(0.4);
  TGaxis::SetMaxDigits(3);
}

void plot1d(TCanvas* c, char* name){
    TH1F *h;
    c->Divide(1,3);
    c->cd(1)->SetLogy();
    readfile(OPT,11);
    h = (TH1F*)mTFile->Get(Form("%s",name));   h->Draw(); h->SetLineWidth(2); h->SetMinimum(1.0);
    h = (TH1F*)mTFile->Get(Form("%sAG",name)); h->Draw("same"); h->SetLineColor(2);h->SetLineWidth(2);
    t=new TText(0.2, 0.25,"pp collisions"); t->SetNDC(); t->Draw();
    t=new TText(0.2, 0.20,"pp abort-gap");  t->SetNDC(); t->Draw(); t->SetTextColor(2);
    c->cd(2)->SetLogy();
    readfile(OPT,13);
    h = (TH1F*)mTFile->Get(Form("%s",name));   h->Draw(); h->SetLineWidth(2); h->SetMinimum(1.0);
    h = (TH1F*)mTFile->Get(Form("%sAG",name)); h->Draw("same"); h->SetLineColor(2);h->SetLineWidth(2);
    t=new TText(0.2, 0.25,"pAl collisions"); t->SetNDC(); t->Draw();
    t=new TText(0.2, 0.20,"pAl abort-gap");  t->SetNDC(); t->Draw(); t->SetTextColor(2);
    c->cd(3)->SetLogy();
    readfile(OPT,12);
    h = (TH1F*)mTFile->Get(Form("%s",name));  h->Draw(); h->SetLineWidth(2);h->SetMinimum(1.0);
    h = (TH1F*)mTFile->Get(Form("%sAG",name)); h->Draw("same"); h->SetLineColor(2); h->SetLineWidth(2);
    readfile(OPT,15);
    h = (TH1F*)mTFile->Get(Form("%s",name));   h->Draw("same"); h->SetLineColor(4); h->SetLineWidth(2);
    h = (TH1F*)mTFile->Get(Form("%sAG",name)); h->Draw("same"); h->SetLineColor(6); h->SetLineWidth(2);
    t=new TText(0.2,  0.25,"pAu2 collisions"); t->SetNDC(); t->Draw();
    t=new TText(0.2,  0.20,"pAu2 abort-gap");  t->SetNDC(); t->Draw(); t->SetTextColor(2);
    t=new TText(0.35, 0.25,"pAu1 collisions"); t->SetNDC(); t->Draw(); t->SetTextColor(4);
    t=new TText(0.35, 0.20,"pAu1 abort-gap");  t->SetNDC(); t->Draw(); t->SetTextColor(6);
    c->SaveAs(Form("plot/%s.png",name));
}

void plot1d2(char* name){
    TH1F *h;
    TText* t;
    TLine* l;
    c1->Divide(1,3);
    c1->cd(1)->SetLogy();
    readfile(OPT,11);
    h = (TH1F*)mTFile->Get(Form("%s",name));   h->Draw(); h->SetLineWidth(2); h->SetLineColor(4); h->SetMinimum(1.0);
    t=new TText(0.8, 0.80,"pp"); t->SetNDC();  t->SetTextColor(4); t->SetTextSize(0.1); t->Draw(); 
    l=new TLine( 3000,1, 3000,1e8); l->Draw();
    l=new TLine( 5000,1, 5000,1e8); l->Draw();
    l=new TLine( 8000,1, 8000,1e8); l->Draw();
    l=new TLine(12000,1,12000,1e8); l->Draw();
    t=new TText(0.4, 0.92,"BBC East ADC Sum"); t->SetNDC(); t->SetTextColor(1); t->SetTextSize(0.1); t->Draw();    

    c1->cd(2)->SetLogy();
    readfile(OPT,13);
    h = (TH1F*)mTFile->Get(Form("%s",name));   h->Draw("same"); h->SetLineWidth(2);  h->SetLineColor(6); h->SetMinimum(1.0);
    t=new TText(0.8, 0.80,"pAl"); t->SetNDC(); t->SetTextColor(6); t->SetTextSize(0.1); t->Draw();
    l=new TLine( 3000,1, 3000,0.5e8); l->Draw();
    l=new TLine(10000,1,10000,0.5e8); l->Draw();
    l=new TLine(15000,1,15000,0.5e8); l->Draw();
    l=new TLine(20000,1,20000,0.5e8); l->Draw();

    c1->cd(3)->SetLogy();
    readfile(OPT,12);
    h = (TH1F*)mTFile->Get(Form("%s",name));   h->Draw("same"); h->SetLineWidth(2);  h->SetLineColor(2); h->SetMinimum(1.0);
    t=new TText(0.8, 0.80,"pAu"); t->SetNDC(); t->SetTextColor(2); t->SetTextSize(0.1); t->Draw();
    l=new TLine( 3000,1, 3000,0.5e8); l->Draw();
    l=new TLine(12000,1,12000,0.5e8); l->Draw();
    l=new TLine(24000,1,24000,0.5e8); l->Draw();
    l=new TLine(36000,1,36000,0.5e8); l->Draw();

    c1->SaveAs(Form("plot/%s.2.png",name));    
}

void plot2d(TCanvas* c, char* name){
    TH2F *h2;
    c->Divide(2,2);
    c->cd(1)->SetLogz();
    readfile(OPT,11);
    h2 = (TH2F*)mTFile->Get(Form("%s",name));
    h2->Draw("colz");
    t=new TText(0.75, 0.15,"pp"); t->SetNDC(); t->Draw();
    c->cd(2)->SetLogz();
    readfile(OPT,13);
    h2 = (TH2F*)mTFile->Get(Form("%s",name));
    h2->Draw("colz");
    t=new TText(0.75, 0.15,"pAl"); t->SetNDC(); t->Draw();
    c->cd(3)->SetLogz();
    readfile(OPT,15);
    h2 = (TH2F*)mTFile->Get(Form("%s",name));
    h2->Draw("colz");
    t=new TText(0.75, 0.15,"pAu1"); t->SetNDC(); t->Draw();
    c->cd(4)->SetLogz();
    readfile(OPT,12);
    h2 = (TH2F*)mTFile->Get(Form("%s",name));
    h2->Draw("colz");
    t=new TText(0.75, 0.15,"pAu2"); t->SetNDC(); t->Draw();
    c->SaveAs(Form("plot/%s.png",name));    
}

void bbc(int plt=0){
    gStyle->SetOptStat(0);
    if(plt==0 || plt==1){
	plot1d(c1,"BBCE");
	plot1d(c2,"BBCMult");
	plot1d(c3,"TOF");
    }
    if(plt==0 || plt==2){
	plot2d(c1,"BBC_BBCMult");
	plot2d(c2,"BBC_TOF");
	plot2d(c3,"BBCMult_TOF");	
    }
    if(plt==0 || plt==3){
	plot2d(c1,"TOF_TOF");
    }
}

TH1F* mix(int run=21, int cut=1, int bin1=3, int bin2=1, int plot=1, int method=1){
    readfile(OPT,run);
    TH1F* h1= (TH1F*)mTFile->Get(Form("phi1_%1d%1d_c%d",bin1,bin2,cut));
    TH1F* h2= (TH1F*)mTFile->Get(Form("phi2_%1d%1d_c%d",bin1,bin2,cut));
    TH1F* h3= (TH1F*)mTFile->Get(Form("dphi_%1d%1d_c%d",bin1,bin2,cut));
    TH1F* h4= (TH1F*)h3->Clone(Form("mix_%1d%1d_c%d",bin1,bin2,cut));
    TH1F* h5= (TH1F*)h3->Clone(Form("dphi_corr_%1d%1d_c%d",bin1,bin2,cut));
    h4->Reset();
    h5->Reset();
    mixing(h1,h2,h3,h4,1);
    h5->Divide(h3,h4);
    
    if(plot==1){
	TText* t;
	gStyle->SetOptStat(0);
	c1->Divide(2,2);
	c1->cd(1); h1->SetMinimum(0); h1->SetLineWidth(2); h1->Draw();
	t= new TText(0.2, 0.85,Form("%s %s",CBEAM,CCUT[JBEAM][cut])); t->SetNDC(); t->SetTextSize(0.06); t->SetTextColor(1); t->Draw();
	t= new TText(0.70, 0.80,"Phi1"); t->SetTextSize(0.05); t->SetTextColor(1); t->SetNDC(); t->Draw();

	c1->cd(2); h2->SetMinimum(0); h2->SetLineWidth(2); h2->Draw();
	t= new TText(0.70, 0.80,"Phi2"); t->SetTextSize(0.05); t->SetTextColor(1); t->SetNDC(); t->Draw();

	float m4=h4->GetMaximum();
	c1->cd(3); h4->SetMinimum(0); h4->SetLineWidth(2); h4->SetMaximum(m4*1.1); h4->Draw();
	t= new TText(0.40, 0.20,"Mix1 (Phi1*Phi2)"); t->SetTextSize(0.05); t->SetTextColor(1); t->SetNDC(); t->Draw();

	c1->cd(4); 
	h3->Rebin(4); h5->Rebin(4); h15->Rebin(4);
	float m3=h3->GetBinContent(h3->GetNbinsX()*3/4);
	h3->SetMinimum(0); h3->SetLineWidth(2); h3->SetMaximum(m3*1.5); h3->SetLineColor(1); h3->Draw();
	h5->SetLineWidth(2);  h5->SetLineColor(2);  h5->Draw("same");
	t= new TText(0.20, 0.20,"UnCorrected"); t->SetTextSize(0.04); t->SetTextColor(1); t->SetNDC(); t->Draw();
	t= new TText(0.20, 0.16,"Corrected1");  t->SetTextSize(0.04); t->SetTextColor(2); t->SetNDC(); t->Draw();

	c1->SaveAs(Form("plot/mix_%s_%1d%1d_c%d.png",CBEAM,bin1,bin2,cut));
    }//plot==1
    if(plot==2){
	if(method==0) return h4;
    }//plot==2
    if(method==0) return h5;
    return 0;
}

void plot(const char* v, int run, int cut, TCanvas* cvs, int fit=0, int bin1=-1, int bin2=-1, float ymax=0.0, int rebin=4){   
    printf("v=%s run=%d cut=%d fit=%d bin1=%d bin2=%d\n",v,run,cut,fit,bin1,bin2);
    int bin0=1;
    char c[100];
    char c2[100];
    readfile(OPT,run);
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(0);
    gStyle->SetOptTitle(0);
    gStyle->SetPadGridX(0);
    gStyle->SetPadGridY(0);
    int b1=bin1, b2=bin1+1, b3=bin2, b4=b3;
    if(cvs){
	cvs->Clear();
	if(bin1<0) {cvs->Divide(kNPtBin-bin0,kNPtBin-bin0);}
    }
    if(bin1<0) {b1=bin0; b2=kNPtBin; b3=bin0;}
    TText* t;
    for(int i=b1; i<b2; i++){
	if(bin1<0) b4=i;
	for(int j=b3; j<b4; j++){
	    int cc=cut;
	    if(cut==99 && (v=="m1" || v=="m2")) cc=0;
	    if(cut==99 && v=="dphi") cc=1;
	    TH1F *h,*h2,*h3,*h4;
	    TH2F *h2d;

	    //get normalizations
	    float norm0=1.0;
	    float norm1=1.0;
	    float norm2=1.0;
	    float norm3=1.0;
	    if(v=="m0" || v=="phi0"){}
	    else{
		sprintf(c,"m0_%1d_c%d",i,cc);
		printf("%s\n",c);
		TH1F* h0 = (TH1F*)mTFile->Get(c);
		norm0 = h0->GetEntries();
		TH1F* h1 = (TH1F*)mTFile->Get(c);
		norm1 = h1->GetEntries();
		printf("n0=%f n1=%f\n",norm0,norm1);
		norm2=norm1/norm0;
		norm3=norm2/ZggCut;
	    }

	    printf("n0=%f n1=%f\n",norm0,norm1);
	    int opt=1, log=0;

	    if(v=="mix"){
		h=mix(run,cc,i,j,2,0);
		h->SetLineColor(2);
		h->SetMinimum(0.45);
		h->SetMaximum(1.55);
		//h2=mix(run,cc,i,j,2,1);
		//h2->SetLineColor(1);
		h->GetXaxis()->SetNdivisions(-4);
		h->GetYaxis()->SetNdivisions(204);
	    }else if(v=="corr"){
		h = mix(run,cc,i,j,0,0);
		if(rebin>0) h->Rebin(rebin);
		if(fit==1 || fit==-1) h->GetXaxis()->SetRangeUser(PI/2.0,3.0*PI/2.0);
		int nbin = h->GetNbinsX();
                h->Sumw2();
                if(run<20) {h->Scale(1.0/norm0*nbin/2.0/PI/ZggCut);}
                else       {h->Scale(1.0/norm0*nbin/2.0/PI);}
		if(j==1) h->SetMaximum(0.04);
		if(j==2) h->SetMaximum(0.015);
		if(j==2&&i==4)h->SetMaximum(0.025);
		if(j==3) h->SetMaximum(0.005);
		if(j==3&&i==5)h->SetMaximum(0.002);
		if(j==4) h->SetMaximum(0.0008);
		if(j==5) h->SetMaximum(0.00025);
		h->GetXaxis()->SetNdivisions(-4);
		h->GetYaxis()->SetNdivisions(204);
		TAxis* ax=h->GetXaxis();
		ax->SetLabelOffset(1);
		sprintf(c,"dphi_%1d%1d_c%d",i,j,cc);
                h2 = (TH1F*)mTFile->Get(c);
		h2->Sumw2(); h2->SetLineColor(4);
		if(rebin>0) h2->Rebin(rebin);
		if(run<20) {h2->Scale(1.0/norm0*nbin/2.0/PI/ZggCut);}
                else       {h2->Scale(1.0/norm0*nbin/2.0/PI);}
		float msize=1.0;
		if(bin1<0) msize=0.5;
		h->SetMarkerStyle(20); h->SetMarkerSize(msize+0.2);
		h2->SetMarkerStyle(21); h2->SetMarkerSize(msize); h2->SetMarkerColor(4);
	    }else if(v=="norm" || v=="dphi"){
		sprintf(c,"dphi_%1d%1d_c%d",i,j,cc);
                h = (TH1F*)mTFile->Get(c);
		if(rebin>0) h->Rebin(rebin);
		printf("Getting %s max=%f\n",c,h->GetMaximum());
		if(fit==1 || fit==-1) h->GetXaxis()->SetRangeUser(PI/2.0,3.0*PI/2.0);
		int nbin = h->GetNbinsX();
		if(v=="norm"){
		    h->Sumw2();
		    if(run<20) {h->Scale(1.0/norm0*nbin/2.0/PI/ZggCut);}
		    else       {h->Scale(1.0/norm0*nbin/2.0/PI);}
		    if(fit==1 || fit==-1){
;
			if(j==1) h->SetMaximum(0.01);
			if(j==2) h->SetMaximum(0.0015);
			if(j==3) h->SetMaximum(0.0005);
			if(j==4) h->SetMaximum(0.0002);
			if(j==5) h->SetMaximum(0.00006);
		    }else{
			if(j==1) h->SetMaximum(0.01);
			if(j==2) h->SetMaximum(0.003);
			if(j==3) h->SetMaximum(0.0005);
			if(j==4) h->SetMaximum(0.0002);
			if(j==5) h->SetMaximum(0.0001);
		    }
		}
		printf("Getting %s max=%f\n",c,h->GetMaximum());
		h->GetXaxis()->SetNdivisions(-4);
		h->GetYaxis()->SetNdivisions(204);
		TAxis* ax=h->GetXaxis();
		ax->SetLabelOffset(1);
		if(QM>0) opt=0;
		if(QM==3){
		    for(int bin=1; bin<=nbin; bin++) {
			h->SetBinContent(bin,0.01);
		    }
		    h->SetFillColor(2);
		    h->SetLineColor(2);
		    h->SetLineWidth(2);
		    opt=6;
		}
	    }else if(v=="mall"){
		sprintf(c,"m0_%1d_c%d",i,0);
		sprintf(c2,"m0_%1d%1d_c%d",i,j,0);
		h4 = (TH1F*)((TH1F*)mTFile->Get(c))->Clone(c2);
		float norm4 = h4->Integral(h4->GetXaxis()->FindBin(MassCut0),h4->GetXaxis()->FindBin(MassCut1));
		h4->Scale(norm1/norm4);
		h = (TH1F*)((TH1F*)mTFile->Get(c))->Clone(c2);
		sprintf(c,"m0_%1d_c%d",i,cc);
		sprintf(c2,"m0_%1d%1d_c%d",i,j,cc);
		h = (TH1F*)((TH1F*)mTFile->Get(c))->Clone(c2); h->SetLineColor(6);
		h->Scale(norm2); 
		sprintf(c,"m1_%1d%1d_c%d",i,j,cc);
                h2 = (TH1F*)mTFile->Get(c); h2->SetLineColor(2);
		sprintf(c,"m2_%1d%1d_c%d",i,j,cc); 
                h3 = (TH1F*)mTFile->Get(c); h3->SetLineColor(4);	   
	    }else if(v=="z12"){
		sprintf(c,"z1_%1d%1d_c%d",i,j,cc);
                h = (TH1F*)mTFile->Get(c); h->SetLineColor(2);
		sprintf(c,"z2_%1d%1d_c%d",i,j,cc); 
                h2 = (TH1F*)mTFile->Get(c); h2->SetLineColor(4);
	    }else if(v=="phiall"){
		sprintf(c,"phi0_%1d_c%d",i,cc);
                h = (TH1F*)((TH1F*)mTFile->Get(c))->Clone(); h->SetLineColor(1); h->Scale(1.0/h->GetEntries());		
		h->GetXaxis()->SetNdivisions(-4);
		sprintf(c,"phi1_%1d%1d_c%d",i,j,cc); 
                h2 = (TH1F*)mTFile->Get(c); h2->SetLineColor(2); h2->Scale(1.0/h2->GetEntries());
		sprintf(c,"phi2_%1d%1d_c%d",i,j,cc); 
                h3 = (TH1F*)mTFile->Get(c); h3->SetLineColor(4); h3->Scale(1.0/h3->GetEntries());
	    }else if(v=="m0" || v=="phi0"){
		sprintf(c,"%s_%1d_c%d",v,i,cc);
		printf("%s\n",c);
		h = (TH1F*)mTFile->Get(c);		
		h->GetXaxis()->SetNdivisions(505);
		h->GetYaxis()->SetNdivisions(505);
	    }else if(v=="bbce"){
		opt=1;
		log=1;
		sprintf(c,"%s_%1d%1d_c%d",v,i,j,cc);
		printf("%s\n",c);
		h = (TH1F*)mTFile->Get(c);		
		h->SetMinimum(0.1);
	    }else if(v=="phi1" || v=="phi2"){
		opt=1;
		sprintf(c,"%s_%1d%1d_c%d",v,i,j,cc);
		printf("%s\n",c);
		h = (TH1F*)mTFile->Get(c);		
		h->GetYaxis()->SetNdivisions(505);
	    }else if(v=="phi1dphi"){
		opt=2;
		sprintf(c,"%s_%1d%1d_c%d",v,i,j,cc);
		printf("%s\n",c);
		h = (TH1F*)mTFile->Get(c);		
	    }else{
		sprintf(c,"%s_%1d%1d_c%d",v,i,j,cc);
		printf("HIST NAME=%s\n",c);
		h = (TH1F*)mTFile->Get(c);		
	    }
	    if(bin1<0 && cvs){
		//TVirtualPad *pad= cvs->cd((i-bin0)*(kNPtBin-bin0)+(j-bin0)+1);
		TVirtualPad *pad= cvs->cd((j-bin0)*(kNPtBin-bin0)+(i-bin0)+1);
		pad->SetRightMargin(0.005);
		pad->SetLeftMargin(0.08);
		//pad->SetTopMargin(0.10);
		//pad->SetBottomMargin(0.03);
		if(i==1&&j==1){pad->SetRightMargin(0.0);pad->SetTopMargin(0.0);pad->SetBottomMargin(0.0);}
		if(i==5&&j==5){
		pad->SetBottomMargin(0.00);}
		pad->Draw();		
		h->GetXaxis()->SetLabelSize(0.3);
		h->GetYaxis()->SetLabelSize(0.09); 
		//h->GetYaxis()->SetMaxDigits(4);
	    }
	    if(v!="mix"){
		h->SetMinimum(0.0);
		if(ymax>0.0) h->SetMaximum(ymax);
	    }
	    if(QM==1){
		h->GetYaxis()->SetLabelSize(0.0); 
	    }
	    if(cut==19 && cvs==0) opt=5;
	    if(v=="norm" && cut==19 && cvs==0) opt=4;
	    if(v=="norm" && fit==0 && run==20) opt=3;
	    if(log) {h->SetMinimum(0.1); gPad->SetLogy();}
	    if(QM>0) {h->SetMarkerSize(0.7);}
	    //actually draw 
	    printf("opt=%d\n",opt);
	    if(opt==6) h->Draw("e1");
	    if(opt==0) h->Draw("e");
	    if(opt==1) h->Draw();
	    if(opt==2) h->Draw("colz");
	    if(opt==3) {h->SetLineColor(3); h->Draw("C same");}
	    if(opt==4) {gStyle->SetPadGridX(0);gStyle->SetPadGridY(0);}//h->SetLineColor(4); h->Draw("e same");}
	    if(opt==5) {
		h->SetLineColor(4); 
		NNN=NNN/h->GetEntries();
		h->Scale(NNN);
		h->Draw("same");
	    }
	    //draw additional
	    if(v=="mall"){
		h4->Draw("same");
		h2->Draw("same");
		h3->Draw("same");
	    }
	    if((v=="z12" || v=="mix" || v=="corr") && QM==0){//h2->SetMarkerSize(0);h2->Draw("same"); 
h->Draw("same");}
	    if(v=="phiall") {h2->Draw("same"); h3->Draw("same");}
	    if(cut==18){
		NNN=h->GetEntries();
		h->GetXaxis()->SetRangeUser(PI/2.,3*PI/2.);
		plot(v,run,19,0,0,i,j);					
	    }
	    TF1* f;
	    if(v=="norm" || v=="corr"){				
		if(fit==1){
		    f=new TF1("oneGaus",oneGaus,+PI/2.0,+PI*3.0/2.0,3);

		    f->SetParameters(norm3/10.0,norm3/2.0,0.3);
		    f->SetParNames("Const","IntFar","SigFar");
		    f->SetParLimits(0,0.0,1.0);
		    f->SetParLimits(1,0.0,1.0);
		    f->SetParLimits(2,0.0,3.0);
		    f->SetLineColor(2); f->SetLineWidth(2);
		    h->Fit("oneGaus","Q");
		    PAR0[i][j][JBEAM]=f->GetParameter(0);
		    PAR1[i][j][JBEAM]=f->GetParameter(1);
		    PAR2[i][j][JBEAM]=f->GetParameter(2);
		    ERR0[i][j][JBEAM]=f->GetParError(0);
		    ERR1[i][j][JBEAM]=f->GetParError(1);
		    ERR2[i][j][JBEAM]=f->GetParError(2);
		    int ndf=f->GetNDF();
		    if(ndf>0){
			CHI[i][j][JBEAM]=f->GetChisquare()/float(ndf);
		    }else{
			CHI[i][j][JBEAM]=-1.0;
		    }
		    printf("norm=%8.6f Int=%8.6f IntFar=%8.6f SigFar=%6.3f C=%8.6f Chi2=%8.6f\n",
			   norm3,PAR0[i][j][JBEAM]+PAR1[i][j][JBEAM],
			   PAR1[i][j][JBEAM],PAR2[i][j][JBEAM],PAR0[i][j][JBEAM],CHI[i][j][JBEAM]);
		    if(JBEAM==0 && cut==2){
			//plot("norm",20,16,0,0,i,j);//Xiaoxuan, why cut is 16 for Pythia6.4???????			
			//t=new TText(0.5,0.20,"Pythia6.4");
			//t->SetNDC(); t->SetTextSize(0.05); t->SetTextColor(3); t->Draw();		       
			readfile(OPT,run);
		    }
		    if(JBEAM==0 && cut==2 && bin1==3 && bin2==1){
			dihadron_theory(9,6,PAR0[i][j][JBEAM]/twoPI);
			t=new TText(0.43,0.15,"rcBK, pT1=2.0-2.5, pT2=1.0-1.5");
			t->SetNDC(); t->SetTextSize(0.05); t->SetTextColor(6); t->Draw();		       
		    }
		    if(JBEAM==0 && cut==2 && bin1==4 && bin2==2){
			dihadron_theory(10,6,PAR0[i][j][JBEAM]/twoPI);
			t=new TText(0.43,0.15,"rcBK, pT1=2.5-3.0, pT2=1.5-2.0");
			t->SetNDC(); t->SetTextSize(0.05); t->SetTextColor(6); t->Draw();
		    }
		    if(JBEAM==0 && cut==2 && bin1==5 && bin2==3){
			dihadron_theory(11,6,PAR0[i][j][JBEAM]/twoPI);
			t=new TText(0.43,0.15,"rcBK, pT1=3.0-10.0, pT2=2.0-2.5");
			t->SetNDC(); t->SetTextSize(0.05); t->SetTextColor(6); t->Draw();
		    }
		    if(JBEAM==2 && cut==16 && bin1==3 && bin2==1){
			//dihadron_theory(13,6,PAR0[i][j][JBEAM]/twoPI);
			dihadron_theory(13,6,0.01877/twoPI);
			t=new TText(0.43,0.15,"rcBK, pT1=2.0-2.5, pT2=1.0-1.5");
			t->SetNDC(); t->SetTextSize(0.05); t->SetTextColor(6); t->Draw();
		    }
		    if(JBEAM==2 && cut==16 && bin1==4 && bin2==2){ 
			dihadron_theory(14,6,PAR0[i][j][JBEAM]/twoPI);
			t=new TText(0.43,0.15,"rcBK, pT1=2.5-3.0, pT2=1.5-2.0");
			t->SetNDC(); t->SetTextSize(0.05); t->SetTextColor(6); t->Draw();
		    }
		    if(JBEAM==2 && cut==16 && bin1==5 && bin2==3){
			dihadron_theory(15,6,PAR0[i][j][JBEAM]/twoPI);
			t=new TText(0.43,0.15,"rcBK, pT1=3.0-10.0, pT2=2.0-2.5");
			t->SetNDC(); t->SetTextSize(0.05); t->SetTextColor(6); t->Draw();
		    }

		    if(JBEAM==2 && cut==2 && bin1==3 && bin2==1){
			dihadron_theory(2,4,PAR0[i][j][JBEAM]/twoPI);
			t=new TText(0.43,0.15,"GBW, pT1=2.0-2.5, pT2=1.0-1.5");
			t->SetNDC(); t->SetTextSize(0.05); t->SetTextColor(4); t->Draw();
		    }
		    if(JBEAM==2 && cut==2 && bin1==4 && bin2==2){ 
			dihadron_theory(3,4,PAR0[i][j][JBEAM]/twoPI);
			t=new TText(0.43,0.15,"GBW, pT1=2.5-3.0, pT2=1.5-2.0");
			t->SetNDC(); t->SetTextSize(0.05); t->SetTextColor(4); t->Draw();
		    }
		    if(JBEAM==2 && cut==2 && bin1==5 && bin2==3){
			dihadron_theory(4,4,PAR0[i][j][JBEAM]/twoPI);
			t=new TText(0.43,0.15,"GBW, pT1=3.0-4.0, pT2=2.0-2.5");
			t->SetNDC(); t->SetTextSize(0.05); t->SetTextColor(4); t->Draw();
		    }
/*
		    if(JBEAM==2 && cut==16 && bin1==3 && bin2==1){
			dihadron_theory(6,6);
			t=new TText(0.5,0.15,"Heikki Private Comm.");
			t->SetNDC(); t->SetTextSize(0.05); t->SetTextColor(6); t->Draw();
		    }
		    if(JBEAM==2 && cut==16 && bin1==4 && bin2==2){
			dihadron_theory(7,6);
			t=new TText(0.5,0.15,"Heikki Private Comm.");
			t->SetNDC(); t->SetTextSize(0.05); t->SetTextColor(6); t->Draw();
		    }
*/
		}
		if(fit==2){
		    f=new TF1("twoGaus",twoGaus,-PI/2.0,+PI*3.0/2.0,5);
		    f->SetParameters(norm3/10.0,norm3/2.0,0.12,norm3/2.0,0.3);
		    f->SetParNames("Const","IntFar","SigFar","IntNear","SigNear");
		    f->SetParLimits(0,0.0,1.0);
		    f->SetParLimits(1,0.0,1.0);
		    f->SetParLimits(2,0.0,3.0);
		    f->SetParLimits(3,0.0,1.0);
		    f->SetParLimits(4,0.0,3.0);
		    f->SetLineColor(4); f->SetLineWidth(1);
		    if(i==5&&j==2&&JBEAM==2&&cut==15){
		    f->SetParameter(0,0.003);
		    }
		    if(i==3&&j==2&&JBEAM==2&&cut==16){
		    f->SetParameter(0,0.003);
		    }
		    h->Fit("twoGaus","Q");
		    PAR0[i][j][JBEAM]=f->GetParameter(0);
		    ERR0[i][j][JBEAM]=f->GetParError(0);
		    PAR1[i][j][JBEAM]=f->GetParameter(1);
	            ERR1[i][j][JBEAM]=f->GetParError(1);
		    PAR2[i][j][JBEAM]=f->GetParameter(2);
                    ERR2[i][j][JBEAM]=f->GetParError(2);
		    PAR3[i][j][JBEAM]=f->GetParameter(3);
		    PAR4[i][j][JBEAM]=f->GetParameter(4);
                    int ndf=f->GetNDF();
                    if(ndf>0){
                        CHI[i][j][JBEAM]=f->GetChisquare()/float(ndf);
                    }else{
                        CHI[i][j][JBEAM]=-1.0;
                    }
		    printf("norm=%8.6f Int=%8.6f IntNear=%8.6f IntFar=%8.6f SigNear=%6.3f  SigFar=%6.3f C=%8.6f,Chi2=%8.6f\n",
			   norm3,PAR1[i][j][JBEAM]+PAR3[i][j][JBEAM]+PAR0[i][j][JBEAM],
			   PAR3[i][j][JBEAM],PAR1[i][j][JBEAM],
			   PAR4[i][j][JBEAM],PAR2[i][j][JBEAM],
			   PAR0[i][j][JBEAM],CHI[i][j][JBEAM]);
		}
	    }//if(v=="norm" || v=="corr")

	    float xx=0.70, yy=0.85, dy=0.04, size=0.04;
	    int col=1;
	    //if(bin1<0){xx=0.15, yy=0.80, dy=0.08, size=0.08;}
	    if(bin1<0){xx=0.50, yy=0.80, dy=0.09, size=0.09;}
	    if(v=="z12" || v=="bbce") {xx=0.15; yy=0.3;}
	    if(v=="m0" || v=="m1" || v=="m2") {xx=0.6; yy=0.8;}
	    if(cvs){		
		if(QM<2){
		    //t = new TText(xx, yy-3*dy,    Form("pT1=%3.1f-%3.1f",ptcut[i],ptcut[i+1])); t->SetNDC(); t->SetTextSize(size); t->Draw();
		    drawLatex(xx, yy-4*dy, Form("p_{T1}=%3.1f-%3.1f GeV",ptcut[i],ptcut[i+1]), 42,size,1);
	 	    drawLatex(xx, yy-5*dy, Form("p_{T2}=%3.1f-%3.1f GeV",ptcut[j],ptcut[j+1]), 42,size,1);
		    //t = new TText(xx, yy-4*dy, Form("pT2=%3.1f-%3.1f",ptcut[j],ptcut[j+1])); t->SetNDC(); t->SetTextSize(size); t->Draw();
		}else if(QM==2){
		    t = new TText(xx, yy,    Form("Example pT bin")); t->SetNDC(); t->SetTextSize(size); t->Draw();
		}		
	    }
	    if(bin1<0 && cvs)  {xx=0.5, yy=0.70+dy*2; size=0.08;}
	    if(!cvs)           {dy=0.08; xx=0.5, yy=0.80+dy; size=0.08; col=4;}
	    if(v=="bbce"){
		t = new TText(xx, yy-dy*2, Form("<bbce>=%7.0f",h->GetMean())); t->SetNDC(); t->SetTextSize(size); 
		t->SetTextColor(col); t->Draw();
	    }
	    if(v=="eta1" || v=="eta2"){
		t = new TText(xx, yy-dy*2, Form("<eta>=%7.2f",h->GetMean())); t->SetNDC(); t->SetTextSize(size); t->Draw();
	    }
	    if(v=="m2" && cut==19){
		t=new TText(0.6,0.35,"Top");    t->SetNDC(); t->SetTextSize(0.1); t->SetTextColor(1); t->Draw();
		t=new TText(0.6,0.25,"Bottom"); t->SetNDC(); t->SetTextSize(0.1); t->SetTextColor(4); t->Draw();
		t=new TText(0.6,0.15,Form("T/B=%4.2f",NNN)); t->SetNDC(); t->SetTextSize(0.1); t->SetTextColor(1); t->Draw();	       
	    }
	    if(v=="norm" || v=="corr" || v=="dphi"){
		if(bin1<0){
		    float y=h->GetMaximum()*0.08;		
		    //t=new TLatex(-PI/2.0, -y,"#pi/2");  t->SetTextAlign(22);t->SetTextSize(0.1); t->Draw();
		    t=new TLatex(0.0,      -y,"0.0");    t->SetTextAlign(22); t->SetTextSize(0.1); t->Draw();
		    t=new TLatex(PI/2.0,   -y,"#pi/2");  t->SetTextAlign(22); t->SetTextSize(0.1); t->Draw();
		    t=new TLatex(PI,      -y,"#pi");    t->SetTextAlign(22); t->SetTextSize(0.1); t->Draw();
		    //t=new TLatex(3*PI/2.0,-y,"3#pi/2"); t->SetTextAlign(22); t->SetTextSize(0.1); t->Draw();
		}else{
		    float y=h->GetMaximum()*0.04;		
		    t=new TLatex(-PI/2.0,  -y,"-#pi/2"); t->SetTextAlign(22); t->SetTextSize(0.06); t->Draw();
		    t=new TLatex(0.0,      -y,"0.0");    t->SetTextAlign(22); t->SetTextSize(0.06); t->Draw();
		    t=new TLatex(PI/2.0,   -y,"#pi/2");  t->SetTextAlign(22); t->SetTextSize(0.06); t->Draw();
		    t=new TLatex(PI,       -y,"#pi");    t->SetTextAlign(22); t->SetTextSize(0.06); t->Draw();
		    t=new TLatex(3*PI/2.0, -y,"3#pi/2"); t->SetTextAlign(22); t->SetTextSize(0.06); t->Draw();
		}		
		if(norm3>0.0 && cvs && QM==0){
		    //t = new TText(xx, yy-dy*2, Form("P=%7.5f",norm3)); t->SetNDC(); t->SetTextSize(size); t->Draw();
		}
		if(fit==1 && cvs){
		    t = new TText(xx, yy-dy*3, Form("PBg=%7.5f",  PAR0[i][j][JBEAM])); t->SetNDC(); t->SetTextSize(size); t->Draw();
		    t = new TText(xx, yy-dy*4, Form("Paway=%7.5f",PAR1[i][j][JBEAM])); t->SetNDC(); t->SetTextSize(size); t->Draw();
		    t = new TText(xx, yy-dy*5, Form("Saway=%4.2f",PAR2[i][j][JBEAM])); t->SetNDC(); t->SetTextSize(size); t->Draw();
		}
		if(fit==2){
		    //t = new TText(xx, yy-dy*3, Form("Pnear=%7.5f",PAR3[i][j][JBEAM])); t->SetNDC(); t->SetTextSize(size); t->Draw();
		    //t = new TText(xx, yy-dy*3, Form("Area=%7.5f#pm%7.5f",PAR1[i][j][JBEAM],ERR1[i][j][JBEAM])); t->SetNDC(); t->SetTextSize(size); t->Draw();
		    drawLatex(xx-0.25, yy-dy, Form("               Area=%7.5f#pm%7.5f",PAR1[i][j][JBEAM],ERR1[i][j][JBEAM]), 42, size, 1);
		    drawLatex(xx-0.25, yy-dy*2, Form("              Width=%4.2f#pm%4.2f",PAR2[i][j][JBEAM],ERR2[i][j][JBEAM]), 42, size, 1);
		    drawLatex(xx-0.25, yy-dy*3, Form("         Pedestal=%7.5f#pm%7.5f",PAR0[i][j][JBEAM],ERR0[i][j][JBEAM]), 42, size, 1);
		    //t = new TText(xx, yy-dy*5, Form("Bkg=%7.5f#pm%7.5f",  PAR0[i][j][JBEAM],ERR0[i][j][JBEAM])); t->SetNDC(); t->SetTextSize(size); t->Draw();
		    //t = new TText(xx, yy-dy*6, Form("Snear=%4.2f",PAR4[i][j][JBEAM])); t->SetNDC(); t->SetTextSize(size); t->Draw();
		    //t = new TText(xx, yy-dy*4, Form("Width=%4.2f#pm%7.5f",PAR2[i][j][JBEAM],ERR2[i][j][JBEAM])); t->SetNDC(); t->SetTextSize(size); t->Draw();
		}
		if(bin1>=0 && cut!=18 && cut!=19 && QM==0){
		    //t = new TText(0.15, 0.75,"Uncorrected");      t->SetNDC(); t->SetTextSize(0.05); t->SetTextColor(4); t->Draw();
		    t = new TText(0.15, 0.70,"Data");        t->SetNDC(); t->SetTextSize(0.05); t->SetTextColor(1); t->Draw();
		    t = new TText(0.15, 0.65,"Fit"); t->SetNDC(); t->SetTextSize(0.05); t->SetTextColor(4); t->Draw();
		}
		if(cut==18){
		    //t=new TText(0.15,0.25,"top");    t->SetNDC(); t->SetTextSize(0.05); t->SetTextColor(1); t->Draw();		       
		    //t=new TText(0.15,0.20,"bottom"); t->SetNDC(); t->SetTextSize(0.05); t->SetTextColor(4); t->Draw();		       
		}
	    }
	    if(cut==88) h->SetLineColor(2);
	    if(cut==99 && (v=="m1"|| v=="m2")){
		sprintf(c,"%s_%1d%1d_c%d",v,i,j,1);
		h = (TH1F*)mTFile->Get(c);
		h->SetLineColor(4);
		h->Draw("same");
		sprintf(c,"%s_%1d%1d_c%d",v,i,j,2);
		h = (TH1F*)mTFile->Get(c);
		h->SetLineColor(2);
		h->Draw("same");
	    }
	    if(cut==99 && v=="dphi"){
		h->SetLineColor(4);
		sprintf(c,"%s_%1d%1d_c%d",v,i,j,2);
                h = (TH1F*)mTFile->Get(c);
                h->SetLineColor(2);
                h->Draw("same");		
	    }
	    if(cvs && bin1>=0){
		if(QM==0){
		    t = new TText(0.2, 0.92,Form("%s %s",CBEAM,CCUT[JBEAM][cut])); 
		    t->SetNDC(); t->SetTextSize(0.07); t->SetTextColor(1); t->Draw();
		}else{
		    t = new TText(0.2, 0.92,Form("Run15 pAu Uncorrected Raw")); 
		    t->SetNDC(); t->SetTextSize(0.07); t->SetTextColor(1); t->Draw();
		}
		if     (run==1 || run==11) {sprintf(c,"plot/dipi0_pp_%s_c%d_bin%d%d.png",v,cut,i,j);}
		else if(run==5 || run==15) {sprintf(c,"plot/pAu/dipi0_pau_%s_c%d_bin%d%d.png",v,cut,i,j);}
		else if(run==2 || run==12) {sprintf(c,"plot/dipi0_pau2_%s_c%d_bin%d%d.png",v,cut,i,j);}
		else if(run==3 || run==13) {sprintf(c,"plot/dipi0_pal_%s_c%d_bin%d%d.png",v,cut,i,j);}
		else                       {sprintf(c,"plot/dipi0_%d_%s_c%d_bin%d%d.png",run,v,cut,i,j);}
		printf("Saving %s\n",c);
		cvs->SaveAs(c);	       
	    }
	}
    }
    if(cvs && bin1<0 && QM==0){
	cvs->cd(12);
	//t = new TText(0.1, 0.88 ,"STAR Preliminary"); t->SetNDC(); t->SetTextSize(0.16);t->SetTextColor(2); t->Draw();
	t = new TText(0.0, 0.70,Form("%s %s",CBEAM,CCUT[JBEAM][cut])); t->SetNDC(); t->SetTextSize(0.14); t->SetTextColor(1); t->Draw();
	cvs->cd(25);
	drawLatex(0.67, 0.90, "#Delta#phi [rad]", 42,0.14,1);
	cvs->cd(1);
	t = new TText(0.99, 0.05 ,"Coincidence Probability"); t->SetNDC(); t->SetTextSize(0.085);t->SetTextAngle(90);t->Draw();
    }
    if(v=="mall"){
	t = new TText(0.05, 0.65,"M1(no mass cut, scaled)"); t->SetNDC(); t->SetTextSize(0.10); t->SetTextColor(1); t->Draw();
	t = new TText(0.05, 0.55,"M1(without M2)/P"); t->SetNDC(); t->SetTextSize(0.10); t->SetTextColor(6); t->Draw();
	t = new TText(0.05, 0.45,"M1(with M2)"); t->SetNDC(); t->SetTextSize(0.10); t->SetTextColor(2); t->Draw();
	t = new TText(0.05, 0.35,"M2"); t->SetNDC(); t->SetTextSize(0.10); t->SetTextColor(4); t->Draw();
    }
    if(v=="z12"){
	t = new TText(0.05, 0.65,"Zgg1"); t->SetNDC(); t->SetTextSize(0.10); t->SetTextColor(2); t->Draw();
	t = new TText(0.05, 0.55,"Zgg2"); t->SetNDC(); t->SetTextSize(0.10); t->SetTextColor(4); t->Draw();
    }
    if(v=="phiall"){
	t = new TText(0.05, 0.65,"Phi0"); t->SetNDC(); t->SetTextSize(0.10); t->SetTextColor(1); t->Draw();
	t = new TText(0.05, 0.55,"Phi1"); t->SetNDC(); t->SetTextSize(0.10); t->SetTextColor(2); t->Draw();
	t = new TText(0.05, 0.45,"Phi2"); t->SetNDC(); t->SetTextSize(0.10); t->SetTextColor(4); t->Draw();
    }
    if(v=="mix"){
	//t = new TText(0.05, 0.65,"Mix0=Phi0*Phi0");  t->SetNDC(); t->SetTextSize(0.10); t->SetTextColor(1); t->Draw();
	t = new TText(0.05, 0.55,"Mix12=Phi1*Phi2"); t->SetNDC(); t->SetTextSize(0.10); t->SetTextColor(2); t->Draw();
    }
    if(v=="corr"){
	if(bin1<0){
	    //t = new TText(0.25, 0.65,"Uncorrected");      t->SetNDC(); t->SetTextSize(0.10); t->SetTextColor(4); t->Draw();
	    //t = new TText(0.2, 0.55,"Data");        t->SetNDC(); t->SetTextSize(0.12); t->SetTextColor(1); t->Draw();
	    //t = new TText(0.2, 0.42,"Fit"); t->SetNDC(); t->SetTextSize(0.12); t->SetTextColor(4); t->Draw();
	    cvs->cd(12);
	    TLegend *leg = new TLegend(0.2,0.1,0.75,0.62);
	    leg->AddEntry(h, "Data","p");
	    leg->AddEntry(f, "Fit","l");
	    leg->SetLineColor(0);
	    leg->SetFillStyle(0);
	    leg->Draw("same");
	}
    }
    if(cut==99) {
	t = new TText(0.0, 0.65, "Inclusive Pair");  t->SetNDC(); t->SetTextSize(0.12); t->SetTextColor(4); t->Draw();
	t = new TText(0.0, 0.45, "Exclusive Pair");  t->SetNDC(); t->SetTextSize(0.12); t->SetTextColor(2); t->Draw();
    }
    if(cvs && bin1<0){
	if     (run==1 || run==11) {sprintf(c,"plot/dipi0_pp_%s_c%d.png",v,cut);}
	else if(run==5 || run==15) {sprintf(c,"plot/dipi0_pau_%s_c%d.png",v,cut);}
	else if(run==2 || run==12) {sprintf(c,"plot/dipi0_pau2_%s_c%d.png",v,cut);}
	else if(run==3 || run==13) {sprintf(c,"plot/dipi0_pal_%s_c%d.png",v,cut);}
	else                       {sprintf(c,"plot/dipi0_%d_%s_c%d.png",run,v,cut);}
	printf("Saving %s\n",c);
	cvs->SaveAs(c);
    }
    if(v=="norm" && fit>0 && bin1<0) writepar(cut,0);
    if(v=="corr" && fit>0 && bin1<0) writepar(cut,1);
}
 
void plotphi_proj(int v=0, TCanvas* cvs){
    const char* tit[5]={"Mass0","Mass1","Mass2","Ene","pT"};
    const char* ctit[5]={"Mass pt>0.5GeV",
			 "Mass pt>1.5GeV",
			 "Mass E>30GeV",
			 "E  0.07<mass<0.2GeV",
			 "pT 0.07<mass<0.2GeV"};
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(0);
    cvs->Clear();
    cvs->Divide(2,3);
    //cvs->Divide(2,1);
    int bb[3]={11,13,12};
    int cc=1;
    for(int b=0; b<3; b++){
	readfile(OPT,bb[b]);
	TH2F* h2=(TH2F*)mTFile->Get(tit[v]);
	for(int ls=0; ls<2; ls++){
	    float max=0.0;
	    int imax=0;
	    TH1D *h[4];
	    for(int i=0; i<4; i++){
		int pp=ls*8+i*2+1;
		h[i]=h2->ProjectionX(Form("%d_%s_%d",bb[b],tit[v],pp),pp,pp+1);		
		h[i]->SetLineColor(i+1);
		//h->Scale(1.0/h->GetEntries());
		float m=h[i]->GetMaximum();
		if(m>max) {max=m; imax=i;}
	    }
	    char* CQ[4]={"Q1(ST)","Q3(NT)","Q4(NB)","Q2(SB)"};
	    for(int i=0; i<4; i++){
		if(i==0) {
		    if(v<3) cvs->cd(cc); 		    
		    if(v>=3) cvs->cd(cc)->SetLogy(); 		    
		    h[i]->SetMaximum(max*1.1);
		    h[i]->SetTitle(ctit[v]);
		    h[i]->Draw();
		    cc++;
		    //   t=new TText(0.5,0.80,"Q1 (ST)"); t->SetTextColor(1); t->SetNDC(); t->Draw();
		    //t=new TText(0.5,0.74,"Q3 (NT)"); t->SetTextColor(2); t->SetNDC(); t->Draw();
		    //t=new TText(0.5,0.68,"Q4 (NB)"); t->SetTextColor(3); t->SetNDC(); t->Draw();
		    //t=new TText(0.5,0.62,"Q2 (SB)"); t->SetTextColor(4); t->SetNDC(); t->Draw();
		    TText *t=new TText(0.4,0.92,Form("%s %s",CBEAM,CLS[ls])); t->SetNDC(); t->Draw();
		} else {
		    h[i]->Draw("same");
		}
		if(1){
		    TF1* fpi0 = new TF1("fpi0",pi0fcn,0.07,0.18,3);
		    fpi0->SetLineColor(i+1);
		    fpi0->SetParameter(0,0.135);
		    fpi0->SetParameter(1,0.01);
		    fpi0->SetParameter(2,h[i]->GetMaximum()/100.0);
		    TFitResultPtr fitresult0 = h[i]->Fit("fpi0","SR+");
		    printf("max=%f p2=%f R=%f\n",h[i]->GetMaximum(),fpi0->GetParameter(2),h[i]->GetMaximum()/fpi0->GetParameter(2));
		    /*
		    TF1* fall = new TF1("fall",fitFcn,0.01,0.3,8);
		    fall->SetLineColor(i+1);
		    fall->SetParameter(0,fpi0->GetParameter(0));
		    fall->SetParameter(1,fpi0->GetParameter(1));
		    fall->SetParameter(2,fpi0->GetParameter(2));
		    fall->SetParameter(4,0.0);
		    fall->SetParameter(5,0.0);
		    fall->SetParameter(6,0.0);
		    fall->SetParameter(7,0.0);
		    fall->SetParameter(8,0.0); 
		    TFitResultPtr fitresult = h[i]->Fit("fall","SR+");		    
		    */
		    TText* t=new TText(0.5,0.8-0.06*float(i),Form("%s %4.3f",CQ[i],fpi0->GetParameter(0))); 
		    t->SetTextColor(i+1); t->SetNDC(); t->Draw();
		}else{
		    TText* t=new TText(0.5,0.8-0.06*float(i),CQ[i]); 
		    t->SetTextColor(i+1); t->SetNDC(); t->Draw();
		}
	    }			
	}
    }
    cvs->SaveAs(Form("plot/%s_phiproj.png",tit[v]));
}

void plotphi_axis(int v=0){
    const char* tit[5]={"Mass0","Mass1","Mass2","Ene","pT"};
    const char* ctit[5]={"Mass pt>0.5GeV",
			 "Mass pt>1.5GeV",
			 "Mass E>30GeV",
			 "E  0.07<mass<0.2GeV",
			 "pT 0.07<mass<0.2GeV"};
    TH2F* h=(TH2F*)mTFile->Get(tit[v]); 
    h->SetTitle(ctit[v]);
    TAxis* a=h->GetYaxis();
    a->SetBinLabel(1,"Q1(ST)Lg");
    a->SetBinLabel(2,"Q1(ST)Lg");
    a->SetBinLabel(3,"Q3(NT)Lg");
    a->SetBinLabel(4,"Q3(NT)Lg");
    a->SetBinLabel(5,"Q4(NB)Lg");
    a->SetBinLabel(6,"Q4(NB)Lg");
    a->SetBinLabel(7,"Q2(SB)Lg");
    a->SetBinLabel(8,"Q2(SB)Lg");
    a->SetBinLabel(9, "Q1(ST)Sm");
    a->SetBinLabel(10,"Q1(ST)Sm");
    a->SetBinLabel(11,"Q3(NT)Sm");
    a->SetBinLabel(12,"Q3(NT)Sm");
    a->SetBinLabel(13,"Q4(NB)Sm");
    a->SetBinLabel(14,"Q4(NB)Sm");
    a->SetBinLabel(15,"Q2(SB)Sm");
    a->SetBinLabel(16,"Q2(SB)Sm");
    a->SetLabelSize(0.07);
    h->Draw("colz");
    TText* t=new TText(0.8,0.91,Form("%s",CBEAM)); 
    t->SetNDC(); t->Draw();
}
void plotphi(){
    gStyle->SetOptStat(0);
    TH2F *h;    
    c1->Divide(1,3);
    c1->cd(1)->SetLogz(0); readfile(OPT,11); plotphi_axis(0); 
    c1->cd(2)->SetLogz(0); readfile(OPT,13); plotphi_axis(0); 
    c1->cd(3)->SetLogz(0); readfile(OPT,12); plotphi_axis(0); 
    c1->SaveAs("plot/mass0_phi.png");

    c1->Clear();
    c1->Divide(1,3);
    c1->cd(1)->SetLogz(0); readfile(OPT,11); plotphi_axis(1); 
    c1->cd(2)->SetLogz(0); readfile(OPT,13); plotphi_axis(1); 
    c1->cd(3)->SetLogz(0); readfile(OPT,12); plotphi_axis(1); 
    c1->SaveAs("plot/mass1_phi.png");

    c1->Clear();
    c1->Divide(1,3);
    c1->cd(1)->SetLogz(0); readfile(OPT,11); plotphi_axis(2);
    c1->cd(2)->SetLogz(0); readfile(OPT,13); plotphi_axis(2);
    c1->cd(3)->SetLogz(0); readfile(OPT,12); plotphi_axis(2);
    c1->SaveAs("plot/mass2_phi.png");

    c2->Divide(1,3);
    c2->cd(1)->SetLogz(1); readfile(OPT,11); plotphi_axis(3);
    c2->cd(2)->SetLogz(1); readfile(OPT,13); plotphi_axis(3);
    c2->cd(3)->SetLogz(1); readfile(OPT,12); plotphi_axis(3);
    c2->SaveAs("plot/ene_phi.png");

    c3->Divide(1,3);
    c3->cd(1)->SetLogz(1); readfile(OPT,11); plotphi_axis(4);
    c3->cd(2)->SetLogz(1); readfile(OPT,13); plotphi_axis(4);
    c3->cd(3)->SetLogz(1); readfile(OPT,12); plotphi_axis(4);
    c3->SaveAs("plot/pt_phi.png");
}

void writepar(int cut, int corr){
    char name[200];
    sprintf(name,"txt/beam%d_cut%d_corr%d.par",IBEAM,cut,corr);
    FILE* f=fopen(name,"w");
    for(int i=1;i<kNPtBin; i++){
	for(int j=1; j<i; j++){
	    fprintf(f,"%12.8f %12.8f %12.8f %12.8f %12.8f %12.8f %12.8f\n",
		    PAR0[i][j][JBEAM],PAR1[i][j][JBEAM],PAR2[i][j][JBEAM], 
		    ERR0[i][j][JBEAM],ERR1[i][j][JBEAM],ERR2[i][j][JBEAM],CHI[i][j][JBEAM]);
	   
	    /*fprintf(f,"%12.8f %12.8f %12.8f %d\n",
		    ((TH1F*)mTFile->Get(Form("pt1_%1d%1d_c%d",i,j,cut)))->GetMean(),
		    ((TH1F*)mTFile->Get(Form("pt2_%1d%1d_c%d",i,j,cut)))->GetMean(),
		    ((TH1F*)mTFile->Get(Form("bbce_%1d%1d_c%d",i,j,cut)))->GetMean(),
		    ((TH1F*)mTFile->Get(Form("pt1_%1d%1d_c%d",i,j,cut)))->GetEntries() ); 
*/
	}
    }
    fclose(f);    
    printf("Created %s\n",name);
}

void readpar(int beam=0, int cut, int corr, int print=1){
    char name[200];
    sprintf(name,"txt/beam%d_cut%d_corr%d.par",beam,cut,corr);
    if(print>0) printf("Reading %s\n",name);
    FILE* f=fopen(name,"r"); 
    for(int i=1;i<kNPtBin; i++){
	for(int j=1; j<i; j++){
	    fscanf(f,"%f %f %f %f %f %f %f\n",
		   &(PAR0[i][j][beam]),&(PAR1[i][j][beam]),&(PAR2[i][j][beam]),
		   &(ERR0[i][j][beam]),&(ERR1[i][j][beam]),&(ERR2[i][j][beam]),&(CHI[i][j][beam]));
	    /*fscanf(f,"%f %f %f %d\n",
		   &(PT1[i][j][beam]),&(PT2[i][j][beam]),&(BBC[i][j][beam]),&(NEV[i][j][beam]));*/
	    if(i>0 && j>0 && print>1)
		printf("%1d %1d %10.6f %10.6f %10.6f %10.6f %10.6f %10.6f %10.6f %10.6f %10.6f %6.0f %d\n",
		       i,j,
		       PAR0[i][j][beam],PAR1[i][j][beam],PAR2[i][j][beam],
		       ERR0[i][j][beam],ERR1[i][j][beam],ERR2[i][j][beam],CHI[i][j][beam]);
		       //PT1[i][j][beam],PT2[i][j][beam],BBC[i][j][beam], NEV[i][j][beam]); 
	}
    }
    fclose(f);    
}

TGraphErrors* sumpt(int beam, int cut, int sel, int par, int color, int type, const char* opt, int norm=0){
    if(norm) readpar(0,cut,1);    
    readpar(beam,cut,1);    
    TGraphErrors* g = new TGraphErrors();
    g->SetLineColor(color);
    g->SetMarkerColor(color);
    g->SetMarkerStyle(type);
    int k=0;
    for(int i=1; i<kNPtBin; i++){ 	
	for(int j=1; j<=i; j++){ 
	    if(sel==0 && (i-j)!=2) continue;
	    float p,e,n;
	    switch(par){
	    case 0: p=PAR0[i][j][beam]; e=ERR0[i][j][beam]; n=PAR0[i][j][0]; break;
	    case 1: p=PAR1[i][j][beam]; e=ERR1[i][j][beam]; n=PAR1[i][j][0]; break;
	    case 2: p=PAR2[i][j][beam]; e=ERR2[i][j][beam]; n=PAR2[i][j][0]; break;
	    case 3: p=PAR3[i][j][beam]; e=ERR3[i][j][beam]; n=PAR3[i][j][0]; break;
	    case 4: p=PAR4[i][j][beam]; e=ERR4[i][j][beam]; n=PAR4[i][j][0]; break;
	    }
	    if(norm==0){
		g->SetPoint(k, PT2[i][j][beam], p);
		g->SetPointError(k, 0.25, e);
	    }else{
		g->SetPoint(k, PT2[i][j][beam], p/n);
		g->SetPointError(k, 0.25, e/n);
	    }
	    k++;
	}
    }
    g->Draw(opt);
    return g;
}

TGraphErrors* sumbbc(int corr, int beam, int bin1, int bin2, int par, int color, int type, const char* opt){
    static const int NBBC=4;
    int cuts[NBBC]={4,5,15,16};
    int BBC[NBBC]={3000,12000,24000,36000};//Xiaoxuan
    TGraphErrors* g = new TGraphErrors();
    g->SetLineColor(color);
    g->SetMarkerColor(color);
    g->SetMarkerStyle(type);
    int k=0;
    for(int i=0; i<NBBC; i++){ 	
	readpar(beam,cuts[i],corr);    
	//if(NEV[bin1][bin2][beam]>MINEVT){
	    float p,e;
	    switch(par){
	    case 0: p=PAR0[bin1][bin2][beam]; e=ERR0[bin1][bin2][beam]; break;
	    case 1: p=PAR1[bin1][bin2][beam]; e=ERR1[bin1][bin2][beam]; break;
	    case 2: p=PAR2[bin1][bin2][beam]; e=ERR2[bin1][bin2][beam]; break;
	    case 3: p=PAR3[bin1][bin2][beam]; e=ERR3[bin1][bin2][beam]; break;
	    case 4: p=PAR4[bin1][bin2][beam]; e=ERR4[bin1][bin2][beam]; break;
	    }
	    cout << Form("Beam=%1d bin1=%1d bin2=%1d cut=%2dcorr=%1d par=%1d %10.6f +- %10.6f N=%d\n",
			 beam,bin1,bin2,cuts[i],corr,par,p,e,NEV[bin1][bin2]);
	    g->SetPoint(k, BBC[k], p);
	    g->SetPointError(k, 0.0, e);
	    k++;
	//}
    }
    g->Draw(opt);
    return g;
}

TGraphErrors* sumtrg(int corr, int beam, int bin1, int bin2, int par, int color, int type, const char* opt){
    static const int NTRG=3;
    int cuts[NTRG]={21,23,24};
    TGraphErrors* g = new TGraphErrors();
    g->SetLineColor(color);
    g->SetMarkerColor(color);
    g->SetMarkerStyle(type);
    int k=0;
    for(int i=0; i<NTRG; i++){ 	
	readpar(beam,cuts[i],corr);    
	//if(NEV[bin1][bin2][beam]>MINEVT){
	    float p,e;
	    switch(par){
	    case 0: p=PAR0[bin1][bin2][beam]; e=ERR0[bin1][bin2][beam]; break;
	    case 1: p=PAR1[bin1][bin2][beam]; e=ERR1[bin1][bin2][beam]; break;
	    case 2: p=PAR2[bin1][bin2][beam]; e=ERR2[bin1][bin2][beam]; break;
	    case 3: p=PAR3[bin1][bin2][beam]; e=ERR3[bin1][bin2][beam]; break;
	    case 4: p=PAR4[bin1][bin2][beam]; e=ERR4[bin1][bin2][beam]; break;
	    }
	    cout << Form("Beam=%1d bin1=%1d bin2=%1d cut=%2dcorr=%1d par=%1d %10.6f +- %10.6f N=%d\n",
			 beam,bin1,bin2,cuts[i],corr,par,p,e,NEV[bin1][bin2]);
	    g->SetPoint(k, cuts[k], p);
	    g->SetPointError(k, 0.0, e);
	    k++;
	//}
    }
    g->Draw(opt);
    return g;
}

TText* chi2(int beam, int corr, int color, char* opt, float x, float y){
    //static const int NBBC=5;
    //int cuts[NBBC]={2,4,5,15,16};
    static const int NBBC=1;
    int cuts[NBBC]={2};
    //int cuts[NBBC]={20,21,22,23,24,25};
    char name[200];    
    sprintf(name,"chi2_beam%d_corr%d",beam,corr);
    TH1F* h = new TH1F(name,name,32,0.0,10.0);
    h->SetLineWidth(2);
    h->SetLineColor(color);
    for(int i=0; i<NBBC; i++){ 	
	readpar(beam,cuts[i],corr);    
	for(int bin1=1; bin1<kNPtBin; bin1++){
	    for(int bin2=1; bin2<bin1; bin2++){
		//if(NEV[bin1][bin2]>MINEVT){
		    h->Fill(CHI[bin1][bin2][beam]);
		    cout<<" bin1 "<<bin1<<" bin2 "<<bin2<<" CHI "<<CHI[bin1][bin2][beam]<<endl;
		//}
	    }
	}
    }    
    TText* tb;
    if(beam==0) tb = new TText(0.8,0.8,"pp"); 
    if(beam==1) tb = new TText(0.8,0.8,"pAl"); 
    if(beam==2) tb = new TText(0.8,0.8,"pAu2"); 
    if(beam==3) tb = new TText(0.8,0.8,"pAu");
    tb->SetNDC(); tb->SetTextSize(0.1); tb->Draw();
    if(corr==0){
	TText* t=new TText(x,y,Form("Uncorrected  Mean Chi2/ndf=%4.2f",h->GetMean()));
    }else{
	TText* t=new TText(x,y,Form("Corrected      Mean Chi2/ndf=%4.2f",h->GetMean()));
    }
    t->SetTextColor(color); t->SetNDC(); t->SetTextSize(0.1); t->Draw();
    h->Draw(opt);
    return t;
}

void summarychi2(){
    gStyle->SetOptStat(0);

    c1->Divide(1,3);
    TText* t;
    c1->cd(1);
/*
    t=chi2(0,0,1,""    ,0.4,0.7); t->Draw();
    t=chi2(0,1,2,"same",0.4,0.6); t->Draw();
    c1->cd(2);
    t=chi2(1,0,1,""    ,0.4,0.7); t->Draw();
    t=chi2(1,1,2,"same",0.4,0.6); t->Draw();
    c1->cd(3);
    t=chi2(2,1,2,""    ,0.4,0.7); t->Draw();
    t=chi2(2,0,1,"same",0.4,0.6); t->Draw();
*/
    //t=chi2(3,1,1,""    ,0.4,0.7); t->Draw(); 
    //t=chi2(0,1,1,""    ,0.4,0.7); t->Draw();
    t=chi2(1,1,1,""    ,0.4,0.7); t->Draw();
    c1->SaveAs("plot/summary_chi2_pAl_c2.png");
}

void summary1(int plt=0){
    TGraphErrors* g;
    c1->Divide(3,1);

    c1->cd(1)->SetLogy(1);
    TH2F* frame1=new TH2F("frame1","",1,0.0,3.0,1,0.0002,0.05); frame1->Draw();
    g=sumpt(0, 2,plt,0,1,20,"LP");
    g=sumpt(1, 2,plt,0,4,21,"LP");
    g=sumpt(2, 4,plt,0,7,22,"LP");
    g=sumpt(2, 5,plt,0,8,22,"LP");
    g=sumpt(2,15,plt,0,6,22,"LP");
    g=sumpt(2,16,plt,0,2,23,"LP");

    c1->cd(2)->SetLogy(1);
    TH2F* frame2=new TH2F("frame2","",1,0.0,3.0,1,0.00002,0.01); frame2->Draw();
    g=sumpt(0, 2,plt,1,1,20,"LP");
    g=sumpt(1, 2,plt,1,4,21,"LP");
    g=sumpt(2, 4,plt,1,7,22,"LP");
    g=sumpt(2, 5,plt,1,8,22,"LP");
    g=sumpt(2,15,plt,1,6,22,"LP");
    g=sumpt(2,16,plt,1,2,23,"LP");

    c1->cd(3)->SetLogy(0);
    TH2F* frame3=new TH2F("frame3","",1,0.0,3.0,1,0.0,1.0); frame3->Draw();
    g=sumpt(0, 2,plt,2,1,20,"LP");
    g=sumpt(1, 2,plt,2,4,21,"LP");
    g=sumpt(2, 4,plt,2,7,22,"LP");
    g=sumpt(2, 5,plt,2,8,22,"LP");
    g=sumpt(2,15,plt,2,6,22,"LP");
    g=sumpt(2,16,plt,2,2,23,"LP");
}

void summary1n(int plt=0){
    TGraphErrors* g;
    c1->Divide(3,1);

    c1->cd(1)->SetLogy(0);
    TH2F* frame1=new TH2F("frame1","",1,0.5,2.5,1,0.0,3.0); frame1->Draw();
    g=sumpt(1, 2,plt,0,4,21,"LP",1);
    g=sumpt(2, 4,plt,0,7,22,"LP",1);
    //    g=sumpt(2, 5,plt,0,8,22,"LP",1);
    //g=sumpt(2,15,plt,0,6,22,"LP",1);
    g=sumpt(2,16,plt,0,2,23,"LP",1);

    c1->cd(2)->SetLogy(0);
    TH2F* frame2=new TH2F("frame2","",1,0.5,2.5,1,0.0,3.0); frame2->Draw();
    g=sumpt(1, 2,plt,1,4,21,"LP",1);
    g=sumpt(2, 4,plt,1,7,22,"LP",1);
    //g=sumpt(2, 5,plt,1,8,22,"LP",1);
    //g=sumpt(2,15,plt,1,6,22,"LP",1);
    g=sumpt(2,16,plt,1,2,23,"LP",1);

    c1->cd(3)->SetLogy(0);
    TH2F* frame3=new TH2F("frame3","",1,0.5,2.5,1,0.0,3.0); frame3->Draw();
    g=sumpt(1, 2,plt,2,4,21,"LP",1);
    g=sumpt(2, 4,plt,2,7,22,"LP",1);
    //g=sumpt(2, 5,plt,2,8,22,"LP",1);
    //g=sumpt(2,15,plt,2,6,22,"LP",1);
    g=sumpt(2,16,plt,2,2,23,"LP",1);
}

void summarytrg(int corr=1, int bin1=2, int bin2=1, float maxb=0.1, float maxs=0.1, TCanvas* cvs){
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(1);
    TGraphErrors* g;
    TH2F* frame;
    cvs->Divide(1,3);

    cvs->cd(1)->SetLogy(0);    
    frame = new TH2F("P_constant","",1,19,26,1,0.0,maxb); 
    frame->GetXaxis()->SetLabelSize(0);
    frame->Draw();
    g=sumtrg(corr,3, bin1, bin2, 0, 1, 22, "LP");
    TText* t;
    t= new TLatex(0.75,0.25,"P_{Constant}"); t->SetTextColor(4); t->SetNDC(); t->SetTextSize(0.15); t->Draw();
    t= new TText(0.12,0.80,"pAu1");   t->SetTextColor(1); t->SetNDC(); t->SetTextSize(0.08); t->Draw();
    t= new TText(0.12,0.30,Form("pt1=%3.1f - %3.1f",ptcut[bin1],ptcut[bin1+1])); t->SetNDC(); t->SetTextSize(0.08); t->Draw();
    t= new TText(0.12,0.21,Form("pt2=%3.1f - %3.1f",ptcut[bin2],ptcut[bin2+1])); t->SetNDC(); t->SetTextSize(0.08); t->Draw();
    if(corr==0){
	t= new TText(0.12,0.12,Form("Uncorrected")); t->SetNDC(); t->SetTextSize(0.08); t->Draw();
    }else{
	t= new TText(0.12,0.12,Form("Corrected")); t->SetNDC(); t->SetTextSize(0.08); t->Draw();
    }

    cvs->cd(2)->SetLogy(0);
    frame = new TH2F("P_AwaySide","",1,19,26,1,0.0,maxs); 
    frame->GetXaxis()->SetLabelSize(0);
    frame->Draw();
    g=sumtrg(corr, 3, bin1, bin2, 1, 1, 22, "LP");
    t= new TLatex(0.75,0.75,"P_{Awayside}"); t->SetTextColor(4); t->SetNDC(); t->SetTextSize(0.15); t->Draw();

    cvs->cd(3)->SetLogy(0);
    frame = new TH2F("Sigma_AwaySide","",1,19,26,1,0.0,1.4); 
    frame->GetXaxis()->SetLabelSize(0);
    frame->Draw();
    g=sumtrg(corr, 3, bin1, bin2, 2, 1, 22, "LP");
    t= new TLatex(0.75,0.25,"#sigma_{Awayside}"); t->SetTextColor(4); t->SetNDC(); t->SetTextSize(0.15); t->Draw();

    t= new TText(0.85,0.01,"trigger"); t->SetNDC(); t->SetTextSize(0.08); t->Draw();   
    t= new TText(19.6,0.01,"SmallBS1");t->SetTextSize(0.08);t->Draw();
    t= new TText(20.6,0.01,"SmallBS2");t->SetTextSize(0.08);t->Draw();
    t= new TText(21.6,0.01,"SmallBS3");t->SetTextSize(0.08);t->Draw();
    t= new TText(22.6,0.01,"LargeBS1");t->SetTextSize(0.08);t->Draw();
    t= new TText(23.6,0.01,"LargeBS2");t->SetTextSize(0.08);t->Draw();
    t= new TText(24.6,0.01,"LargeBS3");t->SetTextSize(0.08);t->Draw();
    cvs->SaveAs(Form("plot/summary_trg_bin%d%d_corr%d.png",bin1,bin2,corr));
}

void summary2(int corr=1, int bin1=2, int bin2=1, float maxb=0.1, float maxs=0.1, TCanvas* cvs){
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(1);
    gStyle->SetPadGridX(0);
    gStyle->SetPadGridY(0);
    TGraphErrors* g;
    TH2F* frame;
    cvs->Divide(1,3);

    cvs->cd(1)->SetLogy(0);    
    frame = new TH2F("P_constant","",1,0,50000,1,0.0,maxb); frame->Draw();
    //g=sumbbc(corr, 2, bin1, bin2, 0, 2, 20, "LP");
    //g=sumbbc(corr, 1, bin1, bin2, 0, 4, 21, "LP");
    //g=sumbbc(corr, 0, bin1, bin2, 0, 1, 22, "LP");
    //g=sumbbc(corr, 3, 2, 1, 0, 881, 23, "LP");
    //g=sumbbc(corr, 3, 3, 2, 0, 602, 8, "LP");
    //g=sumbbc(corr, 3, 4, 2, 0, 434, 21, "LP");
    g=sumbbc(corr, 3, bin1, bin2, 0, 881, 23, "LP");
    g=sumbbc(corr, 2, bin1, bin2, 0, 602, 8, "LP");

    TText* t;
    t= new TLatex(0.75,0.25,"P_{Constant}"); t->SetTextColor(1); t->SetNDC(); t->SetTextSize(0.15); t->Draw();
/*
    t= new TText(0.12,0.80,"pp");   t->SetTextColor(1); t->SetNDC(); t->SetTextSize(0.08); t->Draw();
    t= new TText(0.12,0.70,"pAl");  t->SetTextColor(4); t->SetNDC(); t->SetTextSize(0.08); t->Draw();
*/
    t= new TText(0.12,0.70,"pAu1");  t->SetTextColor(881); t->SetNDC(); t->SetTextSize(0.08); t->Draw();
    t= new TText(0.12,0.60,"pAu2");  t->SetTextColor(602); t->SetNDC(); t->SetTextSize(0.08); t->Draw();

    //t= new TText(0.12,0.30,Form("pt1=%3.1f - %3.1f,",ptcut[2],ptcut[2+1])); t->SetTextColor(881);t->SetNDC(); t->SetTextSize(0.08); t->Draw();
    //t= new TText(0.12,0.30,Form("pt1=%3.1f - %3.1f,",ptcut[3],ptcut[4])); t->SetTextColor(602); t->SetNDC(); t->SetTextSize(0.08); t->Draw();
    //t= new TText(0.215,0.30,Form("%3.1f - %3.1f,",ptcut[4],ptcut[5])); t->SetTextColor(434); t->SetNDC(); t->SetTextSize(0.08); t->Draw();
    t= new TText(0.12,0.30,Form("pT1=%3.1f - %3.1f",ptcut[bin1],ptcut[bin1+1]));  t->SetNDC(); t->SetTextSize(0.08); t->Draw();
         
    t= new TText(0.12,0.21,Form("pT2=%3.1f - %3.1f",ptcut[bin2],ptcut[bin2+1])); t->SetNDC(); t->SetTextSize(0.08); t->Draw();
    
    if(corr==0){
	t= new TText(0.12,0.12,Form("Uncorrected")); t->SetNDC(); t->SetTextSize(0.08); t->Draw();
    }else{
	t= new TText(0.12,0.12,Form("Corrected")); t->SetNDC(); t->SetTextSize(0.08); t->Draw();
    }

    cvs->cd(2)->SetLogy(0);
    frame = new TH2F("P_AwaySide","",1,0,50000,1,0.0,maxs); frame->Draw();
    //g=sumbbc(corr, 2, bin1, bin2, 1, 2, 20, "LP");
    //g=sumbbc(corr, 1, bin1, bin2, 1, 4, 21, "LP");
    //g=sumbbc(corr, 0, bin1, bin2, 1, 1, 22, "LP");
    //g=sumbbc(corr, 3, 2, 1, 1, 881, 23, "LP");
    //g=sumbbc(corr, 3, 3, 2, 1, 602, 8, "LP");
    //g=sumbbc(corr, 3, 4, 2, 1, 434, 21, "LP");
    g=sumbbc(corr, 3,bin1, bin2, 1, 881, 23, "LP");
    g=sumbbc(corr, 2, bin1, bin2, 1, 602, 8, "LP");

    t= new TLatex(0.75,0.75,"P_{Awayside}"); t->SetTextColor(1); t->SetNDC(); t->SetTextSize(0.15); t->Draw();

    cvs->cd(3)->SetLogy(0);
    frame = new TH2F("Sigma_AwaySide","",1,0,50000,1,0.0,1.0); frame->Draw();
    //g=sumbbc(corr, 2, bin1, bin2, 2, 2, 20, "LP");
    //g=sumbbc(corr, 1, bin1, bin2, 2, 4, 21, "LP");
    //g=sumbbc(corr, 0, bin1, bin2, 2, 1, 22, "LP");
    //g=sumbbc(corr, 3, 2, 1, 2, 881, 23, "LP");
    //g=sumbbc(corr, 3, 3, 2, 2, 602, 8, "LP");
    //g=sumbbc(corr, 3, 4, 2, 2, 434, 21, "LP");
    g=sumbbc(corr, 3, bin1, bin2, 2, 881, 23, "LP");
    g=sumbbc(corr, 2, bin1, bin2, 2, 602, 8, "LP");

    t= new TLatex(0.75,0.25,"#sigma_{Awayside}"); t->SetTextColor(1); t->SetNDC(); t->SetTextSize(0.15); t->Draw();

    t= new TText(0.7,0.01,"BBCEast ADC Sum"); t->SetNDC(); t->SetTextSize(0.08); t->Draw();    
    cvs->SaveAs(Form("plot/summary_pau12_bbc_bin%d%d_corr%d.png",bin1,bin2,corr));
}


void comp(int run, int pt1, int pt2, TCanvas* cvs, int fit=0){   
    int bin0=1;
    char c[100];
    char c2[100];
    readfile(OPT,run);
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(0);
    gStyle->SetOptTitle(0);
    cvs->Clear();
    float ptcut[kNPtBin+1]={0.5,1.0,1.5,2.0,2.5,3.0,10.0};
    float col[NCUT+1]={0,1,4,3,4,38,6,9,8,kGreen+3,kOrange,kPink+9,kOrange+7,kGreen+3,3,2,1,2};
    TText* t;    
    int cmax=NCUT;
    if(run==20) cmax++;
    int iy=0;
    for(int cc=1; cc<cmax; cc++){
	TH1F *h,*h2,*h3,*h4;	
	if(run==11 && cc==5) continue;
	if(run==11 && cc>14) continue;
	//if(run==20 && cc!=2 && cc!=9 && cc!=10 && cc!=11 && cc!=cmax-3) continue;
	if(run==20 && cc!=2 && cc!=14  && cc!=cmax-3) continue;
	//get normalizations
	sprintf(c,"m0_%1d_c%d",pt1,cc);
	TH1F* h0 = (TH1F*)mTFile->Get(c);
	float norm0 = h0->GetEntries();
	sprintf(c,"m1_%1d%1d_c%d",pt1,pt2,cc);
	TH1F* h1 = (TH1F*)mTFile->Get(c);
	float norm1 = h1->GetEntries();
	float norm2=norm1/norm0;
	float norm3=norm2/ZggCut;
	printf("cut=%2d n0=%d n1=%d n2=%f\n",cc,norm0,norm1,norm2);
	
	sprintf(c,"dphi_%1d%1d_c%d",pt1,pt2,cc);
	h = (TH1F*)mTFile->Get(c);
	int nbin = h->GetNbinsX();
	if(cc==cmax-3){
	    h->Scale(1.0/norm0*nbin/2.0/PI);
	}else{
	    h->Scale(1.0/norm0*nbin/2.0/PI/ZggCut);
	}
	h->SetLineColor(col[cc]);
	h->SetLineWidth(2);
	h->SetMinimum(0.0);
	if(iy==0) {
	    h->SetMaximum(h->GetMaximum()*1.5);
	    h->Draw("l");
	}else{
	    h->Draw("lsame");
	}	
	if(run==20 && cc==cmax-3) cc=cmax-1;
	t = new TText(0.7, 0.85-iy*0.03,CCUT[JBEAM][cc]); t->SetNDC(); t->SetTextSize(0.02); t->SetTextColor(col[cc]); t->Draw();
	iy++;
    }
    float xx=0.45, yy=0.80, dy=0.03;
    t = new TText(xx, yy,    Form("pT1=%3.1f-%3.1f",ptcut[pt1],ptcut[pt1+1])); t->SetNDC(); t->SetTextSize(0.03); t->Draw();
    t = new TText(xx, yy-dy, Form("pT2=%3.1f-%3.1f",ptcut[pt2],ptcut[pt2+1])); t->SetNDC(); t->SetTextSize(0.03); t->Draw();

    if     (run==1 || run==11) {sprintf(c,"plot/dipi0_pp_compdphi.png");}
    else if(run==2 || run==12) {sprintf(c,"plot/dipi0_pau_compdphi.png");}
    else if(run==3 || run==13) {sprintf(c,"plot/dipi0_pal_compdphi.png");}
    else if(run==20)           {sprintf(c,"plot/dipi0_pythia_compdphi.png");}
    else                       {sprintf(c,"plot/dipi0_%d_compdphi.png",run);}
    printf("Saving %s\n",c);
    //cvs->SaveAs(c);
}

void dipi0(int plt=0, int cut=2, int run=1, int opt=4){
    gStyle->SetOptDate(0);
    gStyle->SetPadGridX(0);
    gStyle->SetPadGridY(0);
    printf("plt=%d cut=%d run=%d opt=%d\n",plt,cut,run,opt);
    OPT=opt;
    RUN=run;
    openCanvas();  
    memset(PAR0,0,sizeof(PAR0));
    memset(PAR1,0,sizeof(PAR1));
    memset(PAR2,0,sizeof(PAR2));
    memset(PAR3,0,sizeof(PAR3));
    memset(PAR4,0,sizeof(PAR4));
    memset(ERR0,0,sizeof(ERR0));
    memset(ERR1,0,sizeof(ERR1));
    memset(ERR2,0,sizeof(ERR2));
    memset(ERR3,0,sizeof(ERR3));
    memset(ERR4,0,sizeof(ERR4));
    if(plt==1   || plt==-1) bbc(1);
    if(plt==2   || plt==-1) bbc(2);
    if(plt==3   || plt==-1) bbc(3);
    if(plt==-2  || plt==-1) plot1d2("BBCE");

    if(plt==4 || plt==0 ) {plot("bbce",11,cut,c1); plot("bbce",13,cut,c2); plot("bbce",12,cut,c3);}
    if(plt==5 || plt==-1) {plot("m0",11,cut,c1);} //  plot("m0",13,cut,c2);  plot("m0",12,cut,c3);}
    if(plt==6 || plt==-1) {plot("m1",11,cut,c1);   plot("m1",13,cut,c2);  plot("m1",12,cut,c3);}
    if(plt==7 || plt==-1) {plot("m2",11,cut,c1);   plot("m2",13,cut,c2);  plot("m2",12,cut,c3);}
    if(plt==8 || plt==-1) {plot("z1",11,cut,c1);   plot("z1",13,cut,c2);  plot("z1",12,cut,c3);}
    if(plt==9 || plt==-1) {plot("z2",11,cut,c1);   plot("z2",13,cut,c2);  plot("z2",12,cut,c3);}
    if(plt==10|| plt==-1) {plot("phi0",11,cut,c1); plot("phi0",13,cut,c2);plot("phi0",12,cut,c3);}
    if(plt==11|| plt==-1) {plot("phi1",11,cut,c1);} //plot("phi1",13,cut,c2);plot("phi1",12,cut,c3);}
    if(plt==12|| plt==-1) {plot("phi2",11,cut,c1);}// plot("phi2",13,cut,c2);plot("phi2",12,cut,c3);}
    if(plt==13|| plt==0 ) {plot("eta1",11,cut,c1); plot("eta1",13,cut,c2);plot("eta1",12,cut,c3);}
    if(plt==14|| plt==0 ) {plot("eta2",11,cut,c1); plot("eta2",13,cut,c2);plot("eta2",12,cut,c3);}
    if(plt==15|| plt==-1) {plot("dphi",11,cut,c1);} //plot("dphi",13,cut,c2);plot("dphi",12,cut,c3);}
    if(plt==16|| plt==-1) {plot("phi1dphi",11,cut,c1); plot("phi1dphi",13,cut,c2);plot("phi1dphi",12,cut,c3);}
    if(plt==17|| plt==0 ) {plot("mix",11,cut,c1);}// plot("mix",13,cut,c2);plot("mix",12,cut,c3);}
    if(plt==18|| plt==0 ) {plot("pt1",11,cut,c1); plot("pt1",13,cut,c2);plot("pt1",12,cut,c3);}

    if(plt==20 || plt==0){plot("mall",11,cut,c1);   plot("mall",13,cut,c2);   plot("mall",12,cut,c3);}
    if(plt==21 || plt==0){plot("z12",11,cut,c1);    plot("z12",13,cut,c2);    plot("z12",12,cut,c3);}
    if(plt==22 || plt==0){plot("phiall",11,cut,c1); plot("phiall",13,cut,c2); plot("phiall",12,cut,c3);}
    if(plt==23 || plt==0){plot("m2",11,18,c1); plot("m2",13,18,c2);   plot("m2",12,18,c3);}
    if(plt==24 || plt==0){plot("bbce",11,18,c1); plot("bbce",13,18,c2);   plot("bbce",12,18,c3);}

    if(plt==30|| plt==-1){comp(11,4,2,c1);   comp(13,4,2,c2);  comp(12,4,2,c3);}

    if(plt==40 || plt==0)  {plot("norm",15,20,c1,2,4,1, 80e-3); plot("norm",15,21,c2,2,4,1,80e-3); plot("norm",15,22,c3,2,4,1,80e-3);}
    if(plt==41 || plt==-1) {plot("corr",15,2,c1,1,3,1,0.01);plot("corr",15,2,c2,1,5,3,0.0003);}//plot("corr",15,2,c3,1,5,3,0.3e-3);}
    if(plt==-41 || plt==0){plot("corr",11,2,c1,2);}//pp, c2
    if(plt==42 || plt==0)  {plot("corr",15,2,c1,2);plot("corr",15,4,c2,2);plot("corr",15,5,c3,2);}//pAu, c2, c4 and c5
    if(plt==-42)           {plot("corr",15,15,c1,2);plot("corr",15,16,c2,2);plot("corr",13,2,c3,2);}//pAu: c15, c16 and pAl: c2
    if(plt==43 )           {plot("corr",13,4,c1,2);plot("corr",13,5,c2,2);plot("corr",13,15,c3,2); }//pAl: c4, c5 and c15
    if(plt==-43)           {
	plot("corr",11, 2,c1,1,3,1); plot("corr",13, 2,c2,1,3,1); plot("corr",12, 2,c3,1,3,1); 
	plot("corr",11, 4,c1,1,3,1); plot("corr",13, 4,c2,1,3,1); plot("corr",12, 4,c3,1,3,1); 
	plot("corr",11, 5,c1,1,3,1); plot("corr",13, 5,c2,1,3,1); plot("corr",12, 5,c3,1,3,1); 
	plot("corr",11,15,c1,1,3,1); plot("corr",13,15,c2,1,3,1); plot("corr",12,15,c3,1,3,1); 
	plot("corr",11,16,c1,1,3,1); plot("corr",13,16,c2,1,3,1); plot("corr",12,16,c3,1,3,1); 
	plot("corr",12, 2,c3,1,4,2); 
	plot("corr",12, 2,c3,1,5,3); 
	plot("corr",12,16,c3,1,4,2); 
    }
    if(plt==44 )           {summary1n(0); }
    if(plt==45 )           {summary2(1,5,3, 0.001,0.0004,c1);}// summary2(1,4,2,0.008, 0.002,c2);summary2(1,5,2, 0.008,0.002,c3);}
    if(plt==-45)           {summarytrg(1,4,3,0.01,0.003,c1);}
    if(plt==46 )           {summary2(1,5,3, 0.002,0.0002,c1);}// summary2(1,3,1,0.04, 0.004,c2); summary2(1,4,1,0.04, 0.004,c3);}
    if(plt==47 )           {summary2(1,3,2,0.008,0.002,c1); summary2(1,4,2,0.008,0.002,c2); summary2(1,5,2,0.008,0.002,c3);}
    if(plt==48 )           {summarychi2(); }
    if(plt==49 )           {plot("norm",11,18,c1,1); /*plot("norm",13,18,c2,1);*/ plot("norm",12,18,c3,1);}
    //if(plt==49 )           {plot("phi1",11,18,c1,1); }//plot("norm",13,18,c2,1); plot("norm",12,18,c3,1);}
    if(plt==-40 || plt==-1) {
	plot("norm",11, 2,c1,1); plot("norm",13, 2,c2,1); plot("norm",12, 2,c3,1);
	plot("norm",11, 4,c1,1); plot("norm",13, 4,c2,1); plot("norm",12, 4,c3,1);
	plot("norm",11, 5,c1,1); plot("norm",13, 5,c2,1); plot("norm",12, 5,c3,1);
	plot("norm",11,15,c1,1); plot("norm",13,15,c2,1); plot("norm",12,15,c3,1);
	plot("norm",11,16,c1,1); plot("norm",13,16,c2,1); plot("norm",12,16,c3,1);
	plot("corr",11, 2,c1,1); plot("corr",13, 2,c2,1); plot("corr",12, 2,c3,1);
	plot("corr",11, 4,c1,1); plot("corr",13, 4,c2,1); plot("corr",12, 4,c3,1);
	plot("corr",11, 5,c1,1); plot("corr",13, 5,c2,1); plot("corr",12, 5,c3,1);
	plot("corr",11,15,c1,1); plot("corr",13,15,c2,1); plot("corr",12,15,c3,1);
	plot("corr",11,16,c1,1); plot("corr",13,16,c2,1); plot("corr",12,16,c3,1);
    }

    if(plt==50)  {
	plot("corr",11,2,c1,1,3,1);
	plot("corr",11,2,c2,1,4,2);
	plot("corr",11,2,c3,1,5,3); 
    }
    if(plt==51)  {
	plot("corr",12,2,c1,1,3,1);
	plot("corr",12,2,c2,1,4,2);
	plot("corr",12,2,c3,1,5,3); 
    }
    if(plt==52)  {
	plot("corr",12,16,c1,1,3,1);
	plot("corr",12,16,c2,1,4,2);
    }
    

    if(plt==60) mix(run,cut,3,1); 
    if(plt==61) {/*mix(11,12,4,2);*/ mixsim(11,2,5,1,c1,200000);
mixsim(11,2,5,2,c2,70000);mixsim(11,2,5,3,c3,10000);}
    if(plt==62) {mix(12,16,2,0); mixsim(12,16,2,0,c2,100);}//mixsim2(12,16,2,0,c3);}
    if(plt==63) {mix(11,2,3,1);  mixsim(11, 2,3,1,c2,10000);}
    if(plt==64) {mix(12,16,3,1); mixsim(12,16,3,1,c2,10000);}
    if(plt==65) {mix(13,15,3,1); mixsim(13,15,3,1,c2,10000);}
    if(plt==66) {mix(13,2,2,2);  mixsim(13, 2,2,2,c2,10000);}
    
    if(plt==70) {plotphi();}
    if(plt==71) {plotphi_proj(1,c1); plotphi_proj(0,c2); plotphi_proj(2,c3);}
    if(plt==72) {plotphi_proj(3,c1); plotphi_proj(4,c2);}

    if(plt==100 || plt==0){
	plot("corr",11, 2,c1,1,2,0,0.1);
	plot("corr",11, 3,c1,1,2,0,0.1);
	plot("corr",11, 4,c1,1,2,0,0.1);
	plot("corr",13, 2,c1,1,2,0,0.1);
	plot("corr",13, 3,c1,1,2,0,0.1);
	plot("corr",13, 4,c1,1,2,0,0.1);
	plot("corr",13, 5,c1,1,2,0,0.1);
	plot("corr",13,15,c1,1,2,0,0.1);
	plot("corr",12, 2,c1,1,2,0,0.1);
	plot("corr",12, 3,c1,1,2,0,0.1);
	plot("corr",12, 4,c1,1,2,0,0.1);
	plot("corr",12, 5,c1,1,2,0,0.1);
	plot("corr",12,15,c1,1,2,0,0.1);
	plot("corr",12,16,c1,1,2,0,0.1);
    }
    if(plt==101 || plt==-1){
	plot("corr",11, 2,c1,1,3,1,0.010);
	plot("corr",11, 3,c1,1,3,1,0.010);
	plot("corr",11, 4,c1,1,3,1,0.010);
	plot("corr",13, 2,c1,1,3,1,0.010);
	plot("corr",13, 3,c1,1,3,1,0.010);
	plot("corr",13, 4,c1,1,3,1,0.010);
	plot("corr",13, 5,c1,1,3,1,0.010);
	plot("corr",13,15,c1,1,3,1,0.010);
	plot("corr",12, 2,c1,1,3,1,0.010);
	plot("corr",12, 3,c1,1,3,1,0.010);
	plot("corr",12, 4,c1,1,3,1,0.010);
	plot("corr",12, 5,c1,1,3,1,0.010);
	plot("corr",12,15,c1,1,3,1,0.010);
	plot("corr",12,16,c1,1,3,1,0.010);
    }
    if(plt==102 || plt==-1){
	plot("corr",11,2,c1,1,4,2,0.002);
	plot("corr",12,2,c2,1,4,2,0.002);
	plot("corr",12,3,c2,1,4,2,0.002);
	plot("corr",12,4,c2,1,4,2,0.002);
	plot("corr",12,5,c2,1,4,2,0.002);
	plot("corr",12,15,c2,1,4,2,0.002);
	plot("corr",12,16,c2,1,4,2,0.002);
    }
    if(plt==103 || plt==-1){
	plot("corr",11,2,c1,1,5,3,0.0005);
	plot("corr",12,2,c2,1,5,3,0.0005);
	plot("corr",12,3,c2,1,5,3,0.0005);
	plot("corr",12,4,c2,1,5,3,0.0005);
	plot("corr",12,5,c2,1,5,3,0.0005);
	plot("corr",12,15,c2,1,5,3,0.0005);
	plot("corr",12,16,c2,1,5,3,0.0005);
    }
    if(plt==110 || plt==-1){
	plot("corr",11,2,c1,1,3,1,0.012);
	plot("corr",11,6,c2,1,3,1,0.012);
	plot("corr",12,2,c1,1,3,1,0.012);
	plot("corr",12,6,c2,1,3,1,0.012);
	plot("corr",15,2,c1,1,3,1,0.012);
	plot("corr",15,6,c2,1,3,1,0.012);
	plot("corr",11,2,c1,1,4,2,0.002);
	plot("corr",11,6,c2,1,4,2,0.002);
	plot("corr",12,2,c1,1,4,2,0.002);
	plot("corr",12,6,c2,1,4,2,0.002);
	plot("corr",15,2,c1,1,4,2,0.002);
	plot("corr",15,6,c2,1,4,2,0.002);
    }
    if(plt==111 || plt==-1){
	plot("corr",11,12,c1,1,3,1,0.012);
	plot("corr",11,13,c2,1,3,1,0.012);
	plot("corr",15,12,c1,1,3,1,0.012);
	plot("corr",15,13,c2,1,3,1,0.012);
	plot("corr",12,12,c1,1,3,1,0.012);
	plot("corr",12,13,c2,1,3,1,0.012);
	plot("corr",11,12,c1,1,4,2,0.002);
	plot("corr",11,13,c2,1,4,2,0.002);
	plot("corr",15,12,c1,1,4,2,0.002);
	plot("corr",15,13,c2,1,4,2,0.002);
	plot("corr",12,12,c1,1,4,2,0.002);
	plot("corr",12,13,c2,1,4,2,0.002);
    }
    if(plt==112 || plt==-1){
	plot("corr",11,9,c1,1,3,1,0.012);
	plot("corr",11,10,c2,1,3,1,0.012);
	plot("corr",11,11,c2,1,3,1,0.012);
	plot("corr",12,9,c1,1,3,1,0.012);
	plot("corr",12,10,c2,1,3,1,0.012);
	plot("corr",12,11,c2,1,3,1,0.012);
    }


    if(plt==200){
	bbc();
	for(int c=0; c<NCUT; c++){
	    plot("mall",11,c,c1);   plot("mall",12,c,c2);
	    plot("z12", 11,c,c1);   plot("z12", 12,c,c2);
	    plot("norm",11,c,c1);   plot("norm",12,c,c2);
	}
    }

    if(plt==300){ //QM17
	QM=1;
	//plot("norm",12,2,c1,0,3,1,0.012);
	//plot("norm",11,2,c2,-1,-1,-1);
	QM=2;
	plot("dphi",12,2,c1,0,3,1,50000);
	QM=3;
	plot("norm",12,15,c2,0,3,1,0.03);
    }
    if(plt==301){//Xiaoxuan pp
	plot("dphi",11,2,c1,2,3,1,50000);
        plot("corr",11,2,c2,2,3,1,0.012);
    }
}
