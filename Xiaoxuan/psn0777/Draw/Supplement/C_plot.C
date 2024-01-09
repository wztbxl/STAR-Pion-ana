static int OPT=4;
static const int kNPtBin=6;
static int IBEAM,JBEAM;
static const char CBEAM[20];
TFile* mTFile;
static const double PI=TMath::Pi();
static const double twoPI=PI*2.0;
static Double_t ZggCut=0.7;
float PAR0[kNPtBin][kNPtBin][4];
float PAR1[kNPtBin][kNPtBin][4];
float PAR2[kNPtBin][kNPtBin][4];
float PAR3[kNPtBin][kNPtBin][4];
float PAR4[kNPtBin][kNPtBin][4];
float ERR0[kNPtBin][kNPtBin][4];
float ERR1[kNPtBin][kNPtBin][4];
float ERR2[kNPtBin][kNPtBin][4];
float ERR3[kNPtBin][kNPtBin][4];
float ERR4[kNPtBin][kNPtBin][4];
float CHI[kNPtBin][kNPtBin][4];

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

	if(run==11) {sprintf(file,"YourDirectory/pp.Hist.root");  sprintf(CBEAM,"pp");   IBEAM=0; JBEAM=0;}
	if(run==15) {sprintf(file,"YourDirectory/pAu.Hist.root");     sprintf(CBEAM,"pAu"); IBEAM=3; JBEAM=2;}
	if(run==13) {sprintf(file,"YourDirectory//pAl.Hist.root");sprintf(CBEAM,"pAl");  IBEAM=1; JBEAM=1;}

	printf("Reading %s\n",file);
	mTFile = new TFile(file);
}

TH1F* mix(int run=21, int cut=1, int bin1=3, int bin2=1,  int color=1, int style=24){
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
    f->SetLineColor(1); f->SetLineWidth(1.2);
    //f->SetLineStyle(7);
    h5->Fit("twoGaus","Q");

    h5->SetLineColor(color);
    h5->SetMarkerColor(color);
    h5->SetMarkerSize(1.0);
    h5->SetMarkerStyle(style);

    return h5;   
}

void readpar(int beam=0, int cut, int corr, int print=1){
    char name[200];
    sprintf(name,"../txt/beam%d_cut%d_corr%d.par",beam,cut,corr);
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

void C_plot(){
        gStyle->SetOptStat(0);
        gStyle->SetOptFit(0);
	gStyle->SetOptTitle(0);
	gStyle->SetPadGridX(0);
	gStyle->SetPadGridY(0);
	gStyle->SetOptDate(0);
	gStyle->SetErrorX(0);
	TH1F *pp21,*pp31, *pp41, *pp51, *pp32,*pp42, *pp52, *pp43, *pp53;
	TH1F *pAu21,*pAu31, *pAu41, *pAu51, *pAu32,*pAu42, *pAu52, *pAu43, *pAu53;
        pp21=mix(11,2,2,1,4,24);
	pAu21=mix(15,16,2,1,2,29);
	pp31=mix(11,2,3,1,4,24);
	pAu31=mix(15,16,3,1,2,29);
       	pp41=mix(11,2,4,1,4,24);
	pAu41=mix(15,16,4,1,2,29);
       	pp51=mix(11,2,5,1,4,24);
	pAu51=mix(15,16,5,1,2,29);

	pAl31=mix(13,16,3,1,1,29);
	pAl51=mix(13,16,5,1,1,29);

	pp32=mix(11,2,3,2,4,24);
	pAu32=mix(15,16,3,2,2,29);
	pp42=mix(11,2,4,2,4,24);
	pAu42=mix(15,16,4,2,2,29);
	pp52=mix(11,2,5,2,4,24);
	pAu52=mix(15,16,5,2,2,29);
	pp43=mix(11,2,4,3,4,24);
	pAu43=mix(15,16,4,3,2,29);
	pp53=mix(11,2,5,3,4,24);
	pAu53=mix(15,16,5,3,2,29);
	
	pp21->Fit("twoGaus","Q");
	pAu21->Fit("twoGaus","Q");
	pp41->Fit("twoGaus","Q");
	pAu41->Fit("twoGaus","Q");
	pp51->Fit("twoGaus","Q");
	pAu51->Fit("twoGaus","Q");
	pp31->Fit("twoGaus","Q");
	pAu31->Fit("twoGaus","Q");
	pAl31->Fit("twoGaus","Q");
	pp51->Fit("twoGaus","Q");
	pAu51->Fit("twoGaus","Q");
	pAl51->Fit("twoGaus","Q");
	pp52->Fit("twoGaus","Q");
	pAu52->Fit("twoGaus","Q");
	pp32->Fit("twoGaus","Q");
	pAu32->Fit("twoGaus","Q");
	pp42->Fit("twoGaus","Q");
	pAu42->Fit("twoGaus","Q");
	pp53->Fit("twoGaus","Q");
	pAu53->Fit("twoGaus","Q");
	pp43->Fit("twoGaus","Q");
	pAu43->Fit("twoGaus","Q");

//pp31->GetYaxis()->SetMaxDigits(3);
	pp31->GetYaxis()->SetNdivisions(204);
	pp31->GetXaxis()->SetLabelSize(0.08);
	pp31->GetYaxis()->SetLabelSize(0.08);
	pp51->GetYaxis()->SetNdivisions(204);
	pp51->GetXaxis()->SetLabelSize(0.08);
	pp51->GetYaxis()->SetLabelSize(0.08);
	pp31->GetYaxis()->CenterTitle();
	pp51->GetYaxis()->CenterTitle();
	pp31->GetXaxis()->CenterTitle();
	pp51->GetXaxis()->CenterTitle();
	pp31->GetXaxis()->SetTitleSize(0.08);
	pp51->GetXaxis()->SetTitleSize(0.08);
	pp51->GetYaxis()->SetTitleSize(0.00);
	pAu51->GetYaxis()->SetTitleSize(0.00);
	pAl51->GetYaxis()->SetTitleSize(0.00);
	pp31->GetYaxis()->SetTitleSize(0.08);
	pp51->GetYaxis()->SetTitleOffset(1.0);
	pp31->GetYaxis()->SetTitleOffset(1.0);
	pp51->GetXaxis()->SetTitleOffset(0.8);
	pp31->GetXaxis()->SetTitleOffset(0.8);
	
	pp21->GetYaxis()->SetRangeUser(0.003,0.012);
	pp31->GetYaxis()->SetRangeUser(0.003,0.012);
	pp41->GetYaxis()->SetRangeUser(0.003,0.012);
	pp51->GetYaxis()->SetRangeUser(0.003,0.012);
	pp21->GetYaxis()->SetNdivisions(204);
	pp21->GetXaxis()->SetLabelSize(0.08);
	pp21->GetYaxis()->SetLabelSize(0.08);
	pp21->GetXaxis()->SetRangeUser(PI/2.,3.*PI/2.);
	pp31->GetXaxis()->SetRangeUser(PI/2.,3.*PI/2.);
	pp41->GetXaxis()->SetRangeUser(PI/2.,3.*PI/2.);
	pp51->GetXaxis()->SetRangeUser(PI/2.,3.*PI/2.);
	pp32->GetXaxis()->SetRangeUser(PI/2.,3.*PI/2.);
	pp42->GetXaxis()->SetRangeUser(PI/2.,3.*PI/2.);
	pp52->GetXaxis()->SetRangeUser(PI/2.,3.*PI/2.);
	pp43->GetXaxis()->SetRangeUser(PI/2.,3.*PI/2.);
	pp53->GetXaxis()->SetRangeUser(PI/2.,3.*PI/2.);
	pp41->GetYaxis()->SetNdivisions(204);
	pp41->GetXaxis()->SetLabelSize(0.08);
	pp41->GetYaxis()->SetLabelSize(0.08);
	pp21->GetYaxis()->SetTitle("C(#Delta#phi)");
	//pp21->GetYaxis()->CenterTitle();
	pp41->GetYaxis()->CenterTitle();
	pp21->GetXaxis()->CenterTitle();
	pp41->GetXaxis()->CenterTitle();
	pp21->GetXaxis()->SetTitleSize(0.1);
	pp41->GetXaxis()->SetTitleSize(0.1);
	pp41->GetYaxis()->SetTitleSize(0.00);
	pAu41->GetYaxis()->SetTitleSize(0.00);
	pp21->GetYaxis()->SetTitleSize(0.1);
	pp41->GetYaxis()->SetTitleOffset(1.0);
	pp21->GetYaxis()->SetTitleOffset(0.76);
	pp41->GetXaxis()->SetTitleOffset(0.8);
	pp21->GetXaxis()->SetTitleOffset(0.8);
	
	pp32->GetYaxis()->SetRangeUser(0.0003,0.0024);
	pp42->GetYaxis()->SetRangeUser(0.0003,0.0024);
	pp52->GetYaxis()->SetRangeUser(0.0003,0.0024);
	pp32->GetYaxis()->SetNdivisions(204);
	pp32->GetXaxis()->SetLabelSize(0.08);
	pp32->GetYaxis()->SetLabelSize(0.08);
	pp42->GetYaxis()->SetNdivisions(204);
	pp42->GetXaxis()->SetLabelSize(0.08);
	pp42->GetYaxis()->SetLabelSize(0.08);
	pp32->GetYaxis()->CenterTitle();
	pp42->GetYaxis()->CenterTitle();
	pp32->GetXaxis()->CenterTitle();
	pp42->GetXaxis()->CenterTitle();
	pp32->GetXaxis()->SetTitleSize(0.08);
	pp42->GetXaxis()->SetTitleSize(0.08);
	pp42->GetYaxis()->SetTitleSize(0.00);
	pAu42->GetYaxis()->SetTitleSize(0.00);
	pp32->GetYaxis()->SetTitleSize(0.08);
	pp42->GetYaxis()->SetTitleOffset(1.0);
	pp32->GetYaxis()->SetTitleOffset(1.0);
	pp42->GetXaxis()->SetTitleOffset(0.8);
	pp32->GetXaxis()->SetTitleOffset(0.8);

	pp43->GetYaxis()->SetRangeUser(0.00005,0.00058);
	pp43->GetYaxis()->SetNdivisions(204);
	pp43->GetYaxis()->SetNoExponent();
	pp53->GetYaxis()->SetNoExponent();
	pp43->GetXaxis()->SetLabelSize(0.08);
	pp43->GetYaxis()->SetLabelSize(0.08);
	pp52->GetYaxis()->SetNdivisions(204);
	pp52->GetXaxis()->SetLabelSize(0.08);
	pp52->GetYaxis()->SetLabelSize(0.08);
	pp43->GetYaxis()->CenterTitle();
	pp52->GetYaxis()->CenterTitle();
	pp43->GetXaxis()->CenterTitle();
	pp52->GetXaxis()->CenterTitle();
	pp43->GetXaxis()->SetTitleSize(0.08);
	pp52->GetXaxis()->SetTitleSize(0.08);
	pp52->GetYaxis()->SetTitleSize(0.00);
	pAu52->GetYaxis()->SetTitleSize(0.00);
	pp43->GetYaxis()->SetTitleSize(0.08);
	pp52->GetYaxis()->SetTitleOffset(1.0);
	pp43->GetYaxis()->SetTitleOffset(1.0);
	pp52->GetXaxis()->SetTitleOffset(0.8);
	pp43->GetXaxis()->SetTitleOffset(0.8);
	
	pp53->GetYaxis()->SetRangeUser(0.00005,0.00058);
	pp53->GetYaxis()->SetNdivisions(204);
	pp53->GetXaxis()->SetLabelSize(0.08);
	pp53->GetYaxis()->SetLabelSize(0.08);
	pp53->GetYaxis()->CenterTitle();
	pp53->GetXaxis()->SetTitle("#Delta#phi [rad]");
	pp53->GetXaxis()->CenterTitle();
	pp53->GetXaxis()->SetTitleSize(0.1);
	pp53->GetYaxis()->SetTitleSize(0.08);
	pp53->GetXaxis()->SetTitleOffset(0.8);
	pp43->GetXaxis()->SetLabelSize(0.08);
	pp43->GetYaxis()->SetLabelSize(0.08);
	pp43->GetYaxis()->CenterTitle();
	pp43->GetXaxis()->SetTitle("#Delta#phi [rad]");
	pp43->GetXaxis()->CenterTitle();
	pp43->GetXaxis()->SetTitleSize(0.1);
	pp43->GetYaxis()->SetTitleSize(0.08);
	pp43->GetXaxis()->SetTitleOffset(0.8);
	
        readpar(0,2,1);//pp MinBias
        readpar(3,16,1);//pAu BBCE>36000

	//Drawing
	TCanvas *c = new TCanvas("c", "c", 1200, 600);
c->Divide(4,3);
	int n = 4;
	for(int i = 1; i<=n; i++){
		for(int j = 0; j<i; j++){
			TVirtualPad *pad=c->cd(j*n+i);
			pad->SetRightMargin(0.0003);
			pad->SetLeftMargin(0.16);
			pad->SetTopMargin(0.018);
			pad->SetBottomMargin(0.17);
			if(i==1&&j==0){}
			pad->Draw();
		}
	}
	
        c->cd(2);
        //pp31->GetYaxis()->SetMaxDigits(3);
	//pp31->GetYaxis()->SetMaxDigits(3);
        pp31->Draw("p");
        pAu31->Draw("samep");

        TLegend *leg31 = new TLegend(0.18,0.25,0.97,0.5);
        //leg31->SetHeader("STAR, #sqrt{s_{NN}} = 200 GeV");
	leg31->AddEntry(pp31,"pp, MinBias","p");
	leg31->AddEntry(pAu31,"pAu, highest E.A. ","p");
	//leg31->AddEntry(pAl31,"fit","l");
	leg31->SetLineColor(0);

        float xx=0.5, yy=0.8, dx=0.3, dy=0.08, size=0.08;
        drawLatex(xx-0.01, yy, "        Area",102,size,1);
        drawLatex(xx-0.01, yy-dy,Form("pp:   %6.4f #pm %6.4f",PAR1[3][1][0], ERR1[3][1][0]),42,size,1);
        drawLatex(xx-0.008, yy-dy*2,Form("pAu: %6.4f #pm %6.4f", PAR1[3][1][3],ERR1[3][1][3]),42,size,1);
	//drawLatex(xx-0.01, yy-dy*3, "        Width",102,size,1);
        //drawLatex(xx-0.01, yy-dy*4,Form("pp:   %6.4f #pm %6.4f",PAR2[3][1][0], ERR2[3][1][0]),42,size,1);
        //drawLatex(xx-0.008, yy-dy*5,Form("pAu: %6.4f #pm %6.4f", PAR2[3][1][3],ERR2[3][1][3]),42,size,1);
	drawLatex(xx-0.25,yy+dy, "2.0-2.5#otimes1.0-1.5 GeV/c",102,size+0.01,1);
	
	c->cd(1);
        pp21->Draw("p");
	pAu21->Draw("samep");
	drawLatex(xx-0.05, yy, "        Area",102,size,1);
        drawLatex(xx, yy-dy,Form("pp:   %6.4f #pm %6.4f", PAR1[2][1][0], ERR1[2][1][0]),42,size,1);
        drawLatex(xx-0.004, yy-dy*2,Form("pAu: %6.4f #pm %6.4f", PAR1[2][1][3], ERR1[2][1][3]),42,size,1);
	drawLatex(xx-0.25,yy+dy, "1.5-2.0#otimes1.0-1.5 GeV/c",102,size+0.01,1);

        c->cd(3);
	pp41->Draw("p");
	pAu41->Draw("samep");
	drawLatex(xx-0.05, yy, "        Area",102,size,1);
        drawLatex(xx-0.05, yy-dy,Form("pp:   %6.4f #pm %6.4f", PAR1[4][1][0], ERR1[4][1][0]),42,size,1);
        drawLatex(xx-0.004-0.05, yy-dy*2,Form("pAu: %6.4f #pm %6.4f", PAR1[4][1][3], ERR1[4][1][3]),42,size,1);
  	drawLatex(xx-0.25,yy+dy, "2.5-3.0#otimes1.0-1.5 GeV/c",102,size+0.01,1);

	c->cd(4);
        pp51->Draw("p");
	pAu51->Draw("samep");
 	TLegend *leg51 = new TLegend(0.28,0.45,0.94,0.71);
        leg51->SetHeader("3.0-5.0#otimes1.0-1.5 GeV/c");
	leg51->AddEntry(pp51,"           ","");
	leg51->AddEntry(pAu51,"           ","");
	leg51->SetLineColor(0);
	leg51->SetBorderSize ( 0 );
	leg51->SetFillColorAlpha( kWhite, 0);
	//leg51->Draw("same");

        drawLatex(xx-0.05, yy, "        Area",102,size,1);
        drawLatex(xx-0.05, yy-dy,Form("pp:   %6.4f #pm %6.4f", PAR1[5][1][0], ERR1[5][1][0]),42,size,1);
        drawLatex(xx-0.004-0.05, yy-dy*2,Form("pAu: %6.4f #pm %6.4f", PAR1[5][1][3], ERR1[5][1][3]),42,size,1);
drawLatex(xx-0.25,yy+dy, "3.0-5.0#otimes1.0-1.5 GeV/c",102,size+0.01,1);

	c->cd(6);
	pp32->Draw("p");
	pAu32->Draw("samep");
cout<<"par "<<PAR1[3][2][0]<<endl;
cout<<"par "<<PAR1[3][2][3]<<endl;
//cout<<PAR1[3][2][0]<<endl;
	drawLatex(xx-0.05, yy, "        Area",102,size,1);
        drawLatex(xx-0.05, yy-dy,Form("pp:   %6.5f #pm %6.5f", PAR1[3][2][0], ERR1[3][2][0]),42,size,1);
        drawLatex(xx-0.004-0.05, yy-dy*2,Form("pAu: %6.5f #pm %6.5f", PAR1[3][2][3], ERR1[3][2][3]),42,size,1);
	drawLatex(xx-0.25,yy+dy, "2.0-2.5#otimes1.5-2.0 GeV/c",102,size+0.01,1);

	c->cd(7);
	pp42->Draw("p");
        pAu42->Draw("samep");
	drawLatex(xx-0.05, yy, "        Area",102,size,1);
        drawLatex(xx-0.05, yy-dy,Form("pp:   %6.5f #pm %6.5f", PAR1[4][2][0], ERR1[4][2][0]),42,size,1);
        drawLatex(xx-0.004-0.05, yy-dy*2,Form("pAu: %6.5f #pm %6.5f", PAR1[4][2][3], ERR1[4][2][3]),42,size,1);
  	drawLatex(xx-0.25,yy+dy, "2.5-3.0#otimes1.5-2.0 GeV/c",102,size+0.01,1);


	c->cd(8);
	pp52->Draw("p");
        pAu52->Draw("samep");
	 drawLatex(xx-0.05, yy, "        Area",102,size,1);
        drawLatex(xx-0.05, yy-dy,Form("pp:   %6.5f #pm %6.5f", PAR1[5][2][0], ERR1[5][2][0]),42,size,1);
        drawLatex(xx-0.004-0.05, yy-dy*2,Form("pAu: %6.5f #pm %6.5f", PAR1[5][2][3], ERR1[5][2][3]),42,size,1);
drawLatex(xx-0.25,yy+dy, "3.0-5.0#otimes1.5-2.0 GeV/c",102,size+0.01,1);
	
	c->cd(11);
	pp43->Draw("p");
	pAu43->Draw("samep");
	drawLatex(xx-0.05, yy, "        Area",102,size,1);
        drawLatex(xx-0.05, yy-dy,Form("pp:   %6.5f #pm %6.5f", PAR1[4][3][0], ERR1[4][3][0]),42,size,1);
        drawLatex(xx-0.004-0.05, yy-dy*2,Form("pAu: %6.5f #pm %6.5f", PAR1[4][3][3], ERR1[4][3][3]),42,size,1);
  	drawLatex(xx-0.25,yy+dy, "3.0-5.0#otimes1.5-2.0 GeV/c",102,size+0.01,1);


	c->cd(12);
	pp53->Draw("p");
	pAu53->Draw("samep");
	 drawLatex(xx-0.05, yy, "        Area",102,size,1);
        drawLatex(xx-0.05, yy-dy,Form("pp:   %6.5f #pm %6.5f", PAR1[5][3][0], ERR1[5][3][0]),42,size,1);
        drawLatex(xx-0.004-0.05, yy-dy*2,Form("pAu: %6.5f #pm %6.5f", PAR1[5][3][3], ERR1[5][3][3]),42,size,1);
drawLatex(xx-0.25,yy+dy, "3.0-5.0#otimes2.0-2.5 GeV/c",102,size+0.01,1);
	

	c->cd(10);
	leg31->Draw();
	drawLatex(0.25,0.75,"STAR, #sqrt{s_{NN}} = 200 GeV",22,0.1,1);
        drawLatex(0.25,0.6,"2.6 < #eta < 4",62,0.1,kBlack);

	c1->SaveAs("C_plot.pdf");
}
