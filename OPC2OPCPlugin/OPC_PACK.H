// OPCTHRD.h
//
// This file contains function prototyles
// for the OPC Pack/Unpack functions for use with IDataObject
//
//
//	(C) COPYRIGHT 1997 INTELLUTION INC.
// ALL RIGHTS RESERVED
//
// Original Author: Al Chisholm
//
// Modification Log:
//	Vers    Date   By    Notes
//	----  -------- ---   -----
//  2.00  05/01/97 acc   
//

#include "stdafx.h"
int		OPCVariantSize( VARIANT * v);
int		OPCVariantPack( char * t, VARIANT *s);
void	OPCVariantUnpack( VARIANT *vp, char * src);


