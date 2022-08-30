
#ifndef _SET_H_
#define _SET_H_

#define RAWFILEPATH "../../../data/"
#define RAWFILENAME "data"

#define OUTFILEPATH "./"


#define Crate0
#define Crate0num 1	//Number of modules used in this crate
const int Crate0SamplingRate[Crate0num] = {100};//Specify the sampling rate  of each modules separately; 100/250/500 sampling rates; 0 to skip the module

// true means the channel can be used
const bool FLAGCHANNEL[Crate0num][16] = {/*model0*//*0-3*/true,true,true,true,
                                                   /*4-7*/true,false,false,false,
                                                   /*8-11*/false,false,false,false,
                                                   /*12-15*/false,false,false,false};

#define WINDOWS 300 // ns

// threshols unit keV
#define THRE_LOW  50
#define THRE_HIGH 4096

// TH2I 4096*4096 bin
#define BIN_MIN 0   //keV
#define BIN_MAX 4096  //keV

#endif