set -ev
make buildtype=test verbose=yes dotout=no
zest ./tests/ || more /tmp/zest/output.txt
