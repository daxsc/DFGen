#pragma once

// Define EXPORTED for any platform
#if defined _WIN32 || defined __CYGWIN__
#ifdef WIN_EXPORT
#ifdef __GNUC__
#define EXPORTED __attribute__((visibility("default")))
#else
#define EXPORTED __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
#endif
#else
#ifdef __GNUC__
#define EXPORTED // Apparently no equivalent for GCC
#else
#define EXPORTED __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
#endif
#endif
#endif

extern "C" {
	EXPORTED char* noise(int argc, char* argv[]);
	EXPORTED void del_memory(int argc, char* argv[]);
}