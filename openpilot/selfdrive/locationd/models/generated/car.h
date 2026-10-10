#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_7915958978440955518);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4206628727365054795);
void car_H_mod_fun(double *state, double *out_4706588497916305502);
void car_f_fun(double *state, double dt, double *out_814126097081374712);
void car_F_fun(double *state, double dt, double *out_24590177961215882);
void car_h_25(double *state, double *unused, double *out_3254720649676951962);
void car_H_25(double *state, double *unused, double *out_197103327268359338);
void car_h_24(double *state, double *unused, double *out_77431955460747548);
void car_H_24(double *state, double *unused, double *out_273354154774979386);
void car_h_30(double *state, double *unused, double *out_1163032653627957605);
void car_H_30(double *state, double *unused, double *out_67764380125119268);
void car_h_26(double *state, double *unused, double *out_3262328261670273928);
void car_H_26(double *state, double *unused, double *out_3544399991605696886);
void car_h_27(double *state, double *unused, double *out_8256393917337797607);
void car_H_27(double *state, double *unused, double *out_2106998931675305643);
void car_h_29(double *state, double *unused, double *out_7242624166016269048);
void car_H_29(double *state, double *unused, double *out_3820361658544856676);
void car_h_28(double *state, double *unused, double *out_5219607865893464922);
void car_H_28(double *state, double *unused, double *out_8902760675614387250);
void car_h_31(double *state, double *unused, double *out_8421188197682248718);
void car_H_31(double *state, double *unused, double *out_227749289145319766);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}