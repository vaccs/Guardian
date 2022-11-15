set -ev
make -j buildtype=debug   verbose=no  dotout=no
make -j buildtype=debug   verbose=no  dotout=yes
make -j buildtype=debug   verbose=yes dotout=no
make -j buildtype=debug   verbose=yes dotout=yes
make -j buildtype=test    verbose=no  dotout=no
make -j buildtype=test    verbose=no  dotout=yes
make -j buildtype=test    verbose=yes dotout=no
make -j buildtype=test    verbose=yes dotout=yes
make -j buildtype=release verbose=no  dotout=no
make -j buildtype=release verbose=no  dotout=yes
make -j buildtype=release verbose=yes dotout=no
make -j buildtype=release verbose=yes dotout=yes
