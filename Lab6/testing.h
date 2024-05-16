#ifndef __TESTING_H
#define __TESTING_H

typedef void* (*ctor_t)(void);
typedef void  (*dtor_t)(void*);

typedef void (*operation_t)(void*, const int);

bool TestTree(const int from, const int to, const int step,
             const char* src_path, const char* dest_path, const char* name,
             ctor_t ctor, dtor_t dtor, operation_t insert, operation_t remove);

#endif
