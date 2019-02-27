#-------------------------------------------------
#
# Project created by QtCreator 2019-02-26T12:53:44
#
#-------------------------------------------------

QT       -= core gui

TARGET   = FlexSEA-Stack-Plan
TEMPLATE = lib
CONFIG  += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS \
			BUILD_SHARED_LIB_DLL  \
			TEST_PC \
			INCLUDE_UPROJ_ACTPACK \
			BOARD_TYPE_FLEXSEA_PLAN

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH +=  inc         \
                flexsea-comm/inc \
                flexsea-dephy/inc \
                flexsea-dephy/CycleTester/inc \
                flexsea-dephy/DpEb42/inc \
                flexsea-projects/inc \
                flexsea-projects/ActPack/inc \
                flexsea-projects/MIT_2DoF_Ankle_v1/inc \
                flexsea-projects/MIT_DLEG/inc \
                flexsea-projects/MIT_PocketClimbing/inc \
                flexsea-projects/RICNU_Knee_v1/inc \
                flexsea-projects/Rigid/inc \
                flexsea-shared/inc   \
                flexsea-system/inc

SOURCES += \
    flexsea-comm/src/flexsea.c \
    flexsea-comm/src/flexsea_buffers.c \
    flexsea-comm/src/flexsea_circular_buffer.c \
    flexsea-comm/src/flexsea_comm.c \
    flexsea-comm/src/flexsea_comm_multi.c \
    flexsea-comm/src/flexsea_interface.c \
    flexsea-comm/src/flexsea_multi_circbuff.c \
    flexsea-comm/src/flexsea_payload.c \
    flexsea-dephy/CycleTester/src/cmd-CycleTester.c \
    flexsea-dephy/CycleTester/src/user-mn-CycleTester.c \
    flexsea-dephy/DpEb42/src/analyzeGait.c \
    flexsea-dephy/DpEb42/src/cmd-DpEb42.c \
    flexsea-dephy/DpEb42/src/cmd-GaitStats.c \
    flexsea-dephy/DpEb42/src/cmd-UTT.c \
    flexsea-dephy/DpEb42/src/corr-fun.c \
    flexsea-dephy/DpEb42/src/exoAngles.c \
    flexsea-dephy/DpEb42/src/user-ex-DpEb42.c \
    flexsea-dephy/DpEb42/src/user-mn-DpEb42.c \
    flexsea-dephy/DpEb42/src/walkingController.c \
    flexsea-dephy/src/dephy-ex.c \
    flexsea-dephy/src/dephy-mn.c \
    flexsea-dephy/src/flexsea_cmd_angle_torque_profile.c \
    flexsea-dephy/src/flexsea_cmd_dephy.c \
    flexsea-dephy/src/flexsea_dephy_structs.c \
    flexsea-projects/ActPack/src/cmd-ActPack.c \
    flexsea-projects/ActPack/src/user-ex-ActPack.c \
    flexsea-projects/ActPack/src/user-mn-ActPack.c \
    flexsea-projects/MIT_2DoF_Ankle_v1/src/cmd-MIT_2DoF_Ankle_v1.c \
    flexsea-projects/MIT_2DoF_Ankle_v1/src/user-ex-MIT_2DoF_Ankle_v1.c \
    flexsea-projects/MIT_2DoF_Ankle_v1/src/user-mn-MIT_2DoF_Ankle_v1.c \
    flexsea-projects/MIT_DLEG/src/user-mn-MIT-DLeg.c \
    flexsea-projects/MIT_PocketClimbing/src/user-mn-MIT-PocketClimb.c \
    flexsea-projects/RICNU_Knee_v1/src/cmd-RICNU_Knee_v1.c \
    flexsea-projects/RICNU_Knee_v1/src/user-ex-RICNU_Knee_v1.c \
    flexsea-projects/RICNU_Knee_v1/src/user-mn-RICNU_Knee_v1.c \
    flexsea-projects/Rigid/src/cmd-Bilateral.c \
    flexsea-projects/Rigid/src/cmd-Pocket.c \
    flexsea-projects/Rigid/src/cmd-Rigid.c \
    flexsea-projects/Rigid/src/user-mn-Rigid.c \
    flexsea-projects/src/dynamic_user_structs_common.c \
    flexsea-projects/src/dynamic_user_structs_exec.c \
    flexsea-projects/src/dynamic_user_structs_manage.c \
    flexsea-projects/src/dynamic_user_structs_plan.c \
    flexsea-projects/src/flexsea_cmd_user.c \
    flexsea-projects/src/flexsea_user_structs.c \
    flexsea-projects/src/mn-MotorControl.c \
    flexsea-projects/src/user-ex-rigid.c \
    flexsea-projects/src/user-ex.c \
    flexsea-projects/src/user-mn.c \
    flexsea-shared/unity/unity.c \
    flexsea-system/src/flexsea_cmd_calibration.c \
    flexsea-system/src/flexsea_cmd_control_1.c \
    flexsea-system/src/flexsea_cmd_control_2.c \
    flexsea-system/src/flexsea_cmd_data.c \
    flexsea-system/src/flexsea_cmd_external.c \
    flexsea-system/src/flexsea_cmd_in_control.c \
    flexsea-system/src/flexsea_cmd_sensors.c \
    flexsea-system/src/flexsea_cmd_stream.c \
    flexsea-system/src/flexsea_cmd_sysdata.c \
    flexsea-system/src/flexsea_cmd_tools.c \
    flexsea-system/src/flexsea_device_spec.c \
    flexsea-system/src/flexsea_global_structs.c \
    flexsea-system/src/flexsea_system.c \
    flexsea-system/src/fm_block_allocator.c \
    src/flexsea_board.c \
    src/flexsea_config.c \
    src/revision.c \
    src/trapez.c

HEADERS += \
    flexsea-comm/inc/commStackConfig.h \
    flexsea-comm/inc/flexsea.h \
    flexsea-comm/inc/flexsea_buffers.h \
    flexsea-comm/inc/flexsea_circular_buffer.h \
    flexsea-comm/inc/flexsea_comm.h \
    flexsea-comm/inc/flexsea_comm_def.h \
    flexsea-comm/inc/flexsea_comm_multi.h \
    flexsea-comm/inc/flexsea_interface.h \
    flexsea-comm/inc/flexsea_multi_circbuff.h \
    flexsea-comm/inc/flexsea_multi_frame_packet_def.h \
    flexsea-comm/inc/flexsea_payload.h \
    flexsea-dephy/CycleTester/inc/cmd-CycleTester.h \
    flexsea-dephy/CycleTester/inc/user-mn-CycleTester.h \
    flexsea-dephy/DpEb42/inc/analyzeGait.h \
    flexsea-dephy/DpEb42/inc/cmd-DpEb42.h \
    flexsea-dephy/DpEb42/inc/cmd-GaitStats.h \
    flexsea-dephy/DpEb42/inc/cmd-UTT.h \
    flexsea-dephy/DpEb42/inc/corr-fun.h \
    flexsea-dephy/DpEb42/inc/exoAngles.h \
    flexsea-dephy/DpEb42/inc/exoDef.h \
    flexsea-dephy/DpEb42/inc/user-ex-DpEb42.h \
    flexsea-dephy/DpEb42/inc/user-mn-DpEb42.h \
    flexsea-dephy/DpEb42/inc/walkingController.h \
    flexsea-dephy/inc/dephy-ex.h \
    flexsea-dephy/inc/dephy-mn.h \
    flexsea-dephy/inc/flexsea_cmd_angle_torque_profile.h \
    flexsea-dephy/inc/flexsea_cmd_dephy.h \
    flexsea-dephy/inc/flexsea_dephy_structs.h \
    flexsea-projects/ActPack/inc/cmd-ActPack.h \
    flexsea-projects/ActPack/inc/user-ex-ActPack.h \
    flexsea-projects/ActPack/inc/user-mn-ActPack.h \
    flexsea-projects/inc/dynamic_user_structs.h \
    flexsea-projects/inc/flexsea_cmd_user.h \
    flexsea-projects/inc/flexsea_user_structs.h \
    flexsea-projects/inc/mn-MotorControl.h \
    flexsea-projects/inc/projectsStackConfig.h \
    flexsea-projects/inc/user-ex-rigid.h \
    flexsea-projects/inc/user-ex.h \
    flexsea-projects/inc/user-mn.h \
    flexsea-projects/inc/user-plan.h \
    flexsea-projects/inc/user-testPC.h \
    flexsea-projects/MIT_2DoF_Ankle_v1/inc/cmd-MIT_2DoF_Ankle_v1.h \
    flexsea-projects/MIT_2DoF_Ankle_v1/inc/user-ex-MIT_2DoF_Ankle_v1.h \
    flexsea-projects/MIT_2DoF_Ankle_v1/inc/user-mn-MIT_2DoF_Ankle_v1.h \
    flexsea-projects/MIT_DLEG/inc/user-mn-MIT-DLeg.h \
    flexsea-projects/MIT_PocketClimbing/inc/user-mn-MIT-PocketClimb.h \
    flexsea-projects/RICNU_Knee_v1/inc/cmd-RICNU_Knee_v1.h \
    flexsea-projects/RICNU_Knee_v1/inc/user-ex-RICNU_Knee_v1.h \
    flexsea-projects/RICNU_Knee_v1/inc/user-mn-RICNU_Knee_v1.h \
    flexsea-projects/Rigid/inc/cmd-Bilateral.h \
    flexsea-projects/Rigid/inc/cmd-Pocket.h \
    flexsea-projects/Rigid/inc/cmd-Rigid.h \
    flexsea-projects/Rigid/inc/user-mn-Rigid.h \
    flexsea-shared/unity/unity.h \
    flexsea-shared/unity/unity_internals.h \
    flexsea-system/inc/flexsea_cmd_calibration.h \
    flexsea-system/inc/flexsea_cmd_control.h \
    flexsea-system/inc/flexsea_cmd_data.h \
    flexsea-system/inc/flexsea_cmd_external.h \
    flexsea-system/inc/flexsea_cmd_in_control.h \
    flexsea-system/inc/flexsea_cmd_sensors.h \
    flexsea-system/inc/flexsea_cmd_stream.h \
    flexsea-system/inc/flexsea_cmd_sysdata.h \
    flexsea-system/inc/flexsea_cmd_tools.h \
    flexsea-system/inc/flexsea_dataformats.h \
    flexsea-system/inc/flexsea_device_spec.h \
    flexsea-system/inc/flexsea_embedded_mutex.h \
    flexsea-system/inc/flexsea_global_structs.h \
    flexsea-system/inc/flexsea_sys_def.h \
    flexsea-system/inc/flexsea_system.h \
    flexsea-system/inc/fm_block_allocator.h \
    flexsea-system/inc/systemStackConfig.h \
    inc/flexsea_board.h \
    inc/flexsea_config.h \
    inc/flexsea_device_spec_defs.h \
    inc/git_rev_data.h \
    inc/revision.h \
    inc/trapez.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

# Update revision information
PRE_TARGETDEPS      += git_rev_data.h
QMAKE_EXTRA_TARGETS += sharedRevTarget
sharedRevTarget.target = git_rev_data.h
win32: sharedRevTarget.commands = cd $$PWD && python.exe $$PWD/git-revision.py -o $$PWD/inc/git_rev_data.h
else:  sharedRevTarget.commands = python $$PWD/git-revision.py -o $$PWD/inc/git_rev_data.h
sharedRevTarget.depends = FORCE
