set -ev
make -j buildtype=debug
make -j buildtype=test
make -j buildtype=release
zest ./tests/ || more /tmp/zest/output.txt
