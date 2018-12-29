/**
 * File: lm_eval.c
 * Subroutines for the Levenberg Marqwart Minimization
 *
 * @author  Martin Kuemmel
 * @package lm_eval
 * @version $Revision: 1.2 $
 * @date    $Date: 2010-06-15 09:48:34 $
 */
#include "lmmin.h"
#include "lm_eval.h"
#include <stdio.h>

/*
 * This file contains default implementation of the evaluate and printout
 * routines. In most cases, customization of lmfit can be done by modifying
 * these two routines. Either modify them here, or copy and rename them.
 */

void lm_evaluate_default( double* par, int m_dat, double* fvec,
                          void *data, int *info )
/*
 *	par is an input array. At the end of the minimization, it contains
 *        the approximate solution vector.
 *
 *	m_dat is a positive integer input variable set to the number
 *	  of functions.
 *
 *	fvec is an output array of length m_dat which contains the function
 *        values the square sum of which ought to be minimized.
 *
 *	data is a read-only pointer to lm_data_type, as specified by lmuse.h.
 *
 *      info is an integer output variable. If set to a negative value, the
 *        minimization procedure will stop.
 */
{
    int i;
    lm_data_type *mydata;
    mydata = (lm_data_type*)data;

    for (i=0; i<m_dat; i++)
            fvec[i] = mydata->user_y[i]
                - mydata->user_func( mydata->user_t[i], par);

    *info = *info; /* to prevent a 'unused variable' warning */
    /* if <parameters drifted away> { *info = -1; } */
}

void lm_evaluate_fpar( double* par, int m_dat, double* fvec,
                          void *data, int *info )
/*
 *	par is an input array. At the end of the minimization, it contains
 *        the approximate solution vector.
 *
 *	m_dat is a positive integer input variable set to the number
 *	  of functions.
 *
 *	fvec is an output array of length m_dat which contains the function
 *        values the square sum of which ought to be minimized.
 *
 *	data is a read-only pointer to lm_data_type, as specified by lmuse.h.
 *        for this version of the evaluate function, data contains some fixed
 *        parameters which are passed to the evaluation function
 *
 *      info is an integer output variable. If set to a negative value, the
 *        minimization procedure will stop.
 */
{
  int i;
  lm_data_fpar_type *mydata;
  mydata = (lm_data_fpar_type*)data;

  //fprintf(stderr, "%i 1.: %e, %e, %e: %e\n", m_dat, mydata->fpars[0], mydata->fpars[1],  mydata->fpars[2], par[0]);
  for (i=0; i<m_dat; i++)
    {
      //fprintf(stderr, "do print...%i ", i);
      //fprintf(stderr, "indep: %e ", mydata->user_t[i]);
      //fprintf(stderr, "value: %e, ", mydata->user_y[i]);
      //fprintf(stderr, "func_value: %e \n", mydata->user_func( mydata->user_t[i], par, mydata->fpars));


      fvec[i] = mydata->user_y[i]
	- mydata->user_func( mydata->user_t[i], par, mydata->fpars);

    }
  //fprintf(stderr, "2.: %e, %e, %e: %e\n", mydata->fpars[0], mydata->fpars[1],  mydata->fpars[2], par[0]);
  *info = *info; /* to prevent a 'unused variable' warning */
  /* if <parameters drifted away> { *info = -1; } */
}

void lm_print_default( int n_par, double* par, int m_dat, double* fvec,
                       void *data, int iflag, int iter, int nfev )
/*
 *       data  : for soft control of printout behaviour, add control
 *                 variables to the data struct
 *       iflag : 0 (init) 1 (outer loop) 2(inner loop) -1(terminated)
 *       iter  : outer loop counter
 *       nfev  : number of calls to *evaluate
 */
{
    double f, y, t;
    int i;
    lm_data_type *mydata;
    mydata = (lm_data_type*)data;

    if (iflag==2) {
        printf ("trying step in gradient direction\n");
    } else if (iflag==1) {
        printf ("determining gradient (iteration %d)\n", iter);
    } else if (iflag==0) {
        printf ("starting minimization\n");
    } else if (iflag==-1) {
        printf ("terminated after %d evaluations\n", nfev);
    }

    printf( "  par: " );
    for( i=0; i<n_par; ++i )
        printf( " %12g", par[i] );
    printf ( " => norm: %12g\n", lm_enorm( m_dat, fvec ) );

    if ( iflag == -1 ) {
        printf( "  fitting data as follows:\n" );
        for( i=0; i<m_dat; ++i ) {
            t = (mydata->user_t)[i];
            y = (mydata->user_y)[i];
            f = mydata->user_func( t, par );
            printf( "    t[%2d]=%12g y=%12g fit=%12g residue=%12g\n",
                    i, t, y, f, y-f );
        }
    }
}

void lm_print_nothing( int n_par, double* par, int m_dat, double* fvec,
                       void *data, int iflag, int iter, int nfev )
/*
 *       data  : for soft control of printout behaviour, add control
 *                 variables to the data struct
 *       iflag : 0 (init) 1 (outer loop) 2(inner loop) -1(terminated)
 *       iter  : outer loop counter
 *       nfev  : number of calls to *evaluate
 */
{
    //double f, y, t;
    //int i;
    lm_data_type *mydata;
    mydata = (lm_data_type*)data;

}
