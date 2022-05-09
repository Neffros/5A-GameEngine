
#ifdef DllExport
#define DllEngine  __declspec(dllexport)
#else
#define DllEngine  __declspec(dllimport)
#endif
