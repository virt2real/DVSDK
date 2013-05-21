/*
    DM Digital Still Camera Evaluation Software
    (c) Texas Instruments 2005
*/

#ifndef _CACHE_H_
#define _CACHE_H_



typedef unsigned long   CACHE_Addr_t ;
typedef unsigned long   CACHE_Size_t ;


typedef void (*CACHE_Cb)(CACHE_Addr_t addr, CACHE_Size_t size);

/**
  \brief  CACHE_init parameter structure
*/
typedef struct {

    CACHE_Cb wbCb;     ///< Callback for D-cache write back API
    CACHE_Cb invCb;    ///< Callback for D-cache invalidate API
    CACHE_Cb wbInvCb;  ///< Callback for D-cache write back and invalidate API

} CACHE_InitPrm_t;

/**
  \brief Initialize callbacks to write back invalidate D-cache

  \param  pPrm  Callbacks structure
*/
void CACHE_init(CACHE_InitPrm_t *pPrm);

/**
  \brief Write back data from cache

  \param  addr    buffer address
  \param  size    size of buffer
*/
void CACHE_writeBack(CACHE_Addr_t addr, CACHE_Size_t size);

/**
  \brief Invalidate data from cache

  \param  addr    buffer address
  \param  size    size of buffer
*/
void CACHE_invalidate(CACHE_Addr_t addr, CACHE_Size_t size);

/**
  \brief Write back and invalidate data from cache

  \param  addr    buffer address
  \param  size    size of buffer
*/
void CACHE_wbInv(CACHE_Addr_t addr, CACHE_Size_t size);


#endif /* _CACHE_H_  */

/*@}*/
