#ifndef YARK_YHOOK_H
#define YARK_YHOOK_H

#include <linux/hashtable.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/kprobes.h>
#include <linux/version.h>
#include <linux/ftrace.h>
#include <linux/string.h>

#pragma GCC optimize("-fno-optimize-sibling-calls")//Preventing the tracked function from being called recursively

/*
symbol_name: Name of the function being hooked
hook_function: Address of the hooking function
orig_function: A pointer to the address of the hooked function
orig_address:  Address of the hooked function
ops:      ftrace info
*/
struct ftrace_hook
{
    const char *symbol_name;
    void *hook_function;
    void **orig_function;

    unsigned long orig_address;
    struct ftrace_ops ops;
};

#define HOOK_FUNCTION_HASH_TABLE_BITS 26

extern DECLARE_HASHTABLE(hook_function_list, HOOK_FUNCTION_HASH_TABLE_BITS);

struct hook_function_info {
    const char * hook_function_name;
    struct ftrace_hook* fhooker;
    struct hlist_node node;
};

typedef asmlinkage long (*t_syscall)(const struct pt_regs *);

int yhook_init(void);
unsigned long lookup_addr_by_name(const char *name);
int hook_function_name_add(const char* fn_name,void *hook_fn,void *orig_fn);
int hook_function_del(const char* fn_name);
void hook_sys_call_table(long int sysno, t_syscall hook_fn, t_syscall* orig_fn);
void unhook_sys_call_table(long int sysno, t_syscall orig_fn);

#endif
