MPI Toys
========

Author: Jonah Miller (jonah.maxwell.miller@gmail.com)

Time-stamp: <2017-02-21 15:22:15 (jmiller)>

# Description

This is a simple collection of toy codes that I use to test and play
around with MPI. It can be useful for diagnostics.

# Options to use:

I use the following options with these codes when I call `mpirun` or `mpiexec`

```bash
--mca btl_base_verbose 100 \
--mca btl self,vader,openib \
--mca btl_tcp_if_include eth0 \
--mca oob_tcp_if_include eth0 \
--display-map
```

