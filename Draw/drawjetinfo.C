double Average(double E1, double E2, double E3,double w1, double w2, double w3){
	double wsum=w1+w2+w3;
	cout<<" w "<<w1<<endl;
	return (E1*w1+E2*w2+E3*w3)/wsum;
}
double Average(double E1, double E2 ,double w1, double w2){
	double wsum=w1+w2;
	return (E1*w1+E2*w2)/wsum;
}


	Int_t drawjetinfo(char* infile="Run15/" ){
		gStyle->SetLabelFont(22,"xyz");

/*
	const int ebins=7;
	Char_t foutname[ebins][100];//111
	  double   elow[ebins] = {18, 23, 28, 33, 38, 43, 48, 53, 58 };
	  double  ehigh[ebins] = {23, 28, 33, 38, 43, 48, 53, 58, 65 };
*/
	const int ebins=9;
	const int nptbins=7;
	const int njetebins15=9;
	const int njetebins=9;
	const int njetebins11=12;
	Char_t foutname[ebins][100];//111
	  double   elow[ebins] = {18, 23, 28, 33, 38, 43, 48, 53, 58 };
	  double  ehigh[ebins] = {23, 28, 33, 38, 43, 48, 53, 58, 65 };


	TFile *fin15[ebins];
	for (int i=0; i<1; i++) {
	sprintf(foutname[i],"Run15jetE%.1fto%.1f.root",elow[i],ehigh[i]);
	//sprintf(foutname[i],"txt/Run15jetrofE%.1fto%.1f.root",elow[i],ehigh[i]);
		fin15[i] = new TFile(foutname[i],"read");
	}	

  TFile *fin11[ebins];
	for (int i=0; i<1; i++) {
	sprintf(foutname[i],"Run11jetE%.1fto%.1f.root",elow[i],ehigh[i]);
	//sprintf(foutname[i],"txt/Run11all1E%.1fto%.1f.root",elow[i],ehigh[i]);
		fin11[i] = new TFile(foutname[i],"read");
	}	





//new
	double ptlow[8]={1.5 ,2,2.5,3,4,5,6,7};
	double pthigh[8]={2,2.5, 3 ,4,5,6,7,8};


//jet info
    TH1F*   fnjet[njetebins];;
    TH1F*   fjetntow[njetebins];;
    TH1F*   fjetE[njetebins];;
    TH1F*   fjetPt[njetebins];;
    TH1F*   fjetEta[njetebins];;
    TH1F*   fjetPhi[njetebins];;
    TH1F*   fjnph[njetebins];;
    TH1F*   fnjet15[njetebins15];;
    TH1F*   fjetntow15[njetebins15];;
    TH1F*   fjetE15[njetebins15];;
    TH1F*   fjetPt15[njetebins15];;
    TH1F*   fjetEta15[njetebins15];;
    TH1F*   fjetPhi15[njetebins15];;
    TH1F*   fjnph15[njetebins15];;
    TH1F*   fnjet11[njetebins11];;
    TH1F*   fjetntow11[njetebins11];;
    TH1F*   fjetE11[njetebins11];;
    TH1F*   fjetPt11[njetebins11];;
    TH1F*   fjetEta11[njetebins11];;
    TH1F*   fjetPhi11[njetebins11];;
    TH1F*   fjnph11[njetebins11];;

	for (int i=0; i<1; i++) {
		//jet info

		fnjet[i]        =( TH1F*) fin15[i]->Get("fnjet");
        fjetntow11[i]		=( TH1F*) fin11[i]->Get("fjetntow");//from jet rec
        fjetntow15[i]		=( TH1F*) fin15[i]->Get("fjetntow");//from jet rec
        fjetE[i]		=( TH1F*) fin15[i]->Get("fjetE");
        fjetPt[i]		=( TH1F*) fin15[i]->Get("fjetPt");
        fjetEta[i]		=( TH1F*) fin15[i]->Get("fjetEta");
        fjetPhi[i]		=( TH1F*) fin15[i]->Get("fjetPhi");
        fjnph[i]		=( TH1F*) fin15[i]->Get("fjnph");//my correlation
	}

        gROOT->SetStyle("Modern");
         gStyle->SetOptTitle(kFALSE);
        gStyle->SetOptStat(0000);
        gStyle->SetOptFit(1111);//0000);
        gStyle->SetStatColor(0);
        gStyle->SetTitleFillColor(0);
 //       gStyle->SetFillColor(0);
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
        gStyle->SetTitleFont(62,"xyz");;    
        gStyle->SetTitleSize(0.04);;    

TCanvas* c1 = new TCanvas("c1"," ",800,600);
//cout<<fjetntow11[0]->Integral()<<endl;
fjetntow11[0]->SetLineColor(kBlue);
fjetntow15[0]->SetLineColor(kRed);
fjetntow11[0]->SetFillColor(kBlue);;
fjetntow15[0]->SetFillColor(kRed);;
fjetntow11[0]->SetFillStyle(3006);;
fjetntow15[0]->SetFillStyle(3007);;

fjetntow11[0]->Scale(100/fjetntow11[0]->Integral());
fjetntow15[0]->Scale(100/fjetntow15[0]->Integral());
fjetntow11[0]->Draw();
fjetntow15[0]->Draw("same");
fjetntow11[0]->GetXaxis()->SetTitle("Photon number");
fjetntow11[0]->GetXaxis()->CenterTitle(true);;
fjetntow11[0]->GetYaxis()->CenterTitle(true);;
fjetntow11[0]->GetYaxis()->SetRangeUser(0,21);;
//fjetntow11[0]->GetYaxis()->SetTitle("Fraction(%)");

	TLatex l2;
		l2.SetTextSize(0.04);
		l2.SetTextAngle(90.);
		l2.DrawLatexNDC(.04,.70,"Fraction [%]");
		//l2.DrawLatexNDC(.04,.50,"Photon number Fraction [%]");
double mean11= fjetntow11[0]->GetMean();
double mean15= fjetntow15[0]->GetMean();
char mean1[22];
char  mean2[22];
sprintf(mean1,"200 GeV: %.1f ", mean15);
sprintf(mean2,"500 GeV: %.1f ", mean11);
	TLatex l;
		l.SetTextSize(0.04);
	double dy=13.4;
	l.DrawLatex(1,19,"STAR    p^{#uparrow} + p -> EM-jet + X");
		l.SetTextSize(0.04);
	l.DrawLatex(8.5,dy-3,"Average photon multiplicity");
	l.DrawLatex(9.5,dy-4.5,mean1);
	l.DrawLatex(9.5,dy-6,mean2);
	l.DrawLatex(8.5,dy,"p^{jet}_{T}> 2 GeV/c");
	l.DrawLatex(8.5,dy-1.5,"2.9 < #eta_{jet} < 3.8 ");

    TLegend* leg = new TLegend(0.65,0.72,0.9,0.89);
    leg->SetBorderSize(0);
    leg->SetMargin(0.2);
    leg->SetTextSize(0.038);
    leg->AddEntry(fjetntow15[0],"200 GeV","f");
    leg->AddEntry(fjetntow11[0],"500 GeV","f");
    leg->SetFillColor(kWhite);
    leg->Draw("same");
    leg->SetBorderSize(0);

c1->SaveAs("jetinfo.png");

	return 1;
  }
	


