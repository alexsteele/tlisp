
#include "gc.h"
#include "process.h"
#include <stdlib.h>
#include <string.h>

static char ALIVE = 1;

static
void gc_mark(env_t *env, tlisp_obj_t *obj)
{
    if (obj->mark == ALIVE) 
        return;

    env->proc->nalive++;
    obj->mark = ALIVE;
    switch (obj->tag) {
    case BOOL:
    case NUM:
    case STRING:
    case NFUNC:
    case NIL:
    case SYMBOL:
        return;
    case LAMBDA:
    case MACRO:
        
        // In lambda and macro's case, assume symbols and forms
        // were allocated by the reader outside the context
        // of the process.
        return;
    case CONS:
        gc_mark(env, obj->car);
        while ((obj = obj->cdr)) {
            obj->mark = ALIVE;
            env->proc->nalive++;
            gc_mark(env, obj->car);
        }
        return;
    }
}

static
void free_obj(tlisp_obj_t *obj)
{
    switch (obj->tag) {
    case BOOL:
    case NUM:
    case NFUNC:
    case NIL:
    case LAMBDA:
    case MACRO:
    case CONS:
        return;
    case STRING:
        free(obj->str);
        return;
    case SYMBOL:
        free(obj->sym);
        return;
    }
}

static
void heap_shrink(process_t *proc)
{
    tlisp_obj_t *heap;
    int len = 0;
    int i;

    proc->heap_cap = proc->nalive * 2;
    heap = malloc(sizeof(tlisp_obj_t) * proc->heap_cap);
    for (i = 0; i < proc->heap_len; i++) {
        if (proc->heap[i].mark == ALIVE) {
            memcpy(heap + len, proc->heap + i, sizeof(tlisp_obj_t));
            len += 1;
        } else {
            free_obj(proc->heap + i);
        }
    }
    free(proc->heap);
    proc->heap = heap;
    proc->heap_len = len;
}

void gc(env_t *env)
{
    process_t *proc = env->proc;

    proc->nalive = 0;
    env_for_each(env, gc_mark);
    if (proc->nalive < (proc->heap_len / 4) &&
        (proc->nalive * sizeof(tlisp_obj_t) * 2) >= MIN_HEAP_SIZE) {
        
        heap_shrink(proc);
    }
    ALIVE = ALIVE == 1 ? 2 : 1;
}
