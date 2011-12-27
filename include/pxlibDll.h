/* Copyright (c) 2011 Chris Westin.  All Rights Reserved. */
/*
  NAME
    pxlibDll.h - Doubly-linked lists

  SOURCE
    phoenix4c - https://github.com/cwestin/phoenix4c

  LICENSE
    See ../LICENSE.txt.

  NOTES
    The membership structure is embedded in a client data structure that is to
    belong to a doubly-linked list.  Operations are then performed on the
    member structures and head of the list.  The head of the list doubles as a
    sentinel on the list.
 */

#pragma once

#ifndef PXLIBDLL_H
#define PXLIBDLL_H

#ifndef PX_STDDEF_H
#include <stddef.h>
#define PX_STDDEF_H
#endif


/*
  Intrusive Doubly Linked List

  Embed this member structure inside structures that are to be members of
  a linked list.

  The members data is considered private, and will be maintained by the
  list implementation.  idll structures must always be initialized with
  idllInit().

  This structure is also used as the head of a list, and when used as such,
  must also be initialized with idllInit().

  IMPLEMENTATION NOTES
  The head of a list also functions as a sentinel:  the last element of the
  list points back to the head, and this is used to detect the end of the
  list.  This simplifies the insertion and removal operations on the list,
  and eliminates tests for handling empty lists.

  The implementation is simple enough and stable enough to be inlined, so it
  is provided as a set of preprocessor macros.
*/
typedef struct pxlibDllMember
{
    struct pxlibDllMember *pNext;
    struct pxlibDllMember *pPrevious;
} pxlibDllMember, pxlibDllList;


/*
  Given a pointer to a member known to be inside a structure, recover a pointer
  to the original containing structure.

  @param pMember pointer to a member
  @param s structure type name
  @param n member type name
  @returns pointer to an s
*/
#define pxlibDllGetMember(pMember, s, n) ((s *)(((char *)(pMember)) - offsetof(s, n)))

/*
  Initialize a list member.

  @param pointer to a member
*/
#define pxlibDllMemberInit(pMember) ((pMember)->pNext = (pMember), (pMember)->pPrevious = (pMember))

/*
  Add a new link after a specified position.

  Adding the new link after a list head prepends it to the list.

  @param pNew the new link to be added
  @param pPos the position after which to add the new link
*/
#define pxlibDllAddAfter(pNew, pPos) ( \
    (pNew)->pPrevious = (pPos), \
    (pNew)->pNext = (pPos)->pNext, \
    (pPos)->pNext->pPrevious = (pNew), \
    (pPos)->pNext = (pNew) \
    )


/*
  Add a new link before a specified position.

  Adding the new link before a list head appends it to the list.

  @param pNew the new link to be added
  @param pPos the position after which to add the new link
*/
#define pxlibDllAddBefore(pNew, pPos) ( \
    (pNew)->pNext = (pPos), \
    (pNew)->pPrevious = (pPos)->pPrevious, \
    (pPos)->pPrevious->pNext = (pNew), \
    (pPos)->pPrevious = (pNew) \
    )

/*
  Remove a link from a list.

  Removing the list head will cause problems; do not remove it.

  @param pMember pointer to a list link
*/
#define pxlibDllRemove(pMember) ( \
    (pMember)->pPrevious->pNext = (pMember)->pNext, \
    (pMember)->pNext->pPrevious = (pMember)->pPrevious \
    )


/*
  Initialize a list.

  @param pointer to a member
*/
#define pxlibDllListInit(pList) pxlibDllMemberInit(pList)

/*
  Return the member in the list after a specified member.

  @param pList pointer to the list head
  @param pMember pointer to a member
  @returns pointer to the member after pMember on the list or NULL if pMember
    is the last member
*/
#define pxlibDllNext(pList, pMember) ((pMember)->pNext == (pList) ? NULL : (pMember)->pNext)

/*
  Return the member in the list before a specified member.

  @param pList pointer to the list head
  @param pMember pointer to a member
  @returns pointer to the member before pMember on the list or NULL if pMember
    is the first member
*/
#define pxlibDllPrev(pList, pMember) ((pMember)->pPrevious == (pList) ? NULL : (pMember)->pPrevious)

/*
  Return the first member on the list.

  @param pList pointer to the list head
  @returns the first member in the list, or NULL if the list is empty
*/
#define pxlibDllFirst(pList) pxlibDllNext(pList, pList)

/*
  Return the last member on the list.

  @param pList pointer to the list head
  @returns the last member in the list, or NULL if the list is empty
*/
#define pxlibDllLast(pList) pxlibDllPrev(pList, pList)

/*
  Append a new member to a list.

  @param pNew pointer to the new member
  @param pList pointer to the head of the list
*/
#define pxlibDllAppend(pList, pNew) pxlibDllAddBefore(pNew, pList)

/*
  Prepend a new member to a list.

  @param pNew pointer to the new membership
  @param pList pointer to the head of the list
*/
#define pxlibDllPrepend(pList, pNew) pxlibDllAddAfter(pNew, pList)

#endif /* PXLIBDLL_H */
