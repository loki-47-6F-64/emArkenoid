/* 
 * File:   Aemssert.h
 * Author: Loki
 *
 * Created on 07 March 2013, 18:54
 */

#ifndef ASSERT_H
#define	ASSERT_H

#ifdef _DEBUG
extern void AssertFailed( const char *file, int line, const char *expression );

#define assert( x ) if ( x ) { } else AssertFailed( __FILE__, __LINE__, #x )
#else
#define assert( x )
#endif

#endif	/* ASSERT_H */

