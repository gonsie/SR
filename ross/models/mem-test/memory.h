#ifndef INC_mem_h
#define INC_mem_h

#include <ross.h>

	/*
	 * Model Types
	 */

struct mem_state_t;
typedef mem_state_t mem_state;
struct mem_message_t;
typedef mem_message_t mem_message;
struct mem_statistics_t;
typedef mem_statistics_t mem_statistics;
struct mem_packet_t;
typedef mem_packet_t mem_packet;

struct mem_statistics_t
{
	tw_stat s_rb;
	tw_stat s_sent;
	tw_stat s_recv;

	tw_stat s_mem_alloc;
	tw_stat s_mem_free;

	tw_stat s_mem_alloc_rc;
	tw_stat s_mem_free_rc;

	tw_stat s_mem_get;
	tw_stat s_mem_get_rc;
};

struct mem_state_t
{
	mem_statistics	 stats;
	long int	 dummy_state;
};

struct mem_message_t
{
	long int	 dummy_data;
};

struct mem_packet_t
{
	char bytes[64];
};

	/*
	 * Model Globals
	 */

static unsigned int offset_lpid = 0;
static tw_stime mult = 1.4;
static tw_stime percent_remote = 0.25;
static unsigned int ttl_lps = 0;
static unsigned int nlp_per_pe = 8;
static int g_mem_start_events = 1;
static int optimistic_memory = 100;

// rate for timestamp exponential distribution
static tw_stime mean = 1.0;

static char run_id[1024] = "undefined";

static unsigned int nbufs = 1;
static mem_statistics g_stats;
static char test_string [64] = "This is a test!";
static tw_fd	my_fd;

#endif
