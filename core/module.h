#ifndef MODULE_H
#define MODULE_H

typedef void (*module_init_func)();

typedef struct {
    const char *name;
    module_init_func init;
} Module;

// Registration function
void register_module(Module module);

#endif // MODULE_H
