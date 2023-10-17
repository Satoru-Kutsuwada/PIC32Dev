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
FINAL_IMAGE=${DISTDIR}/SimpleFunc_TEST02.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/SimpleFunc_TEST02.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=Source/main.c Source/usr_tools.c Source/vl53/usr_i2cMain.c Source/vl53/vl53l0x_api.c Source/vl53/vl53l0x_api_calibration.c Source/vl53/vl53l0x_api_core.c Source/vl53/vl53l0x_api_strings.c Source/vl53/vl53l0x_platform.c Source/vl53/usr_vl53_main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Source/main.o ${OBJECTDIR}/Source/usr_tools.o ${OBJECTDIR}/Source/vl53/usr_i2cMain.o ${OBJECTDIR}/Source/vl53/vl53l0x_api.o ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o ${OBJECTDIR}/Source/vl53/usr_vl53_main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Source/main.o.d ${OBJECTDIR}/Source/usr_tools.o.d ${OBJECTDIR}/Source/vl53/usr_i2cMain.o.d ${OBJECTDIR}/Source/vl53/vl53l0x_api.o.d ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o.d ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o.d ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o.d ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o.d ${OBJECTDIR}/Source/vl53/usr_vl53_main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Source/main.o ${OBJECTDIR}/Source/usr_tools.o ${OBJECTDIR}/Source/vl53/usr_i2cMain.o ${OBJECTDIR}/Source/vl53/vl53l0x_api.o ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o ${OBJECTDIR}/Source/vl53/usr_vl53_main.o

# Source Files
SOURCEFILES=Source/main.c Source/usr_tools.c Source/vl53/usr_i2cMain.c Source/vl53/vl53l0x_api.c Source/vl53/vl53l0x_api_calibration.c Source/vl53/vl53l0x_api_core.c Source/vl53/vl53l0x_api_strings.c Source/vl53/vl53l0x_platform.c Source/vl53/usr_vl53_main.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/SimpleFunc_TEST02.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Source/main.o: Source/main.c  .generated_files/flags/default/2dbeedb9f17ab6c23fa8cb875756a09b44bcab42 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/main.o.d 
	@${RM} ${OBJECTDIR}/Source/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/vl53/inc" -MP -MMD -MF "${OBJECTDIR}/Source/main.o.d" -o ${OBJECTDIR}/Source/main.o Source/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/usr_tools.o: Source/usr_tools.c  .generated_files/flags/default/d218dfd5f31a9aeaf4993d8592a92b6f043756fc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/usr_tools.o.d 
	@${RM} ${OBJECTDIR}/Source/usr_tools.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/vl53/inc" -MP -MMD -MF "${OBJECTDIR}/Source/usr_tools.o.d" -o ${OBJECTDIR}/Source/usr_tools.o Source/usr_tools.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/usr_i2cMain.o: Source/vl53/usr_i2cMain.c  .generated_files/flags/default/f00c5e00ee8e3e068965dcca6f540adc46747ae0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/usr_i2cMain.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/usr_i2cMain.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/vl53/inc" -MP -MMD -MF "${OBJECTDIR}/Source/vl53/usr_i2cMain.o.d" -o ${OBJECTDIR}/Source/vl53/usr_i2cMain.o Source/vl53/usr_i2cMain.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_api.o: Source/vl53/vl53l0x_api.c  .generated_files/flags/default/1b4e974c5445db6ad6478cd678cd9d942b7b881c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/vl53/inc" -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_api.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_api.o Source/vl53/vl53l0x_api.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o: Source/vl53/vl53l0x_api_calibration.c  .generated_files/flags/default/df75cc850e64035f13039c8208da5f8f27e6e361 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/vl53/inc" -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o Source/vl53/vl53l0x_api_calibration.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o: Source/vl53/vl53l0x_api_core.c  .generated_files/flags/default/46d2486e729f24c1520cb468e2b213ee4ea2d523 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/vl53/inc" -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o Source/vl53/vl53l0x_api_core.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o: Source/vl53/vl53l0x_api_strings.c  .generated_files/flags/default/c9c47449106a750c0da500be723f3f98389ce602 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/vl53/inc" -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o Source/vl53/vl53l0x_api_strings.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_platform.o: Source/vl53/vl53l0x_platform.c  .generated_files/flags/default/1a2408b284ba98b8dbc83e0031f8417251004fd1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/vl53/inc" -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_platform.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o Source/vl53/vl53l0x_platform.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/usr_vl53_main.o: Source/vl53/usr_vl53_main.c  .generated_files/flags/default/da9cd69bae4ae195498ff34c801d33caebdd73b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/usr_vl53_main.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/usr_vl53_main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/vl53/inc" -MP -MMD -MF "${OBJECTDIR}/Source/vl53/usr_vl53_main.o.d" -o ${OBJECTDIR}/Source/vl53/usr_vl53_main.o Source/vl53/usr_vl53_main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/Source/main.o: Source/main.c  .generated_files/flags/default/3548bc21ba116378e19610a4e9bb39b4754ba5c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/main.o.d 
	@${RM} ${OBJECTDIR}/Source/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/vl53/inc" -MP -MMD -MF "${OBJECTDIR}/Source/main.o.d" -o ${OBJECTDIR}/Source/main.o Source/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/usr_tools.o: Source/usr_tools.c  .generated_files/flags/default/a02fea7691cdca3b8f5a835206de7cb104ac78c4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/usr_tools.o.d 
	@${RM} ${OBJECTDIR}/Source/usr_tools.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/vl53/inc" -MP -MMD -MF "${OBJECTDIR}/Source/usr_tools.o.d" -o ${OBJECTDIR}/Source/usr_tools.o Source/usr_tools.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/usr_i2cMain.o: Source/vl53/usr_i2cMain.c  .generated_files/flags/default/efb106dea91264bb4d977d085f012212f24005eb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/usr_i2cMain.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/usr_i2cMain.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/vl53/inc" -MP -MMD -MF "${OBJECTDIR}/Source/vl53/usr_i2cMain.o.d" -o ${OBJECTDIR}/Source/vl53/usr_i2cMain.o Source/vl53/usr_i2cMain.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_api.o: Source/vl53/vl53l0x_api.c  .generated_files/flags/default/7bfa624935c9413b8a00a3be1b884f652a14c92e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/vl53/inc" -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_api.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_api.o Source/vl53/vl53l0x_api.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o: Source/vl53/vl53l0x_api_calibration.c  .generated_files/flags/default/7ecf55929c99aabd0110fcf04324579cb90f33da .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/vl53/inc" -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_api_calibration.o Source/vl53/vl53l0x_api_calibration.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o: Source/vl53/vl53l0x_api_core.c  .generated_files/flags/default/bbe0a856e05224705399146c42386c0e10538f33 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/vl53/inc" -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_api_core.o Source/vl53/vl53l0x_api_core.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o: Source/vl53/vl53l0x_api_strings.c  .generated_files/flags/default/cddb5c406018b8b70eb72ba6e2283444db290dfd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/vl53/inc" -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_api_strings.o Source/vl53/vl53l0x_api_strings.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/vl53l0x_platform.o: Source/vl53/vl53l0x_platform.c  .generated_files/flags/default/3de6aa50e44f117c2e0f8251e0c5e9974261be67 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/vl53/inc" -MP -MMD -MF "${OBJECTDIR}/Source/vl53/vl53l0x_platform.o.d" -o ${OBJECTDIR}/Source/vl53/vl53l0x_platform.o Source/vl53/vl53l0x_platform.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Source/vl53/usr_vl53_main.o: Source/vl53/usr_vl53_main.c  .generated_files/flags/default/50f3341dec61f08df8f2b873e3816f574c1f81c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source/vl53" 
	@${RM} ${OBJECTDIR}/Source/vl53/usr_vl53_main.o.d 
	@${RM} ${OBJECTDIR}/Source/vl53/usr_vl53_main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"." -I"Source" -I"Source/vl53/inc" -MP -MMD -MF "${OBJECTDIR}/Source/vl53/usr_vl53_main.o.d" -o ${OBJECTDIR}/Source/vl53/usr_vl53_main.o Source/vl53/usr_vl53_main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/SimpleFunc_TEST02.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/SimpleFunc_TEST02.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=1024,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/SimpleFunc_TEST02.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/SimpleFunc_TEST02.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=1024,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/SimpleFunc_TEST02.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
