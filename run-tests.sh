set -ev
make -j buildtype=test verbose=yes
zest ./tests/ || more /tmp/zest/output.txt
