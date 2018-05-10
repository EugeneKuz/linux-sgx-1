#include "ippcp.h"

#define IPPFUN(type,name,arg) extern type IPP_STDCALL name arg

#ifndef NULL
#ifdef  __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#if defined (_M_AMD64) || defined (__x86_64__)

#define AVX3X_FEATURES ( ippCPUID_AVX512F|ippCPUID_AVX512CD|ippCPUID_AVX512VL|ippCPUID_AVX512BW|ippCPUID_AVX512DQ )
#define AVX3M_FEATURES ( ippCPUID_AVX512F|ippCPUID_AVX512CD|ippCPUID_AVX512PF|ippCPUID_AVX512ER )


IPPAPI(IppStatus, y8_ippsHashMessage_rmf,(const Ipp8u* pMsg, int len, Ipp8u* pMD, const IppsHashMethod* pMethod))
IPPAPI(IppStatus, l9_ippsHashMessage_rmf,(const Ipp8u* pMsg, int len, Ipp8u* pMD, const IppsHashMethod* pMethod))

IPPFUN(IppStatus,sgx_disp_ippsHashMessage_rmf,(const Ipp8u* pMsg, int len, Ipp8u* pMD, const IppsHashMethod* pMethod))
{
  Ipp64u features;
  ippcpGetCpuFeatures( &features );

      if( ippCPUID_AVX2  == ( features & ippCPUID_AVX2  )) { /* HasweLl ia32=H9, x64=L9 */
        return l9_ippsHashMessage_rmf( pMsg, len, pMD, pMethod );
      } else 
      if( ippCPUID_SSE42 == ( features & ippCPUID_SSE42 )) { /* Nehalem or Westmer = PenrYn + SSE42 + ?CLMUL + ?AES + ?SHA */
        return y8_ippsHashMessage_rmf( pMsg, len, pMD, pMethod );
      } else 
        return ippStsCpuNotSupportedErr;
}
#else


IPPAPI(IppStatus, p8_ippsHashMessage_rmf,(const Ipp8u* pMsg, int len, Ipp8u* pMD, const IppsHashMethod* pMethod))
IPPAPI(IppStatus, h9_ippsHashMessage_rmf,(const Ipp8u* pMsg, int len, Ipp8u* pMD, const IppsHashMethod* pMethod))

IPPFUN(IppStatus,sgx_disp_ippsHashMessage_rmf,(const Ipp8u* pMsg, int len, Ipp8u* pMD, const IppsHashMethod* pMethod))
{
  Ipp64u features;
  ippcpGetCpuFeatures( &features );

      if( ippCPUID_AVX2  == ( features & ippCPUID_AVX2  )) { /* HasweLl ia32=H9, x64=L9 */
        return h9_ippsHashMessage_rmf( pMsg, len, pMD, pMethod );
      } else 
      if( ippCPUID_SSE42 == ( features & ippCPUID_SSE42 )) { /* Nehalem or Westmer = PenrYn + SSE42 + ?CLMUL + ?AES + ?SHA */
        return p8_ippsHashMessage_rmf( pMsg, len, pMD, pMethod );
      } else 
        return ippStsCpuNotSupportedErr;
}
#endif