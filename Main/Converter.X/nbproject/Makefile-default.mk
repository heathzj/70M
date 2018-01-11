#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Converter.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Converter.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=--mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../App/WebUI/HTTPApp.c ../../App/WebUI/HTTPGetDevInfo.c ../../App/WebUI/HTTPPrint.c ../../Bootstrap/Initialization.c ../../Drivers/External-Peripherals/devadc.c ../../Drivers/External-Peripherals/oled_c1.c ../../Drivers/External-Peripherals/oled_c2.c ../../Drivers/MCU-Internal/MPFSImg2.c ../../Drivers/MCU-Internal/devspi.c ../../Drivers/MCU-Internal/ISR.c ../../Drivers/MCU-Internal/internalADC.c ../../Drivers/MCU-Internal/i2c_c1.c "../../Microchip/TCPIP Stack/StackTsk.c" "../../Microchip/TCPIP Stack/TCP.c" "../../Microchip/TCPIP Stack/UDP.c" "../../Microchip/TCPIP Stack/ARP.c" "../../Microchip/TCPIP Stack/ETH97J60.c" "../../Microchip/TCPIP Stack/IP.c" "../../Microchip/TCPIP Stack/DHCP.c" "../../Microchip/TCPIP Stack/DHCPs.c" "../../Microchip/TCPIP Stack/HTTP2.c" "../../Microchip/TCPIP Stack/ICMP.c" "../../Microchip/TCPIP Stack/SNMP.c" "../../Microchip/TCPIP Stack/Delay.c" "../../Microchip/TCPIP Stack/Helpers.c" "../../Microchip/TCPIP Stack/UART.c" "../../Microchip/TCPIP Stack/Tick.c" "../../Microchip/TCPIP Stack/MPFS2.c" "../../Microchip/TCPIP Stack/UART2TCPBridge.c" "../../Microchip/TCPIP Stack/SPIEEPROM.c" "../../Microchip/TCPIP Stack/SPIFlash.c" ../../App/SNMP/SNMPApp.c ../../App/SNMP/SNMPLLiBUCDevInfo.c ../../App/SNMP/SNMPLLiBUCOp.c ../../App/SNMP/SNMPLLiBUCStatus.c ../../App/SNMP/SNMPSysInfo.c ../../SysLib/util.c ../Main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/329253274/HTTPApp.p1 ${OBJECTDIR}/_ext/329253274/HTTPGetDevInfo.p1 ${OBJECTDIR}/_ext/329253274/HTTPPrint.p1 ${OBJECTDIR}/_ext/2106782546/Initialization.p1 ${OBJECTDIR}/_ext/844836729/devadc.p1 ${OBJECTDIR}/_ext/844836729/oled_c1.p1 ${OBJECTDIR}/_ext/844836729/oled_c2.p1 ${OBJECTDIR}/_ext/209185937/MPFSImg2.p1 ${OBJECTDIR}/_ext/209185937/devspi.p1 ${OBJECTDIR}/_ext/209185937/ISR.p1 ${OBJECTDIR}/_ext/209185937/internalADC.p1 ${OBJECTDIR}/_ext/209185937/i2c_c1.p1 ${OBJECTDIR}/_ext/1295770447/StackTsk.p1 ${OBJECTDIR}/_ext/1295770447/TCP.p1 ${OBJECTDIR}/_ext/1295770447/UDP.p1 ${OBJECTDIR}/_ext/1295770447/ARP.p1 ${OBJECTDIR}/_ext/1295770447/ETH97J60.p1 ${OBJECTDIR}/_ext/1295770447/IP.p1 ${OBJECTDIR}/_ext/1295770447/DHCP.p1 ${OBJECTDIR}/_ext/1295770447/DHCPs.p1 ${OBJECTDIR}/_ext/1295770447/HTTP2.p1 ${OBJECTDIR}/_ext/1295770447/ICMP.p1 ${OBJECTDIR}/_ext/1295770447/SNMP.p1 ${OBJECTDIR}/_ext/1295770447/Delay.p1 ${OBJECTDIR}/_ext/1295770447/Helpers.p1 ${OBJECTDIR}/_ext/1295770447/UART.p1 ${OBJECTDIR}/_ext/1295770447/Tick.p1 ${OBJECTDIR}/_ext/1295770447/MPFS2.p1 ${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.p1 ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.p1 ${OBJECTDIR}/_ext/1295770447/SPIFlash.p1 ${OBJECTDIR}/_ext/10479148/SNMPApp.p1 ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCDevInfo.p1 ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCOp.p1 ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCStatus.p1 ${OBJECTDIR}/_ext/10479148/SNMPSysInfo.p1 ${OBJECTDIR}/_ext/1777908168/util.p1 ${OBJECTDIR}/_ext/1472/Main.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/329253274/HTTPApp.p1.d ${OBJECTDIR}/_ext/329253274/HTTPGetDevInfo.p1.d ${OBJECTDIR}/_ext/329253274/HTTPPrint.p1.d ${OBJECTDIR}/_ext/2106782546/Initialization.p1.d ${OBJECTDIR}/_ext/844836729/devadc.p1.d ${OBJECTDIR}/_ext/844836729/oled_c1.p1.d ${OBJECTDIR}/_ext/844836729/oled_c2.p1.d ${OBJECTDIR}/_ext/209185937/MPFSImg2.p1.d ${OBJECTDIR}/_ext/209185937/devspi.p1.d ${OBJECTDIR}/_ext/209185937/ISR.p1.d ${OBJECTDIR}/_ext/209185937/internalADC.p1.d ${OBJECTDIR}/_ext/209185937/i2c_c1.p1.d ${OBJECTDIR}/_ext/1295770447/StackTsk.p1.d ${OBJECTDIR}/_ext/1295770447/TCP.p1.d ${OBJECTDIR}/_ext/1295770447/UDP.p1.d ${OBJECTDIR}/_ext/1295770447/ARP.p1.d ${OBJECTDIR}/_ext/1295770447/ETH97J60.p1.d ${OBJECTDIR}/_ext/1295770447/IP.p1.d ${OBJECTDIR}/_ext/1295770447/DHCP.p1.d ${OBJECTDIR}/_ext/1295770447/DHCPs.p1.d ${OBJECTDIR}/_ext/1295770447/HTTP2.p1.d ${OBJECTDIR}/_ext/1295770447/ICMP.p1.d ${OBJECTDIR}/_ext/1295770447/SNMP.p1.d ${OBJECTDIR}/_ext/1295770447/Delay.p1.d ${OBJECTDIR}/_ext/1295770447/Helpers.p1.d ${OBJECTDIR}/_ext/1295770447/UART.p1.d ${OBJECTDIR}/_ext/1295770447/Tick.p1.d ${OBJECTDIR}/_ext/1295770447/MPFS2.p1.d ${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.p1.d ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.p1.d ${OBJECTDIR}/_ext/1295770447/SPIFlash.p1.d ${OBJECTDIR}/_ext/10479148/SNMPApp.p1.d ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCDevInfo.p1.d ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCOp.p1.d ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCStatus.p1.d ${OBJECTDIR}/_ext/10479148/SNMPSysInfo.p1.d ${OBJECTDIR}/_ext/1777908168/util.p1.d ${OBJECTDIR}/_ext/1472/Main.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/329253274/HTTPApp.p1 ${OBJECTDIR}/_ext/329253274/HTTPGetDevInfo.p1 ${OBJECTDIR}/_ext/329253274/HTTPPrint.p1 ${OBJECTDIR}/_ext/2106782546/Initialization.p1 ${OBJECTDIR}/_ext/844836729/devadc.p1 ${OBJECTDIR}/_ext/844836729/oled_c1.p1 ${OBJECTDIR}/_ext/844836729/oled_c2.p1 ${OBJECTDIR}/_ext/209185937/MPFSImg2.p1 ${OBJECTDIR}/_ext/209185937/devspi.p1 ${OBJECTDIR}/_ext/209185937/ISR.p1 ${OBJECTDIR}/_ext/209185937/internalADC.p1 ${OBJECTDIR}/_ext/209185937/i2c_c1.p1 ${OBJECTDIR}/_ext/1295770447/StackTsk.p1 ${OBJECTDIR}/_ext/1295770447/TCP.p1 ${OBJECTDIR}/_ext/1295770447/UDP.p1 ${OBJECTDIR}/_ext/1295770447/ARP.p1 ${OBJECTDIR}/_ext/1295770447/ETH97J60.p1 ${OBJECTDIR}/_ext/1295770447/IP.p1 ${OBJECTDIR}/_ext/1295770447/DHCP.p1 ${OBJECTDIR}/_ext/1295770447/DHCPs.p1 ${OBJECTDIR}/_ext/1295770447/HTTP2.p1 ${OBJECTDIR}/_ext/1295770447/ICMP.p1 ${OBJECTDIR}/_ext/1295770447/SNMP.p1 ${OBJECTDIR}/_ext/1295770447/Delay.p1 ${OBJECTDIR}/_ext/1295770447/Helpers.p1 ${OBJECTDIR}/_ext/1295770447/UART.p1 ${OBJECTDIR}/_ext/1295770447/Tick.p1 ${OBJECTDIR}/_ext/1295770447/MPFS2.p1 ${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.p1 ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.p1 ${OBJECTDIR}/_ext/1295770447/SPIFlash.p1 ${OBJECTDIR}/_ext/10479148/SNMPApp.p1 ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCDevInfo.p1 ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCOp.p1 ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCStatus.p1 ${OBJECTDIR}/_ext/10479148/SNMPSysInfo.p1 ${OBJECTDIR}/_ext/1777908168/util.p1 ${OBJECTDIR}/_ext/1472/Main.p1

# Source Files
SOURCEFILES=../../App/WebUI/HTTPApp.c ../../App/WebUI/HTTPGetDevInfo.c ../../App/WebUI/HTTPPrint.c ../../Bootstrap/Initialization.c ../../Drivers/External-Peripherals/devadc.c ../../Drivers/External-Peripherals/oled_c1.c ../../Drivers/External-Peripherals/oled_c2.c ../../Drivers/MCU-Internal/MPFSImg2.c ../../Drivers/MCU-Internal/devspi.c ../../Drivers/MCU-Internal/ISR.c ../../Drivers/MCU-Internal/internalADC.c ../../Drivers/MCU-Internal/i2c_c1.c ../../Microchip/TCPIP Stack/StackTsk.c ../../Microchip/TCPIP Stack/TCP.c ../../Microchip/TCPIP Stack/UDP.c ../../Microchip/TCPIP Stack/ARP.c ../../Microchip/TCPIP Stack/ETH97J60.c ../../Microchip/TCPIP Stack/IP.c ../../Microchip/TCPIP Stack/DHCP.c ../../Microchip/TCPIP Stack/DHCPs.c ../../Microchip/TCPIP Stack/HTTP2.c ../../Microchip/TCPIP Stack/ICMP.c ../../Microchip/TCPIP Stack/SNMP.c ../../Microchip/TCPIP Stack/Delay.c ../../Microchip/TCPIP Stack/Helpers.c ../../Microchip/TCPIP Stack/UART.c ../../Microchip/TCPIP Stack/Tick.c ../../Microchip/TCPIP Stack/MPFS2.c ../../Microchip/TCPIP Stack/UART2TCPBridge.c ../../Microchip/TCPIP Stack/SPIEEPROM.c ../../Microchip/TCPIP Stack/SPIFlash.c ../../App/SNMP/SNMPApp.c ../../App/SNMP/SNMPLLiBUCDevInfo.c ../../App/SNMP/SNMPLLiBUCOp.c ../../App/SNMP/SNMPLLiBUCStatus.c ../../App/SNMP/SNMPSysInfo.c ../../SysLib/util.c ../Main.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Converter.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F97J60
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/329253274/HTTPApp.p1: ../../App/WebUI/HTTPApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/329253274" 
	@${RM} ${OBJECTDIR}/_ext/329253274/HTTPApp.p1.d 
	@${RM} ${OBJECTDIR}/_ext/329253274/HTTPApp.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/329253274/HTTPApp.p1  ../../App/WebUI/HTTPApp.c 
	@-${MV} ${OBJECTDIR}/_ext/329253274/HTTPApp.d ${OBJECTDIR}/_ext/329253274/HTTPApp.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/329253274/HTTPApp.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/329253274/HTTPGetDevInfo.p1: ../../App/WebUI/HTTPGetDevInfo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/329253274" 
	@${RM} ${OBJECTDIR}/_ext/329253274/HTTPGetDevInfo.p1.d 
	@${RM} ${OBJECTDIR}/_ext/329253274/HTTPGetDevInfo.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/329253274/HTTPGetDevInfo.p1  ../../App/WebUI/HTTPGetDevInfo.c 
	@-${MV} ${OBJECTDIR}/_ext/329253274/HTTPGetDevInfo.d ${OBJECTDIR}/_ext/329253274/HTTPGetDevInfo.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/329253274/HTTPGetDevInfo.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/329253274/HTTPPrint.p1: ../../App/WebUI/HTTPPrint.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/329253274" 
	@${RM} ${OBJECTDIR}/_ext/329253274/HTTPPrint.p1.d 
	@${RM} ${OBJECTDIR}/_ext/329253274/HTTPPrint.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/329253274/HTTPPrint.p1  ../../App/WebUI/HTTPPrint.c 
	@-${MV} ${OBJECTDIR}/_ext/329253274/HTTPPrint.d ${OBJECTDIR}/_ext/329253274/HTTPPrint.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/329253274/HTTPPrint.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2106782546/Initialization.p1: ../../Bootstrap/Initialization.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2106782546" 
	@${RM} ${OBJECTDIR}/_ext/2106782546/Initialization.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2106782546/Initialization.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2106782546/Initialization.p1  ../../Bootstrap/Initialization.c 
	@-${MV} ${OBJECTDIR}/_ext/2106782546/Initialization.d ${OBJECTDIR}/_ext/2106782546/Initialization.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2106782546/Initialization.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/844836729/devadc.p1: ../../Drivers/External-Peripherals/devadc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/844836729" 
	@${RM} ${OBJECTDIR}/_ext/844836729/devadc.p1.d 
	@${RM} ${OBJECTDIR}/_ext/844836729/devadc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/844836729/devadc.p1  ../../Drivers/External-Peripherals/devadc.c 
	@-${MV} ${OBJECTDIR}/_ext/844836729/devadc.d ${OBJECTDIR}/_ext/844836729/devadc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/844836729/devadc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/844836729/oled_c1.p1: ../../Drivers/External-Peripherals/oled_c1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/844836729" 
	@${RM} ${OBJECTDIR}/_ext/844836729/oled_c1.p1.d 
	@${RM} ${OBJECTDIR}/_ext/844836729/oled_c1.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/844836729/oled_c1.p1  ../../Drivers/External-Peripherals/oled_c1.c 
	@-${MV} ${OBJECTDIR}/_ext/844836729/oled_c1.d ${OBJECTDIR}/_ext/844836729/oled_c1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/844836729/oled_c1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/844836729/oled_c2.p1: ../../Drivers/External-Peripherals/oled_c2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/844836729" 
	@${RM} ${OBJECTDIR}/_ext/844836729/oled_c2.p1.d 
	@${RM} ${OBJECTDIR}/_ext/844836729/oled_c2.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/844836729/oled_c2.p1  ../../Drivers/External-Peripherals/oled_c2.c 
	@-${MV} ${OBJECTDIR}/_ext/844836729/oled_c2.d ${OBJECTDIR}/_ext/844836729/oled_c2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/844836729/oled_c2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/209185937/MPFSImg2.p1: ../../Drivers/MCU-Internal/MPFSImg2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/209185937" 
	@${RM} ${OBJECTDIR}/_ext/209185937/MPFSImg2.p1.d 
	@${RM} ${OBJECTDIR}/_ext/209185937/MPFSImg2.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/209185937/MPFSImg2.p1  ../../Drivers/MCU-Internal/MPFSImg2.c 
	@-${MV} ${OBJECTDIR}/_ext/209185937/MPFSImg2.d ${OBJECTDIR}/_ext/209185937/MPFSImg2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/209185937/MPFSImg2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/209185937/devspi.p1: ../../Drivers/MCU-Internal/devspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/209185937" 
	@${RM} ${OBJECTDIR}/_ext/209185937/devspi.p1.d 
	@${RM} ${OBJECTDIR}/_ext/209185937/devspi.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/209185937/devspi.p1  ../../Drivers/MCU-Internal/devspi.c 
	@-${MV} ${OBJECTDIR}/_ext/209185937/devspi.d ${OBJECTDIR}/_ext/209185937/devspi.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/209185937/devspi.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/209185937/ISR.p1: ../../Drivers/MCU-Internal/ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/209185937" 
	@${RM} ${OBJECTDIR}/_ext/209185937/ISR.p1.d 
	@${RM} ${OBJECTDIR}/_ext/209185937/ISR.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/209185937/ISR.p1  ../../Drivers/MCU-Internal/ISR.c 
	@-${MV} ${OBJECTDIR}/_ext/209185937/ISR.d ${OBJECTDIR}/_ext/209185937/ISR.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/209185937/ISR.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/209185937/internalADC.p1: ../../Drivers/MCU-Internal/internalADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/209185937" 
	@${RM} ${OBJECTDIR}/_ext/209185937/internalADC.p1.d 
	@${RM} ${OBJECTDIR}/_ext/209185937/internalADC.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/209185937/internalADC.p1  ../../Drivers/MCU-Internal/internalADC.c 
	@-${MV} ${OBJECTDIR}/_ext/209185937/internalADC.d ${OBJECTDIR}/_ext/209185937/internalADC.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/209185937/internalADC.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/209185937/i2c_c1.p1: ../../Drivers/MCU-Internal/i2c_c1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/209185937" 
	@${RM} ${OBJECTDIR}/_ext/209185937/i2c_c1.p1.d 
	@${RM} ${OBJECTDIR}/_ext/209185937/i2c_c1.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/209185937/i2c_c1.p1  ../../Drivers/MCU-Internal/i2c_c1.c 
	@-${MV} ${OBJECTDIR}/_ext/209185937/i2c_c1.d ${OBJECTDIR}/_ext/209185937/i2c_c1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/209185937/i2c_c1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/StackTsk.p1: ../../Microchip/TCPIP\ Stack/StackTsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/StackTsk.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/StackTsk.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/StackTsk.p1  "../../Microchip/TCPIP Stack/StackTsk.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/StackTsk.d ${OBJECTDIR}/_ext/1295770447/StackTsk.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/StackTsk.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/TCP.p1: ../../Microchip/TCPIP\ Stack/TCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/TCP.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/TCP.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/TCP.p1  "../../Microchip/TCPIP Stack/TCP.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/TCP.d ${OBJECTDIR}/_ext/1295770447/TCP.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/TCP.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/UDP.p1: ../../Microchip/TCPIP\ Stack/UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UDP.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UDP.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/UDP.p1  "../../Microchip/TCPIP Stack/UDP.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/UDP.d ${OBJECTDIR}/_ext/1295770447/UDP.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/UDP.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/ARP.p1: ../../Microchip/TCPIP\ Stack/ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ARP.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ARP.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/ARP.p1  "../../Microchip/TCPIP Stack/ARP.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/ARP.d ${OBJECTDIR}/_ext/1295770447/ARP.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/ARP.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/ETH97J60.p1: ../../Microchip/TCPIP\ Stack/ETH97J60.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ETH97J60.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ETH97J60.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/ETH97J60.p1  "../../Microchip/TCPIP Stack/ETH97J60.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/ETH97J60.d ${OBJECTDIR}/_ext/1295770447/ETH97J60.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/ETH97J60.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/IP.p1: ../../Microchip/TCPIP\ Stack/IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/IP.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/IP.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/IP.p1  "../../Microchip/TCPIP Stack/IP.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/IP.d ${OBJECTDIR}/_ext/1295770447/IP.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/IP.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/DHCP.p1: ../../Microchip/TCPIP\ Stack/DHCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DHCP.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DHCP.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/DHCP.p1  "../../Microchip/TCPIP Stack/DHCP.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/DHCP.d ${OBJECTDIR}/_ext/1295770447/DHCP.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/DHCP.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/DHCPs.p1: ../../Microchip/TCPIP\ Stack/DHCPs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DHCPs.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DHCPs.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/DHCPs.p1  "../../Microchip/TCPIP Stack/DHCPs.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/DHCPs.d ${OBJECTDIR}/_ext/1295770447/DHCPs.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/DHCPs.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/HTTP2.p1: ../../Microchip/TCPIP\ Stack/HTTP2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/HTTP2.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/HTTP2.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/HTTP2.p1  "../../Microchip/TCPIP Stack/HTTP2.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/HTTP2.d ${OBJECTDIR}/_ext/1295770447/HTTP2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/HTTP2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/ICMP.p1: ../../Microchip/TCPIP\ Stack/ICMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ICMP.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ICMP.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/ICMP.p1  "../../Microchip/TCPIP Stack/ICMP.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/ICMP.d ${OBJECTDIR}/_ext/1295770447/ICMP.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/ICMP.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/SNMP.p1: ../../Microchip/TCPIP\ Stack/SNMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SNMP.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SNMP.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/SNMP.p1  "../../Microchip/TCPIP Stack/SNMP.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/SNMP.d ${OBJECTDIR}/_ext/1295770447/SNMP.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/SNMP.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/Delay.p1: ../../Microchip/TCPIP\ Stack/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Delay.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Delay.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/Delay.p1  "../../Microchip/TCPIP Stack/Delay.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/Delay.d ${OBJECTDIR}/_ext/1295770447/Delay.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/Delay.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/Helpers.p1: ../../Microchip/TCPIP\ Stack/Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Helpers.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Helpers.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/Helpers.p1  "../../Microchip/TCPIP Stack/Helpers.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/Helpers.d ${OBJECTDIR}/_ext/1295770447/Helpers.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/Helpers.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/UART.p1: ../../Microchip/TCPIP\ Stack/UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UART.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UART.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/UART.p1  "../../Microchip/TCPIP Stack/UART.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/UART.d ${OBJECTDIR}/_ext/1295770447/UART.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/UART.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/Tick.p1: ../../Microchip/TCPIP\ Stack/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Tick.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Tick.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/Tick.p1  "../../Microchip/TCPIP Stack/Tick.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/Tick.d ${OBJECTDIR}/_ext/1295770447/Tick.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/Tick.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/MPFS2.p1: ../../Microchip/TCPIP\ Stack/MPFS2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/MPFS2.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/MPFS2.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/MPFS2.p1  "../../Microchip/TCPIP Stack/MPFS2.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/MPFS2.d ${OBJECTDIR}/_ext/1295770447/MPFS2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/MPFS2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.p1: ../../Microchip/TCPIP\ Stack/UART2TCPBridge.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.p1  "../../Microchip/TCPIP Stack/UART2TCPBridge.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.d ${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/SPIEEPROM.p1: ../../Microchip/TCPIP\ Stack/SPIEEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/SPIEEPROM.p1  "../../Microchip/TCPIP Stack/SPIEEPROM.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.d ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/SPIFlash.p1: ../../Microchip/TCPIP\ Stack/SPIFlash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIFlash.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIFlash.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/SPIFlash.p1  "../../Microchip/TCPIP Stack/SPIFlash.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/SPIFlash.d ${OBJECTDIR}/_ext/1295770447/SPIFlash.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/SPIFlash.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/10479148/SNMPApp.p1: ../../App/SNMP/SNMPApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/10479148" 
	@${RM} ${OBJECTDIR}/_ext/10479148/SNMPApp.p1.d 
	@${RM} ${OBJECTDIR}/_ext/10479148/SNMPApp.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/10479148/SNMPApp.p1  ../../App/SNMP/SNMPApp.c 
	@-${MV} ${OBJECTDIR}/_ext/10479148/SNMPApp.d ${OBJECTDIR}/_ext/10479148/SNMPApp.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/10479148/SNMPApp.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/10479148/SNMPLLiBUCDevInfo.p1: ../../App/SNMP/SNMPLLiBUCDevInfo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/10479148" 
	@${RM} ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCDevInfo.p1.d 
	@${RM} ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCDevInfo.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/10479148/SNMPLLiBUCDevInfo.p1  ../../App/SNMP/SNMPLLiBUCDevInfo.c 
	@-${MV} ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCDevInfo.d ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCDevInfo.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCDevInfo.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/10479148/SNMPLLiBUCOp.p1: ../../App/SNMP/SNMPLLiBUCOp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/10479148" 
	@${RM} ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCOp.p1.d 
	@${RM} ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCOp.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/10479148/SNMPLLiBUCOp.p1  ../../App/SNMP/SNMPLLiBUCOp.c 
	@-${MV} ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCOp.d ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCOp.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCOp.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/10479148/SNMPLLiBUCStatus.p1: ../../App/SNMP/SNMPLLiBUCStatus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/10479148" 
	@${RM} ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCStatus.p1.d 
	@${RM} ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCStatus.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/10479148/SNMPLLiBUCStatus.p1  ../../App/SNMP/SNMPLLiBUCStatus.c 
	@-${MV} ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCStatus.d ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCStatus.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCStatus.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/10479148/SNMPSysInfo.p1: ../../App/SNMP/SNMPSysInfo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/10479148" 
	@${RM} ${OBJECTDIR}/_ext/10479148/SNMPSysInfo.p1.d 
	@${RM} ${OBJECTDIR}/_ext/10479148/SNMPSysInfo.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/10479148/SNMPSysInfo.p1  ../../App/SNMP/SNMPSysInfo.c 
	@-${MV} ${OBJECTDIR}/_ext/10479148/SNMPSysInfo.d ${OBJECTDIR}/_ext/10479148/SNMPSysInfo.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/10479148/SNMPSysInfo.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1777908168/util.p1: ../../SysLib/util.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1777908168" 
	@${RM} ${OBJECTDIR}/_ext/1777908168/util.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1777908168/util.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1777908168/util.p1  ../../SysLib/util.c 
	@-${MV} ${OBJECTDIR}/_ext/1777908168/util.d ${OBJECTDIR}/_ext/1777908168/util.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1777908168/util.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/Main.p1: ../Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/Main.p1  ../Main.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/Main.d ${OBJECTDIR}/_ext/1472/Main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/Main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/329253274/HTTPApp.p1: ../../App/WebUI/HTTPApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/329253274" 
	@${RM} ${OBJECTDIR}/_ext/329253274/HTTPApp.p1.d 
	@${RM} ${OBJECTDIR}/_ext/329253274/HTTPApp.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/329253274/HTTPApp.p1  ../../App/WebUI/HTTPApp.c 
	@-${MV} ${OBJECTDIR}/_ext/329253274/HTTPApp.d ${OBJECTDIR}/_ext/329253274/HTTPApp.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/329253274/HTTPApp.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/329253274/HTTPGetDevInfo.p1: ../../App/WebUI/HTTPGetDevInfo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/329253274" 
	@${RM} ${OBJECTDIR}/_ext/329253274/HTTPGetDevInfo.p1.d 
	@${RM} ${OBJECTDIR}/_ext/329253274/HTTPGetDevInfo.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/329253274/HTTPGetDevInfo.p1  ../../App/WebUI/HTTPGetDevInfo.c 
	@-${MV} ${OBJECTDIR}/_ext/329253274/HTTPGetDevInfo.d ${OBJECTDIR}/_ext/329253274/HTTPGetDevInfo.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/329253274/HTTPGetDevInfo.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/329253274/HTTPPrint.p1: ../../App/WebUI/HTTPPrint.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/329253274" 
	@${RM} ${OBJECTDIR}/_ext/329253274/HTTPPrint.p1.d 
	@${RM} ${OBJECTDIR}/_ext/329253274/HTTPPrint.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/329253274/HTTPPrint.p1  ../../App/WebUI/HTTPPrint.c 
	@-${MV} ${OBJECTDIR}/_ext/329253274/HTTPPrint.d ${OBJECTDIR}/_ext/329253274/HTTPPrint.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/329253274/HTTPPrint.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/2106782546/Initialization.p1: ../../Bootstrap/Initialization.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2106782546" 
	@${RM} ${OBJECTDIR}/_ext/2106782546/Initialization.p1.d 
	@${RM} ${OBJECTDIR}/_ext/2106782546/Initialization.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/2106782546/Initialization.p1  ../../Bootstrap/Initialization.c 
	@-${MV} ${OBJECTDIR}/_ext/2106782546/Initialization.d ${OBJECTDIR}/_ext/2106782546/Initialization.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/2106782546/Initialization.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/844836729/devadc.p1: ../../Drivers/External-Peripherals/devadc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/844836729" 
	@${RM} ${OBJECTDIR}/_ext/844836729/devadc.p1.d 
	@${RM} ${OBJECTDIR}/_ext/844836729/devadc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/844836729/devadc.p1  ../../Drivers/External-Peripherals/devadc.c 
	@-${MV} ${OBJECTDIR}/_ext/844836729/devadc.d ${OBJECTDIR}/_ext/844836729/devadc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/844836729/devadc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/844836729/oled_c1.p1: ../../Drivers/External-Peripherals/oled_c1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/844836729" 
	@${RM} ${OBJECTDIR}/_ext/844836729/oled_c1.p1.d 
	@${RM} ${OBJECTDIR}/_ext/844836729/oled_c1.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/844836729/oled_c1.p1  ../../Drivers/External-Peripherals/oled_c1.c 
	@-${MV} ${OBJECTDIR}/_ext/844836729/oled_c1.d ${OBJECTDIR}/_ext/844836729/oled_c1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/844836729/oled_c1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/844836729/oled_c2.p1: ../../Drivers/External-Peripherals/oled_c2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/844836729" 
	@${RM} ${OBJECTDIR}/_ext/844836729/oled_c2.p1.d 
	@${RM} ${OBJECTDIR}/_ext/844836729/oled_c2.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/844836729/oled_c2.p1  ../../Drivers/External-Peripherals/oled_c2.c 
	@-${MV} ${OBJECTDIR}/_ext/844836729/oled_c2.d ${OBJECTDIR}/_ext/844836729/oled_c2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/844836729/oled_c2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/209185937/MPFSImg2.p1: ../../Drivers/MCU-Internal/MPFSImg2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/209185937" 
	@${RM} ${OBJECTDIR}/_ext/209185937/MPFSImg2.p1.d 
	@${RM} ${OBJECTDIR}/_ext/209185937/MPFSImg2.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/209185937/MPFSImg2.p1  ../../Drivers/MCU-Internal/MPFSImg2.c 
	@-${MV} ${OBJECTDIR}/_ext/209185937/MPFSImg2.d ${OBJECTDIR}/_ext/209185937/MPFSImg2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/209185937/MPFSImg2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/209185937/devspi.p1: ../../Drivers/MCU-Internal/devspi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/209185937" 
	@${RM} ${OBJECTDIR}/_ext/209185937/devspi.p1.d 
	@${RM} ${OBJECTDIR}/_ext/209185937/devspi.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/209185937/devspi.p1  ../../Drivers/MCU-Internal/devspi.c 
	@-${MV} ${OBJECTDIR}/_ext/209185937/devspi.d ${OBJECTDIR}/_ext/209185937/devspi.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/209185937/devspi.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/209185937/ISR.p1: ../../Drivers/MCU-Internal/ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/209185937" 
	@${RM} ${OBJECTDIR}/_ext/209185937/ISR.p1.d 
	@${RM} ${OBJECTDIR}/_ext/209185937/ISR.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/209185937/ISR.p1  ../../Drivers/MCU-Internal/ISR.c 
	@-${MV} ${OBJECTDIR}/_ext/209185937/ISR.d ${OBJECTDIR}/_ext/209185937/ISR.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/209185937/ISR.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/209185937/internalADC.p1: ../../Drivers/MCU-Internal/internalADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/209185937" 
	@${RM} ${OBJECTDIR}/_ext/209185937/internalADC.p1.d 
	@${RM} ${OBJECTDIR}/_ext/209185937/internalADC.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/209185937/internalADC.p1  ../../Drivers/MCU-Internal/internalADC.c 
	@-${MV} ${OBJECTDIR}/_ext/209185937/internalADC.d ${OBJECTDIR}/_ext/209185937/internalADC.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/209185937/internalADC.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/209185937/i2c_c1.p1: ../../Drivers/MCU-Internal/i2c_c1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/209185937" 
	@${RM} ${OBJECTDIR}/_ext/209185937/i2c_c1.p1.d 
	@${RM} ${OBJECTDIR}/_ext/209185937/i2c_c1.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/209185937/i2c_c1.p1  ../../Drivers/MCU-Internal/i2c_c1.c 
	@-${MV} ${OBJECTDIR}/_ext/209185937/i2c_c1.d ${OBJECTDIR}/_ext/209185937/i2c_c1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/209185937/i2c_c1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/StackTsk.p1: ../../Microchip/TCPIP\ Stack/StackTsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/StackTsk.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/StackTsk.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/StackTsk.p1  "../../Microchip/TCPIP Stack/StackTsk.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/StackTsk.d ${OBJECTDIR}/_ext/1295770447/StackTsk.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/StackTsk.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/TCP.p1: ../../Microchip/TCPIP\ Stack/TCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/TCP.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/TCP.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/TCP.p1  "../../Microchip/TCPIP Stack/TCP.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/TCP.d ${OBJECTDIR}/_ext/1295770447/TCP.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/TCP.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/UDP.p1: ../../Microchip/TCPIP\ Stack/UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UDP.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UDP.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/UDP.p1  "../../Microchip/TCPIP Stack/UDP.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/UDP.d ${OBJECTDIR}/_ext/1295770447/UDP.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/UDP.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/ARP.p1: ../../Microchip/TCPIP\ Stack/ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ARP.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ARP.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/ARP.p1  "../../Microchip/TCPIP Stack/ARP.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/ARP.d ${OBJECTDIR}/_ext/1295770447/ARP.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/ARP.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/ETH97J60.p1: ../../Microchip/TCPIP\ Stack/ETH97J60.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ETH97J60.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ETH97J60.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/ETH97J60.p1  "../../Microchip/TCPIP Stack/ETH97J60.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/ETH97J60.d ${OBJECTDIR}/_ext/1295770447/ETH97J60.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/ETH97J60.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/IP.p1: ../../Microchip/TCPIP\ Stack/IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/IP.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/IP.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/IP.p1  "../../Microchip/TCPIP Stack/IP.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/IP.d ${OBJECTDIR}/_ext/1295770447/IP.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/IP.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/DHCP.p1: ../../Microchip/TCPIP\ Stack/DHCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DHCP.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DHCP.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/DHCP.p1  "../../Microchip/TCPIP Stack/DHCP.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/DHCP.d ${OBJECTDIR}/_ext/1295770447/DHCP.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/DHCP.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/DHCPs.p1: ../../Microchip/TCPIP\ Stack/DHCPs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DHCPs.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DHCPs.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/DHCPs.p1  "../../Microchip/TCPIP Stack/DHCPs.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/DHCPs.d ${OBJECTDIR}/_ext/1295770447/DHCPs.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/DHCPs.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/HTTP2.p1: ../../Microchip/TCPIP\ Stack/HTTP2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/HTTP2.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/HTTP2.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/HTTP2.p1  "../../Microchip/TCPIP Stack/HTTP2.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/HTTP2.d ${OBJECTDIR}/_ext/1295770447/HTTP2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/HTTP2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/ICMP.p1: ../../Microchip/TCPIP\ Stack/ICMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ICMP.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ICMP.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/ICMP.p1  "../../Microchip/TCPIP Stack/ICMP.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/ICMP.d ${OBJECTDIR}/_ext/1295770447/ICMP.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/ICMP.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/SNMP.p1: ../../Microchip/TCPIP\ Stack/SNMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SNMP.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SNMP.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/SNMP.p1  "../../Microchip/TCPIP Stack/SNMP.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/SNMP.d ${OBJECTDIR}/_ext/1295770447/SNMP.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/SNMP.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/Delay.p1: ../../Microchip/TCPIP\ Stack/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Delay.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Delay.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/Delay.p1  "../../Microchip/TCPIP Stack/Delay.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/Delay.d ${OBJECTDIR}/_ext/1295770447/Delay.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/Delay.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/Helpers.p1: ../../Microchip/TCPIP\ Stack/Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Helpers.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Helpers.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/Helpers.p1  "../../Microchip/TCPIP Stack/Helpers.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/Helpers.d ${OBJECTDIR}/_ext/1295770447/Helpers.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/Helpers.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/UART.p1: ../../Microchip/TCPIP\ Stack/UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UART.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UART.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/UART.p1  "../../Microchip/TCPIP Stack/UART.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/UART.d ${OBJECTDIR}/_ext/1295770447/UART.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/UART.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/Tick.p1: ../../Microchip/TCPIP\ Stack/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Tick.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Tick.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/Tick.p1  "../../Microchip/TCPIP Stack/Tick.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/Tick.d ${OBJECTDIR}/_ext/1295770447/Tick.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/Tick.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/MPFS2.p1: ../../Microchip/TCPIP\ Stack/MPFS2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/MPFS2.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/MPFS2.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/MPFS2.p1  "../../Microchip/TCPIP Stack/MPFS2.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/MPFS2.d ${OBJECTDIR}/_ext/1295770447/MPFS2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/MPFS2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.p1: ../../Microchip/TCPIP\ Stack/UART2TCPBridge.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.p1  "../../Microchip/TCPIP Stack/UART2TCPBridge.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.d ${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/UART2TCPBridge.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/SPIEEPROM.p1: ../../Microchip/TCPIP\ Stack/SPIEEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/SPIEEPROM.p1  "../../Microchip/TCPIP Stack/SPIEEPROM.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.d ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1295770447/SPIFlash.p1: ../../Microchip/TCPIP\ Stack/SPIFlash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1295770447" 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIFlash.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIFlash.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1295770447/SPIFlash.p1  "../../Microchip/TCPIP Stack/SPIFlash.c" 
	@-${MV} ${OBJECTDIR}/_ext/1295770447/SPIFlash.d ${OBJECTDIR}/_ext/1295770447/SPIFlash.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1295770447/SPIFlash.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/10479148/SNMPApp.p1: ../../App/SNMP/SNMPApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/10479148" 
	@${RM} ${OBJECTDIR}/_ext/10479148/SNMPApp.p1.d 
	@${RM} ${OBJECTDIR}/_ext/10479148/SNMPApp.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/10479148/SNMPApp.p1  ../../App/SNMP/SNMPApp.c 
	@-${MV} ${OBJECTDIR}/_ext/10479148/SNMPApp.d ${OBJECTDIR}/_ext/10479148/SNMPApp.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/10479148/SNMPApp.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/10479148/SNMPLLiBUCDevInfo.p1: ../../App/SNMP/SNMPLLiBUCDevInfo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/10479148" 
	@${RM} ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCDevInfo.p1.d 
	@${RM} ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCDevInfo.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/10479148/SNMPLLiBUCDevInfo.p1  ../../App/SNMP/SNMPLLiBUCDevInfo.c 
	@-${MV} ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCDevInfo.d ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCDevInfo.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCDevInfo.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/10479148/SNMPLLiBUCOp.p1: ../../App/SNMP/SNMPLLiBUCOp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/10479148" 
	@${RM} ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCOp.p1.d 
	@${RM} ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCOp.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/10479148/SNMPLLiBUCOp.p1  ../../App/SNMP/SNMPLLiBUCOp.c 
	@-${MV} ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCOp.d ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCOp.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCOp.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/10479148/SNMPLLiBUCStatus.p1: ../../App/SNMP/SNMPLLiBUCStatus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/10479148" 
	@${RM} ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCStatus.p1.d 
	@${RM} ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCStatus.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/10479148/SNMPLLiBUCStatus.p1  ../../App/SNMP/SNMPLLiBUCStatus.c 
	@-${MV} ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCStatus.d ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCStatus.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/10479148/SNMPLLiBUCStatus.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/10479148/SNMPSysInfo.p1: ../../App/SNMP/SNMPSysInfo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/10479148" 
	@${RM} ${OBJECTDIR}/_ext/10479148/SNMPSysInfo.p1.d 
	@${RM} ${OBJECTDIR}/_ext/10479148/SNMPSysInfo.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/10479148/SNMPSysInfo.p1  ../../App/SNMP/SNMPSysInfo.c 
	@-${MV} ${OBJECTDIR}/_ext/10479148/SNMPSysInfo.d ${OBJECTDIR}/_ext/10479148/SNMPSysInfo.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/10479148/SNMPSysInfo.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1777908168/util.p1: ../../SysLib/util.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1777908168" 
	@${RM} ${OBJECTDIR}/_ext/1777908168/util.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1777908168/util.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1777908168/util.p1  ../../SysLib/util.c 
	@-${MV} ${OBJECTDIR}/_ext/1777908168/util.d ${OBJECTDIR}/_ext/1777908168/util.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1777908168/util.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1472/Main.p1: ../Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1472/Main.p1  ../Main.c 
	@-${MV} ${OBJECTDIR}/_ext/1472/Main.d ${OBJECTDIR}/_ext/1472/Main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1472/Main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Converter.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../../lkr/18f97j60.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/Converter.X.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"        $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/Converter.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/Converter.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Converter.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../../lkr/18f97j60.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/Converter.X.${IMAGE_TYPE}.map  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf --stack=compiled "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/Converter.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
