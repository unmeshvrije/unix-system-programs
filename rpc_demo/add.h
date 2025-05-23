/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _ADD_H_RPCGEN
#define _ADD_H_RPCGEN

#define RPCGEN_VERSION	199506

#include <rpc/rpc.h>


struct intpair {
	int a;
	int b;
};
typedef struct intpair intpair;
#ifdef __cplusplus
extern "C" bool_t xdr_intpair(XDR *, intpair*);
#elif __STDC__
extern  bool_t xdr_intpair(XDR *, intpair*);
#else /* Old Style C */
bool_t xdr_intpair();
#endif /* Old Style C */


#define ADD_PROG ((rpc_uint)0x31234567)
#define ADD_VERS ((rpc_uint)1)

#ifdef __cplusplus
#define ADD ((rpc_uint)1)
extern "C" int * add_1(intpair *, CLIENT *);
extern "C" int * add_1_svc(intpair *, struct svc_req *);

#elif __STDC__
#define ADD ((rpc_uint)1)
extern  int * add_1(intpair *, CLIENT *);
extern  int * add_1_svc(intpair *, struct svc_req *);

#else /* Old Style C */
#define ADD ((rpc_uint)1)
extern  int * add_1();
extern  int * add_1_svc();
#endif /* Old Style C */

#endif /* !_ADD_H_RPCGEN */
