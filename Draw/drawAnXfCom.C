TGraphErrors *gjetAn15 ;
TGraphErrors *gjetAn11 ;
TGraphErrors *gjetAn15Err ;
TGraphErrors *gjetAn11Err ;

double Rsyst = 0.0;
double xf15[9]={20.6614 , 25.4635 , 30.2489 , 35.273 , 40.3067 , 45.3355 , 50.3471 , 55.291 , 61.0336 };
double Ptmean15[9]={2.29382 , 2.7605 , 3.00705 , 3.02115 , 2.86867 , 2.78794 , 2.80169 , 2.89822 , 3.14834 };
double xf11[7]={  40.5369 , 45.5033 , 50.4883 , 55.4385 , 61.2923 , 69.4353 , 80.9808 };
double Ptmean11[7]={3.25302 , 3.41935 , 3.53451 , 3.63569 , 3.77359 , 3.97395 , 4.40979 };



//double Syst11[7]= {0.9 ,0.9 ,0.2 ,0.4 ,1.2 ,1.3 ,70 };
double Syst11[7]= {0.9 ,0.9 ,0.2 ,0.4 ,1.2 ,1.3 ,0.7 };
//double Syst15[9]= {0.3 	,0.1 	,0.1 	,0.7 	,0.7 	,1.1 	,1.0 	,1.6 	,140 };
double Syst15[9]= {0.3 	,0.1 	,0.1 	,0.7 	,0.7 	,1.1 	,1.0 	,1.6 	,1.4 };


bool syst = true;
bool drawall = 0;
drawAnXfCom(int history = 1){
	
	
drawAn15( );
drawAn11( );

    TCanvas *c = new TCanvas("roses", "roses", 1000, 1000);
    c->Divide(1,2,0.,.0001);
    double x1[2]={4,5};
    double y1[2]={7,5};
        TH2F *h1 = new TH2F("bkgComAN","  ",20,0.14,0.66,10,-0.03,0.25);
        TH2F *h2 = new TH2F("bkgComPt","  ",20,0.14,0.66,10,  1.5 , 5.3);
        //h1->GetYaxis()->SetNdivisions(504);
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

double Ptxf11[7];
double Ptxf15[9];
	for (int nebin=0; nebin<7; nebin++){
	Ptxf11[nebin]= xf11[nebin]/250;
	//ex0[nebin]= Rsyst*xf[nebin];
	}
	for (int nebin=0; nebin<9; nebin++){
	Ptxf15[nebin]= xf15[nebin]/100;
	//ex0[nebin]= Rsyst*xf[nebin];
	}
      TGraph *pt11=new TGraph(7,Ptxf11,Ptmean11);
      TGraph *pt15=new TGraph(9,Ptxf15,Ptmean15);

	pt11->SetMarkerColor(kBlue);
	pt15->SetMarkerColor(kRed);
	pt11->SetLineColor(kBlue);
	pt15->SetLineColor(kRed);
	pt11->SetMarkerStyle(22);
	pt15->SetMarkerStyle(20);
	pt11->SetMarkerSize(1.6);
	pt15->SetMarkerSize(1.5);
   c->cd(1);
	gjetAn15->SetMarkerSize(1.5);
	gjetAn11->SetMarkerSize(1.6);
	gjetAn11->SetMarkerStyle(22);
	gjetAn15->SetMarkerStyle(20);
	gjetAn15->SetMarkerColor(kRed);
	gjetAn15->SetLineColor(kRed);
	gjetAn11->SetMarkerColor(kBlue);
	gjetAn11->SetMarkerColor(kBlue);
	gjetAn15Err->SetMarkerSize(1.5);
	gjetAn15Err->SetMarkerStyle(20);
	gjetAn15Err->SetMarkerColor(kRed);
	gjetAn15Err->SetLineColor(kRed);
	gjetAn15Err->SetFillStyle(3001);
	gjetAn11Err->SetMarkerSize(1.6);
	gjetAn11Err->SetMarkerStyle(22);
	gjetAn11Err->SetLineColor(kBlue);
	gjetAn11Err->SetLineColor(kBlue);
	gjetAn11Err->SetFillStyle(3001);
	gjetAn15->Draw("psame");
	gjetAn11->Draw("psame");
if(syst)    gjetAn11Err->Draw("[]same");
if(syst)	gjetAn15Err->Draw("[]same");

	 TLatex l;
	 TLatex l2;
    	l.SetTextSize(0.06);
	    double dx=0.16; double dy=0.24;
	    l2.SetTextSize(0.06);
           l2.DrawLatex(dx,dy-0.01,"STAR   p^{#uparrow} + p -> #pi^{0} + X");  // @ #sqrt{s}=200/500 GeV");
	    l2.SetTextSize(0.06);
	    l.SetTextAngle(0.);
	    l.DrawLatex(0.16,dy-0.13,"3.0/3.4% beam pol. scale uncertainty not shown");
	    l2.SetTextSize(0.06);
           l2.DrawLatex(dx,dy-0.05,"p_{T} > 2 GeV/c");
           l2.DrawLatex(dx,dy-0.09,"2.7 < #eta < 4.0");

	TLegend *leg3=new TLegend(0.60,0.80,0.88,0.97);
                leg3->SetMargin(0.5);
                leg3->SetBorderSize(0);
                leg3->SetFillColor(0);
                leg3->SetTextSize(0.07);
                leg3->AddEntry(gjetAn15,"200 GeV","PE");
                leg3->AddEntry(gjetAn11,"500 GeV","PE");
	leg3->Draw();
	c->cd(2);
		pt11->Draw("psame");
		pt15->Draw("psame");

	if (drawall)c->SaveAs("DrawAnComPt.png");
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
	TLegend *leg4=new TLegend(0.65,0.62,0.88,0.78);
                leg4->SetMargin(0.4);
                leg4->SetBorderSize(0);
                leg4->SetFillColor(0);
                leg4->SetTextSize(0.07);
                leg4->AddEntry(gth1_200,"Theory 200 GeV","f");
                leg4->AddEntry(gth1_500,"Theory 500 GeV","f");
	leg4->Draw();
	c->SaveAs("DrawAnComPtT.png");

//no pt
TCanvas *c11 = new TCanvas("c11", "c11",0,0,800,600);
	c11->cd();
TH2F *bkg = new TH2F("bkgCom"," A_{N} for Inclusive #pi^{0} ",20,0.14,0.66,10,-0.02,0.2);
        bkg->GetXaxis()->SetTitle("x_{F}");
        bkg->GetYaxis()->SetTitle("A_{N}");
        bkg->GetXaxis()->CenterTitle(true);;
        bkg->GetYaxis()->CenterTitle(true);;
        bkg->GetYaxis()->SetTitleSize(0.04);;
        bkg->GetXaxis()->SetTitleSize(0.04);;
        bkg->Draw();

gjetAn15->SetMarkerColor(kRed);
gjetAn15->SetLineColor(kRed);
gjetAn15Err->SetMarkerColor(kRed);
gjetAn15Err->SetLineColor(kRed);
gjetAn15->Draw("psame");
if(syst) gjetAn15Err->Draw("psame");
gjetAn11->SetMarkerColor(kBlue);
gjetAn11->SetMarkerColor(kBlue);
gjetAn11Err->SetLineColor(kBlue);
gjetAn11Err->SetLineColor(kBlue);
gjetAn11->Draw("psame");
if(syst) gjetAn11Err->Draw("psame");

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
    l.DrawLatex(0.16,0.12,"3.0/3.4% beam pol. scale uncertainty not shown");
    double dx=0.16; double dy=0.18;
           l2.DrawLatex(dx,dy-0.00,"STAR p^{#uparrow} + p -> #pi^{0} + X");// @ #sqrt{s}=200/500 GeV");
           l2.DrawLatex(dx,dy-0.02,"p_{T} > 2 GeV/c");
           l2.DrawLatex(dx,dy-0.04,"2.7 < #eta < 4.0");


if (drawall) c11->SaveAs("DrawAnCom.png");
	
	
//HISTORY	
	
TCanvas *c22 = new TCanvas("c22", "c22",0,0,800,600);
TH2F *bkghis = new TH2F("bkghis"," A_{N} for Inclusive #pi^{0} ",20,0.,0.75,10,-0.04,0.25);
    //    bkghis->GetXaxis()->SetTitle("x_{F}");
    //    bkghis->GetYaxis()->SetTitle("A_{N}");
        bkghis->GetXaxis()->CenterTitle(true);;
        bkghis->GetYaxis()->CenterTitle(true);;
        bkghis->GetYaxis()->SetTitleSize(0.04);;
        bkghis->GetXaxis()->SetTitleSize(0.04);;
                  bkghis->GetYaxis()->SetLabelSize(0.06);
                  bkghis->GetXaxis()->SetLabelSize(0.06);

        bkghis->Draw();
   latex.SetTextSize(0.045);
   latex.DrawLatexNDC(.02,.92,"A_{N}");
   latex.DrawLatexNDC(.5,0.05,"x_{F}");
//phenix 62
   gre1 = new TGraphErrors(4);
   gre1->SetName("Graph5");

   gre1->SetLineWidth(2);
   gre1->SetLineColor(kOrange+7);//drak green
   gre1->SetMarkerColor(kOrange+7);
   gre1->SetMarkerStyle(26);//open triangle
   gre1->SetMarkerSize(1.6);

  gre1->SetPoint(0,0.25,0.0193);
   gre1->SetPointError(0,0.0,0.0065);
  gre1->SetPoint(1,0.35,0.0469);
   gre1->SetPointError(1,0.0,0.0067);
  gre1->SetPoint(2,0.44,0.0605);
   gre1->SetPointError(2,0.0,0.0099);
  gre1->SetPoint(3,0.56,0.0817);
   gre1->SetPointError(3,0.0,0.0182);

if(history==1)   gre1->Draw("p");


//E704	
   gre2 = new TGraphErrors(7);
   gre2->SetName("Graph2");

   gre2->SetLineColor(kGreen+2);
   gre2->SetLineWidth(2);
   gre2->SetMarkerColor(kGreen+2);
   gre2->SetMarkerStyle(25);//
   gre2->SetMarkerSize(1.5);

  gre2->SetPoint(0,0.03,-0.001);
   gre2->SetPointError(0,0.0,0.012);
  gre2->SetPoint(1,0.13,0.008);
   gre2->SetPointError(1,0.0,0.008);
  gre2->SetPoint(2,0.23,0.007);
   gre2->SetPointError(2,0.0,0.01);
  gre2->SetPoint(3,0.33,0.041);
   gre2->SetPointError(3,0.0,0.011);
  gre2->SetPoint(4,0.43,0.061);
   gre2->SetPointError(4,0.0,0.012);
  gre2->SetPoint(5,0.53,0.121);
   gre2->SetPointError(5,0.0,0.017);
  gre2->SetPoint(6,0.67,0.151);
   gre2->SetPointError(6,0.0,0.027);

if(history==1)   gre2->Draw("p");
//2008STAR
   gre3 = new TGraphErrors(7);
   gre3->SetName("Graph3");

   gre3->SetLineColor(6);
   gre3->SetLineWidth(2);
   gre3->SetMarkerColor(6);
   gre3->SetMarkerStyle(24);//open circle
   gre3->SetMarkerSize(1.5);
/*
  gre3->SetPoint(0,0.237,0.0057);
   gre3->SetPointError(0,0.0,0.0058);
  gre3->SetPoint(1,0.283,0.0019);
   gre3->SetPointError(1,0.0,0.0012);
  gre3->SetPoint(2,0.322,0.0091);
   gre3->SetPointError(2,0.0,0.0009);
  gre3->SetPoint(3,0.371,0.023);
   gre3->SetPointError(3,0.0,0.0014);
  gre3->SetPoint(4,0.427,0.038);
   gre3->SetPointError(4,0.0,0.0022);
  gre3->SetPoint(5,0.501,0.069);
   gre3->SetPointError(5,0.0,0.0048);
  gre3->SetPoint(6,0.598,0.10);
   gre3->SetPointError(6,0.0,0.0137);
  */ 
  gre3->SetPoint(0,0.237,0.0057);
   gre3->SetPointError(0,0.0,0.0085);
  gre3->SetPoint(1,0.283,0.0019);
   gre3->SetPointError(1,0.0,0.0012);
  gre3->SetPoint(2,0.322,0.0091);
   gre3->SetPointError(2,0.0,0.0010);
  gre3->SetPoint(3,0.371,0.023);
   gre3->SetPointError(3,0.0,0.0015);
  gre3->SetPoint(4,0.427,0.038);
   gre3->SetPointError(4,0.0,0.0024);
  gre3->SetPoint(5,0.501,0.069);
   gre3->SetPointError(5,0.0,0.0048);
  gre3->SetPoint(6,0.598,0.10);
   gre3->SetPointError(6,0.0,0.0146);
if(history==1)   gre3->Draw("p");
//2008STAR_2 ///3.3
   gre4 = new TGraphErrors(7);
   gre4->SetName("Graph4");

   gre4->SetLineColor(kBlack);
   gre4->SetLineWidth(2);
   gre4->SetMarkerColor(kBlack);
   gre4->SetMarkerStyle(24);//open square
   gre4->SetMarkerSize(1.5);
/*
  gre4->SetPoint(0,0.201,0.00087);
   gre4->SetPointError(0,0.0,0.0013);
  gre4->SetPoint(1,0.234,0.0021);
   gre4->SetPointError(1,0.0,0.0018);
  gre4->SetPoint(2,0.27,0.010);
   gre4->SetPointError(2,0.0,0.0017);
  gre4->SetPoint(3,0.32,0.027);
   gre4->SetPointError(3,0.0,0.0031);
  gre4->SetPoint(4,0.37,0.039);
   gre4->SetPointError(4,0.0,0.0058);
  gre4->SetPoint(5,0.42,0.053);
   gre4->SetPointError(5,0.0,0.010);
  gre4->SetPoint(6,0.499,0.0599);
   gre4->SetPointError(6,0.0,0.026);
*/
  gre4->SetPoint(0,0.201,0.00087);
   gre4->SetPointError(0,0.0,0.0023);
  gre4->SetPoint(1,0.234,0.0021);
   gre4->SetPointError(1,0.0,0.0017);
  gre4->SetPoint(2,0.27,0.010);
   gre4->SetPointError(2,0.0,0.0019);
  gre4->SetPoint(3,0.32,0.027);
   gre4->SetPointError(3,0.0,0.0033);
  gre4->SetPoint(4,0.37,0.039);
   gre4->SetPointError(4,0.0,0.0061);
  gre4->SetPoint(5,0.42,0.053);
   gre4->SetPointError(5,0.0,0.010);
  gre4->SetPoint(6,0.499,0.0599);
   gre4->SetPointError(6,0.0,0.027);
if(history==1)   gre4->Draw("p");

 
 
 
 
 
  
  
  
   gre5 = new TGraphErrors(8);
   gre5->SetName("Graph6");

   gre5->SetLineColor(28);
   gre5->SetLineWidth(2);
   gre5->SetMarkerColor(28);
   gre5->SetMarkerStyle(32);//reverse triangle
   gre5->SetMarkerSize(1.5);

  gre5->SetPoint(0,0.31, 0.0331 );
  gre5->SetPoint(1,0.39, 0.0318 );
  gre5->SetPoint(2,0.41, 0.0777 );
  gre5->SetPoint(3,0.50, 0.0637 );
  gre5->SetPoint(4,0.52, 0.0654 );
  gre5->SetPoint(5,0.66, 0.0773 );
  gre5->SetPoint(6,0.68, 0.0801 );
  gre5->SetPoint(7,0.70, 0.1237 );
  gre5->SetPoint(8,0.54, 0.0811 ); 
   gre5->SetPointError(0,0.0,0.0186);
   gre5->SetPointError(1,0.0,0.0069);
   gre5->SetPointError(2,0.0,0.0189);
   gre5->SetPointError(3,0.0,0.0053);
   gre5->SetPointError(4,0.0,0.0076);
   gre5->SetPointError(5,0.0,0.0087);
   gre5->SetPointError(6,0.0,0.0068);
   gre5->SetPointError(7,0.0,0.0134);
   gre5->SetPointError(8,0.0,0.0342);
if(history==1)   gre5->Draw("p");
//New	
gjetAn15->SetMarkerColor(kRed);
gjetAn15->SetLineColor(kRed);
		gjetAn11->SetMarkerColor(kBlue);
		gjetAn11->SetLineColor(kBlue);

gjetAn15->SetMarkerSize(1.5);
gjetAn15->SetMarkerStyle(20);//solid square
gjetAn11->SetMarkerSize(1.6);
gjetAn11->SetMarkerStyle(22);//solid circle



gjetAn15->Draw("psame");
gjetAn11->Draw("psame");


   TLegend *leg = new TLegend(0.13,0.5,0.6,0.88,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.036);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
	                leg->AddEntry(gjetAn11,"STAR 500 GeV,2.7<#eta<4.0 This Paper","PE");
	                leg->AddEntry(gjetAn15,"STAR 200 GeV,2.7<#eta<4.0 This Paper","PE");

//   TLegendEntry *entry=leg->AddEntry("Graph0","STAR 200GeV,2.8<#eta<4.0","PE");
//                 entry=leg->AddEntry("Graph1","STAR 500GeV,2.8<#eta<4.0","PE");
   TLegendEntry *     entry=leg->AddEntry("Graph3","STAR 200 GeV, <#eta>=3.7","PE");
                      entry=leg->AddEntry("Graph4","STAR 200 GeV, <#eta>=3.3","PE");
                      entry=leg->AddEntry("Graph6","RHICf 510 GeV, #eta>6","PE");
                      entry=leg->AddEntry("Graph5","PHENIX 62.4 GeV,3.1 <#eta<3.8","PE");
   			          entry=leg->AddEntry("Graph2","E704 19.4 GeV","PE");

	leg->Draw();
  TLine *line = new TLine(0.,0,0.75,0);
  line->SetLineColor(kBlack);
  line->SetLineStyle(7);
//  line->Draw();

	cout<<"  cp"<<endl;

if (drawall) c22->SaveAs("ExpALL.png");

double grePt1[4]={0.52,0.71,0.86,1.01};
double grexf1[4]={0.25,0.35,0.44,0.56};
double grexf2[7]={0.03,0.13,0.23,0.33,0.43,0.53,0.67};
double grePt2[7]={0.7,0.7,0.8,0.8,0.9,1.0,1.1};
double grePt3[7]={1.19,1.34,1.53,1.79,2.04,2.36,2.78};
double grexf3[7]={0.237,0.283,0.322,0.371,0.427,0.501,0.598};
double grePt4[7]={1.56,	1.78,	2.03,	2.39,	2.74,	3.14,	3.66};
double grexf4[7]={0.201,0.234,0.27,0.32,0.37,0.425,0.499};
double grexf5[9]={0.31,0.39,0.41,0.50,0.52,0.54,0.66,0.68,0.70};
double grePt5[9]={0.21,0.23,0.33,0.23,0.34,0.53,0.24,0.37,0.5};

//rhicf
/*
0.31 0.21 0.0331 0.0186
0.39 0.23 0.0318 0.0069
0.41 0.33 0.0777 0.0189
0.50 0.23 0.0637 0.0053
0.52 0.34 0.0654 0.0076
0.66 0.24 0.0773 0.0087 
0.68 0.37 0.0801 0.0068 
0.70 0.55 0.1237 0.0134 
//0.54 0.53 0.0811 0.0342
//0.79 0.77 0.2067 0.0321
*/

	  TGraph *ptgre1=new TGraph(4,grexf1,grePt1);
	  TGraph *ptgre2=new TGraph(7,grexf2,grePt2);
	  TGraph *ptgre3=new TGraph(7,grexf3,grePt3);
	  TGraph *ptgre4=new TGraph(7,grexf4,grePt4);
	  TGraph *ptgre5=new TGraph(9,grexf5,grePt5);

   ptgre1->SetLineColor(kOrange+7);//drak green
   ptgre1->SetMarkerColor(kOrange+7);
   ptgre1->SetMarkerStyle(26);//open triangle
   ptgre1->SetMarkerSize(1.6);
   ptgre2->SetLineColor(kGreen+2);
   ptgre2->SetMarkerColor(kGreen+2);
   ptgre2->SetMarkerStyle(25);//open square
   ptgre2->SetMarkerSize(1.5);
   ptgre3->SetLineColor(6);
   ptgre3->SetMarkerColor(6);
   ptgre3->SetMarkerStyle(24);//open circle
   ptgre3->SetMarkerSize(1.5);
   ptgre4->SetLineColor(kBlack);
   ptgre4->SetMarkerColor(kBlack);
   ptgre4->SetMarkerStyle(24);//open square
   ptgre4->SetMarkerSize(1.5);
   ptgre5->SetLineColor(28);
   ptgre5->SetMarkerColor(28);
   ptgre5->SetMarkerStyle(32);//e
   ptgre5->SetMarkerSize(1.5);
        TH2F *h22 = new TH2F("bkgComPt2","  ",20,0.,0.75,10,  0. , 5.3);
                  h22->GetYaxis()->SetLabelSize(0.06);
                  h22->GetXaxis()->SetLabelSize(0.06);

TCanvas *c23 = new TCanvas("c23", "c233",0,0,1000,1000);
    c23->Divide(1,2,0.,.0001);
   c23->cd(1);
        gPad->SetLeftMargin(0.12);
        gPad->SetRightMargin(0.01);
        gPad->SetBottomMargin(0.001);
        bkghis->Draw();
		gjetAn11->SetMarkerColor(kBlue);
		gjetAn11->SetLineColor(kBlue);
		gjetAn15->Draw("psame");
		gjetAn11->Draw("psame");
		gre1->Draw("psame");
		gre2->Draw("psame");
		gre3->Draw("psame");
		gre4->Draw("psame");
		gre5->Draw("psame");
    c23->cd(2);
        h22->Draw();
        h22->GetYaxis()->SetNdivisions(505);
        gPad->SetLeftMargin(0.12);
        gPad->SetRightMargin(0.01);
        gPad->SetBottomMargin(0.5);
		pt11->Draw("psame");
		pt15->Draw("psame");
		ptgre1->Draw("psame");
		ptgre2->Draw("psame");
		ptgre3->Draw("psame");
		ptgre4->Draw("psame");
		ptgre5->Draw("psame");
	c23->cd(0);
        TPad*  p= new TPad("p","p",0,0,1,1); p->Draw(); p->cd();
                p->SetFillStyle(0);
   latex.SetTextSize(0.035);
   latex.DrawLatexNDC(.02,.93,"A_{N}");
   latex.SetTextAngle(90);
   latex.DrawLatexNDC(.02,.29,"<p_{T}>/[GeV/c]");
//   latex.DrawLatexNDC(.02,.42,"[GeV/c]");
   latex.SetTextAngle(0);
   latex.DrawLatexNDC(.5,0.2,"x_{F}");

   TLegend *leg4 = new TLegend(0.13,0.70,0.6,0.95,NULL,"brNDC");
   leg4->SetBorderSize(0.);
   leg4->SetLineColor(1);
   leg4->SetLineStyle(1);
   leg4->SetLineWidth(1);
   leg4->SetFillColor(0);
   leg4->SetFillStyle(1001);
   leg4->AddEntry(gjetAn11,"STAR 500GeV,2.7<#eta<4.0 This Paper","PE");
   leg4->AddEntry(gjetAn15,"STAR 200GeV,2.7<#eta<4.0 This Paper","PE");
   leg4->AddEntry(gre3,"STAR 200GeV, <#eta>=3.7","PE");
   leg4->AddEntry(gre4,"STAR 200GeV, <#eta>=3.3","PE");
   leg4->AddEntry(gre5,"RHICf 510 GeV, #eta>6","PE");
   leg4->AddEntry(gre1,"PHENIX 62.4GeV,3.1 <#eta<3.8","PE");
   leg4->AddEntry(gre2,"E704 19.4GeV","PE");

   leg4->SetTextSize(0.025);
	leg4->Draw();
 c23->SaveAs("ExpALLPt.png");
	
}
drawAn15(){//backup
	
		gROOT->SetStyle("Modern");
//		 gStyle->SetOptTitle(kFALSE);
		gStyle->SetOptStat(0000);
        gStyle->SetOptFit(1111);//0000);
        gStyle->SetStatColor(0);
    //    gStyle->SetTitleFillColor(0);
    //    gStyle->SetFillColor(0);
    //    gStyle->SetTitleColor(1);
        gStyle->SetOptDate(0);
        gStyle->SetStatFont(42);
        gStyle->SetStatW(0.13);
        gStyle->SetStatH(0.13);
        gStyle->SetStatX(1.0);
        gStyle->SetStatY(1.0);
		gStyle->SetTitleXOffset(1.0); 
		gStyle->SetTitleYOffset(1.1); 
		gStyle->SetHistLineWidth(2);; 
	//	gStyle->SetTitleFont(72,"xyz");;	
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
	
	
	const int nebins = 9;
	double ebinlows[nebins] = {18, 23, 28, 33, 38, 43, 48, 53, 58 };//, 65};
	double ebinhighs[nebins] = { 23, 28, 33, 38, 43, 48, 53, 58, 65 };//, 75};
	const int nmbins = 2;
	double mbinlows[nmbins] = {0.00,  0.20};
	double mbinhighs[nmbins] = {0.20, 0.30};
	char resultname[200];
	char resultname2[200];
	char picname[200];
	char picname2[200];
	double ex[nebins]= {0,0,0,0,0,0,0};//x error 
	double ex1[nebins];//for syst
	double ex0[nebins]= {0.012,0.013,0.014,0.016,0.018,0.020,0.024};//true uncertainty in x axis
//	double xf[nebins]={20,25,30,35,40.44,45.43,50.41,55.36,61.19,69.35};
	double xf[nebins]={  20.6412 ,25.2581 ,30.157 ,35.2599 ,40.3358 ,45.3645 ,50.3435 ,55.2709 ,60.9697 };//,68.9371};// ,80.5924 ,100.48 }
	double xfm[nebins]={  20.6412 ,25.2581 ,30.157 ,35.2599 ,40.3358 ,45.3645 ,50.3435 ,55.2709 ,60.9697 };// ,68.9371};// ,80.5924 ,100.48 }
	double xf1[nebins];
	double xf2[nebins];
	for (int nebin=0; nebin<nebins; nebin++){
	//xf[nebin]= (ebinlows[nebin]+ebinhighs[nebin])/2.0/250; //    !!!!!!!!!!type change!!!!!!!!!!
	xf[nebin]= xf15[nebin]/100;
	xfm[nebin]= -xf15[nebin]/100;
	xf1[nebin]=( (ebinlows[nebin]+ebinhighs[nebin])/2-0.5)/100;
	xf2[nebin]=( (ebinlows[nebin]+ebinhighs[nebin])/2+0.5)/100;
	ex0[nebin]= Rsyst*xf[nebin];
	//out<< xf[nebin]<<" " << xf1[nebin]<<endl;
	ex1[nebin]=0.005;
	}
	ifstream result;
	ifstream result2;
	
	TF1 *fcn1 = new TF1 ("fcn1","pol0",0,60);
	TF1 *fcn2 = new TF1 ("fcn2","pol0",0,60);
	
	
//	TFile *fout= new TFile ("DrawAn15.root","recreate");
//	fout->cd();
	double asy_fill[nmbins][nebins];
	double asyerr_fill[nmbins][nebins];
	double asy_fill2[nmbins][nebins];
	double asyerr_fill2[nmbins][nebins];
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
			sprintf(resultname,"../Run15/result/AN2/AN_Fill%d_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
			sprintf(resultname2,"../Run15/result/AN2/ANy_Fill%d_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
			TString infile(resultname);
			TString infile2(resultname2);
	//		cout<<infile<<endl;
			result.open(resultname,ios::in);
			result2.open(resultname2,ios::in);
			asyerr2[nfill]=0;		
			asyerr[nfill]=0;		
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
			
			sprintf(picname,"./Otherpic/AN_AllFill_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.png",mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
			sprintf(picname2,"./Otherpic/ANy_AllFill_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.png",mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
			TGraphErrors *forfit=new TGraphErrors(fillbin,filldouble,asy,fillex,asyerr);
			TGraphErrors *forfit2=new TGraphErrors(fillbin,filldouble,asy2,fillex,asyerr2);
			forfit->Fit("fcn1","RQ");
			asy_fill[nmbin][nebin]=fcn1->GetParameter(0);
			asyerr_fill[nmbin][nebin]=fcn1->GetParError(0);
			forfit2->Fit("fcn2","RQ");
			asy_fill2[nmbin][nebin]=fcn2->GetParameter(0);
			asyerr_fill2[nmbin][nebin]=fcn2->GetParError(0);
		//		cout<<asy_fill[nmbin][nebin]<<" "<<asyerr_fill[nmbin][nebin]<<" "<<endl;
		 //TCanvas *c1 = new TCanvas("c1", "c1",0,0,1600,900);
		//   cout<<" m= "<<nmbin<<" e= "<<nebin<<" "<<asy_fill[nmbin][nebin]<<" "<<asyerr_fill[nmbin][nebin]<<" "<<endl;
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
	

	double asyb01[nebins];
	double asyb12[nebins];
	double asyb23[nebins];
	double asyerrb01[nebins];
	double asyerrb12[nebins];
	double asyerrb23[nebins];
	double asyy01[nebins];
	double asyy12[nebins];
	double asyy23[nebins];
	double asyerry01[nebins];
	double asyerry12[nebins];
	double asyerry23[nebins];
	for (int nebin=0; nebin<nebins; nebin++){
	//asyf[nebin]=sumasy[3][nebin];
	//asyerrf[nebin]=sumerr[3][nebin];
/*	average(asy_fill[2][nebin],asy_fill[3][nebin],asyerr_fill[2][nebin],asyerr_fill[3][nebin],asyb12[nebin],asyerrb12[nebin]);
	average(asy_fill[4][nebin],asy_fill[5][nebin],asy_fill[1][nebin],asyerr_fill[4][nebin],asyerr_fill[5][nebin],asyerr_fill[1][nebin],asyb23[nebin],asyerrb23[nebin]);
	average(asy_fill2[2][nebin],asy_fill2[3][nebin],asyerr_fill2[2][nebin],asyerr_fill2[3][nebin],asyy12[nebin],asyerry12[nebin]);
	average(asy_fill2[4][nebin],asy_fill2[5][nebin],asy_fill2[1][nebin],asyerr_fill2[4][nebin],asyerr_fill2[5][nebin],asyerr_fill2[1][nebin],asyy23[nebin],asyerry23[nebin]);
*/	
        asyb12[nebin]=asy_fill[0][nebin];
        asyb23[nebin]=asy_fill[1][nebin];
        asyerrb12[nebin]=asyerr_fill[0][nebin];
        asyerrb23[nebin]=asyerr_fill[1][nebin];
        asyy12[nebin]=asy_fill2[0][nebin];
        asyy23[nebin]=asy_fill2[1][nebin];
        asyerry12[nebin]=asyerr_fill2[0][nebin];
        asyerry23[nebin]=asyerr_fill2[1][nebin];



	}
	
	 /*TCanvas *c3 = new TCanvas("c3", "c3",0,0,1200,450);
		 c3->Divide(2,1);
		c3->cd(1);
	//TGraphErrors *gasyb01=new TGraphErrors(nebins,xf,asyb01,ex,asyerrb01);
	TGraphErrors *gasyb12=new TGraphErrors(nebins,xf,asyb12,ex,asyerrb12);
	TGraphErrors *gasyb23=new TGraphErrors(nebins,xf,asyb23,ex,asyerrb23);
	//TGraphErrors *gasyy01=new TGraphErrors(nebins,xf,asyy01,ex,asyerry01);
	TGraphErrors *gasyy12=new TGraphErrors(nebins,xf,asyy12,ex,asyerry12);
	TGraphErrors *gasyy23=new TGraphErrors(nebins,xf,asyy23,ex,asyerry23);
	gasyb12->Draw("ap*");
		c3->cd(2);
	gasyb23->Draw("ap*");
	//gasyb01->SetTitle("Signal m=0.0~0.1");
	gasyb12->SetTitle("Signal m=0.1~0.2");
	gasyb23->SetTitle("Signal m=0.2~0.3");
	//gasyb01->GetXaxis()->SetTitle("PiE/Gev");
	//gasyb01->GetYaxis()->SetTitle("A_{N}");
	gasyb12->GetXaxis()->SetTitle("x_f");
	gasyb12->GetYaxis()->SetTitle("A_{N}");
	gasyb23->GetXaxis()->SetTitle("x_f/Gev");
	gasyb23->GetYaxis()->SetTitle("A_{N}");
	//gasyy01->SetTitle("Signal m=0.0~0.1");
	gasyy12->SetTitle("Signal m=0.1~0.2");
	gasyy23->SetTitle("Signal m=0.2~0.3");
	//gasyy01->GetXaxis()->SetTitle("PiE/Gev");
	//gasyy01->GetYaxis()->SetTitle("A_{N}");
	gasyy12->GetXaxis()->SetTitle("x_f/Gev");
	gasyy12->GetYaxis()->SetTitle("A_{N}");
	gasyy23->GetXaxis()->SetTitle("x_f/Gev");
	gasyy23->GetYaxis()->SetTitle("A_{N}");
	//c1->Print("test.png");
	*/
	//double f1[nebins]={0.694,0.nebins12,0.728,0.732,0.741,0.757,0.792};
	//double f2[nebins]={0.nebins86,0.761,0.748,0.760,0.756,0.718,0.584};
	double asybs[nebins];
	double asyerrbs[nebins];
	double asyerrbs1[nebins]={0,0,0,0,0,0,0};
	double asyerrys1[nebins]={0,0,0,0,0,0,0};
	double asyys[nebins];
	double asyerrys[nebins];
	double asybb[nebins];
	double asyerrbb[nebins];
	double asyerrbb1[nebins]={0,0,0,0,0,0,0};
	double asyerryb1[nebins]={0,0,0,0,0,0,0};
	double asyyb[nebins];
	double asyerryb[nebins];
	double ferrbs1[nebins];
	double ferrbs2[nebins];
	double ferrys1[nebins];
	double ferrys2[nebins];
	double ferrbb1[nebins];
	double ferrbb2[nebins];
	double ferryb1[nebins];
	double ferryb2[nebins];
	
	
	double f1[nebins];//sig in sig
	double f2[nebins];//sig in bkg
	double f1E[nebins];//
	double f2E[nebins];//
	
	ifstream frac;
	frac.open("./txt/15/frac.txt",ios::in);
	for (int i=0 ; i<nebins ; i++){
	frac>>f1[i]>>f1E[i]>>f2[i]>>f2E[i];
	}
	
	double asyFinal;
	double asyerrFinal;
	for (int nebin=0; nebin<nebins; nebin++){
	
	double f3=(1-f1[nebin])/(1-f2[nebin]);
	double f4=f1[nebin]/f2[nebin];
	
	//12-signal region 23bkg region
	asybs[nebin]=(asyb12[nebin]-asyb23[nebin]*f3)/(1-f3)/pol;
	asyerrbs[nebin]=TMath::Sqrt(asyerrb12[nebin]*asyerrb12[nebin]+asyerrb23[nebin]*asyerrb23[nebin]*f3*f3)/TMath::Abs(1-f3)/pol;
	asyys[nebin]=(asyy12[nebin]-asyy23[nebin]*f3)/(1-f3)/polY;
	asyerrys[nebin]=TMath::Sqrt(asyerry12[nebin]*asyerry12[nebin]+asyerry23[nebin]*asyerry23[nebin]*f3*f3)/TMath::Abs(1-f3)/polY;
	asybb[nebin]=(asyb12[nebin]-asyb23[nebin]*f4)/(1-f4)/pol;
	asyerrbb[nebin]=TMath::Sqrt(asyerrb12[nebin]*asyerrb12[nebin]+asyerrb23[nebin]*asyerrb23[nebin]*f4*f4)/TMath::Abs(1-f4)/pol;
	asyyb[nebin]=(asyy12[nebin]-asyy23[nebin]*f4)/(1-f4)/polY;
	asyerryb[nebin]=TMath::Sqrt(asyerry12[nebin]*asyerry12[nebin]+asyerry23[nebin]*asyerry23[nebin]*f4*f4)/TMath::Abs(1-f4)/polY;
	
	//asyerrbs1[nebin]=sqrt(pow(asyerrbs[nebin],2)+pow(unpol*asybs[nebin]/pol/pol,2));//with unpol
	//asyerrbb1[nebin]=sqrt(pow(asyerrbb[nebin],2)+pow(unpol*asybb[nebin]/pol/pol,2));//with unpol
	//12 signal region 23 background region
	//uncertaintt of f1 f2
	//sig
	ferrys1[nebin]=((asyy12[nebin]-asyy23[nebin])*(1-f2[nebin])/(f1[nebin]-f2[nebin])/(f1[nebin]-f2[nebin]))/polY;
	ferrys2[nebin]=((asyy12[nebin]-asyy23[nebin])*(1-f1[nebin])/(f1[nebin]-f2[nebin])/(f1[nebin]-f2[nebin]))/polY;//verse f2[nebin]
	ferrbs1[nebin]=((asyb12[nebin]-asyb23[nebin])*(1-f2[nebin])/(f1[nebin]-f2[nebin])/(f1[nebin]-f2[nebin]))/pol;
	ferrbs2[nebin]=((asyb12[nebin]-asyb23[nebin])*(1-f1[nebin])/(f1[nebin]-f2[nebin])/(f1[nebin]-f2[nebin]))/pol;
	//bkg
	ferryb1[nebin]=((asyy12[nebin]-asyy23[nebin])*f2[nebin]/(f1[nebin]-f2[nebin])/(f1[nebin]-f2[nebin]))/polY;
	ferryb2[nebin]=((asyy12[nebin]-asyy23[nebin])*f1[nebin]/(f1[nebin]-f2[nebin])/(f1[nebin]-f2[nebin]))/polY;//verse f2[nebin]
	ferrbb1[nebin]=((asyb12[nebin]-asyb23[nebin])*f2[nebin]/(f1[nebin]-f2[nebin])/(f1[nebin]-f2[nebin]))/pol;
	ferrbb2[nebin]=((asyb12[nebin]-asyb23[nebin])*f1[nebin]/(f1[nebin]-f2[nebin])/(f1[nebin]-f2[nebin]))/pol;
	
	asyerrbs1[nebin]=sqrt(pow(ferrbs1[nebin]*f1E[nebin],2)+pow(ferrbs2[nebin]*f2E[nebin],2));
	asyerrbb1[nebin]=sqrt(pow(ferrbb1[nebin]*f1E[nebin],2)+pow(ferrbb2[nebin]*f2E[nebin],2));
	asyerrys1[nebin]=sqrt(pow(ferrys1[nebin]*f1E[nebin],2)+pow(ferrys2[nebin]*f2E[nebin],2));
	asyerryb1[nebin]=sqrt(pow(ferryb1[nebin]*f1E[nebin],2)+pow(ferryb2[nebin]*f2E[nebin],2));
	
	//cout<<"f3="<<f3<<" f4="<<f4<<" bs="<<asybs[nebin]<<" bb="<<asybb[nebin]<<" bberr="<<asyerrbb[nebin]<<" bserr="<<asyerrbs[nebin]<<" yberr="<<asyerryb[nebin]<<"yserr="<<asyerrys[nebin]<<" yb="<<asyyb[nebin]<<" ys="<<asyys[nebin]<<"  "<< asyerrbs1[nebin]<<"  "<< asyerrbb1[nebin]<<"  "<< asyerrys1[nebin]<<"  "<< asyerryb1[nebin]<<endl;
//	cout<<" ERR " <<asyerrbs1[nebin]<<" "<<asyerrbb1[nebin]<<" "<<asyerrys1[nebin]<<" "<<asyerryb1[nebin]<<" " <<endl;
	//cout<<"f3="<<f3<<" f4="<<f4<<" b12="<<asyb12[nebin]<<" b34="<<asyb23[nebin]<<" bb="<<asybb[nebin]<<" bs="<<asybs[nebin]<<endl;
	}
	for (int nebin=0; nebin<nebins; nebin++){
		asyerrbs1[nebin] = Syst15[nebin]*asybs[nebin]/100;//
	cout<<nebin<<" "<< xf[nebin]<<" "<<Ptmean15[nebin]<< " "<<asybs[nebin]<< " "<<asyerrbs[nebin]<<" " <<asyerrbs1[nebin]<<endl;
	
	}
	TGraphErrors *gasybs=new TGraphErrors(nebins,xf, asybs,ex0,asyerrbs);//stat uncertainty
	TGraphErrors *gasybb=new TGraphErrors(nebins,xf, asybb,ex0,asyerrbb);
	TGraphErrors *gasybberr=new TGraphErrors(nebins,xf,asybb,ex0,asyerrbb1);//syst uncertainty by fraction
	TGraphErrors *gasybserr=new TGraphErrors(nebins,xf,asybs,ex0,asyerrbs1);
	
	TGraphErrors *gasyys=new TGraphErrors(nebins,xfm, asyys,ex0,asyerrys);
	TGraphErrors *gasyyb=new TGraphErrors(nebins,xfm, asyyb,ex0,asyerryb);
	TGraphErrors *gasyyberr=new TGraphErrors(nebins,xfm,asyyb,ex0,asyerryb1);
	TGraphErrors *gasyyserr=new TGraphErrors(nebins,xfm,asyys,ex0,asyerrys1);
	 TCanvas *c2 = new TCanvas("c2", "c2",0,0,1200,450);
		 c2->SetGrid(0,0);
		 c2->Divide(2,1);
		c2->cd(1);
	TH2F *bkg = new TH2F("bkg","A_{N} for Inclusive #pi^{0} ",20,0.16,0.65,10,-0.03,0.12);
	        bkg->GetXaxis()->SetTitle("x_{F}");
	        bkg->GetYaxis()->SetTitle("A_{N}");
	        bkg->GetXaxis()->CenterTitle(true);;
	        bkg->GetYaxis()->CenterTitle(true);;
	        bkg->GetYaxis()->SetTitleSize(0.04);;
	        bkg->Draw();
	TH2F *bkg1 = new TH2F("bkg1","A_{N} for Inclusive #pi^{0} ",20,-0.65,-0.16,10,-0.03,0.12);
	        bkg1->GetXaxis()->SetTitle("x_{F}");
	        bkg1->GetYaxis()->SetTitle("A_{N}");
	        bkg1->GetXaxis()->CenterTitle(true);;
	        bkg1->GetYaxis()->CenterTitle(true);;
	        bkg1->GetYaxis()->SetTitleSize(0.04);;
	
	gasybs->SetMarkerStyle(20);
	gasybs->SetMarkerSize(1.2);
	gasybs->SetMarkerColor(kBlue);
	gasybs->SetLineWidth(2);
	gasybs->SetLineColor(kBlue);
	gasybs->Draw("psame");
	gasybs->GetXaxis()->SetTitle("PiE/Gev");
	gasybs->GetYaxis()->SetTitle("A_{N} xf>0");
	
	gasybserr->SetMarkerStyle(20);
	gasybserr->SetMarkerSize(1.2);
	gasybserr->SetMarkerColor(kBlue);
	gasybserr->SetLineWidth(2);
	gasybserr->SetLineColor(kBlue);
if(syst)	gasybserr->Draw("p2");
	gasybserr->GetXaxis()->SetTitle("PiE/Gev");
	gasybserr->GetYaxis()->SetTitle("A_{N} xf>0");
	gasybserr->SetFillColor(kBlack);
	gasybserr->SetFillStyle(3001);
	
	gasybb->SetMarkerStyle(4);
	gasybb->SetMarkerSize(1.2);
	gasybb->SetMarkerColor(kGreen+3);
	gasybb->SetLineWidth(2);
	gasybb->SetLineColor(kGreen+3);
	gasybb->Draw("p");
	gasybb->GetXaxis()->SetTitle("PiE/Gev");
	gasybb->GetYaxis()->SetTitle("A_{N} bkg");
	
	gasybberr->SetMarkerStyle(4);
	gasybberr->SetMarkerSize(1.2);
	gasybberr->SetMarkerColor(kGreen+3);
	gasybberr->SetLineWidth(2);
	gasybberr->SetLineColor(kGreen+3);
if(syst)	gasybberr->Draw("p2");
	gasybberr->GetXaxis()->SetTitle("PiE/Gev");
	gasybberr->GetYaxis()->SetTitle("A_{N} bkg");
	gasybberr->SetFillColor(kBlack);
	gasybberr->SetFillStyle(3001);
	
	
	TLegend *leg=new TLegend(0.55,0.75,0.9,0.88);
	                leg->SetMargin(0.2);
	                leg->SetBorderSize(0);
	                leg->SetFillColor(0);
	                leg->SetTextSize(0.04);
	                leg->AddEntry(gasybs,"#pi^{0} signal x_{F}>0","PE");
	                leg->AddEntry(gasybb,"Background x_{F}>0","PE");
	leg->Draw();
	
	 TLatex l;
	 TLatex l2;
	    l.SetTextSize(0.03);
	    l2.SetTextSize(0.04);
		l.SetTextAngle(0.);
		l.DrawLatex(0.18,0.08,"3.0% beam pol. scale uncertainty not shown");
		double dx=0.18; double dy=0.042+0.065;
		       l2.DrawLatex(dx,dy-0.000,"p^{#uparrow}+ p -> #pi^{0}+X @ #sqrt{s}=200 GeV");
		       l2.DrawLatex(dx,dy-0.009,"p_{T} > 2 GeV/c");
		       l2.DrawLatex(dx,dy-0.018,"2.7 < #eta < 4.0");
	
	
	c2->cd(2);
	        bkg1->Draw();
	
	gasyys->SetMarkerStyle(20);
	gasyys->SetMarkerSize(1.2);
	gasyys->SetMarkerColor(kMagenta);
	gasyys->SetLineWidth(2);
	gasyys->SetLineColor(kMagenta);
	gasyys->Draw("psame");
	gasyys->GetXaxis()->SetTitle("PiE/Gev");
	gasyys->GetYaxis()->SetTitle("A_{N} xf>0");
	
	gasyyserr->SetMarkerStyle(20);
	gasyyserr->SetMarkerSize(1.2);
	gasyyserr->SetMarkerColor(kMagenta);
	gasyyserr->SetLineWidth(2);
	gasyyserr->SetLineColor(kMagenta);
if(syst)	gasyyserr->Draw("p2");
	gasyyserr->GetXaxis()->SetTitle("PiE/Gev");
	gasyyserr->GetYaxis()->SetTitle("A_{N} xf>0");
	gasyyserr->SetFillColor(kBlack);
	gasyyserr->SetFillStyle(3001);
	
	gasyyb->SetMarkerStyle(4);
	gasyyb->SetMarkerSize(1.2);
	gasyyb->SetMarkerColor(kGreen+3);
	gasyyb->SetLineWidth(2);
gasyyb->SetLineColor(kGreen+3);
	gasyyb->Draw("p");
	gasyyb->GetXaxis()->SetTitle("PiE/Gev");
	gasyyb->GetYaxis()->SetTitle("A_{N} bkg");
	
	gasyyberr->SetMarkerStyle(4);
	gasyyberr->SetMarkerSize(1.2);
	gasyyberr->SetMarkerColor(kGreen+3);
	gasyyberr->SetLineWidth(2);
	gasyyberr->SetLineColor(kGreen+3);
if(syst)	gasyyberr->Draw("p2");
	gasyyberr->GetXaxis()->SetTitle("PiE/Gev");
	gasyyberr->GetYaxis()->SetTitle("A_{N} bkg");
	gasyyberr->SetFillColor(kBlack);
	gasyyberr->SetFillStyle(3001);
	
	TLegend *leg2=new TLegend(0.55,0.75,0.9,0.88);
	                leg2->SetMargin(0.2);
	                leg2->SetBorderSize(0);
	                leg2->SetFillColor(0);
	                leg2->SetTextSize(0.04);
	                leg2->AddEntry(gasyys,"#pi^{0} signal x_{F}<0","PE");
	                leg2->AddEntry(gasyyb,"Background x_{F}<0","PE");
	leg2->Draw();
	l.DrawLatex(-0.63,0.08,"3.0% beam pol. scale uncertainty not shown");
	
	if(drawall)c2->SaveAs("DrawAnRun15.png");
//	c2->SaveAs("digitRun15AN.C");
	gjetAn15 =  (TGraphErrors*)gasybs->Clone();
	gjetAn15Err =  (TGraphErrors*)gasybserr->Clone();

	

//gasyb01->Write();
//gasyy01->Write();
/*gasybs->Write();
gasybb->Write();
gasyys->Write();
gasyyb->Write();
*/
//fout->Write();

}



drawAn11(){
			gROOT->SetStyle("Modern");
	    gStyle->SetOptStat(0000);
	    gStyle->SetOptTitle(kFALSE);
	    gStyle->SetOptFit(1111);//0000);
        gStyle->SetStatColor(0);
      //  gStyle->SetEndErrorSize(1);
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
      //  gStyle->SetTitleFont(72,"xyz");;    
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


double ebinlows[7] = {38, 43, 48, 53, 58, 65, 75};
double ebinhighs[7] = {43, 48, 53, 58, 65, 75, 90};
int nebins = 7;
const int nmbins = 2;
double mbinlows[nmbins] = {0.00, 0.20};
double mbinhighs[nmbins] = {0.20, 0.30};
char resultname[200];
char resultname2[200];
char picname[200];
char picname2[200];
double ex[7]= {0,0,0,0,0,0,0};//x error 
double ex1[7];//for syst
double ex0[7]= {0.005,0.006,0.007,0.007,0.008,0.009,0.011};//true uncertainty
double xf[7]={40.44,45.43,50.41,55.36,61.19,69.35,81.06};
double xfm[7]={40.44,45.43,50.41,55.36,61.19,69.35,81.06};
double xf1[7];
double xf2[7];
for (int nebin=0; nebin<7; nebin++){
//xf[nebin]= (ebinlows[nebin]+ebinhighs[nebin])/2.0/250; //    !!!!!!!!!!type change!!!!!!!!!!
xf[nebin]= xf11[nebin]/250;
xfm[nebin]= -xf11[nebin]/250;
ex0[nebin]= Rsyst*xf[nebin];

xf1[nebin]=( (ebinlows[nebin]+ebinhighs[nebin])/2-0.5)/250;
xf2[nebin]=( (ebinlows[nebin]+ebinhighs[nebin])/2+0.5)/250;
//out<< xf[nebin]<<" " << xf1[nebin]<<endl;
ex1[nebin]=0.005;
}
ifstream result;
ifstream result2;

TF1 *fcn1 = new TF1 ("fcn1","pol0",0,60);
TF1 *fcn2 = new TF1 ("fcn2","pol0",0,60);

double sumasy[6][7];
double sumerr[6][7];

//TFile *fout= new TFile ("DrawAn11.root","recreate");
//fout->cd();
double asy_fill[nmbins][7];
double asyerr_fill[nmbins][7];
double asy_fill2[nmbins][7];
double asyerr_fill2[nmbins][7];
for (int nmbin=0; nmbin<nmbins;nmbin++){
   for (int nebin=0; nebin<7; nebin++){
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
		sprintf(resultname,"../Run11/result/AN2/AN2_Fill%d_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
		sprintf(resultname2,"../Run11/result/AN2/ANy2_Fill%d_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
	//	sprintf(resultname,"/star/u/zwzhu/workspace/project/FMS/DEV/calAN/ebins/result/crAnvsxF_7ebinsFill%d_mass%.2fto%.2fGeV_E%.1fto%.1fGeV_AllTrigger.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
		TString infile(resultname);
		TString infile2(resultname2);
//		cout<<infile<<endl;
		result.open(resultname,ios::in);
		result2.open(resultname2,ios::in);
			asyerr2[nfill]=0;		
			asyerr[nfill]=0;		
		if(!result )  cout<<" file not exist"<<endl;
		
		result>>fill[nfill]>>ene[nfill]>>asy[nfill]>>asyerr[nfill]>>p0[nfill]>>p0e[nfill]>>ml[nfill]>>mh[nfill];
		result2>>fill[nfill]>>ene[nfill]>>asy2[nfill]>>asyerr2[nfill]>>p02[nfill]>>p0e2[nfill]>>ml[nfill]>>mh[nfill];
//		asy2[nfill]=0.004+0.00*nfill; asyerr2[nfill]=0.004;
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
		//cout<<fill[nfill]<<" asyraw= "<<asy2[nfill]<<" err "<<asyerr2[nfill]<<endl;
//		sumasy[nmbin][nebin] += asy[nfill];
//		sumerr[nmbin][nebin] += asyerr[nfill]*asyerr[nfill];	
		}	
		
		sprintf(picname,"./result/pic/AllFill_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.png",mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
		sprintf(picname2,"./yresult/pic/AllFill_mass%.2fto%.2fGeV_E%.1fto%.1fGeV.png",mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
		TGraphErrors *forfit=new TGraphErrors(fillbin,filldouble,asy,fillex,asyerr);
		TGraphErrors *forfit2=new TGraphErrors(fillbin,filldouble,asy2,fillex,asyerr2);
		forfit->Fit("fcn1","RQ");
		asy_fill[nmbin][nebin]=fcn1->GetParameter(0);
		asyerr_fill[nmbin][nebin]=fcn1->GetParError(0);
		forfit2->Fit("fcn2","RQ");
		asy_fill2[nmbin][nebin]=fcn2->GetParameter(0);
		asyerr_fill2[nmbin][nebin]=fcn2->GetParError(0);
	//		cout<<asy_fill[nmbin][nebin]<<" "<<asyerr_fill[nmbin][nebin]<<" "<<endl;
	// TCanvas *c1 = new TCanvas("c1", "c1",0,0,1600,900);
		 //  cout<<" m= "<<nmbin<<" e= "<<nebin<<" "<<asy_fill[nmbin][nebin]<<" "<<asyerr_fill[nmbin][nebin]<<" "<<endl;
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


double asyb01[7];
double asyb12[7];
double asyb23[7];
double asyerrb01[7];
double asyerrb12[7];
double asyerrb23[7];
double asyy01[7];
double asyy12[7];
double asyy23[7];
double asyerry01[7];
double asyerry12[7];
double asyerry23[7];
for (int nebin=0; nebin<7; nebin++){
/*average(asy_fill[2][nebin],asy_fill[3][nebin],asyerr_fill[2][nebin],asyerr_fill[3][nebin],asyb12[nebin],asyerrb12[nebin]);
average(asy_fill[4][nebin],asy_fill[5][nebin],asy_fill[1][nebin],asyerr_fill[4][nebin],asyerr_fill[5][nebin],asyerr_fill[1][nebin],asyb23[nebin],asyerrb23[nebin]);
average(asy_fill2[2][nebin],asy_fill2[3][nebin],asyerr_fill2[2][nebin],asyerr_fill2[3][nebin],asyy12[nebin],asyerry12[nebin]);
average(asy_fill2[4][nebin],asy_fill2[5][nebin],asy_fill2[1][nebin],asyerr_fill2[4][nebin],asyerr_fill2[5][nebin],asyerr_fill2[1][nebin],asyy23[nebin],asyerry23[nebin]);
*/
        asyb12[nebin]=asy_fill[0][nebin];
        asyb23[nebin]=asy_fill[1][nebin];
        asyerrb12[nebin]=asyerr_fill[0][nebin];
        asyerrb23[nebin]=asyerr_fill[1][nebin];
        asyy12[nebin]=asy_fill2[0][nebin];
        asyy23[nebin]=asy_fill2[1][nebin];
        asyerry12[nebin]=asyerr_fill2[0][nebin];
        asyerry23[nebin]=asyerr_fill2[1][nebin];
}

/* TCanvas *c3 = new TCanvas("c3", "c3",0,0,1200,450);
	 c3->SetGrid(0,0);
	 c3->Divide(2,1);
	c3->cd(1);
//TGraphErrors *gasyb01=new TGraphErrors(nebins,xf,asyb01,ex,asyerrb01);
TGraphErrors *gasyb12=new TGraphErrors(nebins,xf,asyb12,ex,asyerrb12);
TGraphErrors *gasyb23=new TGraphErrors(nebins,xf,asyb23,ex,asyerrb23);
//TGraphErrors *gasyy01=new TGraphErrors(nebins,xf,asyy01,ex,asyerry01);
TGraphErrors *gasyy12=new TGraphErrors(nebins,xf,asyy12,ex,asyerry12);
TGraphErrors *gasyy23=new TGraphErrors(nebins,xf,asyy23,ex,asyerry23);
gasyb12->Draw("ap*");
	c3->cd(2);
gasyb23->Draw("ap*");
//gasyb01->SetTitle("Signal m=0.0~0.1");
gasyb12->SetTitle("Signal m=0.1~0.2");
gasyb23->SetTitle("Signal m=0.2~0.3");
//gasyb01->GetXaxis()->SetTitle("PiE/Gev");
//gasyb01->GetYaxis()->SetTitle("A_{N}");
gasyb12->GetXaxis()->SetTitle("x_f");
gasyb12->GetYaxis()->SetTitle("A_{N}");
gasyb23->GetXaxis()->SetTitle("x_f/Gev");
gasyb23->GetYaxis()->SetTitle("A_{N}");
//gasyy01->SetTitle("Signal m=0.0~0.1");
gasyy12->SetTitle("Signal m=0.1~0.2");
gasyy23->SetTitle("Signal m=0.2~0.3");
//gasyy01->GetXaxis()->SetTitle("PiE/Gev");
//gasyy01->GetYaxis()->SetTitle("A_{N}");
gasyy12->GetXaxis()->SetTitle("x_f/Gev");
gasyy12->GetYaxis()->SetTitle("A_{N}");
gasyy23->GetXaxis()->SetTitle("x_f/Gev");
gasyy23->GetYaxis()->SetTitle("A_{N}");
//c1->Print("test.png");
*/
double asybs[7];
double asyerrbs[7];
double asyerrbs1[7]={0,0,0,0,0,0,0};
double asyerrys1[7]={0,0,0,0,0,0,0};
double asyys[7];
double asyerrys[7];
double asybb[7];
double asyerrbb[7];
double asyerrbb1[7]={0,0,0,0,0,0,0};
double asyerryb1[7]={0,0,0,0,0,0,0};
double asyyb[7];
double asyerryb[7];
//double f1[7]={0.694,0.712,0.728,0.732,0.741,0.757,0.792};
//double f2[7]={0.786,0.761,0.748,0.760,0.756,0.718,0.584};
double ferrbs1[7];
double ferrbs2[7];
double ferrys1[7];
double ferrys2[7];
double ferrbb1[7];
double ferrbb2[7];
double ferryb1[7];
double ferryb2[7];


double f1[7];//sig in sig
double f2[7];//sig in bkg
double f1E[7];//
double f2E[7];//

ifstream frac;
frac.open("./txt/11/frac.txt",ios::in);
for (int i=0 ; i<7 ; i++){
frac>>f1[i]>>f1E[i]>>f2[i]>>f2E[i];
}

double asyFinal;
double asyerrFinal;
for (int nebin=0; nebin<7; nebin++){

double f3=(1-f1[nebin])/(1-f2[nebin]);
double f4=f1[nebin]/f2[nebin];

//12-signal region 23bkg region
asybs[nebin]=(asyb12[nebin]-asyb23[nebin]*f3)/(1-f3)/pol;
asyerrbs[nebin]=TMath::Sqrt(asyerrb12[nebin]*asyerrb12[nebin]+asyerrb23[nebin]*asyerrb23[nebin]*f3*f3)/TMath::Abs(1-f3)/pol;
asyys[nebin]=(asyy12[nebin]-asyy23[nebin]*f3)/(1-f3)/polY;
asyerrys[nebin]=TMath::Sqrt(asyerry12[nebin]*asyerry12[nebin]+asyerry23[nebin]*asyerry23[nebin]*f3*f3)/TMath::Abs(1-f3)/polY;
asybb[nebin]=(asyb12[nebin]-asyb23[nebin]*f4)/(1-f4)/pol;
asyerrbb[nebin]=TMath::Sqrt(asyerrb12[nebin]*asyerrb12[nebin]+asyerrb23[nebin]*asyerrb23[nebin]*f4*f4)/TMath::Abs(1-f4)/pol;
asyyb[nebin]=(asyy12[nebin]-asyy23[nebin]*f4)/(1-f4)/polY;
asyerryb[nebin]=TMath::Sqrt(asyerry12[nebin]*asyerry12[nebin]+asyerry23[nebin]*asyerry23[nebin]*f4*f4)/TMath::Abs(1-f4)/polY;

//asyerrbs1[nebin]=sqrt(pow(asyerrbs[nebin],2)+pow(unpol*asybs[nebin]/pol/pol,2));//with unpol
//asyerrbb1[nebin]=sqrt(pow(asyerrbb[nebin],2)+pow(unpol*asybb[nebin]/pol/pol,2));//with unpol
//12 signal region 23 background region
//uncertaintt of f1 f2
//sig
ferrys1[nebin]=((asyy12[nebin]-asyy23[nebin])*(1-f2[nebin])/(f1[nebin]-f2[nebin])/(f1[nebin]-f2[nebin]))/polY;
ferrys2[nebin]=((asyy12[nebin]-asyy23[nebin])*(1-f1[nebin])/(f1[nebin]-f2[nebin])/(f1[nebin]-f2[nebin]))/polY;//verse f2[nebin]
ferrbs1[nebin]=((asyb12[nebin]-asyb23[nebin])*(1-f2[nebin])/(f1[nebin]-f2[nebin])/(f1[nebin]-f2[nebin]))/pol;
ferrbs2[nebin]=((asyb12[nebin]-asyb23[nebin])*(1-f1[nebin])/(f1[nebin]-f2[nebin])/(f1[nebin]-f2[nebin]))/pol;
//bkg
ferryb1[nebin]=((asyy12[nebin]-asyy23[nebin])*f2[nebin]/(f1[nebin]-f2[nebin])/(f1[nebin]-f2[nebin]))/polY;
ferryb2[nebin]=((asyy12[nebin]-asyy23[nebin])*f1[nebin]/(f1[nebin]-f2[nebin])/(f1[nebin]-f2[nebin]))/polY;//verse f2[nebin]
ferrbb1[nebin]=((asyb12[nebin]-asyb23[nebin])*f2[nebin]/(f1[nebin]-f2[nebin])/(f1[nebin]-f2[nebin]))/pol;
ferrbb2[nebin]=((asyb12[nebin]-asyb23[nebin])*f1[nebin]/(f1[nebin]-f2[nebin])/(f1[nebin]-f2[nebin]))/pol;

asyerrbs1[nebin]=sqrt(pow(ferrbs1[nebin]*f1E[nebin],2)+pow(ferrbs2[nebin]*f2E[nebin],2));
asyerrbb1[nebin]=sqrt(pow(ferrbb1[nebin]*f1E[nebin],2)+pow(ferrbb2[nebin]*f2E[nebin],2));
asyerrys1[nebin]=sqrt(pow(ferrys1[nebin]*f1E[nebin],2)+pow(ferrys2[nebin]*f2E[nebin],2));
asyerryb1[nebin]=sqrt(pow(ferryb1[nebin]*f1E[nebin],2)+pow(ferryb2[nebin]*f2E[nebin],2));

//cout<<"f3="<<f3<<" f4="<<f4<<" bberr="<<asyerrbb[nebin]<<" bserr="<<asyerrbs[nebin]<<" bb="<<asybb[nebin]<<" bs="<<asybs[nebin]<<" yberr="<<asyerryb[nebin]<<"ybserr="<<asyerrys[nebin]<<" yb="<<asyyb[nebin]<<" ys="<<asyys[nebin]<<"  "<< asyerrbs1[nebin]<<"  "<< asyerrbb1[nebin]<<"  "<< asyerrys1[nebin]<<"  "<< asyerryb1[nebin]<<endl;
//cout<<"f3="<<f3<<" f4="<<f4<<" b12="<<asyb12[nebin]<<" b34="<<asyb23[nebin]<<" bb="<<asybb[nebin]<<" bs="<<asybs[nebin]<<endl;
//	cout<<" ERR "<<asyerrbs1[nebin]<<" "<<asyerrbb1[nebin]<<" "<<asyerrys1[nebin]<<" "<<asyerryb1[nebin]<<" " <<endl;
//	cout<<" ERR "<<asyerrbs1[nebin]<<" "<<(asyb12[nebin]-asyb23[nebin])*(1-f2[nebin])<<" "<<(f1[nebin]-f2[nebin])<<" "<<f1E[nebin]<<" " <<endl;
}
	for (int nebin=0; nebin<nebins; nebin++){
		asyerrbs1[nebin] = Syst11[nebin]*asybs[nebin]/100;
	cout<<nebin<<" "<< xf[nebin]<<" "<<Ptmean11[nebin]<< " "<<asybs[nebin]<< " "<<asyerrbs[nebin]<<" "<<asyerrbs1[nebin]<<endl;
	}

TGraphErrors *gasybs=new TGraphErrors(nebins,xf, asybs,ex0,asyerrbs);//stat uncertainty
TGraphErrors *gasybb=new TGraphErrors(nebins,xf, asybb,ex0,asyerrbb);
TGraphErrors *gasybberr=new TGraphErrors(nebins,xf,asybb,ex0,asyerrbb1);//syst uncertainty by fraction
TGraphErrors *gasybserr=new TGraphErrors(nebins,xf,asybs,ex0,asyerrbs1);

TGraphErrors *gasyys=new TGraphErrors(nebins,xfm, asyys,ex0,asyerrys);
TGraphErrors *gasyyb=new TGraphErrors(nebins,xfm, asyyb,ex0,asyerryb);
TGraphErrors *gasyyberr=new TGraphErrors(nebins,xfm,asyyb,ex0,asyerryb1);
TGraphErrors *gasyyserr=new TGraphErrors(nebins,xfm,asyys,ex0,asyerrys1);
 TCanvas *c2 = new TCanvas("c2", "c2",0,0,1200,450);
	 c2->SetGrid(0,0);
	 c2->Divide(2,1);
	c2->cd(1);
TH2F *bkg = new TH2F("bkg_2","A_{N} for Inclusive #pi^{0} ",20,0.15,0.35,10,-0.02,0.06);
        bkg->GetXaxis()->SetTitle("x_{F}");
        bkg->GetYaxis()->SetTitle("A_{N}");
        bkg->GetXaxis()->CenterTitle(true);;
        bkg->GetYaxis()->CenterTitle(true);;
        bkg->GetYaxis()->SetTitleSize(0.04);;
        bkg->Draw();
TH2F *bkg1 = new TH2F("bkg1_2","A_{N} for Inclusive #pi^{0} ",20,-0.35,-0.15,10,-0.02,0.06);
        bkg1->GetXaxis()->SetTitle("x_{F}");
        bkg1->GetYaxis()->SetTitle("A_{N}");
        bkg1->GetXaxis()->CenterTitle(true);;
        bkg1->GetYaxis()->CenterTitle(true);;
        bkg1->GetYaxis()->SetTitleSize(0.04);;

gasybs->SetMarkerStyle(20);
gasybs->SetMarkerSize(1.2);
gasybs->SetMarkerColor(kBlue);
gasybs->SetLineWidth(2);
gasybs->SetLineColor(kBlue);
gasybs->Draw("psame");
gasybs->GetXaxis()->SetTitle("PiE/Gev");
gasybs->GetYaxis()->SetTitle("A_{N} xf>0");

gasybserr->SetMarkerStyle(20);
gasybserr->SetMarkerSize(1.2);
gasybserr->SetMarkerColor(kBlue);
gasybserr->SetLineWidth(2);
gasybserr->SetLineColor(kBlue);
if(syst) gasybserr->Draw("p2");
gasybserr->GetXaxis()->SetTitle("PiE/Gev");
gasybserr->GetYaxis()->SetTitle("A_{N} xf>0");
gasybserr->SetFillColor(kBlack);
gasybserr->SetFillStyle(3001);

gasybb->SetMarkerStyle(4);
gasybb->SetMarkerSize(1.2);
gasybb->SetMarkerColor(kGreen+3);
gasybb->SetLineWidth(2);
gasybb->SetLineColor(kGreen+3);
gasybb->Draw("p");
gasybb->GetXaxis()->SetTitle("PiE/Gev");
gasybb->GetYaxis()->SetTitle("A_{N} bkg");

gasybberr->SetMarkerStyle(4);
gasybberr->SetMarkerSize(1.2);
gasybberr->SetMarkerColor(kGreen+3);
gasybberr->SetLineWidth(2);
gasybberr->SetLineColor(kGreen+3);
if(syst) gasybberr->Draw("p2");
gasybberr->GetXaxis()->SetTitle("PiE/Gev");
gasybberr->GetYaxis()->SetTitle("A_{N} bkg");
gasybberr->SetFillColor(kBlack);
gasybberr->SetFillStyle(3001);


TLegend *leg=new TLegend(0.55,0.75,0.85,0.88);
                leg->SetMargin(0.5);
                leg->SetBorderSize(0);
                leg->AddEntry(gasybs,"#pi^{0} signal x_{F}>0","PE");
                leg->AddEntry(gasybb,"Background x_{F}>0","PE");
leg->Draw();

 TLatex l;
 TLatex l2;
    l.SetTextSize(0.03);
    l2.SetTextSize(0.03);
	l.SetTextAngle(0.);
	l.DrawLatex(0.16,0.03,"3.4% beam pol. scale uncertainty not shown");
	double dx=0.16; double dy=0.042+0.01;
	       l2.DrawLatex(dx,dy-0.000,"p^{#uparrow}+ p -> #pi^{0}+X @ #sqrt{s}=500 GeV");
	       l2.DrawLatex(dx,dy-0.005," p_{T} > 2 GeV/c");
	       l2.DrawLatex(dx,dy-0.010," 2.8 < #eta < 4.0");


	c2->cd(2);
        bkg1->Draw();

gasyys->SetMarkerStyle(20);
gasyys->SetMarkerSize(1.);
gasyys->SetMarkerColor(kMagenta);
gasyys->SetLineWidth(2);
gasyys->SetLineColor(kMagenta);
gasyys->Draw("psame");
gasyys->GetXaxis()->SetTitle("PiE/Gev");
gasyys->GetYaxis()->SetTitle("A_{N} xf>0");

gasyyserr->SetMarkerStyle(20);
gasyyserr->SetMarkerSize(1.);
gasyyserr->SetMarkerColor(kMagenta);
gasyyserr->SetLineWidth(2);
gasyyserr->SetLineColor(kMagenta);
if(syst) gasyyserr->Draw("p2");
gasyyserr->GetXaxis()->SetTitle("PiE/Gev");
gasyyserr->GetYaxis()->SetTitle("A_{N} xf>0");
gasyyserr->SetFillColor(kBlack);
gasyyserr->SetFillStyle(3001);

gasyyb->SetMarkerStyle(4);
gasyyb->SetMarkerSize(1.2);
gasyyb->SetMarkerColor(kGreen+3);
gasyyb->SetLineWidth(2);
gasyyb->SetLineColor(kGreen+3);
gasyyb->Draw("p");
gasyyb->GetXaxis()->SetTitle("PiE/Gev");
gasyyb->GetYaxis()->SetTitle("A_{N} bkg");

gasyyberr->SetMarkerStyle(4);
gasyyberr->SetMarkerSize(1.2);
gasyyberr->SetMarkerColor(kGreen+3);
gasyyberr->SetLineWidth(2);
gasyyberr->SetLineColor(kGreen+3);
if(syst) gasyyberr->Draw("p2");
gasyyberr->GetXaxis()->SetTitle("PiE/Gev");
gasyyberr->GetYaxis()->SetTitle("A_{N} bkg");
gasyyberr->SetFillColor(kBlack);
gasyyberr->SetFillStyle(3001);

//TLegend *leg2=new TLegend(0.48,0.8,0.78,0.88);

TLegend *leg2=new TLegend(0.55,0.75,0.85,0.88);
                leg2->SetMargin(0.5);
                leg2->SetBorderSize(0);
                leg2->SetFillColor(0);
                leg2->SetTextSize(0.03);
                leg2->AddEntry(gasyys,"#pi^{0} signal x_{F}<0","PE");
                leg2->AddEntry(gasyyb,"Background x_{F}<0","PE");
leg2->Draw();
l.DrawLatex(-0.34,0.03,"3.4% beam pol. scale uncertainty not shown");

if (drawall) c2->SaveAs("DrawAnRun11.png");
//c2->SaveAs("digitRun11AN.C");
gjetAn11 =  (TGraphErrors*)gasybs->Clone();
gjetAn11Err =  (TGraphErrors*)gasybserr->Clone();



//gasyb01->Write();
//gasyy01->Write();
/*gasybs->Write();
gasybb->Write();
gasyys->Write();
gasyyb->Write();
*/
//fout->Write();

}

void average(double asy1, double asy2, double err1, double err2,double & asyFinal,double & asyerrFinal){
asyFinal= (asy1/err1/err1+asy2/err2/err2)/(1/err1/err1+1/err2/err2);
asyerrFinal=1/TMath::Sqrt(1/err1/err1+1/err2/err2);
}
void average(double asy1, double asy2,double asy3, double err1, double err2,double err3, double & asyFinal,double & asyerrFinal){
asyFinal= (asy1/err1/err1+asy2/err2/err2+asy3/err3/err3)/(1/err1/err1+1/err2/err2+1/err3/err3);
asyerrFinal=1/TMath::Sqrt(1/err1/err1+1/err2/err2+1/err3/err3);
}
