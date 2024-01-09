TGraphErrors *gjetAn15 ;
TGraphErrors *gjetAn11 ;
TGraphErrors *gjetAn15Err ;
TGraphErrors *gjetAn11Err ;
TGraphErrors *gjetAn15Iso0 ;
TGraphErrors *gjetAn11Iso0 ;
TGraphErrors *gjetAn15Iso0Err ;
TGraphErrors *gjetAn11Iso0Err ;
TGraphErrors *gjetAn15Iso1 ;
TGraphErrors *gjetAn11Iso1 ;
TGraphErrors *gjetAn15Iso1Err ;
TGraphErrors *gjetAn11Iso1Err ;

double Rsyst = 0.0;
double xf15Iso0[9]={20.5952 , 25.4095 , 30.2192 , 35.2676 , 40.2814 , 45.2818 , 50.2623 , 55.2269 , 60.9419 };
double Ptmean15Iso0[9]={2.30668 , 2.77857 , 2.98624 , 2.91988 , 2.76763 , 2.77293 , 2.90095 , 3.11671 , 3.51831 };
double xf15Iso1[9]={20.6595 , 25.4468 , 30.186 , 35.2532 , 40.3528 , 45.4267 , 50.4482 , 55.3343 , 61.0473 };
double Ptmean15Iso1[9]={2.34448 , 2.84648 , 3.12866 , 3.16126 , 2.87456 , 2.67479 , 2.61166 , 2.65142 , 2.82051 };


double xf11Iso0[7]={40.4733 , 45.4601 , 50.4409 , 55.392 , 61.1763 , 69.1982 , 80.6029 };
double Ptmean11Iso0[7]={3.15645 , 3.41967 , 3.56729 , 3.68594 , 3.82524 , 4.11365 , 4.64915 };
double xf11Iso1[7]={40.5525 , 45.5357 , 50.5438 , 55.4822 , 61.3662 , 69.5345 , 81.0987 };
double Ptmean11Iso1[7]={3.21357 , 3.38671 , 3.46385 , 3.52582 , 3.60812 , 3.77195 , 4.18624 };

double xf15[9]={20.6614 , 25.4635 , 30.2489 , 35.273 , 40.3067 , 45.3355 , 50.3471 , 55.291 , 61.0336 };
double Ptmean15[9]={2.29382 , 2.7605 , 3.00705 , 3.02115 , 2.86867 , 2.78794 , 2.80169 , 2.89822 , 3.14834 };

double xf11[7]={40.4364 , 45.4165 , 50.4077 , 55.3826 , 61.2137 , 69.3502 , 80.9911 };
double Ptmean11[7]={3.09494 , 3.28009 , 3.45024 , 3.59778 , 3.81157 , 4.14712 , 4.70364 };


bool syst = false;

drawIsoCom(){
	
	drawIsoAn15(0);
	drawIsoAn11(0);
//new	
    TCanvas *c = new TCanvas("roses", "roses", 1000, 1000);
    c->Divide(1,2,0.,.0001);
    double x1[2]={4,5};
    double y1[2]={7,5};
        TH2F *h1 = new TH2F("bkgComAN","  ",20,0.14,0.66,10,-0.03,0.25);
        TH2F *h2 = new TH2F("bkgComPt","  ",20,0.14,0.66,10,  1.5 , 5.3);
        //h1->GetYaxis()->SetNdivisions(505);
        //h2->GetYaxis()->SetNdivisions(505);
		          h1->GetYaxis()->SetLabelSize(0.06);
		          h1->GetXaxis()->SetLabelSize(0.06);
		          h2->GetYaxis()->SetLabelSize(0.06);
		          h2->GetXaxis()->SetLabelSize(0.06);
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
        gPad->SetLeftMargin(0.12);
        gPad->SetRightMargin(0.01);
        gPad->SetBottomMargin(0.001);
        h1->Draw();
   c->cd(2);
        h2->Draw();
        gPad->SetLeftMargin(0.12);
        gPad->SetRightMargin(0.01);
        gPad->SetBottomMargin(0.5);
c->cd(0);
        TPad*  p= new TPad("p","p",0,0,1,1); p->Draw(); p->cd();
                p->SetFillStyle(0);
   latex.DrawLatexNDC(.02,.92,"A_{N}");
   latex.SetTextAngle(90);
   latex.DrawLatexNDC(.02,.29,"<p_{T}>/ [GeV/c]");
   latex.SetTextAngle(0);
   latex.DrawLatexNDC(.5,0.2,"x_{F}");
    for (int nebin=0; nebin<7; nebin++){
    xf11Iso0[nebin]= xf11Iso0[nebin]/250;
    xf11Iso1[nebin]= xf11Iso1[nebin]/250;
    //ex0[nebin]= Rsyst*xf[nebin];
    }
    for (int nebin=0; nebin<9; nebin++){
    xf15Iso0[nebin]= xf15Iso0[nebin]/100;
    xf15Iso1[nebin]= xf15Iso1[nebin]/100;
    //ex0[nebin]= Rsyst*xf[nebin];
    }
      TGraph *pt11Iso0=new TGraph(7,xf11Iso0,Ptmean11Iso0);
      TGraph *pt15Iso0=new TGraph(9,xf15Iso0,Ptmean15Iso0);
      TGraph *pt11Iso1=new TGraph(7,xf11Iso1,Ptmean11Iso1);
      TGraph *pt15Iso1=new TGraph(9,xf15Iso1,Ptmean15Iso1);

    pt11Iso0->SetMarkerColor(kBlue);
    pt15Iso0->SetMarkerColor(kRed);
    pt11Iso0->SetLineColor(kBlue);
    pt15Iso0->SetLineColor(kRed);
    pt11Iso0->SetMarkerStyle(26);
    pt15Iso0->SetMarkerStyle(24);
    pt11Iso0->SetMarkerSize(1.6);
    pt15Iso0->SetMarkerSize(1.5);
    pt11Iso1->SetMarkerColor(kBlue);
    pt15Iso1->SetMarkerColor(kRed);
    pt11Iso1->SetLineColor(kBlue);
    pt15Iso1->SetLineColor(kRed);
    pt11Iso1->SetMarkerStyle(22);
    pt15Iso1->SetMarkerStyle(20);
    pt11Iso1->SetMarkerSize(1.6);
    pt15Iso1->SetMarkerSize(1.5);
   c->cd(1);
	gjetAn11Iso0->SetMarkerStyle(26);
	gjetAn11Iso1->SetMarkerStyle(22);
	gjetAn11Iso0->SetMarkerSize(1.6);
	gjetAn11Iso1->SetMarkerSize(1.6);
	gjetAn15Iso0->SetMarkerStyle(24);
	gjetAn15Iso1->SetMarkerStyle(20);
	gjetAn15Iso0->SetMarkerSize(1.5);
	gjetAn15Iso1->SetMarkerSize(1.5);
	gjetAn15->SetMarkerColor(kRed);
	gjetAn15Iso0->SetMarkerColor(kRed);
	gjetAn15Iso1->SetMarkerColor(kRed);
	//gjetAn15Err->SetMarkerColor(kRed);
	gjetAn15Iso0Err->SetMarkerColor(kRed);
	gjetAn15Iso1Err->SetMarkerColor(kRed);
	
	gjetAn11->SetMarkerColor(kBlue);
	gjetAn11Iso0->SetMarkerColor(kBlue);
	gjetAn11Iso1->SetMarkerColor(kBlue);
	//gjetAn11Err->SetMarkerColor(kBlue);
	gjetAn11Iso0Err->SetMarkerColor(kBlue);
	gjetAn11Iso1Err->SetMarkerColor(kBlue);
	
	
	gjetAn15->SetLineColor(kRed);
	gjetAn15Iso0->SetLineColor(kRed);
	gjetAn15Iso1->SetLineColor(kRed);
	//gjetAn15Err->SetLineColor(kRed);
	gjetAn15Iso0Err->SetLineColor(kRed);
	gjetAn15Iso1Err->SetLineColor(kRed);
	
	
	gjetAn11->SetLineColor(kBlue);
	gjetAn11Iso0->SetLineColor(kBlue);
	gjetAn11Iso1->SetLineColor(kBlue);
	//gjetAn11Err->SetLineColor(kBlue);
	gjetAn11Iso0Err->SetLineColor(kBlue);
	gjetAn11Iso1Err->SetLineColor(kBlue);
	
	
gjetAn11Iso0Err->SetFillStyle(3002);;
gjetAn11Iso1Err->SetFillStyle(3002);;
gjetAn15Iso0Err->SetFillStyle(3002);;
gjetAn15Iso1Err->SetFillStyle(3002);;


	//gjetAn15->Draw("psame");
	gjetAn15Iso0->Draw("psame");
	gjetAn15Iso1->Draw("psame");
if(syst)	gjetAn15Iso0Err->Draw("psame2");
if(syst)	gjetAn15Iso1Err->Draw("psame2");
	//gjetAn11->Draw("psame");
	gjetAn11Iso0->Draw("psame");
	gjetAn11Iso1->Draw("psame");
if(syst)	gjetAn11Iso0Err->Draw("psame2");
if(syst)	gjetAn11Iso1Err->Draw("psame2");

    TLegend *leg3=new TLegend(0.5,0.67,0.94,0.97);
                leg3->SetMargin(0.25);
                leg3->SetBorderSize(0);
                leg3->SetFillColor(0);
                leg3->SetTextSize(0.07);
	            leg3->AddEntry(gjetAn15Iso1,"Isolated #pi^{0} 200 GeV","PE");
	            leg3->AddEntry(gjetAn11Iso1,"Isolated #pi^{0} 500 GeV","PE");
	            leg3->AddEntry(gjetAn15Iso0,"Non-isolated #pi^{0} 200 GeV","PE");
	            leg3->AddEntry(gjetAn11Iso0,"Non-isolated #pi^{0} 500 GeV ","PE");
    leg3->Draw();

     TLatex l;
     TLatex l2;
        l.SetTextSize(0.06);
        l.SetTextAngle(0.);

		    double dx=0.16; double dy=0.23;
        l2.SetTextSize(0.06);
           l2.DrawLatex(dx,dy-0.00,"STAR    p^{#uparrow} + p -> #pi^{0} + X");// @ #sqrt{s}=200/500 GeV");
        l2.SetTextSize(0.06);
           l2.DrawLatex(dx,dy-0.03,"p_{T} > 2 GeV/c");
           l2.DrawLatex(dx,dy-0.06,"2.7 < #eta < 4.0");
    	l.DrawLatex(0.16,dy-0.09,"3.0/3.4% beam pol. scale uncertainty not shown");

    c->cd(2);
		h2->Draw();
        pt11Iso0->Draw("psame");
        pt15Iso0->Draw("psame");
        pt11Iso1->Draw("psame");
        pt15Iso1->Draw("psame");

//	c->SaveAs("DrawIsoComPt.png");
    // THEORY
    ifstream theo1_200;
    ifstream theo1_500;
     const int Np200=9;
     const int Np500=7;
        string word1,word2,word3;
        double T200N[Np200];
        double T200asy[Np200];
        double T200asyerr[Np200];
        double Ex200[Np200];
        double T500N[Np500];
        double T500asy[Np500];
        double T500asyerr[Np500];
        double Ex500[Np500];
        theo1_500.open("theory/Alexei/pi0_AN_vs_xF-500.dat",ios::in);
        theo1_200.open("theory/Alexei/pi0_AN_vs_xF-200.dat",ios::in);
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
    
			c->cd(1);   
	double Ptxf11[7];
	double Ptxf15[9];
    for (int nebin=0; nebin<7; nebin++){
    Ptxf11[nebin]= xf11[nebin]/250;
    }    
    for (int nebin=0; nebin<9; nebin++){
    Ptxf15[nebin]= xf15[nebin]/100;
    }    

      TGraphErrors *gth1_200=new TGraphErrors(9,Ptxf15,T200asy,Ex200,T200asyerr);
      TGraphErrors *gth1_500=new TGraphErrors(7,Ptxf11,T500asy,Ex500,T500asyerr);
      TGraph *gth1_200L=new TGraph(9,Ptxf15,T200asy);
      TGraph *gth1_500L=new TGraph(7,Ptxf11,T500asy);
        gth1_200L->SetLineColor(kRed);
        gth1_200->SetFillColorAlpha(kRed-9,0.35);
        gth1_500L->SetLineColor(kBlue);
        gth1_500->SetFillColorAlpha(kBlue-7,0.35);
        gth1_200->Draw("3csame");
        gth1_500->Draw("3csame");
        gth1_200L->Draw("csame");
        gth1_500L->Draw("csame");
    TLegend *leg4=new TLegend(0.15,0.40,0.35,0.55);
                leg4->SetMargin(0.3);
                leg4->SetBorderSize(0);
                leg4->SetFillColor(0);
                leg4->SetTextSize(0.07);
                leg4->AddEntry(gth1_200,"Theory 200 GeV","f");
                leg4->AddEntry(gth1_500,"Theory 500 GeV","f");
leg4->Draw();
	c->SaveAs("DrawIsoComPtT.png");
	
//	
TCanvas *c11 = new TCanvas("c11", "c11",0,0,1200,900);
TH2F *bkgCom = new TH2F("bkgCom"," A_{N} for Inclusive #pi^{0} ",20,0.14,0.66,10,-0.04,0.2);
        bkgCom->GetXaxis()->SetTitle("x_{F}");
        bkgCom->GetYaxis()->SetTitle("A_{N}");
        bkgCom->GetXaxis()->CenterTitle(true);;
        bkgCom->GetYaxis()->CenterTitle(true);;
        bkgCom->GetYaxis()->SetTitleSize(0.04);;
		          bkgCom->GetYaxis()->SetLabelSize(0.06);
		          bkgCom->GetXaxis()->SetLabelSize(0.06);

        bkgCom->Draw();

gjetAn15->SetMarkerColor(kRed);
gjetAn15Iso0->SetMarkerColor(kRed);
gjetAn15Iso1->SetMarkerColor(kRed);
//gjetAn15Err->SetMarkerColor(kRed);
gjetAn15Iso0Err->SetMarkerColor(kRed);
gjetAn15Iso1Err->SetMarkerColor(kRed);

gjetAn11->SetMarkerColor(kBlue);
gjetAn11Iso0->SetMarkerColor(kBlue);
gjetAn11Iso1->SetMarkerColor(kBlue);
//gjetAn11Err->SetMarkerColor(kBlue);
gjetAn11Iso0Err->SetMarkerColor(kBlue);
gjetAn11Iso1Err->SetMarkerColor(kBlue);


gjetAn15->SetLineColor(kRed);
gjetAn15Iso0->SetLineColor(kRed);
gjetAn15Iso1->SetLineColor(kRed);
//gjetAn15Err->SetLineColor(kRed);
gjetAn15Iso0Err->SetLineColor(kRed);
gjetAn15Iso1Err->SetLineColor(kRed);


gjetAn11->SetLineColor(kBlue);
gjetAn11Iso0->SetLineColor(kBlue);
gjetAn11Iso1->SetLineColor(kBlue);
//gjetAn11Err->SetLineColor(kBlue);
gjetAn11Iso0Err->SetLineColor(kBlue);
gjetAn11Iso1Err->SetLineColor(kBlue);


gjetAn11Iso0Err->SetFillStyle(3002);;
gjetAn11Iso1Err->SetFillStyle(3002);;
gjetAn15Iso0Err->SetFillStyle(3002);;
gjetAn15Iso1Err->SetFillStyle(3002);;


//gjetAn15->Draw("psame");
gjetAn15Iso0->Draw("psame");
gjetAn15Iso1->Draw("psame");
if(syst) gjetAn15Iso0Err->Draw("psame2");
if(syst) gjetAn15Iso1Err->Draw("psame2");
//gjetAn11->Draw("psame");
gjetAn11Iso0->Draw("psame");
gjetAn11Iso1->Draw("psame");
if(syst) gjetAn11Iso0Err->Draw("p2");
if(syst) gjetAn11Iso1Err->Draw("p2");




TLegend *leg=new TLegend(0.45,0.65,0.85,0.88);
                leg->SetMargin(0.5);
                leg->SetBorderSize(0);
                leg->SetFillColor(0);
                leg->SetTextSize(0.03);
               // leg->AddEntry(gjetAn15," 200 GeV combined","PE");
               // leg->AddEntry(gjetAn11," 500 GeV combined","PE");
	            leg->AddEntry(gjetAn15Iso0,"Non-isolated #pi^{0} 200 GeV","PE");
	            leg->AddEntry(gjetAn11Iso0,"Non-isolated #pi^{0} 500 GeV ","PE");
	            leg->AddEntry(gjetAn15Iso1,"Isolated #pi^{0} 200 GeV","PE");
	            leg->AddEntry(gjetAn11Iso1,"Isolated #pi^{0} 500 GeV","PE");
leg->Draw();

 TLatex l;
 TLatex l2;
    l.SetTextSize(0.03);
    l2.SetTextSize(0.03);
    l.SetTextAngle(0.);
    l.DrawLatex(0.16,0.12,"3.0/3.4% beam pol. scale uncertainty not shown");
    double dx=0.16; double dy=0.18;
           l2.DrawLatex(dx,dy-0.00,"p^{#uparrow} + p -> #pi^{0} + X @ #sqrt{s}=200/500 GeV");
           l2.DrawLatex(dx,dy-0.02,"p_{T} > 2 GeV/c");
           l2.DrawLatex(dx,dy-0.04,"2.7 < #eta < 4.0");


//c11->SaveAs("DrawIsoAnCom.png");	
	
	
	
}


drawIsoAn15(int Mset = 12345){

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
	//	cout<<fillnum[nfill];
	}
	
	int mode[2] = {0,1};
	const int nmodes = 2;
	
//	double ebinlows[nebins] = {38, 43, 48, 53, 58, 65,75};
//	double ebinhighs[nebins] = {43, 48, 53, 58, 65, 75,90};
	const int nebins = 9;
	double ebinlows[nebins] = {18, 23, 28, 33, 38, 43, 48, 53, 58};
	double ebinhighs[nebins] ={23, 28, 33, 38, 43, 48, 53, 58, 65};
	double mbinlows[2] = {0.00, 0.20};
	double mbinhighs[2] = {0.20 , 0.30};
	const int nmbins = 2;
	char resultname[200];
	char resultname2[200];
	char picname[200];
	char picname2[200];
//	double exa[nebins]= {0,0,0,0,0,0,0};//x error 
//	double exb[nebins]= {0,0,0,0,0,0,0};//x error 

//	double ex10[nebins]={0,0,0,0,0,0,0};
//	double ex11[nebins]={0,0,0,0,0,0,0};

	double ex[nmodes][nebins];
	double ex0[nmodes][nebins];//true uncertainty
	double ex1[nmodes][nebins];//for syst
//	double ex00[nebins]= {0.012,0.013,0.014,0.016,0.018,0.020,0.024};
//	double ex01[nebins]= {0.012,0.013,0.014,0.016,0.018,0.020,0.024};
	double xf[nmodes][nebins];
	double xfm[nmodes][nebins];
	double xfb[nmodes][nebins];
	for (int nebin=0; nebin<nebins; nebin++){
		//xf[nebin]= (ebinlows[nebin]+ebinhighs[nebin])/2.0/250; //    !!!!!!!!!!type change!!!!!!!!!!
		xf[0][nebin]= xf15Iso0[nebin]/100;
		xf[1][nebin]= xf15Iso1[nebin]/100;
		ex0[0][nebin]= Rsyst*xf[0][nebin];
		ex0[1][nebin]= Rsyst*xf[1][nebin];
		ex1[0][nebin]= 0.003;
		ex1[1][nebin]= 0.003;
		//ex1[0][nebin] = ex10[nebin];
		//ex1[1][nebin] = ex11[nebin];
		xfb[0][nebin]= xf[0][nebin]+0.005;
		xfb[1][nebin]= xf[1][nebin]+0.005;
//		xf2[nebin]=( (ebinlows[nebin]+ebinhighs[nebin])/2+0.5)/250;
		//out<< xf[nebin]<<" " << xf1[nebin]<<endl;
		xfm[0][nebin]= -xf[0][nebin];
		xfm[1][nebin]= -xf[1][nebin];
	}
	ifstream result;
	ifstream result2;
	
	TF1 *fcn1 = new TF1 ("fcn1","pol0",0,60);
	TF1 *fcn2 = new TF1 ("fcn2","pol0",0,60);
	
	
	//TFile *fout= new TFile ("DrawIso15.root","recreate");
	//fout->cd();
	//	 TCanvas *c1 = new TCanvas("c1", "c1",0,0,1600,900);
	//	 c1->SetGrid(0,0);
	 	TCanvas *c2 = new TCanvas("c2", "c2",0,0,1200,450);
		 c2->SetGrid(0,0);
		 c2->Divide(2,1);
	double asy_fill[nmodes][nmbins][nebins];
	double asyerr_fill[nmodes][nmbins][nebins];
	double asy_fill2[nmodes][nmbins][nebins];
	double asyerr_fill2[nmodes][nmbins][nebins];



	for (int nmode=0; nmode<nmodes  ;nmode++){
		for (int nmbin=0; nmbin<nmbins;nmbin++){
		   for (int nebin=0; nebin<nebins; nebin++){
	
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

 asyerr2[nfill]=0;      asyerr[nfill]=0;

			//cout<<"bin  "<<mbinlows[nmbin]<<"   "<<mbinhighs[nmbin]<<endl;
				sprintf(resultname,"/star/u/zwzhu/01zwzhu/ana/New/PaperCode/Code2/Run15/result/IsoAN2/IsoAN_BKG_Fill%d_mass%.2fto%.2fGeV_E%.1fto%.1fGeV_mode%d.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin],mode[nmode]);
				sprintf(resultname2,"/star/u/zwzhu/01zwzhu/ana/New/PaperCode/Code2/Run15/result/IsoAN2/IsoANy_BKG_Fill%d_mass%.2fto%.2fGeV_E%.1fto%.1fGeV_mode%d.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin],mode[nmode]);
				TString infile(resultname);
				TString infile2(resultname2);
				result.open(resultname,ios::in);
				result2.open(resultname2,ios::in);
				asyerr2[nfill]=0;
				asyerr[nfill]=0;
			 if(!result )  cout<<" file not exist"<<endl;
				result>>fill[nfill]>>ene[nfill]>>asy[nfill]>>asyerr[nfill]>>p0[nfill]>>p0e[nfill]>>ml[nfill]>>mh[nfill];
				result2>>fill[nfill]>>ene[nfill]>>asy2[nfill]>>asyerr2[nfill]>>p02[nfill]>>p0e2[nfill]>>ml[nfill]>>mh[nfill];
				result.close();
				result2.close();
        if (asyerr2[nfill]==0.) { // cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<resultname2<<endl  ;          
            asy2[nfill]=0;       
            asyerr2[nfill]=999;
        }   

        if (asyerr[nfill]==0) { // cout<<"more "<<resultname<<endl  ;    
            asy[nfill]=0; 
            asyerr[nfill]=999;
        } 
		//		cout<<fill[nfill]<<" asyraw= "<<asy2[nfill]<<" err "<<asyerr2[nfill]<<endl;
		//		sumasy[nmbin][nebin] += asy[nfill];
		//		sumerr[nmbin][nebin] += asyerr[nfill]*asyerr[nfill];	
			}	
			
			sprintf(picname,"Otherpic/IsoAn_AllFill_mass%.2fto%.2fGeV_E%.1fto%.1fGeV_mode%d.png",mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin],mode[nmode]);
			sprintf(picname2,"Otherpic/IsoAny_AllFill_mass%.2fto%.2fGeV_E%.1fto%.1fGeV_mode%d.png",mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin],mode[nmode]);
			TGraphErrors *forfit=new TGraphErrors(fillbin,filldouble,asy,fillex,asyerr);
			TGraphErrors *forfit2=new TGraphErrors(fillbin,filldouble,asy2,fillex,asyerr2);
			forfit->Fit("fcn1","RQ");
			asy_fill[nmode][nmbin][nebin]=fcn1->GetParameter(0);
			asyerr_fill[nmode][nmbin][nebin]=fcn1->GetParError(0);
			forfit2->Fit("fcn2","RQ");
			asy_fill2[nmode][nmbin][nebin]=fcn2->GetParameter(0);
			asyerr_fill2[nmode][nmbin][nebin]=fcn2->GetParError(0);
			//	cout<<" mode"<<nmode<<" m="<<nmbin<<" e="<<nebin<<" "<<asy_fill[nmode][nmbin][nebin]<<" "<<asyerr_fill[nmode][nmbin][nebin]<<" "<<endl;
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
	}//end mode
	
	double asyb01[nmodes][nebins];
	double asyb12[nmodes][nebins];
	double asyb23[nmodes][nebins];
	double asyerrb01[nmodes][nebins];
	double asyerrb12[nmodes][nebins];
	double asyerrb23[nmodes][nebins];
	double asyy01[nmodes][nebins];
	double asyy12[nmodes][nebins];
	double asyy23[nmodes][nebins];
	double asyerry01[nmodes][nebins];
	double asyerry12[nmodes][nebins];
	double asyy01[nmodes][nebins];
	double asyy12[nmodes][nebins];
	double asyy23[nmodes][nebins];
	double asyerry01[nmodes][nebins];
	double asyerry12[nmodes][nebins];
	double asyerry23[nmodes][nebins];
	//average loop
	for (int nmode=0; nmode<nmodes; nmode++){
		for (int nebin=0; nebin<nebins; nebin++){
/*
		average(asy_fill[nmode][2][nebin],asy_fill[nmode][3][nebin],asyerr_fill[nmode][2][nebin],asyerr_fill[nmode][3][nebin],asyb12[nmode][nebin],asyerrb12[nmode][nebin]);
		average(asy_fill[nmode][4][nebin],asy_fill[nmode][5][nebin],asy_fill[nmode][1][nebin],asyerr_fill[nmode][4][nebin],asyerr_fill[nmode][5][nebin],asyerr_fill[nmode][1][nebin],asyb23[nmode][nebin],asyerrb23[nmode][nebin]);
		average(asy_fill2[nmode][2][nebin],asy_fill2[nmode][3][nebin],asyerr_fill2[nmode][2][nebin],asyerr_fill2[nmode][3][nebin],asyy12[nmode][nebin],asyerry12[nmode][nebin]);
		average(asy_fill2[nmode][4][nebin],asy_fill2[nmode][5][nebin],asy_fill2[nmode][1][nebin],asyerr_fill2[nmode][4][nebin],asyerr_fill2[nmode][5][nebin],asyerr_fill2[nmode][1][nebin],asyy23[nmode][nebin],asyerry23[nmode][nebin]);
*/		
		asyb12[nmode][nebin]=asy_fill[nmode][0][nebin];
		asyb23[nmode][nebin]=asy_fill[nmode][1][nebin];
		asyerrb12[nmode][nebin]=asyerr_fill[nmode][0][nebin];
		asyerrb23[nmode][nebin]=asyerr_fill[nmode][1][nebin];
		asyy12[nmode][nebin]=asy_fill2[nmode][0][nebin];
		asyy23[nmode][nebin]=asy_fill2[nmode][1][nebin];
		asyerry12[nmode][nebin]=asyerr_fill2[nmode][0][nebin];
		asyerry23[nmode][nebin]=asyerr_fill2[nmode][1][nebin];
//		cout<<" signal region="<<asyb12[nmode][nebin]<<" +  "<<asyerrb12[nmode][nebin]<<" sb region"<<asyb23[nmode][nebin]<<" +  "<<asyerrb23[nmode][nebin]<<endl;
		}
	}

/*
	//mode0
	//TGraphErrors *gasyb01=new TGraphErrors(nebins,xf,asyb01,ex,asyerrb01);
	rGraphErrors *gasyb12m0=new TGraphErrors(nebins,xf,asyb12[0],ex,asyerrb12[0]);
	TGraphErrors *gasyb23m0=new TGraphErrors(nebins,xf,asyb23[0],ex,asyerrb23[0]);
	//TGraphErrors *gasyy01=new TGraphErrors(nebins,xf,asyy01,ex,asyerry01);
	TGraphErrors *gasyy12m0=new TGraphErrors(nebins,xf,asyy12[0],ex,asyerry12[0]);
	TGraphErrors *gasyy23m0=new TGraphErrors(nebins,xf,asyy23[0],ex,asyerry23[0]);
	//mode1
	//TGraphErrors *gasyb01=new TGraphErrors(nebins,xf,asyb01,ex,asyerrb01);
	TGraphErrors *gasyb12m1=new TGraphErrors(nebins,xf,asyb12[1],ex,asyerrb12[1]);
	TGraphErrors *gasyb23m1=new TGraphErrors(nebins,xf,asyb23[1],ex,asyerrb23[1]);
	//TGraphErrors *gasyy01=new TGraphErrors(nebins,xf,asyy01,ex,asyerry01);
	TGraphErrors *gasyy12m1=new TGraphErrors(nebins,xf,asyy12[1],ex,asyerry12[1]);
	TGraphErrors *gasyy23m1=new TGraphErrors(nebins,xf,asyy23[1],ex,asyerry23[1]);
	
	
	
	//gasy->Draw("ap*");
	//gasyb01->SetTitle("Signal m=0.0~0.1");
	gasyb12m0->SetTitle("Signal m=0.1~0.2");
	gasyb23m0->SetTitle("Signal m=0.2~0.3");
	//gasyb01->GetXaxis()->SetTitle("PiE/Gev");
	//gasyb01->GetYaxis()->SetTitle("A_{N}");
	gasyb12m0->GetXaxis()->SetTitle("PiE/Gev");
	gasyb12m0->GetYaxis()->SetTitle("A_{N}");
	gasyb23m0->GetXaxis()->SetTitle("PiE/Gev");
	gasyb23m0->GetYaxis()->SetTitle("A_{N}");
	//gasyy01->SetTitle("Signal m=0.0~0.1");
	gasyy12m0->SetTitle("Signal m=0.1~0.2");
	gasyy23m0->SetTitle("Signal m=0.2~0.3");
	//gasyy01->GetXaxis()->SetTitle("PiE/Gev");
	//gasyy01->GetYaxis()->SetTitle("A_{N}");
	gasyy12m0->GetXaxis()->SetTitle("PiE/Gev");
	gasyy12m0->GetYaxis()->SetTitle("A_{N}");
	gasyy23m0->GetXaxis()->SetTitle("PiE/Gev");
	gasyy23m0->GetYaxis()->SetTitle("A_{N}");
	//c1->Print("test.png");
*/	
	double asybs[nmodes][nebins];
	double asyerrbs[nmodes][nebins];
	double asyerrbs1[nmodes][nebins]=;//{0,0,0,0,0,0,0};
	double asyerrys1[nmodes][nebins];
	double asyys[nmodes][nebins];
	double asyerrys[nmodes][nebins];
	double asybb[nmodes][nebins];
	double asyerrbb[nmodes][nebins];
	double asyerrbb1[nmodes][nebins];
	double asyerryb1[nmodes][nebins];
	double asyyb[nmodes][nebins];
	double asyerryb[nmodes][nebins];
	double ferrbs1[nmodes][nebins];
	double ferrbs2[nmodes][nebins];
	double ferrys1[nmodes][nebins];
	double ferrys2[nmodes][nebins];
	double ferrbb1[nmodes][nebins];
	double ferrbb2[nmodes][nebins];
	double ferryb1[nmodes][nebins];
	double ferryb2[nmodes][nebins];
	
	
	double f1[nmodes][nebins];//sig in sig
	double f2[nmodes][nebins];//sig in bkg
	double f1E[nmodes][nebins];//
	double f2E[nmodes][nebins];//
	
	ifstream frac1;
	ifstream frac2;
	frac1.open("txt/15/fracm0.txt",ios::in);
	for (int i=0 ; i<nebins ; i++){
	frac1>>f1[0][i]>>f1E[0][i]>>f2[0][i]>>f2E[0][i];
	}
	frac2.open("txt/15/fracm1.txt",ios::in);
	for (int i=0 ; i<nebins ; i++){
	frac2>>f1[1][i]>>f1E[1][i]>>f2[1][i]>>f2E[1][i];
	}
	
	double asyFinal;
	double asyerrFinal;
	double f3;
	double f4;
	
for (int nmode=0; nmode<nmodes; nmode++){
	cout<<nmode<<endl;
	for (int nebin=0; nebin<nebins; nebin++){
//	cout<<" f1="<<f1[nmode][nebin]<<" f2="<<f2[nmode][nebin]<<endl;
	f3=(1-f1[nmode][nebin])/(1-f2[nmode][nebin]);
	f4=f1[nmode][nebin]/f2[nmode][nebin];
	if (Mset==12345) f3=0; //  12 is 5 mass region average

	//12-signal region 23bkg region
	asybs[nmode][nebin]=(asyb12[nmode][nebin]-asyb23[nmode][nebin]*f3)/(1-f3)/pol;
	asyerrbs[nmode][nebin]=TMath::Sqrt(asyerrb12[nmode][nebin]*asyerrb12[nmode][nebin]+asyerrb23[nmode][nebin]*asyerrb23[nmode][nebin]*f3*f3)/TMath::Abs(1-f3)/pol;
	asyys[nmode][nebin]=(asyy12[nmode][nebin]-asyy23[nmode][nebin]*f3)/(1-f3)/polY;
	asyerrys[nmode][nebin]=TMath::Sqrt(asyerry12[nmode][nebin]*asyerry12[nmode][nebin]+asyerry23[nmode][nebin]*asyerry23[nmode][nebin]*f3*f3)/TMath::Abs(1-f3)/polY;
	if(Mset !=12345)
	{
	asybb[nmode][nebin]=(asyb12[nmode][nebin]-asyb23[nmode][nebin]*f4)/(1-f4)/pol;
	asyerrbb[nmode][nebin]=TMath::Sqrt(asyerrb12[nmode][nebin]*asyerrb12[nmode][nebin]+asyerrb23[nmode][nebin]*asyerrb23[nmode][nebin]*f4*f4)/TMath::Abs(1-f4)/pol;
	asyyb[nmode][nebin]=(asyy12[nmode][nebin]-asyy23[nmode][nebin]*f4)/(1-f4)/polY;
	asyerryb[nmode][nebin]=TMath::Sqrt(asyerry12[nmode][nebin]*asyerry12[nmode][nebin]+asyerry23[nmode][nebin]*asyerry23[nmode][nebin]*f4*f4)/TMath::Abs(1-f4)/polY;
	}	
	//asyerrbs1[nebin]=sqrt(pow(asyerrbs[nebin],2)+pow(unpol*asybs[nebin]/pol/pol,2));//with unpol
	//asyerrbb1[nebin]=sqrt(pow(asyerrbb[nebin],2)+pow(unpol*asybb[nebin]/pol/pol,2));//with unpol
	//12 signal region 23 background region
	//uncertaintt of f1 f2
	//sig
	ferrys1[nmode][nebin]=((asyy12[nmode][nebin]-asyy23[nmode][nebin])*(1-f2[nmode][nebin])/(f1[nmode][nebin]-f2[nmode][nebin])/(f1[nmode][nebin]-f2[nmode][nebin]))/pol;
	ferrys2[nmode][nebin]=((asyy12[nmode][nebin]-asyy23[nmode][nebin])*(1-f1[nmode][nebin])/(f1[nmode][nebin]-f2[nmode][nebin])/(f1[nmode][nebin]-f2[nmode][nebin]))/pol;//verse f2[nmode][nebin]
	ferrbs1[nmode][nebin]=((asyb12[nmode][nebin]-asyb23[nmode][nebin])*(1-f2[nmode][nebin])/(f1[nmode][nebin]-f2[nmode][nebin])/(f1[nmode][nebin]-f2[nmode][nebin]))/pol;
	ferrbs2[nmode][nebin]=((asyb12[nmode][nebin]-asyb23[nmode][nebin])*(1-f1[nmode][nebin])/(f1[nmode][nebin]-f2[nmode][nebin])/(f1[nmode][nebin]-f2[nmode][nebin]))/pol;
	//bkg
	ferryb1[nmode][nebin]=((asyy12[nmode][nebin]-asyy23[nmode][nebin])*f2[nmode][nebin]/(f1[nmode][nebin]-f2[nmode][nebin])/(f1[nmode][nebin]-f2[nmode][nebin]))/pol;
	ferryb2[nmode][nebin]=((asyy12[nmode][nebin]-asyy23[nmode][nebin])*f1[nmode][nebin]/(f1[nmode][nebin]-f2[nmode][nebin])/(f1[nmode][nebin]-f2[nmode][nebin]))/pol;//verse f2[nmode][nebin]
	ferrbb1[nmode][nebin]=((asyb12[nmode][nebin]-asyb23[nmode][nebin])*f2[nmode][nebin]/(f1[nmode][nebin]-f2[nmode][nebin])/(f1[nmode][nebin]-f2[nmode][nebin]))/pol;
	ferrbb2[nmode][nebin]=((asyb12[nmode][nebin]-asyb23[nmode][nebin])*f1[nmode][nebin]/(f1[nmode][nebin]-f2[nmode][nebin])/(f1[nmode][nebin]-f2[nmode][nebin]))/pol;
	
	asyerrbs1[nmode][nebin]=sqrt(pow(ferrbs1[nmode][nebin]*f1E[nmode][nebin],2)+pow(ferrbs2[nmode][nebin]*f2E[nmode][nebin],2));
	asyerrbb1[nmode][nebin]=sqrt(pow(ferrbb1[nmode][nebin]*f1E[nmode][nebin],2)+pow(ferrbb2[nmode][nebin]*f2E[nmode][nebin],2));
	asyerrys1[nmode][nebin]=sqrt(pow(ferrys1[nmode][nebin]*f1E[nmode][nebin],2)+pow(ferrys2[nmode][nebin]*f2E[nmode][nebin],2));
	asyerryb1[nmode][nebin]=sqrt(pow(ferryb1[nmode][nebin]*f1E[nmode][nebin],2)+pow(ferryb2[nmode][nebin]*f2E[nmode][nebin],2));
	
//	cout<<"f3="<<f3<<" f4="<<f4<<" bberr="<<asyerrbb[nmode][nebin]<<" bserr="<<asyerrbs[nmode][nebin]<<" bb="<<asybb[nmode][nebin]<<" bs="<<asybs[nmode][nebin]<<" yberr="<<asyerryb[nmode][nebin]<<"ybserr="<<asyerrys[nmode][nebin]<<" yb="<<asyyb[nmode][nebin]<<" ys="<<asyys[nmode][nebin]<<"  "<< asyerrbs1[nmode][nebin]<<"  "<< asyerrbb1[nmode][nebin]<<"  "<< asyerrys1[nmode][nebin]<<"  "<< asyerryb1[nmode][nebin]<<endl;
//	cout<<"mode="<<nmode<<" ebin="<<nebin<<" bs="<<asybs[nmode][nebin]<<" ys="<<asyys[nmode][nebin]<<"  "<<endl;
//	cout<<asyerrbs1[nmode][nebin]<<" "<<asyerrbb1[nmode][nebin]<<" "<<asyerrys1[nmode][nebin]<<" "<<asyerryb1[nmode][nebin]<<" " <<endl;

	if (nmode==0) cout<<nebin<<" "<<xf[nmode][nebin] <<" "<< Ptmean15Iso0[nebin]<<" "<<     asybs[nmode][nebin]<<" "<<asyerrbs[nmode][nebin] <<" "<<asyerrbs1[nmode][nebin] <<endl;
	if (nmode==1) cout<<nebin<<" "<<xf[nmode][nebin] <<" "<< Ptmean15Iso1[nebin]<<" "<<     asybs[nmode][nebin]<<" "<<asyerrbs[nmode][nebin] <<" "<<asyerrbs1[nmode][nebin] <<endl;
	}
}
//Overall
	double asybsAll[nebins];
	double asybserrAll[nebins];
	for (int nebin=0; nebin<nebins; nebin++){
	average( asybs[0][nebin], asybs[1][nebin], asyerrbs[0][nebin], asyerrbs[1][nebin],asybsAll[nebin],asybserrAll[nebin]);
	}

	TGraphErrors *gasybs[3];
	TGraphErrors *gasybb[3];
	TGraphErrors *gasybberr[3];
	TGraphErrors *gasybserr[3];
	TGraphErrors *gasyys[3];
	TGraphErrors *gasyyb[3];
	TGraphErrors *gasyyberr[3];
	TGraphErrors *gasyyserr[3];

	TH2F *bkg = new TH2F("bkg15","A_{N} for Inclusive #pi^{0} ",20,0.16,0.65,10,-0.02,0.18);
	        bkg->GetXaxis()->SetTitle("x_{F}");
	        bkg->GetYaxis()->SetTitle("A_{N}");
	        bkg->GetXaxis()->CenterTitle(true);;
	        bkg->GetYaxis()->CenterTitle(true);;
	        bkg->GetYaxis()->SetTitleSize(0.04);;
	TH2F *bkg2 = new TH2F("bkg15_2","A_{N} for Inclusive #pi^{0} ",20,-0.65,-0.16,10,-0.02,0.18);
	        bkg2->GetXaxis()->SetTitle("x_{F}");
	        bkg2->GetYaxis()->SetTitle("A_{N}");
	        bkg2->GetXaxis()->CenterTitle(true);;
	        bkg2->GetYaxis()->CenterTitle(true);;
	        bkg2->GetYaxis()->SetTitleSize(0.04);;

	TLegend *leg;
	TLegend *leg2;
	 TLatex l;
	 TLatex l2;


		c2->cd(1);
	        bkg->Draw();
	for (int i=0 ; i<nmodes ; i++) {
	gasybs[i]=new TGraphErrors(nebins,xf[i], asybs[i],ex0[i],asyerrbs[i]);//only useful in 12345
	gasybb[i]=new TGraphErrors(nebins,xf[i], asybb[i],ex0[i],asyerrbb[i]);
	gasybserr[i]=new TGraphErrors(nebins,xf[i],asybs[i],ex1[i],asyerrbs1[i]);
	gasybberr[i]=new TGraphErrors(nebins,xf[i],asybb[i],ex0[i],asyerrbb1[i]);//syst uncertainty
	
	gasyys[i]=new TGraphErrors(nebins,xfm[i], asyys[i],ex0[i],asyerrys[i]);
	gasyyb[i]=new TGraphErrors(nebins,xfm[i], asyyb[i],ex0[i],asyerryb[i]);
	gasyyserr[i]=new TGraphErrors(nebins,xfm[i], asyys[i],ex0[i],asyerrys1[i]);
	gasyyberr[i]=new TGraphErrors(nebins,xfm[i], asyyb[i],ex0[i],asyerryb1[i]);
	}
	for (int i=0 ; i<nmodes ; i++) {
	gasybs[i]->SetMarkerStyle(24-i*4);
	gasybs[i]->SetMarkerSize(1.3);
	gasybs[i]->SetMarkerColor(kBlue);
	gasybs[i]->SetLineWidth(2);
	gasybs[i]->SetLineColor(kBlue);
	gasybs[i]->Draw("psame");
	gasybs[i]->GetXaxis()->SetTitle("PiE/Gev");
	gasybs[i]->GetYaxis()->SetTitle("A_{N} xf>0");
	
	gasybserr[i]->SetMarkerStyle(24-i*4);
	gasybserr[i]->SetMarkerSize(1.3);
	gasybserr[i]->SetMarkerColor(kBlue);
	gasybserr[i]->SetLineWidth(2);
	gasybserr[i]->SetLineColor(kBlue);
	if(syst) gasybserr[i]->Draw("p2");
	gasybserr[i]->GetXaxis()->SetTitle("PiE/Gev");
	gasybserr[i]->GetYaxis()->SetTitle("A_{N} xf>0");
	gasybserr[i]->SetFillColor(kBlack);
	gasybserr[i]->SetFillStyle(3002);
	
	gasybb[i]->SetMarkerStyle(24-i*4);
	gasybb[i]->SetMarkerSize(1.3);
	gasybb[i]->SetMarkerColor(kGreen+3);
	gasybb[i]->SetLineWidth(2);
	gasybb[i]->SetLineColor(kGreen+3);
 	gasybb[i]->Draw("p");
	gasybb[i]->GetXaxis()->SetTitle("PiE/Gev");
	gasybb[i]->GetYaxis()->SetTitle("A_{N} bkg");
	
	gasybberr[i]->SetMarkerStyle(24-i*4);
	gasybberr[i]->SetMarkerSize(1.3);
	gasybberr[i]->SetMarkerColor(kGreen+3);
	gasybberr[i]->SetLineWidth(2);
	gasybberr[i]->SetLineColor(kGreen+3);
if(syst)  gasybberr[i]->Draw("p2");
	gasybberr[i]->GetXaxis()->SetTitle("PiE/Gev");
	gasybberr[i]->GetYaxis()->SetTitle("A_{N} bkg");
	gasybberr[i]->SetFillColor(kBlack);
	gasybberr[i]->SetFillStyle(3002);
	
	}
	leg=new TLegend(0.50,0.70,0.89,0.85);
	                leg->SetMargin(0.2);
	                leg->SetBorderSize(0);
	                leg->SetFillColor(0);
	                leg->SetTextSize(0.04);
	                leg->AddEntry(gasybs[0],"Non-isolated #pi^{0} x_{F}>0","PE");
	                leg->AddEntry(gasybb[0],"Non-isolated #pi^{0} background ","PE");
	                leg->AddEntry(gasybs[1],"Isolated #pi^{0} x_{F}>0","PE");
	                leg->AddEntry(gasybb[1],"Isolated #pi^{0} background","PE");
	leg->Draw();
	
	    l.SetTextSize(0.03);
	    l2.SetTextSize(0.04);
		l.SetTextAngle(0.);
		l.DrawLatex(0.18,0.10,"3.0% beam pol. scale uncertainty not shown");
		double dx=0.18; double dy=0.042+0.12;
		       l2.DrawLatex(dx,dy-0.000,"p^{#uparrow} + p -> #pi^{0} + X @ #sqrt{s}=200 GeV");
		       l2.DrawLatex(dx,dy-0.012,"  p_{T} > 2 GeV");
		    	l2.DrawLatex(dx,dy-0.024," 2.7 < #eta < 4.0");
	
		c2->cd(2);
	        bkg2->Draw();
	
	for (int i=0 ; i<nmodes ; i++) {
	gasyys[i]->SetMarkerStyle(24-4*i);
	gasyys[i]->SetMarkerSize(1.3);
	gasyys[i]->SetMarkerColor(kMagenta);
	gasyys[i]->SetLineWidth(2);
	gasyys[i]->SetLineColor(kMagenta);
	gasyys[i]->Draw("psame");
	gasyys[i]->GetXaxis()->SetTitle("PiE/Gev");
	gasyys[i]->GetYaxis()->SetTitle("A_{N} xf>0");
	
	gasyyserr[i]->SetMarkerStyle(24-4*i);
	gasyyserr[i]->SetMarkerSize(1.3);
	gasyyserr[i]->SetMarkerColor(kMagenta);
	gasyyserr[i]->SetLineWidth(2);
	gasyyserr[i]->SetLineColor(kMagenta);
	if(syst) gasyyserr[i]->Draw("p2");
	gasyyserr[i]->GetXaxis()->SetTitle("PiE/Gev");
	gasyyserr[i]->GetYaxis()->SetTitle("A_{N} xf>0");
	gasyyserr[i]->SetFillColor(kBlack);
	gasyyserr[i]->SetFillStyle(3002);
	
	gasyyb[i]->SetMarkerStyle(24-i*4);
	gasyyb[i]->SetMarkerSize(1.3);
	gasyyb[i]->SetMarkerColor(kGreen+3);
	gasyyb[i]->SetLineWidth(2);
	gasyyb[i]->SetLineColor(kGreen+3);
 	gasyyb[i]->Draw("p");
	gasyyb[i]->GetXaxis()->SetTitle("PiE/Gev");
	gasyyb[i]->GetYaxis()->SetTitle("A_{N} bkg");
	
	gasyyberr[i]->SetMarkerStyle(24-i*4);
	gasyyberr[i]->SetMarkerSize(1.3);
	gasyyberr[i]->SetMarkerColor(kGreen+3);
	gasyyberr[i]->SetLineWidth(2);
	gasyyberr[i]->SetLineColor(kGreen+3);
 if(syst)	gasyyberr[i]->Draw("p2");
	gasyyberr[i]->GetXaxis()->SetTitle("PiE/Gev");
	gasyyberr[i]->GetYaxis()->SetTitle("A_{N} bkg");
	gasyyberr[i]->SetFillColor(kBlack);
	gasyyberr[i]->SetFillStyle(3002);
	}
	leg2=new TLegend(0.50,0.70,0.89,0.85);
	                leg2->SetMargin(0.2);
	                leg2->SetBorderSize(0);
	                leg2->SetFillColor(0);
	                leg2->SetTextSize(0.04);
					leg2->AddEntry(gasyys[0],"Non-isolated #pi^{0} x_{F}<0","PE");
	                leg2->AddEntry(gasyyb[0],"Non-isolated #pi^{0} background ","PE");
	                leg2->AddEntry(gasyys[1],"Isolated #pi^{0} x_{F}<0","PE");
	                leg2->AddEntry(gasyyb[1],"Isolated #pi^{0} background ","PE");

	leg2->Draw();
	l.DrawLatex(-0.63,0.10,"3.0% beam pol. scale uncertainty not shown");
	
	char pname[100];
//	sprintf(pname,"DrawIsoAn15.png",i);
//	c2->Print(pname);
//	c2->SaveAs("digitRun15Iso.C");
	
	gasybs[2]=new TGraphErrors(nebins,xf[0], asybsAll,ex0[0],asybserrAll);

	gjetAn15Iso0 =  (TGraphErrors*)gasybs[0]->Clone();
    gjetAn15Iso0Err =  (TGraphErrors*)gasybserr[0]->Clone();
	gjetAn15Iso1 =  (TGraphErrors*)gasybs[1]->Clone();
    gjetAn15Iso1Err =  (TGraphErrors*)gasybserr[1]->Clone();
	gjetAn15 =  (TGraphErrors*)gasybs[2]->Clone();



	
	//gasyb01->Write();
	//gasyb12m0->Write();
	//gasyb23m0->Write();
	//gasyy01->Write();
	//gasyy12[i]->Write();
	//gasyy23[i]->Write();
/*	gasybs[i]->Write();
	gasybb[i]->Write();
	gasyys[i]->Write();
	gasyyb[i]->Write();
	fout->Write();
*/

	//mode

}


drawIsoAn11(int Mset = 12345){
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
	
	int mode[2] = {0,1};
	const int nmodes = 2;
	
	double ebinlows[7] = {38, 43, 48, 53, 58, 65, 75};
	double ebinhighs[7] = {43, 48, 53, 58, 65, 75, 90};
	const int nebins = 7;
	double mbinlows[2] = {0.00, 0.20};
	double mbinhighs[2] = { 0.20, 0.30};
	const int nmbins = 2;
	char resultname[200];
	char resultname2[200];
	char picname[200];
	char picname2[200];
	double ex[nmodes][7];
	double exa[7]= {0,0,0,0,0,0,0};//x error 
	double exb[7]= {0,0,0,0,0,0,0};//x error 

	double ex10[7]={0,0,0,0,0,0,0};
	double ex11[7]={0,0,0,0,0,0,0};

	double ex0[nmodes][7];
	double ex1[nmodes][7];
	double ex00[7]= {0.005,0.006,0.007,0.007,0.008,0.009,0.011};
	double ex01[7]= {0.005,0.006,0.007,0.007,0.008,0.009,0.011};
	double xf[nmodes][7];
	double xfm[nmodes][7];
	double xfb[nmodes][7];
	for (int nebin=0; nebin<nebins; nebin++){
		//xf[nebin]= (ebinlows[nebin]+ebinhighs[nebin])/2.0/250; //    !!!!!!!!!!type change!!!!!!!!!!
		xf[0][nebin]= xf11Iso0[nebin]/250;
		xf[1][nebin]= xf11Iso1[nebin]/250;
		ex0[0][nebin]= Rsyst*xf[0][nebin];
		ex0[0][nebin]= Rsyst*xf[0][nebin];
		ex1[0][nebin]= 0.00;
		ex1[1][nebin]= 0.00;
		xfb[0][nebin]= xf[0][nebin]+0.005;
		xfb[1][nebin]= xf[1][nebin]+0.005;
//		xf2[nebin]=( (ebinlows[nebin]+ebinhighs[nebin])/2+0.5)/250;
		//out<< xf[nebin]<<" " << xf1[nebin]<<endl;
		xfm[0][nebin]= -xf[0][nebin];
		xfm[1][nebin]= -xf[0][nebin];
	}
	ifstream result;
	ifstream result2;
	
	TF1 *fcn1 = new TF1 ("fcn1","pol0",0,60);
	TF1 *fcn2 = new TF1 ("fcn2","pol0",0,60);
	
//	TFile *fout= new TFile ("DrawIsoAn11.root","recreate");
//	fout->cd();
	//	 TCanvas *c1 = new TCanvas("c1", "c1",0,0,1600,900);
	//	 c1->SetGrid(0,0);
	 	TCanvas *c2 = new TCanvas("c2", "c2",0,0,1200,450);
		 c2->SetGrid(0,0);
		 c2->Divide(2,1);
	double asy_fill[nmodes][nmbins][7];
	double asyerr_fill[nmodes][nmbins][7];
	double asy_fill2[nmodes][nmbins][7];
	double asyerr_fill2[nmodes][nmbins][7];



	for (int nmode=0; nmode<nmodes  ;nmode++){
		for (int nmbin=0; nmbin<nmbins;nmbin++){
		   for (int nebin=0; nebin<nebins; nebin++){
	
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
				asyerr2[nfill]=0;
				asyerr[nfill]=0;
			//cout<<"bin  "<<mbinlows[nmbin]<<"   "<<mbinhighs[nmbin]<<endl;
				sprintf(resultname,"/star/u/zwzhu/01zwzhu/ana/New/PaperCode/Code2/Run11/result/IsoAN2/IsoAN2_BKG_Fill%d_mass%.2fto%.2fGeV_E%.1fto%.1fGeV_mode%d.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin],mode[nmode]);
				sprintf(resultname2,"/star/u/zwzhu/01zwzhu/ana/New/PaperCode/Code2/Run11/result/IsoAN2/IsoANy2_BKG_Fill%d_mass%.2fto%.2fGeV_E%.1fto%.1fGeV_mode%d.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin],mode[nmode]);
		//	sprintf(resultname,"/star/u/zwzhu/workspace/project/FMS/DEV/calAN/ebins/result/crAnvsxF_7ebinsFill%d_mass%.2fto%.2fGeV_E%.1fto%.1fGeV_AllTrigger.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
				TString infile(resultname);
				TString infile2(resultname2);
				result.open(resultname,ios::in);
				result2.open(resultname2,ios::in);
				 if(!result )  cout<<" file not exist"<<endl;
			
			
				result>>fill[nfill]>>ene[nfill]>>asy[nfill]>>asyerr[nfill]>>p0[nfill]>>p0e[nfill]>>ml[nfill]>>mh[nfill];
				result2>>fill[nfill]>>ene[nfill]>>asy2[nfill]>>asyerr2[nfill]>>p02[nfill]>>p0e2[nfill]>>ml[nfill]>>mh[nfill];
				result.close();
				result2.close();
        if (asyerr2[nfill]==0.) {  cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<resultname2<<endl  ;    
            asy2[nfill]=0;    
            asyerr2[nfill]=999;
        }   

        if (asyerr[nfill]==0.) {  cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<resultname<<endl  ;    
            asy[nfill]=0; 
            asyerr[nfill]=999;
        }   

		//		cout<<fill[nfill]<<" asyraw= "<<asy2[nfill]<<" err "<<asyerr2[nfill]<<endl;
		//		sumasy[nmbin][nebin] += asy[nfill];
		//		sumerr[nmbin][nebin] += asyerr[nfill]*asyerr[nfill];	
			}	
			
			sprintf(picname,"./result/pic/AllFill_mass%.2fto%.2fGeV_E%.1fto%.1fGeV_mode%d.png",mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin],mode[nmode]);
			sprintf(picname2,"./yresult/pic/AllFill_mass%.2fto%.2fGeV_E%.1fto%.1fGeV_mode%d.png",mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin],mode[nmode]);
			TGraphErrors *forfit=new TGraphErrors(fillbin,filldouble,asy,fillex,asyerr);
			TGraphErrors *forfit2=new TGraphErrors(fillbin,filldouble,asy2,fillex,asyerr2);
			forfit->Fit("fcn1","RQ");
			asy_fill[nmode][nmbin][nebin]=fcn1->GetParameter(0);
			asyerr_fill[nmode][nmbin][nebin]=fcn1->GetParError(0);
			forfit2->Fit("fcn2","RQ");
			asy_fill2[nmode][nmbin][nebin]=fcn2->GetParameter(0);
			asyerr_fill2[nmode][nmbin][nebin]=fcn2->GetParError(0);
	//			cout<<nmode<<" "<<nmbin<<" "<<nebin<<" "<<asy_fill[nmode][nmbin][nebin]<<" "<<asyerr_fill[nmode][nmbin][nebin]<<" "<<endl;
					 forfit->SetTitle(picname);
					 forfit->SetLineWidth(2);
					 forfit->SetLineColor(4);
					 forfit->SetMarkerSize(3);
					 forfit->GetXaxis()->SetTitle("Fill Index");
	                 forfit->GetYaxis()->SetTitle("A_{N}");
	                 forfit2->SetTitle(picname2);
					 forfit2->SetLineWidth(2);
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
	}//end mode
	
	double asyb01[nmodes][7];
	double asyb12[nmodes][7];
	double asyb23[nmodes][7];
	double asyerrb01[nmodes][7];
	double asyerrb12[nmodes][7];
	double asyerrb23[nmodes][7];
	double asyy01[nmodes][7];
	double asyy12[nmodes][7];
	double asyy23[nmodes][7];
	double asyerry01[nmodes][7];
	double asyerry12[nmodes][7];
	double asyerry23[nmodes][7];
	//average loop
	for (int nmode=0; nmode<nmodes; nmode++){
		for (int nebin=0; nebin<7; nebin++){

/*
		average(asy_fill[nmode][2][nebin],asy_fill[nmode][3][nebin],asyerr_fill[nmode][2][nebin],asyerr_fill[nmode][3][nebin],asyb12[nmode][nebin],asyerrb12[nmode][nebin]);
		average(asy_fill[nmode][4][nebin],asy_fill[nmode][5][nebin],asy_fill[nmode][1][nebin],asyerr_fill[nmode][4][nebin],asyerr_fill[nmode][5][nebin],asyerr_fill[nmode][1][nebin],asyb23[nmode][nebin],asyerrb23[nmode][nebin]);
		average(asy_fill2[nmode][2][nebin],asy_fill2[nmode][3][nebin],asyerr_fill2[nmode][2][nebin],asyerr_fill2[nmode][3][nebin],asyy12[nmode][nebin],asyerry12[nmode][nebin]);
		average(asy_fill2[nmode][4][nebin],asy_fill2[nmode][5][nebin],asy_fill2[nmode][1][nebin],asyerr_fill2[nmode][4][nebin],asyerr_fill2[nmode][5][nebin],asyerr_fill2[nmode][1][nebin],asyy23[nmode][nebin],asyerry23[nmode][nebin]);
*/		
		asyb12[nmode][nebin]=asy_fill[nmode][0][nebin];
		asyb23[nmode][nebin]=asy_fill[nmode][1][nebin];
		asyerrb12[nmode][nebin]=asyerr_fill[nmode][0][nebin];
		asyerrb23[nmode][nebin]=asyerr_fill[nmode][1][nebin];
		asyy12[nmode][nebin]=asy_fill2[nmode][0][nebin];
		asyy23[nmode][nebin]=asy_fill2[nmode][1][nebin];
		asyerry12[nmode][nebin]=asyerr_fill2[nmode][0][nebin];
		asyerry23[nmode][nebin]=asyerr_fill2[nmode][1][nebin];
		}
	}

/*
	//mode0
	//TGraphErrors *gasyb01=new TGraphErrors(nebins,xf,asyb01,ex,asyerrb01);
	TGraphErrors *gasyb12m0=new TGraphErrors(nebins,xf,asyb12[0],ex,asyerrb12[0]);
	TGraphErrors *gasyb23m0=new TGraphErrors(nebins,xf,asyb23[0],ex,asyerrb23[0]);
	//TGraphErrors *gasyy01=new TGraphErrors(nebins,xf,asyy01,ex,asyerry01);
	TGraphErrors *gasyy12m0=new TGraphErrors(nebins,xf,asyy12[0],ex,asyerry12[0]);
	TGraphErrors *gasyy23m0=new TGraphErrors(nebins,xf,asyy23[0],ex,asyerry23[0]);
	//mode1
	//TGraphErrors *gasyb01=new TGraphErrors(nebins,xf,asyb01,ex,asyerrb01);
	TGraphErrors *gasyb12m1=new TGraphErrors(nebins,xf,asyb12[1],ex,asyerrb12[1]);
	TGraphErrors *gasyb23m1=new TGraphErrors(nebins,xf,asyb23[1],ex,asyerrb23[1]);
	//TGraphErrors *gasyy01=new TGraphErrors(nebins,xf,asyy01,ex,asyerry01);
	TGraphErrors *gasyy12m1=new TGraphErrors(nebins,xf,asyy12[1],ex,asyerry12[1]);
	TGraphErrors *gasyy23m1=new TGraphErrors(nebins,xf,asyy23[1],ex,asyerry23[1]);
	
	
	
	//gasy->Draw("ap*");
	//gasyb01->SetTitle("Signal m=0.0~0.1");
	gasyb12m0->SetTitle("Signal m=0.1~0.2");
	gasyb23m0->SetTitle("Signal m=0.2~0.3");
	//gasyb01->GetXaxis()->SetTitle("PiE/Gev");
	//gasyb01->GetYaxis()->SetTitle("A_{N}");
	gasyb12m0->GetXaxis()->SetTitle("PiE/Gev");
	gasyb12m0->GetYaxis()->SetTitle("A_{N}");
	gasyb23m0->GetXaxis()->SetTitle("PiE/Gev");
	gasyb23m0->GetYaxis()->SetTitle("A_{N}");
	//gasyy01->SetTitle("Signal m=0.0~0.1");
	gasyy12m0->SetTitle("Signal m=0.1~0.2");
	gasyy23m0->SetTitle("Signal m=0.2~0.3");
	//gasyy01->GetXaxis()->SetTitle("PiE/Gev");
	//gasyy01->GetYaxis()->SetTitle("A_{N}");
	gasyy12m0->GetXaxis()->SetTitle("PiE/Gev");
	gasyy12m0->GetYaxis()->SetTitle("A_{N}");
	gasyy23m0->GetXaxis()->SetTitle("PiE/Gev");
	gasyy23m0->GetYaxis()->SetTitle("A_{N}");
	//c1->Print("test.png");
*/	
	double asybs[nmodes][7];
	double asyerrbs[nmodes][7];
	double asyerrbs1[nmodes][7]=;//{0,0,0,0,0,0,0};
	double asyerrys1[nmodes][7];
	double asyys[nmodes][7];
	double asyerrys[nmodes][7];
	double asybb[nmodes][7];
	double asyerrbb[nmodes][7];
	double asyerrbb1[nmodes][7];
	double asyerryb1[nmodes][7];
	double asyyb[nmodes][7];
	double asyerryb[nmodes][7];
	//double f1[7]={0.694,0.712,0.728,0.732,0.741,0.757,0.792};
	//double f2[7]={0.786,0.761,0.748,0.760,0.756,0.718,0.584};
	double ferrbs1[nmodes][7];
	double ferrbs2[nmodes][7];
	double ferrys1[nmodes][7];
	double ferrys2[nmodes][7];
	double ferrbb1[nmodes][7];
	double ferrbb2[nmodes][7];
	double ferryb1[nmodes][7];
	double ferryb2[nmodes][7];
	
	
	double f1[nmodes][7];//sig in sig
	double f2[nmodes][7];//sig in bkg
	double f1E[nmodes][7];//
	double f2E[nmodes][7];//
	
	ifstream frac1;
	ifstream frac2;
	frac1.open("txt/11/fracm0.txt",ios::in);
	for (int i=0 ; i<7 ; i++){
	frac1>>f1[0][i]>>f1E[0][i]>>f2[0][i]>>f2E[0][i];
	}
	frac2.open("txt/11/fracm1.txt",ios::in);
	for (int i=0 ; i<7 ; i++){
	frac2>>f1[1][i]>>f1E[1][i]>>f2[1][i]>>f2E[1][i];
	}
	
	double asyFinal;
	double asyerrFinal;
	double f3;
	double f4;
	
for (int nmode=0; nmode<nmodes; nmode++){
	cout<<nmode<<endl;
	for (int nebin=0; nebin<7; nebin++){
//	cout<<f1[nmode][nebin]<<endl;
	f3=(1-f1[nmode][nebin])/(1-f2[nmode][nebin]);
	f4=f1[nmode][nebin]/f2[nmode][nebin];
	if (Mset==12345) f3=0; //  12 is 5 mass region average

	//12-signal region 23bkg region
	asybs[nmode][nebin]=(asyb12[nmode][nebin]-asyb23[nmode][nebin]*f3)/(1-f3)/pol;
	asyerrbs[nmode][nebin]=TMath::Sqrt(asyerrb12[nmode][nebin]*asyerrb12[nmode][nebin]+asyerrb23[nmode][nebin]*asyerrb23[nmode][nebin]*f3*f3)/TMath::Abs(1-f3)/pol;
	asyys[nmode][nebin]=(asyy12[nmode][nebin]-asyy23[nmode][nebin]*f3)/(1-f3)/polY;
	asyerrys[nmode][nebin]=TMath::Sqrt(asyerry12[nmode][nebin]*asyerry12[nmode][nebin]+asyerry23[nmode][nebin]*asyerry23[nmode][nebin]*f3*f3)/TMath::Abs(1-f3)/polY;
 if(Mset !=12345){
	asybb[nmode][nebin]=(asyb12[nmode][nebin]-asyb23[nmode][nebin]*f4)/(1-f4)/pol;
	asyerrbb[nmode][nebin]=TMath::Sqrt(asyerrb12[nmode][nebin]*asyerrb12[nmode][nebin]+asyerrb23[nmode][nebin]*asyerrb23[nmode][nebin]*f4*f4)/TMath::Abs(1-f4)/pol;
	asyyb[nmode][nebin]=(asyy12[nmode][nebin]-asyy23[nmode][nebin]*f4)/(1-f4)/polY;
	asyerryb[nmode][nebin]=TMath::Sqrt(asyerry12[nmode][nebin]*asyerry12[nmode][nebin]+asyerry23[nmode][nebin]*asyerry23[nmode][nebin]*f4*f4)/TMath::Abs(1-f4)/polY;
	}
	//asyerrbs1[nebin]=sqrt(pow(asyerrbs[nebin],2)+pow(unpol*asybs[nebin]/pol/pol,2));//with unpol
	//asyerrbb1[nebin]=sqrt(pow(asyerrbb[nebin],2)+pow(unpol*asybb[nebin]/pol/pol,2));//with unpol
	//12 signal region 23 background region
	//uncertaintt of f1 f2
	//sig
	ferrys1[nmode][nebin]=((asyy12[nmode][nebin]-asyy23[nmode][nebin])*(1-f2[nmode][nebin])/(f1[nmode][nebin]-f2[nmode][nebin])/(f1[nmode][nebin]-f2[nmode][nebin]))/pol;
	ferrys2[nmode][nebin]=((asyy12[nmode][nebin]-asyy23[nmode][nebin])*(1-f1[nmode][nebin])/(f1[nmode][nebin]-f2[nmode][nebin])/(f1[nmode][nebin]-f2[nmode][nebin]))/pol;//verse f2[nmode][nebin]
	ferrbs1[nmode][nebin]=((asyb12[nmode][nebin]-asyb23[nmode][nebin])*(1-f2[nmode][nebin])/(f1[nmode][nebin]-f2[nmode][nebin])/(f1[nmode][nebin]-f2[nmode][nebin]))/pol;
	ferrbs2[nmode][nebin]=((asyb12[nmode][nebin]-asyb23[nmode][nebin])*(1-f1[nmode][nebin])/(f1[nmode][nebin]-f2[nmode][nebin])/(f1[nmode][nebin]-f2[nmode][nebin]))/pol;
	//bkg
	ferryb1[nmode][nebin]=((asyy12[nmode][nebin]-asyy23[nmode][nebin])*f2[nmode][nebin]/(f1[nmode][nebin]-f2[nmode][nebin])/(f1[nmode][nebin]-f2[nmode][nebin]))/pol;
	ferryb2[nmode][nebin]=((asyy12[nmode][nebin]-asyy23[nmode][nebin])*f1[nmode][nebin]/(f1[nmode][nebin]-f2[nmode][nebin])/(f1[nmode][nebin]-f2[nmode][nebin]))/pol;//verse f2[nmode][nebin]
	ferrbb1[nmode][nebin]=((asyb12[nmode][nebin]-asyb23[nmode][nebin])*f2[nmode][nebin]/(f1[nmode][nebin]-f2[nmode][nebin])/(f1[nmode][nebin]-f2[nmode][nebin]))/pol;
	ferrbb2[nmode][nebin]=((asyb12[nmode][nebin]-asyb23[nmode][nebin])*f1[nmode][nebin]/(f1[nmode][nebin]-f2[nmode][nebin])/(f1[nmode][nebin]-f2[nmode][nebin]))/pol;
	
	asyerrbs1[nmode][nebin]=sqrt(pow(ferrbs1[nmode][nebin]*f1E[nmode][nebin],2)+pow(ferrbs2[nmode][nebin]*f2E[nmode][nebin],2));
	asyerrbb1[nmode][nebin]=sqrt(pow(ferrbb1[nmode][nebin]*f1E[nmode][nebin],2)+pow(ferrbb2[nmode][nebin]*f2E[nmode][nebin],2));
	asyerrys1[nmode][nebin]=sqrt(pow(ferrys1[nmode][nebin]*f1E[nmode][nebin],2)+pow(ferrys2[nmode][nebin]*f2E[nmode][nebin],2));
	asyerryb1[nmode][nebin]=sqrt(pow(ferryb1[nmode][nebin]*f1E[nmode][nebin],2)+pow(ferryb2[nmode][nebin]*f2E[nmode][nebin],2));
	
//	cout<<"f3="<<f3<<" f4="<<f4<<" bberr="<<asyerrbb[nmode][nebin]<<" bserr="<<asyerrbs[nmode][nebin]<<" bb="<<asybb[nmode][nebin]<<" bs="<<asybs[nmode][nebin]<<" yberr="<<asyerryb[nmode][nebin]<<"ybserr="<<asyerrys[nmode][nebin]<<" yb="<<asyyb[nmode][nebin]<<" ys="<<asyys[nmode][nebin]<<"  systBS="<< asyerrbs1[nmode][nebin]<<"  "<< asyerrbb1[nmode][nebin]<<"  "<< asyerrys1[nmode][nebin]<<"  "<< asyerryb1[nmode][nebin]<<endl;
//	cout<<asyerrbs1[nmode][nebin]<<" "<<asyerrbb1[nmode][nebin]<<" "<<asyerrys1[nmode][nebin]<<" "<<asyerryb1[nmode][nebin]<<" " <<endl;

	if (nmode==0) cout<<nebin<<" "<<xf[nmode][nebin] <<" "<< Ptmean11Iso0[nebin]<<" "<<     asybs[nmode][nebin]<<" "<<asyerrbs[nmode][nebin]<<" "<<asyerrbs1[nmode][nebin]  <<endl;
	if (nmode==1) cout<<nebin<<" "<<xf[nmode][nebin] <<" "<< Ptmean11Iso1[nebin]<<" "<<     asybs[nmode][nebin]<<" "<<asyerrbs[nmode][nebin]<<" "<<asyerrbs1[nmode][nebin]  <<endl;

	}
}

	double asybsAll[nebins];
	double asybserrAll[nebins];
	for (int nebin=0; nebin<nebins; nebin++){
	average( asybs[0][nebin], asybs[1][nebin], asyerrbs[0][nebin], asyerrbs[1][nebin],asybsAll[nebin],asybserrAll[nebin]);
	}

	TGraphErrors *gasybs[3];
	TGraphErrors *gasybb[3];
	TGraphErrors *gasybberr[3];
	TGraphErrors *gasybserr[3];
	TGraphErrors *gasyys[3];
	TGraphErrors *gasyyb[3];
	TGraphErrors *gasyyberr[3];
	TGraphErrors *gasyyserr[3];

	TH2F *bkg = new TH2F("bkg","A_{N} for Inclusive #pi^{0} ",20,0.15,0.35,10,-0.04,0.12);
	        bkg->GetXaxis()->SetTitle("x_{F}");
	        bkg->GetYaxis()->SetTitle("A_{N}");
	        bkg->GetXaxis()->CenterTitle(true);;
	        bkg->GetYaxis()->CenterTitle(true);;
	        bkg->GetYaxis()->SetTitleSize(0.04);;
	TH2F *bkg2 = new TH2F("bkg2","A_{N} for Inclusive #pi^{0} ",20,-0.35,-0.15,10,-0.04,0.12);
	        bkg2->GetXaxis()->SetTitle("x_{F}");
	        bkg2->GetYaxis()->SetTitle("A_{N}");
	        bkg2->GetXaxis()->CenterTitle(true);;
	        bkg2->GetYaxis()->CenterTitle(true);;
	        bkg2->GetYaxis()->SetTitleSize(0.04);;

	TLegend *leg;
	TLegend *leg2;
	 TLatex l;
	 TLatex l2;

	
		c2->cd(1);
	        bkg->Draw();
	for (int i=0 ; i<nmodes ; i++) {
	gasybs[i]=new TGraphErrors(nebins,xf[i], asybs[i],ex1[i],asyerrbs[i]);//only useful
	gasybb[i]=new TGraphErrors(nebins,xf[i], asybb[i],ex0[i],asyerrbb[i]);
	gasybberr[i]=new TGraphErrors(nebins,xf[i],asybb[i],ex0[i],asyerrbb1[i]);//x uncertainty
	gasybserr[i]=new TGraphErrors(nebins,xf[i],asybs[i],ex1[i],asyerrbs1[i]);
	
	gasyys[i]=new TGraphErrors(nebins,xfm[i], asyys[i],ex0[i],asyerrys[i]);//only useful
	gasyyb[i]=new TGraphErrors(nebins,xfm[i], asyyb[i],ex0[i],asyerryb[i]);
	gasyyserr[i]=new TGraphErrors(nebins,xfm[i], asyys[i],ex0[i],asyerrys1[i]);
	gasyyberr[i]=new TGraphErrors(nebins,xfm[i], asybb[i],ex0[i],asyerryb1[i]);
	}
	for (int i=0 ; i<nmodes ; i++) {
	gasybs[i]->SetMarkerStyle(24-i*4);
	gasybs[i]->SetMarkerSize(1.3);
	gasybs[i]->SetMarkerColor(kBlue);
	gasybs[i]->SetLineWidth(2);
	gasybs[i]->SetLineColor(kBlue);
	gasybs[i]->Draw("psame");
	gasybs[i]->GetXaxis()->SetTitle("PiE/Gev");
	gasybs[i]->GetYaxis()->SetTitle("A_{N} xf>0");
	
	gasybserr[i]->SetMarkerStyle(24-i*4);
	gasybserr[i]->SetMarkerSize(1.3);
	gasybserr[i]->SetMarkerColor(kBlue);
	gasybserr[i]->SetLineWidth(2);
	gasybserr[i]->SetLineColor(kBlue);
if(syst)	gasybserr[i]->Draw("p2");
	gasybserr[i]->GetXaxis()->SetTitle("PiE/Gev");
	gasybserr[i]->GetYaxis()->SetTitle("A_{N} xf>0");
	gasybserr[i]->SetFillColor(kBlack);
	gasybserr[i]->SetFillStyle(3002);
	
	gasybb[i]->SetMarkerStyle(24-i*4);
	gasybb[i]->SetMarkerSize(1.3);
	gasybb[i]->SetMarkerColor(kGreen+3);
	gasybb[i]->SetLineWidth(2);
	gasybb[i]->SetLineColor(kGreen+3);
 	gasybb[i]->Draw("p");
	gasybb[i]->GetXaxis()->SetTitle("PiE/Gev");
	gasybb[i]->GetYaxis()->SetTitle("A_{N} bkg");
	
	gasybberr[i]->SetMarkerStyle(24-i*4);
	gasybberr[i]->SetMarkerSize(1.3);
	gasybberr[i]->SetMarkerColor(kGreen+3);
	gasybberr[i]->SetLineWidth(2);
	gasybberr[i]->SetLineColor(kGreen+3);
 if(syst)	gasybberr[i]->Draw("p2");
	gasybberr[i]->GetXaxis()->SetTitle("PiE/Gev");
	gasybberr[i]->GetYaxis()->SetTitle("A_{N} bkg");
	gasybberr[i]->SetFillColor(kBlack);
	gasybberr[i]->SetFillStyle(3002);
	
	}
	leg=new TLegend(0.50,0.70,0.89,0.85);
	                leg->SetMargin(0.2);
	                leg->SetBorderSize(0);
	                leg->SetFillColor(0);
	                leg->SetTextSize(0.04);
	                leg->AddEntry(gasybs[0],"Non-isolated #pi^{0} x_{F}>0","PE");
	                leg->AddEntry(gasybb[0],"Non-isolated #pi^{0} background","PE");
	                leg->AddEntry(gasybs[1],"Isolated #pi^{0} x_{F}>0","PE");
	                leg->AddEntry(gasybb[1],"Isolated #pi^{0} background","PE");
	leg->Draw();
	
	    l.SetTextSize(0.03);
	    l2.SetTextSize(0.04);
		l.SetTextAngle(0.);
		l.DrawLatex(0.16,0.0+0.06,"3.4% beam pol. scale uncertainty not shown");
		double dx=0.16; double dy=0.042+0.06;
		       l2.DrawLatex(dx,dy-0.000,"p^{#uparrow} + p -> #pi^{0} + X @ #sqrt{s}=500 GeV");
		       l2.DrawLatex(dx,dy-0.008,"  p_{T} > 2 GeV");
		    	l2.DrawLatex(dx,dy-0.016," 2.7 < #eta < 4.0");
	
		c2->cd(2);
	        bkg2->Draw();
	
	for (int i=0 ; i<nmodes ; i++) {
	gasyys[i]->SetMarkerStyle(24-i*4);
	gasyys[i]->SetMarkerSize(1.3);
	gasyys[i]->SetMarkerColor(kMagenta);
	gasyys[i]->SetLineWidth(2);
	gasyys[i]->SetLineColor(kMagenta);
	gasyys[i]->Draw("psame");
	gasyys[i]->GetXaxis()->SetTitle("PiE/Gev");
	gasyys[i]->GetYaxis()->SetTitle("A_{N} xf>0");
	
	gasyyserr[i]->SetMarkerStyle(24-i*4);
	gasyyserr[i]->SetMarkerSize(1.3);
	gasyyserr[i]->SetMarkerColor(kMagenta);
	gasyyserr[i]->SetLineWidth(2);
	gasyyserr[i]->SetLineColor(kMagenta);
if(syst)	gasyyserr[i]->Draw("p2");
	gasyyserr[i]->GetXaxis()->SetTitle("PiE/Gev");
	gasyyserr[i]->GetYaxis()->SetTitle("A_{N} xf>0");
	gasyyserr[i]->SetFillColor(kBlack);
	gasyyserr[i]->SetFillStyle(3002);
	
	gasyyb[i]->SetMarkerStyle(24-i*4);
	gasyyb[i]->SetMarkerSize(1.3);
	gasyyb[i]->SetMarkerColor(kGreen+3);
	gasyyb[i]->SetLineWidth(2);
	gasyyb[i]->SetLineColor(kGreen+3);
 	gasyyb[i]->Draw("p");
	gasyyb[i]->GetXaxis()->SetTitle("PiE/Gev");
	gasyyb[i]->GetYaxis()->SetTitle("A_{N} bkg");
	
	gasyyberr[i]->SetMarkerStyle(24-i*4);
	gasyyberr[i]->SetMarkerSize(1.3);
	gasyyberr[i]->SetMarkerColor(kGreen+3);
	gasyyberr[i]->SetLineWidth(2);
	gasyyberr[i]->SetLineColor(kGreen+3);
 if(syst)	gasyyberr[i]->Draw("p2");
	gasyyberr[i]->GetXaxis()->SetTitle("PiE/Gev");
	gasyyberr[i]->GetYaxis()->SetTitle("A_{N} bkg");
	gasyyberr[i]->SetFillColor(kBlack);
	gasyyberr[i]->SetFillStyle(3002);
	}
	leg2=new TLegend(0.5,0.70,0.89,0.85);
	                leg2->SetMargin(0.2);
	                leg2->SetBorderSize(0);
	                leg2->SetFillColor(0);
	                leg2->SetTextSize(0.04);
					leg2->AddEntry(gasyys[0],"Non-isolated #pi^{0} x_{F}<0","PE");
	                leg2->AddEntry(gasyys[1],"Isolated #pi^{0} x_{F}<0","PE");
					leg2->AddEntry(gasyyb[0],"Non-isolated #pi^{0} background","PE");
	                leg2->AddEntry(gasyyb[1],"Isolated #pi^{0} background","PE");

	leg2->Draw();
	l.DrawLatex(-0.34,0.06,"3.4% beam pol. scale uncertainty not shown");
	
	char pname[100];
//	sprintf(pname,"DrawIsoAn11.png",i);
//	c2->Print(pname);
//	c2->SaveAs("digitRun11Iso.C");
	
	gasybs[2]=new TGraphErrors(nebins,xf[0], asybsAll,ex0[0],asybserrAll);

	gjetAn11Iso0 =  (TGraphErrors*)gasybs[0]->Clone();
    gjetAn11Iso0Err =  (TGraphErrors*)gasybserr[0]->Clone();
	gjetAn11Iso1 =  (TGraphErrors*)gasybs[1]->Clone();
    gjetAn11Iso1Err =  (TGraphErrors*)gasybserr[1]->Clone();
	gjetAn11 =  (TGraphErrors*)gasybs[2]->Clone();
	
	
	//gasyb01->Write();
	//gasyb12m0->Write();
	//gasyb23m0->Write();
	//gasyy01->Write();
	//gasyy12[i]->Write();
	//gasyy23[i]->Write();
/*	gasybs[i]->Write();
	gasybb[i]->Write();
	gasyys[i]->Write();
	gasyyb[i]->Write();
	fout->Write();

*/
	//mode

}


void average(double asy1, double asy2, double err1, double err2,double & asyFinal,double & asyerrFinal){
asyFinal= (asy1/err1/err1+asy2/err2/err2)/(1/err1/err1+1/err2/err2);
asyerrFinal=1/TMath::Sqrt(1/err1/err1+1/err2/err2);
}
void average(double asy1, double asy2,double asy3, double err1, double err2,double err3, double & asyFinal,double & asyerrFinal){
asyFinal= (asy1/err1/err1+asy2/err2/err2+asy3/err3/err3)/(1/err1/err1+1/err2/err2+1/err3/err3);
asyerrFinal=1/TMath::Sqrt(1/err1/err1+1/err2/err2+1/err3/err3);
}
void average(double asy1, double asy2,double asy3,double asy4, double err1, double err2,double err3,double err4, double & asyFinal,double & asyerrFinal){
asyFinal= (asy1/err1/err1+asy2/err2/err2+asy3/err3/err3+asy4/err4/err4)/(1/err1/err1+1/err2/err2+1/err3/err3+1/err4/err4 );
asyerrFinal=1/TMath::Sqrt(1/err1/err1+1/err2/err2+1/err3/err3+1/err4/err4);
}
void average(double asy1, double asy2,double asy3,double asy4, double asy5, double err1, double err2,double err3,double err4, double err5,double & asyFinal,double & asyerrFinal){
asyFinal= (asy1/err1/err1+asy2/err2/err2+asy3/err3/err3+asy4/err4/err4+asy5/err5/err5)/(1/err1/err1+1/err2/err2+1/err3/err3+1/err4/err4+1/err5/err5 );
asyerrFinal=1/TMath::Sqrt(1/err1/err1+1/err2/err2+1/err3/err3+1/err4/err4+1/err5/err5);
}
