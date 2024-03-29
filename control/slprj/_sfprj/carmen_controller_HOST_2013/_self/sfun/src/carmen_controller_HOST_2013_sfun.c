/* Include files */

#include "carmen_controller_HOST_2013_sfun.h"
#include "carmen_controller_HOST_2013_sfun_debug_macros.h"
#include "c1_carmen_controller_HOST_2013.h"
#include "c2_carmen_controller_HOST_2013.h"
#include "c3_carmen_controller_HOST_2013.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _carmen_controller_HOST_2013MachineNumber_;
real_T _sfTime_;

/* Function Declarations */

/* Function Definitions */
void carmen_controller_HOST_2013_initializer(void)
{
}

void carmen_controller_HOST_2013_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_carmen_controller_HOST_2013_method_dispatcher(SimStruct
  *simstructPtr, unsigned int chartFileNumber, const char* specsCksum, int_T
  method, void *data)
{
  if (chartFileNumber==1) {
    c1_carmen_controller_HOST_2013_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==2) {
    c2_carmen_controller_HOST_2013_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==3) {
    c3_carmen_controller_HOST_2013_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_carmen_controller_HOST_2013_process_check_sum_call( int nlhs,
  mxArray * plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[20];
  if (nrhs<1 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the checksum */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"sf_get_check_sum"))
    return 0;
  plhs[0] = mxCreateDoubleMatrix( 1,4,mxREAL);
  if (nrhs>1 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if (!strcmp(commandName,"machine")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3473110075U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(926123048U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3694925389U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3212804772U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(24707525U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(46025064U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2769075556U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1161633378U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 1:
        {
          extern void sf_c1_carmen_controller_HOST_2013_get_check_sum(mxArray
            *plhs[]);
          sf_c1_carmen_controller_HOST_2013_get_check_sum(plhs);
          break;
        }

       case 2:
        {
          extern void sf_c2_carmen_controller_HOST_2013_get_check_sum(mxArray
            *plhs[]);
          sf_c2_carmen_controller_HOST_2013_get_check_sum(plhs);
          break;
        }

       case 3:
        {
          extern void sf_c3_carmen_controller_HOST_2013_get_check_sum(mxArray
            *plhs[]);
          sf_c3_carmen_controller_HOST_2013_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3031367619U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4001028638U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3978939492U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(838979348U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4270046400U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3975771662U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4032990324U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(82360226U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_carmen_controller_HOST_2013_autoinheritance_info( int nlhs,
  mxArray * plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char aiChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;
  mxGetString(prhs[2], aiChksum,sizeof(aiChksum)/sizeof(char));
  aiChksum[(sizeof(aiChksum)/sizeof(char)-1)] = '\0';

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(aiChksum, "KYBli7Lbins55yvqp1RsW") == 0) {
          extern mxArray
            *sf_c1_carmen_controller_HOST_2013_get_autoinheritance_info(void);
          plhs[0] = sf_c1_carmen_controller_HOST_2013_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 2:
      {
        if (strcmp(aiChksum, "M5OSWmToAXRaFPKmG3MnHG") == 0) {
          extern mxArray
            *sf_c2_carmen_controller_HOST_2013_get_autoinheritance_info(void);
          plhs[0] = sf_c2_carmen_controller_HOST_2013_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 3:
      {
        if (strcmp(aiChksum, "J4Yc8jmJlIouUccFUoTWwH") == 0) {
          extern mxArray
            *sf_c3_carmen_controller_HOST_2013_get_autoinheritance_info(void);
          plhs[0] = sf_c3_carmen_controller_HOST_2013_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_carmen_controller_HOST_2013_get_eml_resolved_functions_info( int
  nlhs, mxArray * plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[64];
  if (nrhs<2 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the get_eml_resolved_functions_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_eml_resolved_functions_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        extern const mxArray
          *sf_c1_carmen_controller_HOST_2013_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c1_carmen_controller_HOST_2013_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 2:
      {
        extern const mxArray
          *sf_c2_carmen_controller_HOST_2013_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_carmen_controller_HOST_2013_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 3:
      {
        extern const mxArray
          *sf_c3_carmen_controller_HOST_2013_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c3_carmen_controller_HOST_2013_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_carmen_controller_HOST_2013_third_party_uses_info( int nlhs,
  mxArray * plhs[], int nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the third_party_uses_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_third_party_uses_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "Df28XUDDuoqdi5KuEIzyZF") == 0) {
          extern mxArray
            *sf_c1_carmen_controller_HOST_2013_third_party_uses_info(void);
          plhs[0] = sf_c1_carmen_controller_HOST_2013_third_party_uses_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "EfuuzEvuIIpStXN9eNlGXD") == 0) {
          extern mxArray
            *sf_c2_carmen_controller_HOST_2013_third_party_uses_info(void);
          plhs[0] = sf_c2_carmen_controller_HOST_2013_third_party_uses_info();
          break;
        }
      }

     case 3:
      {
        if (strcmp(tpChksum, "F0VfkFdexTsqvEqAFIGUlG") == 0) {
          extern mxArray
            *sf_c3_carmen_controller_HOST_2013_third_party_uses_info(void);
          plhs[0] = sf_c3_carmen_controller_HOST_2013_third_party_uses_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

unsigned int sf_carmen_controller_HOST_2013_updateBuildInfo_args_info( int nlhs,
  mxArray * plhs[], int nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the updateBuildInfo_args_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_updateBuildInfo_args_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "Df28XUDDuoqdi5KuEIzyZF") == 0) {
          extern mxArray
            *sf_c1_carmen_controller_HOST_2013_updateBuildInfo_args_info(void);
          plhs[0] = sf_c1_carmen_controller_HOST_2013_updateBuildInfo_args_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "EfuuzEvuIIpStXN9eNlGXD") == 0) {
          extern mxArray
            *sf_c2_carmen_controller_HOST_2013_updateBuildInfo_args_info(void);
          plhs[0] = sf_c2_carmen_controller_HOST_2013_updateBuildInfo_args_info();
          break;
        }
      }

     case 3:
      {
        if (strcmp(tpChksum, "F0VfkFdexTsqvEqAFIGUlG") == 0) {
          extern mxArray
            *sf_c3_carmen_controller_HOST_2013_updateBuildInfo_args_info(void);
          plhs[0] = sf_c3_carmen_controller_HOST_2013_updateBuildInfo_args_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

void carmen_controller_HOST_2013_debug_initialize(struct SfDebugInstanceStruct*
  debugInstance)
{
  _carmen_controller_HOST_2013MachineNumber_ = sf_debug_initialize_machine
    (debugInstance,"carmen_controller_HOST_2013","sfun",0,3,0,0,0);
  sf_debug_set_machine_event_thresholds(debugInstance,
    _carmen_controller_HOST_2013MachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(debugInstance,
    _carmen_controller_HOST_2013MachineNumber_,0);
}

void carmen_controller_HOST_2013_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_carmen_controller_HOST_2013_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info(
      "carmen_controller_HOST_2013", "carmen_controller_HOST_2013");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_carmen_controller_HOST_2013_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
