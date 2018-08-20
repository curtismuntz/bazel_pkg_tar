Repo for showing current issues with pkg_tar.

Build via `bazel build src:foo_tar`


I've set up a cpp example with a system installed dependency. If you don't have boost installed, for this to work correctly you'll have to install:
`sudo apt-get install libboost-program-options-dev`

Depending on your system, the .so files might be in another base location. Use `apt-file list` to find the install path and modify `WORKSPACE` and `//third_party/boost.BUILD` accrodingly. On my machine:

```
murt•~/murt/bazel_pkg_tar(master⚡)» apt-file list libboost-program-options                                                                          [9:33:54]
libboost-program-options-dev: /usr/share/doc/libboost-program-options-dev/changelog.gz
libboost-program-options-dev: /usr/share/doc/libboost-program-options-dev/copyright
libboost-program-options1.58-dev: /usr/lib/x86_64-linux-gnu/libboost_program_options.a
libboost-program-options1.58-dev: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
libboost-program-options1.58-dev: /usr/share/doc/libboost-program-options1.58-dev/changelog.Debian.gz
libboost-program-options1.58-dev: /usr/share/doc/libboost-program-options1.58-dev/copyright
libboost-program-options1.58.0: /usr/lib/x86_64-linux-gnu/libboost_program_options.so.1.58.0
libboost-program-options1.58.0: /usr/share/doc/libboost-program-options1.58.0/changelog.Debian.gz
libboost-program-options1.58.0: /usr/share/doc/libboost-program-options1.58.0/copyright
libboost-program-options1.58.0: /usr/share/lintian/overrides/libboost-program-options1.58.0
```


The resultant issue can be seen here:
```
murt•Desktop/tmp/extracted_tarball» ldd opt/cpp/foo_cpp                                                                                                         [15:05:29]
	linux-vdso.so.1 =>  (0x00007ffeb0bea000)
	libboost_program_options.so.1.58.0 => /usr/lib/x86_64-linux-gnu/libboost_program_options.so.1.58.0 (0x00007fc5c06fe000)
	libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007fc5c037c000)
	libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007fc5c0073000)
	libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007fc5bfe5d000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fc5bfa93000)
	libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007fc5bf876000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fc5c097c000)
murt•Desktop/tmp/extracted_tarball» ldd opt/__main__/src/cpp/foo_cpp                                                                                            [15:05:37]
	linux-vdso.so.1 =>  (0x00007ffc3f363000)
	libboost_program_options.so.1.58.0 => /home/murt/Desktop/tmp//tmp/extracted_tarball/opt/__main__/src/cpp/../../_solib_k8/_U@local_Uboost_S_S_Cboost___Uexternal_Slocal_Uboost_Slib_Sx86_U64-linux-gnu/libboost_program_options.so.1.58.0 (0x00007fab0d86c000)
	libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007fab0d4ea000)
	libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007fab0d1e1000)
	libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007fab0cfcb000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fab0cc01000)
	libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007fab0c9e4000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fab0daea000)
```

Note that one ldd shows the correct boost program options linkage in the `_solib_k8` directory but the top level linkage is choosing system installed boost (and on a system without it installed it results to 'not found')