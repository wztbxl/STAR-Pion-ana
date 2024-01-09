//Iso frac
//
 Int_t readfrac(  ){
// Int_t Fitdata( Float_t elow = 65, Float_t ehigh = 75, Int_t fillnum = 15314 ){
double xf15Iso0[9]={20.5952 , 25.4095 , 30.2192 , 35.2676 , 40.2814 , 45.2818 , 50.2623 , 55.2269 , 60.9419 };
double xf15Iso1[9]={20.6595 , 25.4468 , 30.186 , 35.2532 , 40.3528 , 45.4267 , 50.4482 , 55.3343 , 61.0473 };
double xf11Iso0[7]={40.4733 , 45.4601 , 50.4409 , 55.392 , 61.1763 , 69.1982 , 80.6029 };
double xf11Iso1[7]={40.5525 , 45.5357 , 50.5438 , 55.4822 , 61.3662 , 69.5345 , 81.0987 };


	
	TVirtualFitter::SetMaxIterations(200000);
	gStyle->SetOptDate(0);
        gStyle->SetOptStat(0);
        gStyle->SetOptFit(0);
        gStyle->SetTitleBorderSize(0);
	
	Bool_t calfrac =0  ;	
	double elow[11]={18, 23, 28, 33, 38, 43, 48, 53, 58,65,75 };
	double ehigh[11]={ 23, 28, 33, 38, 43, 48, 53, 58,65,75 ,90};

	TCanvas* c1 = new TCanvas("c1","c1",800,600);
        c1->SetGridx(0);
        c1->SetGridy(0);
//        const Float_t fitlow = 0.02;
//        const Float_t fithigh = 0.32;	
        const Float_t fitlow = 0.0;
        const Float_t fithigh = 0.3;



	Char_t infilename[11][100];
	Char_t infilename2[11][100];
//       sprintf(infilename,"/star/u/zwzhu/01zwzhu/ana/New/PaperCode/analyzeCode/Run15/Run15_20190927_18754_E58.0to65.0.root",elow,ehigh);
       //  sprintf(infilename,"/star/u/zwzhu/01zwzhu/ana/New/PaperCode/analyzeCode/Run11/Run11_20190930_15315_E75.0to90.0.root",elow,ehigh);
	   TFile* fdata;
	   TH1F* fmdata;
	   TH1F* fmdata1;//iso
	   TH1F* fmdata2;
	   TH1F* fmdata0;//non-iso

		double fracm0[11];
		double fracm1[11];
		double frac[11];

ifstream fin;
fin.open("txt/11/outfrac11.txt",ios::in);
ifstream fin0;
fin0.open("txt/11/outfrac11_iso0.txt",ios::in);
ifstream fin1;
fin1.open("txt/11/outfrac11_iso1.txt",ios::in);
	for ( int i=4 ; i<11; i++ ){
		fin>>frac[i];
		fin0>>fracm0[i];
		fin1>>fracm1[i];
	}
		double frac2m0[11];
		double frac2m1[11];
		double frac2[11];

ifstream fin15;
fin15.open("txt/15/outfrac15.txt",ios::in);
ifstream fin150;
fin150.open("txt/15/outfrac15_iso0.txt",ios::in);
ifstream fin151;
fin151.open("txt/15/outfrac15_iso1.txt",ios::in);
	for ( int i=0 ; i<11; i++ ){
		fin15>>frac2[i];
		fin150>>frac2m0[i];
		fin151>>frac2m1[i];
	}

double f11iso0[7];
double f11iso1[7];
double f15iso0[9];
double f15iso1[9];
double f15iso2[9];
double xf11[7];
double xf11iso0[7];
double xf11iso1[7];
double xf15[9];
double xf15iso0[9];
double xf15iso1[9];

TH2F *bkg = new TH2F("bkg"," ",100,0.14,0.66,10,0,80);
TH1F *bkg1 = new TH1F("bkg1"," A_{N}",100,0.14,0.66);
   bkg1->SetFillColor(kRed);
   bkg1->SetFillStyle(3001);
          bkg->GetXaxis()->SetTitle("x_{F}");
          bkg->GetYaxis()->SetTitle("fraction %");
          bkg->GetXaxis()->CenterTitle(true);;
          bkg->GetYaxis()->CenterTitle(true);;
          bkg->GetXaxis()->SetTitleSize(0.06);;
          bkg->GetYaxis()->SetTitleSize(0.06);;
          bkg->GetYaxis()->SetTitleOffset(0.66);;
          bkg->GetXaxis()->SetTitleOffset(0.66);;
TH1F *bkg2 = new TH1F("bkg2"," A_{N}",100,0.14,0.66);//iso
   bkg2->SetFillColor(kBlue);
   bkg2->SetFillStyle(3001);
TH1F *bkg3 = new TH1F("bkg3"," A_{N}",100,0.14,0.66);//iso
   bkg3->SetFillColor(kRed);
   bkg3->SetFillStyle(3007);
TH1F *bkg4 = new TH1F("bkg4"," A_{N}",100,0.14,0.66);//iso
   bkg4->SetFillColor(kBlue);
   bkg4->SetFillStyle(3007);

	for ( int i=4 ; i<11; i++ ){
	    
        sprintf(infilename[i],"/star/u/zwzhu/01zwzhu/ana/New/PaperCode/Submit/drawresult/txt/Run11ME%.1fto%.1f.root",elow[i],ehigh[i]);
        fdata = new TFile(infilename[i],"read");
        fmdata = (TH1F*)fdata->Get("fmdata");
        fmdata1 = (TH1F*)fdata->Get("fmdataIso1");
        TH1F* fmdata2 = (TH1F*)fdata->Get("fmdataIso2");//gap
        fmdata0 = (TH1F*)fdata->Get("fmdataIso0all");

		fmdata->GetXaxis()->SetRangeUser(fitlow,fithigh);
		double sum=0;
		for ( int bin=1 ; bin<24; bin++ ){
			sum += fmdata->GetBinContent(bin);
		}
		int xf =1 + floor(((elow[i]+ehigh[i])/2/250-0.14)/(0.66-0.14)*100);
		bkg1->SetBinContent(xf,100*fmdata0->GetEntries()/sum*fracm0[i]/frac[i]  );
		bkg2->SetBinContent(xf,100*fmdata1->GetEntries()/sum*fracm1[i]/frac[i]  );
		f11iso0[i-4]=100*fmdata0->GetEntries()/sum*fracm0[i]/frac[i];
		f11iso1[i-4]=100*fmdata1->GetEntries()/sum*fracm1[i]/frac[i];
		xf11[i-4]=(elow[i]+ehigh[i])/2/250;
		xf11iso0[i-4]=xf11Iso0[i-4]/250;
		xf11iso1[i-4]=xf11Iso1[i-4]/250;
	//	cout<<" xf="<<((elow[i]+ehigh[i])/2/250-0.14)<<" " <<100*fmdata0->GetEntries()/sum<<" fracm0="<<fracm0[i]/frac[i]<<" " <<100*fmdata1->GetEntries()/sum<<" fracm1="<<fracm1[i]/frac[i] <<endl;
		cout<<xf11[i-4]<<" "<<f11iso0[i-4]<<" "<<f11iso1[i-4]<<endl;
	}
	for ( int i=0 ; i<9; i++ ){
	    
        sprintf(infilename2[i],"/star/u/zwzhu/01zwzhu/ana/New/PaperCode/Submit/drawresult/Run15allE%.1fto%.1f.root",elow[i],ehigh[i]);
        fdata = new TFile(infilename2[i],"read");
        fmdata = (TH1F*)fdata->Get("fmdata");
        fmdata1 = (TH1F*)fdata->Get("fmdataIso1");
        fmdata2 = (TH1F*)fdata->Get("fmdataIso2");//gap
        fmdata0 = (TH1F*)fdata->Get("fmdataIso0all");

		fmdata->GetXaxis()->SetRangeUser(fitlow,fithigh);
		double sum=0;
		for ( int bin=1 ; bin<24; bin++ ){
			sum += fmdata->GetBinContent(bin);
		}
		int xf =1 + floor(((elow[i]+ehigh[i])/2/100-0.14)/(0.66-0.14)*100);
		xf15[i]=(elow[i]+ehigh[i])/2/100;
		xf15iso0[i]=xf15Iso0[i]/100;
		xf15iso1[i]=xf15Iso1[i]/100;
		//cout<<" xf="<<((elow[i]+ehigh[i])/2/100-0.14)<<" " <<100*fmdata0->GetEntries()/sum<<" fracm0="<<frac2m0[i]/frac2[i]<<" " <<100*fmdata1->GetEntries()/sum<<" fracm1="<<frac2m1[i]/frac2[i] <<endl;
		bkg3->SetBinContent(xf,100*fmdata0->GetEntries()/sum*frac2m0[i]/frac2[i]  );
		bkg4->SetBinContent(xf,100*fmdata1->GetEntries()/sum*frac2m1[i]/frac2[i]  );
		f15iso0[i]=100*fmdata0->GetEntries()/sum*frac2m0[i]/frac2[i];
		f15iso1[i]=100*fmdata1->GetEntries()/sum*frac2m1[i]/frac2[i];
		f15iso2[i]=100*fmdata1->GetEntries()/sum*(frac2m0[i]/2+frac2m1[i]/2)/frac2[i];
		cout<<xf15[i]<<"  in  "<<i<<"  "<<f15iso0[i]<<" "<<f15iso1[i]<<endl;
	}


   bkg->Draw("");
   c1->Update();
   THStack hs("hs","same ");
   hs.Add(bkg1);
   hs.Add(bkg2);
   hs.Add(bkg3);
   hs.Add(bkg4);
   hs.Draw("same");
 //  TCanvas c1("c1","stacked hists",10,10,1200,900);

//	cout<<"  #="<<sum<<" "<<fmdata0->GetEntries()/sum<<" "<<fmdata1->GetEntries()/sum<<" "<<fmdata2->GetEntries()/sum<<endl;
//	cout<<"  #="<<sum<<" "<<fmdata0->GetEntries()/sum+fmdata1->GetEntries()/sum+fmdata2->GetEntries()/sum<<endl;


	/*
        fmdata->SetMarkerStyle(20);
        fmdata->SetMarkerSize(1.0);
        fmdata->SetLineColor(kBlue);
        fmdata->GetXaxis()->SetRangeUser(fitlow,fithigh);
        fmdata->GetXaxis()->SetTitle("M_{#gamma#gamma} / GeV");
        fmdata->SetTitle("");
	*/


	
	TLegend* leg = new TLegend(0.50,0.50,0.85,0.88);
	leg->SetBorderSize(0);
	leg->SetMargin(0.2);
	leg->SetTextSize(0.05);
	leg->AddEntry(bkg1,"500GeV Non-isolated #pi^{0} ","f");
	leg->AddEntry(bkg2,"500GeV Isolated #pi^{0} ","f");
	leg->AddEntry(bkg3,"200GeV Non-isolated #pi^{0} ","f");
	leg->AddEntry(bkg4,"200GeV Isolated #pi^{0}","f");
	leg->SetFillColor(kWhite);
	leg->Draw("same");
	leg->SetBorderSize(0);


	Char_t outfilename[100];
   //    sprintf(outfilename,"DrawIsofracH.png",elow,ehigh);	
  //     c1->SaveAs(outfilename);	


	TCanvas* c2 = new TCanvas("c2","c2",700,500);
        c2->SetGridx(0);
        c2->SetGridy(0);
		c2->cd();
		bkg->Draw();
	TGraph* g11iso0=new TGraph(7,xf11iso0,f11iso0);
	TGraph* g11iso1=new TGraph(7,xf11iso1,f11iso1);
	TGraph* g15iso0=new TGraph(9,xf15iso0,f15iso0);
	TGraph* g15iso1=new TGraph(9,xf15iso1,f15iso1);
	TGraph* g15iso2=new TGraph(9,xf15,f15iso2);

    g11iso0->SetMarkerStyle(26);
    g11iso1->SetMarkerStyle(22);
    g11iso0->SetMarkerSize(1.4);
    g11iso1->SetMarkerSize(1.4);
    g15iso0->SetMarkerStyle(24);
    g15iso1->SetMarkerStyle(20);
    g15iso0->SetMarkerSize(1.3);
    g15iso1->SetMarkerSize(1.3);


	g11iso0->SetMarkerColor(kBlue);
	g11iso1->SetMarkerColor(kBlue);
	g15iso0->SetMarkerColor(kRed);
	g15iso1->SetMarkerColor(kRed);
	g15iso2->SetMarkerColor(kRed+4);
	g11iso0->Draw("psame");
	g11iso1->Draw("psame");
	g15iso0->Draw("psame");
	g15iso1->Draw("psame");
//	g15iso2->Draw("psame");
	TLegend* leg2 = new TLegend(0.45,0.60,0.85,0.88);
	leg2->SetBorderSize(0);
	leg2->SetMargin(0.2);
	leg2->SetTextSize(0.05);
	leg2->AddEntry(g11iso0,"500GeV Non-isolated #pi^{0} ","lp");
	leg2->AddEntry(g11iso1,"500GeV Isolated #pi^{0} ","lp");
	leg2->AddEntry(g15iso0,"200GeV Non-isolated #pi^{0} ","lp");
	leg2->AddEntry(g15iso1,"200GeV Isolated #pi^{0}","lp");
	leg2->SetFillColor(kWhite);
	leg2->Draw("same");
	leg2->SetBorderSize(0);


		TLatex l2;
	double dx=0.16; double dy=60;
	     l2.SetTextSize(0.05);
	     l2.DrawLatex(dx,dy-0.00,"STAR ");

       c2->SaveAs("DrawIsofracG.png");	

	return 1;
  }	
