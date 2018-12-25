/**
 * @file poros_bin.c
 * @brief The Poros binary.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2018
 * @version 1
 * @date 2018-09-06
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "poros.h"
#include "wildriver.h"

#include <stdio.h>


int main(
    int const argc,
    char const * const * const argv)
{
  if (argc < 3) {
    printf("Usage: %s <graph> <num parts> [seed]\n", argv[0]);
    return 1;
  }

  char const * const graphFilename = argv[1];
  
  poros_pid_type const numParts = (poros_pid_type)atoi(argv[2]);
  if (numParts <= 0) {
    printf("Invalid number of parts: %s\n", argv[2]);
    return 1;
  }

  wildriver_graph_handle * handle = wildriver_open_graph( \
      graphFilename, \
      WILDRIVER_IN);

  poros_vtx_type const nvtxs = handle->nvtxs;
  poros_adj_type const nedges = handle->nedges;

  if (handle->ewgt) {
    printf("Has edge weights\n.");
  }

  poros_adj_type * xadj = malloc(sizeof(poros_adj_type)*(nvtxs+1));
  poros_vtx_type * adjncy = malloc(sizeof(poros_vtx_type)*nedges);
  poros_wgt_type * vwgt = handle->nvwgt == 0 ? NULL : malloc(sizeof(poros_wgt_type)*nvtxs);
  poros_wgt_type * adjwgt = handle->ewgt ? malloc(sizeof(poros_wgt_type)*nedges) : NULL;

  int const readSuccess = wildriver_load_graph( \
      handle, xadj, adjncy, vwgt, adjwgt, NULL);
  if (!readSuccess) {
    printf("Failed to read graph: %s\n", graphFilename);
    return 1;
  }
  wildriver_close_graph(handle);

  poros_options_struct opts = POROS_defaultOptions();
  opts.outputTimes = 1;

  if (argc >= 4) {
    opts.randomSeed = (unsigned int)atoi(argv[3]);
  }

  poros_wgt_type cutWeight;
  poros_pid_type * const part = malloc(sizeof(poros_pid_type)*nvtxs);

  int const partSuccess = POROS_PartGraphRecursive(
      nvtxs, xadj, adjncy, vwgt, adjwgt, numParts, &opts, &cutWeight, part);
  if (!partSuccess) {
    printf("Failed to partition graph.\n");
    return 1;
  }

  printf("Cut graph into %d parts with a cut weight of %llu\n", \
      numParts, cutWeight);

  return 0;
}
