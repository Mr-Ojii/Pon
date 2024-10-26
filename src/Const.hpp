#pragma once

#define PONSTR(s) PONXSTR(s)
#define PONXSTR(s) #s
#define APP_NAME Pon

constexpr const char* app_name = PONSTR(APP_NAME);