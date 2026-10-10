#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_4830641336023112635) {
   out_4830641336023112635[0] = delta_x[0] + nom_x[0];
   out_4830641336023112635[1] = delta_x[1] + nom_x[1];
   out_4830641336023112635[2] = delta_x[2] + nom_x[2];
   out_4830641336023112635[3] = delta_x[3] + nom_x[3];
   out_4830641336023112635[4] = delta_x[4] + nom_x[4];
   out_4830641336023112635[5] = delta_x[5] + nom_x[5];
   out_4830641336023112635[6] = delta_x[6] + nom_x[6];
   out_4830641336023112635[7] = delta_x[7] + nom_x[7];
   out_4830641336023112635[8] = delta_x[8] + nom_x[8];
   out_4830641336023112635[9] = delta_x[9] + nom_x[9];
   out_4830641336023112635[10] = delta_x[10] + nom_x[10];
   out_4830641336023112635[11] = delta_x[11] + nom_x[11];
   out_4830641336023112635[12] = delta_x[12] + nom_x[12];
   out_4830641336023112635[13] = delta_x[13] + nom_x[13];
   out_4830641336023112635[14] = delta_x[14] + nom_x[14];
   out_4830641336023112635[15] = delta_x[15] + nom_x[15];
   out_4830641336023112635[16] = delta_x[16] + nom_x[16];
   out_4830641336023112635[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7197149123055641316) {
   out_7197149123055641316[0] = -nom_x[0] + true_x[0];
   out_7197149123055641316[1] = -nom_x[1] + true_x[1];
   out_7197149123055641316[2] = -nom_x[2] + true_x[2];
   out_7197149123055641316[3] = -nom_x[3] + true_x[3];
   out_7197149123055641316[4] = -nom_x[4] + true_x[4];
   out_7197149123055641316[5] = -nom_x[5] + true_x[5];
   out_7197149123055641316[6] = -nom_x[6] + true_x[6];
   out_7197149123055641316[7] = -nom_x[7] + true_x[7];
   out_7197149123055641316[8] = -nom_x[8] + true_x[8];
   out_7197149123055641316[9] = -nom_x[9] + true_x[9];
   out_7197149123055641316[10] = -nom_x[10] + true_x[10];
   out_7197149123055641316[11] = -nom_x[11] + true_x[11];
   out_7197149123055641316[12] = -nom_x[12] + true_x[12];
   out_7197149123055641316[13] = -nom_x[13] + true_x[13];
   out_7197149123055641316[14] = -nom_x[14] + true_x[14];
   out_7197149123055641316[15] = -nom_x[15] + true_x[15];
   out_7197149123055641316[16] = -nom_x[16] + true_x[16];
   out_7197149123055641316[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_9025793039380934379) {
   out_9025793039380934379[0] = 1.0;
   out_9025793039380934379[1] = 0.0;
   out_9025793039380934379[2] = 0.0;
   out_9025793039380934379[3] = 0.0;
   out_9025793039380934379[4] = 0.0;
   out_9025793039380934379[5] = 0.0;
   out_9025793039380934379[6] = 0.0;
   out_9025793039380934379[7] = 0.0;
   out_9025793039380934379[8] = 0.0;
   out_9025793039380934379[9] = 0.0;
   out_9025793039380934379[10] = 0.0;
   out_9025793039380934379[11] = 0.0;
   out_9025793039380934379[12] = 0.0;
   out_9025793039380934379[13] = 0.0;
   out_9025793039380934379[14] = 0.0;
   out_9025793039380934379[15] = 0.0;
   out_9025793039380934379[16] = 0.0;
   out_9025793039380934379[17] = 0.0;
   out_9025793039380934379[18] = 0.0;
   out_9025793039380934379[19] = 1.0;
   out_9025793039380934379[20] = 0.0;
   out_9025793039380934379[21] = 0.0;
   out_9025793039380934379[22] = 0.0;
   out_9025793039380934379[23] = 0.0;
   out_9025793039380934379[24] = 0.0;
   out_9025793039380934379[25] = 0.0;
   out_9025793039380934379[26] = 0.0;
   out_9025793039380934379[27] = 0.0;
   out_9025793039380934379[28] = 0.0;
   out_9025793039380934379[29] = 0.0;
   out_9025793039380934379[30] = 0.0;
   out_9025793039380934379[31] = 0.0;
   out_9025793039380934379[32] = 0.0;
   out_9025793039380934379[33] = 0.0;
   out_9025793039380934379[34] = 0.0;
   out_9025793039380934379[35] = 0.0;
   out_9025793039380934379[36] = 0.0;
   out_9025793039380934379[37] = 0.0;
   out_9025793039380934379[38] = 1.0;
   out_9025793039380934379[39] = 0.0;
   out_9025793039380934379[40] = 0.0;
   out_9025793039380934379[41] = 0.0;
   out_9025793039380934379[42] = 0.0;
   out_9025793039380934379[43] = 0.0;
   out_9025793039380934379[44] = 0.0;
   out_9025793039380934379[45] = 0.0;
   out_9025793039380934379[46] = 0.0;
   out_9025793039380934379[47] = 0.0;
   out_9025793039380934379[48] = 0.0;
   out_9025793039380934379[49] = 0.0;
   out_9025793039380934379[50] = 0.0;
   out_9025793039380934379[51] = 0.0;
   out_9025793039380934379[52] = 0.0;
   out_9025793039380934379[53] = 0.0;
   out_9025793039380934379[54] = 0.0;
   out_9025793039380934379[55] = 0.0;
   out_9025793039380934379[56] = 0.0;
   out_9025793039380934379[57] = 1.0;
   out_9025793039380934379[58] = 0.0;
   out_9025793039380934379[59] = 0.0;
   out_9025793039380934379[60] = 0.0;
   out_9025793039380934379[61] = 0.0;
   out_9025793039380934379[62] = 0.0;
   out_9025793039380934379[63] = 0.0;
   out_9025793039380934379[64] = 0.0;
   out_9025793039380934379[65] = 0.0;
   out_9025793039380934379[66] = 0.0;
   out_9025793039380934379[67] = 0.0;
   out_9025793039380934379[68] = 0.0;
   out_9025793039380934379[69] = 0.0;
   out_9025793039380934379[70] = 0.0;
   out_9025793039380934379[71] = 0.0;
   out_9025793039380934379[72] = 0.0;
   out_9025793039380934379[73] = 0.0;
   out_9025793039380934379[74] = 0.0;
   out_9025793039380934379[75] = 0.0;
   out_9025793039380934379[76] = 1.0;
   out_9025793039380934379[77] = 0.0;
   out_9025793039380934379[78] = 0.0;
   out_9025793039380934379[79] = 0.0;
   out_9025793039380934379[80] = 0.0;
   out_9025793039380934379[81] = 0.0;
   out_9025793039380934379[82] = 0.0;
   out_9025793039380934379[83] = 0.0;
   out_9025793039380934379[84] = 0.0;
   out_9025793039380934379[85] = 0.0;
   out_9025793039380934379[86] = 0.0;
   out_9025793039380934379[87] = 0.0;
   out_9025793039380934379[88] = 0.0;
   out_9025793039380934379[89] = 0.0;
   out_9025793039380934379[90] = 0.0;
   out_9025793039380934379[91] = 0.0;
   out_9025793039380934379[92] = 0.0;
   out_9025793039380934379[93] = 0.0;
   out_9025793039380934379[94] = 0.0;
   out_9025793039380934379[95] = 1.0;
   out_9025793039380934379[96] = 0.0;
   out_9025793039380934379[97] = 0.0;
   out_9025793039380934379[98] = 0.0;
   out_9025793039380934379[99] = 0.0;
   out_9025793039380934379[100] = 0.0;
   out_9025793039380934379[101] = 0.0;
   out_9025793039380934379[102] = 0.0;
   out_9025793039380934379[103] = 0.0;
   out_9025793039380934379[104] = 0.0;
   out_9025793039380934379[105] = 0.0;
   out_9025793039380934379[106] = 0.0;
   out_9025793039380934379[107] = 0.0;
   out_9025793039380934379[108] = 0.0;
   out_9025793039380934379[109] = 0.0;
   out_9025793039380934379[110] = 0.0;
   out_9025793039380934379[111] = 0.0;
   out_9025793039380934379[112] = 0.0;
   out_9025793039380934379[113] = 0.0;
   out_9025793039380934379[114] = 1.0;
   out_9025793039380934379[115] = 0.0;
   out_9025793039380934379[116] = 0.0;
   out_9025793039380934379[117] = 0.0;
   out_9025793039380934379[118] = 0.0;
   out_9025793039380934379[119] = 0.0;
   out_9025793039380934379[120] = 0.0;
   out_9025793039380934379[121] = 0.0;
   out_9025793039380934379[122] = 0.0;
   out_9025793039380934379[123] = 0.0;
   out_9025793039380934379[124] = 0.0;
   out_9025793039380934379[125] = 0.0;
   out_9025793039380934379[126] = 0.0;
   out_9025793039380934379[127] = 0.0;
   out_9025793039380934379[128] = 0.0;
   out_9025793039380934379[129] = 0.0;
   out_9025793039380934379[130] = 0.0;
   out_9025793039380934379[131] = 0.0;
   out_9025793039380934379[132] = 0.0;
   out_9025793039380934379[133] = 1.0;
   out_9025793039380934379[134] = 0.0;
   out_9025793039380934379[135] = 0.0;
   out_9025793039380934379[136] = 0.0;
   out_9025793039380934379[137] = 0.0;
   out_9025793039380934379[138] = 0.0;
   out_9025793039380934379[139] = 0.0;
   out_9025793039380934379[140] = 0.0;
   out_9025793039380934379[141] = 0.0;
   out_9025793039380934379[142] = 0.0;
   out_9025793039380934379[143] = 0.0;
   out_9025793039380934379[144] = 0.0;
   out_9025793039380934379[145] = 0.0;
   out_9025793039380934379[146] = 0.0;
   out_9025793039380934379[147] = 0.0;
   out_9025793039380934379[148] = 0.0;
   out_9025793039380934379[149] = 0.0;
   out_9025793039380934379[150] = 0.0;
   out_9025793039380934379[151] = 0.0;
   out_9025793039380934379[152] = 1.0;
   out_9025793039380934379[153] = 0.0;
   out_9025793039380934379[154] = 0.0;
   out_9025793039380934379[155] = 0.0;
   out_9025793039380934379[156] = 0.0;
   out_9025793039380934379[157] = 0.0;
   out_9025793039380934379[158] = 0.0;
   out_9025793039380934379[159] = 0.0;
   out_9025793039380934379[160] = 0.0;
   out_9025793039380934379[161] = 0.0;
   out_9025793039380934379[162] = 0.0;
   out_9025793039380934379[163] = 0.0;
   out_9025793039380934379[164] = 0.0;
   out_9025793039380934379[165] = 0.0;
   out_9025793039380934379[166] = 0.0;
   out_9025793039380934379[167] = 0.0;
   out_9025793039380934379[168] = 0.0;
   out_9025793039380934379[169] = 0.0;
   out_9025793039380934379[170] = 0.0;
   out_9025793039380934379[171] = 1.0;
   out_9025793039380934379[172] = 0.0;
   out_9025793039380934379[173] = 0.0;
   out_9025793039380934379[174] = 0.0;
   out_9025793039380934379[175] = 0.0;
   out_9025793039380934379[176] = 0.0;
   out_9025793039380934379[177] = 0.0;
   out_9025793039380934379[178] = 0.0;
   out_9025793039380934379[179] = 0.0;
   out_9025793039380934379[180] = 0.0;
   out_9025793039380934379[181] = 0.0;
   out_9025793039380934379[182] = 0.0;
   out_9025793039380934379[183] = 0.0;
   out_9025793039380934379[184] = 0.0;
   out_9025793039380934379[185] = 0.0;
   out_9025793039380934379[186] = 0.0;
   out_9025793039380934379[187] = 0.0;
   out_9025793039380934379[188] = 0.0;
   out_9025793039380934379[189] = 0.0;
   out_9025793039380934379[190] = 1.0;
   out_9025793039380934379[191] = 0.0;
   out_9025793039380934379[192] = 0.0;
   out_9025793039380934379[193] = 0.0;
   out_9025793039380934379[194] = 0.0;
   out_9025793039380934379[195] = 0.0;
   out_9025793039380934379[196] = 0.0;
   out_9025793039380934379[197] = 0.0;
   out_9025793039380934379[198] = 0.0;
   out_9025793039380934379[199] = 0.0;
   out_9025793039380934379[200] = 0.0;
   out_9025793039380934379[201] = 0.0;
   out_9025793039380934379[202] = 0.0;
   out_9025793039380934379[203] = 0.0;
   out_9025793039380934379[204] = 0.0;
   out_9025793039380934379[205] = 0.0;
   out_9025793039380934379[206] = 0.0;
   out_9025793039380934379[207] = 0.0;
   out_9025793039380934379[208] = 0.0;
   out_9025793039380934379[209] = 1.0;
   out_9025793039380934379[210] = 0.0;
   out_9025793039380934379[211] = 0.0;
   out_9025793039380934379[212] = 0.0;
   out_9025793039380934379[213] = 0.0;
   out_9025793039380934379[214] = 0.0;
   out_9025793039380934379[215] = 0.0;
   out_9025793039380934379[216] = 0.0;
   out_9025793039380934379[217] = 0.0;
   out_9025793039380934379[218] = 0.0;
   out_9025793039380934379[219] = 0.0;
   out_9025793039380934379[220] = 0.0;
   out_9025793039380934379[221] = 0.0;
   out_9025793039380934379[222] = 0.0;
   out_9025793039380934379[223] = 0.0;
   out_9025793039380934379[224] = 0.0;
   out_9025793039380934379[225] = 0.0;
   out_9025793039380934379[226] = 0.0;
   out_9025793039380934379[227] = 0.0;
   out_9025793039380934379[228] = 1.0;
   out_9025793039380934379[229] = 0.0;
   out_9025793039380934379[230] = 0.0;
   out_9025793039380934379[231] = 0.0;
   out_9025793039380934379[232] = 0.0;
   out_9025793039380934379[233] = 0.0;
   out_9025793039380934379[234] = 0.0;
   out_9025793039380934379[235] = 0.0;
   out_9025793039380934379[236] = 0.0;
   out_9025793039380934379[237] = 0.0;
   out_9025793039380934379[238] = 0.0;
   out_9025793039380934379[239] = 0.0;
   out_9025793039380934379[240] = 0.0;
   out_9025793039380934379[241] = 0.0;
   out_9025793039380934379[242] = 0.0;
   out_9025793039380934379[243] = 0.0;
   out_9025793039380934379[244] = 0.0;
   out_9025793039380934379[245] = 0.0;
   out_9025793039380934379[246] = 0.0;
   out_9025793039380934379[247] = 1.0;
   out_9025793039380934379[248] = 0.0;
   out_9025793039380934379[249] = 0.0;
   out_9025793039380934379[250] = 0.0;
   out_9025793039380934379[251] = 0.0;
   out_9025793039380934379[252] = 0.0;
   out_9025793039380934379[253] = 0.0;
   out_9025793039380934379[254] = 0.0;
   out_9025793039380934379[255] = 0.0;
   out_9025793039380934379[256] = 0.0;
   out_9025793039380934379[257] = 0.0;
   out_9025793039380934379[258] = 0.0;
   out_9025793039380934379[259] = 0.0;
   out_9025793039380934379[260] = 0.0;
   out_9025793039380934379[261] = 0.0;
   out_9025793039380934379[262] = 0.0;
   out_9025793039380934379[263] = 0.0;
   out_9025793039380934379[264] = 0.0;
   out_9025793039380934379[265] = 0.0;
   out_9025793039380934379[266] = 1.0;
   out_9025793039380934379[267] = 0.0;
   out_9025793039380934379[268] = 0.0;
   out_9025793039380934379[269] = 0.0;
   out_9025793039380934379[270] = 0.0;
   out_9025793039380934379[271] = 0.0;
   out_9025793039380934379[272] = 0.0;
   out_9025793039380934379[273] = 0.0;
   out_9025793039380934379[274] = 0.0;
   out_9025793039380934379[275] = 0.0;
   out_9025793039380934379[276] = 0.0;
   out_9025793039380934379[277] = 0.0;
   out_9025793039380934379[278] = 0.0;
   out_9025793039380934379[279] = 0.0;
   out_9025793039380934379[280] = 0.0;
   out_9025793039380934379[281] = 0.0;
   out_9025793039380934379[282] = 0.0;
   out_9025793039380934379[283] = 0.0;
   out_9025793039380934379[284] = 0.0;
   out_9025793039380934379[285] = 1.0;
   out_9025793039380934379[286] = 0.0;
   out_9025793039380934379[287] = 0.0;
   out_9025793039380934379[288] = 0.0;
   out_9025793039380934379[289] = 0.0;
   out_9025793039380934379[290] = 0.0;
   out_9025793039380934379[291] = 0.0;
   out_9025793039380934379[292] = 0.0;
   out_9025793039380934379[293] = 0.0;
   out_9025793039380934379[294] = 0.0;
   out_9025793039380934379[295] = 0.0;
   out_9025793039380934379[296] = 0.0;
   out_9025793039380934379[297] = 0.0;
   out_9025793039380934379[298] = 0.0;
   out_9025793039380934379[299] = 0.0;
   out_9025793039380934379[300] = 0.0;
   out_9025793039380934379[301] = 0.0;
   out_9025793039380934379[302] = 0.0;
   out_9025793039380934379[303] = 0.0;
   out_9025793039380934379[304] = 1.0;
   out_9025793039380934379[305] = 0.0;
   out_9025793039380934379[306] = 0.0;
   out_9025793039380934379[307] = 0.0;
   out_9025793039380934379[308] = 0.0;
   out_9025793039380934379[309] = 0.0;
   out_9025793039380934379[310] = 0.0;
   out_9025793039380934379[311] = 0.0;
   out_9025793039380934379[312] = 0.0;
   out_9025793039380934379[313] = 0.0;
   out_9025793039380934379[314] = 0.0;
   out_9025793039380934379[315] = 0.0;
   out_9025793039380934379[316] = 0.0;
   out_9025793039380934379[317] = 0.0;
   out_9025793039380934379[318] = 0.0;
   out_9025793039380934379[319] = 0.0;
   out_9025793039380934379[320] = 0.0;
   out_9025793039380934379[321] = 0.0;
   out_9025793039380934379[322] = 0.0;
   out_9025793039380934379[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5208585272876606477) {
   out_5208585272876606477[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5208585272876606477[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5208585272876606477[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5208585272876606477[3] = dt*state[12] + state[3];
   out_5208585272876606477[4] = dt*state[13] + state[4];
   out_5208585272876606477[5] = dt*state[14] + state[5];
   out_5208585272876606477[6] = state[6];
   out_5208585272876606477[7] = state[7];
   out_5208585272876606477[8] = state[8];
   out_5208585272876606477[9] = state[9];
   out_5208585272876606477[10] = state[10];
   out_5208585272876606477[11] = state[11];
   out_5208585272876606477[12] = state[12];
   out_5208585272876606477[13] = state[13];
   out_5208585272876606477[14] = state[14];
   out_5208585272876606477[15] = state[15];
   out_5208585272876606477[16] = state[16];
   out_5208585272876606477[17] = state[17];
}
void F_fun(double *state, double dt, double *out_7627934588865845465) {
   out_7627934588865845465[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7627934588865845465[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7627934588865845465[2] = 0;
   out_7627934588865845465[3] = 0;
   out_7627934588865845465[4] = 0;
   out_7627934588865845465[5] = 0;
   out_7627934588865845465[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7627934588865845465[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7627934588865845465[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7627934588865845465[9] = 0;
   out_7627934588865845465[10] = 0;
   out_7627934588865845465[11] = 0;
   out_7627934588865845465[12] = 0;
   out_7627934588865845465[13] = 0;
   out_7627934588865845465[14] = 0;
   out_7627934588865845465[15] = 0;
   out_7627934588865845465[16] = 0;
   out_7627934588865845465[17] = 0;
   out_7627934588865845465[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7627934588865845465[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7627934588865845465[20] = 0;
   out_7627934588865845465[21] = 0;
   out_7627934588865845465[22] = 0;
   out_7627934588865845465[23] = 0;
   out_7627934588865845465[24] = 0;
   out_7627934588865845465[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7627934588865845465[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7627934588865845465[27] = 0;
   out_7627934588865845465[28] = 0;
   out_7627934588865845465[29] = 0;
   out_7627934588865845465[30] = 0;
   out_7627934588865845465[31] = 0;
   out_7627934588865845465[32] = 0;
   out_7627934588865845465[33] = 0;
   out_7627934588865845465[34] = 0;
   out_7627934588865845465[35] = 0;
   out_7627934588865845465[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7627934588865845465[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7627934588865845465[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7627934588865845465[39] = 0;
   out_7627934588865845465[40] = 0;
   out_7627934588865845465[41] = 0;
   out_7627934588865845465[42] = 0;
   out_7627934588865845465[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7627934588865845465[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7627934588865845465[45] = 0;
   out_7627934588865845465[46] = 0;
   out_7627934588865845465[47] = 0;
   out_7627934588865845465[48] = 0;
   out_7627934588865845465[49] = 0;
   out_7627934588865845465[50] = 0;
   out_7627934588865845465[51] = 0;
   out_7627934588865845465[52] = 0;
   out_7627934588865845465[53] = 0;
   out_7627934588865845465[54] = 0;
   out_7627934588865845465[55] = 0;
   out_7627934588865845465[56] = 0;
   out_7627934588865845465[57] = 1;
   out_7627934588865845465[58] = 0;
   out_7627934588865845465[59] = 0;
   out_7627934588865845465[60] = 0;
   out_7627934588865845465[61] = 0;
   out_7627934588865845465[62] = 0;
   out_7627934588865845465[63] = 0;
   out_7627934588865845465[64] = 0;
   out_7627934588865845465[65] = 0;
   out_7627934588865845465[66] = dt;
   out_7627934588865845465[67] = 0;
   out_7627934588865845465[68] = 0;
   out_7627934588865845465[69] = 0;
   out_7627934588865845465[70] = 0;
   out_7627934588865845465[71] = 0;
   out_7627934588865845465[72] = 0;
   out_7627934588865845465[73] = 0;
   out_7627934588865845465[74] = 0;
   out_7627934588865845465[75] = 0;
   out_7627934588865845465[76] = 1;
   out_7627934588865845465[77] = 0;
   out_7627934588865845465[78] = 0;
   out_7627934588865845465[79] = 0;
   out_7627934588865845465[80] = 0;
   out_7627934588865845465[81] = 0;
   out_7627934588865845465[82] = 0;
   out_7627934588865845465[83] = 0;
   out_7627934588865845465[84] = 0;
   out_7627934588865845465[85] = dt;
   out_7627934588865845465[86] = 0;
   out_7627934588865845465[87] = 0;
   out_7627934588865845465[88] = 0;
   out_7627934588865845465[89] = 0;
   out_7627934588865845465[90] = 0;
   out_7627934588865845465[91] = 0;
   out_7627934588865845465[92] = 0;
   out_7627934588865845465[93] = 0;
   out_7627934588865845465[94] = 0;
   out_7627934588865845465[95] = 1;
   out_7627934588865845465[96] = 0;
   out_7627934588865845465[97] = 0;
   out_7627934588865845465[98] = 0;
   out_7627934588865845465[99] = 0;
   out_7627934588865845465[100] = 0;
   out_7627934588865845465[101] = 0;
   out_7627934588865845465[102] = 0;
   out_7627934588865845465[103] = 0;
   out_7627934588865845465[104] = dt;
   out_7627934588865845465[105] = 0;
   out_7627934588865845465[106] = 0;
   out_7627934588865845465[107] = 0;
   out_7627934588865845465[108] = 0;
   out_7627934588865845465[109] = 0;
   out_7627934588865845465[110] = 0;
   out_7627934588865845465[111] = 0;
   out_7627934588865845465[112] = 0;
   out_7627934588865845465[113] = 0;
   out_7627934588865845465[114] = 1;
   out_7627934588865845465[115] = 0;
   out_7627934588865845465[116] = 0;
   out_7627934588865845465[117] = 0;
   out_7627934588865845465[118] = 0;
   out_7627934588865845465[119] = 0;
   out_7627934588865845465[120] = 0;
   out_7627934588865845465[121] = 0;
   out_7627934588865845465[122] = 0;
   out_7627934588865845465[123] = 0;
   out_7627934588865845465[124] = 0;
   out_7627934588865845465[125] = 0;
   out_7627934588865845465[126] = 0;
   out_7627934588865845465[127] = 0;
   out_7627934588865845465[128] = 0;
   out_7627934588865845465[129] = 0;
   out_7627934588865845465[130] = 0;
   out_7627934588865845465[131] = 0;
   out_7627934588865845465[132] = 0;
   out_7627934588865845465[133] = 1;
   out_7627934588865845465[134] = 0;
   out_7627934588865845465[135] = 0;
   out_7627934588865845465[136] = 0;
   out_7627934588865845465[137] = 0;
   out_7627934588865845465[138] = 0;
   out_7627934588865845465[139] = 0;
   out_7627934588865845465[140] = 0;
   out_7627934588865845465[141] = 0;
   out_7627934588865845465[142] = 0;
   out_7627934588865845465[143] = 0;
   out_7627934588865845465[144] = 0;
   out_7627934588865845465[145] = 0;
   out_7627934588865845465[146] = 0;
   out_7627934588865845465[147] = 0;
   out_7627934588865845465[148] = 0;
   out_7627934588865845465[149] = 0;
   out_7627934588865845465[150] = 0;
   out_7627934588865845465[151] = 0;
   out_7627934588865845465[152] = 1;
   out_7627934588865845465[153] = 0;
   out_7627934588865845465[154] = 0;
   out_7627934588865845465[155] = 0;
   out_7627934588865845465[156] = 0;
   out_7627934588865845465[157] = 0;
   out_7627934588865845465[158] = 0;
   out_7627934588865845465[159] = 0;
   out_7627934588865845465[160] = 0;
   out_7627934588865845465[161] = 0;
   out_7627934588865845465[162] = 0;
   out_7627934588865845465[163] = 0;
   out_7627934588865845465[164] = 0;
   out_7627934588865845465[165] = 0;
   out_7627934588865845465[166] = 0;
   out_7627934588865845465[167] = 0;
   out_7627934588865845465[168] = 0;
   out_7627934588865845465[169] = 0;
   out_7627934588865845465[170] = 0;
   out_7627934588865845465[171] = 1;
   out_7627934588865845465[172] = 0;
   out_7627934588865845465[173] = 0;
   out_7627934588865845465[174] = 0;
   out_7627934588865845465[175] = 0;
   out_7627934588865845465[176] = 0;
   out_7627934588865845465[177] = 0;
   out_7627934588865845465[178] = 0;
   out_7627934588865845465[179] = 0;
   out_7627934588865845465[180] = 0;
   out_7627934588865845465[181] = 0;
   out_7627934588865845465[182] = 0;
   out_7627934588865845465[183] = 0;
   out_7627934588865845465[184] = 0;
   out_7627934588865845465[185] = 0;
   out_7627934588865845465[186] = 0;
   out_7627934588865845465[187] = 0;
   out_7627934588865845465[188] = 0;
   out_7627934588865845465[189] = 0;
   out_7627934588865845465[190] = 1;
   out_7627934588865845465[191] = 0;
   out_7627934588865845465[192] = 0;
   out_7627934588865845465[193] = 0;
   out_7627934588865845465[194] = 0;
   out_7627934588865845465[195] = 0;
   out_7627934588865845465[196] = 0;
   out_7627934588865845465[197] = 0;
   out_7627934588865845465[198] = 0;
   out_7627934588865845465[199] = 0;
   out_7627934588865845465[200] = 0;
   out_7627934588865845465[201] = 0;
   out_7627934588865845465[202] = 0;
   out_7627934588865845465[203] = 0;
   out_7627934588865845465[204] = 0;
   out_7627934588865845465[205] = 0;
   out_7627934588865845465[206] = 0;
   out_7627934588865845465[207] = 0;
   out_7627934588865845465[208] = 0;
   out_7627934588865845465[209] = 1;
   out_7627934588865845465[210] = 0;
   out_7627934588865845465[211] = 0;
   out_7627934588865845465[212] = 0;
   out_7627934588865845465[213] = 0;
   out_7627934588865845465[214] = 0;
   out_7627934588865845465[215] = 0;
   out_7627934588865845465[216] = 0;
   out_7627934588865845465[217] = 0;
   out_7627934588865845465[218] = 0;
   out_7627934588865845465[219] = 0;
   out_7627934588865845465[220] = 0;
   out_7627934588865845465[221] = 0;
   out_7627934588865845465[222] = 0;
   out_7627934588865845465[223] = 0;
   out_7627934588865845465[224] = 0;
   out_7627934588865845465[225] = 0;
   out_7627934588865845465[226] = 0;
   out_7627934588865845465[227] = 0;
   out_7627934588865845465[228] = 1;
   out_7627934588865845465[229] = 0;
   out_7627934588865845465[230] = 0;
   out_7627934588865845465[231] = 0;
   out_7627934588865845465[232] = 0;
   out_7627934588865845465[233] = 0;
   out_7627934588865845465[234] = 0;
   out_7627934588865845465[235] = 0;
   out_7627934588865845465[236] = 0;
   out_7627934588865845465[237] = 0;
   out_7627934588865845465[238] = 0;
   out_7627934588865845465[239] = 0;
   out_7627934588865845465[240] = 0;
   out_7627934588865845465[241] = 0;
   out_7627934588865845465[242] = 0;
   out_7627934588865845465[243] = 0;
   out_7627934588865845465[244] = 0;
   out_7627934588865845465[245] = 0;
   out_7627934588865845465[246] = 0;
   out_7627934588865845465[247] = 1;
   out_7627934588865845465[248] = 0;
   out_7627934588865845465[249] = 0;
   out_7627934588865845465[250] = 0;
   out_7627934588865845465[251] = 0;
   out_7627934588865845465[252] = 0;
   out_7627934588865845465[253] = 0;
   out_7627934588865845465[254] = 0;
   out_7627934588865845465[255] = 0;
   out_7627934588865845465[256] = 0;
   out_7627934588865845465[257] = 0;
   out_7627934588865845465[258] = 0;
   out_7627934588865845465[259] = 0;
   out_7627934588865845465[260] = 0;
   out_7627934588865845465[261] = 0;
   out_7627934588865845465[262] = 0;
   out_7627934588865845465[263] = 0;
   out_7627934588865845465[264] = 0;
   out_7627934588865845465[265] = 0;
   out_7627934588865845465[266] = 1;
   out_7627934588865845465[267] = 0;
   out_7627934588865845465[268] = 0;
   out_7627934588865845465[269] = 0;
   out_7627934588865845465[270] = 0;
   out_7627934588865845465[271] = 0;
   out_7627934588865845465[272] = 0;
   out_7627934588865845465[273] = 0;
   out_7627934588865845465[274] = 0;
   out_7627934588865845465[275] = 0;
   out_7627934588865845465[276] = 0;
   out_7627934588865845465[277] = 0;
   out_7627934588865845465[278] = 0;
   out_7627934588865845465[279] = 0;
   out_7627934588865845465[280] = 0;
   out_7627934588865845465[281] = 0;
   out_7627934588865845465[282] = 0;
   out_7627934588865845465[283] = 0;
   out_7627934588865845465[284] = 0;
   out_7627934588865845465[285] = 1;
   out_7627934588865845465[286] = 0;
   out_7627934588865845465[287] = 0;
   out_7627934588865845465[288] = 0;
   out_7627934588865845465[289] = 0;
   out_7627934588865845465[290] = 0;
   out_7627934588865845465[291] = 0;
   out_7627934588865845465[292] = 0;
   out_7627934588865845465[293] = 0;
   out_7627934588865845465[294] = 0;
   out_7627934588865845465[295] = 0;
   out_7627934588865845465[296] = 0;
   out_7627934588865845465[297] = 0;
   out_7627934588865845465[298] = 0;
   out_7627934588865845465[299] = 0;
   out_7627934588865845465[300] = 0;
   out_7627934588865845465[301] = 0;
   out_7627934588865845465[302] = 0;
   out_7627934588865845465[303] = 0;
   out_7627934588865845465[304] = 1;
   out_7627934588865845465[305] = 0;
   out_7627934588865845465[306] = 0;
   out_7627934588865845465[307] = 0;
   out_7627934588865845465[308] = 0;
   out_7627934588865845465[309] = 0;
   out_7627934588865845465[310] = 0;
   out_7627934588865845465[311] = 0;
   out_7627934588865845465[312] = 0;
   out_7627934588865845465[313] = 0;
   out_7627934588865845465[314] = 0;
   out_7627934588865845465[315] = 0;
   out_7627934588865845465[316] = 0;
   out_7627934588865845465[317] = 0;
   out_7627934588865845465[318] = 0;
   out_7627934588865845465[319] = 0;
   out_7627934588865845465[320] = 0;
   out_7627934588865845465[321] = 0;
   out_7627934588865845465[322] = 0;
   out_7627934588865845465[323] = 1;
}
void h_4(double *state, double *unused, double *out_2307759765937998853) {
   out_2307759765937998853[0] = state[6] + state[9];
   out_2307759765937998853[1] = state[7] + state[10];
   out_2307759765937998853[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6269034493598865802) {
   out_6269034493598865802[0] = 0;
   out_6269034493598865802[1] = 0;
   out_6269034493598865802[2] = 0;
   out_6269034493598865802[3] = 0;
   out_6269034493598865802[4] = 0;
   out_6269034493598865802[5] = 0;
   out_6269034493598865802[6] = 1;
   out_6269034493598865802[7] = 0;
   out_6269034493598865802[8] = 0;
   out_6269034493598865802[9] = 1;
   out_6269034493598865802[10] = 0;
   out_6269034493598865802[11] = 0;
   out_6269034493598865802[12] = 0;
   out_6269034493598865802[13] = 0;
   out_6269034493598865802[14] = 0;
   out_6269034493598865802[15] = 0;
   out_6269034493598865802[16] = 0;
   out_6269034493598865802[17] = 0;
   out_6269034493598865802[18] = 0;
   out_6269034493598865802[19] = 0;
   out_6269034493598865802[20] = 0;
   out_6269034493598865802[21] = 0;
   out_6269034493598865802[22] = 0;
   out_6269034493598865802[23] = 0;
   out_6269034493598865802[24] = 0;
   out_6269034493598865802[25] = 1;
   out_6269034493598865802[26] = 0;
   out_6269034493598865802[27] = 0;
   out_6269034493598865802[28] = 1;
   out_6269034493598865802[29] = 0;
   out_6269034493598865802[30] = 0;
   out_6269034493598865802[31] = 0;
   out_6269034493598865802[32] = 0;
   out_6269034493598865802[33] = 0;
   out_6269034493598865802[34] = 0;
   out_6269034493598865802[35] = 0;
   out_6269034493598865802[36] = 0;
   out_6269034493598865802[37] = 0;
   out_6269034493598865802[38] = 0;
   out_6269034493598865802[39] = 0;
   out_6269034493598865802[40] = 0;
   out_6269034493598865802[41] = 0;
   out_6269034493598865802[42] = 0;
   out_6269034493598865802[43] = 0;
   out_6269034493598865802[44] = 1;
   out_6269034493598865802[45] = 0;
   out_6269034493598865802[46] = 0;
   out_6269034493598865802[47] = 1;
   out_6269034493598865802[48] = 0;
   out_6269034493598865802[49] = 0;
   out_6269034493598865802[50] = 0;
   out_6269034493598865802[51] = 0;
   out_6269034493598865802[52] = 0;
   out_6269034493598865802[53] = 0;
}
void h_10(double *state, double *unused, double *out_7546301760810218582) {
   out_7546301760810218582[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_7546301760810218582[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_7546301760810218582[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_8725060870542409515) {
   out_8725060870542409515[0] = 0;
   out_8725060870542409515[1] = 9.8100000000000005*cos(state[1]);
   out_8725060870542409515[2] = 0;
   out_8725060870542409515[3] = 0;
   out_8725060870542409515[4] = -state[8];
   out_8725060870542409515[5] = state[7];
   out_8725060870542409515[6] = 0;
   out_8725060870542409515[7] = state[5];
   out_8725060870542409515[8] = -state[4];
   out_8725060870542409515[9] = 0;
   out_8725060870542409515[10] = 0;
   out_8725060870542409515[11] = 0;
   out_8725060870542409515[12] = 1;
   out_8725060870542409515[13] = 0;
   out_8725060870542409515[14] = 0;
   out_8725060870542409515[15] = 1;
   out_8725060870542409515[16] = 0;
   out_8725060870542409515[17] = 0;
   out_8725060870542409515[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_8725060870542409515[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_8725060870542409515[20] = 0;
   out_8725060870542409515[21] = state[8];
   out_8725060870542409515[22] = 0;
   out_8725060870542409515[23] = -state[6];
   out_8725060870542409515[24] = -state[5];
   out_8725060870542409515[25] = 0;
   out_8725060870542409515[26] = state[3];
   out_8725060870542409515[27] = 0;
   out_8725060870542409515[28] = 0;
   out_8725060870542409515[29] = 0;
   out_8725060870542409515[30] = 0;
   out_8725060870542409515[31] = 1;
   out_8725060870542409515[32] = 0;
   out_8725060870542409515[33] = 0;
   out_8725060870542409515[34] = 1;
   out_8725060870542409515[35] = 0;
   out_8725060870542409515[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_8725060870542409515[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_8725060870542409515[38] = 0;
   out_8725060870542409515[39] = -state[7];
   out_8725060870542409515[40] = state[6];
   out_8725060870542409515[41] = 0;
   out_8725060870542409515[42] = state[4];
   out_8725060870542409515[43] = -state[3];
   out_8725060870542409515[44] = 0;
   out_8725060870542409515[45] = 0;
   out_8725060870542409515[46] = 0;
   out_8725060870542409515[47] = 0;
   out_8725060870542409515[48] = 0;
   out_8725060870542409515[49] = 0;
   out_8725060870542409515[50] = 1;
   out_8725060870542409515[51] = 0;
   out_8725060870542409515[52] = 0;
   out_8725060870542409515[53] = 1;
}
void h_13(double *state, double *unused, double *out_3092656760019408503) {
   out_3092656760019408503[0] = state[3];
   out_3092656760019408503[1] = state[4];
   out_3092656760019408503[2] = state[5];
}
void H_13(double *state, double *unused, double *out_8965435754778353013) {
   out_8965435754778353013[0] = 0;
   out_8965435754778353013[1] = 0;
   out_8965435754778353013[2] = 0;
   out_8965435754778353013[3] = 1;
   out_8965435754778353013[4] = 0;
   out_8965435754778353013[5] = 0;
   out_8965435754778353013[6] = 0;
   out_8965435754778353013[7] = 0;
   out_8965435754778353013[8] = 0;
   out_8965435754778353013[9] = 0;
   out_8965435754778353013[10] = 0;
   out_8965435754778353013[11] = 0;
   out_8965435754778353013[12] = 0;
   out_8965435754778353013[13] = 0;
   out_8965435754778353013[14] = 0;
   out_8965435754778353013[15] = 0;
   out_8965435754778353013[16] = 0;
   out_8965435754778353013[17] = 0;
   out_8965435754778353013[18] = 0;
   out_8965435754778353013[19] = 0;
   out_8965435754778353013[20] = 0;
   out_8965435754778353013[21] = 0;
   out_8965435754778353013[22] = 1;
   out_8965435754778353013[23] = 0;
   out_8965435754778353013[24] = 0;
   out_8965435754778353013[25] = 0;
   out_8965435754778353013[26] = 0;
   out_8965435754778353013[27] = 0;
   out_8965435754778353013[28] = 0;
   out_8965435754778353013[29] = 0;
   out_8965435754778353013[30] = 0;
   out_8965435754778353013[31] = 0;
   out_8965435754778353013[32] = 0;
   out_8965435754778353013[33] = 0;
   out_8965435754778353013[34] = 0;
   out_8965435754778353013[35] = 0;
   out_8965435754778353013[36] = 0;
   out_8965435754778353013[37] = 0;
   out_8965435754778353013[38] = 0;
   out_8965435754778353013[39] = 0;
   out_8965435754778353013[40] = 0;
   out_8965435754778353013[41] = 1;
   out_8965435754778353013[42] = 0;
   out_8965435754778353013[43] = 0;
   out_8965435754778353013[44] = 0;
   out_8965435754778353013[45] = 0;
   out_8965435754778353013[46] = 0;
   out_8965435754778353013[47] = 0;
   out_8965435754778353013[48] = 0;
   out_8965435754778353013[49] = 0;
   out_8965435754778353013[50] = 0;
   out_8965435754778353013[51] = 0;
   out_8965435754778353013[52] = 0;
   out_8965435754778353013[53] = 0;
}
void h_14(double *state, double *unused, double *out_9098138133249498712) {
   out_9098138133249498712[0] = state[6];
   out_9098138133249498712[1] = state[7];
   out_9098138133249498712[2] = state[8];
}
void H_14(double *state, double *unused, double *out_8214468723771201285) {
   out_8214468723771201285[0] = 0;
   out_8214468723771201285[1] = 0;
   out_8214468723771201285[2] = 0;
   out_8214468723771201285[3] = 0;
   out_8214468723771201285[4] = 0;
   out_8214468723771201285[5] = 0;
   out_8214468723771201285[6] = 1;
   out_8214468723771201285[7] = 0;
   out_8214468723771201285[8] = 0;
   out_8214468723771201285[9] = 0;
   out_8214468723771201285[10] = 0;
   out_8214468723771201285[11] = 0;
   out_8214468723771201285[12] = 0;
   out_8214468723771201285[13] = 0;
   out_8214468723771201285[14] = 0;
   out_8214468723771201285[15] = 0;
   out_8214468723771201285[16] = 0;
   out_8214468723771201285[17] = 0;
   out_8214468723771201285[18] = 0;
   out_8214468723771201285[19] = 0;
   out_8214468723771201285[20] = 0;
   out_8214468723771201285[21] = 0;
   out_8214468723771201285[22] = 0;
   out_8214468723771201285[23] = 0;
   out_8214468723771201285[24] = 0;
   out_8214468723771201285[25] = 1;
   out_8214468723771201285[26] = 0;
   out_8214468723771201285[27] = 0;
   out_8214468723771201285[28] = 0;
   out_8214468723771201285[29] = 0;
   out_8214468723771201285[30] = 0;
   out_8214468723771201285[31] = 0;
   out_8214468723771201285[32] = 0;
   out_8214468723771201285[33] = 0;
   out_8214468723771201285[34] = 0;
   out_8214468723771201285[35] = 0;
   out_8214468723771201285[36] = 0;
   out_8214468723771201285[37] = 0;
   out_8214468723771201285[38] = 0;
   out_8214468723771201285[39] = 0;
   out_8214468723771201285[40] = 0;
   out_8214468723771201285[41] = 0;
   out_8214468723771201285[42] = 0;
   out_8214468723771201285[43] = 0;
   out_8214468723771201285[44] = 1;
   out_8214468723771201285[45] = 0;
   out_8214468723771201285[46] = 0;
   out_8214468723771201285[47] = 0;
   out_8214468723771201285[48] = 0;
   out_8214468723771201285[49] = 0;
   out_8214468723771201285[50] = 0;
   out_8214468723771201285[51] = 0;
   out_8214468723771201285[52] = 0;
   out_8214468723771201285[53] = 0;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_4830641336023112635) {
  err_fun(nom_x, delta_x, out_4830641336023112635);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7197149123055641316) {
  inv_err_fun(nom_x, true_x, out_7197149123055641316);
}
void pose_H_mod_fun(double *state, double *out_9025793039380934379) {
  H_mod_fun(state, out_9025793039380934379);
}
void pose_f_fun(double *state, double dt, double *out_5208585272876606477) {
  f_fun(state,  dt, out_5208585272876606477);
}
void pose_F_fun(double *state, double dt, double *out_7627934588865845465) {
  F_fun(state,  dt, out_7627934588865845465);
}
void pose_h_4(double *state, double *unused, double *out_2307759765937998853) {
  h_4(state, unused, out_2307759765937998853);
}
void pose_H_4(double *state, double *unused, double *out_6269034493598865802) {
  H_4(state, unused, out_6269034493598865802);
}
void pose_h_10(double *state, double *unused, double *out_7546301760810218582) {
  h_10(state, unused, out_7546301760810218582);
}
void pose_H_10(double *state, double *unused, double *out_8725060870542409515) {
  H_10(state, unused, out_8725060870542409515);
}
void pose_h_13(double *state, double *unused, double *out_3092656760019408503) {
  h_13(state, unused, out_3092656760019408503);
}
void pose_H_13(double *state, double *unused, double *out_8965435754778353013) {
  H_13(state, unused, out_8965435754778353013);
}
void pose_h_14(double *state, double *unused, double *out_9098138133249498712) {
  h_14(state, unused, out_9098138133249498712);
}
void pose_H_14(double *state, double *unused, double *out_8214468723771201285) {
  H_14(state, unused, out_8214468723771201285);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
