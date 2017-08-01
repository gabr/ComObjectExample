#include <stdio.h>
#include <windows.h>
#include <objbase.h>
#include <INITGUID.H>

#define BUFFER_LEN 80

typedef struct iExample IExample;
typedef HRESULT STDMETHODCALLTYPE QueryInterfacePtr(IExample *, REFIID, void **);
typedef ULONG STDMETHODCALLTYPE AddRefPtr(IExample *);
typedef ULONG STDMETHODCALLTYPE ReleasePtr(IExample *);

typedef long SetStringPtr(IExample *, char *);
typedef long GetStringPtr(IExample *, char *, long);

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
  IExampleVtbl *lpVtbl;
  DWORD         count;
  char          buffer[BUFFER_LEN];
} IExample;

long SetString(IExample *this, char *str)
{
  DWORD i;

  i = lstrlen(str);
  if (i > BUFFER_LEN - 1) i = BUFFER_LEN - 1;
  CopyMemory(this->buffer, str, i);
  this->buffer[i] = 0;

  return 0;
}

long GetString(IExample *this, char *buffer, DWORD length)
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
  return 0;
}

