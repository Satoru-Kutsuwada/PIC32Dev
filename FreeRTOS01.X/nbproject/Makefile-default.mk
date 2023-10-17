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
FINAL_IMAGE=${DISTDIR}/FreeRTOS01.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/FreeRTOS01.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=Source/main.c Source/usr_tools.c Source/FreeRTOS/RegisterTestTasks.S Source/FreeRTOS/heap_4.c Source/FreeRTOS/list.c Source/FreeRTOS/port.c Source/FreeRTOS/port_asm.S Source/FreeRTOS/queue.c Source/FreeRTOS/tasks.c Source/ConfigPerformance.c Source/vl53/usr_i2cMain.c Source/vl53/vl53l0x_api.c Source/vl53/vl53l0x_api_calibration.c Source/vl53/vl53l0x_api_core.c Source/vl53/vl53l0x_api_strings.c Source/vl53/vl53l0x_platform.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Source/main.o ${OBJECTDIR}/Source/usr_tools.o ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o ${OBJECTDIR}/Source/FreeRTOS/heap_4.o ${OBJECTDIR}/Source/FreeRTOS/list.o ${OBJECTDIR}/Source/FreeRTOS/port.o ${OBJECTDIR}/Source/FreeRTOS/port_asm.o ${OBJECTDIR}/Source/FreeRTOS/queue.o ${OBJECTDIR}/Source/FreeRTOS/tasks.o ${OBJECTDIR}/Source/ConfigPerformance.o ${OBJECTDIR}/Source/vl53/usr_i2cMain.o ${OBJECTDIR}/Source/vl53/vl53l0x_api.o ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Source/main.o.d ${OBJECTDIR}/Source/usr_tools.o.d ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.d ${OBJECTDIR}/Source/FreeRTOS/heap_4.o.d ${OBJECTDIR}/Source/FreeRTOS/list.o.d ${OBJECTDIR}/Source/FreeRTOS/port.o.d ${OBJECTDIR}/Source/FreeRTOS/port_asm.o.d ${OBJECTDIR}/Source/FreeRTOS/queue.o.d ${OBJECTDIR}/Source/FreeRTOS/tasks.o.d ${OBJECTDIR}/Source/ConfigPerformance.o.d ${OBJECTDIR}/Source/vl53/usr_i2cMain.o.d ${OBJECTDIR}/Source/vl53/vl53l0x_api.o.d ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o.d ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o.d ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o.d ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Source/main.o ${OBJECTDIR}/Source/usr_tools.o ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o ${OBJECTDIR}/Source/FreeRTOS/heap_4.o ${OBJECTDIR}/Source/FreeRTOS/list.o ${OBJECTDIR}/Source/FreeRTOS/port.o ${OBJECTDIR}/Source/FreeRTOS/port_asm.o ${OBJECTDIR}/Source/FreeRTOS/queue.o ${OBJECTDIR}/Source/FreeRTOS/tasks.o ${OBJECTDIR}/Source/ConfigPerformance.o ${OBJECTDIR}/Source/vl53/usr_i2cMain.o ${OBJECTDIR}/Source/vl53/vl53l0x_api.o ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o

# Source Files
SOURCEFILES=Source/main.c Source/usr_tools.c Source/FreeRTOS/RegisterTestTasks.S Source/FreeRTOS/heap_4.c Source/FreeRTOS/list.c Source/FreeRTOS/port.c Source/FreeRTOS/port_asm.S Source/FreeRTOS/queue.c Source/FreeRTOS/tasks.c Source/ConfigPerformance.c Source/vl53/usr_i2cMain.c Source/vl53/vl53l0x_api.c Source/vl53/vl53l0x_api_calibration.c Source/vl53/vl53l0x_api_core.c Source/vl53/vl53l0x_api_strings.c Source/vl53/vl53l0x_platform.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/FreeRTOS01.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX534F064H
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o: Source/FreeRTOS/RegisterTestTasks.S  .generated_files/flags/default/eea15fdbdf5e91d4d619d0c73ac213a2c3fcc869 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.ok ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.d"  -o ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o Source/FreeRTOS/RegisterTestTasks.S  -DXPRJ_default=$(CND_CONF)    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.d" "${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source/FreeRTOS/port_asm.o: Source/FreeRTOS/port_asm.S  .generated_files/flags/default/11301a0cc56c0c6cf12214960c6bf98362182071 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port_asm.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port_asm.o 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port_asm.o.ok ${OBJECTDIR}/Source/FreeRTOS/port_asm.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/port_asm.o.d"  -o ${OBJECTDIR}/Source/FreeRTOS/port_asm.o Source/FreeRTOS/port_asm.S  -DXPRJ_default=$(CND_CONF)    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/Source/FreeRTOS/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/Source/FreeRTOS/port_asm.o.d" "${OBJECTDIR}/Source/FreeRTOS/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o: Source/FreeRTOS/RegisterTestTasks.S  .generated_files/flags/default/d77286c6e4a892109e79faceb21ec51d03bbfe1c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.ok ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.d"  -o ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o Source/FreeRTOS/RegisterTestTasks.S  -DXPRJ_default=$(CND_CONF)    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.asm.d",--gdwarf-2,-I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.d" "${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source/FreeRTOS/port_asm.o: Source/FreeRTOS/port_asm.S  .generated_files/flags/default/78c367b984f125b969d8b784e293c11c0bf6cf71 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
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
${OBJECTDIR}/Source/main.o: Source/main.c  .generated_files/flags/default/80d19e9ae7f0f5ab43df70e2ed5f431a64fc69b6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/main.o.d 
	@${RM} ${OBJECTDIR}/Source/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/main.o.d" -o ${OBJECTDIR}/Source/main.o Source/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/usr_tools.o: Source/usr_tools.c  .generated_files/flags/default/cc8e7e463e60e1aa1d06e2102a9d0cb0b636c2f8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/usr_tools.o.d 
	@${RM} ${OBJECTDIR}/Source/usr_tools.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/usr_tools.o.d" -o ${OBJECTDIR}/Source/usr_tools.o Source/usr_tools.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/heap_4.o: Source/FreeRTOS/heap_4.c  .generated_files/flags/default/f7160c82aee869d45c31eb18026ea16a45c48b03 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/heap_4.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/heap_4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/heap_4.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/heap_4.o Source/FreeRTOS/heap_4.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/list.o: Source/FreeRTOS/list.c  .generated_files/flags/default/1f35c41ff0a2ee16c17519de96eea074ecb4a921 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/list.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/list.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/list.o Source/FreeRTOS/list.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/port.o: Source/FreeRTOS/port.c  .generated_files/flags/default/e7dd791833d201df7351068c2234ebd3e7a720df .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/port.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/port.o Source/FreeRTOS/port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/queue.o: Source/FreeRTOS/queue.c  .generated_files/flags/default/a9d4f1f80bbf6b74dc6f5ba5400687a39ce26431 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/queue.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/queue.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/queue.o Source/FreeRTOS/queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/tasks.o: Source/FreeRTOS/tasks.c  .generated_files/flags/default/8d4d522a79b1a27cd8dfe701c9954d7db1ad380e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/tasks.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/tasks.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/tasks.o Source/FreeRTOS/tasks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/ConfigPerformance.o: Source/ConfigPerformance.c  .generated_files/flags/default/d611a44c5f90c191a7ae59e54a3e45d4b9ce02bd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/ConfigPerformance.o.d 
	@${RM} ${OBJECTDIR}/Source/ConfigPerformance.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/ConfigPerformance.o.d" -o ${OBJECTDIR}/Source/ConfigPerformance.o Source/ConfigPerformance.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/usr_i2cMain.o: Source/vl53/usr_i2cMain.c  .generated_files/flags/default/43d486593379c9ef6ba2a07653cbda850bde704c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/usr_i2cMain.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/usr_i2cMain.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/usr_i2cMain.o.d" -o ${OBJECTDIR}/Source/vl53/usr_i2cMain.o Source/vl53/usr_i2cMain.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_api.o: Source/vl53/vl53l0x_api.c  .generated_files/flags/default/6c95f0c3576a0a3abbe5538999ba10e3b5ea0876 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_api.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_api.o Source/vl53/vl53l0x_api.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o: Source/vl53/vl53l0x_api_calibration.c  .generated_files/flags/default/47a1a28f1516aec41ed4773da251e4375aabc09b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o Source/vl53/vl53l0x_api_calibration.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o: Source/vl53/vl53l0x_api_core.c  .generated_files/flags/default/8c13b8b1907f4da90b0d12d45bf80cd9b34f2a33 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o Source/vl53/vl53l0x_api_core.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o: Source/vl53/vl53l0x_api_strings.c  .generated_files/flags/default/ada10eb961b6e279a21ee2e07d44bef7c81c5913 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o Source/vl53/vl53l0x_api_strings.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_platform.o: Source/vl53/vl53l0x_platform.c  .generated_files/flags/default/2b31c71a0c92447d124ecfbac14ac2613695aa36 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_platform.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o Source/vl53/vl53l0x_platform.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/Source/main.o: Source/main.c  .generated_files/flags/default/9205707bcd31eaa888adaeeabd1340ee16b6985 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/main.o.d 
	@${RM} ${OBJECTDIR}/Source/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/main.o.d" -o ${OBJECTDIR}/Source/main.o Source/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/usr_tools.o: Source/usr_tools.c  .generated_files/flags/default/bec27a04f928d4a8beee118c3fa056eba6d54705 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/usr_tools.o.d 
	@${RM} ${OBJECTDIR}/Source/usr_tools.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/usr_tools.o.d" -o ${OBJECTDIR}/Source/usr_tools.o Source/usr_tools.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/heap_4.o: Source/FreeRTOS/heap_4.c  .generated_files/flags/default/c1db2eaac92955c4edcb24e50e1b6892cf24a40c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/heap_4.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/heap_4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/heap_4.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/heap_4.o Source/FreeRTOS/heap_4.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/list.o: Source/FreeRTOS/list.c  .generated_files/flags/default/fdbbd67eda41af1dada3ad60ad24b197d8733908 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/list.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/list.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/list.o Source/FreeRTOS/list.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/port.o: Source/FreeRTOS/port.c  .generated_files/flags/default/20bea1a7f8974494c2a23598dde74431138e7d3a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/port.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/port.o Source/FreeRTOS/port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/queue.o: Source/FreeRTOS/queue.c  .generated_files/flags/default/f17768c3b7ca5419fd6e5cdf595331f779cb0413 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/queue.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/queue.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/queue.o Source/FreeRTOS/queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/tasks.o: Source/FreeRTOS/tasks.c  .generated_files/flags/default/b42930c0d9b41c1b12bae7e63b6d9d4e10a808ee .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/tasks.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/tasks.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/tasks.o Source/FreeRTOS/tasks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/ConfigPerformance.o: Source/ConfigPerformance.c  .generated_files/flags/default/6a6f7f3ce232fcba896c55f773f0ff145c6b4ab1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/ConfigPerformance.o.d 
	@${RM} ${OBJECTDIR}/Source/ConfigPerformance.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/ConfigPerformance.o.d" -o ${OBJECTDIR}/Source/ConfigPerformance.o Source/ConfigPerformance.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/usr_i2cMain.o: Source/vl53/usr_i2cMain.c  .generated_files/flags/default/344796940b87003340720f33b30a77a75bb4a933 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/usr_i2cMain.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/usr_i2cMain.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/usr_i2cMain.o.d" -o ${OBJECTDIR}/Source/vl53/usr_i2cMain.o Source/vl53/usr_i2cMain.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_api.o: Source/vl53/vl53l0x_api.c  .generated_files/flags/default/bf1feb41aef6cb6f8d21a0d867fb3c01d5c1fbab .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_api.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_api.o Source/vl53/vl53l0x_api.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o: Source/vl53/vl53l0x_api_calibration.c  .generated_files/flags/default/722ffd8a73d219ce76acb8b01212125c2c458867 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o Source/vl53/vl53l0x_api_calibration.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o: Source/vl53/vl53l0x_api_core.c  .generated_files/flags/default/4de82cb949aef505636b78006f65aa7ac236409e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o Source/vl53/vl53l0x_api_core.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o: Source/vl53/vl53l0x_api_strings.c  .generated_files/flags/default/ccaa734df465942d74a10110b19fe6c4fb228e17 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o Source/vl53/vl53l0x_api_strings.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_platform.o: Source/vl53/vl53l0x_platform.c  .generated_files/flags/default/ec9c529da3c55fac4b545d6246795c192c874691 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -I"Source/vl53/inc" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_platform.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o Source/vl53/vl53l0x_platform.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/FreeRTOS01.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/FreeRTOS01.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/FreeRTOS01.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/FreeRTOS01.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/FreeRTOS01.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
