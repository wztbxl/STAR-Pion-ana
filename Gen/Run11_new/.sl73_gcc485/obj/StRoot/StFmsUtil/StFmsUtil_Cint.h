/********************************************************************
* .sl73_gcc485/obj/StRoot/StFmsUtil/StFmsUtil_Cint.h
* CAUTION: DON'T CHANGE THIS FILE. THIS FILE IS AUTOMATICALLY GENERATED
*          FROM HEADER FILES LISTED IN G__setup_cpp_environmentXXX().
*          CHANGE THOSE HEADER FILES AND REGENERATE THIS FILE.
********************************************************************/
#ifdef __CINT__
#error .sl73_gcc485/obj/StRoot/StFmsUtil/StFmsUtil_Cint.h/C is only for compilation. Abort cint.
#endif
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define G__ANSIHEADER
#define G__DICTIONARY
#define G__PRIVATE_GVALUE
#include "G__ci.h"
#include "FastAllocString.h"
extern "C" {
extern void G__cpp_setup_tagtableStFmsUtil_Cint();
extern void G__cpp_setup_inheritanceStFmsUtil_Cint();
extern void G__cpp_setup_typetableStFmsUtil_Cint();
extern void G__cpp_setup_memvarStFmsUtil_Cint();
extern void G__cpp_setup_globalStFmsUtil_Cint();
extern void G__cpp_setup_memfuncStFmsUtil_Cint();
extern void G__cpp_setup_funcStFmsUtil_Cint();
extern void G__set_cpp_environmentStFmsUtil_Cint();
}


#include "TObject.h"
#include "TMemberInspector.h"
#include "StFmsClusterFinder.h"
#include "StFmsClusterFitter.h"
#include "StFmsDbConfig.h"
#include "StFmsEventClusterer.h"
#include "StFmsTower.h"
#include "StFmsTowerCluster.h"
#include <algorithm>
namespace std { }
using namespace std;

#ifndef G__MEMFUNCBODY
#endif

extern G__linked_taginfo G__StFmsUtil_CintLN_TClass;
extern G__linked_taginfo G__StFmsUtil_CintLN_TBuffer;
extern G__linked_taginfo G__StFmsUtil_CintLN_TMemberInspector;
extern G__linked_taginfo G__StFmsUtil_CintLN_TObject;
extern G__linked_taginfo G__StFmsUtil_CintLN_vectorlElongcOallocatorlElonggRsPgR;
extern G__linked_taginfo G__StFmsUtil_CintLN_vectorlEdoublecOallocatorlEdoublegRsPgR;
extern G__linked_taginfo G__StFmsUtil_CintLN_string;
extern G__linked_taginfo G__StFmsUtil_CintLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR;
extern G__linked_taginfo G__StFmsUtil_CintLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__StFmsUtil_CintLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR;
extern G__linked_taginfo G__StFmsUtil_CintLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__StFmsUtil_CintLN_FMSCluster;
extern G__linked_taginfo G__StFmsUtil_CintLN_FMSClustercLcLStFmsTowerCluster;
extern G__linked_taginfo G__StFmsUtil_CintLN_FMSClustercLcLStFmsTower;
extern G__linked_taginfo G__StFmsUtil_CintLN_FMSClustercLcLStFmsClusterFinder;
extern G__linked_taginfo G__StFmsUtil_CintLN_listlEFMSClustercLcLStFmsTowermUcOallocatorlEFMSClustercLcLStFmsTowermUgRsPgR;
extern G__linked_taginfo G__StFmsUtil_CintLN_TMinuit;
extern G__linked_taginfo G__StFmsUtil_CintLN_FMSClustercLcLStFmsFittedPhoton;
extern G__linked_taginfo G__StFmsUtil_CintLN_StFmsCluster;
extern G__linked_taginfo G__StFmsUtil_CintLN_vectorlEFMSClustercLcLStFmsFittedPhotoncOallocatorlEFMSClustercLcLStFmsFittedPhotongRsPgR;
extern G__linked_taginfo G__StFmsUtil_CintLN_reverse_iteratorlEvectorlEFMSClustercLcLStFmsFittedPhotoncOallocatorlEFMSClustercLcLStFmsFittedPhotongRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__StFmsUtil_CintLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR;
extern G__linked_taginfo G__StFmsUtil_CintLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR;
extern G__linked_taginfo G__StFmsUtil_CintLN_TVectorTlEfloatgR;
extern G__linked_taginfo G__StFmsUtil_CintLN_TVectorTlEdoublegR;
extern G__linked_taginfo G__StFmsUtil_CintLN_fmsRec_st;
extern G__linked_taginfo G__StFmsUtil_CintLN_StFmsDbConfig;
extern G__linked_taginfo G__StFmsUtil_CintLN_maplEstringcOstringcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOstringgRsPgRsPgR;
extern G__linked_taginfo G__StFmsUtil_CintLN_StFmsHit;
extern G__linked_taginfo G__StFmsUtil_CintLN_StFmsDbMaker;
extern G__linked_taginfo G__StFmsUtil_CintLN_StMuDst;
extern G__linked_taginfo G__StFmsUtil_CintLN_TF2;
extern G__linked_taginfo G__StFmsUtil_CintLN_listlEFMSClustercLcLStFmsFittedPhotoncOallocatorlEFMSClustercLcLStFmsFittedPhotongRsPgR;
extern G__linked_taginfo G__StFmsUtil_CintLN_FMSClustercLcLStFmsClusterFitter;
extern G__linked_taginfo G__StFmsUtil_CintLN_FMSClustercLcLStFmsEventClusterer;
extern G__linked_taginfo G__StFmsUtil_CintLN_vectorlEFMSClustercLcLStFmsTowercOallocatorlEFMSClustercLcLStFmsTowergRsPgR;
extern G__linked_taginfo G__StFmsUtil_CintLN_reverse_iteratorlEvectorlEFMSClustercLcLStFmsTowercOallocatorlEFMSClustercLcLStFmsTowergRsPgRcLcLiteratorgR;

/* STUB derived class for protected member access */
