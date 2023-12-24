#include "myshell_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// this is just a copy of test_simple input, so we can show two test programs 

#define TEST_ASSERT(x) do { \
	if (!(x)) { \
		fprintf(stderr, "%s:%d: Assertion (%s) failed!\n", \
				__FILE__, __LINE__, #x); \
	       	abort(); \
	} \
} while(0)

int
main(void)
{
	struct pipeline* my_pipeline = pipeline_build("ls | cat\n");

	// Test that a pipeline was returned
	TEST_ASSERT(my_pipeline != NULL);
	TEST_ASSERT(!my_pipeline->is_background);
	TEST_ASSERT(my_pipeline->commands != NULL);

	// Test the parsed args
	TEST_ASSERT(strcmp("ls", my_pipeline->commands->command_args[0]) == 0);
	TEST_ASSERT(my_pipeline->commands->command_args[1] == NULL);

	// Test the redirect state
	TEST_ASSERT(my_pipeline->commands->redirect_in_path == NULL);
	TEST_ASSERT(my_pipeline->commands->redirect_out_path == NULL);

	// Test that there are multiple parsed command in the pipeline
	TEST_ASSERT(my_pipeline->commands->next != NULL);

	// keep going... what should we be testign next
	pipeline_free(my_pipeline);
}
