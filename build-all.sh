set -ev
make -j buildtype=debug
make -j buildtype=test
# make -j buildtype=release
