static const double PI=TMath::Pi();
static const double twoPI=PI*2.0;
static const int kNPtBin=6;
static const int kNCut=26;

float PAR0[kNPtBin][kNPtBin][kNCut][3];
float PAR1[kNPtBin][kNPtBin][kNCut][3];
float PAR2[kNPtBin][kNPtBin][kNCut][3];
float ERR0[kNPtBin][kNPtBin][kNCut][3];
float ERR1[kNPtBin][kNPtBin][kNCut][3];
float ERR2[kNPtBin][kNPtBin][kNCut][3];
float CHI[kNPtBin][kNPtBin][kNCut][3];

TLatex* drawLatex(Double_t x, Double_t y, TString text, Int_t textFont, Double_t textSize, Int_t colorIndex){
  TLatex *latex = new TLatex(x,y,text);
  latex->SetNDC();
  latex->SetTextFont(textFont);
  latex->SetTextSize(textSize);
  latex->SetTextColor(colorIndex);
  latex->Draw("same");
  return latex;
}

TLatex* drawTof(Double_t x, Double_t y, TString text, Int_t textFont, Double_t textSize, Int_t colorIndex){
  TLatex *latex = new TLatex(x,y,text);
  latex->SetTextFont(textFont);
  latex->SetTextSize(textSize);
  latex->SetTextColor(colorIndex);
  latex->Draw("same");
  return latex;
}

void readpar(int beam, int cut, int corr, int print=0){
    char name[200];
    sprintf(name,"../txt/beam%d_cut%d_corr%d.par",beam,cut,corr);
    if(print>0) printf("Reading %s\n",name);
    FILE* f=fopen(name,"r");
    for(int i=1;i<kNPtBin; i++){
        for(int j=1; j<i; j++){
            fscanf(f,"%f %f %f %f %f %f %f\n",
                   &(PAR0[i][j][cut][beam]),&(PAR1[i][j][cut][beam]),&(PAR2[i][j][cut][beam]),
                   &(ERR0[i][j][cut][beam]),&(ERR1[i][j][cut][beam]),&(ERR2[i][j][cut][beam]),&(CHI[i][j][cut][beam]));
            if(i>0 && j>0 && print==1)
                printf("%1d %d %1d %1d %10.6f %10.6f %10.6f %10.6f %10.6f %10.6f %10.6f %d\n",
                       beam,cut,i,j,
                       PAR0[i][j][cut][beam],PAR1[i][j][cut][beam],PAR2[i][j][cut][beam],
                       ERR0[i][j][cut][beam],ERR1[i][j][cut][beam],ERR2[i][j][cut][beam],CHI[i][j][cut][beam]);
                       }
		}
	fclose(f);
}


Double_t oneGaus(Double_t *x, Double_t *par){
    Double_t OP=1.0/sqrt(2.0*PI);
    Double_t x1 = x[0]+PI;
    while(x1<-PI) x1+=2.0*PI;
    while(x1>=PI) x1-=2.0*PI;
    Double_t f = par[0]/2.0/PI;
    f += par[1]*OP/par[2]*exp(-x1*x1/2.0/par[2]/par[2]);
    return f;
}

Double_t ratioerr(Double_t a, Double_t aerr,Double_t b,Double_t berr){
     Double_t e = a/b * sqrt(pow(aerr/a,2)+pow(berr/b,2));
     return e;
}

void sumSigma()
{
	gStyle->SetOptTitle(0);
	gStyle->SetPadGridX(0);
	gStyle->SetPadGridY(0);
	gStyle->SetEndErrorSize(8);
//theory from cyrill
//int BBC[4]= {3000,12000,24000,36000};
int BBC[4] = {7300,18000,30000,43500};
int shift = 850;
Double_t cyrillepp_dphi[27] = {1.041592653589793,1.341592653589793,1.6415926535897931,1.9415926535897932,2.241592653589793,2.441592653589793,2.641592653589793,2.8415926535897933,2.941592653589793 ,3.041592653589793,3.0915926535897933,3.116592653589793 ,3.126592653589793,3.141592653589793,3.1565926535897932 ,3.166592653589793,3.191592653589793,3.241592653589793,3.3415926535897933,3.441592653589793,3.641592653589793,3.8415926535897933,4.0415926535897935,4.341592653589793,4.641592653589793 ,4.941592653589793,5.241592653589793
};
Double_t cyrillepp_pt21[27]={0.0013938998641915116,0.0013832373032955725,0.0015700358967885308,0.001993093711414387,0.0027983636896036232,0.0036801003906890444,0.004942972695818311,0.006513542714757178,0.0072397022859074294,0.007736853862220406,0.007863505585692144,0.007894863876287123,0.00790152750566637,0.007905267701113296,0.00790152750566637,0.007894863876287123,0.007863505585692144,0.007736853862220406,0.0072397022859074294,0.006513542714757178,0.004942972695818311,0.0036801003906890444,0.0027983636896036232,0.001993093711414387,0.0015700358967885308,0.0013832373032955725,0.0013938998641915116};
Double_t cyrillepp_pt31[27]={0.00031808187311126336,0.00031278303646312735,0.0003532751229823465,0.00045162572818184185,0.000662020171879133,0.0009401233124314776,0.0014719340779195485,0.0025400423049006856,0.003351658420158297,0.00414806453338066,0.004385143213525191,0.004442628923833037,0.004454587648473964,0.004461250629324608,0.004454587648473964,0.004442628923833037,0.004385143213525191,0.00414806453338066,0.003351658420158297,0.0025400423049006856,0.0014719340779195485,0.0009401233124314776,0.000662020171879133,0.00045162572818184185,0.0003532751229823465,0.00031278303646312735,0.00031808187311126336};
Double_t cyrillepp_pt41[27]={0.0002505549964887706,0.00024486252899197917,0.00027365268513919125,0.00034343953638933244,0.0004882573895767407,0.0006746446840186107,0.0010309634703026108,0.0017956381654542447,0.0024458735993916968,0.0031603235909835052,0.0033882537551985473,0.003443631991365256,0.003455073386054155,0.003461423365958762,0.003455073386054155,0.003443631991365256,0.0033882537551985473,0.0031603235909835052,0.0024458735993916968,0.0017956381654542447,0.0010309634703026108,0.0006746446840186107,0.0004882573895767407,0.00034343953638933244,0.00027365268513919125,0.00024486252899197917,0.0002505549964887706};
Double_t cyrillepp_pt51[27]={
0.00018379762465705793	
,0.00017815857707671357	
,0.0001961869242099673	
,0.00023986340240013515	
,0.00032560466579881464	
,0.00042858021976450647	
,0.000612684056425105	
,0.0009966252377145981	
,0.0013372576265278393	
,0.0017421235296086988	
,0.0018808837747315561	
,0.0019155123569402233	
,0.0019227168724805675	
,0.001926723068092276	
,0.0019227168724805675	
,0.0019155123569402233	
,0.0018808837747315561	
,0.0017421235296086988	
,0.0013372576265278393	
,0.0009966252377145981	
,0.000612684056425105	
,0.00042858021976450647	
,0.00032560466579881464	
,0.00023986340240013515	
,0.0001961869242099673	
,0.00017815857707671357	
,0.00018379762465705793	
};
Double_t cyrillepp_pt32[27]={
0.00006394289565545205	
,0.00006315074388283766	
,0.00007218658998604518	
,0.00009435094587724685	
,0.0001438991750126036	
,0.0002136239791390511	
,0.0003580341389123151	
,0.0006807198678903494	
,0.0009493596517434512	
,0.0012332388108450014	
,0.0013219385807171637	
,0.0013434799658534734	
,0.0013479354482889767	
,0.0013504097099029696	
,0.0013479354482889767	
,0.0013434799658534734	
,0.0013219385807171637	
,0.0012332388108450014	
,0.0009493596517434512	
,0.0006807198678903494	
,0.0003580341389123151	
,0.0002136239791390511	
,0.0001438991750126036	
,0.00009435094587724685	
,0.00007218658998604518	
,0.00006315074388283766	
,0.00006394289565545205	
};
Double_t cyrillepp_pt42[27]={0.00004813310131785156,0.00004739060856705321,0.00005389301220552927,0.00006969347139206258,0.0001042172416877134,0.0001519193939044362,0.0002513775823005786,0.0004897460972060204,0.0007101250651809976,0.0009650684363108454,0.0010476781834748519,0.0010675147957394844,0.0010715810283179542,0.001073833664696748,0.0010715810283179542,0.0010675147957394844,0.0010476781834748519,0.0009650684363108454,0.0007101250651809976,0.0004897460972060204,0.0002513775823005786,0.0001519193939044362,0.0001042172416877134,0.00006969347139206258,0.00005389301220552927,0.00004739060856705321,0.00004813310131785156};
Double_t cyrillepp_pt52[27]={
0.00003341860399866375	
,0.000032706123253327834	
,0.00003679134090642477	
,0.00004663178071499499	
,0.00006713961142180583	
,0.00009388991002921622	
,0.00014719581869017463	
,0.0002794066821113614	
,0.00042054247003928705	
,0.0006174065633345941	
,0.00068796168973278	
,0.0007042962963817561	
,0.0007075180766571473	
,0.0007092754898873724	
,0.0007075180766571473	
,0.0007042962963817561	
,0.00068796168973278	
,0.0006174065633345941	
,0.00042054247003928705	
,0.0002794066821113614	
,0.00014719581869017463	
,0.00009388991002921622	
,0.00006713961142180583	
,0.00004663178071499499	
,0.00003679134090642477	
,0.000032706123253327834	
,0.00003341860399866375	
};
Double_t cyrillepp_pt53[27]={7.810751518464136e-6,7.690341705774283e-6,8.761624210901256e-6,0.000011365508272546918,0.00001702147695853648,0.00002482345371687858,0.00004142788216839504,0.00008560462543149372,0.0001338697418691557,0.0002006852321438478,0.00022541725666372497,0.00023157290446212798,0.0002328387304898879,0.00023353761904767908,0.0002328387304898879,0.00023157290446212798,0.00022541725666372497,0.0002006852321438478,0.0001338697418691557,0.00008560462543149372,0.00004142788216839504,0.00002482345371687858,0.00001702147695853648,0.000011365508272546918,8.761624210901256e-6,7.690341705774283e-6,7.810751518464136e-6};
Double_t cyrillepAu_pt21[27]={0.00042251933101532523,0.00041827846527429013,0.00047678992240753423,0.0006181414275960982,0.0009221118519568706,0.0013186680634992077,0.0020405536964648832,0.003337777877288067,0.0042117934631788825,0.005000391282892456,0.005227203554456209,0.005282290215350687,0.005293783890876901,0.005300187713559647,0.005293783890876901,0.005282290215350687,0.005227203554456209,0.005000391282892456,0.0042117934631788825,0.003337777877288067,0.0020405536964648832,0.0013186680634992077,0.0009221118519568706,0.0006181414275960982,0.00047678992240753423,0.00041827846527429013,0.00042251933101532523};
Double_t cyrillepAu_pt31[27]={0.0003612160159149545,0.00035809508420836685,0.00040727099443404796,0.0005206012012499747,0.0007442538424379051,0.0010023103843070829,0.0013979908112781712,0.001936258694242614,0.002203038267011911,0.0023915724255742445,0.0024401353368686423,0.0024521734003989304,0.0024547317500543,0.0024561688141574644,0.0024547317500543,0.0024521734003989304,0.0024401353368686423,0.0023915724255742445,0.002203038267011911,0.001936258694242614,0.0013979908112781712,0.0010023103843070829,0.0007442538424379051,0.0005206012012499747,0.00040727099443404796,0.00035809508420836685,0.0003612160159149545};
Double_t cyrillepAu_pt41[27]={0.0002679173328089066,0.0002644402940781783,0.0002990353089197551,0.00037959962255339756,0.0005402048677076802,0.0007300011302180103,0.001034497874281517,0.0014829767500658436,0.0017228316498807802,0.0018993574435833978,0.0019453086913531485,0.0019566693272394906,0.0019590803169976865,0.0019604333042075586,0.0019590803169976865,0.0019566693272394906,0.0019453086913531485,0.0018993574435833978,0.0017228316498807802,0.0014829767500658436,0.001034497874281517,0.0007300011302180103,0.0005402048677076802,0.00037959962255339756,0.0002990353089197551,0.0002644402940781783,0.0002679173328089066};
Double_t cyrillepAu_pt51[27]={
0.00019061448509069122
,0.00018666527800637503
,0.00020825871181843401
,0.00025877659429170125
,0.00035723626247972
,0.00047163965293443844
,0.0006558352862272376
,0.0009382528408218371
,0.0010985950358374766
,0.0012226490568014172
,0.0012561382218766876
,0.001264524668805077
,0.001266310796761856
,0.0012673142619012386
,0.001266310796761856
,0.001264524668805077
,0.0012561382218766876
,0.0012226490568014172
,0.0010985950358374766
,0.0009382528408218371
,0.0006558352862272376
,0.00047163965293443844
,0.00035723626247972
,0.00025877659429170125
,0.00020825871181843401
,0.00018666527800637503
,0.00019061448509069122
};
Double_t cyrillepAu_pt32[27]={
0.00007272081129180481
,0.00007255608142944159
,0.00008391076966692072
,0.00011060033096852587
,  0.00016651166996533702
,  0.00023582320171136728
,  0.0003505551485882633
,  0.0005208860356672569
,  0.000611000952504341
,  0.0006765876014424865
,  0.0006935310576891039
,  0.0006977091997497441
,  0.0006985952687555046
,  0.0006990924536753347
,  0.0006985952687555046
,  0.0006977091997497441
,  0.0006935310576891039
,  0.0006765876014424865
,  0.000611000952504341
,  0.0005208860356672569
,  0.0003505551485882633
,  0.00023582320171136728
,  0.00016651166996533702
,0.00011060033096852587
,0.00008391076966692072
,0.00007255608142944159
,0.00007272081129180481
};
Double_t cyrillepAu_pt42[27]={0.00005134317353809318,0.00005112423746370942,0.000058981616697435465,0.00007755567013040841,0.00011701153781975224,0.00016740260572919562,0.0002551133461094629,0.0003961355981539536,0.00047601993310784137,0.0005360450016331008,0.0005516541646544155,0.0005554940811804245,0.0005563075173845463,0.0005567639950220811,0.0005563075173845463,0.0005554940811804245,0.0005516541646544155,0.0005360450016331008,0.00047601993310784137,0.0003961355981539536,0.0002551133461094629,0.00016740260572919562,0.00011701153781975224,0.00007755567013040841,0.000058981616697435465,0.00005112423746370942,0.00005134317353809318};
Double_t cyrillepAu_pt52[27]={
0.0000345189356747537
,0.00003417039475543601
,0.00003901914104028335
,0.000050441224175444775
,0.00007428632798117417
,0.00010455329307418936
,0.00015845004723298554
,0.00025246342896729904
,0.0003113184392673756
,0.00035781689684270395
,0.00036976345899393146
,0.0003726327188546222
,0.00037323509969163404
,0.00037357220903348325
,0.00037323509969163404
,0.0003726327188546222
,0.00036976345899393146
,0.00035781689684270395
,0.0003113184392673756
,0.00025246342896729904
,0.00015845004723298554
,0.00010455329307418936
,0.00007428632798117417
,0.000050441224175444775
,0.00003901914104028335
,0.00003417039475543601
,0.0000345189356747537
};
Double_t cyrillepAu_pt53[27]={8.035558030881161e-6,8.00618604243299e-6,9.272028817197547e-6,0.000012296645433118835,0.00001894784941197356,0.000027957826024474038,0.00004515180398781511,0.00007723509017786493,0.00009814718063916196,0.00011521534548833548,0.00011977791671351406,0.00012089728493668655,0.00012113387104742701,0.00012126629054607242,0.00012113387104742701,0.00012089728493668655,0.00011977791671351406,0.00011521534548833548,0.00009814718063916196,0.00007723509017786493,0.00004515180398781511,0.000027957826024474038,0.00001894784941197356,0.000012296645433118835,9.272028817197547e-6,8.00618604243299e-6,8.035558030881161e-6};
    
    TGraph *graphpp21 = new TGraph(27,cyrillepp_dphi,cyrillepp_pt21);
    TGraph *graphpp31 = new TGraph(27,cyrillepp_dphi,cyrillepp_pt31);
    TGraph *graphpp41 = new TGraph(27,cyrillepp_dphi,cyrillepp_pt51);
    TGraph *graphpp51 = new TGraph(27,cyrillepp_dphi,cyrillepp_pt51);
    TGraph *graphpp32 = new TGraph(27,cyrillepp_dphi,cyrillepp_pt32);
    TGraph *graphpp42 = new TGraph(27,cyrillepp_dphi,cyrillepp_pt42);
    TGraph *graphpp52 = new TGraph(27,cyrillepp_dphi,cyrillepp_pt52);
    TGraph *graphpp53 = new TGraph(27,cyrillepp_dphi,cyrillepp_pt53);
    TGraph *graphpAu21 = new TGraph(27,cyrillepp_dphi,cyrillepAu_pt21);
    TGraph *graphpAu31 = new TGraph(27,cyrillepp_dphi,cyrillepAu_pt31);
    TGraph *graphpAu41 = new TGraph(27,cyrillepp_dphi,cyrillepAu_pt51);
    TGraph *graphpAu51 = new TGraph(27,cyrillepp_dphi,cyrillepAu_pt51);
    TGraph *graphpAu32 = new TGraph(27,cyrillepp_dphi,cyrillepAu_pt32);
    TGraph *graphpAu42 = new TGraph(27,cyrillepp_dphi,cyrillepAu_pt42);
    TGraph *graphpAu52 = new TGraph(27,cyrillepp_dphi,cyrillepAu_pt52);
    TGraph *graphpAu53 = new TGraph(27,cyrillepp_dphi,cyrillepAu_pt53);

    float norm3=1.0;
    double PAR0pp[8],PAR1pp[8],PAR2pp[8];
    double PARErr0pp[8],PARErr1pp[8],PARErr2pp[8];
double PAR0pAu[8],PAR1pAu[8],PAR2pAu[8];
    double PARErr0pAu[8],PARErr1pAu[8],PARErr2pAu[8];
    
    f=new TF1("oneGaus",oneGaus,+PI/2.0,+PI*3.0/2.0,3);
    f->SetParameters(norm3/10.0,norm3/2.0,0.3);
    f->SetParNames("Const","IntFar","SigFar");
    f->SetParLimits(0,0.0,1.0);
    f->SetParLimits(1,0.0,1.0);
    f->SetParLimits(2,0.0,3.0);
    f->SetLineColor(10); f->SetLineWidth(2);

    graphpp21->Fit("oneGaus","Q");
    PAR0pp[0]=f->GetParameter(0);
    PAR1pp[0]=f->GetParameter(1);
    PAR2pp[0]=f->GetParameter(2);
    PARErr0pp[0]=f->GetParError(0);
    PARErr1pp[0]=f->GetParError(1);
    PARErr2pp[0]=f->GetParError(2);
    graphpp21->SetLineColor(kRed);
    graphpAu21->Fit("oneGaus","Q");
    PAR0pAu[0]=f->GetParameter(0);
    PAR1pAu[0]=f->GetParameter(1);
    PAR2pAu[0]=f->GetParameter(2);
    PARErr0pAu[0]=f->GetParError(0);
    PARErr1pAu[0]=f->GetParError(1);
    PARErr2pAu[0]=f->GetParError(2);

    graphpp31->Fit("oneGaus","Q");
    PAR0pp[1]=f->GetParameter(0);
    PAR1pp[1]=f->GetParameter(1);
    PAR2pp[1]=f->GetParameter(2);
    PARErr0pp[1]=f->GetParError(0);
    PARErr1pp[1]=f->GetParError(1);
    PARErr2pp[1]=f->GetParError(2);
    graphpp31->SetLineColor(kRed);
    graphpAu31->Fit("oneGaus","Q");
    PAR0pAu[1]=f->GetParameter(0);
    PAR1pAu[1]=f->GetParameter(1);
    PAR2pAu[1]=f->GetParameter(2);
    PARErr0pAu[1]=f->GetParError(0);
    PARErr1pAu[1]=f->GetParError(1);
    PARErr2pAu[1]=f->GetParError(2);

    graphpp41->Fit("oneGaus","Q");
    PAR0pp[2]=f->GetParameter(0);
    PAR1pp[2]=f->GetParameter(1);
    PAR2pp[2]=f->GetParameter(2);
    PARErr0pp[2]=f->GetParError(0);
    PARErr1pp[2]=f->GetParError(1);
    PARErr2pp[2]=f->GetParError(2);
    graphpAu41->Fit("oneGaus","Q");
    PAR0pAu[2]=f->GetParameter(0);
    PAR1pAu[2]=f->GetParameter(1);
    PAR2pAu[2]=f->GetParameter(2);
    PARErr0pAu[2]=f->GetParError(0);
    PARErr1pAu[2]=f->GetParError(1);
    PARErr2pAu[2]=f->GetParError(2);

    graphpp51->Fit("oneGaus","Q");
    PAR0pp[3]=f->GetParameter(0);
    PAR1pp[3]=f->GetParameter(1);
    PAR2pp[3]=f->GetParameter(2);
    PARErr0pp[3]=f->GetParError(0);
    PARErr1pp[3]=f->GetParError(1);
    PARErr2pp[3]=f->GetParError(2);
    graphpAu51->Fit("oneGaus","Q");
    PAR0pAu[3]=f->GetParameter(0);
    PAR1pAu[3]=f->GetParameter(1);
    PAR2pAu[3]=f->GetParameter(2);
    PARErr0pAu[3]=f->GetParError(0);
    PARErr1pAu[3]=f->GetParError(1);
    PARErr2pAu[3]=f->GetParError(2);

    graphpp32->Fit("oneGaus","Q");
    PAR0pp[4]=f->GetParameter(0);
    PAR1pp[4]=f->GetParameter(1);
    PAR2pp[4]=f->GetParameter(2);
    PARErr0pp[4]=f->GetParError(0);
    PARErr1pp[4]=f->GetParError(1);
    PARErr2pp[4]=f->GetParError(2);
    graphpAu32->Fit("oneGaus","Q");
    PAR0pAu[4]=f->GetParameter(0);
    PAR1pAu[4]=f->GetParameter(1);
    PAR2pAu[4]=f->GetParameter(2);
    PARErr0pAu[4]=f->GetParError(0);
    PARErr1pAu[4]=f->GetParError(1);
    PARErr2pAu[4]=f->GetParError(2);

    graphpp42->Fit("oneGaus","Q");
    PAR0pp[5]=f->GetParameter(0);
    PAR1pp[5]=f->GetParameter(1);
    PAR2pp[5]=f->GetParameter(2);
    PARErr0pp[5]=f->GetParError(0);
    PARErr1pp[5]=f->GetParError(1);
    PARErr2pp[5]=f->GetParError(2);
    graphpAu42->Fit("oneGaus","Q");
    PAR0pAu[5]=f->GetParameter(0);
    PAR1pAu[5]=f->GetParameter(1);
    PAR2pAu[5]=f->GetParameter(2);
    PARErr0pAu[5]=f->GetParError(0);
    PARErr1pAu[5]=f->GetParError(1);
    PARErr2pAu[5]=f->GetParError(2);

    graphpp52->Fit("oneGaus","Q");
    PAR0pp[6]=f->GetParameter(0);
    PAR1pp[6]=f->GetParameter(1);
    PAR2pp[6]=f->GetParameter(2);
    PARErr0pp[6]=f->GetParError(0);
    PARErr1pp[6]=f->GetParError(1);
    PARErr2pp[6]=f->GetParError(2);
    graphpAu52->Fit("oneGaus","Q");
    PAR0pAu[6]=f->GetParameter(0);
    PAR1pAu[6]=f->GetParameter(1);
    PAR2pAu[6]=f->GetParameter(2);
    PARErr0pAu[6]=f->GetParError(0);
    PARErr1pAu[6]=f->GetParError(1);
    PARErr2pAu[6]=f->GetParError(2);

    graphpAu53->SetLineColor(kBlue);
    graphpp53->Fit("oneGaus","Q");
    PAR0pp[7]=f->GetParameter(0);
    PAR1pp[7]=f->GetParameter(1);
    PAR2pp[7]=f->GetParameter(2);
    PARErr0pp[7]=f->GetParError(0);
    PARErr1pp[7]=f->GetParError(1);
    PARErr2pp[7]=f->GetParError(2);
    graphpp53->SetLineColor(kRed);
    graphpAu53->Fit("oneGaus","Q");
    PAR0pAu[7]=f->GetParameter(0);
    PAR1pAu[7]=f->GetParameter(1);
    PAR2pAu[7]=f->GetParameter(2);
    PARErr0pAu[7]=f->GetParError(0);
    PARErr1pAu[7]=f->GetParError(1);
    PARErr2pAu[7]=f->GetParError(2);
    graphpAu53->SetLineColor(kBlue);

TGraphErrors* cyrill21 = new TGraphErrors();
        cyrill21->SetPoint(0, BBC[3]-shift,PAR2pAu[0]/PAR2pp[0]);
        cyrill21->SetPointError(0, 0.0,10*ratioerr(PAR2pAu[0],PARErr2pAu[0],PAR2pp[0],PARErr2pp[0]));
/*
        cyrill21->SetPoint(1, BBC[3],PAR2pAu[1]/PAR2pp[1]);
        cyrill21->SetPointError(1, 0.0,10*ratioerr(PAR2pAu[1],PARErr2pAu[1],PAR2pp[1],PARErr2pp[1]));
        cyrill21->SetPoint(2, BBC[3]+shift,PAR2pAu[2]/PAR2pp[2]);
        cyrill21->SetPointError(2, 0.0,10*ratioerr(PAR2pAu[2],PARErr2pAu[2],PAR2pp[2],PARErr2pp[2]));
        cyrill21->SetPoint(3, BBC[3]+2*shift,PAR2pAu[3]/PAR2pp[3]);
        cyrill21->SetPointError(3, 0.0,10*ratioerr(PAR2pAu[3],PARErr2pAu[3],PAR2pp[3],PARErr2pp[3]));
*/
TGraphErrors* cyrill32 = new TGraphErrors();
  //      cyrill32->SetPoint(0, BBC[3]-1*shift,PAR2pAu[4]/PAR2pp[4]);
    //    cyrill32->SetPointError(0, 0.0,10*ratioerr(PAR2pAu[4],PARErr2pAu[4],PAR2pp[4],PARErr2pp[4]));
        cyrill32->SetPoint(0, BBC[3],PAR2pAu[5]/PAR2pp[5]);
        cyrill32->SetPointError(0, 0.0,10*ratioerr(PAR2pAu[5],PARErr2pAu[5],PAR2pp[5],PARErr2pp[5]));
      //  cyrill32->SetPoint(2, BBC[3]+1*shift,PAR2pAu[6]/PAR2pp[6]);
        //cyrill32->SetPointError(2, 0.0,10*ratioerr(PAR2pAu[6],PARErr2pAu[6],PAR2pp[6],PARErr2pp[6]));

TGraphErrors* cyrill53 = new TGraphErrors();
        cyrill53->SetPoint(0, BBC[3]+shift,PAR2pAu[7]/PAR2pp[7]);
        cyrill53->SetPointError(0, 0.0,10*ratioerr(PAR2pAu[7],PARErr2pAu[7],PAR2pp[7],PARErr2pp[7]));

	memset(PAR0,0,sizeof(PAR0));
	memset(PAR1,0,sizeof(PAR1));
	memset(PAR2,0,sizeof(PAR2));
	memset(ERR0,0,sizeof(ERR0));
	memset(ERR0,0,sizeof(ERR0));
        memset(ERR1,0,sizeof(ERR1));
        memset(ERR2,0,sizeof(ERR2));

	readpar(0,2,1,1);//pp
	readpar(3,4,1,1);//pAu1 3000<BBCE<12000
	readpar(3,5,1,1);//pAu1 12000<BBCE<24000
        readpar(3,15,1,1);//pAu1 24000<BBCE<36000
	readpar(3,16,1,1);//pAu1 36000<BBCE

        //calculate ratio pAu/pp, and error
	double RAT2_4[kNPtBin][kNPtBin],RAT2_5[kNPtBin][kNPtBin],RAT2_16[kNPtBin][kNPtBin],RAT2_15[kNPtBin][kNPtBin];
	double ERROR2_4[kNPtBin][kNPtBin],ERROR2_5[kNPtBin][kNPtBin],ERROR2_16[kNPtBin][kNPtBin],ERROR2_15[kNPtBin][kNPtBin];
	
        for(int i=1;i<kNPtBin; i++){
		for(int j=1; j<i; j++){
			//ratio
			RAT2_4[i][j] = PAR2[i][j][4][3]/PAR2[i][j][2][0];
			RAT2_5[i][j]= PAR2[i][j][5][3]/PAR2[i][j][2][0];
			RAT2_15[i][j]= PAR2[i][j][15][3]/PAR2[i][j][2][0];
			RAT2_16[i][j] = PAR2[i][j][16][3]/PAR2[i][j][2][0];

			//statistic error
			ERROR2_4[i][j] = RAT2_4[i][j]*sqrt(pow(ERR2[i][j][4][3],2)/pow(PAR2[i][j][4][3],2)+pow(ERR2[i][j][2][0],2)/pow(PAR2[i][j][2][0],2));
			ERROR2_5[i][j] = RAT2_5[i][j]*sqrt(pow(ERR2[i][j][5][3],2)/pow(PAR2[i][j][5][3],2)+pow(ERR2[i][j][2][0],2)/pow(PAR2[i][j][2][0],2));
			ERROR2_15[i][j] = RAT2_15[i][j]*sqrt(pow(ERR2[i][j][15][3],2)/pow(PAR2[i][j][15][3],2)+pow(ERR2[i][j][2][0],2)/pow(PAR2[i][j][2][0],2));
			ERROR2_16[i][j] = RAT2_16[i][j]*sqrt(pow(ERR2[i][j][16][3],2)/pow(PAR2[i][j][16][3],2)+pow(ERR2[i][j][2][0],2)/pow(PAR2[i][j][2][0],2));


		}
	}
	//sys error divided by content
        double sys21 = 0.011*1.414, sys31 = 0.006*1.414, sys41 = 0.0004*1.414, sys51 = 0.013*1.414;
        double sys32 = 0.002*1.414, sys42 = 0.037*1.414, sys52 = 0.02*1.414;
        double sys43 = 0.11*1.414,sys53 = 0.07*1.414;
	TGraphErrors* g21 = new TGraphErrors();
	g21->SetPoint(0, BBC[0]-3*shift,RAT2_4[2][1]);
	g21->SetPoint(1, BBC[1]-3*shift,RAT2_5[2][1]);
	g21->SetPoint(2, BBC[2]-3*shift,RAT2_15[2][1]);
	g21->SetPoint(3, BBC[3]-3*shift,RAT2_16[2][1]);
	//stat error
	g21->SetPointError(0, 0.0,ERROR2_4[2][1]);
	g21->SetPointError(1, 0.0,ERROR2_5[2][1]);
	g21->SetPointError(2, 0.0,ERROR2_15[2][1]);
	g21->SetPointError(3, 0.0,ERROR2_16[2][1]);
        TGraphErrors* g21s = new TGraphErrors();
	g21s->SetPoint(0, BBC[0]-shift*3,RAT2_4[2][1]);
	g21s->SetPoint(1, BBC[1]-shift*3,RAT2_5[2][1]);
	g21s->SetPoint(2, BBC[2]-shift*3,RAT2_15[2][1]);
	g21s->SetPoint(3, BBC[3]-shift*3,RAT2_16[2][1]);
	//add total error = sqrt(stat error*stat error + sys error*sys error)
	/*
	g21s->SetPointError(0, 0.0,sqrt(ERROR2_4[2][1]*ERROR2_4[2][1]+sys21*sys21*RAT2_4[2][1]*RAT2_4[2][1]));
	g21s->SetPointError(1, 0.0,sqrt(ERROR2_5[2][1]*ERROR2_5[2][1]+sys21*sys21*RAT2_5[2][1]*RAT2_5[2][1]));
	g21s->SetPointError(2, 0.0,sqrt(ERROR2_15[2][1]*ERROR2_15[2][1]+sys21*sys21*RAT2_15[2][1]*RAT2_15[2][1]));
	g21s->SetPointError(3, 0.0,sqrt(ERROR2_16[2][1]*ERROR2_16[2][1]+sys21*sys21*RAT2_16[2][1]*RAT2_16[2][1]));
*/
	//add sys error
g21s->SetPointError(0, 0.0,sys21*RAT2_4[2][1]);
	g21s->SetPointError(1, 0.0,sys21*RAT2_5[2][1]);
	g21s->SetPointError(2, 0.0,sys21*RAT2_15[2][1]);
	g21s->SetPointError(3, 0.0,sys21*RAT2_16[2][1]);
TGraphErrors* g31 = new TGraphErrors();
	g31->SetPoint(0, BBC[0]-shift,RAT2_4[3][1]);
	g31->SetPoint(1, BBC[1]-shift,RAT2_5[3][1]);
	g31->SetPoint(2, BBC[2]-shift,RAT2_15[3][1]);
	g31->SetPoint(3, BBC[3]-shift,RAT2_16[3][1]);
	g31->SetPointError(0, 0.0,ERROR2_4[3][1]);
	g31->SetPointError(1, 0.0,ERROR2_5[3][1]);
	g31->SetPointError(2, 0.0,ERROR2_15[3][1]);
	g31->SetPointError(3, 0.0,ERROR2_16[3][1]);
        TGraphErrors* g31s = new TGraphErrors();
	g31s->SetPoint(0, BBC[0]-shift,RAT2_4[3][1]);
	g31s->SetPoint(1, BBC[1]-shift,RAT2_5[3][1]);
	g31s->SetPoint(2, BBC[2]-shift,RAT2_15[3][1]);
	g31s->SetPoint(3, BBC[3]-shift,RAT2_16[3][1]);
/*
	g31s->SetPointError(0, 0.0,sqrt(ERROR2_4[3][1]*ERROR2_4[3][1]+sys31*sys31*RAT2_4[3][1]*RAT2_4[3][1]));
	g31s->SetPointError(1, 0.0,sqrt(ERROR2_5[3][1]*ERROR2_5[3][1]+sys31*sys31*RAT2_5[3][1]*RAT2_5[3][1]));
	g31s->SetPointError(2, 0.0,sqrt(ERROR2_15[3][1]*ERROR2_15[3][1]+sys31*sys31*RAT2_15[3][1]*RAT2_15[3][1]));
	g31s->SetPointError(3, 0.0,sqrt(ERROR2_16[3][1]*ERROR2_16[3][1]+sys31*sys31*RAT2_16[3][1]*RAT2_16[3][1]));
*/
g31s->SetPointError(0, 0.0,sys31*RAT2_4[3][1]);
	g31s->SetPointError(1, 0.0,sys31*RAT2_5[3][1]);
	g31s->SetPointError(2, 0.0,sys31*RAT2_15[3][1]);
	g31s->SetPointError(3, 0.0,sys31*RAT2_16[3][1]);
TGraphErrors* g41 = new TGraphErrors();
	g41->SetPoint(0, BBC[0]+shift,RAT2_4[4][1]);
	g41->SetPoint(1, BBC[1]+shift,RAT2_5[4][1]);
	g41->SetPoint(2, BBC[2]+shift,RAT2_15[4][1]);
	g41->SetPoint(3, BBC[3]+shift,RAT2_16[4][1]);
	g41->SetPointError(0, 0.0,ERROR2_4[4][1]);
	g41->SetPointError(1, 0.0,ERROR2_5[4][1]);
	g41->SetPointError(2, 0.0,ERROR2_15[4][1]);
	g41->SetPointError(3, 0.0,ERROR2_16[4][1]);
        TGraphErrors* g41s = new TGraphErrors();
	g41s->SetPoint(0, BBC[0]+shift,RAT2_4[4][1]);
	g41s->SetPoint(1, BBC[1]+shift,RAT2_5[4][1]);
	g41s->SetPoint(2, BBC[2]+shift,RAT2_15[4][1]);
	g41s->SetPoint(3, BBC[3]+shift,RAT2_16[4][1]);
/*
	g41s->SetPointError(0, 0.0,sqrt(ERROR2_4[4][1]*ERROR2_4[4][1]+sys41*sys41*RAT2_4[4][1]*RAT2_4[4][1]));
	g41s->SetPointError(1, 0.0,sqrt(ERROR2_5[4][1]*ERROR2_5[4][1]+sys41*sys41*RAT2_5[4][1]*RAT2_5[4][1]));
	g41s->SetPointError(2, 0.0,sqrt(ERROR2_15[4][1]*ERROR2_15[4][1]+sys41*sys41*RAT2_15[4][1]*RAT2_15[4][1]));
	g41s->SetPointError(3, 0.0,sqrt(ERROR2_16[4][1]*ERROR2_16[4][1]+sys41*sys41*RAT2_16[4][1]*RAT2_16[4][1]));
*/
	g41s->SetPointError(0, 0.0,sys41*RAT2_4[4][1]);
	g41s->SetPointError(1, 0.0,sys41*RAT2_5[4][1]);
	g41s->SetPointError(2, 0.0,sys41*RAT2_15[4][1]);
	g41s->SetPointError(3, 0.0,sys41*RAT2_16[4][1]);

TGraphErrors* g51 = new TGraphErrors();
	g51->SetPoint(0, BBC[0]+3*shift,RAT2_4[5][1]);
	g51->SetPoint(1, BBC[1]+3*shift,RAT2_5[5][1]);
	g51->SetPoint(2, BBC[2]+3*shift,RAT2_15[5][1]);
	g51->SetPoint(3, BBC[3]+3*shift,RAT2_16[5][1]);
	g51->SetPointError(0, 0.0,ERROR2_4[5][1]);
	g51->SetPointError(1, 0.0,ERROR2_5[5][1]);
	g51->SetPointError(2, 0.0,ERROR2_15[5][1]);
	g51->SetPointError(3, 0.0,ERROR2_16[5][1]);
	TGraphErrors* g51s = new TGraphErrors();
	g51s->SetPoint(0, BBC[0]+3*shift,RAT2_4[5][1]);
	g51s->SetPoint(1, BBC[1]+3*shift,RAT2_5[5][1]);
	g51s->SetPoint(2, BBC[2]+3*shift,RAT2_15[5][1]);
	g51s->SetPoint(3, BBC[3]+3*shift,RAT2_16[5][1]);
/*
	g51s->SetPointError(0, 0.0,sqrt(ERROR2_4[5][1]*ERROR2_4[5][1]+sys51*sys51*RAT2_4[5][1]*RAT2_4[5][1]));
	g51s->SetPointError(1, 0.0,sqrt(ERROR2_5[5][1]*ERROR2_5[5][1]+sys51*sys51*RAT2_5[5][1]*RAT2_5[5][1]));
	g51s->SetPointError(2, 0.0,sqrt(ERROR2_15[5][1]*ERROR2_15[5][1]+sys51*sys51*RAT2_15[5][1]*RAT2_15[5][1]));
	g51s->SetPointError(3, 0.0,sqrt(ERROR2_16[5][1]*ERROR2_16[5][1]+sys51*sys51*RAT2_16[5][1]*RAT2_16[5][1]));
*/
	g51s->SetPointError(0, 0.0,sys51*RAT2_4[5][1]);
	g51s->SetPointError(1, 0.0,sys51*RAT2_5[5][1]);
	g51s->SetPointError(2, 0.0,sys51*RAT2_15[5][1]);
	g51s->SetPointError(3, 0.0,sys51*RAT2_16[5][1]);

TGraphErrors* g32 = new TGraphErrors();
	g32->SetPoint(0, BBC[0]-2*shift,RAT2_4[3][2]);
	g32->SetPoint(1, BBC[1]-2*shift,RAT2_5[3][2]);
	g32->SetPoint(2, BBC[2]-2*shift,RAT2_15[3][2]);
	g32->SetPoint(3, BBC[3]-2*shift,RAT2_16[3][2]);
	g32->SetPointError(0, 0.0,ERROR2_4[3][2]);
	g32->SetPointError(1, 0.0,ERROR2_5[3][2]);
	g32->SetPointError(2, 0.0,ERROR2_15[3][2]);
	g32->SetPointError(3, 0.0,ERROR2_16[3][2]);
TGraphErrors* g32s = new TGraphErrors();
	g32s->SetPoint(0, BBC[0]-2*shift,RAT2_4[3][2]);
	g32s->SetPoint(1, BBC[1]-2*shift,RAT2_5[3][2]);
	g32s->SetPoint(2, BBC[2]-2*shift,RAT2_15[3][2]);
	g32s->SetPoint(3, BBC[3]-2*shift,RAT2_16[3][2]);
/*
	g32s->SetPointError(0, 0.0,sqrt(ERROR2_4[3][2]*ERROR2_4[3][2]+sys32*sys32*RAT2_4[3][2]*RAT2_4[3][2]));
	g32s->SetPointError(1, 0.0,sqrt(ERROR2_5[3][2]*ERROR2_5[3][2]+sys32*sys32*RAT2_5[3][2]*RAT2_5[3][2]));
	g32s->SetPointError(2, 0.0,sqrt(ERROR2_15[3][2]*ERROR2_15[3][2]+sys32*sys32*RAT2_15[3][2]*RAT2_15[3][2]));
	g32s->SetPointError(3, 0.0,sqrt(ERROR2_16[3][2]*ERROR2_16[3][2]+sys32*sys32*RAT2_16[3][2]*RAT2_16[3][2]));
*/
	g32s->SetPointError(0, 0.0,sys32*RAT2_4[3][2]);
	g32s->SetPointError(1, 0.0,sys32*RAT2_5[3][2]);
	g32s->SetPointError(2, 0.0,sys32*RAT2_15[3][2]);
	g32s->SetPointError(3, 0.0,sys32*RAT2_16[3][2]);
	
TGraphErrors* g42 = new TGraphErrors();
	g42->SetPoint(0, BBC[0],RAT2_4[4][2]);
	g42->SetPoint(1, BBC[1],RAT2_5[4][2]);
	g42->SetPoint(2, BBC[2],RAT2_15[4][2]);
	g42->SetPoint(3, BBC[3],RAT2_16[4][2]);
	g42->SetPointError(0, 0.0,ERROR2_4[4][2]);
	g42->SetPointError(1, 0.0,ERROR2_5[4][2]);
	g42->SetPointError(2, 0.0,ERROR2_15[4][2]);
	g42->SetPointError(3, 0.0,ERROR2_16[4][2]);
 TGraphErrors* g42s = new TGraphErrors();
	g42s->SetPoint(0, BBC[0],RAT2_4[4][2]);
	g42s->SetPoint(1, BBC[1],RAT2_5[4][2]);
	g42s->SetPoint(2, BBC[2],RAT2_15[4][2]);
	g42s->SetPoint(3, BBC[3],RAT2_16[4][2]);
/*
	g42s->SetPointError(0, 0.0,sqrt(ERROR2_4[4][2]*ERROR2_4[4][2]+sys42*sys42*RAT2_4[4][2]*RAT2_4[4][2]));
	g42s->SetPointError(1, 0.0,sqrt(ERROR2_5[4][2]*ERROR2_5[4][2]+sys42*sys42*RAT2_5[4][2]*RAT2_5[4][2]));
	g42s->SetPointError(2, 0.0,sqrt(ERROR2_15[4][2]*ERROR2_15[4][2]+sys42*sys42*RAT2_15[4][2]*RAT2_15[4][2]));
	g42s->SetPointError(3, 0.0,sqrt(ERROR2_16[4][2]*ERROR2_16[4][2]+sys42*sys42*RAT2_16[4][2]*RAT2_16[4][2]));
*/
	g42s->SetPointError(0, 0.0,sys42*RAT2_4[4][2]);
	g42s->SetPointError(1, 0.0,sys42*RAT2_5[4][2]);
	g42s->SetPointError(2, 0.0,sys42*RAT2_15[4][2]);
	g42s->SetPointError(3, 0.0,sys42*RAT2_16[4][2]);
	
TGraphErrors* g52 = new TGraphErrors();
	g52->SetPoint(0, BBC[0]+2*shift,RAT2_4[5][2]);
	g52->SetPoint(1, BBC[1]+2*shift,RAT2_5[5][2]);
	g52->SetPoint(2, BBC[2]+2*shift,RAT2_15[5][2]);
	g52->SetPoint(3, BBC[3]+2*shift,RAT2_16[5][2]);
	g52->SetPointError(0, 0.0,ERROR2_4[5][2]);
	g52->SetPointError(1, 0.0,ERROR2_5[5][2]);
	g52->SetPointError(2, 0.0,ERROR2_15[5][2]);
	g52->SetPointError(3, 0.0,ERROR2_16[5][2]);
TGraphErrors* g52s = new TGraphErrors();
	g52s->SetPoint(0, BBC[0]+2*shift,RAT2_4[5][2]);
	g52s->SetPoint(1, BBC[1]+2*shift,RAT2_5[5][2]);
	g52s->SetPoint(2, BBC[2]+2*shift,RAT2_15[5][2]);
	g52s->SetPoint(3, BBC[3]+2*shift,RAT2_16[5][2]);
/*
		g52s->SetPointError(0, 0.0,sqrt(ERROR2_4[5][2]*ERROR2_4[5][2]+sys52*sys52*RAT2_4[5][2]*RAT2_4[5][2]));
	g52s->SetPointError(1, 0.0,sqrt(ERROR2_5[5][2]*ERROR2_5[5][2]+sys52*sys52*RAT2_5[5][2]*RAT2_5[5][2]));
	g52s->SetPointError(2, 0.0,sqrt(ERROR2_15[5][2]*ERROR2_15[5][2]+sys52*sys52*RAT2_15[5][2]*RAT2_15[5][2]));
	g52s->SetPointError(3, 0.0,sqrt(ERROR2_16[5][2]*ERROR2_16[5][2]+sys52*sys52*RAT2_16[5][2]*RAT2_16[5][2]));
*/
	g52s->SetPointError(0, 0.0,sys52*RAT2_4[5][2]);
	g52s->SetPointError(1, 0.0,sys52*RAT2_5[5][2]);
	g52s->SetPointError(2, 0.0,sys52*RAT2_15[5][2]);
	g52s->SetPointError(3, 0.0,sys52*RAT2_16[5][2]);
	

TGraphErrors* g43 = new TGraphErrors();
	g43->SetPoint(0, BBC[0]-shift,RAT2_4[4][3]);
	g43->SetPoint(1, BBC[1]-shift,RAT2_5[4][3]);
	g43->SetPoint(2, BBC[2]-shift,RAT2_15[4][3]);
	g43->SetPoint(3, BBC[3]-shift,RAT2_16[4][3]);
	g43->SetPointError(0, 0.0,ERROR2_4[4][3]);
	g43->SetPointError(1, 0.0,ERROR2_5[4][3]);
	g43->SetPointError(2, 0.0,ERROR2_15[4][3]);
	g43->SetPointError(3, 0.0,ERROR2_16[4][3]);
TGraphErrors* g43s = new TGraphErrors();
	g43s->SetPoint(0, BBC[0]-shift,RAT2_4[4][3]);
	g43s->SetPoint(1, BBC[1]-shift,RAT2_5[4][3]);
	g43s->SetPoint(2, BBC[2]-shift,RAT2_15[4][3]);
	g43s->SetPoint(3, BBC[3]-shift,RAT2_16[4][3]);
	g43s->SetPointError(0, 0.0,sys43*RAT2_4[4][3]);
	g43s->SetPointError(1, 0.0,sys43*RAT2_5[4][3]);
	g43s->SetPointError(2, 0.0,sys43*RAT2_15[4][3]);
	g43s->SetPointError(3, 0.0,sys43*RAT2_16[4][3]);
	
TGraphErrors* g53 = new TGraphErrors();
	g53->SetPoint(0, BBC[0]+shift,RAT2_4[5][3]);
	g53->SetPoint(1, BBC[1]+shift,RAT2_5[5][3]);
	g53->SetPoint(2, BBC[2]+shift,RAT2_15[5][3]);
	g53->SetPoint(3, BBC[3]+shift,RAT2_16[5][3]);
	g53->SetPointError(0, 0.0,ERROR2_4[5][3]);
	g53->SetPointError(1, 0.0,ERROR2_5[5][3]);
	g53->SetPointError(2, 0.0,ERROR2_15[5][3]);
	g53->SetPointError(3, 0.0,ERROR2_16[5][3]);
TGraphErrors* g53s = new TGraphErrors();
	g53s->SetPoint(0, BBC[0]+shift,RAT2_4[5][3]);
	g53s->SetPoint(1, BBC[1]+shift,RAT2_5[5][3]);
	g53s->SetPoint(2, BBC[2]+shift,RAT2_15[5][3]);
	g53s->SetPoint(3, BBC[3]+shift,RAT2_16[5][3]);
	g53s->SetPointError(0, 0.0,sys53*RAT2_4[5][3]);
	g53s->SetPointError(1, 0.0,sys53*RAT2_5[5][3]);
	g53s->SetPointError(2, 0.0,sys53*RAT2_15[5][3]);
	g53s->SetPointError(3, 0.0,sys53*RAT2_16[5][3]);
	

TGraphErrors* g54 = new TGraphErrors();
	g54->SetPoint(0, BBC[0],RAT2_4[5][4]);
	g54->SetPoint(1, BBC[1],RAT2_5[5][4]);
	g54->SetPoint(2, BBC[2],RAT2_15[5][4]);
	g54->SetPoint(3, BBC[3],RAT2_16[5][4]);
	g54->SetPointError(0, 0.0,ERROR2_4[5][4]);
	g54->SetPointError(1, 0.0,ERROR2_5[5][4]);
	g54->SetPointError(2, 0.0,ERROR2_15[5][4]);
	g54->SetPointError(3, 0.0,ERROR2_16[5][4]);
cout<<"g41 "<<endl;
g41->Print();
g41s->Print();
cout<<"g42 "<<endl;
g42->Print();
g42s->Print();
cout<<"g43 "<<endl;
g43->Print();
g43s->Print();

	TF1 *baseline = new TF1("baseline","1",1000,52000);
	baseline->GetYaxis()->SetRangeUser(-0.1,2.5);
	baseline->SetLineWidth(1.5);
	        baseline->GetYaxis()->SetNdivisions(505);
        baseline->GetXaxis()->SetNdivisions(505);

	auto c1 = new TCanvas("c1","Paway_pAu/Paway_pp",200,10,600,800);
        TPad *pad_1 = new TPad("pad_1", "pad_1", 0.00,0.67,1.0,1.00);
	pad_1->SetMargin(0.11, 0.01, 0.00, 1.00);
	TPad *pad_2 = new TPad("pad_2", "pad_2", 0.00,0.38,1.0,0.67);
    	pad_2->SetMargin(0.11, 0.01, 0.00, 0.005);
	TPad *pad_3 = new TPad("pad_3", "pad_3", 0.00,0.05,1.0,0.38);
    	pad_3->SetMargin(0.11, 0.01, 1.00, 0.00);
	TPad *pad_4 = new TPad("pad_4", "pad_4", 0.00,0.0,1.0,0.05);
	pad_4->SetMargin(0., 0.0, 0.00, 0.00);

	c1->cd();
	pad_1->Draw();
	pad_2->Draw();
    	pad_3->Draw();
    	pad_4->Draw();

	pad_1->cd();
	double size = 1.7;
	double width = 2.8;
	baseline->SetLineStyle(7);
	baseline->GetYaxis()->SetLabelSize(0.08);
	baseline->Draw();
	g21->GetYaxis()->SetRangeUser(0,2.0);
	g21->SetMarkerColor(kMagenta-6);
	g21->SetMarkerStyle(30);
	g21->SetLineColor(kMagenta-6);
	g21->SetLineWidth(width);
	g21->SetMarkerSize(size);
	g21->Draw("sameP");
	g21s->SetMarkerSize(size);
	g21s->SetLineColor(kMagenta-6);
	g21s->SetLineWidth(width);
	g21s->Draw("same[]");
	g31->SetMarkerColor(kBlue-6);
	g31->SetMarkerStyle(8);
	g31->SetLineColor(kBlue-6);
	g31->SetLineWidth(width);
	g31->SetMarkerSize(size);
	g31->Draw("sameP");
	g31s->SetLineColor(kBlue-6);
	g31s->SetLineWidth(width);
	g31s->Draw("same[]");
	g41s->SetLineColor(kCyan+2);
	g41s->SetLineWidth(width);
	g41s->Draw("same[]");
	g41->SetMarkerColor(kCyan+2);
	g41->SetMarkerStyle(25);
	g41->SetLineColor(kCyan+2);
	g41->SetLineWidth(width);
	g41->SetMarkerSize(size);
	g41->Draw("sameP");
	g51->SetMarkerColor(kGreen+3);
	g51->SetMarkerStyle(22);
	g51->SetLineColor(kGreen+3);
	g51->SetLineWidth(width);
	g51->SetMarkerSize(size);
	g51->Draw("sameP");
	g51s->SetLineColor(kGreen+3);
	g51s->SetLineWidth(width);
	g51s->Draw("same[]");
	cyrill21->SetMarkerSize(size+1);
        cyrill21->SetLineWidth(width);
	cyrill21->SetLineColor(46);
        cyrill21->SetFillStyle(3002);
        cyrill21->Draw("3csame");
        cyrill21->SetFillColorAlpha(46,0.05);
	//cyrill21->Draw("sameP");
	cyrill21->SetMarkerColor(kRed);
	cyrill21->SetMarkerStyle(24);
        double xx = 0.25;
        double yy = 0.09;
	drawLatex(0.15, 0.8,"#sqrt{s_{NN}} = 200 GeV, 2.6 < #eta < 4.0",62,0.088,kBlack);
	drawLatex(0.18, 0.58,"p_{T}^{trig}",62,0.085,kBlack);
        drawLatex(0.65, yy,"p_{T}^{asso} = 1.0-1.5 GeV/c",62,0.085,kBlack);
	drawLatex(0.88,0.8,"STAR",62,0.09,1);
	TLegend *leg1_1 = new TLegend(0.25,0.56,0.85,0.78);
	leg1_1->SetNColumns(2);
	leg1_1->AddEntry(g21,"1.5-2.0 GeV/c","P");
	leg1_1->AddEntry(g31,"2.0-2.5 GeV/c","P");
	TLegend *leg1_2 = new TLegend(0.25,0.43,0.85,0.65);
	leg1_2->SetNColumns(2);
	leg1_2->AddEntry(g41,"2.5-3.0 GeV/c","P");
	leg1_2->AddEntry(g51,"3.0-5.0 GeV/c","P");
	leg1_1->SetFillStyle(0);
	leg1_1->SetLineColor(0);
	leg1_2->SetFillStyle(0);
	leg1_2->SetLineColor(0);
	leg1_2->SetBorderSize(0);
	leg1_1->Draw("same");
	leg1_2->Draw("same");

        TLegend *leg1_3 = new TLegend(0.78,0.50,1.0,0.92);
        leg1_3->AddEntry(cyrill21,"rcBK, b=0","p");
        leg1_3->SetFillStyle(0);
        leg1_3->SetLineColor(0);
//leg1_3->Draw("same");
	pad_2->cd();
	g32->GetYaxis()->SetRangeUser(-0.1,1.8);
	g32->GetYaxis()->SetLabelSize(0.08);
	g32->GetYaxis()->SetTitle("Relative width");
	g32->GetYaxis()->SetTitleSize(0.1);
	g32->GetYaxis()->SetTitleOffset(0.5);
	g32->GetYaxis()->SetNdivisions(505);
	//baseline->GetYaxis()->SetTitle("#frac{Paway pAu1}{Paway pp}");
	g32->SetMarkerColor(kBlue-6);
	g32->SetMarkerStyle(8);
	g32->SetLineColor(kBlue-6);
	g32->SetLineWidth(width);
	g32->SetMarkerSize(size);
        TF1 *baseline2 = new TF1("baseline2","1",1000,52000);
	baseline2->SetLineWidth(1.5);
        baseline2->GetYaxis()->SetRangeUser(-0.1,1.8);
	baseline2->GetYaxis()->SetTitle("Relative width");
	baseline2->GetYaxis()->CenterTitle();
	baseline2->GetYaxis()->SetTitleSize(0.12);
	baseline2->GetYaxis()->SetTitleOffset(0.46);
	baseline2->GetYaxis()->SetLabelSize(0.09);
	baseline2->SetLineStyle(7);
                baseline2->GetYaxis()->SetNdivisions(505);
        baseline2->GetXaxis()->SetNdivisions(505);
	baseline2->Draw();
	g32->Draw("sameP");
	g32s->SetLineColor(kBlue-6);
	g32s->SetLineWidth(width);
	g32s->Draw("same[]");
	baseline->Draw("same");
	g42->SetMarkerColor(kCyan+2);
	g42->SetMarkerStyle(25);
	g42->SetLineColor(kCyan+2);
	g42->SetLineWidth(width);
	g42->SetMarkerSize(size);
	g42->Draw("sameP");
	g42s->SetLineColor(kCyan+2);
	g42s->SetLineWidth(width);
	g42s->Draw("same[]");
cyrill32->SetLineWidth(width);
cyrill32->SetMarkerSize(size+1);
cyrill32->SetLineColor(46);
cyrill32->SetFillColorAlpha(46,0.05);
cyrill32->SetFillStyle(3002);
cyrill32->SetMarkerStyle(24);
cyrill32->SetMarkerColor(kRed);
//        cyrill32->Draw("sameP");
	g52->SetMarkerColor(kGreen+3);
	g52->SetMarkerStyle(22);
	g52->SetLineColor(kGreen+3);
	g52->SetLineWidth(width);
	g52->SetMarkerSize(size);
	g52->Draw("sameP");
	g52s->SetLineColor(kGreen+3);
	g52s->SetLineWidth(width);
	g52s->Draw("same[]");
	drawLatex(0.67, yy,"p^{asso}_{T} = 1.5-2.0 GeV/c",62,0.09,kBlack);
        TLegend *leg2 = new TLegend(0.1,0.7,0.48,0.9);
        leg2->AddEntry(g32,"pT1 = 2.0-2.5 GeV/c","P");
        leg2->AddEntry(g42,"pT1 = 2.5-3.0 GeV/c","P");
        leg2->AddEntry(g52,"pT1 = 3.0-5.0 GeV/c","P");
        //leg2->Draw("same");

	pad_3->cd();
	//g53->GetYaxis()->SetRangeUser(0,1.1);
	TF1 *baseline3 = new TF1("baseline3","1",1000,52000);
        baseline3->SetLineWidth(1.5);
        baseline3->GetYaxis()->SetRangeUser(0.1,1.9);
	baseline3->GetXaxis()->SetLabelSize(0.08);
	baseline3->GetYaxis()->SetLabelOffset(0.01);
        baseline3->GetYaxis()->SetNdivisions(505);
        baseline3->GetXaxis()->SetNdivisions(505);
        baseline3->SetLineStyle(7);
        baseline3->GetYaxis()->SetLabelSize(0.08);
baseline3->Draw();
	g53->SetMarkerColor(kGreen+3);
	g53->SetMarkerStyle(22);
	g53->SetLineColor(kGreen+3);
	g53->SetLineWidth(width);
	g53->SetMarkerSize(size);
	g53->Draw("sameP");
	g53s->SetLineColor(kGreen+3);
	g53s->SetLineWidth(width);
	g53s->Draw("same[]");
	cyrill53->SetLineColor(46);
	cyrill53->SetMarkerStyle(24);
	cyrill53->SetMarkerColor(kRed);
	cyrill53->SetLineWidth(width);
	cyrill53->SetMarkerSize(size+1);
	g43->SetMarkerColor(kCyan+2);
	g43->SetMarkerStyle(25);
	g43->SetLineColor(kCyan+2);
	g43->SetLineWidth(width);
	g43->SetMarkerSize(size);
	g43->Draw("sameP");
	g43s->SetLineColor(kCyan+2);
	g43s->SetLineWidth(width);
	g43s->Draw("same[]");
	//cyrill53->Draw("sameP");
        drawLatex(0.67, yy+0.1,"p^{asso}_{T} = 2.0-2.5 GeV/c",62,0.08,kBlack);
        TLegend *leg3 = new TLegend(0.1,0.7,0.48,0.9);
        leg3->AddEntry(g53,"pT1 = 2.8-5.0 GeV/c","P");
/*
        TArrow *line = new TArrow(1000,0.1,45000,0.1,0.01);
        line->SetAngle(60);
        TLine *line1 = new TLine(7300,0.08,7300,0.12);
        TLine *line2 = new TLine(18000,0.08,18000,0.12);
        TLine *line3 = new TLine(30000,0.08,30000,0.12);
        TLine *line4 = new TLine(43500,0.08,43500,0.12);
        drawTof(46000, 0.07,"TofM",102,0.08,kBlack);

        line->SetLineColor(13);
        line1->SetLineColor(13);
        line2->SetLineColor(13);
        line3->SetLineColor(13);
        line4->SetLineColor(13);
drawTof(5700, 0.13,"18.4%",62,0.06,13);
        drawTof(16500, 0.13,"24.2%",62,0.06,13);
        drawTof(28500, 0.13,"30.7%",62,0.06,13);
        drawTof(42000, 0.13,"42.8%",62,0.06,13);
        line->SetLineWidth(2);
        line1->SetLineWidth(3);
        line2->SetLineWidth(3);
        line3->SetLineWidth(3);
        line4->SetLineWidth(3);
        line->Draw();
        line1->Draw("same");
        line2->Draw("same");
        line3->Draw("same");
        line4->Draw("same");
        //leg3->Draw("same");
        pad_4->cd();
	drawLatex(0.45, 0.4,"Event Activity",62,0.7,kBlack);
c1->SaveAs("plot/HighpAu_MBpp_Width_Ratio.pdf");
*/
//Draw inclusive pi0 yields
/*
TArrow *line = new TArrow(1000,0.1,45000,0.1,0.01);
        line->SetAngle(60);
        TLine *line1 = new TLine(12000,0.08,12000,0.12);
        TLine *line2 = new TLine(24000,0.08,24000,0.12);
        TLine *line3 = new TLine(36000,0.08,36000,0.12);
        drawTof(46000, 0.07,"N_{#pi^{0}}",102,0.08,kBlack);

        line->SetLineColor(13);
        line1->SetLineColor(13);
        line2->SetLineColor(13);
        line3->SetLineColor(13);
        drawTof(11000, 0.13,"31.6%",62,0.06,13);
        drawTof(23000, 0.13,"63.5%",62,0.06,13);
        drawTof(35000, 0.13,"85.3%",62,0.06,13);
        line->SetLineWidth(2);
        line1->SetLineWidth(3);
        line2->SetLineWidth(3);
        line3->SetLineWidth(3);
        line->Draw();
        line1->Draw("same");
        line2->Draw("same");
        line3->Draw("same");
*/
        //leg3->Draw("same");
                pad_4->cd();
                        drawLatex(0.43, 0.4,"E.A. (#SigmaE_{BBC})",62,0.7,kBlack);
c1->SaveAs("Width_pppAu.pdf");
/*

	c1->cd(4);
	baseline->Draw();
	g54->GetYaxis()->SetRangeUser(0,1.1);
	g54->SetMarkerColor(4);
	g54->SetMarkerStyle(21);
	g54->SetLineColor(4);
	g54->Draw("sameP");
*/
}
