#define ShowMessages 1 // 0 or 1

#include <iostream>
using std::cout;
using std::endl;

#if ShowMessages
#define MSG(msg) cout << msg << endl;
#else
#define MSG(msg);
#endif