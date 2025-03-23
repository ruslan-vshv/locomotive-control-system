Locomotive Control System
=========================
Logger core module
----
Provides logging method with two parameters:  
`event` - text of the event;  
`type` - one of three types of events _error_, _warning_, _info_;  
```
log_event("Event text", "info");
```
Logs events into _.log_ files inside `logs\` directory with following naming format:  
_locomotiveYYYY-MM-DD.log_;

Translator core module
----
Provides translation method with one parameter:  
`string` - text string to be translated;  
Returns translated to current language string or original string if no translation found for provided 
string
```
t("String to be translated");
```
Current language is stored in global variable after `select_language()` method run, this method
shows UI for selecting language, list of languages generates on runtime based on _.txt_ files inside
`translation\` folder (Names of files are names of languages) so adding new languages is possible without
changing or compiling code base.

User interface core module
----
Main module to handle user interface