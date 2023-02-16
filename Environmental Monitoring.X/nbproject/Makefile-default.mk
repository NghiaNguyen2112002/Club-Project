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
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=${DISTDIR}/Environmental_Monitoring.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=${DISTDIR}/Environmental_Monitoring.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=button_matrix.c i2c_ds1307.c interrupt.c timer.c lcd.c main.c DHT11.c global.c fsm.c uart.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/button_matrix.o ${OBJECTDIR}/i2c_ds1307.o ${OBJECTDIR}/interrupt.o ${OBJECTDIR}/timer.o ${OBJECTDIR}/lcd.o ${OBJECTDIR}/main.o ${OBJECTDIR}/DHT11.o ${OBJECTDIR}/global.o ${OBJECTDIR}/fsm.o ${OBJECTDIR}/uart.o
POSSIBLE_DEPFILES=${OBJECTDIR}/button_matrix.o.d ${OBJECTDIR}/i2c_ds1307.o.d ${OBJECTDIR}/interrupt.o.d ${OBJECTDIR}/timer.o.d ${OBJECTDIR}/lcd.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/DHT11.o.d ${OBJECTDIR}/global.o.d ${OBJECTDIR}/fsm.o.d ${OBJECTDIR}/uart.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/button_matrix.o ${OBJECTDIR}/i2c_ds1307.o ${OBJECTDIR}/interrupt.o ${OBJECTDIR}/timer.o ${OBJECTDIR}/lcd.o ${OBJECTDIR}/main.o ${OBJECTDIR}/DHT11.o ${OBJECTDIR}/global.o ${OBJECTDIR}/fsm.o ${OBJECTDIR}/uart.o

# Source Files
SOURCEFILES=button_matrix.c i2c_ds1307.c interrupt.c timer.c lcd.c main.c DHT11.c global.c fsm.c uart.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Environmental_Monitoring.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F4620
MP_PROCESSOR_OPTION_LD=18f4620
MP_LINKER_DEBUG_OPTION=  -u_DEBUGSTACK
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/button_matrix.o: button_matrix.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/button_matrix.o.d 
	@${RM} ${OBJECTDIR}/button_matrix.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/button_matrix.o   button_matrix.c 
	@${DEP_GEN} -d ${OBJECTDIR}/button_matrix.o 
	@${FIXDEPS} "${OBJECTDIR}/button_matrix.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/i2c_ds1307.o: i2c_ds1307.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/i2c_ds1307.o.d 
	@${RM} ${OBJECTDIR}/i2c_ds1307.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/i2c_ds1307.o   i2c_ds1307.c 
	@${DEP_GEN} -d ${OBJECTDIR}/i2c_ds1307.o 
	@${FIXDEPS} "${OBJECTDIR}/i2c_ds1307.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/interrupt.o: interrupt.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupt.o.d 
	@${RM} ${OBJECTDIR}/interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/interrupt.o   interrupt.c 
	@${DEP_GEN} -d ${OBJECTDIR}/interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/timer.o: timer.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timer.o.d 
	@${RM} ${OBJECTDIR}/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/timer.o   timer.c 
	@${DEP_GEN} -d ${OBJECTDIR}/timer.o 
	@${FIXDEPS} "${OBJECTDIR}/timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/lcd.o: lcd.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lcd.o.d 
	@${RM} ${OBJECTDIR}/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lcd.o   lcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lcd.o 
	@${FIXDEPS} "${OBJECTDIR}/lcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/main.o   main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/DHT11.o: DHT11.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DHT11.o.d 
	@${RM} ${OBJECTDIR}/DHT11.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/DHT11.o   DHT11.c 
	@${DEP_GEN} -d ${OBJECTDIR}/DHT11.o 
	@${FIXDEPS} "${OBJECTDIR}/DHT11.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/global.o: global.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/global.o.d 
	@${RM} ${OBJECTDIR}/global.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/global.o   global.c 
	@${DEP_GEN} -d ${OBJECTDIR}/global.o 
	@${FIXDEPS} "${OBJECTDIR}/global.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fsm.o: fsm.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fsm.o.d 
	@${RM} ${OBJECTDIR}/fsm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fsm.o   fsm.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fsm.o 
	@${FIXDEPS} "${OBJECTDIR}/fsm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/uart.o: uart.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart.o.d 
	@${RM} ${OBJECTDIR}/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG  -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/uart.o   uart.c 
	@${DEP_GEN} -d ${OBJECTDIR}/uart.o 
	@${FIXDEPS} "${OBJECTDIR}/uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/button_matrix.o: button_matrix.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/button_matrix.o.d 
	@${RM} ${OBJECTDIR}/button_matrix.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/button_matrix.o   button_matrix.c 
	@${DEP_GEN} -d ${OBJECTDIR}/button_matrix.o 
	@${FIXDEPS} "${OBJECTDIR}/button_matrix.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/i2c_ds1307.o: i2c_ds1307.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/i2c_ds1307.o.d 
	@${RM} ${OBJECTDIR}/i2c_ds1307.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/i2c_ds1307.o   i2c_ds1307.c 
	@${DEP_GEN} -d ${OBJECTDIR}/i2c_ds1307.o 
	@${FIXDEPS} "${OBJECTDIR}/i2c_ds1307.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/interrupt.o: interrupt.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupt.o.d 
	@${RM} ${OBJECTDIR}/interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/interrupt.o   interrupt.c 
	@${DEP_GEN} -d ${OBJECTDIR}/interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/timer.o: timer.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timer.o.d 
	@${RM} ${OBJECTDIR}/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/timer.o   timer.c 
	@${DEP_GEN} -d ${OBJECTDIR}/timer.o 
	@${FIXDEPS} "${OBJECTDIR}/timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/lcd.o: lcd.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lcd.o.d 
	@${RM} ${OBJECTDIR}/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/lcd.o   lcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/lcd.o 
	@${FIXDEPS} "${OBJECTDIR}/lcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/main.o   main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/DHT11.o: DHT11.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DHT11.o.d 
	@${RM} ${OBJECTDIR}/DHT11.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/DHT11.o   DHT11.c 
	@${DEP_GEN} -d ${OBJECTDIR}/DHT11.o 
	@${FIXDEPS} "${OBJECTDIR}/DHT11.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/global.o: global.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/global.o.d 
	@${RM} ${OBJECTDIR}/global.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/global.o   global.c 
	@${DEP_GEN} -d ${OBJECTDIR}/global.o 
	@${FIXDEPS} "${OBJECTDIR}/global.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/fsm.o: fsm.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fsm.o.d 
	@${RM} ${OBJECTDIR}/fsm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/fsm.o   fsm.c 
	@${DEP_GEN} -d ${OBJECTDIR}/fsm.o 
	@${FIXDEPS} "${OBJECTDIR}/fsm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/uart.o: uart.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart.o.d 
	@${RM} ${OBJECTDIR}/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/uart.o   uart.c 
	@${DEP_GEN} -d ${OBJECTDIR}/uart.o 
	@${FIXDEPS} "${OBJECTDIR}/uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Environmental_Monitoring.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o ${DISTDIR}/Environmental_Monitoring.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
${DISTDIR}/Environmental_Monitoring.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o ${DISTDIR}/Environmental_Monitoring.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
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
