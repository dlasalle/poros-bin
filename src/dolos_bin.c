/**
 * @file dolos_bin.c
 * @brief The Dolos binary.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2018
 * @version 1
 * @date 2018-09-06
 */

#include "dolos.h"
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
  
  dolos_pid_type const numParts = (dolos_pid_type)atoi(argv[2]);
  if (numParts <= 0) {
    printf("Invalid number of parts: %s\n", argv[2]);
    return 1;
  }

  int nvwgts;
  int ewgts;
  dolos_vtx_type nvtxs;
  dolos_adj_type nedges;
  dolos_adj_type * xadj;
  dolos_vtx_type * adjncy;
  dolos_wgt_type * vwgt;
  dolos_wgt_type * adjwgt;

  int const readSuccess = wildriver_read_graph(graphFilename, &nvtxs, \
      &nedges, &nvwgts, &ewgts, &xadj, &adjncy, &vwgt, &adjwgt);
  if (!readSuccess) {
    printf("Failed to read graph: %s\n", graphFilename);
    return 1;
  }

  if (vwgt == NULL) {
    vwgt = malloc(sizeof(dolos_wgt_type)*nvtxs);
    for (dolos_vtx_type v = 0; v < nvtxs; ++v) {
      vwgt[v] = 1;
    }
  }
  if (adjwgt == NULL) {
    adjwgt = malloc(sizeof(dolos_wgt_type)*nvtxs);
    for (dolos_adj_type e = 0; e < nedges; ++e) {
      adjwgt[e] = 1;
    }
  }

  dolos_options_struct opts = DOLOS_defaultOptions();
  opts.outputTimes = 1;

  if (argc >= 4) {
    opts.randomSeed = (unsigned int)atoi(argv[3]);
  }

  dolos_wgt_type cutWeight;
  dolos_pid_type * const part = malloc(sizeof(dolos_pid_type)*nvtxs);

  int const partSuccess = DOLOS_PartGraphRecursive(
      nvtxs, xadj, adjncy, vwgt, adjwgt, numParts, &opts, &cutWeight, part);
  if (!partSuccess) {
    printf("Failed to partition graph.\n");
    return 1;
  }

  printf("Cut graph into %d parts with a cut weight of %llu\n", \
      numParts, cutWeight);

  return 0;
}
