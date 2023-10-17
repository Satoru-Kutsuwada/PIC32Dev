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
SOURCEFILES_QUOTED_IF_SPACED=Source/main.c Source/usr_tools.c Source/FreeRTOS/RegisterTestTasks.S Source/FreeRTOS/heap_4.c Source/FreeRTOS/list.c Source/FreeRTOS/port.c Source/FreeRTOS/port_asm.S Source/FreeRTOS/queue.c Source/FreeRTOS/tasks.c Source/ConfigPerformance.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Source/main.o ${OBJECTDIR}/Source/usr_tools.o ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o ${OBJECTDIR}/Source/FreeRTOS/heap_4.o ${OBJECTDIR}/Source/FreeRTOS/list.o ${OBJECTDIR}/Source/FreeRTOS/port.o ${OBJECTDIR}/Source/FreeRTOS/port_asm.o ${OBJECTDIR}/Source/FreeRTOS/queue.o ${OBJECTDIR}/Source/FreeRTOS/tasks.o ${OBJECTDIR}/Source/ConfigPerformance.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Source/main.o.d ${OBJECTDIR}/Source/usr_tools.o.d ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.d ${OBJECTDIR}/Source/FreeRTOS/heap_4.o.d ${OBJECTDIR}/Source/FreeRTOS/list.o.d ${OBJECTDIR}/Source/FreeRTOS/port.o.d ${OBJECTDIR}/Source/FreeRTOS/port_asm.o.d ${OBJECTDIR}/Source/FreeRTOS/queue.o.d ${OBJECTDIR}/Source/FreeRTOS/tasks.o.d ${OBJECTDIR}/Source/ConfigPerformance.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Source/main.o ${OBJECTDIR}/Source/usr_tools.o ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o ${OBJECTDIR}/Source/FreeRTOS/heap_4.o ${OBJECTDIR}/Source/FreeRTOS/list.o ${OBJECTDIR}/Source/FreeRTOS/port.o ${OBJECTDIR}/Source/FreeRTOS/port_asm.o ${OBJECTDIR}/Source/FreeRTOS/queue.o ${OBJECTDIR}/Source/FreeRTOS/tasks.o ${OBJECTDIR}/Source/ConfigPerformance.o

# Source Files
SOURCEFILES=Source/main.c Source/usr_tools.c Source/FreeRTOS/RegisterTestTasks.S Source/FreeRTOS/heap_4.c Source/FreeRTOS/list.c Source/FreeRTOS/port.c Source/FreeRTOS/port_asm.S Source/FreeRTOS/queue.c Source/FreeRTOS/tasks.c Source/ConfigPerformance.c



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
${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o: Source/FreeRTOS/RegisterTestTasks.S  .generated_files/flags/default/2771438d5793d0fc8cec8efe36bcc541f0e58039 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.ok ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.d"  -o ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o Source/FreeRTOS/RegisterTestTasks.S  -DXPRJ_default=$(CND_CONF)    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,-I"." -I"Source" -I"Source/FreeRTOS/include" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.d" "${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source/FreeRTOS/port_asm.o: Source/FreeRTOS/port_asm.S  .generated_files/flags/default/c26a62013cd5548a5a2ccc9d22eecf76b2456dff .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port_asm.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port_asm.o 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port_asm.o.ok ${OBJECTDIR}/Source/FreeRTOS/port_asm.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/port_asm.o.d"  -o ${OBJECTDIR}/Source/FreeRTOS/port_asm.o Source/FreeRTOS/port_asm.S  -DXPRJ_default=$(CND_CONF)    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/Source/FreeRTOS/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,-I"." -I"Source" -I"Source/FreeRTOS/include" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/Source/FreeRTOS/port_asm.o.d" "${OBJECTDIR}/Source/FreeRTOS/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o: Source/FreeRTOS/RegisterTestTasks.S  .generated_files/flags/default/afe8f5bdd291bf05ef624bafe89bffef4f7f7e5f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.ok ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.d"  -o ${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o Source/FreeRTOS/RegisterTestTasks.S  -DXPRJ_default=$(CND_CONF)    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.asm.d",--gdwarf-2,-I"." -I"Source" -I"Source/FreeRTOS/include" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.d" "${OBJECTDIR}/Source/FreeRTOS/RegisterTestTasks.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Source/FreeRTOS/port_asm.o: Source/FreeRTOS/port_asm.S  .generated_files/flags/default/b4ff80139e615163a414e2ecec0f685ef7e2ff96 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port_asm.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port_asm.o 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port_asm.o.ok ${OBJECTDIR}/Source/FreeRTOS/port_asm.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/port_asm.o.d"  -o ${OBJECTDIR}/Source/FreeRTOS/port_asm.o Source/FreeRTOS/port_asm.S  -DXPRJ_default=$(CND_CONF)    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/Source/FreeRTOS/port_asm.o.asm.d",--gdwarf-2,-I"." -I"Source" -I"Source/FreeRTOS/include" -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/Source/FreeRTOS/port_asm.o.d" "${OBJECTDIR}/Source/FreeRTOS/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Source/main.o: Source/main.c  .generated_files/flags/default/1e9ca7505da154e4f072094f91c41ac34bd899d1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/main.o.d 
	@${RM} ${OBJECTDIR}/Source/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/main.o.d" -o ${OBJECTDIR}/Source/main.o Source/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/usr_tools.o: Source/usr_tools.c  .generated_files/flags/default/ddd0c41fc18f815769e860003249ff7e3daea72 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/usr_tools.o.d 
	@${RM} ${OBJECTDIR}/Source/usr_tools.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/usr_tools.o.d" -o ${OBJECTDIR}/Source/usr_tools.o Source/usr_tools.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/heap_4.o: Source/FreeRTOS/heap_4.c  .generated_files/flags/default/ae0acd46e67404baf133917741a357d09dcbfac4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/heap_4.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/heap_4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/heap_4.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/heap_4.o Source/FreeRTOS/heap_4.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/list.o: Source/FreeRTOS/list.c  .generated_files/flags/default/3d9cb1cf03daf916948c370f953346a93603bd2c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/list.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/list.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/list.o Source/FreeRTOS/list.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/port.o: Source/FreeRTOS/port.c  .generated_files/flags/default/5bffe1a55116209685979d8d5bde41e0dc4bee2a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/port.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/port.o Source/FreeRTOS/port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/queue.o: Source/FreeRTOS/queue.c  .generated_files/flags/default/7018486217f86e6b3d4750fb8e5b56fd396111d9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/queue.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/queue.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/queue.o Source/FreeRTOS/queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/tasks.o: Source/FreeRTOS/tasks.c  .generated_files/flags/default/a3dc44f47f2f092a338589cccc73b3881527f359 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/tasks.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/tasks.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/tasks.o Source/FreeRTOS/tasks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/ConfigPerformance.o: Source/ConfigPerformance.c  .generated_files/flags/default/b6bb61d3a1cc71fae00170fb1e3b96185786252 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/ConfigPerformance.o.d 
	@${RM} ${OBJECTDIR}/Source/ConfigPerformance.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/ConfigPerformance.o.d" -o ${OBJECTDIR}/Source/ConfigPerformance.o Source/ConfigPerformance.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/Source/main.o: Source/main.c  .generated_files/flags/default/fb5d07845c26e064454d7756ab4845f9ff63cb36 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/main.o.d 
	@${RM} ${OBJECTDIR}/Source/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/main.o.d" -o ${OBJECTDIR}/Source/main.o Source/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/usr_tools.o: Source/usr_tools.c  .generated_files/flags/default/7c88b9114cf5a3dd2f98e1ce560d16712e10351b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/usr_tools.o.d 
	@${RM} ${OBJECTDIR}/Source/usr_tools.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/usr_tools.o.d" -o ${OBJECTDIR}/Source/usr_tools.o Source/usr_tools.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/heap_4.o: Source/FreeRTOS/heap_4.c  .generated_files/flags/default/469188934df09e2eff72f6074ce78472e37742a0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/heap_4.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/heap_4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/heap_4.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/heap_4.o Source/FreeRTOS/heap_4.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/list.o: Source/FreeRTOS/list.c  .generated_files/flags/default/b126d65c02fe8fd2e9813e37f4ed7414ce44bc69 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/list.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/list.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/list.o Source/FreeRTOS/list.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/port.o: Source/FreeRTOS/port.c  .generated_files/flags/default/7716f03e0a9e339f9153bcb9d793a2775313c856 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/port.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/port.o Source/FreeRTOS/port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/queue.o: Source/FreeRTOS/queue.c  .generated_files/flags/default/7f2a6996a8488c76134801eaf455aebd989c9837 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/queue.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/queue.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/queue.o Source/FreeRTOS/queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/FreeRTOS/tasks.o: Source/FreeRTOS/tasks.c  .generated_files/flags/default/d59dd1da050e077b98b78e59a9614d7e9f8129be .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/FreeRTOS" 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/tasks.o.d 
	@${RM} ${OBJECTDIR}/Source/FreeRTOS/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/FreeRTOS/tasks.o.d" -o ${OBJECTDIR}/Source/FreeRTOS/tasks.o Source/FreeRTOS/tasks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/ConfigPerformance.o: Source/ConfigPerformance.c  .generated_files/flags/default/e7415a36a76085373ed4883fbcaeecb62ca61697 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/ConfigPerformance.o.d 
	@${RM} ${OBJECTDIR}/Source/ConfigPerformance.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/FreeRTOS/include" -fno-common -MP -MMD -MF "${OBJECTDIR}/Source/ConfigPerformance.o.d" -o ${OBJECTDIR}/Source/ConfigPerformance.o Source/ConfigPerformance.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
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
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/FreeRTOS01.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
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
