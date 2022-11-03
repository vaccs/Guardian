set -ev
make buildtype=debug
make buildtype=test
zest ./tests/
