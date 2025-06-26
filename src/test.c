#include <stdio.h>
#include "util/aur_util/aur_util.h"
#include "util/hash/uthash.h"
#include "util/sds/sds.h"
#include "util/sds/sdsalloc.h"
#define WIN32_LEAN_AND_MEAN // 在包含 windows.h 之前定义，减少包含内容,防止宏污染
// #include <winsock2.h>
// #include <ws2tcpip.h>
#include <windows.h> //加上Windows.h头文件,如果有旧版本不兼容问题,需要先include新h文件
#include <bluetoothapis.h>
#include <errhandlingapi.h>
// #include <pthread.h>

// #pragma comment(lib, "ws2_32.lib") 仅在MSCV中有效,对MinGW失效
void get_error();
int main(int argc, char const *argv[])
{
   println("hello");
   println("helloAurxsiu");

   sds str = sdsnew("hello SDS");
   println(str);

   HBLUETOOTH_RADIO_FIND hbf = NULL;
   HANDLE hbr = NULL;
   BLUETOOTH_FIND_RADIO_PARAMS btfrp = {sizeof(btfrp)};

   hbf = BluetoothFindFirstRadio(&btfrp, &hbr);
   if (hbf == NULL)
   {
      printf("No Bluetooth radio found. Error: %lu\n", GetLastError());
      return 1;
   }

   do
   {
      BLUETOOTH_RADIO_INFO bri = {sizeof(bri)};
      if (BluetoothGetRadioInfo(hbr, &bri) == ERROR_SUCCESS)
      {
         wprintf(L"Radio: %s\n", bri.szName);
      }

      BLUETOOTH_DEVICE_SEARCH_PARAMS btsp = {sizeof(btsp)};
      btsp.hRadio = hbr;
      btsp.fReturnAuthenticated = TRUE;
      btsp.fReturnConnected = TRUE;
      btsp.fReturnRemembered = TRUE;
      btsp.fReturnUnknown = TRUE;
      btsp.fIssueInquiry = TRUE;
      btsp.cTimeoutMultiplier = 2;

      BLUETOOTH_DEVICE_INFO btdi = {sizeof(btdi)};
      HBLUETOOTH_DEVICE_FIND hbdf = BluetoothFindFirstDevice(&btsp, &btdi);
      if (hbdf != NULL)
      {
         do
         {
            wprintf(L"Found device: %s\n", btdi.szName);
         } while (BluetoothFindNextDevice(hbdf, &btdi));
         BluetoothFindDeviceClose(hbdf);
      }
      else
      {
         printf("  No device found for this radio. Error: %lu\n", GetLastError());
      }

      CloseHandle(hbr);
   } while (BluetoothFindNextRadio(hbf, &hbr));

   BluetoothFindRadioClose(hbf);
   return 0;
}

void get_bluetooth()
{
   BLUETOOTH_SELECT_DEVICE_PARAMS parm;
   ZeroMemory(&parm, sizeof(parm)); // 推荐先清零，避免未定义行为

   parm.dwSize = sizeof(parm); // ✅ 必须！
   parm.fShowAuthenticated = TRUE;
   parm.fShowRemembered = TRUE;
   parm.fShowUnknown = TRUE;
   // parm.fAddNewDeviceWizard = TRUE;
   parm.cNumDevices = 0; // 初始设备数（0 表示 API 会动态填充）
   WINBOOL result = BluetoothSelectDevices(&parm);
   printf("%d", result);
   if (result == 0)
   {
      get_error();
   }
}

void get_error()
{
   LPVOID lpMsgBuf;
   DWORD dw = GetLastError();

   if (FormatMessage(
           FORMAT_MESSAGE_ALLOCATE_BUFFER |
               FORMAT_MESSAGE_FROM_SYSTEM |
               FORMAT_MESSAGE_IGNORE_INSERTS,
           NULL,
           dw,
           MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
           (LPTSTR)&lpMsgBuf,
           0, NULL) == 0)
   {
      MessageBox(NULL, TEXT("FormatMessage failed"), TEXT("Error"), MB_OK);
      ExitProcess(dw);
   }

   MessageBox(NULL, (LPCTSTR)lpMsgBuf, TEXT("Error"), MB_OK);

   LocalFree(lpMsgBuf);
   ExitProcess(dw);
}