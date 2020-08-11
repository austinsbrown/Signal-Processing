/*
 * Filter Coefficients (C Source) generated by the Filter Design and Analysis Tool
 * Generated by MATLAB(R) 9.7 and Signal Processing Toolbox 8.3.
 * Generated on: 12-Apr-2020 21:31:41
 */

/*
 * Discrete-Time FIR Filter (real)
 * -------------------------------
 * Filter Structure  : Direct-Form FIR
 * Filter Length     : 431
 * Stable            : Yes
 * Linear Phase      : Yes (Type 1)
 */

/* General type conversion for MATLAB generated C-code  */
#include "tmwtypes.h"
/* 
 * Expected path to tmwtypes.h 
 * C:\Program Files\MATLAB\R2019b\extern\include\tmwtypes.h 
 */
const int DEN44100 = 431;
const real64_T NUM44100[431] = {
   -0.01100900679554, 0.006434661026447, 0.004803009440286, 0.003570772062174,
   0.002643811843078, 0.001946665314057,  0.00142745507993, 0.001043179790313,
  0.0007658131284807,0.0005700353959581,0.0004408446030044,0.0003614129782673,
  0.0003225660105249, 0.000310837150239,0.0003186998195404,0.0003338009949113,
  0.0003489858166448,0.0003532558252584, 0.000341208442034,0.0003044201621584,
  0.0002422469819935,0.0001518308319945,3.881291951499e-05,-9.347635570192e-05,
  -0.0002326625140048,-0.0003697617847688,-0.0004884878864077,-0.0005785263673019,
  -0.0006243109323624,-0.0006192703360344,-0.000554531356981,-0.0004326530154684,
  -0.0002550998257333,-3.578248769208e-05,0.0002126546823792,0.0004662833838492,
   0.000706626502063,   0.0009057042962,  0.00104624837715, 0.001104735811943,
   0.001074463510075,0.0009441761276219, 0.000724656583825,0.0004197651346416,
  6.048596321803e-05,-0.0003358359458922,-0.0007319117194718, -0.00108071992098,
  -0.001384474411393,-0.001563930738583,-0.001630580171838,-0.001569225534234,
  -0.001366630671096,-0.001029533456277,-0.0005930446131157,-8.846764178056e-05,
  0.0004484751279911,0.0009771692134723, 0.001447697816211, 0.001813743537479,
   0.002039483225892, 0.002103502197433, 0.001996311020499, 0.001721209787388,
   0.001293798047742,0.0007448572447399,0.0001178970405181,-0.0005345411569218,
  -0.001156166232408,-0.001693618606708,-0.002100142469073,-0.002340873664804,
  -0.002392783948771,-0.002249456240292,-0.001919339686753,-0.001429185754463,
  -0.0008181014659607,-0.0001382550340966,0.0005535559975341, 0.001197233967831,
   0.001739371398089, 0.002133964337514, 0.002350489507559, 0.002371402067436,
   0.002199866598202, 0.001851730649475, 0.001361807175451,0.0007720972320912,
  0.0001382933625328,-0.0004877619073825,-0.001048370383217,-0.001502758866106,
   -0.00181054246384,-0.001954732479456,-0.001932149200697,  -0.0017467837846,
  -0.001435186441074,-0.001026287326919,-0.0005647354308653,-0.0001003924149491,
  0.0003241420448556,0.0006753564026934,0.0009233949230616, 0.001053568318918,
   0.001067895709128,0.0009802470133684,0.0008136459971699,0.0005982303278842,
  0.0003710319011891,0.0001678625311922,1.757116215396e-05,-6.049477439332e-05,
  -5.787725752005e-05,2.209443553492e-05,0.0001630229631822, 0.000336188386562,
  0.0005055008147458,0.0006321691092138,0.0006808182395967,0.0006221699674775,
  0.0004392839443973,0.0001290692143949,-0.0002928655268729,-0.0007948520315298,
  -0.001328346904415,-0.001835193087458,-0.002251247503993,-0.002515610891242,
  -0.002574613818724,-0.002390790172957,-0.001946483583588,-0.001251997119947,
  -0.0003426171825662,0.0007177631475686, 0.001845608661152, 0.002938251738928,
   0.003890835267535, 0.004595986618798, 0.004966169925398,  0.00492995498103,
   0.004454973080207, 0.003543381834927, 0.002236720572806,0.0006227773751082,
  -0.001181710415615,-0.003031058841687,-0.004761842873408,-0.006213517487289,
  -0.007238868142662,-0.007715770840423,-0.007564696924847,-0.006758513944326,
  -0.005323303901528,-0.003344417957364,-0.0009592255116231,  0.00164857301163,
   0.004268104003182, 0.006675010267068, 0.008650771489812,  0.01000247984441,
     0.0105828391515,  0.01030409237319, 0.009148230623678, 0.007170932356338,
   0.004502097089475, 0.001337062820606,-0.002076988961988,-0.005462694405165,
  -0.008532752925209, -0.01101602882321, -0.01267935694372, -0.01335228926327,
   -0.01294162934355, -0.01144378284602,-0.008946093724678,-0.005624458274207,
  -0.001729554448941, 0.002430647509292, 0.006517414453392,   0.0101863533961,
    0.01312010832211,  0.01505332765874,  0.01579958901404,  0.01526370246682,
    0.01345983170136,  0.01050474622708, 0.006619745365611, 0.002103700856991,
     -0.002681428958,-0.007344286984996, -0.01149829592454, -0.01478917941013,
   -0.01692779785947, -0.01771910109757, -0.01707382611523, -0.01502204760016,
   -0.01171311208399,-0.007401413422735,-0.002426875472923, 0.002807275600167,
   0.007875012865329,  0.01235615391488,  0.01587771126232,  0.01813919080992,
    0.01894394590966,  0.01821359886858,  0.01599676390768,  0.01246439746379,
   0.007898703335324, 0.002668388523288,-0.002801001583164,-0.008063315176495,
   -0.01268678364789, -0.01629137211096, -0.01857966356175,   0.9806359195175,
   -0.01857966356175, -0.01629137211096, -0.01268678364789,-0.008063315176495,
  -0.002801001583164, 0.002668388523288, 0.007898703335324,  0.01246439746379,
    0.01599676390768,  0.01821359886858,  0.01894394590966,  0.01813919080992,
    0.01587771126232,  0.01235615391488, 0.007875012865329, 0.002807275600167,
  -0.002426875472923,-0.007401413422735, -0.01171311208399, -0.01502204760016,
   -0.01707382611523, -0.01771910109757, -0.01692779785947, -0.01478917941013,
   -0.01149829592454,-0.007344286984996,   -0.002681428958, 0.002103700856991,
   0.006619745365611,  0.01050474622708,  0.01345983170136,  0.01526370246682,
    0.01579958901404,  0.01505332765874,  0.01312010832211,   0.0101863533961,
   0.006517414453392, 0.002430647509292,-0.001729554448941,-0.005624458274207,
  -0.008946093724678, -0.01144378284602, -0.01294162934355, -0.01335228926327,
   -0.01267935694372, -0.01101602882321,-0.008532752925209,-0.005462694405165,
  -0.002076988961988, 0.001337062820606, 0.004502097089475, 0.007170932356338,
   0.009148230623678,  0.01030409237319,   0.0105828391515,  0.01000247984441,
   0.008650771489812, 0.006675010267068, 0.004268104003182,  0.00164857301163,
  -0.0009592255116231,-0.003344417957364,-0.005323303901528,-0.006758513944326,
  -0.007564696924847,-0.007715770840423,-0.007238868142662,-0.006213517487289,
  -0.004761842873408,-0.003031058841687,-0.001181710415615,0.0006227773751082,
   0.002236720572806, 0.003543381834927, 0.004454973080207,  0.00492995498103,
   0.004966169925398, 0.004595986618798, 0.003890835267535, 0.002938251738928,
   0.001845608661152,0.0007177631475686,-0.0003426171825662,-0.001251997119947,
  -0.001946483583588,-0.002390790172957,-0.002574613818724,-0.002515610891242,
  -0.002251247503993,-0.001835193087458,-0.001328346904415,-0.0007948520315298,
  -0.0002928655268729,0.0001290692143949,0.0004392839443973,0.0006221699674775,
  0.0006808182395967,0.0006321691092138,0.0005055008147458, 0.000336188386562,
  0.0001630229631822,2.209443553492e-05,-5.787725752005e-05,-6.049477439332e-05,
  1.757116215396e-05,0.0001678625311922,0.0003710319011891,0.0005982303278842,
  0.0008136459971699,0.0009802470133684, 0.001067895709128, 0.001053568318918,
  0.0009233949230616,0.0006753564026934,0.0003241420448556,-0.0001003924149491,
  -0.0005647354308653,-0.001026287326919,-0.001435186441074,  -0.0017467837846,
  -0.001932149200697,-0.001954732479456, -0.00181054246384,-0.001502758866106,
  -0.001048370383217,-0.0004877619073825,0.0001382933625328,0.0007720972320912,
   0.001361807175451, 0.001851730649475, 0.002199866598202, 0.002371402067436,
   0.002350489507559, 0.002133964337514, 0.001739371398089, 0.001197233967831,
  0.0005535559975341,-0.0001382550340966,-0.0008181014659607,-0.001429185754463,
  -0.001919339686753,-0.002249456240292,-0.002392783948771,-0.002340873664804,
  -0.002100142469073,-0.001693618606708,-0.001156166232408,-0.0005345411569218,
  0.0001178970405181,0.0007448572447399, 0.001293798047742, 0.001721209787388,
   0.001996311020499, 0.002103502197433, 0.002039483225892, 0.001813743537479,
   0.001447697816211,0.0009771692134723,0.0004484751279911,-8.846764178056e-05,
  -0.0005930446131157,-0.001029533456277,-0.001366630671096,-0.001569225534234,
  -0.001630580171838,-0.001563930738583,-0.001384474411393, -0.00108071992098,
  -0.0007319117194718,-0.0003358359458922,6.048596321803e-05,0.0004197651346416,
   0.000724656583825,0.0009441761276219, 0.001074463510075, 0.001104735811943,
    0.00104624837715,   0.0009057042962, 0.000706626502063,0.0004662833838492,
  0.0002126546823792,-3.578248769208e-05,-0.0002550998257333,-0.0004326530154684,
  -0.000554531356981,-0.0006192703360344,-0.0006243109323624,-0.0005785263673019,
  -0.0004884878864077,-0.0003697617847688,-0.0002326625140048,-9.347635570192e-05,
  3.881291951499e-05,0.0001518308319945,0.0002422469819935,0.0003044201621584,
   0.000341208442034,0.0003532558252584,0.0003489858166448,0.0003338009949113,
  0.0003186998195404, 0.000310837150239,0.0003225660105249,0.0003614129782673,
  0.0004408446030044,0.0005700353959581,0.0007658131284807, 0.001043179790313,
    0.00142745507993, 0.001946665314057, 0.002643811843078, 0.003570772062174,
   0.004803009440286, 0.006434661026447, -0.01100900679554
};