
const int NMul=2;
TGraphErrors *gjetAn15[NMul] ;
TGraphErrors *gjetAn11[NMul] ;
TGraphErrors *gjetAn15Err[NMul] ;
TGraphErrors *gjetAn11Err[NMul] ;

double Rsyst = 0.0;
double Run15jetUECorr[NMul][9];
double Run11jetUECorr[NMul][12];
double Run15jetECorr[NMul][9];
double Run11jetECorr[NMul][12];
double Run15jetPCorr[NMul][9];
double Run11jetPCorr[NMul][12];

//316
double jetE11[2][12]={{6.92577e-310 , 6.92577e-310 , 0 , 36.1769 , 40.6859 , 45.5748 , 50.5089 , 55.4616 , 61.3676 , 69.6291 , 81.3849 , 99.5113 },{6.92577e-310 , 6.92577e-310 , 0 , 36.207 , 40.7136 , 45.5913 , 50.5224 , 55.469 , 61.3711 , 69.6093 , 81.3186 , 99.4038 }};
double jetPt11[2][12]={{6.92577e-310 , 6.92577e-310 , 0 , 2.21366 , 2.47172 , 2.72023 , 2.93305 , 3.12669 , 3.31401 , 3.51139 , 3.80878 , 5.10962 },{6.92577e-310 , 6.92577e-310 , 0 , 2.21334 , 2.46865 , 2.71827 , 2.93009 , 3.11991 , 3.30673 , 3.51657 , 3.84797 , 5.10542 }};

double jetE15[2][9]={{22.3656 , 25.8028 , 30.496 , 35.3487 , 40.3045 , 45.3105 , 50.3258 , 55.3514 , 61.2011 },{22.37 , 25.8415 , 30.4992 , 35.3548 , 40.3034 , 45.3047 , 50.3198 , 55.341 , 61.1883 }};
double jetPt15[2][9]={{2.12505 , 2.30141 , 2.55286 , 2.83645 , 3.0418 , 3.15529 , 3.24785 , 3.36232 , 3.58637 },{2.12466 , 2.30371 , 2.55158 , 2.83282 , 3.04123 , 3.16811 , 3.27237 , 3.39886 , 3.63019 }};
/*
double jetE11[2][12]={{0 , 0 , -32.4793 , 35.9424 , 40.6282 , 45.5371 , 50.4838 , 55.4536 , 61.371 , 69.6651 , 81.4296 , 99.9014 },{0 , 0 , -32.4835 , 35.9794 , 40.6539 , 45.5519 , 50.4959 , 55.4604 , 61.3711 , 69.6446 , 81.3734 , 99.7791 }};
double jetPt11[2][12]={{0 , 0 , -2.05831 , 2.24964 , 2.49657 , 2.72334 , 2.92613 , 3.10579 , 3.27272 , 3.44621 , 3.97863 , 5.10323 },{0 , 0 , -2.05831 , 2.24991 , 2.49472 , 2.7214 , 2.92072 , 3.09554 , 3.26135 , 3.44769 , 4.0135 , 5.10491 }};


double jetE15[2][9]={{22.1159 , 25.6825 , 30.3733 , 35.2844 , 40.2939 , 45.3195 , 50.3432 , 55.3647 , 61.2384 },{22.1274 , 25.7051 , 30.3834 , 35.2904 , 40.2909 , 45.313 , 50.3341 , 55.3565 , 61.2303 }};
double jetPt15[2][9]={{2.09381 , 2.28749 , 2.53129 , 2.75185 , 2.91211 , 3.02936 , 3.16088 , 3.30719 , 3.55531 },{2.09401 , 2.28619 , 2.53046 , 2.753 , 2.91755 , 3.04704 , 3.19122 , 3.35289 , 3.60826 }};
*/


int drawall=0;

drawjetAnCom2_all2(){
	gStyle->SetLabelFont(22,"xyz");

for (int nmul=0; nmul<NMul; nmul++){
	for (int nebin=0; nebin<9; nebin++){
	Run15jetECorr[nmul][nebin]= 1 ;//(jetE15[nmul][nebin]-jetEUE15[nmul][nebin])*jetPCorr[nebin]/jetE15[nmul][nebin];
	 jetPt15[nmul][nebin] -= 0;
	}
	for (int nebin=0; nebin<12; nebin++){
	Run11jetECorr[nmul][nebin]= 1; //(jetE11[nmul][nebin]-jetEUE11[nmul][nebin])*jetPCorr[nebin]/jetE11[nmul][nebin];
	 jetPt11[nmul][nebin] -= 0;
	}
}
drawjetAn15( );
drawjetAn11( );

double AxF[5]= {0.151,	0.238,	0.335,	0.434,	0.534};
double AxE[5]= {0.,	0.,	0.,	0.,	0.};
double Asym[5]={0.00077,	0.00116,	0.00237,	0.00192,	0.00926};
double Aerr[5]={0.00016,	0.00022,	0.00052,	0.00135,	0.0037};
double Aerr2[5]={0.00009,	0.00016,	0.00022,	0.00048,	0.00242};

TGraphErrors* andy=new TGraphErrors(5,AxF,Asym,AxE,Aerr);

	andy->SetMarkerColor(kBlack);
	andy->SetLineColor(kBlack);
	andy->SetMarkerStyle(34);
	andy->SetMarkerSize(1.6);
	andy->SetLineWidth(2);
TCanvas *c = new TCanvas("roses", "roses", 1000, 1000);
    c->Divide(1,2,0.,.0001);
    double x1[2]={4,5};
    double y1[2]={7,5};
        TH2F *h1 = new TH2F("bkgComAN","  ",20,0.09,0.66,10,-0.008,0.044);
        TH2F *h2 = new TH2F("bkgComPt","  ",20,0.09,0.66,10,  1.0 , 7.3);
        h2->GetYaxis()->SetNdivisions(505);
        //h1->GetYaxis()->SetNdivisions(402);
		h2->GetXaxis()->SetLabelSize(0.06);
		h2->GetYaxis()->SetLabelSize(0.06);
		h1->GetXaxis()->SetLabelSize(0.06);
		h1->GetYaxis()->SetLabelSize(0.06);
    /*  h1->GetYaxis()->SetNdivisions(405);
        h1->GetXaxis()->SetNdivisions(505);
        h2->GetXaxis()->SetNdivisions(505);
    */

   float d = 0.40;
//   TPad *p1 = new TPad("i1", "i1", 0.05, 0.8, 0.1 , 0.9);// xl yl xm ym
//   p1->Draw();
//  p1->Divide(1,2,0.0,0.01);

TLatex *   tex = new TLatex(.05,.9,"A_{N}");
   tex->SetNDC();

TLatex latex;
   latex.SetTextSize(0.035);
   latex.SetTextAlign(13);  //align at top
   c->cd(1);
        gPad->SetRightMargin(0.01);
        gPad->SetBottomMargin(0.001);
        h1->Draw();
		andy->Draw("psame");
   c->cd(2);
        h2->Draw();
        gPad->SetRightMargin(0.01);
        gPad->SetBottomMargin(0.5);
	c->cd(0);
        TPad*  p= new TPad("p","p",0,0,1,1); p->Draw(); p->cd();
                p->SetFillStyle(0);
   latex.DrawLatexNDC(.02,.90,"A_{N}");
   latex.SetTextAngle(90.);
   latex.DrawLatexNDC(.02,.29,"#LT#it{p}_{T}#GT [GeV/#it{c}]");
   latex.SetTextAngle(0.);
   latex.DrawLatexNDC(.5,0.2,"x_{F}");

TGraph* pt11[NMul];
TGraph* pt15[NMul];

   c->cd(1);
double Ptxf11[NMul][12];
double Ptxf15[NMul][9];
for (int nmul=0; nmul<NMul; nmul++){
	for (int nebin=0; nebin<12; nebin++){
	Ptxf11[nmul][nebin]= jetE11[nmul][nebin]/250*Run11jetECorr[nmul][nebin];
	//ex0[nebin]= Rsyst*xf[nebin];
	}
	for (int nebin=0; nebin<9; nebin++){
	Ptxf15[nmul][nebin]= jetE15[nmul][nebin]/100*Run15jetECorr[nmul][nebin];
	//ex0[nebin]= Rsyst*xf[nebin];
	}
      pt11[nmul]=new TGraph(12,Ptxf11[nmul],jetPt11[nmul]);
      pt15[nmul]=new TGraph(9,Ptxf15[nmul],jetPt15[nmul]);

	pt11[nmul]->SetMarkerColor(kBlue);
	pt15[nmul]->SetMarkerColor(kRed);
	pt11[nmul]->SetLineColor(kBlue);
	pt15[nmul]->SetLineColor(kRed);
	pt11[nmul]->SetMarkerStyle(22+nmul*4);
	pt15[nmul]->SetMarkerStyle(20+nmul*4);
	pt11[nmul]->SetMarkerSize(1.6);
	pt15[nmul]->SetMarkerSize(1.5);
	gjetAn11[nmul]->SetMarkerStyle(22+nmul*4);
	gjetAn15[nmul]->SetMarkerStyle(20+nmul*4);
	gjetAn11[nmul]->SetMarkerSize(1.6);
	gjetAn15[nmul]->SetMarkerSize(1.5);
	gjetAn15[nmul]->SetMarkerColor(kRed);
	gjetAn15[nmul]->SetLineColor(kRed);
//	gjetAn15Err[nmul]->SetMarkerColor(kRed);
//	gjetAn15Err[nmul]->SetLineColor(kRed);
	gjetAn15[nmul]->Draw("psame");
//	gjetAn15Err->Draw("psame");
	gjetAn11[nmul]->SetMarkerColor(kBlue);
	gjetAn11[nmul]->SetMarkerColor(kBlue);
//	gjetAn11Err[nmul]->SetLineColor(kBlue);
//	gjetAn11Err[nmul]->SetLineColor(kBlue);
	gjetAn11[nmul]->Draw("psame");
//	gjetAn11Err->Draw("psame");
}
	TLegend *leg3=new TLegend(0.60,0.57,0.88,0.98);
                leg3->SetMargin(0.1);
                leg3->SetBorderSize(0);
                leg3->SetFillColor(0);
                leg3->SetTextSize(0.07);
                leg3->AddEntry(gjetAn15[0]," 200 GeV ","PE");
                leg3->AddEntry(gjetAn15[1]," 200 GeV Multiplicity>2","PE");
                leg3->AddEntry(gjetAn11[0]," 500 GeV","PE");
                leg3->AddEntry(gjetAn11[1]," 500 GeV Multiplicity>2","PE");
                leg3->AddEntry(andy," A_{N}DY 500 GeV","PE");
	leg3->Draw();

	 TLatex l;
	 TLatex l2;
    	l.SetTextSize(0.06);
	    l2.SetTextSize(0.06);
	    l.SetTextAngle(0.);
	    double dx=0.12; double dy=0.04; double dd7=0.0052;
           l2.DrawLatex(dx,dy-0.00,"STAR    p^{#uparrow} + p -> EM-jet + X" ); // @ #sqrt{s}=200/500 GeV");
	    l2.SetTextSize(0.06);
		l.DrawLatex(dx,dy-dd7,"Jet algorithm: anti-k_{T} R=0.7 ");
           l2.DrawLatex(dx,dy-dd7*2,"#it{p}^{jet}_{T} > 2 GeV/#it{c}");
           l2.DrawLatex(dx,dy-dd7*3,"2.9 < #eta^{jet} < 3.8");
	    l.DrawLatex(dx,dy-dd7*4,"3.0/3.4% beam pol. scale uncertainty not shown");

	c->cd(2);
for (int nmul=0; nmul<NMul; nmul++){
		pt11[nmul]->Draw("psame");
		pt15[nmul]->Draw("psame");
}



if (drawall==1)  c->SaveAs("DrawjetAnComPtALL.png");

    // THEORY
    c->cd(1);   
    ifstream theo1_200;
    ifstream theo1_500;
     const int Np200=15;
     const int Np500=15;
        string word1,word2,word3;
        double T200N[Np200];
        double T200asy[Np200];
        double T200asyerr[Np200];
        double T200asyerrl[Np200];
        double T200asyerrh[Np200];
        double Ex200[Np200];
        double T500N[Np500];
        double T500asy[Np500];
        double T500asyerr[Np500];
        double T500asyerrl[Np500];
        double T500asyerrh[Np500];
        double Ex500[Np500];
/*        theo1_500.open("theory/Alexei/pi0_AN_vs_xF-jet-500.dat",ios::in);
        theo1_200.open("theory/Alexei/pi0_AN_vs_xF-jet-200.dat",ios::in);
        for (int np=0; np<=Np200; np++){
            if (np==0) theo1_200>>word1>>word2>>word3;
            else theo1_200>>T200N[np-1]>>T200asy[np-1]>>T200asyerr[np-1];
            if (np!=Np200) Ex200[np]=0;
            }    
        for (int np=0; np<=Np500; np++){
            if (np==0) theo1_500>>word1>>word2>>word3;
            else theo1_500>>T500N[np-1]>>T500asy[np-1]>>T500asyerr[np-1];
            if (np!=Np500) Ex500[np]=0;
            }    
            theo1_200.close();
            theo1_500.close();
    
	double Ptxf11_t[10];
        for (int np=0; np<10; np++){
	    Ptxf11_t[np]=Ptxf11[1][np+2];
		}
      TGraphErrors *gth1_200=new TGraphErrors(9,Ptxf15[1],T200asy,Ex200,T200asyerr);
      TGraphErrors *gth1_500=new TGraphErrors(9,Ptxf11_t,T500asy,Ex500,T500asyerr);
      TGraph *gth1_200L=new TGraph(9,Ptxf15[1],T200asy);
      TGraph *gth1_500L=new TGraph(7,Ptxf11_t,T500asy);
*/

        double T200asyerrL[Np500];
        double T500asyerrL[Np500];
        double T200asyerrH[Np500];
        double T500asyerrH[Np500];

        theo1_500.open("theory/Alexei/pi0_AN_vs_xF-jet-500-v2.dat",ios::in);
        theo1_200.open("theory/Alexei/pi0_AN_vs_xF-jet-200-v2.dat",ios::in);
        for (int np=0; np<=Np200; np++){
            if (np==0) theo1_200>>word1>>word2>>word3;
            else theo1_200>>T200N[np-1]>>T200asy[np-1]>>T200asyerrl[np-1]>>T200asyerrh[np-1];
			if (np>0){  T200asyerrL[np-1]=T200asy[np-1]-T200asyerrl[np-1];
						T200asyerrH[np-1]=-T200asy[np-1]+T200asyerrh[np-1];
					}
            if (np!=Np200) Ex200[np]=0;
            }    
        for (int np=0; np<=Np500; np++){
            if (np==0) theo1_500>>word1>>word2>>word3;
            else theo1_500>>T500N[np-1]>>T500asy[np-1]>>T500asyerrl[np-1]>>T500asyerrh[np-1];
			if (np>0){  T500asyerrL[np-1]=T500asy[np-1]-T500asyerrl[np-1];
						T500asyerrH[np-1]=-T500asy[np-1]+T500asyerrh[np-1];
			//			cout<<T500N[np-1]<<" "<< T500asyerrL[np-1]<< "        " <<  T500asyerrH[np-1]<<endl;
					}
            if (np!=Np500) Ex500[np]=0;
		}

   TGraphAsymmErrors *gth1_200 = new TGraphAsymmErrors(Np200,T200N,T200asy,Ex200,Ex200,T200asyerrL,T200asyerrH);
   TGraphAsymmErrors *gth1_500 = new TGraphAsymmErrors(Np500,T500N,T500asy,Ex200,Ex200,T500asyerrL,T500asyerrH);
      TGraph *gth1_200L=new TGraph(Np200,T200N,T200asy);
      TGraph *gth1_500L=new TGraph(Np500,T500N,T500asy);
        gth1_200L->SetLineColor(kRed);
        //gth1_200L->SetLineWidth(3.5);
        gth1_200->SetFillColorAlpha(kRed-9,0.35);
        gth1_500L->SetLineColor(kBlue);
        gth1_500->SetFillColorAlpha(kBlue-7,0.35);
        gth1_200->Draw("3csame");
        gth1_500->Draw("3csame");
        gth1_200L->Draw("csame");
        gth1_500L->Draw("csame");
	TLegend *leg3=new TLegend(0.65,0.77,0.88,0.98);
                leg3->SetMargin(0.4);
                leg3->SetBorderSize(0);
                leg3->SetFillColor(0);
                leg3->SetTextSize(0.06);
                leg3->AddEntry(gth1_200,"Theory 200 GeV","f");
                leg3->AddEntry(gth1_500,"Theory 500 GeV","f");
	    TLine* line=new TLine(0.1,0,0.64,0);
    line->SetLineStyle(9);
    line->Draw();

	c->cd(2);
    leg3->Draw();


c->SaveAs("DrawjetAnComPtALL-JPT_ALL2.png");
/*

TCanvas *c1 = new TCanvas("c1", "c1",0,0,1200,900);
TH2F *bkg = new TH2F("bkgCom","jet A_{N} for Inclusive jet ",20,0.05,0.7,10,-0.008,0.025);
        bkg->GetXaxis()->SetTitle("x_{F}");
        bkg->GetYaxis()->SetTitle("jet A_{N}");
        bkg->GetXaxis()->CenterTitle(true);;
        bkg->GetYaxis()->CenterTitle(true);;
        bkg->GetYaxis()->SetTitleSize(0.04);;
        bkg->Draw();

gjetAn15->SetMarkerColor(kRed);
gjetAn15->SetLineColor(kRed);
gjetAn15Err->SetMarkerColor(kRed);
gjetAn15Err->SetLineColor(kRed);
gjetAn15->Draw("psame");
gjetAn11->SetMarkerColor(kBlue);
gjetAn11->SetMarkerColor(kBlue);
gjetAn11Err->SetLineColor(kBlue);
gjetAn11Err->SetLineColor(kBlue);
gjetAn11->Draw("psame");
//gjetAn11Err->Draw("psame");
//gjetAn15Err->Draw("psame");

TLegend *leg=new TLegend(0.55,0.75,0.85,0.88);
                leg->SetMargin(0.5);
                leg->SetBorderSize(0);
                leg->SetFillColor(0);
                leg->SetTextSize(0.04);
                leg->AddEntry(gjetAn15," 200 GeV","PE");
                leg->AddEntry(gjetAn11," 500 GeV","PE");
//                leg->AddEntry(gasybb,"Background x_{F}>0","PE");
leg->Draw();

 TLatex l;
 TLatex l2;
    l.SetTextSize(0.03);
    l2.SetTextSize(0.03);
	l.SetTextAngle(0.);
	l.DrawLatex(0.06,0.0125,"3.0/3.4% beam pol. scale uncertainty not shown");
	double dx=0.06; double dy=0.023;
	       l2.DrawLatex(dx,dy-0.000,"p^{#uparrow} + p -> EM-jet + X @ #sqrt{s}=200/500 GeV");
		   l2.DrawLatex(dx,dy-0.0025,"Jet algorithm: anti-kT R=0.7 ");
	       l2.DrawLatex(dx,dy-0.005," p_{T} > 2 GeV");
	       l2.DrawLatex(dx,dy-0.0075," 2.9 < #eta < 3.8");

TLine *line = new TLine(0.05,0,0.7,0);
	  line->SetLineColor(kBlack);
	    line->SetLineStyle(7);
	//	  line->Draw();


//c1->SaveAs("DrawjetAnCom.png");
*/

}

drawjetAn15(  ){
		gROOT->SetStyle("Modern");
	 gStyle->SetOptTitle(kFALSE);
	gStyle->SetOptStat(0000);
        gStyle->SetOptFit(1111);//0000);
        gStyle->SetStatColor(0);
 //       gStyle->SetEndErrorSize(0.05);
        gStyle->SetTitleFillColor(0);
        gStyle->SetFillColor(0);
        gStyle->SetTitleColor(1);
        gStyle->SetOptDate(0);
        gStyle->SetStatFont(42);
        gStyle->SetStatW(0.13);
        gStyle->SetStatH(0.13);
        gStyle->SetStatX(1.0);
        gStyle->SetStatY(1.0);
		gStyle->SetTitleXOffset(1.0); 
		gStyle->SetTitleYOffset(1.1); 
		gStyle->SetHistLineWidth(2);; 
		gStyle->SetTitleFont(72,"xyz");;	
		gStyle->SetTitleSize(0.04);;	
                
bool updateplot =0;
const int Nfill=51;
double pol=0.5734;
double polY=0.5837;

 double unpol=0;

ifstream filllist;
filllist.open("Run15filllist");
int fillnum[Nfill];
double fillex[Nfill];
double filldouble[Nfill];
int fillbin=Nfill;
for (int nfill=0; nfill<Nfill;nfill++){
    filllist>>fillnum[nfill];
    fillex[nfill]=0;
    filldouble[nfill] = double(nfill+1);
//	cout<<fillnum[nfill];
}


double ebinlows[9] = {18, 23, 28, 33, 38, 43, 48, 53, 58};
double ebinhighs[9] = {23, 28, 33, 38 , 43, 48, 53, 58, 65};
const int nebins = 9;
double mbinlows[6] = {1.0};
double mbinhighs[6] ={1.0};
int nmbins = 1;
char resultname[200];
char resultname2[200];
char resultname3[200];
char resultname4[200];
char picname[200];
char picname2[200];
double ex0[12]= {0.005,0.006,0.007,0.007,  0.005,0.006,0.007,0.007,0.008,0.009,0.011};//E uncertainty
double jetECorr[9]={ 0.480819,0.223509,0.256389,0.397506,0.655983,1.02898,1.53417,2.16055,3.056};
//double jetECorr[9]={0.0139628 , 0.0065157,  0.00541349,  0.00593327 , 0.00782867,  0.0114732,  0.0171086,  0.0261118,  0.0440385};
double xf[NMul][12];
double xfm[NMul][12];
//double xf1[12];
//double xf2[12];
for (int nmul=0; nmul<NMul; nmul++){
for (int nebin=0; nebin<nebins; nebin++){
//xf[nebin]= (ebinlows[nebin]+ebinhighs[nebin])/2.0/250; //    !!!!!!!!!!type change!!!!!!!!!!
xf[nmul][nebin]= jetE15[nmul][nebin]/100*Run15jetECorr[nmul][nebin];
xfm[nmul][nebin]= -jetE15[nmul][nebin]/100*Run15jetECorr[nmul][nebin];
ex0[nebin]=Rsyst*jetE15[nmul][nebin]/100*Run15jetECorr[nmul][nebin];
//xf1[nebin]=( (ebinlows[nebin]+ebinhighs[nebin])/2-0.5)/250;
//xf2[nebin]=( (ebinlows[nebin]+ebinhighs[nebin])/2+0.5)/250;
//out<< xf[nebin]<<" " << xf1[nebin]<<endl;
}}
ifstream result;
ifstream result2;
ifstream result3;
ifstream result4;

TF1 *fcn1 = new TF1 ("fcn1","pol0",0,60);
TF1 *fcn2 = new TF1 ("fcn2","pol0",0,60);


//TFile *fout= new TFile ("DrawjetAn15.root","recreate");
//fout->cd();
double asy_fill[NMul][nebins];
double asyerr_fill[NMul][nebins];
double asy_fill2[NMul][nebins];
double asyerr_fill2[NMul][nebins];
for (int nmbin=0; nmbin<1;nmbin++){
   for (int nebin=0; nebin<nebins; nebin++){
/*	 fill[Nfill]=-9;
	 ene[Nfill]=-9.;
	 asy[Nfill]=-9.;
	 asyerr[Nfill]=-9.;
	 ml[Nfill]=-9.;
	 mh[Nfill]=-9.;
	 p0[Nfill]=-9.;
	 p0e[Nfill]=-9.;
*/
	int fill[Nfill];
	double ene[Nfill];
	double asy[NMul][Nfill];
	double asy2[NMul][Nfill];
	double asyerr[NMul][Nfill];
	double asyerr2[NMul][Nfill];
	double ml[Nfill];
	double mh[Nfill];
	double p0[Nfill];
	double p0e[Nfill];
	double p02[Nfill];
	double p0e2[Nfill];
		for (int nfill=0; nfill<Nfill;nfill++){
		asyerr2[0][nfill]=0;
		asyerr[0][nfill]=0;
		asyerr2[1][nfill]=0;
		asyerr[1][nfill]=0;
		//cout<<"bin  "<<mbinlows[nmbin]<<"   "<<mbinhighs[nmbin]<<endl;
//		sprintf(resultname,"../Run15/result/jetAn3/jetAn_Fill%d_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
//		sprintf(resultname2,"../Run15/result/jetAn3/jetAny_Fill%d_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
//		sprintf(resultname3,"../Run15/result/jetAn3/jetAnM3_Fill%d_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
//		sprintf(resultname4,"../Run15/result/jetAn3/jetAnyM3_Fill%d_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
		sprintf(resultname,"../Run15/result/jetAn3_all/jetAnJP_Fill%d_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
		sprintf(resultname2,"../Run15/result/jetAn3_all/jetAnyJP_Fill%d_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
		sprintf(resultname3,"../Run15/result/jetAn3_all/jetAnM3JP_Fill%d_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
		sprintf(resultname4,"../Run15/result/jetAn3_all/jetAnyM3JP_Fill%d_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);

		TString infile(resultname);
		TString infile2(resultname2);
		TString infile3(resultname3);
		TString infile4(resultname4);
	//	cout<<infile<<endl;
		result.open(resultname,ios::in);
		result2.open(resultname2,ios::in);
		result3.open(resultname3,ios::in);
		result4.open(resultname4,ios::in);
		
		 if(!result || !result3)  cout<<" file not exist"<<endl;
		
		result>>fill[nfill]>>ene[nfill]>>asy[0][nfill]>>asyerr[0][nfill]>>p0[nfill]>>p0e[nfill]>>ml[nfill]>>mh[nfill];
		result2>>fill[nfill]>>ene[nfill]>>asy2[0][nfill]>>asyerr2[0][nfill]>>p02[nfill]>>p0e2[nfill]>>ml[nfill]>>mh[nfill];
		result3>>fill[nfill]>>ene[nfill]>>asy[1][nfill]>>asyerr[1][nfill]>>p0[nfill]>>p0e[nfill]>>ml[nfill]>>mh[nfill];
		result4>>fill[nfill]>>ene[nfill]>>asy2[1][nfill]>>asyerr2[1][nfill]>>p02[nfill]>>p0e2[nfill]>>ml[nfill]>>mh[nfill];
		result.close();
		result2.close();
		result3.close();
		result4.close();

		//if (nebin ==0)cout<<nfill<<" "<<resultname2<<" "<< asy[0][nfill]<<endl;

	for (int nmul=0; nmul<NMul; nmul++){
        if (asyerr2[nmul][nfill]==0.) {  cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<resultname2<<endl  ;          
            asy2[nmul][nfill]=0;       
            asyerr2[nmul][nfill]=999;
        }   

        if (asyerr[nmul][nfill]==0.) {  cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<resultname4<<endl  ;    
            asy[nmul][nfill]=0; 
            asyerr[nmul][nfill]=999;
        } 
	}
	//	cout<<fill[nfill]<<" asyraw= "<<asy2[nfill]<<" err "<<asyerr2[nfill]<<endl;
//		sumasy[nmbin][nebin] += asy[nfill];
//		sumerr[nmbin][nebin] += asyerr[nfill]*asyerr[nfill];	
		}	
		
		sprintf(picname,"./Otherpic/Anjet2_allFill_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.png",mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
		sprintf(picname2,"./Otherpic/Anjety2_allFill_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.png",mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
	for (int nmul=0; nmul<NMul; nmul++){
		TGraphErrors *forfit=new TGraphErrors(fillbin,filldouble,asy[nmul],fillex,asyerr[nmul]);
		TGraphErrors *forfit2=new TGraphErrors(fillbin,filldouble,asy2[nmul],fillex,asyerr2[nmul]);
		forfit->Fit("fcn1","RQ");
		asy_fill[nmul][nebin]=fcn1->GetParameter(0)/(1-jetECorr[nebin]/100)/pol; // correction
		asyerr_fill[nmul][nebin]=fcn1->GetParError(0)/pol;
		forfit2->Fit("fcn2","RQ");
		asy_fill2[nmul][nebin]=fcn2->GetParameter(0)/polY;
		asyerr_fill2[nmul][nebin]=fcn2->GetParError(0)/polY;
	// TCanvas *c1 = new TCanvas("c1", "c1",0,0,1600,900);
	// c1->SetGrid(0,0);
				 forfit->SetTitle(picname);
				 forfit->SetLineWidth(3);
				 forfit->SetLineColor(4);
				 forfit->SetMarkerSize(3);
				 forfit->GetXaxis()->SetTitle("Fill Index");
                 forfit->GetYaxis()->SetTitle("jet A_{N}");
                 forfit2->SetTitle(picname2);
				 forfit2->SetLineWidth(3);
				 forfit2->SetLineColor(4);
				 forfit2->SetMarkerSize(3);
                 forfit2->GetXaxis()->SetTitle("Fill Index");
                 forfit2->GetYaxis()->SetTitle("jet A_{N}");
	if(updateplot){
		forfit->Draw("AP*");
		c1->SaveAs(picname);
		c1->Clear();
		forfit2->Draw("AP*");
		c1->SaveAs(picname2);
	}
	}
//	cout<<" sumasy= "<<sumasy[nmbin][nebin]<<"in "<<nmbin<<" "<<nebin<<endl;
    }
}	
TGraphErrors *gasybs[NMul];
for (int nmul=0; nmul<NMul; nmul++){
	gasybs[nmul]=new TGraphErrors(nebins,xf[nmul], asy_fill[nmul],ex0,asyerr_fill[nmul]);//stat uncertainty
	gasybs[nmul]->SetMarkerStyle(20+nmul*4);
	gasybs[nmul]->SetMarkerSize(1.3);
	gasybs[nmul]->SetMarkerColor(kBlue);
	gasybs[nmul]->SetLineWidth(2);
	gasybs[nmul]->SetLineColor(kBlue);
	gjetAn15[nmul] =  (TGraphErrors*)gasybs[nmul]->Clone();
//	gjetAn15Err[nmul] =  (TGraphErrors*)gasybserr[nmul]->Clone();
for (int nebin=0; nebin<nebins; nebin++){
			cout<<nebin<<" "<<xf[nmul][nebin]<<" "<<jetPt15[nmul][nebin]<<" " <<asy_fill[nmul][nebin]<<" "<<asyerr_fill[nmul][nebin]<<" "<<endl;
}}



}


drawjetAn11(){
		gROOT->SetStyle("Modern");
	 gStyle->SetOptTitle(kFALSE);
	gStyle->SetOptStat(0000);
        gStyle->SetOptFit(1111);//0000);
        gStyle->SetStatColor(0);
 //       gStyle->SetEndErrorSize(0.05);
        gStyle->SetTitleFillColor(0);
        gStyle->SetFillColor(0);
        gStyle->SetTitleColor(1);
        gStyle->SetOptDate(0);
        gStyle->SetStatFont(42);
        gStyle->SetStatW(0.13);
        gStyle->SetStatH(0.13);
        gStyle->SetStatX(1.0);
        gStyle->SetStatY(1.0);
		gStyle->SetTitleXOffset(1.0); 
		gStyle->SetTitleYOffset(1.1); 
		gStyle->SetHistLineWidth(2);; 
		gStyle->SetTitleFont(72,"xyz");;	
		gStyle->SetTitleSize(0.04);;	
                
bool updateplot =0;
const int Nfill=29;
double pol=0.5249;
double polY=0.5117;
 double unpol=0;

ifstream filllist;
filllist.open("Run11filllist");
int fillnum[Nfill];
double fillex[Nfill];
double filldouble[Nfill];
int fillbin=Nfill;
for (int nfill=0; nfill<Nfill;nfill++){
    filllist>>fillnum[nfill];
    fillex[nfill]=0;
    filldouble[nfill] = double(nfill+1);
//	cout<<fillnum[nfill];
}

const int nebins = 12;
double ebinlows[nebins] = {18, 23, 28, 33, 38, 43, 48, 53, 58, 65, 75 , 90};
double ebinhighs[nebins] = {23, 28, 33, 38 , 43, 48, 53, 58, 65, 75, 90, 120};
//double ebinlows[nebins] = { 38, 43, 48, 53, 58, 65, 75 , 90, 120 ,150, 180, 210};
//double ebinhighs[nebins] = { 43, 48, 53, 58, 65, 75, 90, 120, 150, 180, 210,240};
double mbinlows[6] = {1.0};
double mbinhighs[6] ={1.0};
int nmbins = 1;
char resultname[200];
char resultname2[200];
char resultname3[200];
char resultname4[200];
char picname[200];
char picname2[200];
double ex[11]= {0,0,0,0,0,0,0};//x error 
double ex1[nebins];//for syst
double ex0[nebins]= {0.005,0.006,0.007,0.007,  0.005,0.006,0.007,0.007,0.008,0.009,0.011};//true uncertainty
double xf[NMul][nebins];
double xfm[NMul][nebins];
//double xf1[nebins];
//double xf2[nebins];
for (int nmul=0; nmul<NMul; nmul++){
for (int nebin=0; nebin<nebins; nebin++){
//xf[nebin]= (ebinlows[nebin]+ebinhighs[nebin])/2.0/250; //    !!!!!!!!!!type change!!!!!!!!!!
xf[nmul][nebin]= jetE11[nmul][nebin]/250*Run11jetECorr[nmul][nebin];
xfm[nmul][nebin]= -jetE11[nmul][nebin]/250*Run11jetECorr[nmul][nebin];
ex0[nebin]=Rsyst*jetE11[nmul][nebin]/250*Run11jetECorr[nmul][nebin];
//xf1[nebin]=( (ebinlows[nebin]+ebinhighs[nebin])/2-0.5)/250;
//xf2[nebin]=( (ebinlows[nebin]+ebinhighs[nebin])/2+0.5)/250;
//out<< xf[nebin]<<" " << xf1[nebin]<<endl;
}}
ifstream result;
ifstream result2;
ifstream result3;
ifstream result4;

TF1 *fcn1 = new TF1 ("fcn1","pol0",0,60);
TF1 *fcn2 = new TF1 ("fcn2","pol0",0,60);


//TFile *fout= new TFile ("DrawjetAn15.root","recreate");
//fout->cd();
double asy_fill[NMul][nebins];
double asyerr_fill[NMul][nebins];
double asy_fill2[NMul][nebins];
double asyerr_fill2[NMul][nebins];
for (int nmbin=0; nmbin<1;nmbin++){
   for (int nebin=2; nebin<nebins; nebin++){
	int fill[Nfill];
	double ene[Nfill];
	double asy[NMul][Nfill];
	double asy2[NMul][Nfill];
	double asyerr[NMul][Nfill];
	double asyerr2[NMul][Nfill];
	double ml[Nfill];
	double mh[Nfill];
	double p0[Nfill];
	double p0e[Nfill];
	double p02[Nfill];
	double p0e2[Nfill];
		for (int nfill=0; nfill<Nfill;nfill++){
		asyerr2[0][nfill]=0;
		asyerr[0][nfill]=0;
		asyerr2[1][nfill]=0;
		asyerr[1][nfill]=0;
		//cout<<"bin  "<<mbinlows[nmbin]<<"   "<<mbinhighs[nmbin]<<endl;
		sprintf(resultname, "../Run11/result//jetAn3_all/jetAnJP_Fill%d_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
		sprintf(resultname2,"../Run11/result//jetAn3_all/jetAnyJP_Fill%d_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
		sprintf(resultname3,"../Run11/result//jetAn3_all/jetAnM3JP_Fill%d_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
		sprintf(resultname4,"../Run11/result//jetAn3_all/jetAnyM3JP_Fill%d_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);

		TString infile(resultname);
		TString infile2(resultname2);
		TString infile3(resultname3);
		TString infile4(resultname4);
	//	cout<<infile<<endl;
		result.open(resultname,ios::in);
		result2.open(resultname2,ios::in);
		result3.open(resultname3,ios::in);
		result4.open(resultname4,ios::in);
		
		 if(!result || !result3)  cout<<" file not exist"<<endl;
		
		result>>fill[nfill]>>ene[nfill]>>asy[0][nfill]>>asyerr[0][nfill]>>p0[nfill]>>p0e[nfill]>>ml[nfill]>>mh[nfill];
		result2>>fill[nfill]>>ene[nfill]>>asy2[0][nfill]>>asyerr2[0][nfill]>>p02[nfill]>>p0e2[nfill]>>ml[nfill]>>mh[nfill];
		result3>>fill[nfill]>>ene[nfill]>>asy[1][nfill]>>asyerr[1][nfill]>>p0[nfill]>>p0e[nfill]>>ml[nfill]>>mh[nfill];
		result4>>fill[nfill]>>ene[nfill]>>asy2[1][nfill]>>asyerr2[1][nfill]>>p02[nfill]>>p0e2[nfill]>>ml[nfill]>>mh[nfill];
		result.close();
		result2.close();
		result3.close();
		result4.close();

	for (int nmul=0; nmul<NMul; nmul++){
        if (asyerr2[nmul][nfill]==0.) {  cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<resultname3<<endl  ;          
            asy2[nmul][nfill]=0;       
            asyerr2[nmul][nfill]=999;
        }   

        if (asyerr[nmul][nfill]==0.) {  cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<resultname4<<endl  ;    
            asy[nmul][nfill]=0; 
            asyerr[nmul][nfill]=999;
        } 
	}
		}	
		
		sprintf(picname,"./Otherpic/Anjet15_allFill_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.png",mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
		sprintf(picname2,"./Otherpic/Anjety15_allFill_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.png",mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
	for (int nmul=0; nmul<NMul; nmul++){
		TGraphErrors *forfit=new TGraphErrors(fillbin,filldouble,asy[nmul],fillex,asyerr[nmul]);
		TGraphErrors *forfit2=new TGraphErrors(fillbin,filldouble,asy2[nmul],fillex,asyerr2[nmul]);
		forfit->Fit("fcn1","RQ");
		asy_fill[nmul][nebin]=fcn1->GetParameter(0)/pol; // correction
		asyerr_fill[nmul][nebin]=fcn1->GetParError(0)/pol;
		forfit2->Fit("fcn2","RQ");
		asy_fill2[nmul][nebin]=fcn2->GetParameter(0)/polY;
		asyerr_fill2[nmul][nebin]=fcn2->GetParError(0)/polY;
	// TCanvas *c1 = new TCanvas("c1", "c1",0,0,1600,900);
	// c1->SetGrid(0,0);
				 forfit->SetTitle(picname);
				 forfit->SetLineWidth(3);
				 forfit->SetLineColor(4);
				 forfit->SetMarkerSize(3);
				 forfit->GetXaxis()->SetTitle("Fill Index");
                 forfit->GetYaxis()->SetTitle("jet A_{N}");
                 forfit2->SetTitle(picname2);
				 forfit2->SetLineWidth(3);
				 forfit2->SetLineColor(4);
				 forfit2->SetMarkerSize(3);
                 forfit2->GetXaxis()->SetTitle("Fill Index");
                 forfit2->GetYaxis()->SetTitle("jet A_{N}");
	if(updateplot){
		forfit->Draw("AP*");
		c1->SaveAs(picname);
		c1->Clear();
		forfit2->Draw("AP*");
		c1->SaveAs(picname2);
	}
	}
//	cout<<" sumasy= "<<sumasy[nmbin][nebin]<<"in "<<nmbin<<" "<<nebin<<endl;
    }
}	
TGraphErrors *gasybs[NMul];
for (int nmul=0; nmul<NMul; nmul++){
	gasybs[nmul]=new TGraphErrors(nebins,xf[nmul], asy_fill[nmul],ex0,asyerr_fill[nmul]);//stat uncertainty
	gasybs[nmul]->SetMarkerStyle(20+nmul*4);
	gasybs[nmul]->SetMarkerSize(1.3);
	gasybs[nmul]->SetMarkerColor(kBlue);
	gasybs[nmul]->SetLineWidth(2);
	gasybs[nmul]->SetLineColor(kBlue);
	gjetAn11[nmul] =  (TGraphErrors*)gasybs[nmul]->Clone();
//	gjetAn11Err[nmul] =  (TGraphErrors*)gasybserr[nmul]->Clone();
for (int nebin=0; nebin<nebins; nebin++){
			cout<<nebin<<" "<<xf[nmul][nebin]<<" "<<jetPt11[nmul][nebin]<<" " <<asy_fill[nmul][nebin]<<" "<<asyerr_fill[nmul][nebin]<<" "<<endl;
}}




}

void average(double asy1, double asy2, double err1, double err2,double & asyFinal,double & asyerrFinal){
asyFinal= (asy1/err1/err1+asy2/err2/err2)/(1/err1/err1+1/err2/err2);
asyerrFinal=1/TMath::Sqrt(1/err1/err1+1/err2/err2);
}
void average(double asy1, double asy2,double asy3, double err1, double err2,double err3, double & asyFinal,double & asyerrFinal){
asyFinal= (asy1/err1/err1+asy2/err2/err2+asy3/err3/err3)/(1/err1/err1+1/err2/err2+1/err3/err3);
asyerrFinal=1/TMath::Sqrt(1/err1/err1+1/err2/err2+1/err3/err3);
}

void STAR_2020_200gev_jet()
{
//=========Macro generated from canvas: result/result
//=========  (Fri Feb 28 16:07:41 2020) by ROOT version 6.16/00
   TLatex *   tex = new TLatex(0.08,0.6,"A_{N}");
   tex->SetTextSize(0.08);
   tex->SetTextAngle(90);
   tex->SetLineWidth(2);
//   tex->Draw();
      tex = new TLatex(0.85,0.05,"x_{F}");
   tex->SetLineWidth(2);
//   tex->Draw();
  
// ------------>Primitives in pad: nemo
   TPad *nemo = new TPad("nemo", "This is nemo",0.1,0.1,1,1);
//   nemo->Draw();
   nemo->cd();
   nemo->Range(0.02499999,-0.025,0.715,0.025);
   nemo->SetFillColor(0);
   nemo->SetFillStyle(4000);
   nemo->SetBorderMode(0);
   nemo->SetBorderSize(0);
   nemo->SetFrameFillStyle(0);
   nemo->SetFrameBorderMode(0);
   nemo->SetFrameFillStyle(0);
   nemo->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1[15] = {
   0.14,
   0.1728571,
   0.2057143,
   0.2385714,
   0.2714286,
   0.3042857,
   0.3371429,
   0.37,
   0.4028571,
   0.4357143,
   0.4685714,
   0.5014286,
   0.5342857,
   0.5671429,
   0.6};
   Double_t Graph0_fy1[15] = {
   -0.0003907174,
   0.0001888173,
   0.0009836138,
   0.001845132,
   0.002653916,
   0.003250949,
   0.003572249,
   0.003547877,
   0.003165656,
   0.0024356,
   0.001379411,
   4.514817e-05,
   -0.001513305,
   -0.003235699,
   -0.005059186};
   TGraph *graph = new TGraph(15,Graph0_fx1,Graph0_fy1);
   graph->SetName("Graph0");
   graph->SetTitle("");
   graph->SetFillStyle(1000);
   graph->SetLineColor(2);
   graph->SetLineWidth(3);
   
   TH1F *Graph_Graph01 = new TH1F("Graph_Graph01","",100,0.094,0.646);
   Graph_Graph01->SetMinimum(-0.02);
   Graph_Graph01->SetMaximum(0.02);
   Graph_Graph01->SetDirectory(0);
   Graph_Graph01->SetStats(0);
   Graph_Graph01->GetXaxis()->SetNdivisions(8);
   Graph_Graph01->GetXaxis()->SetLabelFont(42);
   Graph_Graph01->GetXaxis()->SetLabelOffset(0.04);
   Graph_Graph01->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph01->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph01->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01->GetXaxis()->SetTitleColor(0);
   Graph_Graph01->GetXaxis()->SetTitleFont(42);
   Graph_Graph01->GetYaxis()->SetNdivisions(8);
   Graph_Graph01->GetYaxis()->SetLabelFont(42);
   Graph_Graph01->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph01->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph01->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph01->GetYaxis()->SetTitleFont(42);
   Graph_Graph01->GetZaxis()->SetLabelFont(42);
   Graph_Graph01->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph01->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph01->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph01);
   
   graph->Draw("acp");
   
   Double_t Graph1_fx2[31] = {
   0.14,
   0.1728571,
   0.2057143,
   0.2385714,
   0.2714286,
   0.3042857,
   0.3371429,
   0.37,
   0.4028571,
   0.4357143,
   0.4685714,
   0.5014286,
   0.5342857,
   0.5671429,
   0.6,
   0.6,
   0.5671429,
   0.5342857,
   0.5014286,
   0.4685714,
   0.4357143,
   0.4028571,
   0.37,
   0.3371429,
   0.3042857,
   0.2714286,
   0.2385714,
   0.2057143,
   0.1728571,
   0.14,
   0.14};
   Double_t Graph1_fy2[31] = {
   -0.001307996,
   -0.00156192,
   -0.001415446,
   -0.0008023628,
   5.20857e-05,
   0.0008856947,
   0.001347203,
   0.001295749,
   0.0006336965,
   -0.001706759,
   -0.00440633,
   -0.007358797,
   -0.01048611,
   -0.01374305,
   -0.01710126,
   0.01154222,
   0.01129045,
   0.01074722,
   0.009933569,
   0.008976682,
   0.007801066,
   0.006492334,
   0.005138614,
   0.004204543,
   0.004503687,
   0.004541036,
   0.003930363,
   0.002886102,
   0.001538422,
   0.0002876129,
   -0.001307996};
   graph = new TGraph(31,Graph1_fx2,Graph1_fy2);
   graph->SetName("Graph1");
   graph->SetTitle("Graph");
   graph->SetFillColor(16);
   graph->SetFillStyle(1000);
   graph->SetLineWidth(0);
   
   TH1F *Graph_Graph12 = new TH1F("Graph_Graph12","Graph",100,0.094,0.646);
   Graph_Graph12->SetMinimum(-0.01996561);
   Graph_Graph12->SetMaximum(0.01440657);
   Graph_Graph12->SetDirectory(0);
   Graph_Graph12->SetStats(0);
   Graph_Graph12->GetXaxis()->SetNdivisions(8);
   Graph_Graph12->GetXaxis()->SetLabelFont(42);
   Graph_Graph12->GetXaxis()->SetLabelOffset(0.04);
   Graph_Graph12->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph12->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph12->GetXaxis()->SetTitleOffset(1);
   Graph_Graph12->GetXaxis()->SetTitleColor(0);
   Graph_Graph12->GetXaxis()->SetTitleFont(42);
   Graph_Graph12->GetYaxis()->SetNdivisions(8);
   Graph_Graph12->GetYaxis()->SetLabelFont(42);
   Graph_Graph12->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph12->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph12->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph12->GetYaxis()->SetTitleFont(42);
   Graph_Graph12->GetZaxis()->SetLabelFont(42);
   Graph_Graph12->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph12->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph12->GetZaxis()->SetTitleOffset(1);
   Graph_Graph12->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph12);
   
   graph->Draw("f");
   
   Double_t Graph1_fx3[31] = {
   0.14,
   0.1728571,
   0.2057143,
   0.2385714,
   0.2714286,
   0.3042857,
   0.3371429,
   0.37,
   0.4028571,
   0.4357143,
   0.4685714,
   0.5014286,
   0.5342857,
   0.5671429,
   0.6,
   0.6,
   0.5671429,
   0.5342857,
   0.5014286,
   0.4685714,
   0.4357143,
   0.4028571,
   0.37,
   0.3371429,
   0.3042857,
   0.2714286,
   0.2385714,
   0.2057143,
   0.1728571,
   0.14,
   0.14};
   Double_t Graph1_fy3[31] = {
   -0.001307996,
   -0.00156192,
   -0.001415446,
   -0.0008023628,
   5.20857e-05,
   0.0008856947,
   0.001347203,
   0.001295749,
   0.0006336965,
   -0.001706759,
   -0.00440633,
   -0.007358797,
   -0.01048611,
   -0.01374305,
   -0.01710126,
   0.01154222,
   0.01129045,
   0.01074722,
   0.009933569,
   0.008976682,
   0.007801066,
   0.006492334,
   0.005138614,
   0.004204543,
   0.004503687,
   0.004541036,
   0.003930363,
   0.002886102,
   0.001538422,
   0.0002876129,
   -0.001307996};
   graph = new TGraph(31,Graph1_fx3,Graph1_fy3);
   graph->SetName("Graph1");
   graph->SetTitle("Graph");
   graph->SetFillColor(16);
   graph->SetFillStyle(1000);
   graph->SetLineWidth(0);
   
   TH1F *Graph_Graph_Graph123 = new TH1F("Graph_Graph_Graph123","Graph",100,0.094,0.646);
   Graph_Graph_Graph123->SetMinimum(-0.01996561);
   Graph_Graph_Graph123->SetMaximum(0.01440657);
   Graph_Graph_Graph123->SetDirectory(0);
   Graph_Graph_Graph123->SetStats(0);
   Graph_Graph_Graph123->GetXaxis()->SetNdivisions(8);
   Graph_Graph_Graph123->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph123->GetXaxis()->SetLabelOffset(0.04);
   Graph_Graph_Graph123->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph_Graph123->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph_Graph123->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph123->GetXaxis()->SetTitleColor(0);
   Graph_Graph_Graph123->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph123->GetYaxis()->SetNdivisions(8);
   Graph_Graph_Graph123->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph123->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph_Graph123->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph_Graph123->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph_Graph123->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph123->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph123->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_Graph123->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_Graph123->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph123->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph_Graph123);
   
   graph->Draw("l");
   
   Double_t Graph0_fx4[15] = {
   0.14,
   0.1728571,
   0.2057143,
   0.2385714,
   0.2714286,
   0.3042857,
   0.3371429,
   0.37,
   0.4028571,
   0.4357143,
   0.4685714,
   0.5014286,
   0.5342857,
   0.5671429,
   0.6};
   Double_t Graph0_fy4[15] = {
   -0.0003907174,
   0.0001888173,
   0.0009836138,
   0.001845132,
   0.002653916,
   0.003250949,
   0.003572249,
   0.003547877,
   0.003165656,
   0.0024356,
   0.001379411,
   4.514817e-05,
   -0.001513305,
   -0.003235699,
   -0.005059186};
   graph = new TGraph(15,Graph0_fx4,Graph0_fy4);
   graph->SetName("Graph0");
   graph->SetTitle("");
   graph->SetFillStyle(1000);
   graph->SetLineColor(2);
   graph->SetLineWidth(3);
   
   TH1F *Graph_Graph_Graph014 = new TH1F("Graph_Graph_Graph014","",100,0.094,0.646);
   Graph_Graph_Graph014->SetMinimum(-0.02);
   Graph_Graph_Graph014->SetMaximum(0.02);
   Graph_Graph_Graph014->SetDirectory(0);
   Graph_Graph_Graph014->SetStats(0);
   Graph_Graph_Graph014->GetXaxis()->SetNdivisions(8);
   Graph_Graph_Graph014->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph014->GetXaxis()->SetLabelOffset(0.04);
   Graph_Graph_Graph014->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph_Graph014->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph_Graph014->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph014->GetXaxis()->SetTitleColor(0);
   Graph_Graph_Graph014->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph014->GetYaxis()->SetNdivisions(8);
   Graph_Graph_Graph014->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph014->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph_Graph014->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph_Graph014->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph_Graph014->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph014->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph014->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_Graph014->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_Graph014->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph014->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph_Graph014);
   
   graph->Draw("cp");
   TLine *line = new TLine(0.094,0,0.646,0);
//   line->Draw();
   
   TPaveText *pt = new TPaveText(0.2,0.65,0.4,0.85,"brNDC");
   pt->SetName("description");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextAlign(12);
   TText *pt_LaTex = pt->AddText("STAR");
   pt_LaTex = pt->AddText("P^{#uparrow}P#rightarrow Jet X");
   pt_LaTex = pt->AddText(" #sqrt{s} = 200 (GeV) ");
//   pt->Draw();
   nemo->Modified();
}



