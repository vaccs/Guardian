set -ev
make -j buildtype=release verbose=yes dotout=no
zest ./tests/ || more /tmp/zest/output.txt
