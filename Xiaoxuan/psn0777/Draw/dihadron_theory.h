//=========Macro generated from canvas: c1/
//=========  (Tue Nov  8 12:59:26 2016) by ROOT version6.06/00
//Thoery predictions from Cyrille, Bowen and Heikki
//cyrille: rcBK model
//bowen: GWB, without Sudokov effects
//bw: with Sudokov effets, self-normalization
//heikki: with calculations of pedestal

void dihadron_theory(int plot=0, int color=-1,float bg=0.0){
    Int_t ci;      // for color index setting
    if(plot==0){
	TCanvas *c1 = new TCanvas("c1", "",49,104,1076,1049);
	gStyle->SetOptStat(0);
	c1->Range(1.03783,-7.067948,4.808174,-1.038151);
	c1->SetFillColor(0);
	c1->SetBorderMode(0);
	c1->SetBorderSize(2);
	c1->SetLogy();
	c1->SetLeftMargin(0.1597122);
	c1->SetRightMargin(0.04460432);
	c1->SetTopMargin(0.04359673);
	c1->SetBottomMargin(0.1771117);
	c1->SetFrameBorderMode(0);
	c1->SetFrameBorderMode(0);
	TH2F *FMS = new TH2F("FMS","",1,1.68,4.6,1,1e-06,0.05);
	FMS->SetStats(0);

	TColor *color; // for color definition with alpha
	ci = TColor::GetColor("#000099");
	FMS->SetLineColor(ci);
	FMS->GetXaxis()->SetTitle("#varphi [radian]");
	FMS->GetXaxis()->CenterTitle(true);
	FMS->GetXaxis()->SetLabelFont(42);
	FMS->GetXaxis()->SetLabelSize(0.05);
	FMS->GetXaxis()->SetTitleSize(0.06);
	FMS->GetXaxis()->SetTitleOffset(1.2);
	FMS->GetXaxis()->SetTitleFont(42);
	FMS->GetYaxis()->SetTitle("C(#Delta#varphi)");
	FMS->GetYaxis()->CenterTitle(true);
	FMS->GetYaxis()->SetNdivisions(508);
	FMS->GetYaxis()->SetLabelFont(42);
	FMS->GetYaxis()->SetLabelOffset(0.011);
	FMS->GetYaxis()->SetLabelSize(0.05);
	FMS->GetYaxis()->SetTitleSize(0.06);
	FMS->GetYaxis()->SetTitleOffset(1.23);
	FMS->GetYaxis()->SetTitleFont(42);
	FMS->GetZaxis()->SetLabelFont(42);
	FMS->GetZaxis()->SetLabelSize(0.035);
	FMS->GetZaxis()->SetTitleSize(0.035);
	FMS->GetZaxis()->SetTitleFont(42);
	FMS->Draw("");
    }
    Double_t cyrillepp_dphi[27] = {1.041592653589793,1.341592653589793,1.6415926535897931,1.9415926535897932,2.241592653589793,2.441592653589793,2.641592653589793,2.8415926535897933,2.941592653589793	,3.041592653589793,3.0915926535897933,3.116592653589793	,3.126592653589793,3.141592653589793,3.1565926535897932	,3.166592653589793,3.191592653589793,3.241592653589793,3.3415926535897933,3.441592653589793,3.641592653589793,3.8415926535897933,4.0415926535897935,4.341592653589793,4.641592653589793	,4.941592653589793,5.241592653589793	
};    
    
    Double_t cyrillepp_pt1[27]={0.00042251933101532523,0.00041827846527429013,0.00047678992240753423,0.0006181414275960982,0.0009221118519568706,0.0013186680634992077,0.0020405536964648832,0.003337777877288067,0.0042117934631788825,0.005000391282892456,0.005227203554456209,0.005282290215350687,0.005293783890876901,0.005300187713559647,0.005293783890876901,0.005282290215350687,0.005227203554456209,0.005000391282892456,0.0042117934631788825,0.003337777877288067,0.0020405536964648832,0.0013186680634992077,0.0009221118519568706,0.0006181414275960982,0.00047678992240753423,0.00041827846527429013,0.00042251933101532523};
    Double_t cyrillepp_pt2[27]={0.00031808187311126336,0.00031278303646312735,0.0003532751229823465,0.00045162572818184185,0.000662020171879133,0.0009401233124314776,0.0014719340779195485,0.0025400423049006856,0.003351658420158297,0.00414806453338066,0.004385143213525191,0.004442628923833037,0.004454587648473964,0.004461250629324608,0.004454587648473964,0.004442628923833037,0.004385143213525191,0.00414806453338066,0.003351658420158297,0.0025400423049006856,0.0014719340779195485,0.0009401233124314776,0.000662020171879133,0.00045162572818184185,0.0003532751229823465,0.00031278303646312735,0.00031808187311126336};
Double_t cyrillepp_pt3[27]={0.00004813310131785156,0.00004739060856705321,0.00005389301220552927,0.00006969347139206258,0.0001042172416877134,0.0001519193939044362,0.0002513775823005786,0.0004897460972060204,0.0007101250651809976,0.0009650684363108454,0.0010476781834748519,0.0010675147957394844,0.0010715810283179542,0.001073833664696748,0.0010715810283179542,0.0010675147957394844,0.0010476781834748519,0.0009650684363108454,0.0007101250651809976,0.0004897460972060204,0.0002513775823005786,0.0001519193939044362,0.0001042172416877134,0.00006969347139206258,0.00005389301220552927,0.00004739060856705321,0.00004813310131785156};
Double_t cyrillepp_pt4[27]={7.810751518464136e-6,7.690341705774283e-6,8.761624210901256e-6,0.000011365508272546918,0.00001702147695853648,0.00002482345371687858,0.00004142788216839504,0.00008560462543149372,0.0001338697418691557,0.0002006852321438478,0.00022541725666372497,0.00023157290446212798,0.0002328387304898879,0.00023353761904767908,0.0002328387304898879,0.00023157290446212798,0.00022541725666372497,0.0002006852321438478,0.0001338697418691557,0.00008560462543149372,0.00004142788216839504,0.00002482345371687858,0.00001702147695853648,0.000011365508272546918,8.761624210901256e-6,7.690341705774283e-6,7.810751518464136e-6};
Double_t cyrillepAu_pt1[27]={0.0013938998641915116,0.0013832373032955725,0.0015700358967885308,0.001993093711414387,0.0027983636896036232,0.0036801003906890444,0.004942972695818311,0.006513542714757178,0.0072397022859074294,0.007736853862220406,0.007863505585692144,0.007894863876287123,0.00790152750566637,0.007905267701113296,0.00790152750566637,0.007894863876287123,0.007863505585692144,0.007736853862220406,0.0072397022859074294,0.006513542714757178,0.004942972695818311,0.0036801003906890444,0.0027983636896036232,0.001993093711414387,0.0015700358967885308,0.0013832373032955725,0.0013938998641915116};
Double_t cyrillepAu_pt2[27]={0.0003612160159149545,0.00035809508420836685,0.00040727099443404796,0.0005206012012499747,0.0007442538424379051,0.0010023103843070829,0.0013979908112781712,0.001936258694242614,0.002203038267011911,0.0023915724255742445,0.0024401353368686423,0.0024521734003989304,0.0024547317500543,0.0024561688141574644,0.0024547317500543,0.0024521734003989304,0.0024401353368686423,0.0023915724255742445,0.002203038267011911,0.001936258694242614,0.0013979908112781712,0.0010023103843070829,0.0007442538424379051,0.0005206012012499747,0.00040727099443404796,0.00035809508420836685,0.0003612160159149545};
Double_t cyrillepAu_pt3[27]={0.00005134317353809318,0.00005112423746370942,0.000058981616697435465,0.00007755567013040841,0.00011701153781975224,0.00016740260572919562,0.0002551133461094629,0.0003961355981539536,0.00047601993310784137,0.0005360450016331008,0.0005516541646544155,0.0005554940811804245,0.0005563075173845463,0.0005567639950220811,0.0005563075173845463,0.0005554940811804245,0.0005516541646544155,0.0005360450016331008,0.00047601993310784137,0.0003961355981539536,0.0002551133461094629,0.00016740260572919562,0.00011701153781975224,0.00007755567013040841,0.000058981616697435465,0.00005112423746370942,0.00005134317353809318};
Double_t cyrillepAu_pt4[27]={8.035558030881161e-6,8.00618604243299e-6,9.272028817197547e-6,0.000012296645433118835,0.00001894784941197356,0.000027957826024474038,0.00004515180398781511,0.00007723509017786493,0.00009814718063916196,0.00011521534548833548,0.00011977791671351406,0.00012089728493668655,0.00012113387104742701,0.00012126629054607242,0.00012113387104742701,0.00012089728493668655,0.00011977791671351406,0.00011521534548833548,0.00009814718063916196,0.00007723509017786493,0.00004515180398781511,0.000027957826024474038,0.00001894784941197356,0.000012296645433118835,9.272028817197547e-6,8.00618604243299e-6,8.035558030881161e-6};

    if(bg>0.0){
	for(int i=0; i<27; i++){
            cyrillepp_pt1[i]+=bg;
	    cyrillepp_pt2[i]+=bg;
	    cyrillepp_pt3[i]+=bg;
	    cyrillepp_pt4[i]+=bg;
	    cyrillepAu_pt1[i]+=bg;
	    cyrillepAu_pt2[i]+=bg;
	    cyrillepAu_pt3[i]+=bg;
	    cyrillepAu_pt4[i]+=bg;
	    
	}
    }
    TGraph *graph = new TGraph(27,cyrillepp_dphi,cyrillepp_pt1);
    graph->SetName("cyrillepp_1"); graph->SetTitle("cyrillepp_1");
    graph->SetLineColor(2); graph->SetLineWidth(3);
    if(color>0) graph->SetLineColor(color);    
    if(plot==0 || plot==8) graph->Draw("c");

    TGraph *graph = new TGraph(27,cyrillepp_dphi,cyrillepp_pt2);
    graph->SetName("cyrillepp_1"); graph->SetTitle("cyrillepp_1");
    graph->SetLineColor(2); graph->SetLineWidth(3);
    if(color>0) graph->SetLineColor(color);    
    if(plot==0 || plot==9) graph->Draw("c");

    TGraph *graph = new TGraph(27,cyrillepp_dphi,cyrillepp_pt3);
    graph->SetName("cyrillepp_1"); graph->SetTitle("cyrillepp_1");
    graph->SetLineColor(2); graph->SetLineWidth(3);
    if(color>0) graph->SetLineColor(color);    
    if(plot==0 || plot==10) graph->Draw("c");

    TGraph *graph = new TGraph(27,cyrillepp_dphi,cyrillepp_pt4);
    graph->SetName("cyrillepp_1"); graph->SetTitle("cyrillepp_1");
    graph->SetLineColor(2); graph->SetLineWidth(3);
    if(color>0) graph->SetLineColor(color);    
    if(plot==0 || plot==11) graph->Draw("c");

    TGraph *graph = new TGraph(27,cyrillepp_dphi,cyrillepAu_pt1);
    graph->SetName("cyrillepAu_1"); graph->SetTitle("cyrillepAu_1");
    graph->SetLineColor(2); graph->SetLineWidth(3);
    if(color>0) graph->SetLineColor(color);    
    if(plot==0 || plot==12) graph->Draw("c");

    TGraph *graph = new TGraph(27,cyrillepp_dphi,cyrillepAu_pt2);
    graph->SetName("cyrillepAu_1"); graph->SetTitle("cyrillepAu_1");
    graph->SetLineColor(2); graph->SetLineWidth(3);
    if(color>0) graph->SetLineColor(color);    
    if(plot==0 || plot==13) graph->Draw("c");

    TGraph *graph = new TGraph(27,cyrillepp_dphi,cyrillepAu_pt3);
    graph->SetName("cyrillepAu_1"); graph->SetTitle("cyrillepAu_1");
    graph->SetLineColor(2); graph->SetLineWidth(3);
    if(color>0) graph->SetLineColor(color);    
    if(plot==0 || plot==14) graph->Draw("c");

    TGraph *graph = new TGraph(27,cyrillepp_dphi,cyrillepAu_pt4);
    graph->SetName("cyrillepAu_1"); graph->SetTitle("cyrillepAu_1");
    graph->SetLineColor(2); graph->SetLineWidth(3);
    if(color>0) graph->SetLineColor(color);    
    if(plot==0 || plot==15) graph->Draw("c");

    Double_t bowenpAu1_fx1[21] = {
	1.594785,1.799439,1.998707,2.197976,2.397244,
	2.596513,2.795782,2.898109,2.99505,3.097377,
	3.140462,3.199704,3.296646,3.398973,3.495914,
	3.695183,3.899837,4.099105,4.298374,4.497642,
	4.599969};
    Double_t bowenpAu1_fy1[21] = {
	0.008430444,0.008107355,0.008430444,0.00911576,
	0.01024959,0.01152445,0.01270715,0.01295788,
	0.01321355,0.01347427,0.01347427,0.01347427,
	0.01321355,0.01295788,0.01246128,0.01152445,
	0.01024959,0.00911576,0.008267321,0.008107355,
	0.008267321};
    if(bg>0.0) {for(int i=0; i<21; i++) {bowenpAu1_fy1[i]+=(bg-0.008430444);}}
    TGraph *graph = new TGraph(21,bowenpAu1_fx1,bowenpAu1_fy1);
    graph->SetName("bowenpAu1");
    graph->SetTitle("bowenpAu1");
    graph->SetFillColor(1);
    graph->SetLineColor(2);
    if(color>0) graph->SetLineColor(color);
    graph->SetLineWidth(3);
    
    TH1F *bowenpAu1 = new TH1F("bowenpAu1","bowenpAu1",100,1.3,4.9);
    bowenpAu1->SetMinimum(0.007495577);
    bowenpAu1->SetMaximum(0.01375894);
    bowenpAu1->SetDirectory(0);
    bowenpAu1->SetStats(0);
    
    ci = TColor::GetColor("#000099");
    bowenpAu1->SetLineColor(ci);
    bowenpAu1->GetXaxis()->SetLabelFont(42);
    bowenpAu1->GetXaxis()->SetLabelSize(0.06);
    bowenpAu1->GetXaxis()->SetTitleSize(0.06);
    bowenpAu1->GetXaxis()->SetTitleOffset(1.2);
    bowenpAu1->GetXaxis()->SetTitleFont(42);
    bowenpAu1->GetYaxis()->SetLabelFont(42);
    bowenpAu1->GetYaxis()->SetLabelSize(0.06);
    bowenpAu1->GetYaxis()->SetTitleSize(0.06);
    bowenpAu1->GetYaxis()->SetTitleFont(42);
    bowenpAu1->GetZaxis()->SetLabelFont(42);
    bowenpAu1->GetZaxis()->SetLabelSize(0.035);
    bowenpAu1->GetZaxis()->SetTitleSize(0.035);
    bowenpAu1->GetZaxis()->SetTitleFont(42);
    graph->SetHistogram(bowenpAu1);
    
    if(plot==0 || plot==1) graph->Draw("c");
    
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
    if(bg>0.0) {for(int i=0; i<21; i++) {bowenpAu2_fy2[i]+=(bg-0.0005362648);}}
    graph = new TGraph(21,bowenpAu2_fx2,bowenpAu2_fy2);
    graph->SetName("bowenpAu2");
    graph->SetTitle("bowenpAu2");
    graph->SetFillColor(1);
    graph->SetLineColor(8);
    if(color>0) graph->SetLineColor(color);
    graph->SetLineWidth(3);
    
    TH1F *bowenpAu2 = new TH1F("bowenpAu2","bowenpAu2",100,1.3,4.9);
    bowenpAu2->SetMinimum(0.0003473337);
    bowenpAu2->SetMaximum(0.002547861);
    bowenpAu2->SetDirectory(0);
    bowenpAu2->SetStats(0);
    
    ci = TColor::GetColor("#000099");
    bowenpAu2->SetLineColor(ci);
    bowenpAu2->GetXaxis()->SetLabelFont(42);
    bowenpAu2->GetXaxis()->SetLabelSize(0.06);
    bowenpAu2->GetXaxis()->SetTitleSize(0.06);
    bowenpAu2->GetXaxis()->SetTitleOffset(1.2);
    bowenpAu2->GetXaxis()->SetTitleFont(42);
    bowenpAu2->GetYaxis()->SetLabelFont(42);
    bowenpAu2->GetYaxis()->SetLabelSize(0.06);
    bowenpAu2->GetYaxis()->SetTitleSize(0.06);
    bowenpAu2->GetYaxis()->SetTitleFont(42);
    bowenpAu2->GetZaxis()->SetLabelFont(42);
    bowenpAu2->GetZaxis()->SetLabelSize(0.035);
    bowenpAu2->GetZaxis()->SetTitleSize(0.035);
    bowenpAu2->GetZaxis()->SetTitleFont(42);
    graph->SetHistogram(bowenpAu2);
    
    if(plot==0 || plot==2) graph->Draw("c");
    
    Double_t bowenpAu3_fx3[21] = {
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
    Double_t bowenpAu3_fy3[21] = {
	4.755142e-05,
	6.374522e-05,
	9.422364e-05,
	0.0001476825,
	0.0002314717,
	0.0003488959,
	0.0004677136,
	0.0005157129,
	0.0005362648,
	0.0005576356,
	0.0005576356,
	0.0005576356,
	0.0005362648,
	0.0005057343,
	0.0004586637,
	0.0003355248,
	0.0002226008,
	0.0001420227,
	9.061261e-05,
	6.25118e-05,
	5.346593e-05};
    if(bg>0.0) {for(int i=0; i<21; i++) {bowenpAu3_fy3[i]+=(bg-4.755142e-05);}}
    graph = new TGraph(21,bowenpAu3_fx3,bowenpAu3_fy3);
    graph->SetName("bowenpAu3");
    graph->SetTitle("bowenpAu3");
    graph->SetFillColor(1);
    graph->SetLineColor(4);
    if(color>0) graph->SetLineColor(color);
    graph->SetLineWidth(3);
    
    TH1F *bowenpAu3 = new TH1F("bowenpAu3","bowenpAu3",100,1.3,4.9);
    bowenpAu3->SetMinimum(4.224501e-05);
    bowenpAu3->SetMaximum(0.0006007005);
    bowenpAu3->SetDirectory(0);
    bowenpAu3->SetStats(0);
    
    ci = TColor::GetColor("#000099");
    bowenpAu3->SetLineColor(ci);
    bowenpAu3->GetXaxis()->SetLabelFont(42);
    bowenpAu3->GetXaxis()->SetLabelSize(0.06);
    bowenpAu3->GetXaxis()->SetTitleSize(0.06);
    bowenpAu3->GetXaxis()->SetTitleOffset(1.2);
    bowenpAu3->GetXaxis()->SetTitleFont(42);
    bowenpAu3->GetYaxis()->SetLabelFont(42);
    bowenpAu3->GetYaxis()->SetLabelSize(0.06);
    bowenpAu3->GetYaxis()->SetTitleSize(0.06);
    bowenpAu3->GetYaxis()->SetTitleFont(42);
    bowenpAu3->GetZaxis()->SetLabelFont(42);
    bowenpAu3->GetZaxis()->SetLabelSize(0.035);
    bowenpAu3->GetZaxis()->SetTitleSize(0.035);
    bowenpAu3->GetZaxis()->SetTitleFont(42);
    graph->SetHistogram(bowenpAu3);
    
    if(plot==0 || plot==3) graph->Draw("c");
   
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
    if(bg>0.0) {for(int i=0; i<21; i++) {bowenpAu4_fy4[i]+=(bg-3.14531e-06);}}
    graph = new TGraph(21,bowenpAu4_fx4,bowenpAu4_fy4);
    graph->SetName("bowenpAu4");
    graph->SetTitle("bowenpAu4");
    graph->SetFillColor(1);
    if(color>0) graph->SetLineColor(color);
    graph->SetLineWidth(3);
    
    TH1F *bowenpAu4 = new TH1F("bowenpAu4","bowenpAu4",100,1.3,4.9);
    bowenpAu4->SetMinimum(2.829456e-06);
    bowenpAu4->SetMaximum(0.0001084181);
    bowenpAu4->SetDirectory(0);
    bowenpAu4->SetStats(0);
    
    ci = TColor::GetColor("#000099");
    bowenpAu4->SetLineColor(ci);
    bowenpAu4->GetXaxis()->SetLabelFont(42);
    bowenpAu4->GetXaxis()->SetLabelSize(0.06);
    bowenpAu4->GetXaxis()->SetTitleSize(0.06);
    bowenpAu4->GetXaxis()->SetTitleOffset(1.2);
    bowenpAu4->GetXaxis()->SetTitleFont(42);
    bowenpAu4->GetYaxis()->SetLabelFont(42);
    bowenpAu4->GetYaxis()->SetLabelSize(0.06);
    bowenpAu4->GetYaxis()->SetTitleSize(0.06);
    bowenpAu4->GetYaxis()->SetTitleFont(42);
    bowenpAu4->GetZaxis()->SetLabelFont(42);
    bowenpAu4->GetZaxis()->SetLabelSize(0.035);
    bowenpAu4->GetZaxis()->SetTitleSize(0.035);
    bowenpAu4->GetZaxis()->SetTitleFont(42);
    graph->SetHistogram(bowenpAu4);
    
    if(plot==0 || plot==4) graph->Draw("c");

    Double_t bwpp2_fy2[61] = {
	0.197457,0.202516,0.208141,0.213518,0.219183,0.225752,0.232156,0.240295,0.248607,
	0.256859,0.266275,0.275192,0.285412,0.295413,0.306344,0.317104,0.328456,0.340270,
	0.350966,0.362155,0.373557,0.384553,0.394405,0.403449,0.412077,0.420092,0.426291,
	0.431322,0.435438,0.437590,0.438018,0.437352,0.435438,0.431734,0.426483,0.419680,
	0.412270,0.403659,0.394067,0.384139,0.373239,0.362368,0.351252,0.340225,0.328588,
	0.317929,0.306058,0.295398,0.285516,0.274826,0.265229,0.256563,0.247699,0.239968,
	0.233108,0.226092,0.218644,0.213113,0.207836,0.202789,0.196778};
    Double_t bwpp2_fx2[61] = {1.59655,1.64805,1.69955,1.75105,1.80255,1.85405,1.90556  
	,1.95706,2.00856,2.06006,2.11156,2.16306,2.21457,2.26607,2.31757,2.36907  
	,2.42057,2.47207,2.52357,2.57508,2.62658,2.67808,2.72958,2.78108,2.83258  
	,2.88409,2.93559,2.98709,3.03859,3.09009,3.14159,3.19309,3.24460,3.29610
	,3.34760,3.39910,3.45060,3.50210,3.55360,3.60511,3.65661,3.70811,3.75961  
	,3.81111,3.86261,3.91412,3.96562,4.01712,4.06862,4.12012,4.17162,4.22312  
	,4.27463,4.32613,4.37763,4.42913,4.48063,4.53213,4.58364,4.63514,4.68664  
};
    if(bg>0.0) {for(int i=0; i<61; i++) {bwpp2_fy2[i]+=(bg-0.197457);}}
    TGraph *graph = new TGraph(61,bwpp2_fx2,bwpp2_fy2);
    graph->SetName("bwpp2");
    graph->SetTitle("bwpp2");
    graph->SetFillColor(1);
    graph->SetLineColor(2);
    if(color>0) graph->SetLineColor(color);
    graph->SetLineWidth(3);
    
    TH1F *bwpp2 = new TH1F("bwpp2","bwpp2",100,1.3,4.9);
    bwpp2->SetMinimum(0.007495577);
    bwpp2->SetMaximum(0.01375894);
    bwpp2->SetDirectory(0);
    bwpp2->SetStats(0);
    
    ci = TColor::GetColor("#000099");
    bwpp2->SetLineColor(ci);
    bwpp2->GetXaxis()->SetLabelFont(42);
    bwpp2->GetXaxis()->SetLabelSize(0.06);
    bwpp2->GetXaxis()->SetTitleSize(0.06);
    bwpp2->GetXaxis()->SetTitleOffset(1.2);
    bwpp2->GetXaxis()->SetTitleFont(42);
    bwpp2->GetYaxis()->SetLabelFont(42);
    bwpp2->GetYaxis()->SetLabelSize(0.06);
    bwpp2->GetYaxis()->SetTitleSize(0.06);
    bwpp2->GetYaxis()->SetTitleFont(42);
    bwpp2->GetZaxis()->SetLabelFont(42);
    bwpp2->GetZaxis()->SetLabelSize(0.035);
    bwpp2->GetZaxis()->SetTitleSize(0.035);
    bwpp2->GetZaxis()->SetTitleFont(42);
    graph->SetHistogram(bwpp2);
    
    if(plot==0 || plot==17) graph->Draw("c");
 
    Double_t bwpp3_fy3[61] = {
 0.1288
, 0.137828
, 0.146586
, 0.155762
, 0.165217
, 0.174765
, 0.18465
, 0.196205
, 0.208208
, 0.220104
, 0.233936
, 0.247304
, 0.262056
, 0.277025
, 0.293491
, 0.310309
, 0.327864
, 0.346421
, 0.363993
, 0.382496
, 0.401333
, 0.419834
, 0.437112
, 0.453306
, 0.468661
, 0.482903
, 0.494444
, 0.503788
, 0.511213
, 0.515339
, 0.516514
, 0.515077
,0.511186
,0.504438
,0.494737
,0.4824
,0.468874
,0.453437
,0.436718
, 0.419388
, 0.401129
, 0.382682
, 0.364387
, 0.346399
, 0.327916
, 0.311413
, 0.293303
, 0.27726
, 0.261918
, 0.246785
, 0.232684
, 0.220131
, 0.207298
, 0.195764
, 0.185567
, 0.174877
, 0.164311
, 0.155878
, 0.146822
, 0.138087
, 0.128573
};
    if(bg>0.0) {for(int i=0; i<61; i++) {bwpp3_fy3[i]+=(bg-0.1288);}}
    TGraph *graph = new TGraph(61,bwpp2_fx2,bwpp3_fy3);
    graph->SetName("bwpp3");
    graph->SetTitle("bwpp3");
    graph->SetFillColor(1);
    graph->SetLineColor(2);
    if(color>0) graph->SetLineColor(color);
    graph->SetLineWidth(3);
    
    TH1F *bwpp3 = new TH1F("bwpp3","bwpp3",100,1.3,4.9);
    bwpp3->SetMinimum(0.007495577);
    bwpp3->SetMaximum(0.01375894);
    bwpp3->SetDirectory(0);
    bwpp3->SetStats(0);
    
    ci = TColor::GetColor("#000099");
    bwpp3->SetLineColor(ci);
    bwpp3->GetXaxis()->SetLabelFont(42);
    bwpp3->GetXaxis()->SetLabelSize(0.06);
    bwpp3->GetXaxis()->SetTitleSize(0.06);
    bwpp3->GetXaxis()->SetTitleOffset(1.2);
    bwpp3->GetXaxis()->SetTitleFont(42);
    bwpp3->GetYaxis()->SetLabelFont(42);
    bwpp3->GetYaxis()->SetLabelSize(0.06);
    bwpp3->GetYaxis()->SetTitleSize(0.06);
    bwpp3->GetYaxis()->SetTitleFont(42);
    bwpp3->GetZaxis()->SetLabelFont(42);
    bwpp3->GetZaxis()->SetLabelSize(0.035);
    bwpp3->GetZaxis()->SetTitleSize(0.035);
    bwpp3->GetZaxis()->SetTitleFont(42);
    graph->SetHistogram(bwpp3);
    
    if(plot==0 || plot==18) graph->Draw("c");
 
Double_t bwpp4_fy4[61] = {
  0.0769267
,  0.0867694
,  0.0974863
,  0.10844
,  0.11917
,  0.13056
,  0.142083
,  0.15567
,  0.169779
,  0.183572
,  0.199996
,  0.21585
,  0.234203
,  0.252065
,  0.273466
,  0.295223
,  0.31875
,  0.34243
,  0.367402
,  0.39352
,  0.42033
,  0.447799
,  0.474038
,  0.498699
,  0.523477
,  0.54563
,  0.565294
,  0.580222
,  0.592279
,  0.599514
,  0.601111
,  0.598657
, 0.59236
, 0.580516
, 0.565119
, 0.545078
, 0.523595
, 0.499033
, 0.473063
,  0.447013
,  0.41985
,  0.393916
,  0.367992
,  0.342895
,  0.318008
,  0.295826
,  0.273052
,  0.253082
,  0.233122
,  0.215629
,  0.198498
,  0.183129
,  0.168945
,  0.154988
,  0.142579
,  0.131004
,  0.118134
,  0.107901
,  0.0978756
,  0.0870139
,  0.0772749
};
    if(bg>0.0) {for(int i=0; i<61; i++) {bwpp4_fy4[i]+=(bg-0.0769267);}}
    TGraph *graph = new TGraph(61,bwpp2_fx2,bwpp4_fy4);
    graph->SetName("bwpp4");
    graph->SetTitle("bwpp4");
    graph->SetFillColor(1);
    graph->SetLineColor(2);
    if(color>0) graph->SetLineColor(color);
    graph->SetLineWidth(3);
    
    TH1F *bwpp4 = new TH1F("bwpp4","bwpp4",100,1.3,4.9);
    bwpp4->SetMinimum(0.007495577);
    bwpp4->SetMaximum(0.01375894);
    bwpp4->SetDirectory(0);
    bwpp4->SetStats(0);
    
    ci = TColor::GetColor("#000099");
    bwpp4->SetLineColor(ci);
    bwpp4->GetXaxis()->SetLabelFont(42);
    bwpp4->GetXaxis()->SetLabelSize(0.06);
    bwpp4->GetXaxis()->SetTitleSize(0.06);
    bwpp4->GetXaxis()->SetTitleOffset(1.2);
    bwpp4->GetXaxis()->SetTitleFont(42);
    bwpp4->GetYaxis()->SetLabelFont(42);
    bwpp4->GetYaxis()->SetLabelSize(0.06);
    bwpp4->GetYaxis()->SetTitleSize(0.06);
    bwpp4->GetYaxis()->SetTitleFont(42);
    bwpp4->GetZaxis()->SetLabelFont(42);
    bwpp4->GetZaxis()->SetLabelSize(0.035);
    bwpp4->GetZaxis()->SetTitleSize(0.035);
    bwpp4->GetZaxis()->SetTitleFont(42);
    graph->SetHistogram(bwpp4);
    
    if(plot==0 || plot==19) graph->Draw("c");

    Double_t bwpAu2_fy2[61] = {
 0.222809
, 0.225687
, 0.229783
, 0.233286
, 0.237295
, 0.242339
, 0.247333
, 0.254025
, 0.260742
, 0.267584
, 0.275207
, 0.282632
, 0.291302
, 0.299478
, 0.308518
, 0.317412
, 0.326895
, 0.336541
, 0.345331
, 0.354459
, 0.363769
, 0.372591
, 0.380569
, 0.387666
, 0.394546
, 0.400888
, 0.405822
, 0.409675
, 0.412994
, 0.414633
, 0.414996
, 0.414403
,0.412936
,0.410053
,0.405981
,0.400575
,0.394751
,0.38792
,0.380311
, 0.372281
, 0.363507
, 0.354648
, 0.34562
, 0.336584
, 0.327078
, 0.318093
, 0.308309
, 0.299458
, 0.291297
, 0.282427
, 0.274399
, 0.267278
, 0.260054
, 0.253745
, 0.248278
, 0.242745
, 0.236926
, 0.233
, 0.22935
, 0.226019
, 0.22207
};
    if(bg>0.0) {for(int i=0; i<61; i++) {bwpAu2_fy2[i]+=(bg-0.222809);}}
    TGraph *graph = new TGraph(61,bwpp2_fx2,bwpAu2_fy2);
    graph->SetName("bwpAu2");
    graph->SetTitle("bwpAu2");
    graph->SetFillColor(1);
    graph->SetLineColor(2);
    if(color>0) graph->SetLineColor(color);
    graph->SetLineWidth(3);
    
    TH1F *bwpAu2 = new TH1F("bwpAu2","bwpAu2",100,1.3,4.9);
    bwpAu2->SetMinimum(0.007495577);
    bwpAu2->SetMaximum(0.01375894);
    bwpAu2->SetDirectory(0);
    bwpAu2->SetStats(0);
    
    ci = TColor::GetColor("#000099");
    bwpAu2->SetLineColor(ci);
    bwpAu2->GetXaxis()->SetLabelFont(42);
    bwpAu2->GetXaxis()->SetLabelSize(0.06);
    bwpAu2->GetXaxis()->SetTitleSize(0.06);
    bwpAu2->GetXaxis()->SetTitleOffset(1.2);
    bwpAu2->GetXaxis()->SetTitleFont(42);
    bwpAu2->GetYaxis()->SetLabelFont(42);
    bwpAu2->GetYaxis()->SetLabelSize(0.06);
    bwpAu2->GetYaxis()->SetTitleSize(0.06);
    bwpAu2->GetYaxis()->SetTitleFont(42);
    bwpAu2->GetZaxis()->SetLabelFont(42);
    bwpAu2->GetZaxis()->SetLabelSize(0.035);
    bwpAu2->GetZaxis()->SetTitleSize(0.035);
    bwpAu2->GetZaxis()->SetTitleFont(42);
    graph->SetHistogram(bwpAu2);
    
    if(plot==0 || plot==20) graph->Draw("c");
 
    Double_t bwpAu3_fy3[61] = {
 0.147813
, 0.15569
, 0.163679
, 0.171862
, 0.180539
, 0.18921
, 0.198381
, 0.209196
, 0.22021
, 0.231401
, 0.244007
, 0.256426
, 0.270137
, 0.283703
, 0.298699
, 0.313857
, 0.329632
, 0.346041
, 0.361608
, 0.37785
, 0.394241
, 0.410156
, 0.424975
, 0.438533
, 0.451484
, 0.463362
, 0.473026
, 0.480687
, 0.486865
, 0.490192
, 0.491175
, 0.48989
,0.486749
,0.481209
,0.473297
,0.462995
,0.451751
,0.438777
,0.424605
, 0.409686
, 0.394071
, 0.377953
, 0.362018
, 0.346163
, 0.329737
, 0.314808
, 0.298506
, 0.283938
, 0.270104
, 0.256074
, 0.242997
, 0.231386
, 0.219398
, 0.208845
, 0.199107
, 0.189548
, 0.179761
, 0.171957
, 0.163624
, 0.156096
, 0.147217
};
    if(bg>0.0) {for(int i=0; i<61; i++) {bwpAu3_fy3[i]+=(bg-0.147813);}}
    TGraph *graph = new TGraph(61,bwpp2_fx2,bwpAu3_fy3);
    graph->SetName("bwpAu3");
    graph->SetTitle("bwpAu3");
    graph->SetFillColor(1);
    graph->SetLineColor(2);
    if(color>0) graph->SetLineColor(color);
    graph->SetLineWidth(3);
    
    TH1F *bwpAu3 = new TH1F("bwpAu3","bwpAu3",100,1.3,4.9);
    bwpAu3->SetMinimum(0.007495577);
    bwpAu3->SetMaximum(0.01375894);
    bwpAu3->SetDirectory(0);
    bwpAu3->SetStats(0);
    
    ci = TColor::GetColor("#000099");
    bwpAu3->SetLineColor(ci);
    bwpAu3->GetXaxis()->SetLabelFont(42);
    bwpAu3->GetXaxis()->SetLabelSize(0.06);
    bwpAu3->GetXaxis()->SetTitleSize(0.06);
    bwpAu3->GetXaxis()->SetTitleOffset(1.2);
    bwpAu3->GetXaxis()->SetTitleFont(42);
    bwpAu3->GetYaxis()->SetLabelFont(42);
    bwpAu3->GetYaxis()->SetLabelSize(0.06);
    bwpAu3->GetYaxis()->SetTitleSize(0.06);
    bwpAu3->GetYaxis()->SetTitleFont(42);
    bwpAu3->GetZaxis()->SetLabelFont(42);
    bwpAu3->GetZaxis()->SetLabelSize(0.035);
    bwpAu3->GetZaxis()->SetTitleSize(0.035);
    bwpAu3->GetZaxis()->SetTitleFont(42);
    graph->SetHistogram(bwpAu3);
    
    if(plot==0 || plot==21) graph->Draw("c");
 
Double_t bwpAu4_fy4[61] = {
 0.0888393
, 0.0982853
, 0.108235
, 0.119547
, 0.130004
, 0.140881
, 0.152227
, 0.165511
, 0.179371
, 0.192932
, 0.209089
, 0.224568
, 0.242447
, 0.259732
, 0.280315
, 0.300934
, 0.323117
, 0.345459
, 0.368813
, 0.392843
, 0.417406
, 0.44229
, 0.465892
, 0.487634
, 0.509301
, 0.528583
, 0.54555
, 0.558437
, 0.568837
, 0.574797
, 0.576209
, 0.574089
,0.568861
,0.558765
,0.545552
,0.528154
,0.509572
,0.487943
,0.464873
, 0.441552
, 0.417084
, 0.393255
, 0.369413
, 0.346002
, 0.322679
, 0.301713
, 0.279897
, 0.260794
, 0.241536
, 0.224307
, 0.207676
, 0.192779
, 0.178691
, 0.164976
, 0.15274
, 0.141154
, 0.128888
, 0.118955
, 0.109126
, 0.0986293
, 0.0891619
};
    if(bg>0.0) {for(int i=0; i<61; i++) {bwpAu4_fy4[i]+=(bg-0.0888393);}}
    TGraph *graph = new TGraph(61,bwpp2_fx2,bwpAu4_fy4);
    graph->SetName("bwpAu4");
    graph->SetTitle("bwpAu4");
    graph->SetFillColor(1);
    graph->SetLineColor(2);
    if(color>0) graph->SetLineColor(color);
    graph->SetLineWidth(3);
    
    TH1F *bwpAu4 = new TH1F("bwpAu4","bwpAu4",100,1.3,4.9);
    bwpAu4->SetMinimum(0.007495577);
    bwpAu4->SetMaximum(0.01375894);
    bwpAu4->SetDirectory(0);
    bwpAu4->SetStats(0);
    
    ci = TColor::GetColor("#000099");
    bwpAu4->SetLineColor(ci);
    bwpAu4->GetXaxis()->SetLabelFont(42);
    bwpAu4->GetXaxis()->SetLabelSize(0.06);
    bwpAu4->GetXaxis()->SetTitleSize(0.06);
    bwpAu4->GetXaxis()->SetTitleOffset(1.2);
    bwpAu4->GetXaxis()->SetTitleFont(42);
    bwpAu4->GetYaxis()->SetLabelFont(42);
    bwpAu4->GetYaxis()->SetLabelSize(0.06);
    bwpAu4->GetYaxis()->SetTitleSize(0.06);
    bwpAu4->GetYaxis()->SetTitleFont(42);
    bwpAu4->GetZaxis()->SetLabelFont(42);
    bwpAu4->GetZaxis()->SetLabelSize(0.035);
    bwpAu4->GetZaxis()->SetTitleSize(0.035);
    bwpAu4->GetZaxis()->SetTitleFont(42);
    graph->SetHistogram(bwpAu4);
    
    if(plot==0 || plot==22) graph->Draw("c");


    Double_t heikki1_fx5[19] = {
	1,
	1.23795,
	1.47591,
	1.71386,
	1.95182,
	2.18977,
	2.42773,
	2.661141,
	2.90364,
	3.14159,
	3.379542,
	3.617492,
	3.855442,
	4.093392,
	4.331342,
	4.569292,
	4.807242,
	5.045192,
	5.283142};
    Double_t heikki1_fy5[19] = {
	0.03492293,
	0.03492592,
	0.03510954,
	0.03548827,
	0.03611033,
	0.03706098,
	0.03859527,
	0.04103788,
	0.04313032,
	0.04387093,
	0.04313032,
	0.04083448,
	0.03859527,
	0.03706098,
	0.03611033,
	0.03548827,
	0.03510954,
	0.03492592,
	0.03492293};
    graph = new TGraph(19,heikki1_fx5,heikki1_fy5);
    graph->SetName("heikki1");
    graph->SetTitle("heikki1");
    graph->SetFillColor(1);
    graph->SetLineColor(2);
    if(color>0) graph->SetLineColor(color);
    graph->SetLineStyle(7);
    graph->SetLineWidth(3);
    
    TH1F *heikki1 = new TH1F("heikki1","heikki1",100,1.64,4.64);
    heikki1->SetMinimum(0.00078546);
    heikki1->SetMaximum(0.1438151);
    heikki1->SetDirectory(0);
    heikki1->SetStats(0);
    
    ci = TColor::GetColor("#000099");
    heikki1->SetLineColor(ci);
    heikki1->GetXaxis()->SetLabelFont(42);
    heikki1->GetXaxis()->SetLabelSize(0.06);
    heikki1->GetXaxis()->SetTitleSize(0.06);
    heikki1->GetXaxis()->SetTitleOffset(1.2);
    heikki1->GetXaxis()->SetTitleFont(42);
    heikki1->GetYaxis()->SetLabelFont(42);
    heikki1->GetYaxis()->SetLabelSize(0.06);
    heikki1->GetYaxis()->SetTitleSize(0.06);
    heikki1->GetYaxis()->SetTitleFont(42);
    heikki1->GetZaxis()->SetLabelFont(42);
    heikki1->GetZaxis()->SetLabelSize(0.035);
    heikki1->GetZaxis()->SetTitleSize(0.035);
    heikki1->GetZaxis()->SetTitleFont(42);
    graph->SetHistogram(heikki1);
    
    if(plot==0 || plot==5) graph->Draw("c");
    
    Double_t heikki2_fx6[19] = {
	1.007751,
	1.233947,
	1.470915,
	1.713269,
	1.950237,
	2.187205,
	2.424173,
	2.661141,
	2.903494,
	3.140462,
	3.37743,
	3.614398,
	3.851366,
	4.088334,
	4.330688,
	4.567656,
	4.804624,
	5.041592,
	5.27856};
    Double_t heikki2_fy6[19] = {
	0.003568482,
	0.003638892,
	0.003638892,
	0.003710691,
	0.003783906,
	0.0039347,
	0.004254554,
	0.004783742,
	0.0055931,
	0.005930747,
	0.0055931,
	0.004783742,
	0.004254554,
	0.0039347,
	0.003783906,
	0.003710691,
	0.003638892,
	0.003638892,
	0.003568482};
    graph = new TGraph(19,heikki2_fx6,heikki2_fy6);
    graph->SetName("heikki2");
    graph->SetTitle("heikki2");
    graph->SetFillColor(1);
    graph->SetLineColor(8);
    graph->SetLineStyle(7);
    if(color>0) {
	graph->SetLineColor(color);
	graph->SetLineStyle(0);
    }
    graph->SetLineWidth(3);
    
    TH1F *heikki2 = new TH1F("heikki2","heikki2",100,0.5716858,5.711456);
    heikki2->SetMinimum(0.003338579);
    heikki2->SetMaximum(0.006094917);
    heikki2->SetDirectory(0);
    heikki2->SetStats(0);
    
    ci = TColor::GetColor("#000099");
    heikki2->SetLineColor(ci);
    heikki2->GetXaxis()->SetLabelFont(42);
    heikki2->GetXaxis()->SetLabelSize(0.06);
    heikki2->GetXaxis()->SetTitleSize(0.06);
    heikki2->GetXaxis()->SetTitleOffset(1.2);
    heikki2->GetXaxis()->SetTitleFont(42);
    heikki2->GetYaxis()->SetLabelFont(42);
    heikki2->GetYaxis()->SetLabelSize(0.06);
    heikki2->GetYaxis()->SetTitleSize(0.06);
    heikki2->GetYaxis()->SetTitleFont(42);
    heikki2->GetZaxis()->SetLabelFont(42);
    heikki2->GetZaxis()->SetLabelSize(0.035);
    heikki2->GetZaxis()->SetTitleSize(0.035);
    heikki2->GetZaxis()->SetTitleFont(42);
    graph->SetHistogram(heikki2);
    
    if(plot==0 || plot==6) graph->Draw("c");
   
    Double_t heikki3_fx7[19] = {
	1.002365,
	1.233947,
	1.470915,
	1.713269,
	1.950237,
	2.187205,
	2.424173,
	2.661141,
	2.903494,
	3.140462,
	3.37743,
	3.614398,
	3.851366,
	4.088334,
	4.330688,
	4.567656,
	4.804624,
	5.041592,
	5.27856};
    Double_t heikki3_fy7[19] = {
	0.0004677136,
	0.0004677136,
	0.0004677136,
	0.000476942,
	0.0004863525,
	0.0005157129,
	0.0005686383,
	0.0006779639,
	0.000908847,
	0.001042054,
	0.000908847,
	0.0006779639,
	0.0005686383,
	0.0005157129,
	0.0004863525,
	0.000476942,
	0.0004677136,
	0.0004677136,
	0.0004677136};
    graph = new TGraph(19,heikki3_fx7,heikki3_fy7);
    graph->SetName("heikki3");
    graph->SetTitle("heikki3");
    graph->SetFillColor(1);
    graph->SetLineColor(4);
    if(color>0) {
	graph->SetLineColor(color);
	graph->SetLineStyle(0);
    }
    graph->SetLineWidth(3);
    
    TH1F *heikki3 = new TH1F("heikki3","heikki3",100,0.5716858,5.711456);
    heikki3->SetMinimum(0.0004076624);
    heikki3->SetMaximum(0.001080297);
    heikki3->SetDirectory(0);
    heikki3->SetStats(0);
    
    ci = TColor::GetColor("#000099");
    heikki3->SetLineColor(ci);
    heikki3->GetXaxis()->SetLabelFont(42);
    heikki3->GetXaxis()->SetLabelSize(0.06);
    heikki3->GetXaxis()->SetTitleSize(0.06);
    heikki3->GetXaxis()->SetTitleOffset(1.2);
    heikki3->GetXaxis()->SetTitleFont(42);
    heikki3->GetYaxis()->SetLabelFont(42);
    heikki3->GetYaxis()->SetLabelSize(0.06);
    heikki3->GetYaxis()->SetTitleSize(0.06);
    heikki3->GetYaxis()->SetTitleFont(42);
    heikki3->GetZaxis()->SetLabelFont(42);
    heikki3->GetZaxis()->SetLabelSize(0.035);
    heikki3->GetZaxis()->SetTitleSize(0.035);
    heikki3->GetZaxis()->SetTitleFont(42);
    graph->SetHistogram(heikki3);
    
    if(plot==0 || plot==7) graph->Draw("c");
    
    if(plot==0){
	TLatex *   tex = new TLatex(2.32,1.088268e-05,"1.5<p_{T}_{1}<2.0, 0.5<p_{T}_{2}<1.0 GeV/c");
	tex->SetTextColor(2);
	tex->SetTextSize(0.035);
	tex->SetLineWidth(3);
	tex->Draw();
	tex = new TLatex(2.32,6.148515e-06,"2.0<p_{T}_{1}<2.5, 1.0<p_{T}_{2}<1.5 GeV/c");
	tex->SetTextColor(8);
	tex->SetTextSize(0.035);
	tex->SetLineWidth(3);
	tex->Draw();
	tex = new TLatex(2.32,3.522513e-06,"2.5<p_{T}_{1}<3.0, 1.5<p_{T}_{2}<2.0 GeV/c");
	tex->SetTextColor(4);
	tex->SetTextSize(0.035);
	tex->SetTextAngle(0.5748547);
	tex->SetLineWidth(3);
	tex->Draw();
	tex = new TLatex(2.32,1.990156e-06,"3.0<p_{T}_{1}<4.0, 2.0<p_{T}_{2}<2.5 GeV/c");
	tex->SetTextSize(0.035);
	tex->SetLineWidth(3);
	tex->Draw();
	c1->Modified();
	c1->cd();
	c1->SetSelected(c1);
	c1->ToggleToolBar();
    }
}

