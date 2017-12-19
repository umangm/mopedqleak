/*****************************************************************************/
/* Internal functions and data structures of the WPDS library.		     */

#ifndef WPDSINT_H
#define WPDSINT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "int.h"

/***************************************************************************
                DATA STRUCTURES
 ***************************************************************************/

/***************************************************************************
 Generic hash table:

 These structures are used to implement a hash table. The hash table is
 generic in the sense that the hashed elements can be any C struct, provided
 that the first two fields in the struct are compatible with the wStub struct.
 The size of the hash table will grow automatically as more elements are
 inserted, but will not shrink if elements are removed.
*/ 

#define wHashElement void

typedef struct wStub
{
	struct wStub *next;
	unsigned long hash;
} wStub;

typedef struct wHash
{
	wStub** buckets;
	int min_buckets;
	int num_buckets;
	int num_entries;
	int mask;
	int (*cmp)(wHashElement*,wHashElement*);
} wHash;

#define WHASH_MIN 256

/* Create a new hash table. Initially, the table has WHASH_MIN buckets. The
   table will grow automatically if the fill rate exceeds a certain ratio.
   wHashCreate takes a pointer to a user-supplied function as its argument.
   The function is expected to compare two hash elements and to return -1,0,1
   if the elements are smaller, equal, larger to each other. This function is
   used by whash_find_element and whash_insert_element to determine the
   correct position of elements. */
extern wHash* wHashCreate (int(*)(wHashElement*,wHashElement*));

/* Delete the table, i.e. free its memory. The function pointer will be
   called on every entry in the hash and is expected to release the memory
   associated with it. */
extern void wHashDelete (wHash*,void(*)(wHashElement*));

/* Insert an element into the table. If the element is already present in 
   the table, returns the pointer to the corresponding entry in the table.
   If the element is indeed new, return the element. The element is expected
   to carry its hash value in the 'hash' field of its struct. */
extern wHashElement* wHashInsert (wHash*, wHashElement*);

/* Find an element (return NULL if not present). */
extern wHashElement* wHashFind (wHash*, wHashElement*);

/* Remove an element from the hash. The element itself is not changed. */
extern void wHashRemove (wHash*, wHashElement*);

/***************************************************************************/
/* Identifier hash table:						   */

extern char **wident_array;		/* maps integers to strings */

typedef struct wIdentCell		/* identifier hash entry */
{
	struct wIdentCell *next;	/* next and hash needed by hash.c */
	unsigned long hash;
	wIdent ident;
} wIdentCell;

/* Return an identifier associated with the given string. Calling the function
   twice with the same argument will produce the same identifier. The function
   calls strdup() on the argument, which means that the user can release the
   string afterwards without causing harm. */
extern wIdent wIdentCreate (char*);

/* Map an identifier to its string (the reverse of wIdentCreate). */
extern char* wIdentString (wIdent);

/* Sets up the hash. This function must be called before the first call
   to wident_create (this is done by wInit()). */
extern void wIdentInit ();			

/* Releases the memory used by the hash. Should be called after the last
   use of wIdentCreate or wIdentString (done by wFinish()). */
extern void wIdentFinish ();

#endif
