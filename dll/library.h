#ifndef INC_5A_GAMEENGINE_LIBRARY_H
#define INC_5A_GAMEENGINE_LIBRARY_H

#ifdef DllExport
#define DllEngine extern "C" __declspec(dllexport)
#else
#define DllEngine extern "C" __declspec(dllimport)
#endif


DllEngine void hello();

#endif //INC_5A_GAMEENGINE_LIBRARY_H
