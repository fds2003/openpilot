#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_4830641336023112635);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7197149123055641316);
void pose_H_mod_fun(double *state, double *out_9025793039380934379);
void pose_f_fun(double *state, double dt, double *out_5208585272876606477);
void pose_F_fun(double *state, double dt, double *out_7627934588865845465);
void pose_h_4(double *state, double *unused, double *out_2307759765937998853);
void pose_H_4(double *state, double *unused, double *out_6269034493598865802);
void pose_h_10(double *state, double *unused, double *out_7546301760810218582);
void pose_H_10(double *state, double *unused, double *out_8725060870542409515);
void pose_h_13(double *state, double *unused, double *out_3092656760019408503);
void pose_H_13(double *state, double *unused, double *out_8965435754778353013);
void pose_h_14(double *state, double *unused, double *out_9098138133249498712);
void pose_H_14(double *state, double *unused, double *out_8214468723771201285);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}