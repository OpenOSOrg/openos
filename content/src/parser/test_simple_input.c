#include "myshell_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int
main(void)
{
  struct pipeline* my_pipeline = pipeline_build("ls\n");
  
  // Test that a pipeline was returned
  assert(my_pipeline != NULL);
  assert(!my_pipeline->is_background);
  assert(my_pipeline->commands != NULL);
  
  // Test the parsed args
  assert(strcmp("ls", my_pipeline->commands->command_args[0]) == 0);
  assert(my_pipeline->commands->command_args[1] == NULL);
  
  // Test the redirect state
  assert(my_pipeline->commands->redirect_in_path == NULL);
  assert(my_pipeline->commands->redirect_out_path == NULL);
  
  // Test that there is only one parsed command in the pipeline
  assert(my_pipeline->commands->next == NULL);
  
  pipeline_free(my_pipeline);
}
