
# Guardian

The integrity of systems files is necessary for the secure functioning of an
operating system. Integrity is not generally discussed in terms of complete
computer systems. Instead, integrity issues tend to be either tightly coupled
to a particular domain (e.g. database constraints), or else so broad as to be
useless except after the fact (e.g. backups). Often, file integrity is
determined by who modifies the file or by a checksum. This repository focuses
on a general model of the internal integrity of a file. Even if a file is
modified by a subject with trust or has a valid checksum, it may not meet the
specification of a valid file. An example would be a password file with no user
assigned a user id of 0. This repository hosts a program called Guardian that
provides a means to specify what the contents of a valid file should be. Guardian
can be used to specify the format and valid properties of system configuration
files and others.
