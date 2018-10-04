/**
 * Copyright 2017 Comcast Cable Communications Management, LLC
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
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <CUnit/Basic.h>

#include "../src/libseshat.h"

/*----------------------------------------------------------------------------*/
/*                                   Mocks                                    */
/*----------------------------------------------------------------------------*/
#define UNUSED(x) (void)(x)

int nn_socket (int domain, int protocol)
{
    UNUSED(domain); UNUSED(protocol);
    return 100;
}

int nn_shutdown (int s, int how)
{
    UNUSED(s); UNUSED(how);
    return 0;
}

int nn_setsockopt (int s, int level, int option, const void *optval, size_t optvallen)
{
    UNUSED(s); UNUSED(level); UNUSED(option); UNUSED(optval); UNUSED(optvallen);
    return -1;
}

int nn_close (int s)
{
    UNUSED(s);
    return 0;
}

int nn_connect (int s, const char *addr)
{
    UNUSED(s); UNUSED(addr);
    return 0;
}

int nn_send (int s, const void *buf, size_t len, int flags)
{
    UNUSED(s); UNUSED(buf); UNUSED(len); UNUSED(flags);
    return 1;
}

int nn_recv (int s, void *buf, size_t len, int flags)
{
    UNUSED(s); UNUSED(buf); UNUSED(len); UNUSED(flags);
    return 1;
}

int nn_freemsg (void *msg)
{
    UNUSED(msg);
    return 0;
}


/*----------------------------------------------------------------------------*/
/*                                   Macros                                   */
/*----------------------------------------------------------------------------*/
#define SESHAT_URL "ipc:///tmp/sehsat_services.ipc"

/*----------------------------------------------------------------------------*/
/*                               Data Structures                              */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                            File Scoped Variables                           */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                             Function Prototypes                            */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                             Internal functions                             */
/*----------------------------------------------------------------------------*/
void test_failure( void )
{
    CU_ASSERT(-4 == init_lib_seshat(SESHAT_URL));
}

void add_suites( CU_pSuite *suite )
{
    *suite = CU_add_suite( "libseshat tests", NULL, NULL );
    CU_add_test( *suite, "Test failure", test_failure );
}

/*----------------------------------------------------------------------------*/
/*                             External Functions                             */
/*----------------------------------------------------------------------------*/
int main(void)
{
    unsigned rv = 1;
    CU_pSuite suite = NULL;
    
    if( CUE_SUCCESS == CU_initialize_registry() ) {
        add_suites( &suite );

        if( NULL != suite ) {
            CU_basic_set_mode( CU_BRM_VERBOSE );
            CU_basic_run_tests();
            printf( "\n" );
            CU_basic_show_failures( CU_get_failure_list() );
            printf( "\n\n" );
            rv = CU_get_number_of_tests_failed();
        }

        CU_cleanup_registry();
    }

    if( 0 != rv ) {
        return 1;
    }

    return 0;
}
