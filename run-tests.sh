set -ev
make buildtype=debug
make buildtype=test
zest ./tests/ || more /tmp/zest/output.txt
