/*
 * %CopyrightBegin%
 *
 * Copyright Ericsson AB 1996-2024. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * %CopyrightEnd%
 */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include "sys.h"

/* II. Prototypes */

/* II.I Spawn prototypes */
EXTERN ErlDrvData spawn_start(ErlDrvPort, char*, SysDriverOpts*);
EXTERN ErlDrvSSizeT spawn_control(ErlDrvData, unsigned int, char *,
                                  ErlDrvSizeT, char **, ErlDrvSizeT);

/* II.IV Common prototypes */
EXTERN void stop(ErlDrvData);
EXTERN void ready_input(ErlDrvData, ErlDrvEvent);
EXTERN void ready_output(ErlDrvData, ErlDrvEvent);
EXTERN void output(ErlDrvData, char*, ErlDrvSizeT);
EXTERN void stop_select(ErlDrvEvent, void*);

/* II.V Forker prototypes */
EXTERN ErlDrvData forker_start(ErlDrvPort, char*, SysDriverOpts*);
EXTERN void forker_stop(ErlDrvData);
EXTERN void forker_ready_input(ErlDrvData, ErlDrvEvent);
EXTERN void forker_ready_output(ErlDrvData, ErlDrvEvent);
EXTERN ErlDrvSSizeT forker_control(ErlDrvData, unsigned int, char *,
                                   ErlDrvSizeT, char **, ErlDrvSizeT);

/* III Driver entries */

/* III.I The spawn driver */
struct erl_drv_entry spawn_driver_entry = {
#ifdef __WIN32__
    spawn_init,
#else
    NULL, /* init */
#endif
    spawn_start,
    stop,
    output,
    ready_input,
    ready_output,
    "spawn",
    NULL, /* finish */
    NULL, /* handle */
    spawn_control,
    NULL, /* timeout */
    NULL, /* outputv */
    NULL, /* ready_async */
    NULL, /* flush */
    NULL, /* call */
    NULL, /* event */
    ERL_DRV_EXTENDED_MARKER,
    ERL_DRV_EXTENDED_MAJOR_VERSION,
    ERL_DRV_EXTENDED_MINOR_VERSION,
#ifdef __WIN32__
    0,	/* driver_flags */
#else
    ERL_DRV_FLAG_USE_PORT_LOCKING | ERL_DRV_FLAG_USE_INIT_ACK,
#endif
    NULL, /* handle2 */
    NULL, /* process_exit */
    stop_select,
    NULL /* emergency_close */
};

/* III.III The forker driver */
struct erl_drv_entry forker_driver_entry = {
    NULL, /* init */
    forker_start,
    forker_stop,
    NULL, /* output */
    forker_ready_input,
    forker_ready_output,
    "spawn_forker",
    NULL, /* finish */
    NULL, /* handle */
    forker_control,
    NULL, /* timeout */
    NULL, /* outputv */
    NULL, /* ready_async */
    NULL, /* flush */
    NULL, /* call */
    NULL, /* event */
    ERL_DRV_EXTENDED_MARKER,
    ERL_DRV_EXTENDED_MAJOR_VERSION,
    ERL_DRV_EXTENDED_MINOR_VERSION,
    0, /* driver_flags */
    NULL, /* handle2 */
    NULL, /* process_exit */
    stop_select,
    NULL /* emergency_close */
};
