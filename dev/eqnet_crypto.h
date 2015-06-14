
#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#define IMPORT __declspec(dllimport)
#else
#define IMPORT extern
#endif

IMPORT unsigned char* EQNet_Encrypt(const void* msg, size_t* len);
IMPORT unsigned char* EQNet_Decrypt(const void* msg, size_t* len);
IMPORT void EQNet_Free(void* ptr);

#ifdef __cplusplus
}
#endif
