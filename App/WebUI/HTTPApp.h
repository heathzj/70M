
#include<GenericTypeDefs.h>
#include"Global.h"
#include "TCPIP Stack/TCPIP.h"
#include "Main.h"
#include "Global.h"		// Needed for SaveAppConfig() prototype
#include "flash.h"
#include "define.h"
#include "Comm.h"
#include "DeviceManager.h"
#if defined(RCUT) || defined(RCUR)
#include "RCULLAccess.h"
#elif defined(SPT)
#endif

#include "BUCClient.h"
#include "AppUtil.h"
#include "RCUHLAccess.h"

#if defined(HTTP_USE_POST)
        static HTTP_IO_RESULT HTTPPostlut(void); 
	#if defined(USE_LCD)
        
		static HTTP_IO_RESULT HTTPPostLCD(void);
                    static HTTP_IO_RESULT HTTPPostLCD2(void);
	#endif
	#if defined(STACK_USE_HTTP_MD5_DEMO)
		#if !defined(STACK_USE_MD5)
			#error The HTTP_MD5_DEMO requires STACK_USE_MD5
		#endif
		static HTTP_IO_RESULT HTTPPostMD5(void);
	#endif
	#if defined(STACK_USE_HTTP_APP_RECONFIG)
		extern APP_CONFIG AppConfig;
		static HTTP_IO_RESULT HTTPPostConfig(void);
		#if defined(STACK_USE_SNMP_SERVER)
		static HTTP_IO_RESULT HTTPPostSNMPCommunity(void);
		#endif
	#endif
	#if defined(STACK_USE_HTTP_EMAIL_DEMO) || defined(STACK_USE_SMTP_CLIENT)
		#if !defined(STACK_USE_SMTP_CLIENT)
			#error The HTTP_EMAIL_DEMO requires STACK_USE_SMTP_CLIENT
		#endif
		static HTTP_IO_RESULT HTTPPostEmail(void);
	#endif
	#if defined(STACK_USE_DYNAMICDNS_CLIENT)
		static HTTP_IO_RESULT HTTPPostDDNSConfig(void);
	#endif
#endif

/* Prototype for HTTPExe_get_deviceinfo function */
BOOL HTTPExe_get_deviceinfo (void);

extern char oldp[10];
extern char newp[10];
extern char rep[10];

extern webpassword_t webpassinfo;
extern APP_CONFIG AppConfig;
extern BOOL lastSuccess;
extern BOOL lastFailure;
extern BYTE WIFI_EN;
extern BYTE Unit_KUDRIVER;
extern unsigned char ostart,oend,ctemp;
extern BYTE rfout_num, rfout_offset;
extern BYTE sspa_temp_shutdown_thd_degree;
