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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/emArkenoid.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/emArkenoid.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Dogm128x64/bitmap/ball.o ${OBJECTDIR}/Dogm128x64/BoldFont.o ${OBJECTDIR}/Dogm128x64/dogm.o ${OBJECTDIR}/Dogm128x64/dogmBuffer.o ${OBJECTDIR}/game/game.o ${OBJECTDIR}/ioTree/ioTree.o ${OBJECTDIR}/configuration_bits.o ${OBJECTDIR}/interrupts.o ${OBJECTDIR}/main.o ${OBJECTDIR}/system.o ${OBJECTDIR}/traps.o ${OBJECTDIR}/user.o ${OBJECTDIR}/emMalloc.o ${OBJECTDIR}/game/collision.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Dogm128x64/bitmap/ball.o.d ${OBJECTDIR}/Dogm128x64/BoldFont.o.d ${OBJECTDIR}/Dogm128x64/dogm.o.d ${OBJECTDIR}/Dogm128x64/dogmBuffer.o.d ${OBJECTDIR}/game/game.o.d ${OBJECTDIR}/ioTree/ioTree.o.d ${OBJECTDIR}/configuration_bits.o.d ${OBJECTDIR}/interrupts.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/system.o.d ${OBJECTDIR}/traps.o.d ${OBJECTDIR}/user.o.d ${OBJECTDIR}/emMalloc.o.d ${OBJECTDIR}/game/collision.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Dogm128x64/bitmap/ball.o ${OBJECTDIR}/Dogm128x64/BoldFont.o ${OBJECTDIR}/Dogm128x64/dogm.o ${OBJECTDIR}/Dogm128x64/dogmBuffer.o ${OBJECTDIR}/game/game.o ${OBJECTDIR}/ioTree/ioTree.o ${OBJECTDIR}/configuration_bits.o ${OBJECTDIR}/interrupts.o ${OBJECTDIR}/main.o ${OBJECTDIR}/system.o ${OBJECTDIR}/traps.o ${OBJECTDIR}/user.o ${OBJECTDIR}/emMalloc.o ${OBJECTDIR}/game/collision.o


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/emArkenoid.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ64GB002
MP_LINKER_FILE_OPTION=,--script="app_hid_boot_p24FJ64GB002.gld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Dogm128x64/bitmap/ball.o: Dogm128x64/bitmap/ball.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Dogm128x64/bitmap 
	@${RM} ${OBJECTDIR}/Dogm128x64/bitmap/ball.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Dogm128x64/bitmap/ball.c  -o ${OBJECTDIR}/Dogm128x64/bitmap/ball.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Dogm128x64/bitmap/ball.o.d"        -g -D__DEBUG   -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Dogm128x64/bitmap/ball.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Dogm128x64/BoldFont.o: Dogm128x64/BoldFont.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Dogm128x64 
	@${RM} ${OBJECTDIR}/Dogm128x64/BoldFont.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Dogm128x64/BoldFont.c  -o ${OBJECTDIR}/Dogm128x64/BoldFont.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Dogm128x64/BoldFont.o.d"        -g -D__DEBUG   -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Dogm128x64/BoldFont.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Dogm128x64/dogm.o: Dogm128x64/dogm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Dogm128x64 
	@${RM} ${OBJECTDIR}/Dogm128x64/dogm.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Dogm128x64/dogm.c  -o ${OBJECTDIR}/Dogm128x64/dogm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Dogm128x64/dogm.o.d"        -g -D__DEBUG   -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Dogm128x64/dogm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Dogm128x64/dogmBuffer.o: Dogm128x64/dogmBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Dogm128x64 
	@${RM} ${OBJECTDIR}/Dogm128x64/dogmBuffer.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Dogm128x64/dogmBuffer.c  -o ${OBJECTDIR}/Dogm128x64/dogmBuffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Dogm128x64/dogmBuffer.o.d"        -g -D__DEBUG   -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Dogm128x64/dogmBuffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/game/game.o: game/game.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/game 
	@${RM} ${OBJECTDIR}/game/game.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  game/game.c  -o ${OBJECTDIR}/game/game.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/game/game.o.d"        -g -D__DEBUG   -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/game/game.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ioTree/ioTree.o: ioTree/ioTree.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ioTree 
	@${RM} ${OBJECTDIR}/ioTree/ioTree.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ioTree/ioTree.c  -o ${OBJECTDIR}/ioTree/ioTree.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ioTree/ioTree.o.d"        -g -D__DEBUG   -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/ioTree/ioTree.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/configuration_bits.o: configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/configuration_bits.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  configuration_bits.c  -o ${OBJECTDIR}/configuration_bits.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/configuration_bits.o.d"        -g -D__DEBUG   -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/configuration_bits.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/interrupts.o: interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/interrupts.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  interrupts.c  -o ${OBJECTDIR}/interrupts.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/interrupts.o.d"        -g -D__DEBUG   -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/interrupts.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"        -g -D__DEBUG   -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/system.o: system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/system.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  system.c  -o ${OBJECTDIR}/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/system.o.d"        -g -D__DEBUG   -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/system.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/traps.o: traps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/traps.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  traps.c  -o ${OBJECTDIR}/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/traps.o.d"        -g -D__DEBUG   -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/traps.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/user.o: user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/user.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  user.c  -o ${OBJECTDIR}/user.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/user.o.d"        -g -D__DEBUG   -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/user.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/emMalloc.o: emMalloc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/emMalloc.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  emMalloc.c  -o ${OBJECTDIR}/emMalloc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/emMalloc.o.d"        -g -D__DEBUG   -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/emMalloc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/game/collision.o: game/collision.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/game 
	@${RM} ${OBJECTDIR}/game/collision.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  game/collision.c  -o ${OBJECTDIR}/game/collision.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/game/collision.o.d"        -g -D__DEBUG   -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/game/collision.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/Dogm128x64/bitmap/ball.o: Dogm128x64/bitmap/ball.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Dogm128x64/bitmap 
	@${RM} ${OBJECTDIR}/Dogm128x64/bitmap/ball.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Dogm128x64/bitmap/ball.c  -o ${OBJECTDIR}/Dogm128x64/bitmap/ball.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Dogm128x64/bitmap/ball.o.d"        -g -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Dogm128x64/bitmap/ball.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Dogm128x64/BoldFont.o: Dogm128x64/BoldFont.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Dogm128x64 
	@${RM} ${OBJECTDIR}/Dogm128x64/BoldFont.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Dogm128x64/BoldFont.c  -o ${OBJECTDIR}/Dogm128x64/BoldFont.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Dogm128x64/BoldFont.o.d"        -g -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Dogm128x64/BoldFont.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Dogm128x64/dogm.o: Dogm128x64/dogm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Dogm128x64 
	@${RM} ${OBJECTDIR}/Dogm128x64/dogm.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Dogm128x64/dogm.c  -o ${OBJECTDIR}/Dogm128x64/dogm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Dogm128x64/dogm.o.d"        -g -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Dogm128x64/dogm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Dogm128x64/dogmBuffer.o: Dogm128x64/dogmBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Dogm128x64 
	@${RM} ${OBJECTDIR}/Dogm128x64/dogmBuffer.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Dogm128x64/dogmBuffer.c  -o ${OBJECTDIR}/Dogm128x64/dogmBuffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Dogm128x64/dogmBuffer.o.d"        -g -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Dogm128x64/dogmBuffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/game/game.o: game/game.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/game 
	@${RM} ${OBJECTDIR}/game/game.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  game/game.c  -o ${OBJECTDIR}/game/game.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/game/game.o.d"        -g -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/game/game.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ioTree/ioTree.o: ioTree/ioTree.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ioTree 
	@${RM} ${OBJECTDIR}/ioTree/ioTree.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ioTree/ioTree.c  -o ${OBJECTDIR}/ioTree/ioTree.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ioTree/ioTree.o.d"        -g -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/ioTree/ioTree.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/configuration_bits.o: configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/configuration_bits.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  configuration_bits.c  -o ${OBJECTDIR}/configuration_bits.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/configuration_bits.o.d"        -g -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/configuration_bits.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/interrupts.o: interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/interrupts.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  interrupts.c  -o ${OBJECTDIR}/interrupts.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/interrupts.o.d"        -g -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/interrupts.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/system.o: system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/system.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  system.c  -o ${OBJECTDIR}/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/system.o.d"        -g -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/system.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/traps.o: traps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/traps.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  traps.c  -o ${OBJECTDIR}/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/traps.o.d"        -g -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/traps.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/user.o: user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/user.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  user.c  -o ${OBJECTDIR}/user.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/user.o.d"        -g -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/user.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/emMalloc.o: emMalloc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/emMalloc.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  emMalloc.c  -o ${OBJECTDIR}/emMalloc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/emMalloc.o.d"        -g -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/emMalloc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/game/collision.o: game/collision.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/game 
	@${RM} ${OBJECTDIR}/game/collision.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  game/collision.c  -o ${OBJECTDIR}/game/collision.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/game/collision.o.d"        -g -omf=elf -D_DEBUG -O0 -I"Dogm128x64" -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/game/collision.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/emArkenoid.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    app_hid_boot_p24FJ64GB002.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/emArkenoid.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG   -omf=elf -D_DEBUG -Wl,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/emArkenoid.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   app_hid_boot_p24FJ64GB002.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/emArkenoid.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -D_DEBUG -Wl,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/emArkenoid.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf 
	
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
