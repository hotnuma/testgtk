#ifndef PREFERENCES_H
#define PREFERENCES_H

#include "config.h"
#include <cstring.h>

typedef struct
{
    CString *filepath;
    int window_width;
    int window_height;
    int window_maximized;

} Preferences;

Preferences* get_preferences();
void prefs_cleanup();

Preferences* prefs_file_read();
void prefs_write();

#endif // PREFERENCES_H


