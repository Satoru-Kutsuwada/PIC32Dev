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
FINAL_IMAGE=${DISTDIR}/FreeRTOS_CLICKER2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/FreeRTOS_CLICKER2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=Source/FreeRTOS/RegisterTestTasks.S Source/FreeRTOS/heap_4.c Source/FreeRTOS/list.c Source/FreeRTOS/port.c Source/FreeRTOS/port_asm.S Source/FreeRTOS/queue.c Source/FreeRTOS/tasks.c Source/ConfigPerformance.c Source/main.c Source/usr_Rs485.c Source/usr_timer.c Source/usr_tools.c Source/vl53/usr_i2cMain.c Source/vl53/vl53l0x_api.c Source/vl53/vl53l0x_api_calibration.c Source/vl53/vl53l0x_api_core.c Source/vl53/vl53l0x_api_strings.c Source/vl53/vl53l0x_platform.c Source/vl53/usr_vl53_main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o ${OBJECTDIR}/Source/FreeRTOS/heap_4.o ${OBJECTDIR}/Source/FreeRTOS/list.o ${OBJECTDIR}/Source/FreeRTOS/port.o ${OBJECTDIR}/Source/FreeRTOS/port_asm.o ${OBJECTDIR}/Source/FreeRTOS/queue.o ${OBJECTDIR}/Source/FreeRTOS/tasks.o ${OBJECTDIR}/Source/ConfigPerformance.o ${OBJECTDIR}/Source/main.o ${OBJECTDIR}/Source/usr_Rs485.o ${OBJECTDIR}/Source/usr_timer.o ${OBJECTDIR}/Source/usr_tools.o ${OBJECTDIR}/Source/vl53/usr_i2cMain.o ${OBJECTDIR}/Source/vl53/vl53l0x_api.o ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o ${OBJECTDIR}/Source/vl53/usr_vl53_main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.d ${OBJECTDIR}/Source/FreeRTOS/heap_4.o.d ${OBJECTDIR}/Source/FreeRTOS/list.o.d ${OBJECTDIR}/Source/FreeRTOS/port.o.d ${OBJECTDIR}/Source/FreeRTOS/port_asm.o.d ${OBJECTDIR}/Source/FreeRTOS/queue.o.d ${OBJECTDIR}/Source/FreeRTOS/tasks.o.d ${OBJECTDIR}/Source/ConfigPerformance.o.d ${OBJECTDIR}/Source/main.o.d ${OBJECTDIR}/Source/usr_Rs485.o.d ${OBJECTDIR}/Source/usr_timer.o.d ${OBJECTDIR}/Source/usr_tools.o.d ${OBJECTDIR}/Source/vl53/usr_i2cMain.o.d ${OBJECTDIR}/Source/vl53/vl53l0x_api.o.d ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o.d ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o.d ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o.d ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o.d ${OBJECTDIR}/Source/vl53/usr_vl53_main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o ${OBJECTDIR}/Source/FreeRTOS/heap_4.o ${OBJECTDIR}/Source/FreeRTOS/list.o ${OBJECTDIR}/Source/FreeRTOS/port.o ${OBJECTDIR}/Source/FreeRTOS/port_asm.o ${OBJECTDIR}/Source/FreeRTOS/queue.o ${OBJECTDIR}/Source/FreeRTOS/tasks.o ${OBJECTDIR}/Source/ConfigPerformance.o ${OBJECTDIR}/Source/main.o ${OBJECTDIR}/Source/usr_Rs485.o ${OBJECTDIR}/Source/usr_timer.o ${OBJECTDIR}/Source/usr_tools.o ${OBJECTDIR}/Source/vl53/usr_i2cMain.o ${OBJECTDIR}/Source/vl53/vl53l0x_api.o ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o ${OBJECTDIR}/Source/vl53/usr_vl53_main.o

# Source Files
SOURCEFILES=Source/FreeRTOS/RegisterTestTasks.S Source/FreeRTOS/heap_4.c Source/FreeRTOS/list.c Source/FreeRTOS/port.c Source/FreeRTOS/port_asm.S Source/FreeRTOS/queue.c Source/FreeRTOS/tasks.c Source/ConfigPerformance.c Source/main.c Source/usr_Rs485.c Source/usr_timer.c Source/usr_tools.c Source/vl53/usr_i2cMain.c Source/vl53/vl53l0x_api.c Source/vl53/vl53l0x_api_calibration.c Source/vl53/vl53l0x_api_core.c Source/vl53/vl53l0x_api_strings.c Source/vl53/vl53l0x_platform.c Source/vl53/usr_vl53_main.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/FreeRTOS_CLICKER2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX460F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o: Source/FreeRTOS/RegisterTestTasks.S  .generated_files/flags/default/db7fe470f8b6b19c1a1553d06c39de216d9c2f5b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.ok ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.d"  -o ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o Source/FreeRTOS/RegisterTestTasks.S  -DXPRJ_default=$(CND_CONF)    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.d" "${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source/FreeRTOS/port_asm.o: Source/FreeRTOS/port_asm.S  .generated_files/flags/default/14f4b59687c34942bb703c1bf4555910cffb4bba .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port_asm.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port_asm.o 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port_asm.o.ok ${OBJECTDIR}/Source/FreeRTOS/port_asm.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/port_asm.o.d"  -o ${OBJECTDIR}/Source/FreeRTOS/port_asm.o Source/FreeRTOS/port_asm.S  -DXPRJ_default=$(CND_CONF)    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/Source/FreeRTOS/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/Source/FreeRTOS/port_asm.o.d" "${OBJECTDIR}/Source/FreeRTOS/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o: Source/FreeRTOS/RegisterTestTasks.S  .generated_files/flags/default/3cf69c62de5c8c97efea4dce1e44e2d82517584d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.ok ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.d"  -o ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o Source/FreeRTOS/RegisterTestTasks.S  -DXPRJ_default=$(CND_CONF)    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.asm.d",--gdwarf-2,-I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.d" "${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source/FreeRTOS/port_asm.o: Source/FreeRTOS/port_asm.S  .generated_files/flags/default/a30bda40140a9a2a6b40029603587145bf243975 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port_asm.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port_asm.o 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port_asm.o.ok ${OBJECTDIR}/Source/FreeRTOS/port_asm.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/port_asm.o.d"  -o ${OBJECTDIR}/Source/FreeRTOS/port_asm.o Source/FreeRTOS/port_asm.S  -DXPRJ_default=$(CND_CONF)    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/Source/FreeRTOS/port_asm.o.asm.d",--gdwarf-2,-I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/Source/FreeRTOS/port_asm.o.d" "${OBJECTDIR}/Source/FreeRTOS/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Source/FreeRTOS/heap_4.o: Source/FreeRTOS/heap_4.c  .generated_files/flags/default/776d535d74be0394e2a7198c57cf440b7e280065 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/heap_4.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/heap_4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/heap_4.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/heap_4.o Source/FreeRTOS/heap_4.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/list.o: Source/FreeRTOS/list.c  .generated_files/flags/default/4a076fc033c5bc88fd348a29cfa65934af0650ab .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/list.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/list.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/list.o Source/FreeRTOS/list.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/port.o: Source/FreeRTOS/port.c  .generated_files/flags/default/3d0d8057a661386eaeb3e0cfaaf0095d113fae34 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/port.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/port.o Source/FreeRTOS/port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/queue.o: Source/FreeRTOS/queue.c  .generated_files/flags/default/7baff5dbdbd5422b586651e5865a62137d590899 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/queue.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/queue.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/queue.o Source/FreeRTOS/queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/tasks.o: Source/FreeRTOS/tasks.c  .generated_files/flags/default/ad2a9ec3bf68318662b7da0f657b3e1e53138493 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/tasks.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/tasks.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/tasks.o Source/FreeRTOS/tasks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/ConfigPerformance.o: Source/ConfigPerformance.c  .generated_files/flags/default/17bc4b35ae0a6d94dc69b305dce9bef58e954745 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/ConfigPerformance.o.d 
	@${RM} ${OBJECTDIR}/Source/ConfigPerformance.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/ConfigPerformance.o.d" -o ${OBJECTDIR}/Source/ConfigPerformance.o Source/ConfigPerformance.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/main.o: Source/main.c  .generated_files/flags/default/351d0f4d9863c391388e49a852bb644379961c18 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/main.o.d 
	@${RM} ${OBJECTDIR}/Source/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/main.o.d" -o ${OBJECTDIR}/Source/main.o Source/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/usr_Rs485.o: Source/usr_Rs485.c  .generated_files/flags/default/dd407626e9beb5f9f59956905127f098e9592dc8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/usr_Rs485.o.d 
	@${RM} ${OBJECTDIR}/Source/usr_Rs485.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/usr_Rs485.o.d" -o ${OBJECTDIR}/Source/usr_Rs485.o Source/usr_Rs485.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/usr_timer.o: Source/usr_timer.c  .generated_files/flags/default/4a4cd05218ec567f3989db7b7e527ee3309e1730 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/usr_timer.o.d 
	@${RM} ${OBJECTDIR}/Source/usr_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/usr_timer.o.d" -o ${OBJECTDIR}/Source/usr_timer.o Source/usr_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/usr_tools.o: Source/usr_tools.c  .generated_files/flags/default/cb1bde9a0cf8a1fada2935cbb21d7705094d56ba .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/usr_tools.o.d 
	@${RM} ${OBJECTDIR}/Source/usr_tools.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/usr_tools.o.d" -o ${OBJECTDIR}/Source/usr_tools.o Source/usr_tools.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/usr_i2cMain.o: Source/vl53/usr_i2cMain.c  .generated_files/flags/default/700b2e6f4a0c50c59f9b0c6b818ee8f82af62cc2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/usr_i2cMain.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/usr_i2cMain.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/usr_i2cMain.o.d" -o ${OBJECTDIR}/Source/vl53/usr_i2cMain.o Source/vl53/usr_i2cMain.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_api.o: Source/vl53/vl53l0x_api.c  .generated_files/flags/default/246c456072fbf8d3984e2e5de86aee57edc2115 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_api.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_api.o Source/vl53/vl53l0x_api.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o: Source/vl53/vl53l0x_api_calibration.c  .generated_files/flags/default/a627bd7874b5ae926ee563381a256bb966bec063 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o Source/vl53/vl53l0x_api_calibration.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o: Source/vl53/vl53l0x_api_core.c  .generated_files/flags/default/7864306b3150a30de37415b4fcd2c103a4d9d95e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o Source/vl53/vl53l0x_api_core.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o: Source/vl53/vl53l0x_api_strings.c  .generated_files/flags/default/8c1481c276c94cb380411a5d7ee14bf0cb9b7a63 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o Source/vl53/vl53l0x_api_strings.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_platform.o: Source/vl53/vl53l0x_platform.c  .generated_files/flags/default/e579f0d49e7479abfc1cac2102ae23d55e39ab0a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_platform.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o Source/vl53/vl53l0x_platform.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/usr_vl53_main.o: Source/vl53/usr_vl53_main.c  .generated_files/flags/default/72ed0b893c4fb1f32fd37d33bc3232317f13f0eb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/usr_vl53_main.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/usr_vl53_main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/usr_vl53_main.o.d" -o ${OBJECTDIR}/Source/vl53/usr_vl53_main.o Source/vl53/usr_vl53_main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/Source/FreeRTOS/heap_4.o: Source/FreeRTOS/heap_4.c  .generated_files/flags/default/41c255d3e50706bc738c97f8fa5858a7fd241245 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/heap_4.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/heap_4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/heap_4.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/heap_4.o Source/FreeRTOS/heap_4.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/list.o: Source/FreeRTOS/list.c  .generated_files/flags/default/b3f70d6686c5ac0ed40cb1bb983e8b7c550f9950 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/list.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/list.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/list.o Source/FreeRTOS/list.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/port.o: Source/FreeRTOS/port.c  .generated_files/flags/default/d1a8f76f202013a748836f3d030eaab572dd9de5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/port.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/port.o Source/FreeRTOS/port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/queue.o: Source/FreeRTOS/queue.c  .generated_files/flags/default/7e817713178e0ddf62ef1316551bac3b1db1e20 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/queue.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/queue.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/queue.o Source/FreeRTOS/queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/tasks.o: Source/FreeRTOS/tasks.c  .generated_files/flags/default/9c7daab86c549ba374496180c0d69204c70d9b0c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/tasks.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/tasks.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/tasks.o Source/FreeRTOS/tasks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/ConfigPerformance.o: Source/ConfigPerformance.c  .generated_files/flags/default/7a01aa080511e0030c527e4b45eb4e398d0f184a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/ConfigPerformance.o.d 
	@${RM} ${OBJECTDIR}/Source/ConfigPerformance.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/ConfigPerformance.o.d" -o ${OBJECTDIR}/Source/ConfigPerformance.o Source/ConfigPerformance.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/main.o: Source/main.c  .generated_files/flags/default/a040342e3948096724fb2b34011cb36d0cd2297d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/main.o.d 
	@${RM} ${OBJECTDIR}/Source/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/main.o.d" -o ${OBJECTDIR}/Source/main.o Source/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/usr_Rs485.o: Source/usr_Rs485.c  .generated_files/flags/default/87488460c0182f5b2e9a28076dae0f358ea4f07c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/usr_Rs485.o.d 
	@${RM} ${OBJECTDIR}/Source/usr_Rs485.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/usr_Rs485.o.d" -o ${OBJECTDIR}/Source/usr_Rs485.o Source/usr_Rs485.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/usr_timer.o: Source/usr_timer.c  .generated_files/flags/default/369a1db0fb454d13022801ff9f6d7574ed561046 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/usr_timer.o.d 
	@${RM} ${OBJECTDIR}/Source/usr_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/usr_timer.o.d" -o ${OBJECTDIR}/Source/usr_timer.o Source/usr_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/usr_tools.o: Source/usr_tools.c  .generated_files/flags/default/7f786bd1c8104c892040f08eb584e51acf086408 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/usr_tools.o.d 
	@${RM} ${OBJECTDIR}/Source/usr_tools.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/usr_tools.o.d" -o ${OBJECTDIR}/Source/usr_tools.o Source/usr_tools.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/usr_i2cMain.o: Source/vl53/usr_i2cMain.c  .generated_files/flags/default/4139fa7172684239161e01c9f8a54543a9e89667 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/usr_i2cMain.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/usr_i2cMain.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/usr_i2cMain.o.d" -o ${OBJECTDIR}/Source/vl53/usr_i2cMain.o Source/vl53/usr_i2cMain.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_api.o: Source/vl53/vl53l0x_api.c  .generated_files/flags/default/2853f8871ec4936128a771cbe934206f145d01bd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_api.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_api.o Source/vl53/vl53l0x_api.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o: Source/vl53/vl53l0x_api_calibration.c  .generated_files/flags/default/95f40a4a246c31e900cc042090c522ce062accca .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o Source/vl53/vl53l0x_api_calibration.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o: Source/vl53/vl53l0x_api_core.c  .generated_files/flags/default/713543bcb7687a4322099985c198ce26d43cfbc0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o Source/vl53/vl53l0x_api_core.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o: Source/vl53/vl53l0x_api_strings.c  .generated_files/flags/default/91feb26203c67fef9b1f44d35efcb5b8048dde45 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o Source/vl53/vl53l0x_api_strings.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_platform.o: Source/vl53/vl53l0x_platform.c  .generated_files/flags/default/93fd2eeddd568b9719fc796c5a8b3db37f07694c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_platform.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o Source/vl53/vl53l0x_platform.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/usr_vl53_main.o: Source/vl53/usr_vl53_main.c  .generated_files/flags/default/90d24ec51fcd8f3eeee3cd497c19a96d13a11573 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/usr_vl53_main.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/usr_vl53_main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/usr_vl53_main.o.d" -o ${OBJECTDIR}/Source/vl53/usr_vl53_main.o Source/vl53/usr_vl53_main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/FreeRTOS_CLICKER2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/FreeRTOS_CLICKER2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/FreeRTOS_CLICKER2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/FreeRTOS_CLICKER2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/FreeRTOS_CLICKER2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
