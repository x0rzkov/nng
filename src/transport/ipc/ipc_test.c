//
// Copyright 2020 Staysail Systems, Inc. <info@staysail.tech>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

#include <nng/nng.h>
#include <nng/protocol/pair0/pair.h>
#include <nng/transport/ipc/ipc.h>

#include <testutil.h>

#include <acutest.h>

void
test_abstract_sockets(void)
{
#ifdef NNG_HAVE_ABSTRACT_SOCKETS
	nng_socket s1;
	nng_socket s2;
	char       addr[64];

	testutil_scratch_addr("ipc+abstract", sizeof(addr), addr);

	TEST_NNG_PASS(nng_pair0_open(&s1));
	TEST_NNG_PASS(nng_pair0_open(&s2));
	TEST_NNG_PASS(testutil_marry_ex(s1, s2, addr, NULL, NULL));
	TEST_NNG_SEND_STR(s1, "ping");
	TEST_NNG_RECV_STR(s2, "ping");
        TEST_NNG_PASS(nng_close(s1));
        TEST_NNG_PASS(nng_close(s2));
#endif
}

TEST_LIST = {
	{ "ipc abstract sockets", test_abstract_sockets },
	{ NULL, NULL },
};