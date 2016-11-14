==========
optdrivers
==========

Analysis drivers for general optimization.

How to build drivers
--------------------
.. code:: shell

  mkdir bld
  cd bld
  cmake ../
  make
  make install

List of available drivers:

* ``flamedriver_oc``: orbit correction driver

To test if the driver(s) could be evoked correctly:
simply execute ``flamedriver_oc``, if error like 'cannot find 
libflame_core.so' happens, just add the path to ``LD_LIBRARY_PATH``
environ value.

Tong Zhang

2016-11-10 15:54:17 PM EST
