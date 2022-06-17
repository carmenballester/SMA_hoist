/* Include files */

#include <stddef.h>
#include "blas.h"
#include "carmen_controller_sfun.h"
#include "c1_carmen_controller.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "carmen_controller_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c1_debug_family_names[9] = { "nargin", "nargout", "lectura",
  "anterior", "pasos", "offset", "salida", "salida_anterior", "sal_pasos" };

/* Function Declarations */
static void initialize_c1_carmen_controller(SFc1_carmen_controllerInstanceStruct
  *chartInstance);
static void initialize_params_c1_carmen_controller
  (SFc1_carmen_controllerInstanceStruct *chartInstance);
static void enable_c1_carmen_controller(SFc1_carmen_controllerInstanceStruct
  *chartInstance);
static void disable_c1_carmen_controller(SFc1_carmen_controllerInstanceStruct
  *chartInstance);
static void c1_update_debugger_state_c1_carmen_controller
  (SFc1_carmen_controllerInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c1_carmen_controller
  (SFc1_carmen_controllerInstanceStruct *chartInstance);
static void set_sim_state_c1_carmen_controller
  (SFc1_carmen_controllerInstanceStruct *chartInstance, const mxArray *c1_st);
static void finalize_c1_carmen_controller(SFc1_carmen_controllerInstanceStruct
  *chartInstance);
static void sf_c1_carmen_controller(SFc1_carmen_controllerInstanceStruct
  *chartInstance);
static void initSimStructsc1_carmen_controller
  (SFc1_carmen_controllerInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static int8_T c1_emlrt_marshallIn(SFc1_carmen_controllerInstanceStruct
  *chartInstance, const mxArray *c1_sal_pasos, const char_T *c1_identifier);
static int8_T c1_b_emlrt_marshallIn(SFc1_carmen_controllerInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static uint16_T c1_c_emlrt_marshallIn(SFc1_carmen_controllerInstanceStruct
  *chartInstance, const mxArray *c1_salida_anterior, const char_T *c1_identifier);
static uint16_T c1_d_emlrt_marshallIn(SFc1_carmen_controllerInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_e_emlrt_marshallIn(SFc1_carmen_controllerInstanceStruct
  *chartInstance, const mxArray *c1_salida, const char_T *c1_identifier);
static int32_T c1_f_emlrt_marshallIn(SFc1_carmen_controllerInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_g_emlrt_marshallIn(SFc1_carmen_controllerInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static void c1_info_helper(const mxArray **c1_info);
static const mxArray *c1_emlrt_marshallOut(char * c1_u);
static const mxArray *c1_b_emlrt_marshallOut(uint32_T c1_u);
static uint8_T c1_h_emlrt_marshallIn(SFc1_carmen_controllerInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_carmen_controller, const
  char_T *c1_identifier);
static uint8_T c1_i_emlrt_marshallIn(SFc1_carmen_controllerInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void init_dsm_address_info(SFc1_carmen_controllerInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c1_carmen_controller(SFc1_carmen_controllerInstanceStruct
  *chartInstance)
{
  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_is_active_c1_carmen_controller = 0U;
}

static void initialize_params_c1_carmen_controller
  (SFc1_carmen_controllerInstanceStruct *chartInstance)
{
}

static void enable_c1_carmen_controller(SFc1_carmen_controllerInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c1_carmen_controller(SFc1_carmen_controllerInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c1_update_debugger_state_c1_carmen_controller
  (SFc1_carmen_controllerInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c1_carmen_controller
  (SFc1_carmen_controllerInstanceStruct *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  int8_T c1_hoistedGlobal;
  int8_T c1_u;
  const mxArray *c1_b_y = NULL;
  int32_T c1_b_hoistedGlobal;
  int32_T c1_b_u;
  const mxArray *c1_c_y = NULL;
  uint16_T c1_c_hoistedGlobal;
  uint16_T c1_c_u;
  const mxArray *c1_d_y = NULL;
  uint8_T c1_d_hoistedGlobal;
  uint8_T c1_d_u;
  const mxArray *c1_e_y = NULL;
  int8_T *c1_sal_pasos;
  int32_T *c1_salida;
  uint16_T *c1_salida_anterior;
  c1_sal_pasos = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_salida_anterior = (uint16_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_salida = (int32_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(4), FALSE);
  c1_hoistedGlobal = *c1_sal_pasos;
  c1_u = c1_hoistedGlobal;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 2, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_b_hoistedGlobal = *c1_salida;
  c1_b_u = c1_b_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  c1_c_hoistedGlobal = *c1_salida_anterior;
  c1_c_u = c1_c_hoistedGlobal;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_c_u, 5, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 2, c1_d_y);
  c1_d_hoistedGlobal = chartInstance->c1_is_active_c1_carmen_controller;
  c1_d_u = c1_d_hoistedGlobal;
  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_d_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 3, c1_e_y);
  sf_mex_assign(&c1_st, c1_y, FALSE);
  return c1_st;
}

static void set_sim_state_c1_carmen_controller
  (SFc1_carmen_controllerInstanceStruct *chartInstance, const mxArray *c1_st)
{
  const mxArray *c1_u;
  int8_T *c1_sal_pasos;
  int32_T *c1_salida;
  uint16_T *c1_salida_anterior;
  c1_sal_pasos = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_salida_anterior = (uint16_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_salida = (int32_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c1_doneDoubleBufferReInit = TRUE;
  c1_u = sf_mex_dup(c1_st);
  *c1_sal_pasos = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c1_u, 0)), "sal_pasos");
  *c1_salida = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c1_u, 1)), "salida");
  *c1_salida_anterior = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 2)), "salida_anterior");
  chartInstance->c1_is_active_c1_carmen_controller = c1_h_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 3)),
     "is_active_c1_carmen_controller");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_carmen_controller(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_carmen_controller(SFc1_carmen_controllerInstanceStruct
  *chartInstance)
{
}

static void sf_c1_carmen_controller(SFc1_carmen_controllerInstanceStruct
  *chartInstance)
{
  uint16_T c1_hoistedGlobal;
  uint16_T c1_b_hoistedGlobal;
  int8_T c1_c_hoistedGlobal;
  uint16_T c1_d_hoistedGlobal;
  uint16_T c1_lectura;
  uint16_T c1_anterior;
  int8_T c1_pasos;
  uint16_T c1_offset;
  uint32_T c1_debug_family_var_map[9];
  real_T c1_nargin = 4.0;
  real_T c1_nargout = 3.0;
  int32_T c1_salida;
  uint16_T c1_salida_anterior;
  int8_T c1_sal_pasos;
  int32_T c1_i0;
  int32_T c1_i1;
  int32_T c1_b;
  int32_T c1_i2;
  int32_T c1_i3;
  int32_T c1_y;
  int64_T c1_i4;
  int64_T c1_i5;
  uint16_T *c1_b_lectura;
  uint16_T *c1_b_anterior;
  int32_T *c1_b_salida;
  uint16_T *c1_b_salida_anterior;
  int8_T *c1_b_pasos;
  uint16_T *c1_b_offset;
  int8_T *c1_b_sal_pasos;
  c1_b_sal_pasos = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_b_offset = (uint16_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c1_b_pasos = (int8_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c1_b_salida_anterior = (uint16_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_b_salida = (int32_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_b_anterior = (uint16_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c1_b_lectura = (uint16_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*c1_b_lectura, 0U);
  _SFD_DATA_RANGE_CHECK((real_T)*c1_b_anterior, 1U);
  _SFD_DATA_RANGE_CHECK((real_T)*c1_b_salida, 2U);
  _SFD_DATA_RANGE_CHECK((real_T)*c1_b_salida_anterior, 3U);
  _SFD_DATA_RANGE_CHECK((real_T)*c1_b_pasos, 4U);
  _SFD_DATA_RANGE_CHECK((real_T)*c1_b_offset, 5U);
  _SFD_DATA_RANGE_CHECK((real_T)*c1_b_sal_pasos, 6U);
  chartInstance->c1_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  c1_hoistedGlobal = *c1_b_lectura;
  c1_b_hoistedGlobal = *c1_b_anterior;
  c1_c_hoistedGlobal = *c1_b_pasos;
  c1_d_hoistedGlobal = *c1_b_offset;
  c1_lectura = c1_hoistedGlobal;
  c1_anterior = c1_b_hoistedGlobal;
  c1_pasos = c1_c_hoistedGlobal;
  c1_offset = c1_d_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 9U, 9U, c1_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 0U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 1U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_lectura, 2U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_anterior, 3U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_pasos, 4U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_offset, 5U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_salida, 6U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_salida_anterior, 7U,
    c1_b_sf_marshallOut, c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_sal_pasos, 8U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 4);
  c1_salida_anterior = c1_lectura;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 6);
  if (CV_EML_IF(0, 1, 0, (real_T)c1_lectura > 3500.0)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 7);
    if (CV_EML_IF(0, 1, 1, (real_T)c1_anterior < 1000.0)) {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 8);
      c1_i0 = c1_pasos + 1;
      if (c1_i0 > 127) {
        CV_SATURATION_EVAL(4, 0, 0, 0, 1);
        c1_i0 = 127;
      } else {
        if (CV_SATURATION_EVAL(4, 0, 0, 0, c1_i0 < -128)) {
          c1_i0 = -128;
        }
      }

      c1_pasos = (int8_T)c1_i0;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 12);
  if (CV_EML_IF(0, 1, 2, (real_T)c1_lectura < 1000.0)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 13);
    if (CV_EML_IF(0, 1, 3, (real_T)c1_anterior > 3500.0)) {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 14);
      c1_i1 = c1_pasos - 1;
      if (c1_i1 > 127) {
        CV_SATURATION_EVAL(4, 0, 1, 0, 1);
        c1_i1 = 127;
      } else {
        if (CV_SATURATION_EVAL(4, 0, 1, 0, c1_i1 < -128)) {
          c1_i1 = -128;
        }
      }

      c1_pasos = (int8_T)c1_i1;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 20);
  c1_sal_pasos = c1_pasos;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 22);
  if (CV_EML_IF(0, 1, 4, (real_T)c1_pasos == 0.0)) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 23);
    c1_salida = c1_offset - c1_lectura;
  } else {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 25);
    c1_b = c1_pasos;
    c1_i2 = c1_b;
    if (c1_i2 > 524287) {
      CV_SATURATION_EVAL(4, 0, 4, 0, 1);
      c1_i3 = MAX_int32_T;
    } else if (CV_SATURATION_EVAL(4, 0, 4, 0, c1_i2 <= -524288)) {
      c1_i3 = MIN_int32_T;
    } else {
      c1_i3 = c1_i2 << 12;
    }

    c1_y = c1_i3;
    c1_i4 = (int64_T)(int32_T)c1_offset + (int64_T)c1_y;
    if (c1_i4 > 2147483647LL) {
      CV_SATURATION_EVAL(4, 0, 2, 0, 1);
      c1_i4 = 2147483647LL;
    } else {
      if (CV_SATURATION_EVAL(4, 0, 2, 0, c1_i4 < -2147483648LL)) {
        c1_i4 = -2147483648LL;
      }
    }

    c1_i5 = (int64_T)(int32_T)c1_i4 - (int64_T)(int32_T)c1_lectura;
    if (c1_i5 > 2147483647LL) {
      CV_SATURATION_EVAL(4, 0, 3, 0, 1);
      c1_i5 = 2147483647LL;
    } else {
      if (CV_SATURATION_EVAL(4, 0, 3, 0, c1_i5 < -2147483648LL)) {
        c1_i5 = -2147483648LL;
      }
    }

    c1_salida = (int32_T)c1_i5;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -25);
  _SFD_SYMBOL_SCOPE_POP();
  *c1_b_salida = c1_salida;
  *c1_b_salida_anterior = c1_salida_anterior;
  *c1_b_sal_pasos = c1_sal_pasos;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_carmen_controllerMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc1_carmen_controller
  (SFc1_carmen_controllerInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber)
{
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int8_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_carmen_controllerInstanceStruct *chartInstance;
  chartInstance = (SFc1_carmen_controllerInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int8_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 2, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static int8_T c1_emlrt_marshallIn(SFc1_carmen_controllerInstanceStruct
  *chartInstance, const mxArray *c1_sal_pasos, const char_T *c1_identifier)
{
  int8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_sal_pasos),
    &c1_thisId);
  sf_mex_destroy(&c1_sal_pasos);
  return c1_y;
}

static int8_T c1_b_emlrt_marshallIn(SFc1_carmen_controllerInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int8_T c1_y;
  int8_T c1_i6;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i6, 1, 2, 0U, 0, 0U, 0);
  c1_y = c1_i6;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_sal_pasos;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int8_T c1_y;
  SFc1_carmen_controllerInstanceStruct *chartInstance;
  chartInstance = (SFc1_carmen_controllerInstanceStruct *)chartInstanceVoid;
  c1_sal_pasos = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_sal_pasos),
    &c1_thisId);
  sf_mex_destroy(&c1_sal_pasos);
  *(int8_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  uint16_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_carmen_controllerInstanceStruct *chartInstance;
  chartInstance = (SFc1_carmen_controllerInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(uint16_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 5, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static uint16_T c1_c_emlrt_marshallIn(SFc1_carmen_controllerInstanceStruct
  *chartInstance, const mxArray *c1_salida_anterior, const char_T *c1_identifier)
{
  uint16_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_salida_anterior),
    &c1_thisId);
  sf_mex_destroy(&c1_salida_anterior);
  return c1_y;
}

static uint16_T c1_d_emlrt_marshallIn(SFc1_carmen_controllerInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint16_T c1_y;
  uint16_T c1_u0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 5, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_salida_anterior;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  uint16_T c1_y;
  SFc1_carmen_controllerInstanceStruct *chartInstance;
  chartInstance = (SFc1_carmen_controllerInstanceStruct *)chartInstanceVoid;
  c1_salida_anterior = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_salida_anterior),
    &c1_thisId);
  sf_mex_destroy(&c1_salida_anterior);
  *(uint16_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_carmen_controllerInstanceStruct *chartInstance;
  chartInstance = (SFc1_carmen_controllerInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static int32_T c1_e_emlrt_marshallIn(SFc1_carmen_controllerInstanceStruct
  *chartInstance, const mxArray *c1_salida, const char_T *c1_identifier)
{
  int32_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_salida), &c1_thisId);
  sf_mex_destroy(&c1_salida);
  return c1_y;
}

static int32_T c1_f_emlrt_marshallIn(SFc1_carmen_controllerInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i7;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i7, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i7;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_salida;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_carmen_controllerInstanceStruct *chartInstance;
  chartInstance = (SFc1_carmen_controllerInstanceStruct *)chartInstanceVoid;
  c1_salida = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_salida), &c1_thisId);
  sf_mex_destroy(&c1_salida);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_carmen_controllerInstanceStruct *chartInstance;
  chartInstance = (SFc1_carmen_controllerInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_g_emlrt_marshallIn(SFc1_carmen_controllerInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d0, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_nargout;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_carmen_controllerInstanceStruct *chartInstance;
  chartInstance = (SFc1_carmen_controllerInstanceStruct *)chartInstanceVoid;
  c1_nargout = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nargout), &c1_thisId);
  sf_mex_destroy(&c1_nargout);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

const mxArray *sf_c1_carmen_controller_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  sf_mex_assign(&c1_nameCaptureInfo, sf_mex_createstruct("structure", 2, 3, 1),
                FALSE);
  c1_info_helper(&c1_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c1_nameCaptureInfo);
  return c1_nameCaptureInfo;
}

static void c1_info_helper(const mxArray **c1_info)
{
  const mxArray *c1_rhs0 = NULL;
  const mxArray *c1_lhs0 = NULL;
  const mxArray *c1_rhs1 = NULL;
  const mxArray *c1_lhs1 = NULL;
  const mxArray *c1_rhs2 = NULL;
  const mxArray *c1_lhs2 = NULL;
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mtimes"), "name", "name", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("int32"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363713878U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c1_rhs0, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs0, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m!common_checks"),
                  "context", "context", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c1_rhs1, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs1, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m!common_checks"),
                  "context", "context", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("int32"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c1_rhs2, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs2, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs2), "lhs", "lhs", 2);
  sf_mex_destroy(&c1_rhs0);
  sf_mex_destroy(&c1_lhs0);
  sf_mex_destroy(&c1_rhs1);
  sf_mex_destroy(&c1_lhs1);
  sf_mex_destroy(&c1_rhs2);
  sf_mex_destroy(&c1_lhs2);
}

static const mxArray *c1_emlrt_marshallOut(char * c1_u)
{
  const mxArray *c1_y = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c1_u)), FALSE);
  return c1_y;
}

static const mxArray *c1_b_emlrt_marshallOut(uint32_T c1_u)
{
  const mxArray *c1_y = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 7, 0U, 0U, 0U, 0), FALSE);
  return c1_y;
}

static uint8_T c1_h_emlrt_marshallIn(SFc1_carmen_controllerInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_carmen_controller, const
  char_T *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_is_active_c1_carmen_controller), &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_carmen_controller);
  return c1_y;
}

static uint8_T c1_i_emlrt_marshallIn(SFc1_carmen_controllerInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u1;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u1, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u1;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void init_dsm_address_info(SFc1_carmen_controllerInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c1_carmen_controller_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3509287164U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3923898876U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4047166040U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3587472884U);
}

mxArray *sf_c1_carmen_controller_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("unz1HUJPryCm6BmzwAzmgG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(5));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(5));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(4));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(5));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(8));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(5));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(4));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c1_carmen_controller_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c1_carmen_controller_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c1_carmen_controller(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x4'type','srcId','name','auxInfo'{{M[1],M[9],T\"sal_pasos\",},{M[1],M[5],T\"salida\",},{M[1],M[10],T\"salida_anterior\",},{M[8],M[0],T\"is_active_c1_carmen_controller\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 4, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_carmen_controller_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_carmen_controllerInstanceStruct *chartInstance;
    chartInstance = (SFc1_carmen_controllerInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _carmen_controllerMachineNumber_,
           1,
           1,
           1,
           7,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_carmen_controllerMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_carmen_controllerMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _carmen_controllerMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"lectura");
          _SFD_SET_DATA_PROPS(1,1,1,0,"anterior");
          _SFD_SET_DATA_PROPS(2,2,0,1,"salida");
          _SFD_SET_DATA_PROPS(3,2,0,1,"salida_anterior");
          _SFD_SET_DATA_PROPS(4,1,1,0,"pasos");
          _SFD_SET_DATA_PROPS(5,1,1,0,"offset");
          _SFD_SET_DATA_PROPS(6,2,0,1,"sal_pasos");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,5,0,5,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,521);
        _SFD_CV_INIT_EML_SATURATION(0,1,0,184,-1,193);
        _SFD_CV_INIT_EML_SATURATION(0,1,1,272,-1,281);
        _SFD_CV_INIT_EML_SATURATION(0,1,2,465,-1,498);
        _SFD_CV_INIT_EML_SATURATION(0,1,3,465,-1,513);
        _SFD_CV_INIT_EML_SATURATION(0,1,4,480,-1,497);
        _SFD_CV_INIT_EML_IF(0,1,0,126,142,-1,212);
        _SFD_CV_INIT_EML_IF(0,1,1,147,164,-1,208);
        _SFD_CV_INIT_EML_IF(0,1,2,214,230,-1,354);
        _SFD_CV_INIT_EML_IF(0,1,3,235,252,-1,350);
        _SFD_CV_INIT_EML_IF(0,1,4,383,395,444,520);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_INT32,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_INT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_INT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);

        {
          uint16_T *c1_lectura;
          uint16_T *c1_anterior;
          int32_T *c1_salida;
          uint16_T *c1_salida_anterior;
          int8_T *c1_pasos;
          uint16_T *c1_offset;
          int8_T *c1_sal_pasos;
          c1_sal_pasos = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 3);
          c1_offset = (uint16_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c1_pasos = (int8_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c1_salida_anterior = (uint16_T *)ssGetOutputPortSignal
            (chartInstance->S, 2);
          c1_salida = (int32_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c1_anterior = (uint16_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c1_lectura = (uint16_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c1_lectura);
          _SFD_SET_DATA_VALUE_PTR(1U, c1_anterior);
          _SFD_SET_DATA_VALUE_PTR(2U, c1_salida);
          _SFD_SET_DATA_VALUE_PTR(3U, c1_salida_anterior);
          _SFD_SET_DATA_VALUE_PTR(4U, c1_pasos);
          _SFD_SET_DATA_VALUE_PTR(5U, c1_offset);
          _SFD_SET_DATA_VALUE_PTR(6U, c1_sal_pasos);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _carmen_controllerMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "uXn8EVxnTJseuIjMqR01uG";
}

static void sf_opaque_initialize_c1_carmen_controller(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_carmen_controllerInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c1_carmen_controller((SFc1_carmen_controllerInstanceStruct*)
    chartInstanceVar);
  initialize_c1_carmen_controller((SFc1_carmen_controllerInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c1_carmen_controller(void *chartInstanceVar)
{
  enable_c1_carmen_controller((SFc1_carmen_controllerInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c1_carmen_controller(void *chartInstanceVar)
{
  disable_c1_carmen_controller((SFc1_carmen_controllerInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c1_carmen_controller(void *chartInstanceVar)
{
  sf_c1_carmen_controller((SFc1_carmen_controllerInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c1_carmen_controller(SimStruct*
  S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_carmen_controller
    ((SFc1_carmen_controllerInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_carmen_controller();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c1_carmen_controller(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_carmen_controller();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_carmen_controller((SFc1_carmen_controllerInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c1_carmen_controller(SimStruct* S)
{
  return sf_internal_get_sim_state_c1_carmen_controller(S);
}

static void sf_opaque_set_sim_state_c1_carmen_controller(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c1_carmen_controller(S, st);
}

static void sf_opaque_terminate_c1_carmen_controller(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_carmen_controllerInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_carmen_controller_optimization_info();
    }

    finalize_c1_carmen_controller((SFc1_carmen_controllerInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_carmen_controller((SFc1_carmen_controllerInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_carmen_controller(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_carmen_controller((SFc1_carmen_controllerInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_carmen_controller(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_carmen_controller_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,1,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,1);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,4);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,3);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=3; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 4; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1165847282U));
  ssSetChecksum1(S,(2604527090U));
  ssSetChecksum2(S,(1162466130U));
  ssSetChecksum3(S,(411413497U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_carmen_controller(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_carmen_controller(SimStruct *S)
{
  SFc1_carmen_controllerInstanceStruct *chartInstance;
  chartInstance = (SFc1_carmen_controllerInstanceStruct *)utMalloc(sizeof
    (SFc1_carmen_controllerInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_carmen_controllerInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c1_carmen_controller;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c1_carmen_controller;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c1_carmen_controller;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_carmen_controller;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_carmen_controller;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c1_carmen_controller;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c1_carmen_controller;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c1_carmen_controller;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_carmen_controller;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_carmen_controller;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c1_carmen_controller;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c1_carmen_controller_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_carmen_controller(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_carmen_controller(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_carmen_controller(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_carmen_controller_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
