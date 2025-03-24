# Locomotive Control System

## Core components

### _Logger_ core component

Provides logging method with two parameters:  
`event` - text of the event;  
`type` - one of three types of events _error_, _warning_, _info_;  
```c++
log_event("Event text", "info");
```
Logs events into _.log_ files inside `logs\` directory with following naming format:  
_locomotiveYYYY-MM-DD.log_;

### _Translator_ core component

Provides translation method with one parameter:  
`string` - text string to be translated;  
Returns translated to current language string or original string if no translation found for provided 
string
```c++
t("String to be translated");
```
Current language is stored in global variable after `select_language()` method run, this method
shows UI for selecting language, list of languages generates on runtime based on _.txt_ files inside
`translation\` folder (Names of files are names of languages) so adding new languages is possible without
changing or compiling code base.

### _User interface_ core component

Main module to handle user interface

### _Modules menu_ core component

Contains logic related to modules actions menu building.  
Provides module action registeration method `register_menu_item` with one parameter:  
`menu_item` - menu item struct with action name and action method; (`{"Action name", action_method_name}`)
```c++
register_menu_item((MenuItem){t("Action name"), action_method_name});
```

## Modules development

All modules should #include `module.h` and call register_module method in constructor for 
auto initialization. `register_module` method accepts 1 parameter:
`module` - module struct with module name and module init method; (`{"Module name", init_method_name}`)
```c++
register_module((Module){ "Module name", init_method_name });
```
Autoloader call all modules init methods after user select language (So it's possible to use translator in module)
