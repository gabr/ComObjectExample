#include <stdio.h>
#include <windows.h>
#include <objbase.h>
#include <INITGUID.H>

#define BUFFER_LEN 80

// GUID Generator: C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\Tools\guidgen.exe

// for IExample
// {86461787-A54D-42A6-A126-4310B476B3DE}
DEFINE_GUID(CLSID_IExample, 0x86461787, 0xa54d, 0x42a6, 0xa1, 0x26, 0x43, 0x10, 0xb4, 0x76, 0xb3, 0xde);

// for IExampleVtbl
// {08C8DC7A-ED70-4FC1-BDF4-F0F930FBAD63}
DEFINE_GUID(IID_IExample, 0x8c8dc7a, 0xed70, 0x4fc1, 0xbd, 0xf4, 0xf0, 0xf9, 0x30, 0xfb, 0xad, 0x63);


typedef struct iExample IExample;
typedef HRESULT STDMETHODCALLTYPE QueryInterfacePtr(IExample *, REFIID, void **);
typedef ULONG STDMETHODCALLTYPE AddRefPtr(IExample *);
typedef ULONG STDMETHODCALLTYPE ReleasePtr(IExample *);

typedef HRESULT STDMETHODCALLTYPE SetStringPtr(IExample *, char *);
typedef HRESULT STDMETHODCALLTYPE GetStringPtr(IExample *, char *, long);

typedef struct iExampleVtbl
{
  // first 3 members must be call QueryInterface, AddRef, and Release
  QueryInterfacePtr *QueryInterface;
  AddRefPtr         *AddRef;
  ReleasePtr        *Release;
  SetStringPtr      *SetString;
  GetStringPtr      *GetString;
} IExampleVtbl;

typedef struct iExample
{
  // first pointer has to be pointer to VTable
  IExampleVtbl *lpVtbl;
  DWORD         count;
  char          buffer[BUFFER_LEN];
} IExample;

HRESULT STDMETHODCALLTYPE SetString(IExample *this, char *str)
{
  DWORD i;

  i = lstrlen(str);
  if (i > BUFFER_LEN - 1) i = BUFFER_LEN - 1;
  CopyMemory(this->buffer, str, i);
  this->buffer[i] = 0;

  return 0;
}

HRESULT STDMETHODCALLTYPE GetString(IExample *this, char *buffer, DWORD length)
{
  DWORD i;

  i = lstrlen(this->buffer);
  --length;
  if (i > length) i = length;
  CopyMemory(buffer, this->buffer, i);
  buffer[i] = 0;

  return 0;
}


int main()
{
  IExample *example = (IExample *)GlobalAlloc(GMEM_FIXED, sizeof(IExample));

  strcpy_s(example->buffer, sizeof example->buffer, "Hello World!");
  example->count = lstrlen(example->buffer);

  printf("Count: %d\n%s", example->count, example->buffer);

  GlobalFree(example);
  return 0;
}

