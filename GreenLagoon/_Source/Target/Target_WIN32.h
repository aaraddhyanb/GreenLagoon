#ifndef __WIN32_H
#define __WIN32_H
#define CACHE_LINE_SIZE 16
#define CACHE_ALIGN __declspec(align(CACHE_LINE_SIZE))
#endif