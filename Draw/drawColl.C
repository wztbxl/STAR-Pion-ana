bool updateplot=0;
TGraphErrors *gjetAn15 ;
TGraphErrors *gjetAn11 ;
double Rsyst = 0.0;

     double xf15[6] = {0.356,	0.466,	0.571,	0.665,	0.755,	0.832};;//already corrected
     double xf11[6] = {0.379,	0.500,	0.610,	0.703,	0.782,	0.846};
TGraphErrors * AnvsMass11[2];
TGraphErrors * AnvsMass15[2];

drawColl(){
	
	//	gROOT->SetStyle("Modern");
	drawColl15(1);	
	drawColl11(1);	


TCanvas *c11 = new TCanvas("c11", "c11",0,0,800,600);
	
TH2F *bkgCom = new TH2F("bkgCom","",20,0.3,0.9,10,-0.012,0.02);
 /*       bkgCom->GetXaxis()->SetTitle("Z_{em}");
        bkgCom->GetYaxis()->SetTitle("A_{UT}");
        bkgCom->GetXaxis()->CenterTitle(true);;
        bkgCom->GetYaxis()->CenterTitle(true);;
        bkgCom->GetYaxis()->SetTitleSize(0.04);;
		bkgCom->GetYaxis()->SetTitleOffset(1.2);
*/		bkgCom->Draw();

    gjetAn11->SetMarkerStyle(22);
    gjetAn11->SetMarkerSize(1.5);
    gjetAn11->SetMarkerColor(kBlue);
    gjetAn11->SetLineWidth(2);
    gjetAn11->SetLineColor(kBlue);
    gjetAn11->Draw("psame");
    gjetAn15->SetMarkerStyle(20);
    gjetAn15->SetMarkerSize(1.3);
    gjetAn15->SetMarkerColor(kRed);
    gjetAn15->SetLineWidth(2);
    gjetAn15->SetLineColor(kRed);
    gjetAn15->Draw("psame");



TLegend *leg=new TLegend(0.55,0.70,0.85,0.88);
                leg->SetMargin(0.5);
                leg->SetBorderSize(0);
                leg->SetFillColor(0);
                leg->SetTextSize(0.04);
                leg->AddEntry(gjetAn15,"200 GeV","PE");
                leg->AddEntry(gjetAn11,"500 GeV","PE");
leg->Draw();

 TLatex l;
 TLatex l2;
     l.SetTextSize(0.036);
     l2.SetTextSize(0.036);
	 l.SetTextAngle(0.);
	 l2.DrawLatex(0.32,0.008,"3.0/3.4% beam pol. scale uncertainty not shown");
double dx=0.32; double dy=0.018;
	l.DrawLatex(dx,dy-0.000,"STAR    p^{#uparrow} + p -> EM-jet + #pi^{0} + X");// @ #sqrt{s}=200/500 GeV");
	l.DrawLatex(dx,dy-0.0025,"Jet algorithm: anti-kT R=0.7 ");
    l.DrawLatex(dx,dy-0.005, "Jet p_{T} > 2 GeV/c");
    l.DrawLatex(dx,dy-0.0075,"2.9< #eta_{jet} <3.8, 2.7< #eta_{#pi^{0}} <4.0 ");
//    l.DrawLatex(dx,dy-0.01,"j_{T} < 0.2 GeV");

	TLine* line=new TLine(0.3,0,0.9,0);
	line->Draw();
gPad->SetLeftMargin(0.1);
TLatex latex;
      latex.SetTextSize(0.05);
       latex.SetTextAlign(13);
        latex.DrawLatexNDC(.02,.85,"A_{UT}");
	    latex.DrawLatexNDC(.5,0.05,"z_{em}");

//c11->SaveAs("DrawCollCom.png");
// theory
//    c->cd(1);   
    ifstream theo1_200[2];
    ifstream theo1_500[2];
     const int Np200=7;
     const int Np500=7;
        string word1,word2,word3;
        double T200N[2][Np200];
        double T200asy[2][Np200];
        double T200asyerr[2][Np200];
        double T200asyerrl[2][Np200];
        double T200asyerrh[2][Np200];
        double Ex200[2][Np200];
        double T500N[2][Np500];
        double T500asy[2][Np500];
        double T500asyerr[2][Np500];
        double T500asyerrl[2][Np500];
        double T500asyerrh[2][Np500];
        double Ex500[2][Np500];

        double T200asyerrL[2][Np500];
        double T500asyerrL[2][Np500];
        double T200asyerrH[2][Np500];
        double T500asyerrH[2][Np500];
		TGraphAsymmErrors * gth1_200[2];
		TGraph * gth1_200L[2]   ;     
		TGraphAsymmErrors * gth1_500[2];
		TGraph * gth1_500L[2]   ;     

		theo1_500[0].open("theory/Alexei/STAR_2020_500gev_no_evo__pi0_z.dat",ios::in);
        theo1_200[0].open("theory/Alexei/STAR_2020_200gev_no_evo__pi0_z.dat",ios::in);
        theo1_500[1].open("theory/Alexei/STAR_2020_500gev_pi0_z.dat",ios::in);
        theo1_200[1].open("theory/Alexei/STAR_2020_200gev_pi0_z.dat",ios::in);
	for(int  i=0 ; i<2; i++){
        for (int np=0; np<=Np200; np++){
            if (np==0) theo1_200[i]>>word1>>word2>>word3;
            else theo1_200[i]>>T200N[i][np-1]>>T200asy[i][np-1]>>T200asyerrl[i][np-1]>>T200asyerrh[i][np-1];
            if (np>0){  T200asyerrL[i][np-1]=T200asy[i][np-1]-T200asyerrl[i][np-1];
                        T200asyerrH[i][np-1]=-T200asy[i][np-1]+T200asyerrh[i][np-1];
                //      cout<< T200asyerrL[np-1]<< "        " <<  T200asyerrH[np-1]<<endl;
                    }    
            if (np!=Np200) Ex200[i][np]=0;
            }    
        for (int np=0; np<=Np500; np++){
            if (np==0) theo1_500[i]>>word1>>word2>>word3;
            else theo1_500[i]>>T500N[i][np-1]>>T500asy[i][np-1]>>T500asyerrl[i][np-1]>>T500asyerrh[i][np-1];
            if (np>0){  T500asyerrL[i][np-1]=T500asy[i][np-1]-T500asyerrl[i][np-1];
                        T500asyerrH[i][np-1]=-T500asy[i][np-1]+T500asyerrh[i][np-1];
                    }    
            if (np!=Np500) Ex500[i][np]=0;
        }  
   gth1_200[i] = new TGraphAsymmErrors(Np200,T200N[i],T200asy[i],Ex200[i],Ex200[i],T200asyerrL[i],T200asyerrH[i]);
   gth1_500[i] = new TGraphAsymmErrors(Np500,T500N[i],T500asy[i],Ex500[i],Ex500[i],T500asyerrL[i],T500asyerrH[i]);
      gth1_200L[i]=new TGraph(Np200,T200N[i],T200asy[i]);
      gth1_500L[i]=new TGraph(Np500,T500N[i],T500asy[i]);
        gth1_200L[i]->SetLineColor(kRed-9*i);
        gth1_200[i]->SetFillColorAlpha(kRed-9*i,0.85-0.5*i);
        gth1_500L[i]->SetLineColor(kBlue-7*i);
        gth1_500[i]->SetFillColorAlpha(kBlue-7*i,0.85-0.5*i);
	}
        gth1_200[0]->SetFillColorAlpha(kRed,0.85);
		gth1_500[0]->SetFillStyle(3345);
		gth1_200[0]->SetFillStyle(3354);
		gth1_200[1]->SetLineStyle(7);
		gth1_500[1]->SetLineStyle(7);
		gth1_200L[1]->SetLineStyle(7);
		gth1_500L[1]->SetLineStyle(7);
		gth1_200[1]->SetLineWidth(3);
		gth1_200L[1]->SetLineWidth(3);
		gth1_500[1]->SetLineWidth(3);
		gth1_500L[1]->SetLineWidth(3);
			
        gth1_200[0]->Draw("3csame");
        gth1_500[0]->Draw("3csame");
        gth1_200L[0]->Draw("csame");
        gth1_500L[0]->Draw("csame");
        gth1_200[1]->Draw("3csame");
        gth1_500[1]->Draw("3csame");
        gth1_200L[1]->Draw("csame");
        gth1_500L[1]->Draw("csame");
    TLegend *leg3=new TLegend(0.15,0.12,0.28,0.25);
                leg3->SetMargin(0.3);
                leg3->SetBorderSize(0);
                leg3->SetFillColor(0);
                leg3->SetTextSize(0.04);
                leg3->AddEntry(gth1_200[0],"Theory 200 GeV","f");
                leg3->AddEntry(gth1_500[0],"Theory 500 GeV","f");
    leg3->Draw();
    TLegend *leg4=new TLegend(0.43,0.12,0.68,0.25);
                leg4->SetMargin(0.25);
                leg4->SetBorderSize(0);
                leg4->SetFillColor(0);
                leg4->SetTextSize(0.04);
                leg4->AddEntry(gth1_200[1],"Theory(Evo.) 200 GeV","f");
                leg4->AddEntry(gth1_500[1],"Theory(Evo.) 500 GeV","f");
    leg4->Draw();

c11->SaveAs("DrawCollComT.png");



// mass dependent
TCanvas *c333=new TCanvas("c333", "c333",0,0,1500,600);
//c333->cd();
c333->Divide(2,1);
	TH2F*  bkgm = new TH2F("bkgm","",20,0.3,1,22,-0.004,0.004);
	TH2F*  bkgm2 = new TH2F("bkgm2","",20,0.3,1,22,-0.004,0.004);
    bkgm->GetXaxis()->SetTitle("z_{em}");;
    bkgm->GetYaxis()->SetTitle("A_{UT}");;
    bkgm->GetXaxis()->CenterTitle(true);;
    bkgm->GetYaxis()->CenterTitle(true);;
    bkgm->GetYaxis()->SetTitleSize(0.05);;
    bkgm->GetXaxis()->SetTitleSize(0.05);;
	bkgm->GetYaxis()->SetTitleOffset(1.2);
c333->cd(1);	
	bkgm->Draw();
   AnvsMass11[0]->Draw("Psame");
   AnvsMass11[1]->Draw("Psame");
   AnvsMass11[0]->SetMarkerColor(kBlue);;
   AnvsMass11[1]->SetMarkerColor(kBlue);;
   AnvsMass11[0]->SetMarkerStyle(20);;
   AnvsMass11[1]->SetMarkerStyle(24);;
   AnvsMass11[0]->SetLineColor(kBlue);;
   AnvsMass11[1]->SetLineColor(kBlue);;
TLegend *legm2=new TLegend(0.5,0.70,0.88,0.88);
                legm2->SetMargin(0.2);
                legm2->SetBorderSize(0);
                legm2->SetFillColor(0);
                legm2->SetTextSize(0.04);
 //               legm2->AddEntry( AnvsMass15[0],"200GeV M<0.2 GeV","PE");
   //             legm2->AddEntry( AnvsMass15[1],"200GeV 0.2<M<0.3 GeV","PE");
                legm2->AddEntry( AnvsMass11[0],"500GeV M<0.2 GeV","PE");
                legm2->AddEntry( AnvsMass11[1],"500GeV 0.2<M<0.3 GeV","PE");
legm2->Draw();
c333->cd(2);	
	bkgm->Draw();
   AnvsMass15[0]->Draw("Psame");
   AnvsMass15[1]->Draw("Psame");
   AnvsMass15[0]->SetMarkerColor(kRed);;
   AnvsMass15[1]->SetMarkerColor(kRed);;
   AnvsMass15[0]->SetMarkerStyle(20);;
   AnvsMass15[1]->SetMarkerStyle(24);;
   AnvsMass15[0]->SetLineColor(kRed);;
   AnvsMass15[1]->SetLineColor(kRed);;
TLegend *legm3=new TLegend(0.5,0.70,0.88,0.88);
                legm3->SetMargin(0.2);
                legm3->SetBorderSize(0);
                legm3->SetFillColor(0);
                legm3->SetTextSize(0.04);
                legm3->AddEntry( AnvsMass15[0],"200GeV M<0.2 GeV","PE");
                legm3->AddEntry( AnvsMass15[1],"200GeV 0.2<M<0.3 GeV","PE");
     //           legm2->AddEntry( AnvsMass11[0],"500GeV M<0.2 GeV","PE");
       //         legm2->AddEntry( AnvsMass11[1],"500GeV 0.2<M<0.3 GeV","PE");
legm3->Draw();
                
//   c333->SaveAs("CollinsMass2.png");
}

drawColl15( int Mset=12345){
		gROOT->SetStyle("Modern");
	gStyle->SetOptStat(0000);
	gStyle->SetOptFit(1111);//0000);
        gStyle->SetStatColor(0);
      //  gStyle->SetEndErrorSize(1);
        gStyle->SetOptDate(0);
        gStyle->SetStatFont(42);
        gStyle->SetStatW(0.13);
        gStyle->SetStatH(0.13);
        gStyle->SetStatX(1.0);
        gStyle->SetStatY(1.0);
        gStyle->SetTitleXOffset(1.0); 
        gStyle->SetTitleYOffset(1.1); 
        gStyle->SetHistLineWidth(2);; 
        gStyle->SetTitleSize(0.04);;  
	 gStyle->SetTitleFont(72,"xyz");;
double pol=0.5734;
double polY=0.5836;

fstream AUTre("AUTre",ios::app|ios::out);

ifstream filllist;
filllist.open("Run15filllist");
const int nfills=53;// how many fill are being used
int fillnum[nfills];
double fillex[nfills];
double filldouble[nfills];
int fillbin=nfills;
for (int nfill=0; nfill<nfills; nfill++){
    filllist>>fillnum[nfill];
    fillex[nfill]=0;
    filldouble[nfill] = double(nfill+1);
//	cout<<fillnum[nfill];
}

auto mg = new TMultiGraph("mg","mg"); 
double ebinlows[6] = {0.3, 0.4, 0.5, 0.6, 0.7, 0.8};
double ebinhighs[6] ={0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
const int nebins = 6;
const int nmbins = 2;
double mbinlows[nmbins] = {0.00, 0.20};
double mbinhighs[nmbins] = {0.20, 0.30};
double jtbinlows[2] = {0.00, 0.20};
double jtbinhighs[2] = {0.20, 0.60 };
const int njtbins = 2;
char resultname[200];
char resultname2[200];
char picname[200];
char picname2[200];
double ex0[njtbins][6];
double ex[6];
double ex1[6];
double xf[6] ;//after z correction  ;Zem
double xf1[6];
double xf2[6];

double unz[6] = {0.0254, 0.0303, 0.0351 , 0.0398 ,  0.0441 ,0.0478};//z un
double unpol=0.00;
//double unsys[6]={3.5, 4.5 , 6 , 8, 12.6, 27};
double unsys[6]={1., 1.1 , 1.4 , 2.1, 2.5, 3.9};

for (int nebin=0; nebin<nebins; nebin++){
//xf[nebin]= (ebinlows[nebin]+ebinhighs[nebin])/2.0; //    !!!!!!!!!!type change!!!!!!!!!!
//xf[nebin]=( (ebinlows[nebin]+ebinhighs[nebin])/2-0.0)/250;
xf1[nebin]=( (ebinlows[nebin]+ebinhighs[nebin])/2-0.01);
xf2[nebin]=( (ebinlows[nebin]+ebinhighs[nebin])/2+0.01);
//ex[nebin]=unz[nebin];
ex[nebin]=xf15[nebin]*Rsyst;
ex1[nebin]=0.01;
xf[nebin]=xf15[nebin];
ex0[0][nebin]=0;
ex0[1][nebin]=0;


//out<< xf[nebin]<<" " << xf1[nebin]<<end
}
ifstream result;
ifstream result2;

TF1 *fcn1 = new TF1 ("fcn1","pol0",0,55);
TF1 *fcn2 = new TF1 ("fcn2","pol0",0,55);

double sumasy[6][6];
double sumerr[6][6];

//TFile *fout= new TFile ("DrawColl15.root","recreate");
//fout->cd();
double asy_fill[njtbins][6][6];
double asyerr_fill[njtbins][6][6];
double asy_fill2[njtbins][6][6];
double asyerr_fill2[njtbins][6][6];
for (int njtbin=0; njtbin<njtbins;njtbin++){
	for (int nmbin=0; nmbin<nmbins;nmbin++){
   		for (int nebin=0; nebin<6; nebin++){
	int fill[nfills];
	double ene[nfills];
	double asy[nfills];
	double asy2[nfills];
	double asyerr[nfills];
	double asyerr2[nfills];
	double ml[nfills];
	double mh[nfills];
	double p0[nfills];
	double p0e[nfills];
	double p02[nfills];
	double p0e2[nfills];
		for (int nfill=0; nfill<nfills;nfill++){
		//cout<<"bin  "<<mbinlows[nmbin]<<"   "<<mbinhighs[nmbin]<<endl;
		sprintf(resultname,"/star/u/zwzhu/01zwzhu/ana/New/PaperCode/Code2/Run15/result/Collins2/Collins_Fill_%d_mass%.2fto%.2fGeV_Z%.1fto%.1f_Jt%.2fto%.2fGeV_AllTrigger.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin],jtbinlows[njtbin],jtbinhighs[njtbin]);
		sprintf(resultname2,"/star/u/zwzhu/01zwzhu/ana/New/PaperCode/Code2/Run15/result/Collins2/Collinsy_Fill%d_mass%.2fto%.2fGeV_Z%.1fto%.1f_Jt%.2fto%.2fGeV_AllTrigger.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin],jtbinlows[njtbin],jtbinhighs[njtbin]);
		TString infile(resultname);
		TString infile2(resultname2);
	//	cout<<infile<<endl;
		result.open(resultname,ios::in);
		result2.open(resultname2,ios::in);
		
		asyerr2[nfill]=0;
		asyerr[nfill]=0;
		 if(!result )  cout<<" file not exist"<<endl;
		result>>fill[nfill]>>ene[nfill]>>asy[nfill]>>asyerr[nfill]>>p0[nfill]>>p0e[nfill]>>ml[nfill]>>mh[nfill];
		result2>>fill[nfill]>>ene[nfill]>>asy2[nfill]>>asyerr2[nfill]>>p02[nfill]>>p0e2[nfill]>>ml[nfill]>>mh[nfill];
//		cout<<fill[nfill]<<" asyraw= "<<asy[nfill]<<" err "<<asyerr[nfill]<<endl;
//		cout<<fill[nfill]<<" asyraw2= "<<asy2[nfill]<<" err2 "<<asyerr2[nfill]<<endl;
		result.close();
		result2.close();
        if (asyerr2[nfill]==0.) {  //cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<resultname2<<endl  ;          
            asy2[nfill]=0;       
            asyerr2[nfill]=999;
        }   

        if (asyerr[nfill]==0.) {  //cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<resultname<<endl  ;    
            asy[nfill]=0; 
            asyerr[nfill]=999;
        } 
//		sumerr[nmbin][nebin] += asyerr[nfill]*asyerr[nfill];	
		}	
		
		sprintf(picname,"./count/pic/crAnvsxF_mass%.2fto%.2fGeV_Z%.2fto%.2fGeV_AllTrigger.png",mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
		sprintf(picname2,"./ycount/pic/crAnvsxF_mass%.2fto%.2fGeV_Z%.2fto%.2fGeV_AllTrigger.png",mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
		TGraphErrors *forfit=new TGraphErrors(fillbin,filldouble,asy,fillex,asyerr);
		TGraphErrors *forfit2=new TGraphErrors(fillbin,filldouble,asy2,fillex,asyerr2);
		forfit->Fit("fcn1","RQ");
		asy_fill[njtbin][nmbin][nebin]=fcn1->GetParameter(0);
		asyerr_fill[njtbin][nmbin][nebin]=fcn1->GetParError(0);
		forfit2->Fit("fcn2","RQ");
		asy_fill2[njtbin][nmbin][nebin]=fcn2->GetParameter(0);
		asyerr_fill2[njtbin][nmbin][nebin]=fcn2->GetParError(0);
	//	cout<<njtbin<<" m="<<nmbin<<" e="<<nebin<<" "<<asy_fill[njtbin][nmbin][nebin]<<" "<<asyerr_fill[njtbin][nmbin][nebin]<<" "<<endl;
	//	TCanvas *c1 = new TCanvas("c1", "c1",0,0,1500,900);
				 forfit->SetTitle(picname);
				 forfit->SetLineWidth(3);
				 forfit->SetLineColor(4);
				 forfit->SetMarkerSize(3);
                                forfit->GetXaxis()->SetTitle("Fill number");
                                forfit->GetYaxis()->SetTitle("A_{N}");
                                forfit2->SetTitle(picname2);
                                forfit2->GetXaxis()->SetTitle("Fill number");
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
}//jt


//mass-dependant


TGraphErrors * AnvsMass[2];
double asymbin[2][6];
double asymbinerr[2][6];
TCanvas *c3=new TCanvas("c3", "c3",0,0,800,600);
for (int nregion=0; nregion<2; nregion++){//mbin
	for (int nebin=0; nebin<6; nebin++){//zbin
	average(asy_fill[0][nregion][nebin],asy_fill[1][nregion][nebin],asyerr_fill[0][nregion][nebin],asyerr_fill[1][nregion][nebin], asymbin[nregion][nebin],asymbinerr[nregion][nebin]);
      }
 }             
	for (int nebin=0; nebin<6; nebin++){//zbin
	//	cout<<"e="<<nebin<<" m01="<<asymbin[0][nebin]<<" m02= "<< asymbin[1][nebin]<<endl;
	}
for (int nregion=0; nregion<2; nregion++){//mbin
   AnvsMass[nregion]=new TGraphErrors(nebins,xf,asymbin[nregion],ex,asymbinerr[nregion]);
   AnvsMass[nregion]->SetMarkerStyle(20+nregion*4);;
//  AnvsMass[nregion]->Draw("APsame");
}
c3->cd();
	TH2F*  bkgm15 = new TH2F("bkgm15","",20,0.3,1,22,-0.002,0.002);
    bkgm15->GetXaxis()->SetTitle("z_{em}");;
    bkgm15->GetYaxis()->SetTitle("A_{UT}");;
	bkgm15->Draw();
   AnvsMass[0]->Draw("Psame");
   AnvsMass[1]->Draw("Psame");
   AnvsMass[0]->SetMarkerColor(kBlue);;
   AnvsMass[1]->SetMarkerColor(kRed);;
   AnvsMass[0]->SetLineColor(kBlue);;
   AnvsMass[1]->SetLineColor(kRed);;
TLegend *leg4=new TLegend(0.5,0.70,0.88,0.88);
                leg4->SetMargin(0.2);
                leg4->SetBorderSize(0);
                leg4->SetFillColor(0);
                leg4->SetTextSize(0.04);
                leg4->AddEntry( AnvsMass[0],"M<0.2 GeV","PE");
                leg4->AddEntry( AnvsMass[1],"0.2<M<0.3 GeV","PE");
leg4->Draw();
                
   AnvsMass15[0] =  (TGraphErrors*)AnvsMass[0]->Clone();
   AnvsMass15[1] =  (TGraphErrors*)AnvsMass[1]->Clone();
//   c3->SaveAs("CollinsMass15.png");
 //  c3->Clear();



double asyb01[njtbins][nebins];
double asyb12[njtbins][nebins];// 0.1-0.2 ; asyfill[2-3]
double asyb23[njtbins][nebins];
double asyerrb01[njtbins][nebins];
double asyerrb12[njtbins][nebins];
double asyerrb23[njtbins][nebins];
double asyy01[njtbins][nebins];
double asyy12[njtbins][nebins];
double asyy23[njtbins][nebins];
double asyerry01[njtbins][nebins];
double asyerry12[njtbins][nebins];
double asyerry23[njtbins][nebins];
for (int njtbin=0; njtbin<njtbins; njtbin++){
	for (int nebin=0; nebin<6; nebin++){
//asyf[nebin]=sumasy[3][nebin];
//asyerrf[nebin]=sumerr[3][nebin];
	if (Mset==23){
	average(asy_fill[njtbin][2][nebin],asy_fill[njtbin][3][nebin],asyerr_fill[njtbin][2][nebin],asyerr_fill[njtbin][3][nebin],asyb12[njtbin][nebin],asyerrb12[njtbin][nebin]);
	average(asy_fill[njtbin][4][nebin],asy_fill[njtbin][5][nebin],asy_fill[njtbin][1][nebin],asyerr_fill[njtbin][4][nebin],asyerr_fill[njtbin][5][nebin],asyerr_fill[njtbin][1][nebin],asyb23[njtbin][nebin],asyerrb23[njtbin][nebin]);
	average(asy_fill2[njtbin][2][nebin],asy_fill2[njtbin][3][nebin],asyerr_fill2[njtbin][2][nebin],asyerr_fill2[njtbin][3][nebin],asyy12[njtbin][nebin],asyerry12[njtbin][nebin]);
	average(asy_fill2[njtbin][4][nebin],asy_fill2[njtbin][5][nebin],asy_fill2[njtbin][1][nebin],asyerr_fill2[njtbin][4][nebin],asyerr_fill2[njtbin][5][nebin],asyerr_fill2[njtbin][1][nebin],asyy23[njtbin][nebin],asyerry23[njtbin][nebin]);
	}
	if (Mset==12345){
	average(asy_fill[njtbin][2][nebin],asy_fill[njtbin][3][nebin],asy_fill[njtbin][4][nebin],asy_fill[njtbin][5][nebin],asy_fill[njtbin][1][nebin],asyerr_fill[njtbin][2][nebin],asyerr_fill[njtbin][3][nebin],asyerr_fill[njtbin][4][nebin],asyerr_fill[njtbin][5][nebin],asyerr_fill[njtbin][1][nebin],asyb12[njtbin][nebin],asyerrb12[njtbin][nebin]);
	average(asy_fill2[njtbin][2][nebin],asy_fill2[njtbin][3][nebin],asy_fill2[njtbin][4][nebin],asy_fill2[njtbin][5][nebin],asy_fill2[njtbin][1][nebin],asyerr_fill2[njtbin][2][nebin],asyerr_fill2[njtbin][3][nebin],asyerr_fill2[njtbin][4][nebin],asyerr_fill2[njtbin][5][nebin],asyerr_fill2[njtbin][1][nebin],asyy12[njtbin][nebin],asyerry12[njtbin][nebin]);
	}
	if (Mset==1234){
	average(asy_fill[njtbin][2][nebin],asy_fill[njtbin][3][nebin],asy_fill[njtbin][4][nebin],asy_fill[njtbin][1][nebin],asyerr_fill[njtbin][2][nebin],asyerr_fill[njtbin][3][nebin],asyerr_fill[njtbin][4][nebin],asyerr_fill[njtbin][1][nebin],asyb12[njtbin][nebin],asyerrb12[njtbin][nebin]);
	average(asy_fill2[njtbin][2][nebin],asy_fill2[njtbin][3][nebin],asy_fill2[njtbin][4][nebin],asy_fill2[njtbin][1][nebin],asyerr_fill2[njtbin][2][nebin],asyerr_fill2[njtbin][3][nebin],asyerr_fill2[njtbin][4][nebin],asyerr_fill2[njtbin][1][nebin],asyy12[njtbin][nebin],asyerry12[njtbin][nebin]);
	}
	if (Mset==2345){
	average(asy_fill[njtbin][2][nebin],asy_fill[njtbin][3][nebin],asy_fill[njtbin][4][nebin],asy_fill[njtbin][5][nebin],asyerr_fill[njtbin][2][nebin],asyerr_fill[njtbin][3][nebin],asyerr_fill[njtbin][4][nebin],asyerr_fill[njtbin][5][nebin],asyb12[njtbin][nebin],asyerrb12[njtbin][nebin]);
	average(asy_fill2[njtbin][2][nebin],asy_fill2[njtbin][3][nebin],asy_fill2[njtbin][4][nebin],asy_fill2[njtbin][5][nebin],asyerr_fill2[njtbin][2][nebin],asyerr_fill2[njtbin][3][nebin],asyerr_fill2[njtbin][4][nebin],asyerr_fill2[njtbin][5][nebin],asyy12[njtbin][nebin],asyerry12[njtbin][nebin]);
	}
	if (Mset==1){
	average(asy_fill[njtbin][0][nebin],asy_fill[njtbin][1][nebin],asyerr_fill[njtbin][0][nebin],asyerr_fill[njtbin][1][nebin],asyb12[njtbin][nebin],asyerrb12[njtbin][nebin]);
	average(asy_fill2[njtbin][0][nebin],asy_fill2[njtbin][1][nebin],asyerr_fill2[njtbin][0][nebin],asyerr_fill2[njtbin][1][nebin],asyy12[njtbin][nebin],asyerry12[njtbin][nebin]);
	}
	}
}


 TCanvas *c2 = new TCanvas("c2", "c13",0,0,1200,450);
	c2->Divide(2,1);
 TCanvas *c13 = new TCanvas("c13", "c13",0,0,800,600);

//TGraphErrors *gasyb01=new TGraphErrors(nebins,xf,asyb01,ex,asyerrb01);
TGraphErrors *gasyb12=new TGraphErrors(nebins,xf ,asy_fill[1][0],asyerr_fill[1][0]);// jt mass
TGraphErrors *gasyb23=new TGraphErrors(nebins,xf1,asy_fill[1][1],asyerr_fill[1][1]);// jt mass
//TGraphErrors *gasyy01=new TGraphErrors(nebins,xf,asyy01,ex,asyerry01);
//TGraphErrors *gasyy12=new TGraphErrors(nebins,xf,asyy12,ex,asyerry12);
//TGraphErrors *gasyy23=new TGraphErrors(nebins,xf,asyy23,ex,asyerry23);
//gasy->Draw("ap*");
//gasyb01->SetTitle("Signal m=0.0~0.1");
gasyb12->SetTitle("Signal m=0.05~0.2");
gasyb23->SetTitle("Signal m=0.2~0.3");
gasyb12->SetMarkerStyle(20);
gasyb23->SetMarkerStyle(24);
gasyb12->SetMarkerColor(kBlue);
gasyb23->SetMarkerColor(kRed);
//gasyb01->GetXaxis()->SetTitle("PiE/Gev");
//gasyb01->GetYaxis()->SetTitle("A_{N}");
gasyb12->GetXaxis()->SetTitle("z_{em}");
gasyb12->GetYaxis()->SetTitle("A_{UT}");
gasyb23->GetXaxis()->SetTitle("z_{em}");
gasyb23->GetYaxis()->SetTitle("A_{UT}");
//gasyy01->SetTitle("Signal m=0.0~0.1");
//gasyy12->SetTitle("Signal m=0.1~0.2");
//gasyy23->SetTitle("Signal m=0.2~0.3");
//gasyy01->GetXaxis()->SetTitle("PiE/Gev");
//gasyy01->GetYaxis()->SetTitle("A_{N}");
//gasyy12->GetXaxis()->SetTitle("PiE/Gev");
//gasyy12->GetYaxis()->SetTitle("A_{N}");
//gasyy23->GetXaxis()->SetTitle("PiE/Gev");
//gasyy23->GetYaxis()->SetTitle("A_{N}");
//gasyb12->Draw("alp");
//gasyb23->Draw("apsame");

//c13->Print("CollinsMass.png");


double asybs[njtbins][6];
double asyerrbs[njtbins][6];
double asyerrbs1[njtbins][6];
double asyys[njtbins][6];
double asyerrys[njtbins][6];
double asyerrys1[njtbins][6];
double asybb[njtbins][6];
double asyerrbb[njtbins][6];
double asyerrbb1[njtbins][6];
double asyyb[njtbins][6];
double asyerryb[njtbins][6];
double asyerryb1[njtbins][6];


//double f1[7]={0.694,0.712,0.728,0.732,0.741,0.757,0.792};
//double f2[7]={0.786,0.761,0.748,0.760,0.756,0.718,0.584};

double f1[njtbins][6];//sig in sig
double f2_0[njtbins][6];
double f2[njtbins][6];//bkg in bkg

/*
ifstream frac;
frac.open("frac.txt",ios::in);
for (int i=0 ; i<6 ; i++){
frac>>f1[i]>>f2_0[i];
f2[i]=1-f2_0[i];
}
*/
double asyFinal;
double asyerrFinal;
for (int njtbin=0; njtbin<njtbins; njtbin++){
	for (int nebin=0; nebin<6; nebin++){

	//double f3=(1-f1[nebin])/f2[nebin];
	double f3=0;//no background
	double phiC=1-unsys[nebin]/100;
	
	asybs[njtbin][nebin]=(asyb12[njtbin][nebin])/(1-f3)/pol/phiC;
	asyerrbs[njtbin][nebin]=TMath::Sqrt(asyerrb12[njtbin][nebin]*asyerrb12[njtbin][nebin])/(1-f3)/pol;
	asyys[njtbin][nebin]=(asyy12[njtbin][nebin])/(1-f3)/polY/phiC;
	asyerrys[njtbin][nebin]=TMath::Sqrt(asyerry12[njtbin][nebin]*asyerry12[njtbin][nebin])/(1-f3)/polY;
	//asybb[nebin]=(asyb12[nebin]-asyb23[nebin]/f3)/(1-1/f3)/pol;
	//asyerrbb[nebin]=TMath::Sqrt(asyerrb12[nebin]*asyerrb12[nebin]+asyerrb23[nebin]*asyerrb23[nebin]/f3/f3)/TMath::Abs(1-1/f3)/pol;
	//asyyb[nebin]=(asyy12[nebin]-asyy23[nebin]/f3)/(1-1/f3)/pol;
	//asyerryb[nebin]=TMath::Sqrt(asyerry12[nebin]*asyerry12[nebin]+asyerry23[nebin]*asyerry23[nebin]/f3/f3)/TMath::Abs(1-1/f3)/pol;
	
	//combine with unpol
	//asyerrbs1[nebin]=sqrt(pow(asyerrbs[nebin],2)+pow(unpol*asybs[nebin]/pol/pol,2));
	asyerrbb[njtbin][nebin]=unsys[nebin]/100*asybs[njtbin][nebin];
	asyerryb[njtbin][nebin]=unsys[nebin]/100*asyys[njtbin][nebin];
	//cout<<"asyerrbs="<<asyerrbs[nebin]<<" 2nd="<<unpol*asybs[nebin]/pol/pol<<endl;
//	cout<<"result"<<f3<<" "<<xf[nebin]<<" "<<" asybs= "<<asybs[njtbin][nebin]<<" asyerrbs="<<asyerrbs[njtbin][nebin]<<" asyys= "<<asyys[njtbin][nebin]<<" asyerrys="<<asyerrys[njtbin][nebin]<<" ex="<<ex[nebin] <<endl;
	}
}
/*
AUTre<<"//Run15Collins Jt="<<jtset<<endl;
AUTre<<"double RunAut15Jt"<<jtset<<"[6]={";
for(int ii=0 ; ii<6 ; ii++){
	            AUTre<<asybs[ii]<<", ";   
}
AUTre<<"};"<<endl<<"double Run15ErrJt"<<jtset<<"[6]={";
for(int ii=0 ; ii<6 ; ii++){
	            AUTre<<asyerrbs[ii]<<", ";    
}
AUTre<<"};"<<endl;

*/


    double asybsAll[nebins];
    double asybserrAll[nebins];
    for (int nebin=0; nebin<nebins; nebin++){
    average( asybs[0][nebin], asybs[1][nebin], asyerrbs[0][nebin], asyerrbs[1][nebin],asybsAll[nebin],asybserrAll[nebin]);
	 cout<<nebin<<"  "<<xf15[nebin]<< " "<<asybsAll[nebin]<< " "<<asybserrAll[nebin]<<endl;
    }

    TGraphErrors *gasybs[3];
    TGraphErrors *gasybb[3];
    TGraphErrors *gasybberr[3];
    TGraphErrors *gasybserr[3];
    TGraphErrors *gasyys[3];
    TGraphErrors *gasyyb[3];
    TGraphErrors *gasyyberr[3];
    TGraphErrors *gasyyserr[3];

    for (int i=0 ; i<njtbins ; i++) {
    gasybs[i]=new TGraphErrors(nebins,xf, asybs[i],ex,asyerrbs[i]);//only useful
//    gasybb[i]=new TGraphErrors(nebins,xf, asybb[i],ex,asyerrbb[i]);
//    gasybberr[i]=new TGraphErrors(nebins,xf,asybb[i],ex,asyerrbb1[i]);//x uncertainty
//    gasybserr[i]=new TGraphErrors(nebins,xf,asybs[i],ex,asyerrbs1[i]);

    gasyys[i]=new TGraphErrors(nebins,xf, asyys[i],ex,asyerrys[i]);//only useful
 //   gasyyb[i]=new TGraphErrors(nebins,xf, asyyb[i],ex,asyerryb[i]);
//    gasyyserr[i]=new TGraphErrors(nebins,xf, asyys[i],ex,asyerrys[i]);
//    gasyyberr[i]=new TGraphErrors(nebins,xf, asybb[i],ex,asyerryb1[i]);
    }




TH2F *bkg = new TH2F("bkg15","A_{UT} for #pi^{0} in a jet",20,0.25,1,10,-0.01,0.02);
        bkg->GetXaxis()->SetTitle("Z_{em}");
        bkg->GetYaxis()->SetTitle("A_{UT}");
        bkg->GetXaxis()->CenterTitle(true);;
        bkg->GetYaxis()->CenterTitle(true);;
        bkg->GetYaxis()->SetTitleSize(0.04);;

TH2F *bkg2 = new TH2F("bkg152","A_{UT} for #pi^{0} in a jet",20,0.25,1,10,-0.01,0.02);
        bkg2->GetXaxis()->SetTitle("Z_{em}");
        bkg2->GetYaxis()->SetTitle("A_{UT}");
        bkg2->GetXaxis()->CenterTitle(true);;
        bkg2->GetYaxis()->CenterTitle(true);;
        bkg2->GetYaxis()->SetTitleSize(0.04);;

  c2->cd(1);
  bkg->Draw();

   for (int i=0 ; i<njtbins ; i++) {
    gasybs[i]->SetMarkerStyle(20+i*4);
    gasybs[i]->SetMarkerSize(1.3);
    gasybs[i]->SetMarkerColor(kBlue);
    gasybs[i]->SetLineWidth(2);
    gasybs[i]->SetLineColor(kBlue);
    gasybs[i]->Draw("psame");
    gasybs[i]->GetXaxis()->SetTitle("PiE/Gev");
    gasybs[i]->GetYaxis()->SetTitle("A_{N} xf>0");
/*
    gasybserr[i]->SetMarkerStyle(3);
    gasybserr[i]->SetMarkerSize(1.3);
    gasybserr[i]->SetMarkerColor(kBlue);
    gasybserr[i]->SetLineWidth(2);
    gasybserr[i]->SetLineColor(kBlue);
 //   gasybserr[i]->Draw("p2");
    gasybserr[i]->GetXaxis()->SetTitle("PiE/Gev");
    gasybserr[i]->GetYaxis()->SetTitle("A_{N} xf>0");
    gasybserr[i]->SetFillColor(kBlack);
    gasybserr[i]->SetFillStyle(3144);

    gasybb[i]->SetMarkerStyle(4);
    gasybb[i]->SetMarkerSize(1.3);
    gasybb[i]->SetMarkerColor(kGreen+3);
    gasybb[i]->SetLineWidth(2);
    gasybb[i]->SetLineColor(kGreen+3);
  //  gasybb[i]->Draw("p");
    gasybb[i]->GetXaxis()->SetTitle("PiE/Gev");
    gasybb[i]->GetYaxis()->SetTitle("A_{N} bkg");

    gasybberr[i]->SetMarkerStyle(4);
    gasybberr[i]->SetMarkerSize(1.3);
    gasybberr[i]->SetMarkerColor(kGreen+3);
    gasybberr[i]->SetLineWidth(2);
    gasybberr[i]->SetLineColor(kGreen+3);
  //  gasybberr[i]->Draw("p2");
    gasybberr[i]->GetXaxis()->SetTitle("PiE/Gev");
    gasybberr[i]->GetYaxis()->SetTitle("A_{N} bkg");
    gasybberr[i]->SetFillColor(kBlack);
    gasybberr[i]->SetFillStyle(3144);
*/
    }



TLegend *leg=new TLegend(0.48,0.7,0.78,0.88);
                leg->SetMargin(0.5);
                leg->SetBorderSize(0);
                leg->SetFillColor(0);
                leg->SetTextSize(0.03);
                  leg->AddEntry(gasybs[0],"j_{T} < 0.2 GeV, x_{F}>0","PE");
                  leg->AddEntry(gasybs[1],"j_{T} > 0.2 GeV, x_{F}>0","PE");
leg->Draw();

 TLatex l;
     l.SetTextSize(0.03);
	 l.SetTextAngle(0.);
	 l.DrawLatex(0.3,0.008,"3.0% beam pol. scale uncertainty not shown");
double dx=0.3; double dy=0.018;
	l.DrawLatex(dx,dy-0.000,"p^{#uparrow} + p -> EM-jet + #pi^{0}+X @ #sqrt{s}=200 GeV");
	l.DrawLatex(dx,dy-0.0025,"Jet algorithm: anti-kT R=0.7 ");
    l.DrawLatex(dx,dy-0.005," Jet p_{T} > 2 GeV");
    l.DrawLatex(dx,dy-0.0075,"2.9< #eta_{jet} <3.8, 2.7< #eta_{#pi^{0}} <4.0 ");



        c2->cd(2);
		
            bkg2->Draw();
	 l.DrawLatex(0.3,0.008,"3.0% beam pol. scale uncertainty not shown");


    for (int i=0 ; i<njtbins ; i++) {
    gasyys[i]->SetMarkerStyle(20+i*4);
    gasyys[i]->SetMarkerSize(1.3);
    gasyys[i]->SetMarkerColor(kMagenta);
    gasyys[i]->SetLineWidth(2);
    gasyys[i]->SetLineColor(kMagenta);
    gasyys[i]->Draw("psame");
    gasyys[i]->GetXaxis()->SetTitle("PiE/Gev");
    gasyys[i]->GetYaxis()->SetTitle("A_{N} xf>0");
/*
    gasyyserr[i]->SetMarkerStyle(3);
    gasyyserr[i]->SetMarkerSize(1.3);
    gasyyserr[i]->SetMarkerColor(kBlue);
    gasyyserr[i]->SetLineWidth(2);
    gasyyserr[i]->SetLineColor(kBlue);
//    gasyyserr[i]->Draw("p2");
    gasyyserr[i]->GetXaxis()->SetTitle("PiE/Gev");
    gasyyserr[i]->GetYaxis()->SetTitle("A_{N} xf>0");
    gasyyserr[i]->SetFillColor(kBlack);
    gasyyserr[i]->SetFillStyle(3144);

    gasyyb[i]->SetMarkerStyle(4);
    gasyyb[i]->SetMarkerSize(1.3);
    gasyyb[i]->SetMarkerColor(kGreen+3);
    gasyyb[i]->SetLineWidth(2);
    gasyyb[i]->SetLineColor(kGreen+3);
//    gasyyb[i]->Draw("p");
    gasyyb[i]->GetXaxis()->SetTitle("PiE/Gev");
    gasyyb[i]->GetYaxis()->SetTitle("A_{N} bkg");

    gasyyberr[i]->SetMarkerStyle(4);
    gasyyberr[i]->SetMarkerSize(1.3);
    gasyyberr[i]->SetMarkerColor(kGreen+3);
    gasyyberr[i]->SetLineWidth(2);
    gasyyberr[i]->SetLineColor(kGreen+3);
//    gasyyberr[i]->Draw("p2");
    gasyyberr[i]->GetXaxis()->SetTitle("PiE/Gev");
    gasyyberr[i]->GetYaxis()->SetTitle("A_{N} bkg");
    gasyyberr[i]->SetFillColor(kBlack);
    gasyyberr[i]->SetFillStyle(3144);
	*/
}

    double chi1[6];
    double chisum1=0;
    for (int nebin=0; nebin<6; nebin++){
      chi1[nebin]=pow((asybs[0][nebin]-asybs[1][nebin]),2)/(pow(asyerrbs[0][nebin],2)+pow(asyerrbs[1][nebin],2));
      chisum1 += chi1[nebin];
      cout<< chi1[nebin]<<endl;
    }   
    
      cout<<" chi2=="<< chisum1 << " " <<endl;



TLegend *leg2=new TLegend(0.48,0.7,0.78,0.88);
                leg2->SetMargin(0.5);
                leg2->SetBorderSize(0);
                leg2->SetFillColor(0);
                leg2->SetTextSize(0.03);
                  leg2->AddEntry(gasyys[0],"j_{T} < 0.2 GeV, x_{f}<0","PE");
                  leg2->AddEntry(gasyys[1],"j_{T} > 0.2 GeV, x_{f}<0","PE");
leg2->Draw();



//c2->SaveAs(Form("DrawCollRun15.png",Mset));
    gasybs[2]=new TGraphErrors(nebins,xf, asybsAll,ex,asybserrAll);

   gjetAn15 =  (TGraphErrors*)gasybs[2]->Clone();




//c2->SaveAs(Form("digitRun15AUTJt%dMBin%d.C",jtset,Mset));
//gasyb01->Write();
/*gasyb12->Write();
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


drawColl11(int  Mset=12345){
		gROOT->SetStyle("Modern");
	gStyle->SetOptStat(0000);
	gStyle->SetOptFit(1111);//0000);
        gStyle->SetStatColor(0);
      //  gStyle->SetEndErrorSize(1);
        gStyle->SetOptDate(0);
        gStyle->SetStatFont(42);
        gStyle->SetStatW(0.13);
        gStyle->SetStatH(0.13);
        gStyle->SetStatX(1.0);
        gStyle->SetStatY(1.0);
        gStyle->SetTitleXOffset(1.0); 
        gStyle->SetTitleYOffset(1.1); 
        gStyle->SetHistLineWidth(2);; 
        gStyle->SetTitleSize(0.04);;  
	 gStyle->SetTitleFont(62,"xyz");;
double pol=0.5249;
 double polY=0.5117;


//fstream AUTre("AUTre",ios::app|ios::out);
ifstream filllist;
filllist.open("Run11filllist");
const int nfills=29;// how many fill are being used
int fillnum[nfills];
double fillex[nfills];
double filldouble[nfills];
int fillbin=nfills;
for (int nfill=0; nfill<nfills; nfill++){
    filllist>>fillnum[nfill];
    fillex[nfill]=0;
    filldouble[nfill] = double(nfill+1);
//	cout<<fillnum[nfill];
}

auto mg = new TMultiGraph("mg","mg"); 
double ebinlows[6] = {0.3, 0.4, 0.5, 0.6, 0.7, 0.8};
double ebinhighs[6] ={0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
const int nebins = 6;
const int nmbins = 2;
double mbinlows[nmbins] = {0.00, 0.20};
double mbinhighs[nmbins] = {0.20, 0.30};
double jtbinlows[2] = {0.00, 0.20};
double jtbinhighs[2] = {0.20, 9.99};
const int njtbins = 2;
char resultname[200];
char resultname2[200];
char picname[200];
char picname2[200];
double ex0[njtbins][6];
double ex[6];
double ex1[6];
double xf[6];//z_em after  correction
double xf1[6];
double xf2[6];

double unz[6] = {0.016,0.021,0.026,0.030,0.035,0.040};//z_em  uncertainty
double unpol=0.00;
//double unsys[6]={3.5, 4.5 , 6 , 8, 12.6, 27};
double unsys[6]={1., 1.1 , 1.4 , 2.1, 2.5, 3.9};//position uncertainty// as correction now


for (int nebin=0; nebin<6; nebin++){
//xf[nebin]= (ebinlows[nebin]+ebinhighs[nebin])/2.0; //    !!!!!!!!!!type change!!!!!!!!!!
//xf[nebin]=( (ebinlows[nebin]+ebinhighs[nebin])/2-0.0)/250;
xf1[nebin]=( (ebinlows[nebin]+ebinhighs[nebin])/2-0.01);
xf2[nebin]=( (ebinlows[nebin]+ebinhighs[nebin])/2+0.01);
//ex[nebin]=unz[nebin];
ex[nebin]=xf[nebin]*Rsyst;
ex1[nebin]=0.01;
xf[nebin]=xf11[nebin];

//out<< xf[nebin]<<" " << xf1[nebin]<<end
}
ifstream result;
ifstream result2;

TF1 *fcn1 = new TF1 ("fcn1","pol0",0,60);
TF1 *fcn2 = new TF1 ("fcn2","pol0",0,60);

double sumasy[6][6];
double sumerr[6][6];

//TFile *fout= new TFile ("DrawColl11.root","recreate");
//fout->cd();
double asy_fill[njtbins][6][6];
double asyerr_fill[njtbins][6][6];
double asy_fill2[njtbins][6][6];
double asyerr_fill2[njtbins][6][6];
for (int njtbin=0; njtbin<njtbins;njtbin++){
	for (int nmbin=0; nmbin<nmbins;nmbin++){
   		for (int nebin=0; nebin<6; nebin++){
/*	 fill[15]=-9;
	 ene[15]=-9.;
	 asy[15]=-9.;
	 asyerr[15]=-9.;
	 ml[15]=-9.;
	 mh[15]=-9.;
	 p0[15]=-9.;
	 p0e[15]=-9.;
*/
	int fill[nfills];
	double ene[nfills];
	double asy[nfills];
	double asy2[nfills];
	double asyerr[nfills];
	double asyerr2[nfills];
	double ml[nfills];
	double mh[nfills];
	double p0[nfills];
	double p0e[nfills];
	double p02[nfills];
	double p0e2[nfills];
		for (int nfill=0; nfill<nfills;nfill++){
		sprintf(resultname,"/star/u/zwzhu/01zwzhu/ana/New/PaperCode/Code2/Run11/result/Collins2/Collins_Fill_%d_mass%.2fto%.2fGeV_Z%.1fto%.1f_Jt%.2fto%.2fGeV_AllTrigger.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin],jtbinlows[njtbin],jtbinhighs[njtbin]);
		sprintf(resultname2,"/star/u/zwzhu/01zwzhu/ana/New/PaperCode/Code2/Run11/result/Collins2/Collinsy_Fill%d_mass%.2fto%.2fGeV_Z%.1fto%.1f_Jt%.2fto%.2fGeV_AllTrigger.txt",fillnum[nfill],mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin],jtbinlows[njtbin],jtbinhighs[njtbin]);
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
//		sumasy[nmbin][nebin] += asy[nfill];
//		sumerr[nmbin][nebin] += asyerr[nfill]*asyerr[nfill];	
		}	
		
	//	sprintf(picname,"./UpNorthDownNorth/count/pic/crAnvsxF_mass%.2fto%.2fGeV_Z%.2fto%.2fGeV_AllTrigger.png",mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
	//	sprintf(picname2,"./UpNorthDownNorth/ycount/pic/crAnvsxF_mass%.2fto%.2fGeV_Z%.2fto%.2fGeV_AllTrigger.png",mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
		sprintf(picname,"./count/pic/crAnvsxF_mass%.2fto%.2fGeV_Z%.2fto%.2fGeV_AllTrigger.png",mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
		sprintf(picname2,"./ycount/pic/crAnvsxF_mass%.2fto%.2fGeV_Z%.2fto%.2fGeV_AllTrigger.png",mbinlows[nmbin],mbinhighs[nmbin],ebinlows[nebin],ebinhighs[nebin]);
		TGraphErrors *forfit=new TGraphErrors(fillbin,filldouble,asy,fillex,asyerr);
		TGraphErrors *forfit2=new TGraphErrors(fillbin,filldouble,asy2,fillex,asyerr2);
		forfit->Fit("fcn1","RQ");
		asy_fill[njtbin][nmbin][nebin]=fcn1->GetParameter(0);
		asyerr_fill[njtbin][nmbin][nebin]=fcn1->GetParError(0);
		forfit2->Fit("fcn2","RQ");
		asy_fill2[njtbin][nmbin][nebin]=fcn2->GetParameter(0);
		asyerr_fill2[njtbin][nmbin][nebin]=fcn2->GetParError(0);
	//		cout<<asy_fill[nmbin][nebin]<<" "<<asyerr_fill[nmbin][nebin]<<" "<<endl;
	// TCanvas *c1 = new TCanvas("c1", "c1",0,0,1500,900);
				 forfit->SetTitle(picname);
				 forfit->SetLineWidth(3);
				 forfit->SetLineColor(4);
				 forfit->SetMarkerSize(3);
                                forfit->GetXaxis()->SetTitle("Fill number");
                                forfit->GetYaxis()->SetTitle("A_{N}");
                                forfit2->SetTitle(picname2);
                                forfit2->GetXaxis()->SetTitle("Fill number");
                                forfit2->GetYaxis()->SetTitle("A_{N}");
        if(updateplot){
            forfit->Draw("AP*");
            c1->SaveAs(picname);
            c1->Clear();
            forfit2->Draw("AP*");
            c1->SaveAs(picname2);
		}
		}
	}
}	

//mass-dependant

TGraphErrors * AnvsMass[2];
double asymbin[2][6];
double asymbinerr[2][6];
TCanvas *c33=new TCanvas("c33", "c3",0,0,800,600);
for (int nregion=0; nregion<2; nregion++){//mbin
	for (int nebin=0; nebin<6; nebin++){//zbin
	average(asy_fill[0][nregion][nebin],asy_fill[1][nregion][nebin],asyerr_fill[0][nregion][nebin],asyerr_fill[1][nregion][nebin], asymbin[nregion][nebin],asymbinerr[nregion][nebin]);
      }
	for (int nebin=0; nebin<6; nebin++){//zbin
	//	cout<<"e="<<nebin<<" m01="<<asymbin[0][nebin]<<" m02= "<< asymbin[1][nebin]<<endl;
	}

 }             
for (int nregion=0; nregion<2; nregion++){//mbin
   AnvsMass[nregion]=new TGraphErrors(nebins,xf,asymbin[nregion],ex,asymbinerr[nregion]);
   AnvsMass[nregion]->SetMarkerStyle(20+nregion*4);;
//  AnvsMass[nregion]->Draw("APsame");
}
c33->cd();
	TH2F*  bkgm11 = new TH2F("bkgm11","",20,0.3,1,22,-0.004,0.004);
	bkgm11->Draw();
    bkgm11->GetXaxis()->SetTitle("z_{em}");;
    bkgm11->GetYaxis()->SetTitle("A_{UT}");;
   AnvsMass[0]->Draw("Psame");
   AnvsMass[1]->Draw("Psame");
   AnvsMass[0]->SetMarkerColor(kBlue);;
   AnvsMass[1]->SetMarkerColor(kRed);;
   AnvsMass[0]->SetLineColor(kBlue);;
   AnvsMass[1]->SetLineColor(kRed);;
TLegend *leg=new TLegend(0.6,0.70,0.88,0.88);
                leg->SetMargin(0.2);
                leg->SetBorderSize(0);
                leg->SetFillColor(0);
                leg->SetTextSize(0.04);
                leg->AddEntry( AnvsMass[0],"M<0.2 GeV","PE");
                leg->AddEntry( AnvsMass[1],"0.2<M<0.3 GeV","PE");
leg->Draw();
   AnvsMass11[0] =  (TGraphErrors*)AnvsMass[0]->Clone();
   AnvsMass11[1] =  (TGraphErrors*)AnvsMass[1]->Clone();
                
//   c33->SaveAs("CollinsMass11.png");

/*
TGraphErrors * AnvsMass[6];
double asymbin[6];
double asymbinerr[6];
double xf4[6]={0.025,0.075,0.125,0.175,0.225,0.275};
TCanvas *c3=new TCanvas("c3", "c3",0,0,600,450);
;
for (int nebin=0; nebin<6; nebin++){//zbin
      for (int nregion=1; nregion<6; nregion++){//mbin
	asymbin[nregion]=asy_fill[nregion][nebin];
		cout<<"mbin"<<asymbin[nregion]<<endl;
	asymbinerr[nregion]=asyerr_fill[nregion][nebin];
      }
	asymbin[0]=0;

   AnvsMass[nebin]=new TGraphErrors(nebins,xf4,asymbin,ex,asymbinerr);
   AnvsMass[nebin]->GetXaxis()->SetTitle("Mass/GeV");;
   AnvsMass[nebin]->GetYaxis()->SetTitle("A_UT");;
   sprintf(picname1,"./count/pic/AnvsMass_Z%.1fto%.1f.png",ebinlows[nebin],ebinhighs[nebin]);
   AnvsMass[nebin]->SetTitle(picname1);;
   AnvsMass[nebin]->Draw("AP*");
   c3->SaveAs(picname1);
   c3->Clear();
 }             
                
*/

double asyb01[njtbins][nebins];
double asyb12[njtbins][nebins];// 0.1-0.2 ; asyfill[2-3]
double asyb23[njtbins][nebins];
double asyerrb01[njtbins][nebins];
double asyerrb12[njtbins][nebins];
double asyerrb23[njtbins][nebins];
double asyy01[njtbins][nebins];
double asyy12[njtbins][nebins];
double asyy23[njtbins][nebins];
double asyerry01[njtbins][nebins];
double asyerry12[njtbins][nebins];
double asyerry23[njtbins][nebins];
for (int njtbin=0; njtbin<njtbins; njtbin++){
	for (int nebin=0; nebin<6; nebin++){
//asyf[nebin]=sumasy[3][nebin];
//asyerrf[nebin]=sumerr[3][nebin];
	if (Mset==23){
	average(asy_fill[njtbin][2][nebin],asy_fill[njtbin][3][nebin],asyerr_fill[njtbin][2][nebin],asyerr_fill[njtbin][3][nebin],asyb12[njtbin][nebin],asyerrb12[njtbin][nebin]);
	average(asy_fill[njtbin][4][nebin],asy_fill[njtbin][5][nebin],asy_fill[njtbin][1][nebin],asyerr_fill[njtbin][4][nebin],asyerr_fill[njtbin][5][nebin],asyerr_fill[njtbin][1][nebin],asyb23[njtbin][nebin],asyerrb23[njtbin][nebin]);
	average(asy_fill2[njtbin][2][nebin],asy_fill2[njtbin][3][nebin],asyerr_fill2[njtbin][2][nebin],asyerr_fill2[njtbin][3][nebin],asyy12[njtbin][nebin],asyerry12[njtbin][nebin]);
	average(asy_fill2[njtbin][4][nebin],asy_fill2[njtbin][5][nebin],asy_fill2[njtbin][1][nebin],asyerr_fill2[njtbin][4][nebin],asyerr_fill2[njtbin][5][nebin],asyerr_fill2[njtbin][1][nebin],asyy23[njtbin][nebin],asyerry23[njtbin][nebin]);
	}
	if (Mset==12345){
	average(asy_fill[njtbin][2][nebin],asy_fill[njtbin][3][nebin],asy_fill[njtbin][4][nebin],asy_fill[njtbin][5][nebin],asy_fill[njtbin][1][nebin],asyerr_fill[njtbin][2][nebin],asyerr_fill[njtbin][3][nebin],asyerr_fill[njtbin][4][nebin],asyerr_fill[njtbin][5][nebin],asyerr_fill[njtbin][1][nebin],asyb12[njtbin][nebin],asyerrb12[njtbin][nebin]);
	average(asy_fill2[njtbin][2][nebin],asy_fill2[njtbin][3][nebin],asy_fill2[njtbin][4][nebin],asy_fill2[njtbin][5][nebin],asy_fill2[njtbin][1][nebin],asyerr_fill2[njtbin][2][nebin],asyerr_fill2[njtbin][3][nebin],asyerr_fill2[njtbin][4][nebin],asyerr_fill2[njtbin][5][nebin],asyerr_fill2[njtbin][1][nebin],asyy12[njtbin][nebin],asyerry12[njtbin][nebin]);
	}
	if (Mset==1234){
	average(asy_fill[njtbin][2][nebin],asy_fill[njtbin][3][nebin],asy_fill[njtbin][4][nebin],asy_fill[njtbin][1][nebin],asyerr_fill[njtbin][2][nebin],asyerr_fill[njtbin][3][nebin],asyerr_fill[njtbin][4][nebin],asyerr_fill[njtbin][1][nebin],asyb12[njtbin][nebin],asyerrb12[njtbin][nebin]);
	average(asy_fill2[njtbin][2][nebin],asy_fill2[njtbin][3][nebin],asy_fill2[njtbin][4][nebin],asy_fill2[njtbin][1][nebin],asyerr_fill2[njtbin][2][nebin],asyerr_fill2[njtbin][3][nebin],asyerr_fill2[njtbin][4][nebin],asyerr_fill2[njtbin][1][nebin],asyy12[njtbin][nebin],asyerry12[njtbin][nebin]);
	}
	if (Mset==2345){
	average(asy_fill[njtbin][2][nebin],asy_fill[njtbin][3][nebin],asy_fill[njtbin][4][nebin],asy_fill[njtbin][5][nebin],asyerr_fill[njtbin][2][nebin],asyerr_fill[njtbin][3][nebin],asyerr_fill[njtbin][4][nebin],asyerr_fill[njtbin][5][nebin],asyb12[njtbin][nebin],asyerrb12[njtbin][nebin]);
	average(asy_fill2[njtbin][2][nebin],asy_fill2[njtbin][3][nebin],asy_fill2[njtbin][4][nebin],asy_fill2[njtbin][5][nebin],asyerr_fill2[njtbin][2][nebin],asyerr_fill2[njtbin][3][nebin],asyerr_fill2[njtbin][4][nebin],asyerr_fill2[njtbin][5][nebin],asyy12[njtbin][nebin],asyerry12[njtbin][nebin]);
	}
	if (Mset==1){
	average(asy_fill[njtbin][0][nebin],asy_fill[njtbin][1][nebin],asyerr_fill[njtbin][0][nebin],asyerr_fill[njtbin][1][nebin],asyb12[njtbin][nebin],asyerrb12[njtbin][nebin]);
	average(asy_fill2[njtbin][0][nebin],asy_fill2[njtbin][1][nebin],asyerr_fill2[njtbin][0][nebin],asyerr_fill2[njtbin][1][nebin],asyy12[njtbin][nebin],asyerry12[njtbin][nebin]);
	}
	}
}

// TCanvas *c1 = new TCanvas("c1", "c1",0,0,1200,900);
 TCanvas *c2 = new TCanvas("c2", "c2",0,0,1200,450);
        c2->SetGrid(0,0);
        c2->Divide(2,1);
/*
//TGraphErrors *gasyb01=new TGraphErrors(nebins,xf,asyb01,ex,asyerrb01);
TGraphErrors *gasyb12=new TGraphErrors(nebins,xf,asyb12,ex,asyerrb12);
TGraphErrors *gasyb23=new TGraphErrors(nebins,xf,asyb23,ex,asyerrb23);
//TGraphErrors *gasyy01=new TGraphErrors(nebins,xf,asyy01,ex,asyerry01);
TGraphErrors *gasyy12=new TGraphErrors(nebins,xf,asyy12,ex,asyerry12);
TGraphErrors *gasyy23=new TGraphErrors(nebins,xf,asyy23,ex,asyerry23);
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
double asybs[njtbins][6];
double asyerrbs[njtbins][6];
double asyerrbs1[njtbins][6];
double asyys[njtbins][6];
double asyerrys[njtbins][6];
double asyerrys1[njtbins][6];
double asybb[njtbins][6];
double asyerrbb[njtbins][6];
double asyerrbb1[njtbins][6];
double asyyb[njtbins][6];
double asyerryb[njtbins][6];
double asyerryb1[njtbins][6];
//double f1[7]={0.694,0.712,0.728,0.732,0.741,0.757,0.792};
//double f2[7]={0.786,0.761,0.748,0.760,0.756,0.718,0.584};

double f1[njtbins][6];//sig in sig
double f2_0[njtbins][6];
double f2[njtbins][6];//bkg in bkg

/*
ifstream frac;
frac.open("frac.txt",ios::in);
for (int i=0 ; i<6 ; i++){
frac>>f1[i]>>f2_0[i];
f2[i]=1-f2_0[i];
}
*/
double asyFinal;
double asyerrFinal;
for (int njtbin=0; njtbin<njtbins; njtbin++){
	for (int nebin=0; nebin<6; nebin++){

	//double f3=(1-f1[nebin])/f2[nebin];
	double f3=0;//no background
	double phiC=1-unsys[nebin]/100;
	
	asybs[njtbin][nebin]=(asyb12[njtbin][nebin])/(1-f3)/pol/phiC;
	asyerrbs[njtbin][nebin]=TMath::Sqrt(asyerrb12[njtbin][nebin]*asyerrb12[njtbin][nebin])/(1-f3)/pol;
	asyys[njtbin][nebin]=(asyy12[njtbin][nebin])/(1-f3)/polY/phiC;
	asyerrys[njtbin][nebin]=TMath::Sqrt(asyerry12[njtbin][nebin]*asyerry12[njtbin][nebin])/(1-f3)/polY;
	//asybb[nebin]=(asyb12[nebin]-asyb23[nebin]/f3)/(1-1/f3)/pol;
	//asyerrbb[nebin]=TMath::Sqrt(asyerrb12[nebin]*asyerrb12[nebin]+asyerrb23[nebin]*asyerrb23[nebin]/f3/f3)/TMath::Abs(1-1/f3)/pol;
	//asyyb[nebin]=(asyy12[nebin]-asyy23[nebin]/f3)/(1-1/f3)/pol;
	//asyerryb[nebin]=TMath::Sqrt(asyerry12[nebin]*asyerry12[nebin]+asyerry23[nebin]*asyerry23[nebin]/f3/f3)/TMath::Abs(1-1/f3)/pol;
	
	//combine with unpol
	//asyerrbs1[nebin]=sqrt(pow(asyerrbs[nebin],2)+pow(unpol*asybs[nebin]/pol/pol,2));
	asyerrbb[njtbin][nebin]=unsys[nebin]/100*asybs[njtbin][nebin];
	asyerryb[njtbin][nebin]=unsys[nebin]/100*asyys[njtbin][nebin];
	//cout<<"result"<<f3<<" "<<xf[nebin]<<" "<<xf1[nebin]<<" asybs= "<<asybs[njtbin][nebin]<<" asyerrbs="<<asyerrbs[njtbin][nebin]<<" asyys= "<<asyys[njtbin][nebin]<<" asyerrys="<<asyerrys[njtbin][nebin]<<" ex="<<ex[nebin] <<endl;
	}
}

/*
AUTre<<"//Run11Collins Jt="<<jtset<<endl;
AUTre<<"double RunAut11Jt"<<jtset<<"[6]={";
for(int ii=0 ; ii<6 ; ii++){
	        AUTre<<asybs[ii]<<", ";   
}
AUTre<<"};"<<endl<<"double Run11ErrJt"<<jtset<<"[6]={";
for(int ii=0 ; ii<6 ; ii++){
	        AUTre<<asyerrbs[ii]<<", ";    
}
AUTre<<"};"<<endl;
*/

    double asybsAll[nebins];
    double asybserrAll[nebins];
    for (int nebin=0; nebin<nebins; nebin++){
    average( asybs[0][nebin], asybs[1][nebin], asyerrbs[0][nebin], asyerrbs[1][nebin],asybsAll[nebin],asybserrAll[nebin]);
	 cout<<nebin<<" "<<xf11[nebin]<< " "<<asybsAll[nebin]<< " "<<asybserrAll[nebin]<<endl;
    }

    TGraphErrors *gasybs[3];
    TGraphErrors *gasybb[3];
    TGraphErrors *gasybberr[3];
    TGraphErrors *gasybserr[3];
    TGraphErrors *gasyys[3];
    TGraphErrors *gasyyb[3];
    TGraphErrors *gasyyberr[3];
    TGraphErrors *gasyyserr[3];

    for (int i=0 ; i<njtbins ; i++) {

    gasybs[i]=new TGraphErrors(nebins,xf, asybs[i],ex,asyerrbs[i]);//only useful
//    gasybb[i]=new TGraphErrors(nebins,xf, asybb[i],ex,asyerrbb[i]);
//    gasybberr[i]=new TGraphErrors(nebins,xf,asybb[i],ex,asyerrbb1[i]);//x uncertainty
//    gasybserr[i]=new TGraphErrors(nebins,xf,asybs[i],ex,asyerrbs1[i]);

    gasyys[i]=new TGraphErrors(nebins,xf, asyys[i],ex,asyerrys[i]);//only useful
//    gasyyb[i]=new TGraphErrors(nebins,xf, asyyb[i],ex,asyerryb[i]);
//    gasyyserr[i]=new TGraphErrors(nebins,xf, asyys[i],ex,asyerrys[i]);
//    gasyyberr[i]=new TGraphErrors(nebins,xf, asybb[i],ex,asyerryb1[i]);

    }



TH2F *bkg = new TH2F("bkg","",20,0.25,1,10,-0.01,0.02);
        bkg->GetXaxis()->SetTitle("Z_{em}");
        bkg->GetYaxis()->SetTitle("A_{UT}");
        bkg->GetXaxis()->CenterTitle(true);;
        bkg->GetYaxis()->CenterTitle(true);;
        bkg->GetYaxis()->SetTitleSize(0.04);;
TH2F *bkg2 = new TH2F("bkg2","",20,0.25,1,10,-0.01,0.02);
        bkg2->GetXaxis()->SetTitle("Z_{em}");
        bkg2->GetYaxis()->SetTitle("A_{UT}");
        bkg2->GetXaxis()->CenterTitle(true);;
        bkg2->GetYaxis()->CenterTitle(true);;
        bkg2->GetYaxis()->SetTitleSize(0.04);;

  c2->cd(1);
  bkg->Draw();

   for (int i=0 ; i<njtbins ; i++) {
    gasybs[i]->SetMarkerStyle(20+i*4);
    gasybs[i]->SetMarkerSize(1.3);
    gasybs[i]->SetMarkerColor(kBlue);
    gasybs[i]->SetLineWidth(2);
    gasybs[i]->SetLineColor(kBlue);
    gasybs[i]->Draw("psame");
    gasybs[i]->GetXaxis()->SetTitle("PiE/Gev");
    gasybs[i]->GetYaxis()->SetTitle("A_{N} xf>0");
/*
    gasybserr[i]->SetMarkerStyle(3);
    gasybserr[i]->SetMarkerSize(1.3);
    gasybserr[i]->SetMarkerColor(kBlue);
    gasybserr[i]->SetLineWidth(2);
    gasybserr[i]->SetLineColor(kBlue);
 //   gasybserr[i]->Draw("p2");
    gasybserr[i]->GetXaxis()->SetTitle("PiE/Gev");
    gasybserr[i]->GetYaxis()->SetTitle("A_{N} xf>0");
    gasybserr[i]->SetFillColor(kBlack);
    gasybserr[i]->SetFillStyle(3144);

    gasybb[i]->SetMarkerStyle(4);
    gasybb[i]->SetMarkerSize(1.3);
    gasybb[i]->SetMarkerColor(kGreen+3);
    gasybb[i]->SetLineWidth(2);
    gasybb[i]->SetLineColor(kGreen+3);
  //  gasybb[i]->Draw("p");
    gasybb[i]->GetXaxis()->SetTitle("PiE/Gev");
    gasybb[i]->GetYaxis()->SetTitle("A_{N} bkg");

    gasybberr[i]->SetMarkerStyle(4);
    gasybberr[i]->SetMarkerSize(1.3);
    gasybberr[i]->SetMarkerColor(kGreen+3);
    gasybberr[i]->SetLineWidth(2);
    gasybberr[i]->SetLineColor(kGreen+3);
  //  gasybberr[i]->Draw("p2");
    gasybberr[i]->GetXaxis()->SetTitle("PiE/Gev");
    gasybberr[i]->GetYaxis()->SetTitle("A_{N} bkg");
    gasybberr[i]->SetFillColor(kBlack);
    gasybberr[i]->SetFillStyle(3144);
*/
    }

TLegend *leg=new TLegend(0.48,0.8,0.78,0.88);
                leg->SetMargin(0.5);
                leg->SetBorderSize(0);
                leg->SetFillColor(0);
                leg->SetTextSize(0.03);
                  leg->AddEntry(gasybs[0],"j_{T} < 0.2 GeV, x_{f}>0","PE");
                  leg->AddEntry(gasybs[1],"j_{T} > 0.2 GeV, x_{f}>0","PE");
leg->Draw();

 TLatex l;
     l.SetTextSize(0.03);
     l.SetTextAngle(0.);
     l.DrawLatex(0.30,0.008,"3.4% beam pol. scale uncertainty not shown");
double dx=0.3; double dy=0.018;
    l.DrawLatex(dx,dy-0.000,"p^{#uparrow} + p -> EM-jet + #pi^{0}+X @ #sqrt{s}=500 GeV");
    l.DrawLatex(dx,dy-0.0025,"Jet algorithm: anti-kT R=0.7 ");
    l.DrawLatex(dx,dy-0.005, "Jet p_{T} > 2 GeV");
    l.DrawLatex(dx,dy-0.0075,"2.9< #eta_{jet} <3.8, 2.7< #eta_{#pi^{0}} <4.0 ");


		c2->cd(2);
            bkg2->Draw();
     l.DrawLatex(0.30,0.008,"3.4% beam pol. scale uncertainty not shown");


    for (int i=0 ; i<njtbins ; i++) {
    gasyys[i]->SetMarkerStyle(20+i*4);
    gasyys[i]->SetMarkerSize(1.3);
    gasyys[i]->SetMarkerColor(kMagenta);
    gasyys[i]->SetLineWidth(2);
    gasyys[i]->SetLineColor(kMagenta);
    gasyys[i]->Draw("psame");
    gasyys[i]->GetXaxis()->SetTitle("PiE/Gev");
    gasyys[i]->GetYaxis()->SetTitle("A_{N} xf>0");
/*
    gasyyserr[i]->SetMarkerStyle(3);
    gasyyserr[i]->SetMarkerSize(1.3);
    gasyyserr[i]->SetMarkerColor(kBlue);
    gasyyserr[i]->SetLineWidth(2);
    gasyyserr[i]->SetLineColor(kBlue);
//    gasyyserr[i]->Draw("p2");
    gasyyserr[i]->GetXaxis()->SetTitle("PiE/Gev");
    gasyyserr[i]->GetYaxis()->SetTitle("A_{N} xf>0");
    gasyyserr[i]->SetFillColor(kBlack);
    gasyyserr[i]->SetFillStyle(3144);

    gasyyb[i]->SetMarkerStyle(4);
    gasyyb[i]->SetMarkerSize(1.3);
    gasyyb[i]->SetMarkerColor(kGreen+3);
    gasyyb[i]->SetLineWidth(2);
    gasyyb[i]->SetLineColor(kGreen+3);
//    gasyyb[i]->Draw("p");
    gasyyb[i]->GetXaxis()->SetTitle("PiE/Gev");
    gasyyb[i]->GetYaxis()->SetTitle("A_{N} bkg");

    gasyyberr[i]->SetMarkerStyle(4);
    gasyyberr[i]->SetMarkerSize(1.3);
    gasyyberr[i]->SetMarkerColor(kGreen+3);
    gasyyberr[i]->SetLineWidth(2);
    gasyyberr[i]->SetLineColor(kGreen+3);
//    gasyyberr[i]->Draw("p2");
    gasyyberr[i]->GetXaxis()->SetTitle("PiE/Gev");
    gasyyberr[i]->GetYaxis()->SetTitle("A_{N} bkg");
    gasyyberr[i]->SetFillColor(kBlack);
    gasyyberr[i]->SetFillStyle(3144);
  */  }
TLegend *leg2=new TLegend(0.48,0.8,0.78,0.88);
                leg2->SetMargin(0.5);
                leg2->SetBorderSize(0);
                leg2->SetFillColor(0);
                leg2->SetTextSize(0.03);
                  leg2->AddEntry(gasyys[0],"j_{T} < 0.2 GeV, x_{F}<0","PE");
                  leg2->AddEntry(gasyys[1],"j_{T} > 0.2 GeV, x_{F}<0","PE");
leg2->Draw();


//	c2->SaveAs(Form("DrawCollRun11.png",Mset));
    gasybs[2]=new TGraphErrors(nebins,xf, asybsAll,ex,asybserrAll);

   gjetAn11 =  (TGraphErrors*)gasybs[2]->Clone();

/*
//gasyb01->Write();
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
void average(double asy1, double asy2,double asy3,double asy4, double err1, double err2,double err3,double err4, double & asyFinal,double & asyerrFinal){
	asyFinal= (asy1/err1/err1+asy2/err2/err2+asy3/err3/err3+asy4/err4/err4)/(1/err1/err1+1/err2/err2+1/err3/err3+1/err4/err4 );
	asyerrFinal=1/TMath::Sqrt(1/err1/err1+1/err2/err2+1/err3/err3+1/err4/err4);
}
void average(double asy1, double asy2,double asy3,double asy4, double asy5, double err1, double err2,double err3,double err4, double err5,double & asyFinal,double & asyerrFinal){
	asyFinal= (asy1/err1/err1+asy2/err2/err2+asy3/err3/err3+asy4/err4/err4+asy5/err5/err5)/(1/err1/err1+1/err2/err2+1/err3/err3+1/err4/err4+1/err5/err5 );
	asyerrFinal=1/TMath::Sqrt(1/err1/err1+1/err2/err2+1/err3/err3+1/err4/err4+1/err5/err5);
}

