// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
// 
// release       :
// release_date  :
// 
// file          : include/CGAL/Arithmetic_filter/predicates/Regular_triangulation_ftC2.h
// package       : Interval_arithmetic
// author(s)     : Sylvain Pion <Sylvain.Pion@sophia.inria.fr>
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec@sophia.inria.fr>)
// ======================================================================

// This file is automatically generated by the script
// examples/Interval_arithmetic/filtered_predicate_converter.

#ifndef CGAL_ARITHMETIC_FILTER_REGULAR_TRIANGULATION_FTC2_H
#define CGAL_ARITHMETIC_FILTER_REGULAR_TRIANGULATION_FTC2_H

// This file contains the low level cartesian predicates
// used by the 2D regular triangulation.

CGAL_BEGIN_NAMESPACE

#ifndef CGAL_CFG_NO_EXPLICIT_TEMPLATE_FUNCTION_ARGUMENT_SPECIFICATION
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#endif
Oriented_side
power_testC2( 
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &px, 
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &py, 
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pwt,
              
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qx, 
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qy, 
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qwt,
              
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &rx, 
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &ry, 
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &rwt,
              
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &tx, 
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &ty, 
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &twt)
{
  CGAL::FPU_CW_t backup = CGAL::FPU_get_and_set_cw(CGAL::FPU_cw_up);
  try
  {
    Oriented_side result = power_testC2(
		px.interval(),
		py.interval(),
		pwt.interval(),
		qx.interval(),
		qy.interval(),
		qwt.interval(),
		rx.interval(),
		ry.interval(),
		rwt.interval(),
		tx.interval(),
		ty.interval(),
		twt.interval());
    CGAL::FPU_set_cw(backup);
    return result;
  } 
  catch (CGAL::Interval_nt_advanced::unsafe_comparison)
  {
    CGAL::FPU_set_cw(backup);
    return power_testC2(
		px.exact(),
		py.exact(),
		pwt.exact(),
		qx.exact(),
		qy.exact(),
		qwt.exact(),
		rx.exact(),
		ry.exact(),
		rwt.exact(),
		tx.exact(),
		ty.exact(),
		twt.exact());
  }
}


#ifndef CGAL_CFG_NO_EXPLICIT_TEMPLATE_FUNCTION_ARGUMENT_SPECIFICATION
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#endif
Oriented_side
power_testC2( 
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &px, 
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &py, 
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &pwt,
	      
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qx, 
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qy, 
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &qwt,
	      
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &tx, 
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &ty, 
    const CGAL::Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, CGAL_IA_CACHE> &twt)
{
  CGAL::FPU_CW_t backup = CGAL::FPU_get_and_set_cw(CGAL::FPU_cw_up);
  try
  {
    Oriented_side result = power_testC2(
		px.interval(),
		py.interval(),
		pwt.interval(),
		qx.interval(),
		qy.interval(),
		qwt.interval(),
		tx.interval(),
		ty.interval(),
		twt.interval());
    CGAL::FPU_set_cw(backup);
    return result;
  } 
  catch (CGAL::Interval_nt_advanced::unsafe_comparison)
  {
    CGAL::FPU_set_cw(backup);
    return power_testC2(
		px.exact(),
		py.exact(),
		pwt.exact(),
		qx.exact(),
		qy.exact(),
		qwt.exact(),
		tx.exact(),
		ty.exact(),
		twt.exact());
  }
}

CGAL_END_NAMESPACE

#ifdef CGAL_ARITHMETIC_FILTER_H
#ifndef CGAL_ARITHMETIC_FILTER_REGULAR_TRIANGULATION_FTC2_H
#include <CGAL/Arithmetic_filter/predicates/Regular_triangulation_ftC2.h>
#endif // CGAL_ARITHMETIC_FILTER_REGULAR_TRIANGULATION_FTC2_H
#endif

#endif // CGAL_ARITHMETIC_FILTER_REGULAR_TRIANGULATION_FTC2_H
