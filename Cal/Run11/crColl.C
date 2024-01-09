#include<fstream>
using namespace std;

//calculate asy. for pi0 side band, used as background asymmetries
//using cross-ratio method with sin(phi) fit
  
  Int_t crColl( Float_t zlow = 0.4, Float_t zhigh = 0.5, Float_t mlow = 0.10, Float_t mhigh = 0.15, Int_t fillnum = 15315, Float_t Jtlow = 0.0 , Float_t Jthigh = 0.2,char* infile="/star/u/zwzhu/01zwzhu/Run11/byfill/ipi0jetcor_stfms_Fill15315.root" ){
	
	gStyle->SetOptFit(1111);
	gStyle->SetOptDate(0);
	TCanvas* c1 = new TCanvas("c1","c1",700,500);
	c1->SetGridx(0);
	c1->SetGridy(0);	
	
	Float_t pietalow = 2.7;
        Float_t pietahigh = 4.0;
	Float_t pizcut = 0.7;
	float ecut=10;
	Float_t Jtmin= Jtlow;
	Float_t Jtmax= Jthigh;
	Char_t filllist[50];
	//energy bin is Z bin now
    Float_t ene = (zlow + zhigh)/2.0;//GeV   
	
	Float_t enew = (zhigh-zlow)/2.0;//GeV. energy window
	
//	sprintf(filllist,"newfilllist_stfms.txt");
//        fstream infile(filllist,ios::in);
//        if(!infile){
//                cout<<filllist<<" doesn't exist!!"<<endl;
//                return -1;
//        }
	
	Char_t resultname[200];
	Char_t resultname2[200];
	sprintf(resultname,"Collins_Fill_%d_mass%.2fto%.2fGeV_Z%.1fto%.1f_Jt%.2fto%.2fGeV_AllTrigger.txt",fillnum,mlow,mhigh,zlow,zhigh,Jtmin,Jtmax);
	sprintf(resultname2,"Collinsy_Fill%d_mass%.2fto%.2fGeV_Z%.1fto%.1f_Jt%.2fto%.2fGeV_AllTrigger.txt",fillnum,mlow,mhigh,zlow,zhigh,Jtmin,Jtmax);
	cout<<"results stored at "<<resultname<<endl;
	TString outfilename(resultname);
	TString outfilename2(resultname2);
	TString mvCmd = TString::Format("touch %s",outfilename.Data());
	fstream ofile(outfilename,ios::out);
	fstream ofile2(outfilename2,ios::out);

	Char_t cutbup[700];
	Char_t cutbdown[700];
	Char_t cutyup[700];
	Char_t cutydown[700];

	Char_t filename[200];
	
	Char_t* bdown = "(spinbit==5||spinbit==6)";
	Char_t* bup = "(spinbit==9||spinbit==10)";
	Char_t* ydown = "(spinbit==5||spinbit==9)";
	Char_t* yup = "(spinbit==10||spinbit==6)";

	Int_t fillnum,fillnum1;
	
	//trigger bits
	Int_t JP2=((0x01)<<10);
        Int_t SmlBd2=((0x01)<<4);
        Int_t LrgBd2=((0x01)<<7);

	Int_t JP=((0x07)<<8);
	Int_t HiTow=(0x03);
	Int_t clbit=((0x03F)<<2);

//	Int_t TrigBitsSelect = JP2;
	Int_t TrigBitsSelect = JP+HiTow+clbit;
        Char_t trigselect[400];
        sprintf(trigselect,"(TrigBits&%d)&&TMath::Abs(vertexzyuxi+0)<68&&CjetEta>2.9&&CjetEta<3.8",TrigBitsSelect);
//sprintf(trigselect,"CjetEta>2.9&&CjetEta<3.8&&TMath::Abs(vertexzyuxi+0)<68&&((TrigBits&%d&&pipt>1.84)||(TrigBits&%d&&pipt>2.875&&(phid1<9.1||phid2<9.1))||(TrigBits&%d&&pipt>2.05&&(phid1>9.1&&phid2>9.1))||(TrigBits&%d&&pipt>0.92)||(TrigBits&%d&&pipt>1.61)||(TrigBits&%d&&pipt>1.72)||(TrigBits&%d&&pipt>2.53))",JP1,JP2,JP2,SmlBd1,SmlBd2,LrgBd1,LrgBd2);
	Char_t htitle[200];
	Char_t htitley[200];
	sprintf(htitle,"   crRawAsyFill%d_Z%.1f_M%.2fto%.2fGeV_Jt%.2fto%.2fGeV_AllTrigger",fillnum,ene,mlow,mhigh,Jtmin,Jtmax);
	sprintf(htitley,"y_crRawAsyFill%d_Z%.1f_M%.2fto%.2fGeV_Jt%.2fto%.2fGeV_AllTrigger",fillnum,ene,mlow,mhigh,Jtmin,Jtmax);
	const int nphibin = 10;//must be even
	TGraphErrors* h1asyphi = new TGraphErrors(0); //A_N vs sin(phi);
	TGraphErrors* h2asyphi = new TGraphErrors(0); //A_N vs sin(phi);
	h1asyphi->SetTitle(htitle);
	h2asyphi->SetTitle(htitley);

//	TH1F* h1asyphi = new TH1F(htitle,htitle,nphibin,-TMath::Pi(),TMath::Pi());
	Double_t totbup[nphibin];
	Double_t totbdown[nphibin];
	for(Int_t i = 0; i < nphibin; i++){
		totbup[i] = totbdown[i] = 0;
	}

	TH1F* h1buphi;//hold up to 30 fills
	TH1F* h1bdphi;
	TH1F* h1yuphi;
	TH1F* h1ydphi;
	TH1F* h1buphiN;//hold up to 30 fills
	TH1F* h1bdphiN;
	TH1F* h1ydphiN;
	TH1F* h1ydphiN;
	TH1F* h1buphiS;//hold up to 30 fills
	TH1F* h1bdphiS;
	TH1F* h1ydphiS;
	TH1F* h1ydphiS;

	Int_t kcnt = 0;
	TChain* t1 = new TChain("tjetcor");
//	sprintf(filename,"/star/data05/scratch/zwzhu/FMSnew/JetAna/byFill/ipi0jetcor_stfms_Fill%d.root",fillnum,fillnum);
	sprintf(filename,"/star/data05/scratch/zwzhu/FMSnew/Run11/byfill/ipi0jetcor_stfms_Fill%d.root",fillnum,fillnum);
//	sprintf(filename,"/star/u/zwzhu/workspace/project/MFMS/Newcode/ipi0jetcor_stfmsAnal_run12098008.root.root",fillnum,fillnum);
//	while(infile>>filename){
//		cout<<"adding file: "<<filename<<endl;
		t1->Add(infile);
//		kcnt++;
//	}
	
		
	Char_t hbutitle[100];
	sprintf(hbutitle,"h1_blueup");
	h1buphi = new TH1F(hbutitle,hbutitle,nphibin,-TMath::Pi(),TMath::Pi());//counts per phi bin
	Char_t hbdtitle[100];
	sprintf(hbdtitle,"h1_bluedown");
	h1bdphi = new TH1F(hbdtitle,hbdtitle,nphibin,-TMath::Pi(),TMath::Pi());
	Char_t hyutitle[100];
	sprintf(hyutitle,"h1_yellup");
	h1yuphi = new TH1F(hyutitle,hyutitle,nphibin,-TMath::Pi(),TMath::Pi());//counts per phi bin
	Char_t hydtitle[100];
	sprintf(hydtitle,"h1_yelldown");
	h1ydphi = new TH1F(hydtitle,hydtitle,nphibin,-TMath::Pi(),TMath::Pi());
	cout<<kcnt<<" file added "<<endl;

/*
	Char_t hbutitleN[100];
	sprintf(hbutitleN,"h1_blueupN");
	h1buphiN = new TH1F(hbutitleN,hbutitleN,nphibin,-TMath::Pi(),TMath::Pi());//counts per phi bin
	Char_t hbdtitleN[100];
	sprintf(hbdtitleN,"h1_bluedownN");
	h1bdphiN = new TH1F(hbdtitleN,hbdtitleN,nphibin,-TMath::Pi(),TMath::Pi());
	Char_t hyutitle[N100];
	sprintf(hyutitleN,"h1_yellupN");
	h1yuphiN = new TH1F(hyutitleN,hyutitleN,nphibin,-TMath::Pi(),TMath::Pi());//counts per phi bin
	Char_t hydtitleN[100];
	sprintf(hydtitleN,"h1_yelldownN");
	h1ydphiN = new TH1F(hydtitleN,hydtitleN,nphibin,-TMath::Pi(),TMath::Pi());

	Char_t hbutitleS[100];
	sprintf(hbutitleS,"h1_blueupS");
	h1buphiS = new TH1F(hbutitleS,hbutitleS,nphibin,-TMath::Pi(),TMath::Pi());//counts per phi bin
	Char_t hbdtitleS[100];
	sprintf(hbdtitleS,"h1_bluedown");
	h1bdphiS = new TH1F(hbdtitleS,hbdtitleS,nphibin,-TMath::Pi(),TMath::Pi());
	Char_t hyutitleS[100];
	sprintf(hyutitleS,"h1_yellupS");
	h1yuphiS = new TH1F(hyutitleS,hyutitleS,nphibin,-TMath::Pi(),TMath::Pi());//counts per phi bin
	Char_t hydtitleS[100];
	sprintf(hydtitleS,"h1_yelldownS");
	h1ydphiS = new TH1F(hydtitleS,hydtitleS,nphibin,-TMath::Pi(),TMath::Pi());

*/
//all pions
	sprintf(cutbup,"pim>%.2f&&pim<%.2f&&TMath::Abs(Zem-%.2f)<%.2f&&piz<%.1f&&pieta>%.1f&&pieta<%.1f&&%s&&%s&&pie>%.2f&&Corr==1&&catagory==1&&CjetPt>2&&Jt<%.1f&&Jt>%.1f&&jetdR>0.04",mlow,mhigh,ene,enew,pizcut,pietalow,pietahigh,bup,trigselect,ecut,Jtmax,Jtmin);
	sprintf(cutbdown,"pim>%.2f&&pim<%.2f&&TMath::Abs(Zem-%.2f)<%.2f&&piz<%.1f&&pieta>%.1f&&pieta<%.1f&&%s&&%s&&pie>%.2f&&Corr==1&&catagory==1&&CjetPt>2&&Jt<%.1f&&Jt>%.1f&&jetdR>0.04",mlow,mhigh,ene,enew,pizcut,pietalow,pietahigh,bdown,trigselect,ecut,Jtmax,Jtmin);
	sprintf(cutyup,"pim>%.2f&&pim<%.2f&&TMath::Abs(Zem-%.2f)<%.2f&&piz<%.1f&&pieta>%.1f&&pieta<%.1f&&%s&&%s&&pie>%.2f&&Corr==1&&catagory==1&&CjetPt>2&&Jt<%.1f&&Jt>%.1f&&jetdR>0.04",mlow,mhigh,ene,enew,pizcut,pietalow,pietahigh,yup,trigselect,ecut,Jtmax,Jtmin);
	sprintf(cutydown,"pim>%.2f&&pim<%.2f&&TMath::Abs(Zem-%.2f)<%.2f&&piz<%.1f&&pieta>%.1f&&pieta<%.1f&&%s&&%s&&pie>%.2f&&Corr==1&&catagory==1&&CjetPt>2&&Jt<%.1f&&Jt>%.1f&&jetdR>0.04",mlow,mhigh,ene,enew,pizcut,pietalow,pietahigh,ydown,trigselect,ecut,Jtmax,Jtmin);

//pion w/o recoil	
/*	sprintf(cutbup,"abs(pie-%.1f)<%f&&abs(pipt-%.3f)<%.3f&&%s&&(ptrecoil<2&&ephnear<2&&ephaway<2)",ene,enew,pt,ptw,bup);
	sprintf(cutbdown,"abs(pie-%.1f)<%f&&abs(pipt-%.3f)<%.3f&&%s&&ptrecoil==-1",ene,enew,pt,ptw,bdown);
	sprintf(cutyup,"abs(pie-%.1f)<%f&&abs(pipt-%.3f)<%.3f&&%s&&ptrecoil==-1",ene,enew,pt,ptw,yup);
	sprintf(cutydown,"abs(pie-%.1f)<%f&&abs(pipt-%.3f)<%.3f&&%s&&ptrecoil==-1",ene,enew,pt,ptw,ydown);
*/	
	cout<<" ============"<<Jtlow<<endl;

//pions with recoil
/*	sprintf(cutbup,"abs(pie-%.1f)<%f&&%s&&(ptrecoil>2||ephnear>2||ephaway>2)",ene,enew,bup);
	sprintf(cutbdown,"abs(pie-%.1f)<%f&&%s&&(ptrecoil>2||ephnear>2||ephaway>2)",ene,enew,bdown);
	sprintf(cutyup,"abs(pie-%.1f)<%f&&%s&&(ptrecoil>2||ephnear>2||ephaway>2)",ene,enew,yup);
	sprintf(cutydown,"abs(pie-%.1f)<%f&&%s&&(ptrecoil>2||ephnear>2||ephaway>2)",ene,enew,ydown);
*/       	

		cout<<"cutbup: "<<cutbup<<endl;
		cout<<"cutbdown: "<<cutbdown<<endl;
	//	cout<<"cutyup: "<<cutyup<<endl;
	//	cout<<"cutydown: "<<cutydown<<endl;
	
// generate cos(phi) distribution for blue up/down, for each fill. With fill-dependent mass window
	//	t1->Project(hbutitle,"cos(Phi)",cutyup); //plot yellow beam asy
	//	t1->Project(hbdtitle,"cos(Phi)",cutydown);
//	t1->Project(hbutitle,"piphi",cutbup); //plot yield sorted by blue beam polarizations
//	t1->Project(hbdtitle,"piphi",cutbdown);
	t1->Project(hbutitle,"phiC",cutbup); //plot yield sorted by blue beam polarizations
	t1->Project(hbdtitle,"phiC",cutbdown);
	t1->Project(hyutitle,"yphiC",cutyup); //plot yield sorted by blue beam polarizations
	t1->Project(hydtitle,"yphiC",cutydown);

//calculate raw cross-ratio asymmetry vs sin(phi)
	Double_t rawasybin,rawasybinerr;
	Double_t bdemon; //denominator
	for(Int_t ibin = 1; ibin <= nphibin/2; ibin++){
		totbup[ibin-1] = TMath::Max(h1buphi->GetBinContent(ibin),0.);//blue up at phi
		totbdown[ibin-1+nphibin/2] = TMath::Max(h1bdphi->GetBinContent(ibin+nphibin/2),0.);//blue down at phi+pi
		totbup[ibin-1+nphibin/2] = TMath::Max(h1buphi->GetBinContent(ibin+nphibin/2),0.);//blue up at phi+pi		
		totbdown[ibin-1] = TMath::Max(h1bdphi->GetBinContent(ibin),0.);//blue down at phi
		cout<<" totbup "<< totbup[ibin-1] <<" totbdown "<<totbdown[ibin-1+nphibin/2]<<" totbup "<<totbup[ibin-1+nphibin/2]<<" totbdown "<<totbdown[ibin-1]<<endl;
		//calculate cross-ratio asy. for this particular phi bin
		bdemon = TMath::Sqrt(totbup[ibin-1]*totbdown[ibin-1+nphibin/2])+TMath::Sqrt(totbdown[ibin-1]*totbup[ibin-1+nphibin/2]);//for SS and NN
		int sign= (ibin-2>0)? 1 :-1; //only 3 4 5 remain 1 2 change sign for sine modulation
		rawasybin = sign* (TMath::Sqrt(totbup[ibin-1]*totbdown[ibin-1+nphibin/2])-TMath::Sqrt(totbdown[ibin-1]*totbup[ibin-1+nphibin/2]))/bdemon;//for NN and SS
		rawasybinerr = TMath::Sqrt((totbdown[ibin-1+nphibin/2]+totbup[ibin-1])*totbup[ibin-1+nphibin/2]*totbdown[ibin-1]/TMath::Power(bdemon,4) + (totbup[ibin-1+nphibin/2]+totbdown[ibin-1])*totbdown[ibin-1+nphibin/2]*totbup[ibin-1]/TMath::Power(bdemon,4));
		int shift= (ibin-2>0)? -5 : 0;
		cout<<"sin_phi = "<<TMath::Sin(h1buphi->GetBinCenter(ibin+nphibin/2 + shift ))<<", rawasybin = "<<rawasybin<<", rawasybinerr = "<<rawasybinerr<<endl;

		h1asyphi->SetPoint(ibin-1,TMath::Sin(h1buphi->GetBinCenter(ibin+nphibin/2 + shift )), rawasybin); //becase i am only looking at [-pi,0] 
		h1asyphi->SetPointError(ibin-1,0,rawasybinerr);
		h1asyphi->GetXaxis()->SetTitle("sin#phi");
		h1asyphi->GetYaxis()->SetTitle("raw cross-ratio asy.");
		h1asyphi->GetYaxis()->SetTitleOffset(1.2);
	}
	
	h1asyphi->SetMarkerSize(1.5);
	h1asyphi->SetMarkerStyle(20);
	h1asyphi->SetMarkerColor(kBlue);
	h1asyphi->SetLineColor(kBlue);
	h1asyphi->SetLineWidth(1.5);
	h1asyphi->Draw("Ap");
	TF1* fit = new TF1("fit","pol1",-1,1); //2-parameter fit

    h1asyphi->Fit(fit,"R+");
	Char_t gifname[200];
    sprintf(gifname,"gifs/Collins/crasyxfblueFill%d_7ebins_Z%.2fGeV_M%.2ftoM%.2fGeV_AllTrigger.png",fillnum,ene,mlow,mhigh);
	Char_t coutname[200];
    sprintf(coutname,"coutfile/Collins/crasyxfblueFill%d_7ebins_Z%.2fGeV_M%.2ftoM%.2fGeV_AllTrigger.C",fillnum,ene,mlow,mhigh);
        cout<<"C outname: "<<coutname<<endl;
        cout<<"GIF name: "<<gifname<<endl;
	Float_t asy = fit->GetParameter(1);
	Float_t asyerr = fit->GetParError(1);
	Float_t p0 = fit->GetParameter(0);
	Float_t p0err = fit->GetParError(0);
	ofile<<fillnum<<" "<<ene<<" "<<asy<<" "<<asyerr<<" "<<p0<<" "<<p0err<<" "<<mlow<<" "<<mhigh<<endl;
   //     c1->Print(coutname);
  //      c1->Print(gifname);

cout<<"        Yellow below                      "<<endl;


	for(Int_t ibin = 1; ibin <= nphibin/2; ibin++){
		totbup[ibin-1] = TMath::Max(h1yuphi->GetBinContent(ibin),0.);//blue up at phi
		totbdown[ibin-1+nphibin/2] = TMath::Max(h1ydphi->GetBinContent(ibin+nphibin/2),0.);//blue down at phi+pi
		totbup[ibin-1+nphibin/2] = TMath::Max(h1yuphi->GetBinContent(ibin+nphibin/2),0.);//blue up at phi+pi		
		totbdown[ibin-1] = TMath::Max(h1ydphi->GetBinContent(ibin),0.);//blue down at phi
		cout<<" totbup "<< totbup[ibin-1] <<" totbdown "<<totbdown[ibin-1+nphibin/2]<<" totbup "<<totbup[ibin-1+nphibin/2]<<" totbdown "<<totbdown[ibin-1]<<endl;
		
		//calculate cross-ratio asy. for this particular phi bin
		bdemon = TMath::Sqrt(totbup[ibin-1]*totbdown[ibin-1+nphibin/2])+TMath::Sqrt(totbdown[ibin-1]*totbup[ibin-1+nphibin/2]);//for NN and SS 
		int sign= (ibin-2>0)? 1 :-1;
		rawasybin = sign*(TMath::Sqrt(totbup[ibin-1]*totbdown[ibin-1+nphibin/2])-TMath::Sqrt(totbdown[ibin-1]*totbup[ibin-1+nphibin/2]))/bdemon;//for NN and SS
		rawasybinerr = TMath::Sqrt((totbdown[ibin-1+nphibin/2]+totbup[ibin-1])*totbup[ibin-1+nphibin/2]*totbdown[ibin-1]/TMath::Power(bdemon,4) + (totbup[ibin-1+nphibin/2]+totbdown[ibin-1])*totbdown[ibin-1+nphibin/2]*totbup[ibin-1]/TMath::Power(bdemon,4));
		int shift= (ibin-2>0)? -5 : 0;
		cout<<"sin_phi = "<<TMath::Sin(h1yuphi->GetBinCenter(ibin+nphibin/2 + shift))<<", rawasybin = "<<rawasybin<<", rawasybinerr = "<<rawasybinerr<<endl;

		h2asyphi->SetPoint(ibin-1,TMath::Sin(h1yuphi->GetBinCenter(ibin+nphibin/2 + shift)), rawasybin); //becase i am only looking at [-pi,0] 
		h2asyphi->SetPointError(ibin-1,0,rawasybinerr);
		h2asyphi->GetXaxis()->SetTitle("sin#phi");
		h2asyphi->GetYaxis()->SetTitle("raw cross-ratio asy.");
		h2asyphi->GetYaxis()->SetTitleOffset(1.2);
	}
	
	h2asyphi->SetMarkerSize(1.5);
	h2asyphi->SetMarkerStyle(20);
	h2asyphi->SetMarkerColor(kBlue);
	h2asyphi->SetLineColor(kBlue);
	h2asyphi->SetLineWidth(1.5);
	h2asyphi->Draw("Ap");

    h2asyphi->Fit(fit,"R+");
	Char_t gifname2[200];
    sprintf(gifname2,"gifs/Collinsy/y_crasyxfblueFill%d_7ebins_Z%.2fGeV_M%.2ftoM%.2fGeV_AllTrigger.png",fillnum,ene,mlow,mhigh);
	Char_t coutname2[200];
    sprintf(coutname2,"coutfile/Collinsy/y_crasyxfblueFill%d_7ebins_Z%.2fGeV_M%.2ftoM%.2fGeV_AllTrigger.C",fillnum,ene,mlow,mhigh);
        cout<<"C outname: "<<coutname2<<endl;
        cout<<"GIF name: "<<gifname2<<endl;
	Float_t asy2 = fit->GetParameter(1);
	Float_t asyerr2 = fit->GetParError(1);
	Float_t p02 = fit->GetParameter(0);
	Float_t p0err2 = fit->GetParError(0);
	ofile2<<fillnum<<" "<<ene<<" "<<asy2<<" "<<asyerr2<<" "<<p02<<" "<<p0err2<<" "<<mlow<<" "<<mhigh<<endl;
 //       c1->Print(coutname2);
 //       c1->Print(gifname2);
//	c1->Print("tmp.ps");
  }

