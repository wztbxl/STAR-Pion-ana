static int OPT=4;
static const int kNPtBin=6;
static int IBEAM,JBEAM;
static const char CBEAM[20];
TFile* mTFile;
static const double PI=TMath::Pi();
static const double twoPI=PI*2.0;
static Double_t ZggCut=0.7;
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

Double_t twoGaus(Double_t *x, Double_t *par){
    Double_t OP=1.0/sqrt(2.0*PI);
    Double_t x1 = x[0];
    while(x1<-PI) x1+=2.0*PI;
    while(x1>=PI) x1-=2.0*PI;
    Double_t x2 = x[0]-PI;
    while(x2<-PI) x2+=2.0*PI;
    while(x2>=PI) x2-=2.0*PI;
    Double_t f = par[0]/2.0/PI;
    f += par[3]*OP/par[4]*exp(-x1*x1/2.0/par[4]/par[4]);
    f += par[1]*OP/par[2]*exp(-x2*x2/2.0/par[2]/par[2]);
    return f;
    }
    
void readfile(int opt=-1, int run=-1){
	char file[100];
	IBEAM=0; JBEAM=0;
	if(opt<0) opt=OPT;

	if(run==11) {sprintf(file,"/star/u/xchu/pwg/DiPion0Corr/Ana/pp/Hist/pp.Hist.root");  sprintf(CBEAM,"pp");   IBEAM=0; JBEAM=0;}
	if(run==15) {sprintf(file,"/star/u/xchu/pwg/DiPion0Corr/Ana/pAu/pAu.total.Hist.root");     sprintf(CBEAM,"pAu"); IBEAM=3; JBEAM=2;}
	if(run==13) {sprintf(file,"/star/u/xchu/pwg/DiPion0Corr/Ana/pAl/Hist/BBCE_v8/pAl.Hist.root");sprintf(CBEAM,"pAl");  IBEAM=1; JBEAM=1;}

	printf("Reading %s\n",file);
	mTFile = new TFile(file);
}

TH1F* mix(int run=21, int cut=1, int bin1=3, int bin2=1,  int color=1, int style=8){
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

    //normalization and rebin
    char c[100];
    sprintf(c,"m0_%1d_c%d",bin1,cut);
    printf("%s\n",c);
    TH1F* m0= (TH1F*)mTFile->Get(c);
    int norm0 = m0->GetEntries();
    h5->Rebin(4);
    int nbin = h5->GetNbinsX();
    h5->Sumw2();
    h5->Scale(1.0/norm0*nbin/2.0/PI/ZggCut);

    //fitting
    f=new TF1("twoGaus",twoGaus,-PI/2.0,+PI*3.0/2.0,5);
    double norm3 = 1;
    f->SetParameters(norm3/10.0,norm3/2.0,0.12,norm3/2.0,0.3);
    f->SetParNames("Const","IntFar","SigFar","IntNear","SigNear");
    f->SetParLimits(0,0.0,1.0);
    f->SetParLimits(1,0.0,1.0);
    f->SetParLimits(2,0.0,3.0);
    f->SetParLimits(3,0.0,1.0);
    f->SetParLimits(4,0.0,3.0);
    f->SetLineColor(0); f->SetLineWidth(1);
    h5->Fit("twoGaus","Q");
    PAR0[bin1][bin2][JBEAM]=f->GetParameter(0);
    ERR0[bin1][bin2][JBEAM]=f->GetParError(0);
    PAR1[bin1][bin2][JBEAM]=f->GetParameter(1);
    ERR1[bin1][bin2][JBEAM]=f->GetParError(1);
    PAR2[bin1][bin2][JBEAM]=f->GetParameter(2);
    ERR2[bin1][bin2][JBEAM]=f->GetParError(2);
    PAR3[bin1][bin2][JBEAM]=f->GetParameter(3);
    PAR4[bin1][bin2][JBEAM]=f->GetParameter(4);

    h5->SetLineColor(color);
    h5->SetMarkerColor(color);
    h5->SetMarkerSize(1.6);
    h5->SetMarkerStyle(style);
    return h5;   
}

void readpar(int beam=0, int cut, int corr, int print=1){
    char name[200];
    sprintf(name,"./txt/beam%d_cut%d_corr%d.par",beam,cut,corr);
    if(print>0) printf("Reading %s\n",name);
    FILE* f=fopen(name,"r");
    for(int i=1;i<kNPtBin; i++){
        for(int j=1; j<i; j++){
            fscanf(f,"%f %f %f %f %f %f %f\n",
                   &(PAR0[i][j][beam]),&(PAR1[i][j][beam]),&(PAR2[i][j][beam]),
                   &(ERR0[i][j][beam]),&(ERR1[i][j][beam]),&(ERR2[i][j][beam]),&(CHI[i][j][beam]));
            if(i>0 && j>0 && print>1)
                printf("%1d %1d %10.6f %10.6f %10.6f %10.6f %10.6f %10.6f %10.6f %10.6f %10.6f %6.0f %d\n",
                       i,j,
                       PAR0[i][j][beam],PAR1[i][j][beam],PAR2[i][j][beam],
                       ERR0[i][j][beam],ERR1[i][j][beam],ERR2[i][j][beam],CHI[i][j][beam]);
                       }
      }
      fclose(f);
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

void f1(){
        gStyle->SetOptStat(0);
        gStyle->SetOptFit(0);
	gStyle->SetOptTitle(0);
	gStyle->SetPadGridX(0);
	gStyle->SetPadGridY(0);
	gStyle->SetOptDate(0);
	gStyle->SetErrorX(0);
gStyle->SetTitleFont(42,"XY");
gStyle->SetLegendFont(42);
gStyle->SetLabelFont(42,"XY");
TGaxis::SetMaxDigits(3);

//Theory from Bowen, MB results,GBW model
//bin31
        readpar(0,2,1);
        readpar(3,2,1);
Double_t bowenpAu2_fx2[21] = {
        1.594785,
        1.799439,
        1.998707,
        2.197976,
        2.397244,
        2.596513,
        2.795782,
        2.898109,
        2.99505,
        3.097377,
        3.140462,
        3.199704,
        3.296646,
        3.398973,
        3.495914,
        3.695183,
        3.899837,
        4.099105,
        4.298374,
        4.497642,
        4.599969};
Double_t bowenpAu2_fy2[21] = {
        0.0005362648,
        0.0006148632,
        0.0007622901,
        0.001002118,
        0.001343393,
        0.001766044,
        0.002147127,
        0.002276745,
        0.002367477,
        0.002367477,
        0.002367477,
        0.002367477,
        0.002321668,
        0.002232692,
        0.002105581,
        0.001731873,
        0.001317399,
        0.0009827277,
        0.0007475404,
        0.0006029661,
        0.0005576356};
    for(int i=0; i<21; i++) {bowenpAu2_fy2[i]+=(PAR0[3][1][3]/2/PI-0.0005362648);}
    graph2 = new TGraph(21,bowenpAu2_fx2,bowenpAu2_fy2);
    graph2->SetName("bowenpAu2");
    graph2->SetTitle("bowenpAu2");
    graph2->SetFillColor(1);
    graph2->SetLineColor(8);
    graph2->SetLineWidth(2);
    graph2->SetLineStyle(2);

//bin53
Double_t bowenpAu4_fx4[21] = {
        1.594785,
        1.799439,
        1.998707,
        2.197976,
        2.397244,
        2.596513,
        2.795782,
        2.898109,
        2.99505,
        3.097377,
        3.140462,
        3.199704,
        3.296646,
        3.398973,
        3.495914,
        3.695183,
        3.899837,
        4.099105,
        4.298374,
        4.497642,
        4.599969};
Double_t bowenpAu4_fy4[21] = {
        3.14531e-06,
        5.027108e-06,
        8.687909e-06,
        1.592096e-05,
        2.97515e-05,
        5.243141e-05,
        7.902952e-05,
        8.885933e-05,
        9.608276e-05,
        9.991178e-05,
        9.991178e-05,
        9.991178e-05,
        9.608276e-05,
        8.713997e-05,
        7.600079e-05,
        5.042203e-05,
        2.86113e-05,
        1.53108e-05,
        8.354954e-06,
        4.834449e-06,
        3.824015e-06};
for(int i=0; i<21; i++) {bowenpAu4_fy4[i]+=(PAR0[5][3][3]/2/PI-3.14531e-06);}
    graph4 = new TGraph(21,bowenpAu4_fx4,bowenpAu4_fy4);
    graph4->SetName("bowenpAu4");
    graph4->SetTitle("bowenpAu4");
    graph4->SetFillColor(1);
    graph4->SetLineWidth(2);    
    graph4->SetLineStyle(2);
	TH1F *pp31, *pp43;
	TH1F *pAu31, *pAu43;
	pp31=mix(11,2,3,1,4,24);
	pAu31=mix(15,2,3,1,2,29);
	pAl31=mix(13,2,3,1,1,34);
	pp43=mix(11,2,4,3,4,24);
	pAu43=mix(15,2,4,3,2,29);
	pAl43=mix(13,2,4,3,1,34);

	pp31->Fit("twoGaus","0Q");
	pAu31->Fit("twoGaus","0Q");
	pAl31->Fit("twoGaus","0Q");
	pp43->Fit("twoGaus","0Q");
	pAu43->Fit("twoGaus","0Q");
	pAl43->Fit("twoGaus","0Q");

	pp31->GetYaxis()->SetRangeUser(0.003,0.0093);
	pp43->GetYaxis()->SetRangeUser(0.00007,0.00044);
	//pp53->GetYaxis()->SetNoExponent();
	pp31->GetYaxis()->SetNdivisions(204);
	pp31->GetXaxis()->SetLabelSize(0.06);
	pp31->GetYaxis()->SetLabelSize(0.07);
	pp43->GetYaxis()->SetNdivisions(204);
        pp43->GetXaxis()->SetNdivisions(505);
	pp31->GetXaxis()->SetNdivisions(505);
	pp43->GetXaxis()->SetLabelSize(0.06);
	pp43->GetYaxis()->SetLabelSize(0.06);
	pp31->GetYaxis()->SetTitle("C(#Delta#phi)");
	pp31->GetYaxis()->CenterTitle();
	pp43->GetYaxis()->SetTitle("C(#Delta#phi)");
	pp43->GetYaxis()->CenterTitle();
	pp31->GetXaxis()->SetTitle("#Delta#phi [rad]");
	pp43->GetXaxis()->SetTitle("#Delta#phi [rad]");
	pp31->GetXaxis()->CenterTitle();
	pp43->GetXaxis()->CenterTitle();
	pp31->GetXaxis()->SetTitleSize(0.07);
	pp43->GetXaxis()->SetTitleSize(0.07);
	pp43->GetYaxis()->SetTitleSize(0.07);
	pp31->GetYaxis()->SetTitleSize(0.08);
	pp43->GetYaxis()->SetTitleOffset(1.1);
	pp31->GetYaxis()->SetTitleOffset(0.95);
	pp43->GetXaxis()->SetTitleOffset(0.9);
	pp31->GetXaxis()->SetTitleOffset(0.9);
	
	//Drawing
	TCanvas *c = new TCanvas("c", "c", 500, 700);
	TPad *pad_1 = new TPad("pad_1", "pad_1", 0.01,0.52,1.0,1.00);
	//pad_1->SetMargin(0.20, 0.02, 0.14, 0.01);
	pad_1->SetMargin(0.15, 0.01, 0.0, 0.08);
	TPad *pad_2 = new TPad("pad_2", "pad_2", 0.01,0.00,1.0,0.52);
	//pad_2->SetMargin(0.20, 0.02, 0.14, 0.01);
	pad_2->SetMargin(0.15, 0.01, 0.14, 0.0);
	c->cd();
	pad_1->Draw();
	pad_2->Draw();
	pad_1->cd();
	pp31->GetXaxis()->SetRangeUser(PI/2.0,3.0*PI/2.0);
        pp31->Draw("p");
	pAu31->SetMarkerSize(1.8);
	pAu43->SetMarkerSize(1.8);
        pAu31->Draw("samep");
	pAl31->Draw("samep");

	//drawLatex(0.2,0.86,"2-2.5#otimes1-1.5 GeV/c",62,0.06,1);
	drawLatex(0.2,0.83,"#sqrt{s_{NN}} = 200 GeV, NN #rightarrow #pi^{0}#pi^{0}X",42,0.07,1);
	drawLatex(0.2,0.71,"p_{T}^{trig}=2-2.5 GeV/c, p_{T}^{asso}=1-1.5 GeV/c",42,0.07,1);
	drawLatex(0.21,0.59,"2.6 < #eta < 4",42,0.07,1);
	TLegend *leg = new TLegend(0.18,0.48,0.52,0.56);
        leg->SetMargin(0.13);
	leg->SetFillColorAlpha( kWhite, 0);
	leg->SetBorderSize ( 0 );
	leg->SetTextSize(0.055);
	leg->AddEntry(graph2,"pAu GBW","l");
	//leg->Draw("same");
	TLegend *leg31 = new TLegend(0.2,0.68,0.7,0.78);
	leg31->SetHeader("p_{T}^{trig}=2-2.5 GeV/c, p_{T}^{asso}=1-1.5 GeV/c");
	//leg31->SetNColumns(3);
	leg31->SetTextSize(0.07);
	//leg31->AddEntry(pp31,"pp:","p");
	//leg31->AddEntry(pAl31,"pAl:","p");
	//leg31->AddEntry(pAu31,"pAu:","p");
	//leg31->AddEntry(graph2,"pAu GBW","l");
	leg31->SetFillColorAlpha( kWhite, 0);
	leg31->SetBorderSize ( 0 );
	//leg31->Draw("same");
	

	leg31->SetLineColor(0);
	leg->SetLineColor(0);
	graph2->SetLineColor(1);
	//graph2->Draw("same");

        float xx=0.31, yy=0.80, dx=0.2, dy=0.065, size=0.06;

	//drawLatex(xx-0.3,yy+0.8*dy,"STAR Prelimilary",62,size+0.03,2);
	drawLatex(0.87,0.86,"STAR",22,0.07,1);

	pad_2->cd();
	pp43->GetXaxis()->SetRangeUser(PI/2.0,3.0*PI/2.0);
        pp43->Draw("p");
	pAl43->Draw("samep");
	pAu43->Draw("samep");
	//drawLatex(0.2,0.93,"3-5#otimes2-2.5 GeV/c",62,0.058,1);
	graph4->SetLineColor(1);
	//graph4->Draw("same");

        TLegend *leg5 = new TLegend(0.2,0.78,0.7,0.98);
        leg5->SetHeader("p_{T}^{trig}=2.5-3 GeV/c, p_{T}^{asso}=2-2.5 GeV/c");
        leg5->SetNColumns(3);
        leg5->SetTextSize(0.057);
        leg5->AddEntry(pp43,"pp","p");
        leg5->AddEntry(pAl43,"pAl","p");
        leg5->AddEntry(pAu43,"pAu","p");
        leg5->SetFillColorAlpha( kWhite, 0);
        leg5->SetBorderSize ( 0 );
        leg5->Draw("same");
        TLegend *leg51 = new TLegend(0.19,0.56,0.53,0.64);
        leg51->SetMargin(0.13);
        leg51->SetFillColorAlpha( kWhite, 0);
        leg51->SetBorderSize ( 0 );
        leg51->SetTextSize(0.07);
        leg51->AddEntry(graph2,"pAu GBW","l");
        //leg51->Draw("same");


c->SaveAs("f1.pdf");
/*
ofstream fout("HepData/f1_1_pp_highPt.yaml");
fout<<"independent_variables:"<<endl;
fout<<"- header: {name:deltaphi}"<<endl;
fout<<"  values: "<<endl;
for(int i=17; i<= 32;i++){
fout<<" - value: "<<pp43->GetBinCenter(i)<<endl;
}
fout<<"dependent_variables:"<<endl;
fout<<"- header: {name: C(deltaphi)}"<<endl;
fout<<"  values:"<<endl;
for(int i=17; i<= 32;i++){
fout<<"  - value: "<<pp43->GetBinContent(i)<<endl;
fout<<"    errors:"<<endl;
fout<<"    - {staterror: "<<pp43->GetBinError(i)<<", label: stat}"<<endl;
}

fout.close();*/
}

