set -ev
unset on_error
make buildtype=debug   verbose=no  dotout=no  &
make buildtype=debug   verbose=no  dotout=yes &
make buildtype=debug   verbose=yes dotout=no  &
make buildtype=debug   verbose=yes dotout=yes &
make buildtype=test    verbose=no  dotout=no  &
make buildtype=test    verbose=no  dotout=yes &
make buildtype=test    verbose=yes dotout=no  &
make buildtype=test    verbose=yes dotout=yes &
make buildtype=release verbose=no  dotout=no  &
make buildtype=release verbose=no  dotout=yes &
make buildtype=release verbose=yes dotout=no  &
make buildtype=release verbose=yes dotout=yes &
wait


