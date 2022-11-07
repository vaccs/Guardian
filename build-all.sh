set -ev
make -j buildtype=debug   verbose=yes
make -j buildtype=debug   verbose=no
make -j buildtype=test    verbose=yes
make -j buildtype=test    verbose=no
make -j buildtype=release verbose=yes
make -j buildtype=release verbose=no
