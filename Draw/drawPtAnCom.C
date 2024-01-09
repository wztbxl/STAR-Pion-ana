TGraphErrors *gPtXf1An15 ;
TGraphErrors *gPtXf2An15 ;
TGraphErrors *gPtXf3An15 ;
TGraphErrors *gPtXf1An11 ;
TGraphErrors *gPtXf2An11 ;
TGraphErrors *gPtXf3An11 ;
TGraphErrors *gPtXf1Err15 ;
TGraphErrors *gPtXf2Err15 ;
TGraphErrors *gPtXf3Err15 ;
TGraphErrors *gPtXf1Err11 ;
TGraphErrors *gPtXf2Err11 ;
TGraphErrors *gPtXf3Err11 ;

double ptmean11Xf1[7]={0 , 2.28197 , 2.75819 , 3.39622 , 4.41765 , 5.48167 , 6.40424   };
double ptmean11Xf2[7]={-0, 2.39966 , 2.78545 , 3.47371 , 4.36804 , 5.40924 , 6.49366   };
double ptmean11Xf3[7]={-0, 0 , 2.91929 , 3.60701 , 4.39947 , 5.38342 , 6.40977   };

double ptmean15Xf1[7]={1.78135 , 2.23514 , 2.67572 , 3.06124 , 0 , 0 , 0 };
double ptmean15Xf2[7]={1.74844 , 2.273 , 2.74796 , 3.22564 , 4.005 , 0 , 0 };
double ptmean15Xf3[7]={1.76185 , 2.24919 , 2.75733 , 3.37753 , 4.18825 , 0 , 0 };

   double Syst11= 1.3 ;
   double Syst15= 0.7 ;


bool drawall = 0;
bool syst = 1;
double Rsyst = 0.0;

drawPtAnCom(){


	drawPtAn15();
	drawPtAn11();

	gStyle->SetOptStat(0000);
        gStyle->SetOptDate(0);
		gROOT->SetStyle("Modern");
	 gStyle->SetOptTitle(kFALSE);
        gStyle->SetStatColor(0);
 //       gStyle->SetEndErrorSize(0.05);
        gStyle->SetTitleFillColor(0);
        gStyle->SetFillColor(0);
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
/*
TCanvas *c12 = new TCanvas("c12", "c12",0,0,1200,900);

bkgCom10 = new TH2F("bkgCom10","",20,0.5,8.5,10,-0.02,0.1);
        bkgCom10->GetYaxis()->SetTitle("A_{N}");
        bkgCom10->GetXaxis()->SetTitle("Pt / GeV/c");
       // bkgCom10->GetXaxis()->SetNdivisions(705);;
       // bkgCom10->GetYaxis()->SetNdivisions(505);;

gPtXf1An15->SetMarkerColor(kRed);
gPtXf2An15->SetMarkerColor(kRed);
gPtXf3An15->SetMarkerColor(kRed);
gPtXf1Err15->SetMarkerColor(kRed);
gPtXf2Err15->SetMarkerColor(kRed);
gPtXf3Err15->SetMarkerColor(kRed);
gPtXf1An11->SetMarkerColor(kBlue);
gPtXf2An11->SetMarkerColor(kBlue);
gPtXf3An11->SetMarkerColor(kBlue);
gPtXf1Err11->SetMarkerColor(kBlue);
gPtXf2Err11->SetMarkerColor(kBlue);
gPtXf3Err11->SetMarkerColor(kBlue);

gPtXf1An11->SetMarkerStyle(24);
gPtXf2An11->SetMarkerStyle(20);
gPtXf3An11->SetMarkerStyle(20);
gPtXf1Err11->SetMarkerStyle(24);
gPtXf2Err11->SetMarkerStyle(20);
gPtXf3Err11->SetMarkerStyle(20);
gPtXf1An15->SetMarkerStyle(20);
gPtXf2An15->SetMarkerStyle(25);
gPtXf3An15->SetMarkerStyle(26);
gPtXf1Err15->SetMarkerStyle(20);
gPtXf2Err15->SetMarkerStyle(25);
gPtXf3Err15->SetMarkerStyle(26);

gPtXf1An15->SetLineColor(kRed);
gPtXf2An15->SetLineColor(kRed);
gPtXf3An15->SetLineColor(kRed);
gPtXf1Err15->SetLineColor(kRed);
gPtXf2Err15->SetLineColor(kRed);
gPtXf3Err15->SetLineColor(kRed);
gPtXf1An11->SetLineColor(kBlue);
gPtXf2An11->SetLineColor(kBlue);
gPtXf3An11->SetLineColor(kBlue);
gPtXf1Err11->SetLineColor(kBlue);
gPtXf2Err11->SetLineColor(kBlue);
gPtXf3Err11->SetLineColor(kBlue);


gPtXf1Err15->SetFillStyle(3001);
gPtXf2Err15->SetFillStyle(3001);
gPtXf3Err15->SetFillStyle(3001);
gPtXf1Err11->SetFillStyle(3001);
gPtXf2Err11->SetFillStyle(3001);
gPtXf3Err11->SetFillStyle(3001);

	bkgCom10->Draw();
gPtXf1An15->Draw("psame");
gPtXf1Err15->Draw("p2same");
gPtXf2An15->Draw("psame");
gPtXf2Err15->Draw("p2same");
gPtXf3An15->Draw("psame");
gPtXf3Err15->Draw("p2same");
gPtXf1An11->Draw("psame");
gPtXf1Err11->Draw("p2same");
gPtXf2An11->Draw("psame");
gPtXf2Err11->Draw("p2same");

 TLatex l;
 TLatex l2;
 TLatex l3;
 TLatex l4;
    l.SetTextSize(0.03);
    l2.SetTextSize(0.07);
    l3.SetTextSize(0.07);
    l4.SetTextSize(0.05);


TLegend *leg=new TLegend(0.62,0.7,0.88,0.88);
                leg->SetMargin(0.2);
                leg->SetBorderSize(0);
                leg->SetFillColor(0);
                leg->SetTextSize(0.03);
                leg->AddEntry(gPtXf1An15,"200 GeV 0.212<x_{F}<0.360","PE");
                leg->AddEntry(gPtXf2An15,"200 GeV 0.360<x_{F}<0.430","PE");
                leg->AddEntry(gPtXf3An15,"200 GeV 0.430<x_{F}<0.650","PE");
                leg->AddEntry(gPtXf1An11,"500 GeV 0.192<x_{F}<0.212","PE");
                leg->AddEntry(gPtXf2An11,"500 GeV 0.212<x_{F}<0.360","PE");
leg->Draw();
	double dx=0.7; double dy=0.09;
	double dx1=3; double dy1=0.;
	l.DrawLatex(dx,dy-0.000,"  p^{#uparrow} + p -> #pi^{0} + X @ #sqrt{s}=200 GeV");
//	l.DrawLatex(dx,dy-0.006*20/8,"  2.7 < #eta < 4.0");
	l.DrawLatex(dx,dy-0.012,"  3.4/3.0% beam pol. scale uncertainty not shown");
//	l3.DrawLatex(dx1,dy1-0.035," 0.192<x_{F}<0.232");


c12->SaveAs("DrawPt22AnCom.png");

*/

TCanvas *c11 = new TCanvas("c11", "c11",0,0,1500,600);
	c11->Divide(3,1,0,0);
	   c11->Range(0,0,1,1);
/*
	c11->SetLeftMargin(0.8);
	c11->SetBottomMargin(0.8);
	c11->SetTopMargin(10.8);
	c11->SetRightMargin(10.2);
*/
//	 c11->SetFrameBorderMode(0);

TH2F *bkgCom[6] ;
bkgCom[0] = new TH2F("bkgCom1","",20,0.5,7.5,10,-0.05,0.08);
bkgCom[1] = new TH2F("bkgCom2","",20,0.5,7.5,10,-0.05,0.08);
bkgCom[2] = new TH2F("bkgCom3","",20,0.5,7.5,10,-0.05,0.08);
bkgCom[3] = new TH2F("bkgCom4","",20,0.5,7.5,10,-0.03,0.05);
bkgCom[4] = new TH2F("bkgCom5","",20,0.5,7.5,10,-0.05,0.08);
bkgCom[5] = new TH2F("bkgCom6","",20,0.5,7.5,10,-0.05,0.08);
        //bkgCom[3]->GetYaxis()->SetTitle("A_{N}");
        //bkgCom[3]->GetYaxis()->SetTitleSize(0.5);
        //bkgCom[5]->GetXaxis()->SetTitle("Pt / GeV");
        //bkgCom[3]->GetXaxis()->SetTitleSize(10.5);
	for (int i=0 ; i<6; i++)	{
        bkgCom[0]->GetYaxis()->SetTitle("A_{N}");
        bkgCom[i]->GetYaxis()->SetTitleSize(0.5);
        bkgCom[i]->GetXaxis()->SetNdivisions(705);;
      //  bkgCom[i]->GetXaxis()->SetLabelSize(0);;
        bkgCom[i]->GetYaxis()->SetNdivisions(505);;
        bkgCom[i]->GetYaxis()->SetLabelSize(0);;
        bkgCom[i]->GetXaxis()->SetLabelSize(0.06);;
	}
        bkgCom[0]->GetYaxis()->SetLabelSize(0.06);;
gPtXf1An15->SetMarkerColor(kRed);
gPtXf2An15->SetMarkerColor(kRed);
gPtXf3An15->SetMarkerColor(kRed);
gPtXf1Err15->SetMarkerColor(kRed);
gPtXf2Err15->SetMarkerColor(kRed);
gPtXf3Err15->SetMarkerColor(kRed);
gPtXf1An11->SetMarkerColor(kBlue);
gPtXf2An11->SetMarkerColor(kBlue);
gPtXf3An11->SetMarkerColor(kBlue);
gPtXf1Err11->SetMarkerColor(kBlue);
gPtXf2Err11->SetMarkerColor(kBlue);
gPtXf3Err11->SetMarkerColor(kBlue);

gPtXf1An11->SetMarkerStyle(22);
gPtXf2An11->SetMarkerStyle(22);
gPtXf3An11->SetMarkerStyle(22);
gPtXf1Err11->SetMarkerStyle(20);
gPtXf2Err11->SetMarkerStyle(20);
gPtXf3Err11->SetMarkerStyle(20);

gPtXf1An15->SetLineColor(kRed);
gPtXf2An15->SetLineColor(kRed);
gPtXf3An15->SetLineColor(kRed);
gPtXf1Err15->SetLineColor(kRed);
gPtXf2Err15->SetLineColor(kRed);
gPtXf3Err15->SetLineColor(kRed);
gPtXf1An11->SetLineColor(kBlue);
gPtXf2An11->SetLineColor(kBlue);
gPtXf3An11->SetLineColor(kBlue);
gPtXf1Err11->SetLineColor(kBlue);
gPtXf2Err11->SetLineColor(kBlue);
gPtXf3Err11->SetLineColor(kBlue);


gPtXf1Err15->SetFillStyle(3001);
gPtXf2Err15->SetFillStyle(3001);
gPtXf3Err15->SetFillStyle(3001);
gPtXf1Err11->SetFillStyle(3001);
gPtXf2Err11->SetFillStyle(3001);
gPtXf3Err11->SetFillStyle(3001);

//steve
double ptXf1[4]={1.67,1.93,2.12,2.44};
double ptXf2[5]={1.67,1.93,2.12,2.62,3.15};
double ptXf3[7]={1.67,1.93,2.12,2.65,3.22 ,3.69 ,4.23};
double ex1[4]={0,0,0,0};
double ex2[5]={0,0,0,0,0};
double ex3[7]={0,0,0,0,0,0,0};
double AnXf1[4]={-0.0043,0.0093,0.0067,0.0104};
double ey1[4]={0.007*1,0.0093*0.32,0.0067*0.34,0.0104*0.17};
double AnXf2[5]={0.0085,0.0111,0.00777,0.018,0.026};
double ey2[5]={-0.0085*0.92,0.0111*0.31,0.00777*0.33,0.018*0.05,0.026*0.09};
double AnXf3[7]={0.0278,0.0232,0.0258,0.0279,0.0328,0.037,0.0416};
double ey3[7]={0.0278*0.29,0.0232*0.16,0.0258*0.11,0.0279*0.04,0.0328*0.056,0.037*0.08,0.0416*0.14};
TGraphErrors *gPtXf1An15S =new TGraphErrors(4,ptXf1,AnXf1,ex1,ey1);
TGraphErrors *gPtXf2An15S =new TGraphErrors(5,ptXf2,AnXf2,ex2,ey2);
TGraphErrors *gPtXf3An15S =new TGraphErrors(7,ptXf3,AnXf3,ex3,ey3);
gPtXf1An15S->SetMarkerStyle(24);
gPtXf2An15S->SetMarkerStyle(24);
gPtXf3An15S->SetMarkerStyle(24);
//above from penn state


c11->cd(1);
	bkgCom[0]->Draw();
//	   gPad->SetTickx(-1);
//	   gPad->SetTicky(-1);
	   gPad->SetGrid(0,0);
	   gPad->SetBottomMargin(0.15);
	   gPad->SetLeftMargin(0.1111111111111115);
//gPtXf1An15S->Draw("psame");
gPtXf1An11->Draw("psame");
if(syst) gPtXf1Err11->Draw("[]same");
gPtXf1An15->Draw("psame");
if(syst) gPtXf1Err15->Draw("[]same");
c11->cd(2);
//	   gPad->SetTickx(-1);
//	   gPad->SetTicky(-1);
       gPad->SetBottomMargin(0.15);
		gPad->SetGrid(0,0);
	bkgCom[1]->Draw();
//gPtXf2An15S->Draw("psame");
gPtXf2An11->Draw("psame");
if(syst) gPtXf2Err11->Draw("[]same");
gPtXf2An15->Draw("psame");
if(syst) gPtXf2Err15->Draw("[]same");
c11->cd(3);
//	   gPad->SetTickx(-1);
//	   gPad->SetTicky(0);
	   gPad->SetGrid(0,0);
       gPad->SetBottomMargin(0.15);
	bkgCom[2]->Draw();
//gPtXf3An15S->Draw("psame");
gPtXf3An11->Draw("psame");
if(syst) gPtXf3Err11->Draw("[]same");
gPtXf3An15->Draw("psame");
if(syst) gPtXf3Err15->Draw("[]same");
/*
c11->cd(4);
//	   gPad->SetTickx(0);
//	   gPad->SetTicky(-1);
	   gPad->SetGrid(0,0);
       gPad->SetBottomMargin(0.2);
       gPad->SetLeftMargin(0.15);
	bkgCom[3]->Draw();
gPtXf1An11->Draw("psame");
gPtXf1Err11->Draw("p2same");
c11->cd(5);
//	   gPad->SetTickx(-1);
//	   gPad->SetTicky(-1);
	   gPad->SetGrid(0,0);
       gPad->SetBottomMargin(0.2);
	bkgCom[4]->Draw();
gPtXf2An11->Draw("psame");
gPtXf2Err11->Draw("p2same");
c11->cd(6);
//	   gPad->SetTickx(1);
//	   gPad->SetTicky(1);
	   gPad->SetGrid(0,0);
       gPad->SetBottomMargin(0.2);
	bkgCom[5]->Draw();
gPtXf3An11->Draw("psame");
gPtXf3Err11->Draw("p2same");

*/
 TLatex l;
 TLatex l2;
 TLatex l3;
 TLatex l4;
    l.SetTextSize(0.035);
    l2.SetTextSize(0.06);
    l3.SetTextSize(0.06);
    l4.SetTextSize(0.06);

c11->cd(1);

    l.SetTextSize(0.045);
	double dx=0.7; double dy=0.07;
	double dx1=3; double dy1=0.015;
	l.DrawLatex(dx,dy-0.000,"STAR     p^{#uparrow} + p -> #pi^{0} + X");// @ #sqrt{s}=200/500 GeV");
    l.SetTextSize(0.05);
//	l.DrawLatex(dx,dy-0.006*20/8,"  2.7 < #eta < 4.0");
	l.DrawLatex(dx,dy-0.012,"3.0/3.4% beam pol. scale uncertainty");
    l2.SetTextSize(0.055);
	l2.DrawLatex(dx1,dy1-0.035," 0.18<x_{F}<0.24");
    l2.SetTextSize(0.06);

c11->cd(2);
	l.DrawLatex(dx-0.01,dy-0.012,"not shown");
/*TLegend *leg=new TLegend(0.7,0.85,0.88,0.98);
                leg->SetMargin(0.4);
                leg->SetBorderSize(0);
                leg->SetFillColor(0);
                leg->SetTextSize(0.05);
                leg->AddEntry(gPtXf1An15,"200 GeV ","PE");
                leg->AddEntry(gPtXf1An11,"500 GeV ","PE");

leg->Draw();
*/	l2.DrawLatex(dx1,dy1-0.035," 0.24<x_{F}<0.30");
c11->cd(3);
	l2.DrawLatex(dx1,dy1-0.035," 0.30<x_{F}<0.36");
c11->cd(0);
        TPad*  p= new TPad("p","p",0,0,1,1); p->Draw(); p->cd();
		p->SetFillStyle(0);
		TLatex latex;
    latex.SetTextSize(0.05);
	latex.DrawLatexNDC(.01,.9,"A_{N}");
	latex.DrawLatexNDC(.5,0.03,"p_{T} [GeV/c]");

c11->cd(2);
    TLegend *leg3=new TLegend(0.45,0.86,0.88,0.96);
                leg3->SetMargin(0.4);
                leg3->SetBorderSize(0);
                leg3->SetFillColor(0);
                leg3->SetTextSize(0.07);
                leg3->AddEntry(gPtXf1An15,"200 GeV ","PE");
                leg3->AddEntry(gPtXf1An11,"500 GeV ","PE");
			leg3->Draw();
 if (drawall) c11->SaveAs("DrawPt222AnCom.png");
    // THEORY
     const int Npt=3;
     const int Np200=6;
     const int Np500=6;
    	ifstream theo1_200[Npt];
    	ifstream theo1_500[Npt];
        string word1,word2,word3;
        double T200N[Npt][Np200];
        double T200asy[Npt][Np200];
        double T200asyerr[Npt][Np200];
        double Ex200[Npt][Np200];
        double T500N[Npt][Np500];
        double T500asy[Npt][Np500];
        double T500asyerr[Npt][Np500];
        double Ex500[Npt][Np500];
        double Ptxf15_t[Npt][Np200];
        double Ptxf11_t[Npt][Np500];
		TGraphErrors *gth1_200[Npt];
		TGraphErrors *gth1_500[Npt];
		TGraph *gth1_200L[Npt];
		TGraph *gth1_500L[Npt];
		int Np200_1,Np500_1;
        for (int npt=0; npt<Npt; npt++){
        	theo1_500[npt].open(Form("theory/Alexei/pi0_AN_vs_PT-500-xFbin%i.dat",npt+1),ios::in);
        	theo1_200[npt].open(Form("theory/Alexei/pi0_AN_vs_PT-200-xFbin%i.dat",npt+1),ios::in);
			if (npt==0) {Np200_1=4;Np500_1=4;}
			if (npt==1) {Np200_1=4;Np500_1=4;}
			if (npt==2) {Np200_1=5;Np500_1=2;}
        	for (int np=0; np<Np200; np++){
				T200asy[npt][np]=-1;
				T500asy[npt][np]=-1;
             	Ex200[npt][np]=0;
             	Ex500[npt][np]=0;
				Ptxf11_t[npt][np]=-1;
				Ptxf15_t[npt][np]=-1;
			}
        	for (int np=0; np<=Np200_1; np++){
            	if (np==0) theo1_200[npt]>>word1>>word2>>word3;
            	else theo1_200[npt]>>T200N[npt][np-1]>>T200asy[npt][np-1]>>T200asyerr[npt][np-1];
				if (npt==0) Ptxf15_t[npt][np]=ptmean15Xf1[np];
				if (npt==1) Ptxf15_t[npt][np]=ptmean15Xf2[np];
				if (npt==2) Ptxf15_t[npt][np]=ptmean15Xf3[np];
            }    
        	for (int np=0; np<=Np500_1; np++){
            	if (np==0) theo1_500[npt]>>word1>>word2>>word3;
            	else theo1_500[npt]>>T500N[npt][np-1]>>T500asy[npt][np-1]>>T500asyerr[npt][np-1];
				if (npt==0) Ptxf11_t[npt][np]=ptmean11Xf1[np+1];
				if (npt==1) Ptxf11_t[npt][np]=ptmean11Xf2[np+1];
				if (npt==2) Ptxf11_t[npt][np]=ptmean11Xf3[np+3];
            }    
            theo1_200[npt].close();
            theo1_500[npt].close();
      		gth1_200[npt]=new TGraphErrors(Np200_1[npt],Ptxf15_t[npt],T200asy[npt],Ex200[npt],T200asyerr[npt]);
      		gth1_500[npt]=new TGraphErrors(Np500_1[npt],Ptxf11_t[npt],T500asy[npt],Ex500[npt],T500asyerr[npt]);
      		gth1_200L[npt]=new TGraph(Np200_1[npt],Ptxf15_t[npt],T200asy[npt]);
      		gth1_500L[npt]=new TGraph(Np500_1[npt],Ptxf11_t[npt],T500asy[npt]);
        	gth1_200L[npt]->SetLineColor(kRed);
        	gth1_200[npt]->SetFillColorAlpha(kRed-9,0.35);
        	gth1_500L[npt]->SetLineColor(kBlue);
        	gth1_500[npt]->SetFillColorAlpha(kBlue-7,0.35);
    c11->cd(npt+1);   
        gth1_200[npt]->Draw("3csame");
        gth1_500[npt]->Draw("3csame");
        gth1_200L[npt]->Draw("csame");
        gth1_500L[npt]->Draw("csame");
    	}
    c11->cd(3);   
    TLegend *leg4=new TLegend(0.25,0.86,0.88,0.96);
                leg4->SetMargin(0.3);
                leg4->SetBorderSize(0);
                leg4->SetFillColor(0);
                leg4->SetTextSize(0.07);
                leg4->AddEntry(gth1_200[0],"Theory 200 GeV","f");
                leg4->AddEntry(gth1_500[0],"Theory 500 GeV","f");
			leg4->Draw();




//c11->SaveAs("DrawPtCheck.png");
c11->SaveAs("DrawPt222AnComT.png");


}
drawPtAn15(int Mset=0){
		gROOT->SetStyle("Modern");
	 gStyle->SetOptTitle(kFALSE);
	gStyle->SetOptStat(0000);
        gStyle->SetOptFit(1111);//0000);
        gStyle->SetStatColor(0);
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
	
bool updateplot =0;

    const int Nfill=53;
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
//	cout<<fillnum[nfill]<<endl;;
}


const int nebins = 3;
double ebinlows[nebins] = { 18,  24, 30};
double ebinhighs[nebins] = { 24,  30,  36};
const int nptbins = 7;
double ptbinlows[nptbins] = { 1.5,2,2.5, 3, 4,5,6 };
double ptbinhighs[nptbins] = {2,2.5,3, 4, 5,6,7};
const int nmbins = 2; 
double mbinlows[nmbins] = {0.00, 0.20};
double mbinhighs[nmbins] = {0.20, 0.30};
const int nxfbins=3;

char resultname[400];
char resultname2[400];
char picname[400];
char picname2[400];
double ex[nptbins]= {0,0,0,0,0};//x error 
double ex1[nxfbins][nptbins];//for syst
double ex0[nxfbins][nptbins];//Pt uncertainty
double xf[nxfbins][nptbins] ; //Pt
double xf1[nptbins];
double xf2[nptbins];
for (int nptbin=0; nptbin<nptbins; nptbin++){
//xf[nptbin]= (ptbinlows[nptbin]+ptbinhighs[nptbin])/2.0/250; //    !!!!!!!!!!type change!!!!!!!!!!
xf1[nptbin]=( (ptbinlows[nptbin]+ptbinhighs[nptbin])/2-0.05);
xf2[nptbin]=( (ptbinlows[nptbin]+ptbinhighs[nptbin])/2+0.05);
//xf[0][nptbin]= (ptbinlows[nptbin]+ptbinhighs[nptbin])/2.0;
//xf[1][nptbin]= (ptbinlows[nptbin]+ptbinhighs[nptbin])/2.0;
//xf[2][nptbin]= (ptbinlows[nptbin]+ptbinhighs[nptbin])/2.0;
xf[0][nptbin]= ptmean15Xf1[nptbin];
xf[1][nptbin]= ptmean15Xf2[nptbin];
xf[2][nptbin]= ptmean15Xf3[nptbin];
ex0[0][nptbin]= Rsyst*xf[0][nptbin];
ex0[1][nptbin]= Rsyst*xf[1][nptbin];;
ex0[2][nptbin]= Rsyst*xf[2][nptbin];;
//out<< xf[nptbin]<<" " << xf1[nptbin]<<endl;
ex1[0][nptbin]=0.1;
ex1[1][nptbin]=0.1;
ex1[2][nptbin]=0.1;
}
ifstream result;
ifstream result2;

TF1 *fcn1 = new TF1 ("fcn1","pol0",0,60);
TF1 *fcn2 = new TF1 ("fcn2","pol0",0,60);


//TFile *fout= new TFile ("DrawAn_fracfix.root","recreate");
//fout->cd();

double asy_fill[nmbins][nebins][nptbins];
double asyerr_fill[nmbins][nebins][nptbins];
double asy_fill2[nmbins][nebins][nptbins];
double asyerr_fill2[nmbins][nebins][nptbins];

for (int nmbin=0; nmbin<nmbins;nmbin++){
   for (int nebin=0; nebin<nebins; nebin++){
   	for (int nptbin=0; nptbin<nptbins; nptbin++){
	int fill[Nfill];
	double ene[Nfill];
	double asy[Nfill];
	double asy2[Nfill];
	double asyerr[Nfill];
	double asyerr2[Nfill];
	double ml[Nfill];
	double mh[Nfill];
	double p0[Nfill];
	double p0e[Nfill];
	double p02[Nfill];
	double p0e2[Nfill];
		for (int nfill=0; nfill<Nfill;nfill++){
		//cout<<"bin  "<<mbinlows[nmbin]<<"   "<<mbinhighs[nmbin]<<endl;
		sprintf(resultname,"/star/u/zwzhu/01zwzhu/ana/New/PaperCode/Code2/Run15/result/PtAN2/PtAN_Fill%d_mass%.2fto%.2fGeV_E%.1fto%.1f_Pt%.1fto%.1fGeV.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin],ptbinlows[nptbin],ptbinhighs[nptbin]);
		sprintf(resultname2,"/star/u/zwzhu/01zwzhu/ana/New/PaperCode/Code2/Run15/result/PtAN2/PtANy_Fill%d_mass%.2fto%.2fGeV_E%.1fto%.1f_Pt%.1fto%.1fGeV.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin],ptbinlows[nptbin],ptbinhighs[nptbin]);
		asyerr2[nfill]=0;
		asyerr[nfill]=0;
		TString infile(resultname);
		TString infile2(resultname2);
//		cout<<resultname<<endl;
		result.open(resultname,ios::in);
		result2.open(resultname2,ios::in);
		if(!result  )  cout<<" file not exist "<< resultname<<endl;
	
		result>>fill[nfill]>>ene[nfill]>>asy[nfill]>>asyerr[nfill]>>p0[nfill]>>p0e[nfill]>>ml[nfill]>>mh[nfill];
		result2>>fill[nfill]>>ene[nfill]>>asy2[nfill]>>asyerr2[nfill]>>p02[nfill]>>p0e2[nfill]>>ml[nfill]>>mh[nfill];
//		asy2[nfill]=0.004+0.00*nfill; asyerr2[nfill]=0.004;
		result.close();
		result2.close();

        if (asyerr2[nfill]==0. && nptbin < 4) {//  cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<resultname2<<endl  ;    
            asy2[nfill]=0;    
            asyerr2[nfill]=999;
        }   

        if (asyerr[nfill]==0. && nptbin < 4) {//  cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<resultname<<endl  ;    
            asy[nfill]=0; 
            asyerr[nfill]=999;
        }   

		//cout<<fill[nfill]<<" asyraw= "<<asy2[nfill]<<" err "<<asyerr2[nfill]<<endl;
//		sumasy[nmbin][nebin] += asy[nfill];
//		sumerr[nmbin][nebin] += asyerr[nfill]*asyerr[nfill];	
		}	
		
		sprintf(picname,"Otherpic/PtAN_AllFill_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.png",mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
		sprintf(picname2,"Otherpic/PtANy_AllFill_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.png",mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
		TGraphErrors *forfit=new TGraphErrors(fillbin,filldouble,asy,fillex,asyerr);
		TGraphErrors *forfit2=new TGraphErrors(fillbin,filldouble,asy2,fillex,asyerr2);
		forfit->Fit("fcn1","RQ");
		asy_fill[nmbin][nebin][nptbin]=fcn1->GetParameter(0);
		asyerr_fill[nmbin][nebin][nptbin]=fcn1->GetParError(0);
		forfit2->Fit("fcn2","RQ");
		asy_fill2[nmbin][nebin][nptbin]=fcn2->GetParameter(0);
		asyerr_fill2[nmbin][nebin][nptbin]=fcn2->GetParError(0);
	//		cout<<asy_fill[nmbin][nebin]<<" "<<asyerr_fill[nmbin][nebin]<<" "<<endl;
	// TCanvas *c1 = new TCanvas("c1", "c1",0,0,1600,900);
				 forfit->SetTitle(picname);
				 forfit->SetLineWidth(3);
				 forfit->SetLineColor(4);
				 forfit->SetMarkerSize(3);
				 forfit->GetXaxis()->SetTitle("Fill Index");
                 forfit->GetYaxis()->SetTitle("A_{N}");
                 forfit2->SetTitle(picname2);
				 forfit2->SetLineWidth(3);
				 forfit2->SetLineColor(4);
				 forfit2->SetMarkerSize(3);
                 forfit2->GetXaxis()->SetTitle("Fill Index");
                 forfit2->GetYaxis()->SetTitle("A_{N}");
	if(updateplot){
		forfit->Draw("AP*");
		c1->SaveAs(picname);
		c1->Clear();
		forfit2->Draw("AP*");
		c1->SaveAs(picname2);
	}
//	cout<<" sumasy= "<<sumasy[nmbin][nebin]<<"in "<<nmbin<<" "<<nebin<<endl;
    	}
	}	
}


//12 first mass bin
//23 second mass bin
//double asyb01[nxfbin][nptbins];
double asyb12[nxfbins][nptbins];
double asyb23[nxfbins][nptbins];
//double asyerrb01[nxfbin][nptbins];
double asyerrb12[nxfbins][nptbins];
double asyerrb23[nxfbins][nptbins];
//double asyy01[nxfbin][nptbins];
double asyy12[nxfbins][nptbins];
double asyy23[nxfbins][nptbins];
//double asyerry01[nxfbin][nptbins];
double asyerry12[nxfbins][nptbins];
double asyerry23[nxfbins][nptbins];

for (int nptbin=0; nptbin<nptbins; nptbin++){
	for (int nebin=0; nebin<nebins; nebin++){
// mass e pt -- 
/*
// e0 1 -> xf 0 
// e2 3 -> xf 1 
// e4-6 -> xf 2 
average(asy_fill[0][0][nptbin],asy_fill[0][1][nptbin],asyerr_fill[0][1][nptbin],asyerr_fill[0][1][nptbin],asyb12[0][nptbin],asyerrb12[0][nptbin]);
average(asy_fill[0][2][nptbin],asy_fill[0][3][nptbin],asyerr_fill[0][2][nptbin],asyerr_fill[0][3][nptbin],asyb12[1][nptbin],asyerrb12[1][nptbin]);
average(asy_fill[0][4][nptbin],asy_fill[0][5][nptbin],asy_fill[0][6][nptbin],asyerr_fill[0][4][nptbin],asyerr_fill[0][5][nptbin],asyerr_fill[0][6][nptbin],asyb12[2][nptbin],asyerrb12[2][nptbin]);
average(asy_fill2[0][0][nptbin],asy_fill2[0][1][nptbin],asyerr_fill2[0][1][nptbin],asyerr_fill2[0][1][nptbin],asyy12[0][nptbin],asyerry12[0][nptbin]);
average(asy_fill2[0][2][nptbin],asy_fill2[0][3][nptbin],asyerr_fill2[0][2][nptbin],asyerr_fill2[0][3][nptbin],asyy12[1][nptbin],asyerry12[1][nptbin]);
average(asy_fill2[0][4][nptbin],asy_fill2[0][5][nptbin],asy_fill2[0][6][nptbin],asyerr_fill2[0][4][nptbin],asyerr_fill2[0][5][nptbin],asyerr_fill2[0][6][nptbin],asyy12[2][nptbin],asyerry12[2][nptbin]);
*/
        asyb12[nebin][nptbin]=asy_fill[0][nebin][nptbin];
        asyb23[nebin][nptbin]=asy_fill[1][nebin][nptbin];
        asyerrb12[nebin][nptbin]=asyerr_fill[0][nebin][nptbin];
        asyerrb23[nebin][nptbin]=asyerr_fill[1][nebin][nptbin];
        asyy12[nebin][nptbin]=asy_fill2[0][nebin][nptbin];
        asyy23[nebin][nptbin]=asy_fill2[1][nebin][nptbin];
        asyerry12[nebin][nptbin]=asyerr_fill2[0][nebin][nptbin];
        asyerry23[nebin][nptbin]=asyerr_fill2[1][nebin][nptbin];
    //    cout<<" signal region="<<asyb12[nebin][nptbin]<<" +  "<<asyerrb12[nebin][nptbin]<<" sb region"<<asyb23[nebin][nptbin]<<" +  "<<asyerrb23[nebin][nptbin]<<endl;

	}
}
/*
// TCanvas *c1 = new TCanvas("c1", "c1",0,0,1200,900);
//TGraphErrors *gasyb01=new TGraphErrors(nptbins,xf,asyb01,ex,asyerrb01);
TGraphErrors *gasyb12=new TGraphErrors(nptbins,xf,asyb12,ex,asyerrb12);
TGraphErrors *gasyb23=new TGraphErrors(nptbins,xf,asyb23,ex,asyerrb23);
//TGraphErrors *gasyy01=new TGraphErrors(nptbins,xf,asyy01,ex,asyerry01);
TGraphErrors *gasyy12=new TGraphErrors(nptbins,xf,asyy12,ex,asyerry12);
TGraphErrors *gasyy23=new TGraphErrors(nptbins,xf,asyy23,ex,asyerry23);
//gasy->Draw("ap*");
//gasyb01->SetTitle("Signal m=0.0~0.1");
gasyb12->SetTitle("Signal m=0.1~0.2");
gasyb23->SetTitle("Signal m=0.2~0.3");
//gasyb01->GetXaxis()->SetTitle("PiE/Gev");
//gasyb01->GetYaxis()->SetTitle("A_{N}");
gasyb12->GetXaxis()->SetTitle("PiE/Gev");
gasyb12->GetYaxis()->SetTitle("A_{N}");
gasyb23->GetXaxis()->SetTitle("PiE/Gev");
gasyb23->GetYaxis()->SetTitle("A_{N}");
//gasyy01->SetTitle("Signal m=0.0~0.1");
gasyy12->SetTitle("Signal m=0.1~0.2");
gasyy23->SetTitle("Signal m=0.2~0.3");
//gasyy01->GetXaxis()->SetTitle("PiE/Gev");
//gasyy01->GetYaxis()->SetTitle("A_{N}");
gasyy12->GetXaxis()->SetTitle("PiE/Gev");
gasyy12->GetYaxis()->SetTitle("A_{N}");
gasyy23->GetXaxis()->SetTitle("PiE/Gev");
gasyy23->GetYaxis()->SetTitle("A_{N}");
//c1->Print("test.png");
*/
double asybs[nxfbins][nptbins];
double asyerrbs[nxfbins][nptbins];
double asyerrbs1[nxfbins][nptbins]={0,0,0,0,0};
double asyerrys1[nxfbins][nptbins]={0,0,0,0,0};
double asyys[nxfbins][nptbins];
double asyerrys[nxfbins][nptbins];
double asybb[nxfbins][nptbins];
double asyerrbb[nxfbins][nptbins];
double asyerrbb1[nxfbins][nptbins]={0,0,0,0,0};
double asyerryb1[nxfbins][nptbins]={0,0,0,0,0};
double asyyb[nxfbins][nptbins];
double asyerryb[nxfbins][nptbins];
double ferrbs1[nxfbins][nptbins];
double ferrbs2[nxfbins][nptbins];
double ferrys1[nxfbins][nptbins];
double ferrys2[nxfbins][nptbins];
double ferrbb1[nxfbins][nptbins];
double ferrbb2[nxfbins][nptbins];
double ferryb1[nxfbins][nptbins];
double ferryb2[nxfbins][nptbins];


double f1[nxfbins][nptbins];//sig in sig
double f2[nxfbins][nptbins];//sig in bkg
double f1E[nxfbins][nptbins];//
double f2E[nxfbins][nptbins];//

ifstream frac1;
frac1.open("./txt/frac15PtXf1.txt",ios::in);
ifstream frac2;
frac2.open("./txt/frac15PtXf2.txt",ios::in);
ifstream frac3;
frac3.open("./txt/frac15PtXf3.txt",ios::in);
for (int i=0 ; i<nptbins ; i++){
frac1>>f1[0][i]>>f1E[0][i]>>f2[0][i]>>f2E[0][i];
frac2>>f1[1][i]>>f1E[1][i]>>f2[1][i]>>f2E[1][i];
frac3>>f1[2][i]>>f1E[2][i]>>f2[2][i]>>f2E[2][i];
}

double asyFinal;
double asyerrFinal;

	for (int nxfbin=0; nxfbin<nxfbins; nxfbin++){
		cout<<nxfbin<<endl;
for (int nptbin=0; nptbin<nptbins; nptbin++){

	double f3=(1-f1[nxfbin][nptbin])/(1-f2[nxfbin][nptbin]);
	double f4=f1[nxfbin][nptbin]/f2[nxfbin][nptbin];

//12-signal region 23bkg region
asybs[nxfbin][nptbin]=(asyb12[nxfbin][nptbin]-asyb23[nxfbin][nptbin]*f3)/(1-f3)/pol;
asyerrbs[nxfbin][nptbin]=TMath::Sqrt(asyerrb12[nxfbin][nptbin]*asyerrb12[nxfbin][nptbin]+asyerrb23[nxfbin][nptbin]*asyerrb23[nxfbin][nptbin]*f3*f3)/TMath::Abs(1-f3)/pol;
asyys[nxfbin][nptbin]=(asyy12[nxfbin][nptbin]-asyy23[nxfbin][nptbin]*f3)/(1-f3)/polY;
asyerrys[nxfbin][nptbin]=TMath::Sqrt(asyerry12[nxfbin][nptbin]*asyerry12[nxfbin][nptbin]+asyerry23[nxfbin][nptbin]*asyerry23[nxfbin][nptbin]*f3*f3)/TMath::Abs(1-f3)/polY;
asybb[nxfbin][nptbin]=(asyb12[nxfbin][nptbin]-asyb23[nxfbin][nptbin]*f4)/(1-f4)/pol;
asyerrbb[nxfbin][nptbin]=TMath::Sqrt(asyerrb12[nxfbin][nptbin]*asyerrb12[nxfbin][nptbin]+asyerrb23[nxfbin][nptbin]*asyerrb23[nxfbin][nptbin]*f4*f4)/TMath::Abs(1-f4)/pol;
asyyb[nxfbin][nptbin]=(asyy12[nxfbin][nptbin]-asyy23[nxfbin][nptbin]*f4)/(1-f4)/polY;
asyerryb[nxfbin][nptbin]=TMath::Sqrt(asyerry12[nxfbin][nptbin]*asyerry12[nxfbin][nptbin]+asyerry23[nxfbin][nptbin]*asyerry23[nxfbin][nptbin]*f4*f4)/TMath::Abs(1-f4)/polY;

//asyerrbs1[nxfbin][nptbin]=sqrt(pow(asyerrbs[nxfbin][nptbin],2)+pow(unpol*asybs[nxfbin][nptbin]/pol/pol,2));//with unpol
//asyerrbb1[nxfbin][nptbin]=sqrt(pow(asyerrbb[nxfbin][nptbin],2)+pow(unpol*asybb[nxfbin][nptbin]/pol/pol,2));//with unpol
//12 signal region 23 background region
//uncertaintt of f1 f2
//sig
ferrys1[nxfbin][nptbin]=((asyy12[nxfbin][nptbin]-asyy23[nxfbin][nptbin])*(1-f2[nxfbin][nptbin])/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin])/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin]))/polY;
ferrys2[nxfbin][nptbin]=((asyy12[nxfbin][nptbin]-asyy23[nxfbin][nptbin])*(1-f1[nxfbin][nptbin])/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin])/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin]))/polY;
ferrbs1[nxfbin][nptbin]=((asyb12[nxfbin][nptbin]-asyb23[nxfbin][nptbin])*(1-f2[nxfbin][nptbin])/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin])/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin]))/pol;
ferrbs2[nxfbin][nptbin]=((asyb12[nxfbin][nptbin]-asyb23[nxfbin][nptbin])*(1-f1[nxfbin][nptbin])/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin])/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin]))/pol;
//bkg
ferryb1[nxfbin][nptbin]=((asyy12[nxfbin][nptbin]-asyy23[nxfbin][nptbin])*f2[nxfbin][nptbin]/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin])/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin]))/polY;
ferryb2[nxfbin][nptbin]=((asyy12[nxfbin][nptbin]-asyy23[nxfbin][nptbin])*f1[nxfbin][nptbin]/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin])/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin]))/polY;
ferrbb1[nxfbin][nptbin]=((asyb12[nxfbin][nptbin]-asyb23[nxfbin][nptbin])*f2[nxfbin][nptbin]/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin])/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin]))/pol;
ferrbb2[nxfbin][nptbin]=((asyb12[nxfbin][nptbin]-asyb23[nxfbin][nptbin])*f1[nxfbin][nptbin]/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin])/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin]))/pol;

asyerrbs1[nxfbin][nptbin]=sqrt(pow(ferrbs1[nxfbin][nptbin]*f1E[nxfbin][nptbin],2)+pow(ferrbs2[nxfbin][nptbin]*f2E[nxfbin][nptbin],2));
asyerrbb1[nxfbin][nptbin]=sqrt(pow(ferrbb1[nxfbin][nptbin]*f1E[nxfbin][nptbin],2)+pow(ferrbb2[nxfbin][nptbin]*f2E[nxfbin][nptbin],2));
asyerrys1[nxfbin][nptbin]=sqrt(pow(ferrys1[nxfbin][nptbin]*f1E[nxfbin][nptbin],2)+pow(ferrys2[nxfbin][nptbin]*f2E[nxfbin][nptbin],2));
asyerryb1[nxfbin][nptbin]=sqrt(pow(ferryb1[nxfbin][nptbin]*f1E[nxfbin][nptbin],2)+pow(ferryb2[nxfbin][nptbin]*f2E[nxfbin][nptbin],2));

//cout<<nptbin<<"  f3="<<f3<<" f4="<<f4<<" bberr="<<asyerrbb[nxfbin][nptbin]<<" bserr="<<asyerrbs[nxfbin][nptbin]<<" bb="<<asybb[nxfbin][nptbin]<<" bs="<<asybs[nxfbin][nptbin]<<" yberr="<<asyerryb[nxfbin][nptbin]<<"ybserr="<<asyerrys[nxfbin][nptbin]<<" yb="<<asyyb[nxfbin][nptbin]<<" ys="<<asyys[nxfbin][nptbin]<<"  "<< asyerrbs1[nxfbin][nptbin]<<"  "<< asyerrbb1[nxfbin][nptbin]<<"  "<< asyerrys1[nxfbin][nptbin]<<"  "<< asyerryb1[nxfbin][nptbin]<<endl;
//cout<<"  f1="<<f1[nxfbin][nptbin]<<" f2="<<f2[nxfbin][nptbin]<<"     "<<"  asy23="<<asyy23[nxfbin][nptbin]<<" asyerrb23="<<asyerry23[nxfbin][nptbin]<<"  asy12="<<asyy12[nxfbin][nptbin]<<" asyerrb12="<<asyerry12[nxfbin][nptbin]<<endl;

//	cout<<asyerrbs1[nxfbin][nptbin]<<" "<<asyerrbb1[nxfbin][nptbin]<<" "<<asyerrys1[nxfbin][nptbin]<<" "<<asyerryb1[nxfbin][nptbin]<<" " <<endl;
asyerrbs1[nxfbin][nptbin] = asybs[nxfbin][nptbin] * Syst15/100;
if (nxfbin==0)	cout<<nptbin<<" "<<ptmean15Xf1[nptbin]  <<" "<<asybs[nxfbin][nptbin]<<" "<<asyerrbs[nxfbin][nptbin]<<" "<<asyerrbs1[nxfbin][nptbin]<<endl;
if (nxfbin==1)	cout<<nptbin<<" "<<ptmean15Xf2[nptbin]  <<" "<<asybs[nxfbin][nptbin]<<" "<<asyerrbs[nxfbin][nptbin]<<" "<<asyerrbs1[nxfbin][nptbin]<<endl;
if (nxfbin==2)	cout<<nptbin<<" "<<ptmean15Xf3[nptbin]  <<" "<<asybs[nxfbin][nptbin]<<" "<<asyerrbs[nxfbin][nptbin]<<" "<<asyerrbs1[nxfbin][nptbin]<<endl;
	}
}



    TGraphErrors *gasybs[3];
    TGraphErrors *gasybb[3];
    TGraphErrors *gasybberr[3];
    TGraphErrors *gasybserr[3];
    TGraphErrors *gasyys[3];
    TGraphErrors *gasyyb[3];
    TGraphErrors *gasyyberr[3];
    TGraphErrors *gasyyserr[3];

	//cout<<"o000000000000 "<<asybs[0][0]<<" "<<xf[0][0]<<endl;
	int outlier[10][2]={ {0,4},{0,5},{0,6},{1,4},{1,5},{1,6},{2,6},{2,5}   };
//	int outlier[10][2]={ {0,4},{0,5},{0,6},{1,5},{1,6},{2,6},{2,0},{2,5}   };
for (int i=0 ; i<8 ; i++) {
	//cout<<"ot "<<outlier[i][0]<<" "<<outlier[i][1]<<endl;
	asybs[outlier[i][0]][outlier[i][1]]= 99;
	asybb[outlier[i][0]][outlier[i][1]]= 99;
	asyys[outlier[i][0]][outlier[i][1]]= 99;
	asyyb[outlier[i][0]][outlier[i][1]]= 99;
	asyerrbs[outlier[i][0]][outlier[i][1]]= 0;
	asyerrbb[outlier[i][0]][outlier[i][1]]= 0;
	asyerrys[outlier[i][0]][outlier[i][1]]= 0;
	asyerryb[outlier[i][0]][outlier[i][1]]= 0;
	asyerrbs1[outlier[i][0]][outlier[i][1]]= 0;
	asyerrbb1[outlier[i][0]][outlier[i][1]]= 0;
	asyerrys1[outlier[i][0]][outlier[i][1]]= 0;
	asyerryb1[outlier[i][0]][outlier[i][1]]= 0;
}		

for (int i=0 ; i<nxfbins ; i++) {
    gasybs[i]=new TGraphErrors(nptbins,xf[i], asybs[i],ex0[i],asyerrbs[i]);//
    gasybb[i]=new TGraphErrors(nptbins,xf[i], asybb[i],ex0[i],asyerrbb[i]);
    gasybserr[i]=new TGraphErrors(nptbins,xf[i],asybs[i],ex0[i],asyerrbs1[i]);
    gasybberr[i]=new TGraphErrors(nptbins,xf[i],asybb[i],ex0[i],asyerrbb1[i]);//syst uncertainty

    gasyys[i]=new TGraphErrors(nptbins,xf[i], asyys[i],ex0[i],asyerrys[i]);
    gasyyb[i]=new TGraphErrors(nptbins,xf[i], asyyb[i],ex0[i],asyerryb[i]);
    gasyyserr[i]=new TGraphErrors(nptbins,xf[i], asyys[i],ex0[i],asyerrys1[i]);
    gasyyberr[i]=new TGraphErrors(nptbins,xf[i], asyyb[i],ex0[i],asyerryb1[i]);
}

    TCanvas *c2 = new TCanvas("c2", "c2",0,0,800,900);
         c2->SetGrid(0,0);
         c2->Divide(2,3);

TH2F *bkg = new TH2F("bkg15","A_{N} for Inclusive #pi^{0} ",20,1,8,10,-0.04,0.1);
        bkg->GetXaxis()->SetTitle("p_{T} / GeV");
        bkg->GetYaxis()->SetTitle("A_{N}");
        bkg->GetXaxis()->CenterTitle(true);;
        bkg->GetYaxis()->CenterTitle(true);;
        bkg->GetYaxis()->SetTitleSize(0.04);;
TH2F *bkg2 = new TH2F("bkg15_2","A_{N} for Inclusive #pi^{0} ",20,2,8,10,-0.04,0.1);
        bkg2->GetXaxis()->SetTitle("p_{T} / GeV");
        bkg2->GetYaxis()->SetTitle("A_{N}");
        bkg2->GetXaxis()->CenterTitle(true);;
        bkg2->GetYaxis()->CenterTitle(true);;
        bkg2->GetYaxis()->SetTitleSize(0.04);;

for (int i=0 ; i<nxfbin ; i++) {
	c2->cd(1+2*i);
	bkg->Draw();
    gasybs[i]->SetMarkerStyle(24);
    gasybs[i]->SetMarkerSize(1.3);
    gasybs[i]->SetMarkerColor(kBlue);
    gasybs[i]->SetLineWidth(2);
    gasybs[i]->SetLineColor(kBlue);
    gasybs[i]->Draw("psame");

    gasybserr[i]->SetMarkerStyle(24);
    gasybserr[i]->SetMarkerSize(1.3);
    gasybserr[i]->SetMarkerColor(kBlue);
    gasybserr[i]->SetLineWidth(2);
    gasybserr[i]->SetLineColor(kBlue);
    if(syst) gasybserr[i]->Draw("p2same");
    gasybserr[i]->SetFillColor(kBlack);
    gasybserr[i]->SetFillStyle(3001);

    gasybb[i]->SetMarkerStyle(24);
    gasybb[i]->SetMarkerSize(1.3);
    gasybb[i]->SetMarkerColor(kGreen+3);
    gasybb[i]->SetLineWidth(2);
    gasybb[i]->SetLineColor(kGreen+3);
    gasybb[i]->Draw("p");

    gasybberr[i]->SetMarkerStyle(24);
    gasybberr[i]->SetMarkerSize(1.3);
    gasybberr[i]->SetMarkerColor(kGreen+3);
    gasybberr[i]->SetLineWidth(2);
    gasybberr[i]->SetLineColor(kGreen+3);
	if(syst)  gasybberr[i]->Draw("p2same");
    gasybberr[i]->SetFillColor(kBlack);
    gasybberr[i]->SetFillStyle(3001);

}

for (int i=0 ; i<nxfbins ; i++) {
	c2->cd(2+2*i);
	bkg->Draw();
    gasyys[i]->SetMarkerStyle(24);
    gasyys[i]->SetMarkerSize(1.3);
    gasyys[i]->SetMarkerColor(kMagenta);
    gasyys[i]->SetLineWidth(2);
    gasyys[i]->SetLineColor(kMagenta);
    gasyys[i]->Draw("psame");

    gasyyserr[i]->SetMarkerStyle(24);
    gasyyserr[i]->SetMarkerSize(1.3);
    gasyyserr[i]->SetMarkerColor(kMagenta);
    gasyyserr[i]->SetLineWidth(2);
    gasyyserr[i]->SetLineColor(kMagenta);
   if(syst)  gasyyserr[i]->Draw("p2same");
    gasyyserr[i]->SetFillColor(kBlack);
    gasyyserr[i]->SetFillStyle(3001);

    gasyyb[i]->SetMarkerStyle(24);
    gasyyb[i]->SetMarkerSize(1.3);
    gasyyb[i]->SetMarkerColor(kGreen+3);
    gasyyb[i]->SetLineWidth(2);
    gasyyb[i]->SetLineColor(kGreen+3);
    gasyyb[i]->Draw("psame");

    gasyyberr[i]->SetMarkerStyle(24);
    gasyyberr[i]->SetMarkerSize(1.3);
    gasyyberr[i]->SetMarkerColor(kGreen+3);
    gasyyberr[i]->SetLineWidth(2);
    gasyyberr[i]->SetLineColor(kGreen+3);
 if(syst)   gasyyberr[i]->Draw("p2same");
    gasyyberr[i]->SetFillColor(kBlack);
    gasyyberr[i]->SetFillStyle(3001);
    }



TLegend *leg=new TLegend(0.6,0.7,0.85,0.88);
                leg->SetMargin(0.5);
                leg->SetBorderSize(0);
                leg->SetFillColor(0);
                leg->SetTextSize(0.03);
                leg->AddEntry(gasybs[0],"Signal x_{F}>0","PE");
                leg->AddEntry(gasybb[0],"Background x_{F}>0","PE");


	c2->cd(1);
	leg->Draw();

 TLatex l;
 TLatex l2;
	double dx0=1.2; double dy0=0.08; double dx=5.5 ;double dy=0.065;
    l.SetTextSize(0.05);
	l.DrawLatex(dx0,dy0-0.000," p^{#uparrow} + p -> #pi^{0} + X"); // @ #sqrt{s}=500 GeV");
    l2.SetTextSize(0.05);
	l.SetTextAngle(0.);
    l.SetTextSize(0.05);
	l.DrawLatex(dx0,dy0-0.01,"  2.7 < #eta < 4.0");
	l.DrawLatex(dx0,dy0-0.02,"  3.0% beam pol. scale uncertainty not shown");

	l2.DrawLatex(dx,dy-0.025," 0.18<x_{F}<0.24");

	c2->cd(2);

TLegend *leg2=new TLegend(0.6,0.7,0.85,0.88);
                leg2->SetMargin(0.5);
                leg2->SetBorderSize(0);
                leg2->SetFillColor(0);
                leg2->SetTextSize(0.03);
                leg2->AddEntry(gasyys[0],"Signal x_{f}<0","PE");
                leg2->AddEntry(gasyyb[0],"Background x_{f}<0","PE");
	leg2->Draw();
	l.DrawLatex(dx0,dy0-0.02,"3.0% beam pol. scale uncertainty not shown");


	c2->cd(3);
	l2.DrawLatex(dx,dy-0.025," 0.24<x_{F}<0.30");
	c2->cd(5);
	l2.DrawLatex(dx,dy-0.025," 0.30<x_{F}<0.36");



if (drawall) c2->SaveAs("DrawPt2An15.png");

    gPtXf1An15 =  (TGraphErrors*)gasybs[0]->Clone();
    gPtXf1Err15 =  (TGraphErrors*)gasybserr[0]->Clone();
    gPtXf2An15 =  (TGraphErrors*)gasybs[1]->Clone();
    gPtXf2Err15 =  (TGraphErrors*)gasybserr[1]->Clone();
    gPtXf3An15 =  (TGraphErrors*)gasybs[2]->Clone();
    gPtXf3Err15 =  (TGraphErrors*)gasybserr[2]->Clone();



/*gasyb01->Write();
gasyb12->Write();
gasyb23->Write();
//gasyy01->Write();
gasyy12->Write();
gasyy23->Write();
gasybs->Write();
gasybb->Write();
gasyys->Write();
gasyyb->Write();
fout->Write();
*/
}

drawPtAn11(int Mset=0){
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

bool updateplot =0;

double pol=0.5249;
double polY=0.5117;

double unpol=0;

ifstream filllist;
filllist.open("Run11filllist");
int fillnum[29];
double fillex[29];
double filldouble[29];
int fillbin=29;
for (int nfill=0; nfill<29;nfill++){
    filllist>>fillnum[nfill];
    fillex[nfill]=0;
    filldouble[nfill] = double(nfill+1);
//	cout<<fillnum[nfill]<<endl;;
}


const int nebins = 3;
double ebinlows[nebins] = {45,  60, 75};
double ebinhighs[nebins] = { 60,  75,90};
const int nptbins = 7;
double ptbinlows[nptbins] = { 1.5,2,2.5, 3, 4, 5, 6 };
double ptbinhighs[nptbins] = {2,2.5,3, 4, 5, 6, 7};
const int nmbins = 2; 
double mbinlows[nmbins] = {0.00, 0.20};
double mbinhighs[nmbins] = {0.20, 0.30};
const int nxfbins=3;

char resultname[400];
char resultname2[400];
char picname[400];
char picname2[400];
double ex[nptbins]= {0,0,0,0,0};//x error 
double ex1[nxfbins][nptbins];//for syst
double ex0[nxfbins][nptbins];//Pt uncertainty
double xf[nxfbins][nptbins] ; //Pt
double xf1[nptbins];
double xf2[nptbins];
for (int nptbin=0; nptbin<nptbins; nptbin++){
//xf[nptbin]= (ptbinlows[nptbin]+ptbinhighs[nptbin])/2.0/250; //    !!!!!!!!!!type change!!!!!!!!!!
xf1[nptbin]=( (ptbinlows[nptbin]+ptbinhighs[nptbin])/2-0.05);
xf2[nptbin]=( (ptbinlows[nptbin]+ptbinhighs[nptbin])/2+0.05);
xf[0][nptbin]= ptmean11Xf1[nptbin];
xf[1][nptbin]= ptmean11Xf2[nptbin];
xf[2][nptbin]= ptmean11Xf3[nptbin];

ex0[0][nptbin]= Rsyst*xf[0][nptbin];
ex0[1][nptbin]= Rsyst*xf[1][nptbin];;
ex0[2][nptbin]= Rsyst*xf[2][nptbin];;
//out<< xf[nptbin]<<" " << xf1[nptbin]<<endl;
ex1[0][nptbin]=0.1;
ex1[1][nptbin]=0.1;
ex1[2][nptbin]=0.1;
}
ifstream result;
ifstream result2;

TF1 *fcn1 = new TF1 ("fcn1","pol0",0,60);
TF1 *fcn2 = new TF1 ("fcn2","pol0",0,60);


//TFile *fout= new TFile ("DrawAn_fracfix.root","recreate");
//fout->cd();

double asy_fill[nmbins][nebins][nptbins];
double asyerr_fill[nmbins][nebins][nptbins];
double asy_fill2[nmbins][nebins][nptbins];
double asyerr_fill2[nmbins][nebins][nptbins];

for (int nmbin=0; nmbin<nmbins;nmbin++){
   for (int nebin=0; nebin<nebins; nebin++){
   	for (int nptbin=0; nptbin<nptbins; nptbin++){
	int fill[29];
	double ene[29];
	double asy[29];
	double asy2[29];
	double asyerr[29];
	double asyerr2[29];
	double ml[29];
	double mh[29];
	double p0[29];
	double p0e[29];
	double p02[29];
	double p0e2[29];
		for (int nfill=0; nfill<29;nfill++){
		//cout<<"bin  "<<mbinlows[nmbin]<<"   "<<mbinhighs[nmbin]<<endl;
		sprintf(resultname,"../Run11/result/PtIso2/PtAN2_Fill%d_mass%.2fto%.2fGeV_E%.1fto%.1f_Pt%.1fto%.1fGeV.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin],ptbinlows[nptbin],ptbinhighs[nptbin]);
		sprintf(resultname2,"../Run11/result/PtIso2/PtANy2_Fill%d_mass%.2fto%.2fGeV_E%.1fto%.1f_Pt%.1fto%.1fGeV.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin],ptbinlows[nptbin],ptbinhighs[nptbin]);
		asyerr2[nfill]=0;
		asyerr[nfill]=0;
		TString infile(resultname);
		TString infile2(resultname2);
//		cout<<resultname2<<endl;
		result.open(resultname,ios::in);
		result2.open(resultname2,ios::in);
	//	if(!result  )  cout<<" file not exist"<<endl;
		
		result>>fill[nfill]>>ene[nfill]>>asy[nfill]>>asyerr[nfill]>>p0[nfill]>>p0e[nfill]>>ml[nfill]>>mh[nfill];
		result2>>fill[nfill]>>ene[nfill]>>asy2[nfill]>>asyerr2[nfill]>>p02[nfill]>>p0e2[nfill]>>ml[nfill]>>mh[nfill];
//		asy2[nfill]=0.004+0.00*nfill; asyerr2[nfill]=0.004;
		result.close();
		result2.close();

        if (asyerr2[nfill]==0.  &&  (nebin == 2 && (nptbin==4||nptbin==3)) && (nebin == 1 && (nptbin>0 && nptbin<7))  ) {  cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<resultname2<<endl  ;    
            asy2[nfill]=0;    
            asyerr2[nfill]=999;
        }   

        if (asyerr[nfill]==0.  &&  (nebin == 2 && (nptbin>2||nptbin<6)) && (nebin == 1 && (nptbin>0 && nptbin<7))   ) {  cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<resultname<<endl  ;    
            asy[nfill]=0; 
            asyerr[nfill]=999;
        }   

//		cout<<fill[nfill]<<" asyraw= "<<asy2[nfill]<<" err "<<asyerr2[nfill]<<endl;
//		sumasy[nmbin][nebin] += asy[nfill];
//		sumerr[nmbin][nebin] += asyerr[nfill]*asyerr[nfill];	
		}	
		
		sprintf(picname,"Otherpic/PtAN2_AllFill_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.png",mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
		sprintf(picname2,"Otherpic/PtANy2_AllFill_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.png",mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
		TGraphErrors *forfit=new TGraphErrors(fillbin,filldouble,asy,fillex,asyerr);
		TGraphErrors *forfit2=new TGraphErrors(fillbin,filldouble,asy2,fillex,asyerr2);
		forfit->Fit("fcn1","RQ");
		asy_fill[nmbin][nebin][nptbin]=fcn1->GetParameter(0);
		asyerr_fill[nmbin][nebin][nptbin]=fcn1->GetParError(0);
		forfit2->Fit("fcn2","RQ");
		asy_fill2[nmbin][nebin][nptbin]=fcn2->GetParameter(0);
		asyerr_fill2[nmbin][nebin][nptbin]=fcn2->GetParError(0);
	//		cout<<asy_fill[nmbin][nebin]<<" "<<asyerr_fill[nmbin][nebin]<<" "<<endl;
	 //TCanvas *c1 = new TCanvas("c1", "c1",0,0,1600,900);
				 forfit->SetTitle(picname);
				 forfit->SetLineWidth(3);
				 forfit->SetLineColor(4);
				 forfit->SetMarkerSize(3);
				 forfit->GetXaxis()->SetTitle("Fill Index");
                 forfit->GetYaxis()->SetTitle("A_{N}");
                 forfit2->SetTitle(picname2);
				 forfit2->SetLineWidth(3);
				 forfit2->SetLineColor(4);
				 forfit2->SetMarkerSize(3);
                 forfit2->GetXaxis()->SetTitle("Fill Index");
                 forfit2->GetYaxis()->SetTitle("A_{N}");
	if(updateplot){
		forfit->Draw("AP*");
		c1->SaveAs(picname);
		c1->Clear();
		forfit2->Draw("AP*");
		c1->SaveAs(picname2);
	}
//	cout<<" sumasy= "<<sumasy[nmbin][nebin]<<"in "<<nmbin<<" "<<nebin<<endl;
    	}
	}	
}


//12 first mass bin
//23 second mass bin
//double asyb01[nxfbin][nptbins];
double asyb12[nxfbins][nptbins];
double asyb23[nxfbins][nptbins];
//double asyerrb01[nxfbin][nptbins];
double asyerrb12[nxfbins][nptbins];
double asyerrb23[nxfbins][nptbins];
//double asyy01[nxfbin][nptbins];
double asyy12[nxfbins][nptbins];
double asyy23[nxfbins][nptbins];
//double asyerry01[nxfbin][nptbins];
double asyerry12[nxfbins][nptbins];
double asyerry23[nxfbins][nptbins];

for (int nptbin=0; nptbin<nptbins; nptbin++){
	for (int nebin=0; nebin<nebins; nebin++){
// mass e pt -- 
/*
// e0 1 -> xf 0 
// e2 3 -> xf 1 
// e4-6 -> xf 2 
average(asy_fill[0][0][nptbin],asy_fill[0][1][nptbin],asyerr_fill[0][1][nptbin],asyerr_fill[0][1][nptbin],asyb12[0][nptbin],asyerrb12[0][nptbin]);
average(asy_fill[0][2][nptbin],asy_fill[0][3][nptbin],asyerr_fill[0][2][nptbin],asyerr_fill[0][3][nptbin],asyb12[1][nptbin],asyerrb12[1][nptbin]);
average(asy_fill[0][4][nptbin],asy_fill[0][5][nptbin],asy_fill[0][6][nptbin],asyerr_fill[0][4][nptbin],asyerr_fill[0][5][nptbin],asyerr_fill[0][6][nptbin],asyb12[2][nptbin],asyerrb12[2][nptbin]);
average(asy_fill2[0][0][nptbin],asy_fill2[0][1][nptbin],asyerr_fill2[0][1][nptbin],asyerr_fill2[0][1][nptbin],asyy12[0][nptbin],asyerry12[0][nptbin]);
average(asy_fill2[0][2][nptbin],asy_fill2[0][3][nptbin],asyerr_fill2[0][2][nptbin],asyerr_fill2[0][3][nptbin],asyy12[1][nptbin],asyerry12[1][nptbin]);
average(asy_fill2[0][4][nptbin],asy_fill2[0][5][nptbin],asy_fill2[0][6][nptbin],asyerr_fill2[0][4][nptbin],asyerr_fill2[0][5][nptbin],asyerr_fill2[0][6][nptbin],asyy12[2][nptbin],asyerry12[2][nptbin]);
*/
        asyb12[nebin][nptbin]=asy_fill[0][nebin][nptbin];
        asyb23[nebin][nptbin]=asy_fill[1][nebin][nptbin];
        asyerrb12[nebin][nptbin]=asyerr_fill[0][nebin][nptbin];
        asyerrb23[nebin][nptbin]=asyerr_fill[1][nebin][nptbin];
        asyy12[nebin][nptbin]=asy_fill2[0][nebin][nptbin];
        asyy23[nebin][nptbin]=asy_fill2[1][nebin][nptbin];
        asyerry12[nebin][nptbin]=asyerr_fill2[0][nebin][nptbin];
        asyerry23[nebin][nptbin]=asyerr_fill2[1][nebin][nptbin];
    //    cout<<" signal region="<<asyb12[nebin][nptbin]<<" +  "<<asyerrb12[nebin][nptbin]<<" sb region"<<asyb23[nebin][nptbin]<<" +  "<<asyerrb23[nebin][nptbin]<<endl;

	}
}
/*
// TCanvas *c1 = new TCanvas("c1", "c1",0,0,1200,900);
//TGraphErrors *gasyb01=new TGraphErrors(nptbins,xf,asyb01,ex,asyerrb01);
TGraphErrors *gasyb12=new TGraphErrors(nptbins,xf,asyb12,ex,asyerrb12);
TGraphErrors *gasyb23=new TGraphErrors(nptbins,xf,asyb23,ex,asyerrb23);
//TGraphErrors *gasyy01=new TGraphErrors(nptbins,xf,asyy01,ex,asyerry01);
TGraphErrors *gasyy12=new TGraphErrors(nptbins,xf,asyy12,ex,asyerry12);
TGraphErrors *gasyy23=new TGraphErrors(nptbins,xf,asyy23,ex,asyerry23);
//gasy->Draw("ap*");
//gasyb01->SetTitle("Signal m=0.0~0.1");
gasyb12->SetTitle("Signal m=0.1~0.2");
gasyb23->SetTitle("Signal m=0.2~0.3");
//gasyb01->GetXaxis()->SetTitle("PiE/Gev");
//gasyb01->GetYaxis()->SetTitle("A_{N}");
gasyb12->GetXaxis()->SetTitle("PiE/Gev");
gasyb12->GetYaxis()->SetTitle("A_{N}");
gasyb23->GetXaxis()->SetTitle("PiE/Gev");
gasyb23->GetYaxis()->SetTitle("A_{N}");
//gasyy01->SetTitle("Signal m=0.0~0.1");
gasyy12->SetTitle("Signal m=0.1~0.2");
gasyy23->SetTitle("Signal m=0.2~0.3");
//gasyy01->GetXaxis()->SetTitle("PiE/Gev");
//gasyy01->GetYaxis()->SetTitle("A_{N}");
gasyy12->GetXaxis()->SetTitle("PiE/Gev");
gasyy12->GetYaxis()->SetTitle("A_{N}");
gasyy23->GetXaxis()->SetTitle("PiE/Gev");
gasyy23->GetYaxis()->SetTitle("A_{N}");
//c1->Print("test.png");
*/
double asybs[nxfbins][nptbins];
double asyerrbs[nxfbins][nptbins];
double asyerrbs1[nxfbins][nptbins]={0,0,0,0,0};
double asyerrys1[nxfbins][nptbins]={0,0,0,0,0};
double asyys[nxfbins][nptbins];
double asyerrys[nxfbins][nptbins];
double asybb[nxfbins][nptbins];
double asyerrbb[nxfbins][nptbins];
double asyerrbb1[nxfbins][nptbins]={0,0,0,0,0};
double asyerryb1[nxfbins][nptbins]={0,0,0,0,0};
double asyyb[nxfbins][nptbins];
double asyerryb[nxfbins][nptbins];
double ferrbs1[nxfbins][nptbins];
double ferrbs2[nxfbins][nptbins];
double ferrys1[nxfbins][nptbins];
double ferrys2[nxfbins][nptbins];
double ferrbb1[nxfbins][nptbins];
double ferrbb2[nxfbins][nptbins];
double ferryb1[nxfbins][nptbins];
double ferryb2[nxfbins][nptbins];


double f1[nxfbins][nptbins];//sig in sig
double f2[nxfbins][nptbins];//sig in bkg
double f1E[nxfbins][nptbins];//
double f2E[nxfbins][nptbins];//

ifstream frac1;
frac1.open("txt/frac11PtXf1.txt",ios::in);
ifstream frac2;
frac2.open("txt/frac11PtXf2.txt",ios::in);
ifstream frac3;
frac3.open("txt/frac11PtXf3.txt",ios::in);
for (int i=0 ; i<nptbins ; i++){
frac1>>f1[0][i]>>f1E[0][i]>>f2[0][i]>>f2E[0][i];
frac2>>f1[1][i]>>f1E[1][i]>>f2[1][i]>>f2E[1][i];
frac3>>f1[2][i]>>f1E[2][i]>>f2[2][i]>>f2E[2][i];
}

double asyFinal;
double asyerrFinal;

	for (int nxfbin=0; nxfbin<nxfbins; nxfbin++){
		cout<<nxfbin<<endl;
	for (int nptbin=0; nptbin<nptbins; nptbin++){

	double f3=(1-f1[nxfbin][nptbin])/(1-f2[nxfbin][nptbin]);
	double f4=f1[nxfbin][nptbin]/f2[nxfbin][nptbin];

//12-signal region 23bkg region
asybs[nxfbin][nptbin]=(asyb12[nxfbin][nptbin]-asyb23[nxfbin][nptbin]*f3)/(1-f3)/pol;
asyerrbs[nxfbin][nptbin]=TMath::Sqrt(asyerrb12[nxfbin][nptbin]*asyerrb12[nxfbin][nptbin]+asyerrb23[nxfbin][nptbin]*asyerrb23[nxfbin][nptbin]*f3*f3)/TMath::Abs(1-f3)/pol;
asyys[nxfbin][nptbin]=(asyy12[nxfbin][nptbin]-asyy23[nxfbin][nptbin]*f3)/(1-f3)/polY;
asyerrys[nxfbin][nptbin]=TMath::Sqrt(asyerry12[nxfbin][nptbin]*asyerry12[nxfbin][nptbin]+asyerry23[nxfbin][nptbin]*asyerry23[nxfbin][nptbin]*f3*f3)/TMath::Abs(1-f3)/polY;
asybb[nxfbin][nptbin]=(asyb12[nxfbin][nptbin]-asyb23[nxfbin][nptbin]*f4)/(1-f4)/pol;
asyerrbb[nxfbin][nptbin]=TMath::Sqrt(asyerrb12[nxfbin][nptbin]*asyerrb12[nxfbin][nptbin]+asyerrb23[nxfbin][nptbin]*asyerrb23[nxfbin][nptbin]*f4*f4)/TMath::Abs(1-f4)/pol;
asyyb[nxfbin][nptbin]=(asyy12[nxfbin][nptbin]-asyy23[nxfbin][nptbin]*f4)/(1-f4)/polY;
asyerryb[nxfbin][nptbin]=TMath::Sqrt(asyerry12[nxfbin][nptbin]*asyerry12[nxfbin][nptbin]+asyerry23[nxfbin][nptbin]*asyerry23[nxfbin][nptbin]*f4*f4)/TMath::Abs(1-f4)/polY;

//asyerrbs1[nxfbin][nptbin]=sqrt(pow(asyerrbs[nxfbin][nptbin],2)+pow(unpol*asybs[nxfbin][nptbin]/pol/pol,2));//with unpol
//asyerrbb1[nxfbin][nptbin]=sqrt(pow(asyerrbb[nxfbin][nptbin],2)+pow(unpol*asybb[nxfbin][nptbin]/pol/pol,2));//with unpol
//12 signal region 23 background region
//uncertaintt of f1 f2
//sig
ferrys1[nxfbin][nptbin]=((asyy12[nxfbin][nptbin]-asyy23[nxfbin][nptbin])*(1-f2[nxfbin][nptbin])/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin])/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin]))/polY;
ferrys2[nxfbin][nptbin]=((asyy12[nxfbin][nptbin]-asyy23[nxfbin][nptbin])*(1-f1[nxfbin][nptbin])/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin])/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin]))/polY;
ferrbs1[nxfbin][nptbin]=((asyb12[nxfbin][nptbin]-asyb23[nxfbin][nptbin])*(1-f2[nxfbin][nptbin])/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin])/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin]))/pol;
ferrbs2[nxfbin][nptbin]=((asyb12[nxfbin][nptbin]-asyb23[nxfbin][nptbin])*(1-f1[nxfbin][nptbin])/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin])/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin]))/pol;
//bkg
ferryb1[nxfbin][nptbin]=((asyy12[nxfbin][nptbin]-asyy23[nxfbin][nptbin])*f2[nxfbin][nptbin]/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin])/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin]))/polY;
ferryb2[nxfbin][nptbin]=((asyy12[nxfbin][nptbin]-asyy23[nxfbin][nptbin])*f1[nxfbin][nptbin]/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin])/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin]))/polY;
ferrbb1[nxfbin][nptbin]=((asyb12[nxfbin][nptbin]-asyb23[nxfbin][nptbin])*f2[nxfbin][nptbin]/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin])/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin]))/pol;
ferrbb2[nxfbin][nptbin]=((asyb12[nxfbin][nptbin]-asyb23[nxfbin][nptbin])*f1[nxfbin][nptbin]/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin])/(f1[nxfbin][nptbin]-f2[nxfbin][nptbin]))/pol;

asyerrbs1[nxfbin][nptbin]=sqrt(pow(ferrbs1[nxfbin][nptbin]*f1E[nxfbin][nptbin],2)+pow(ferrbs2[nxfbin][nptbin]*f2E[nxfbin][nptbin],2));
asyerrbb1[nxfbin][nptbin]=sqrt(pow(ferrbb1[nxfbin][nptbin]*f1E[nxfbin][nptbin],2)+pow(ferrbb2[nxfbin][nptbin]*f2E[nxfbin][nptbin],2));
asyerrys1[nxfbin][nptbin]=sqrt(pow(ferrys1[nxfbin][nptbin]*f1E[nxfbin][nptbin],2)+pow(ferrys2[nxfbin][nptbin]*f2E[nxfbin][nptbin],2));
asyerryb1[nxfbin][nptbin]=sqrt(pow(ferryb1[nxfbin][nptbin]*f1E[nxfbin][nptbin],2)+pow(ferryb2[nxfbin][nptbin]*f2E[nxfbin][nptbin],2));

//cout<<"            "<<"asyy23="<<asyy23[nxfbin][nptbin]<<" asyy12="<<asyy12[nxfbin][nptbin]<<endl;
//cout<<nptbin<<"  f3="<<f3<<" f4="<<f4<<" bberr="<<asyerrbb[nxfbin][nptbin]<<" bserr="<<asyerrbs[nxfbin][nptbin]<<" bb="<<asybb[nxfbin][nptbin]<<" bs="<<asybs[nxfbin][nptbin]<<" yberr="<<asyerryb[nxfbin][nptbin]<<"yberr="<<asyerrys[nxfbin][nptbin]<<" yb="<<asyyb[nxfbin][nptbin]<<" ys="<<asyys[nxfbin][nptbin]<<" bserr1= "<< asyerrbs1[nxfbin][nptbin]<<" bberr1= "<< asyerrbb1[nxfbin][nptbin]<<" yserr1= "<< asyerrys1[nxfbin][nptbin]<<" yberr1= "<< asyerryb1[nxfbin][nptbin]<<endl;

//cout<<asyerrbs1[nxfbin][nptbin]<<" "<<asyerrbb1[nxfbin][nptbin]<<" "<<asyerrys1[nxfbin][nptbin]<<" "<<asyerryb1[nxfbin][nptbin]<<" " <<endl;

asyerrbs1[nxfbin][nptbin] = asybs[nxfbin][nptbin] * Syst11/100 ;
if (nxfbin==0)	cout<<nptbin<<" "<<ptmean11Xf1[nptbin]  <<" "<<asybs[nxfbin][nptbin]<<" "<<asyerrbs[nxfbin][nptbin]<<" "<<asyerrbs1[nxfbin][nptbin]<<endl;
if (nxfbin==1)	cout<<nptbin<<" "<<ptmean11Xf2[nptbin]  <<" "<<asybs[nxfbin][nptbin]<<" "<<asyerrbs[nxfbin][nptbin]<<" "<<asyerrbs1[nxfbin][nptbin]<<endl;
if (nxfbin==2)	cout<<nptbin<<" "<<ptmean11Xf3[nptbin]  <<" "<<asybs[nxfbin][nptbin]<<" "<<asyerrbs[nxfbin][nptbin]<<" "<<asyerrbs1[nxfbin][nptbin]<<endl;
	}
}



    TGraphErrors *gasybs[3];
    TGraphErrors *gasybb[3];
    TGraphErrors *gasybberr[3];
    TGraphErrors *gasybserr[3];
    TGraphErrors *gasyys[3];
    TGraphErrors *gasyyb[3];
    TGraphErrors *gasyyberr[3];
    TGraphErrors *gasyyserr[3];

	int outlier[12][2]={{0,0},{0,5}, {0,6},{1,0},{1,1},{1,6},{1,5},{2,0},{2,1},{2,2},{2,5},{2,6}};
for (int i=0 ; i<12 ; i++) {
//	cout<<"ot "<<outlier[i][0]<<" "<<outlier[i][1]<<endl;
	asybs[outlier[i][0]][outlier[i][1]]= 99;
	asybb[outlier[i][0]][outlier[i][1]]= 99;
	asyys[outlier[i][0]][outlier[i][1]]= 99;
	asyyb[outlier[i][0]][outlier[i][1]]= 99;
	asyerrbs[outlier[i][0]][outlier[i][1]]= 0;
	asyerrbb[outlier[i][0]][outlier[i][1]]= 0;
	asyerrys[outlier[i][0]][outlier[i][1]]= 0;
	asyerryb[outlier[i][0]][outlier[i][1]]= 0;
}		


for (int i=0 ; i<nxfbins ; i++) {
    gasybs[i]=new TGraphErrors(nptbins,xf[i], asybs[i],ex0[i],asyerrbs[i]);//
    gasybb[i]=new TGraphErrors(nptbins,xf[i], asybb[i],ex0[i],asyerrbb[i]);
    gasybserr[i]=new TGraphErrors(nptbins,xf[i],asybs[i],ex0[i],asyerrbs1[i]);
    gasybberr[i]=new TGraphErrors(nptbins,xf[i],asybb[i],ex0[i],asyerrbb1[i]);//syst uncertainty

    gasyys[i]=new TGraphErrors(nptbins,xf[i], asyys[i],ex0[i],asyerrys[i]);
    gasyyb[i]=new TGraphErrors(nptbins,xf[i], asyyb[i],ex0[i],asyerryb[i]);
    gasyyserr[i]=new TGraphErrors(nptbins,xf[i], asyys[i],ex0[i],asyerrys1[i]);
    gasyyberr[i]=new TGraphErrors(nptbins,xf[i], asyyb[i],ex0[i],asyerryb1[i]);
}

    TCanvas *c2 = new TCanvas("c2", "c2",0,0,800,900);
         c2->SetGrid(0,0);
         c2->Divide(2,3);

TH2F *bkg = new TH2F("bkg11","A_{N} for Inclusive #pi^{0} ",20,1,8,10,-0.04,0.08);
        bkg->GetXaxis()->SetTitle("p_{T} / GeV");
        bkg->GetYaxis()->SetTitle("A_{N}");
        bkg->GetXaxis()->CenterTitle(true);;
        bkg->GetYaxis()->CenterTitle(true);;
        bkg->GetYaxis()->SetTitleSize(0.04);;
TH2F *bkg2 = new TH2F("bkg11_2","A_{N} for Inclusive #pi^{0} ",20,2,8,10,-0.04,0.08);
        bkg2->GetXaxis()->SetTitle("p_{T} / GeV");
        bkg2->GetYaxis()->SetTitle("A_{N}");
        bkg2->GetXaxis()->CenterTitle(true);;
        bkg2->GetYaxis()->CenterTitle(true);;
        bkg2->GetYaxis()->SetTitleSize(0.04);;

for (int i=0 ; i<nxfbin ; i++) {
	c2->cd(1+2*i);
	bkg->Draw();
    gasybs[i]->SetMarkerStyle(24);
    gasybs[i]->SetMarkerSize(1.3);
    gasybs[i]->SetMarkerColor(kBlue);
    gasybs[i]->SetLineWidth(2);
    gasybs[i]->SetLineColor(kBlue);
    gasybs[i]->Draw("psame");

    gasybserr[i]->SetMarkerStyle(24);
    gasybserr[i]->SetMarkerSize(1.3);
    gasybserr[i]->SetMarkerColor(kBlue);
    gasybserr[i]->SetLineWidth(2);
    gasybserr[i]->SetLineColor(kBlue);
    if(syst) gasybserr[i]->Draw("p2same");
    gasybserr[i]->SetFillColor(kBlack);
    gasybserr[i]->SetFillStyle(3001);

    gasybb[i]->SetMarkerStyle(24);
    gasybb[i]->SetMarkerSize(1.3);
    gasybb[i]->SetMarkerColor(kGreen+3);
    gasybb[i]->SetLineWidth(2);
    gasybb[i]->SetLineColor(kGreen+3);
    gasybb[i]->Draw("p");

    gasybberr[i]->SetMarkerStyle(24);
    gasybberr[i]->SetMarkerSize(1.3);
    gasybberr[i]->SetMarkerColor(kGreen+3);
    gasybberr[i]->SetLineWidth(2);
    gasybberr[i]->SetLineColor(kGreen+3);
	if(syst)  gasybberr[i]->Draw("p2same");
    gasybberr[i]->SetFillColor(kBlack);
    gasybberr[i]->SetFillStyle(3001);

}

for (int i=0 ; i<nxfbins ; i++) {
	c2->cd(2+2*i);
	bkg->Draw();
    gasyys[i]->SetMarkerStyle(24);
    gasyys[i]->SetMarkerSize(1.3);
    gasyys[i]->SetMarkerColor(kMagenta);
    gasyys[i]->SetLineWidth(2);
    gasyys[i]->SetLineColor(kMagenta);
    gasyys[i]->Draw("psame");

    gasyyserr[i]->SetMarkerStyle(24);
    gasyyserr[i]->SetMarkerSize(1.3);
    gasyyserr[i]->SetMarkerColor(kMagenta);
    gasyyserr[i]->SetLineWidth(2);
    gasyyserr[i]->SetLineColor(kMagenta);
    if(syst) gasyyserr[i]->Draw("p2same");
    gasyyserr[i]->SetFillColor(kBlack);
    gasyyserr[i]->SetFillStyle(3001);

    gasyyb[i]->SetMarkerStyle(24);
    gasyyb[i]->SetMarkerSize(1.3);
    gasyyb[i]->SetMarkerColor(kGreen+3);
    gasyyb[i]->SetLineWidth(2);
    gasyyb[i]->SetLineColor(kGreen+3);
    gasyyb[i]->Draw("psame");

    gasyyberr[i]->SetMarkerStyle(24);
    gasyyberr[i]->SetMarkerSize(1.3);
    gasyyberr[i]->SetMarkerColor(kGreen+3);
    gasyyberr[i]->SetLineWidth(2);
    gasyyberr[i]->SetLineColor(kGreen+3);
 if(syst)   gasyyberr[i]->Draw("p2same");
    gasyyberr[i]->SetFillColor(kBlack);
    gasyyberr[i]->SetFillStyle(3001);
    }



TLegend *leg=new TLegend(0.6,0.7,0.85,0.88);
                leg->SetMargin(0.5);
                leg->SetBorderSize(0);
                leg->SetFillColor(0);
                leg->SetTextSize(0.03);
                leg->AddEntry(gasybs[0],"Signal x_{F}>0","PE");
                leg->AddEntry(gasybb[0],"Background x_{F}>0","PE");


	c2->cd(1);
	leg->Draw();

 TLatex l;
 TLatex l2;
    l.SetTextSize(0.05);
    l2.SetTextSize(0.05);
	l.SetTextAngle(0.);
	double dx0=1.2; double dy=0.07; double dx=3.5;
	l.DrawLatex(dx0,dy-0.000,"  p^{#uparrow} + p -> #pi^{0} + X @ #sqrt{s}=500 GeV");
	l.DrawLatex(dx0,dy-0.009,"  2.7 < #eta < 4.0");
	l.DrawLatex(dx0,dy-0.025,"  3.4% beam pol. scale uncertainty not shown");

	l2.DrawLatex(dx,-0.03," 0.18<x_{F}<0.24");

	c2->cd(2);

TLegend *leg2=new TLegend(0.6,0.7,0.85,0.88);
                leg2->SetMargin(0.5);
                leg2->SetBorderSize(0);
                leg2->SetFillColor(0);
                leg2->SetTextSize(0.03);
                leg2->AddEntry(gasyys[0],"Signal x_{f}<0","PE");
                leg2->AddEntry(gasyyb[0],"Background x_{f}<0","PE");
	leg2->Draw();
	l.DrawLatex(dx0,dy-0.025,"3.4% beam pol. scale uncertainty not shown");


	c2->cd(3);
	l2.DrawLatex(dx,dy-0.02," 0.24<x_{F}<0.30");
	c2->cd(5);
	l2.DrawLatex(dx,dy-0.02," 0.30<x_{F}<0.36");



if (drawall) c2->SaveAs("DrawPt2An11.png");


    gPtXf1An11 =  (TGraphErrors*)gasybs[0]->Clone();
    gPtXf1Err11 =  (TGraphErrors*)gasybserr[0]->Clone();
    gPtXf2An11 =  (TGraphErrors*)gasybs[1]->Clone();
    gPtXf2Err11 =  (TGraphErrors*)gasybserr[1]->Clone();
    gPtXf3An11 =  (TGraphErrors*)gasybs[2]->Clone();
    gPtXf3Err11 =  (TGraphErrors*)gasybserr[2]->Clone();

/*gasyb01->Write();
gasyb12->Write();
gasyb23->Write();
//gasyy01->Write();
gasyy12->Write();
gasyy23->Write();
gasybs->Write();
gasybb->Write();
gasyys->Write();
gasyyb->Write();
fout->Write();
*/
}

void average(double asy1, double asy2, double err1, double err2,double & asyFinal,double & asyerrFinal){
asyFinal= (asy1/err1/err1+asy2/err2/err2)/(1/err1/err1+1/err2/err2);
asyerrFinal=1/TMath::Sqrt(1/err1/err1+1/err2/err2);
}
void average(double asy1, double asy2,double asy3, double err1, double err2,double err3, double & asyFinal,double & asyerrFinal){
asyFinal= (asy1/err1/err1+asy2/err2/err2+asy3/err3/err3)/(1/err1/err1+1/err2/err2+1/err3/err3);
asyerrFinal=1/TMath::Sqrt(1/err1/err1+1/err2/err2+1/err3/err3);
}
