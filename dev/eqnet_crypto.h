
#define EXPORT extern "C" __declspec(dllexport)

EXPORT unsigned char* EQNet_Encrypt(const void* msg, size_t* len);
EXPORT unsigned char* EQNet_Decrypt(const void* msg, size_t* len);
EXPORT void EQNet_Free(void* ptr);
